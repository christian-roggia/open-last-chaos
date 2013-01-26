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

#include "OutputBuffer.h"

CMemPool<unsigned char, 303600> g_outbufpool;

COutputBuffer::COutputBuffer(void)
{
    this->p_mempool = g_outbufpool.Get(true);
    this->p_remain = 0;
    this->p_net_msg = 0;
}

COutputBuffer::~COutputBuffer()
{
    g_outbufpool.Set(this->p_mempool);
    this->p_mempool = 0;
    this->p_remain = 0;
}

bool COutputBuffer::Add(CNetMsg &m_msg)
{
    uint32_t v3;
    uint16_t v4;
    uint32_t hostlong;
    uint16_t src;
    long m_out_msg_net;

    if(&m_msg)
    {
        m_out_msg_net = m_msg.p_len + 12;

        if(m_out_msg_net + this->p_remain > 303600)
            return false;

        src = 385;
        hostlong = this->p_net_msg++;
        v3 = m_msg.p_len;
        src = htons(src);
        hostlong = htonl(hostlong);
        v4 = htons(0);
        v3 = htonl(v3);

        memcpy(this->p_remain + this->p_mempool, &src, 2);
        this->p_remain += 2;
        memcpy(this->p_remain + this->p_mempool, &hostlong, 4);
        this->p_remain += 4;
        memcpy(this->p_remain + this->p_mempool, &v4, 2);
        this->p_remain += 2;
        memcpy(this->p_remain + this->p_mempool, &v3, 4);
        this->p_remain += 4;
        memcpy(this->p_remain + this->p_mempool, m_msg.p_data, m_msg.p_len);
        this->p_remain += m_msg.p_len;
    }

    return true;
}

bool COutputBuffer::Update(int a2)
{
    unsigned char *m_temp_array;

    if(a2 >= 0)
    {
        if(this->p_remain > a2)
        {
            m_temp_array = g_outbufpool.Get(true);
            memcpy(m_temp_array, this->p_mempool + a2, this->p_remain - a2);
            this->p_remain = 0;
            g_outbufpool.Set(this->p_mempool);
            this->p_mempool = m_temp_array;

            return false;
        }
        else
        {
            this->p_remain = 0;
            return true;
        }
    }

    return false;
}
