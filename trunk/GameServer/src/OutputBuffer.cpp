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
    this->MemoryPool = g_outbufpool.Get(true);
    this->Pointer = 0;
    this->NetMsgCount = 0;
}

COutputBuffer::~COutputBuffer()
{
    g_outbufpool.Set(this->MemoryPool);
    this->MemoryPool = 0;
    this->Pointer = 0;
}

bool COutputBuffer::Add(CNetMsg &m_msg)
{
    long v3;
    short v4;
    long hostlong;
    short src;
    long m_out_msg_net;

    if(&m_msg)
    {
        m_out_msg_net = m_msg.MsgLength + 12;

        if(m_out_msg_net + this->Pointer > 303600)
            return false;

        src = 385;
        hostlong = this->NetMsgCount++;
        v3 = m_msg.MsgLength;
        src = htons(src);
        hostlong = htonl(hostlong);
        v4 = htons(0);
        v3 = htonl(v3);

        memcpy(this->Pointer + this->MemoryPool, &src, 2);
        this->Pointer += 2;
        memcpy(this->Pointer + this->MemoryPool, &hostlong, 4);
        this->Pointer += 4;
        memcpy(this->Pointer + this->MemoryPool, &v4, 2);
        this->Pointer += 2;
        memcpy(this->Pointer + this->MemoryPool, &v3, 4);
        this->Pointer += 4;
        memcpy(this->Pointer + this->MemoryPool, m_msg.MsgData, m_msg.MsgLength);
        this->Pointer += m_msg.MsgLength;
    }

    return true;
}

bool COutputBuffer::Update(int a2)
{
    unsigned char *m_temp_array;

    if(a2 >= 0)
    {
        if(this->Pointer > a2)
        {
            m_temp_array = g_outbufpool.Get(true);
            memcpy(m_temp_array, this->MemoryPool + a2, this->Pointer - a2);
            this->Pointer = 0;
            g_outbufpool.Set(this->MemoryPool);
            this->MemoryPool = m_temp_array;

            return false;
        }
        else
        {
            this->Pointer = 0;
            return true;
        }
    }

    return false;
}
