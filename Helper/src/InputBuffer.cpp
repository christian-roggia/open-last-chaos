/******************************************************************************************
  Copyright 2013 Andrea Ragusa

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

#include "InputBuffer.hpp"

CMemPool<unsigned char, 50600> g_inbufpool;

CInputBuffer::CInputBuffer()
{
    this->mempool = g_inbufpool.Get(0);
    this->bufseek = 0;
}

void CInputBuffer::Clear()
{
    memset(this->mempool, 0, 0xC5A8u);
    this->bufseek = 0;
}

signed int CInputBuffer::GetMessage(CNetMsg &netmsg)
{
    signed int result; // eax@2
    unsigned char *v3; // ST40_4@9
    int32_t v4; // [sp+20h] [bp-14h]@3
    uint16_t hostshort; // [sp+26h] [bp-Eh]@3
    uint32_t hostlong; // [sp+28h] [bp-Ch]@3
    uint16_t dest; // [sp+2Eh] [bp-6h]@3
    unsigned char *src; // [sp+30h] [bp-4h]@3

    netmsg.Init();
    if ( this->bufseek > 11 )
    {
        src = this->mempool;
        memcpy(&dest, src, 2u);
        src = src + 2;
        memcpy(&hostlong, src, 4u);
        src = src + 4;
        memcpy(&hostshort, src, 2u);
        src = src + 2;
        memcpy(&v4, src, 4u);
        src = src + 4;
        dest = htons(dest);
        hostlong = htonl(hostlong);
        hostshort = htons(hostshort);
        v4 = htonl(v4);
        if ( v4 + 12 <= this->bufseek )
        {
            if ( v4 <= 1000 && v4 >= 0 )
            {
                netmsg.WriteRaw(src, v4);
                src = src + v4;
                this->bufseek = this->bufseek - 12 - v4;
                if ( this->bufseek > 0 )
                {
                    v3 = g_inbufpool.Get(0);
                    memcpy(v3, src, this->bufseek);
                    g_inbufpool.Set(this->mempool);
                    this->mempool = (unsigned __int8 *)v3;
                }
                result = 0;
            }
            else
            {
                result = -1;
            }
        }
        else
        {
            result = 1;
        }
    }
    else
    {
        result = 1;
    }
    return result;
}

uint8_t *CInputBuffer::GetPoint()
{
    return &this->mempool[this->bufseek];
}

int CInputBuffer::GetRemain()
{
    return 50600 - this->bufseek;
}

void CInputBuffer::SetPoint(int point)
{
    this->bufseek += point;
}

CInputBuffer::~CInputBuffer()
{
    g_inbufpool.Set(this->mempool);
    this->mempool = 0;
    this->bufseek = 0;
    //delete [] this;
}

CInputQueue::CInputQueue()
{
    //CMutexObject::CMutexObject(&this->MutexObj);
    //this->MutexObj = new CMutexObject;
    this->curnode = 0;
    this->node = 0;
}

void CInputQueue::Add(CNetMsg &netmsg)
{
//    CNode *v2; // edi@1
    //CNode *newnode; // [sp+20h] [bp-Ch]@1
//    CMutex &m_mutex; // [sp+24h] [bp-8h]@1

    CMutex m_mutex = CMutex(&this->MutexObj, 1);
    //CMutex::CMutex(&m_mutex, &this->MutexObj, 1);
    CNode *newnode = new CNode(netmsg);
    //v2 = (CNode *)__builtin_new(24);
    //newnode = CInputQueue::CNode::CNode(v2, netmsg);
    if ( this->curnode )
    {
        this->node->subnode = newnode;
        this->node = newnode;
    }
    else
    {
        this->node = newnode;
        this->curnode = newnode;
    }
    //delete [] &m_mutex;
}

void CInputQueue::Clear()
{
    CNode *node; // [sp+10h] [bp-Ch]@1
    CMutex m_mutex = CMutex(&this->MutexObj, 1); // [sp+14h] [bp-8h]@1

    //CMutex::CMutex(&m_mutex, &this->MutexObj, 1);
    for ( node = this->curnode; node; node = this->curnode )
    {
        this->curnode = node->subnode;
        if ( node )
            delete [] node;
            //CInputQueue::CNode::_CNode(node, 3);
    }
    this->curnode = 0;
    this->node = 0;
    //delete [] &m_mutex;
    //CMutex::_CMutex(&m_mutex, 2);
}

bool CInputQueue::Get(CNetMsg &netmsg)
{
    CNode *node; // [sp+20h] [bp-Ch]@3
    CMutex m_mutex = CMutex(&this->MutexObj, 1); // [sp+24h] [bp-8h]@1

    //CMutex::CMutex(&m_mutex, &this->MutexObj, 1);
    if ( CInputQueue::IsEmpty() )
    {
        //delete [] &m_mutex;
        //CMutex::_CMutex(&m_mutex, 2);
        return 0;
    }
    else
    {
        node = this->curnode;
        this->curnode = this->curnode->subnode;
        if ( !this->curnode )
            this->node = 0;
        netmsg.Init(node->netmsg);
        //CNetMsg::Init(netmsg, &node->netmsg);
        if ( node )
            delete node;
            //CInputQueue::CNode::_CNode(node, 3);
        netmsg.MoveFirst();
        //CNetMsg::MoveFirst(netmsg);
        //delete [] &m_mutex;
        //CMutex::_CMutex(&m_mutex, 2);
        return 1;
    }
}

bool CInputQueue::IsEmpty()
{

    if ( this->curnode )
        return 0;
    else
        return 1;
}

CInputQueue::~CInputQueue()
{
    CInputQueue::Clear();
    //delete [] &this->MutexObj;
    //delete [] this;
}
