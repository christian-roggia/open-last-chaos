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

#include "OutputBuffer.hpp"

CMemPool<unsigned char, 303600> g_outbufpool;

bool COutputBuffer::Add(CNetMsg &net_msg)
{
    bool result; // al@2
    uint32_t v3; // [sp+14h] [bp-14h]@5
    uint16_t v4; // [sp+1Ah] [bp-Eh]@5
    uint32_t hostlong; // [sp+1Ch] [bp-Ch]@5
    uint16_t src; // [sp+22h] [bp-6h]@5
    int32_t v7; // [sp+24h] [bp-4h]@3

    if ( net_msg.p_msg_type )
    {
        v7 = net_msg.p_len + 12;
        if ( v7 + this->bufseek <= 303600 )
        {
            src = 385;
            hostlong = this->netmsg++;
            v4 = 0;
            v3 = net_msg.p_len;
            src = htons(src);
            hostlong = htonl(hostlong);
            v4 = htons(0);
            v3 = htonl(v3);
            memcpy(&this->mempool[this->bufseek], &src, 2u);
            this->bufseek += 2;
            memcpy(&this->mempool[this->bufseek], &hostlong, 4u);
            this->bufseek += 4;
            memcpy(&this->mempool[this->bufseek], &v4, 2u);
            this->bufseek += 2;
            memcpy(&this->mempool[this->bufseek], &v3, 4u);
            this->bufseek += 4;
            memcpy(&this->mempool[this->bufseek], net_msg.p_data, net_msg.p_len);
            this->bufseek += net_msg.p_len;
            result = 1;
        }
        else
        {
            result = 0;
        }
    }
    else
    {
        result = 1;
    }
    return result;
}

COutputBuffer::COutputBuffer()
{
    this->mempool = g_outbufpool.Get(1);
    this->bufseek = 0;
    this->netmsg = 0;
}

void COutputBuffer::Clear()
{
    this->bufseek = 0;
}

unsigned char *COutputBuffer::GetNextPoint()
{
    unsigned char *result; // eax@2

    if ( this->bufseek )
        result = this->mempool;
    else
        result = 0;
    return result;
}

int COutputBuffer::GetRemain()
{
    return this->bufseek;
}

uint8_t COutputBuffer::Update(int a2)
{
    uint8_t result; // al@2
    unsigned char *v3; // ST34_4@5

    if ( a2 >= 0 )
    {
        if ( this->bufseek > a2 )
        {
            v3 = g_outbufpool.Get(1);
            memcpy(v3, &this->mempool[a2], this->bufseek - a2);
            this->bufseek = 0;
            g_outbufpool.Set(this->mempool);
            this->mempool = v3;
            result = 0;
        }
        else
        {
            this->bufseek = 0;
            result = 1;
        }
    }
    else
    {
        result = 0;
    }
    return result;
}

COutputBuffer::~COutputBuffer()
{
    g_outbufpool.Set(this->mempool);
    this->mempool = 0;
    this->bufseek = 0;
    //delete [] this;
}
