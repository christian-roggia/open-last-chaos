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

#include "NetMsg.h"

CMemPool<unsigned char, 1000> g_netmsgpool;

CNetMsg::CNetMsg(void)
{
    this->p_data = 0;
    this->Init();
}

CNetMsg::CNetMsg(CNetMsg const &net_msg)
{
    this->p_data = 0;
    this->Init(net_msg);
}

CNetMsg::CNetMsg(__tagMessageType msg_type)
{
    this->p_data = 0;
    this->Init(msg_type);
}

CNetMsg::~CNetMsg()
{
    if(this->p_data)
        g_netmsgpool.Set(this->p_data);

    this->p_msg_type    = 0;
    this->p_data        = 0;
    this->p_len         = 0;
    this->p_point       = 0;
}

void CNetMsg::Init(void)
{
    if(!this->p_data)
        this->p_data = g_netmsgpool.Get(false);
    
    this->p_msg_type    = 0;
    this->p_data        = g_netmsgpool.Get(false);
    this->p_len         = 0;
    this->p_point       = 0;
}

void CNetMsg::Init(__tagMessageType msg_type)
{
    this->Init();
    this->p_msg_type = msg_type;
    this->__ls(msg_type);
}

void CNetMsg::Init(CNetMsg const &net_msg)
{
    this->Init();
    this->p_msg_type     = net_msg.p_msg_type;
    this->p_len          = net_msg.p_len;
    this->p_point        = net_msg.p_point;
    memcpy(this->p_data, net_msg.p_data, net_msg.p_len);
}

void CNetMsg::Read(void *dest, long len)
{
    if(len <= 0)
        return;

    if(!this->CanRead(len))
        return;

    memcpy((char *)dest, (char *)(this->p_data + this->p_point), len);
    this->p_point += len;
}

void CNetMsg::Write(void *src, long len)
{
    if(len <= 0)
        return;

    if(!this->CanWrite(len))
        return;


    memcpy(this->p_data + this->p_point, src, len);
    this->p_point += len;

    if (this->p_point > this->p_len)
        this->p_len = this->p_point;
}

void CNetMsg::WriteRaw(void *write, long len)
{
    this->Init(*(uint8_t *)write);
    this->Write((char *)(((char *)write) + 1), len - 1);
    this->p_len = len;
    this->p_point = 0;
    this->MoveFirst();
}

void CNetMsg::__rs(char *dest)
{
    while(this->CanRead(1))
    {
        this->__rs(*dest);
        if(!*dest)
            break;

        dest++;
    }
}

void CNetMsg::__ls(char const *src)
{
    while (this->CanWrite(1))
    {
        this->__ls(*src);
        if(!*src)
            break;
        ++src;
    }
}
