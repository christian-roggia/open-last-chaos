/******************************************************************************************
  Copyright 2013 Christian Roggia

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
******************************************************************************************/

#include "InputBuffer.h"

CMemPool<unsigned char, 50600> g_inbufpool;

CInputBuffer::CInputBuffer(void)
{
    this->p_pool = g_inbufpool.Get(false);
    this->p_point = 0;
}

CInputBuffer::~CInputBuffer()
{
    g_inbufpool.Set(this->p_pool);
    this->p_pool = 0;
    this->p_point = 0;
}

void CInputBuffer::Clear(void)
{
    this->p_point = 0;
    memset(this->p_pool, 0, 50600);
}

char *CInputBuffer::GetPoint(void)
{
    return (char *)(this->p_pool + this->p_point);
}

long CInputBuffer::GetRemain(void)
{
    return 50600 - this->p_point;
}

void CInputBuffer::SetPoint(long new_point)
{
    this->p_point += new_point;
}

signed int CInputBuffer::GetMessage(CNetMsg &net_msg)
{
    unsigned char *m_temp_pool;
    uint32_t v4;
    uint16_t hostshort;
    uint32_t hostlong;
    uint16_t dest;
    unsigned char *m_pool_ptr;

    net_msg.Init();

    if(this->p_point <= 11)
        return 1;

    m_pool_ptr = this->p_pool;
    memcpy(&dest, this->p_pool, 2);
    m_pool_ptr += 2;
    memcpy(&hostlong, m_pool_ptr, 4);
    m_pool_ptr += 4;
    memcpy(&hostshort, m_pool_ptr, 2);
    m_pool_ptr += 2;
    memcpy(&v4, m_pool_ptr, 4);
    m_pool_ptr += 4;

    dest = htons(dest);
    hostlong = htonl(hostlong);
    hostshort = htons(hostshort);
    v4 = htonl(v4);

    if((signed int)(v4 + 12) > this->p_point)
        return 1;

    if((signed int)v4 > 1000 || (signed int)v4 < 0)
        return -1;

    net_msg.WriteRaw(m_pool_ptr, v4);
    m_pool_ptr += v4;
    this->p_point = this->p_point - 12 - v4;

    if(this->p_point > 0)
    {
        m_temp_pool = g_inbufpool.Get(false);
        memcpy(m_temp_pool, m_pool_ptr, this->p_point);
        g_inbufpool.Set(this->p_pool);
        this->p_pool = m_temp_pool;
    }

    return 0;
}

/********************************************************************************
 * Queue
 ********************************************************************************/

void CInputQueue::Clear(void)
{
    CMutex(&this->p_mutex, true);
    CNode *i;

    for(i = this->p_node; i; i = this->p_node)
    {
        this->p_node = i->p_sub_node;

        if(i)
            delete i;
    }

    this->p_node = 0;
    this->p_current_node = 0;
}

void CInputQueue::Add(CNetMsg &net_msg)
{
    CMutex(&this->p_mutex, true);
    CNode *node = new CNode(net_msg);

    if(this->p_node)
    {
        this->p_node->p_sub_node = node;
        this->p_current_node = node;
    }
    else
    {
        this->p_current_node = node;
        this->p_node = node;
    }
}

bool CInputQueue::Get(CNetMsg &net_msg)
{
    CMutex(&this->p_mutex, true);
    CNode *temp_node;

    if(this->IsEmpty())
        return false;

    temp_node = this->p_node;
    this->p_node = this->p_node->p_sub_node;

    if(!this->p_node)
        this->p_current_node = 0;

    net_msg.Init(*temp_node);

    if(temp_node)
        delete temp_node;

    net_msg.MoveFirst();

    return true;
}
