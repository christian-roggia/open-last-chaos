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
    this->MsgData = 0;
    this->Init();
}

CNetMsg::CNetMsg(CNetMsg const &net_msg)
{
    this->MsgData = 0;
    this->Init(net_msg);
}

CNetMsg::CNetMsg(__tagMessageType msg_type)
{
    this->MsgData = 0;
    this->Init(msg_type);
}

CNetMsg::~CNetMsg()
{
    if(this->MsgData)
        g_netmsgpool.Set(this->MsgData);

    this->MsgType       = 0;
    this->MsgData       = 0;
    this->MsgLength     = 0;
    this->MsgPointer    = 0;
}

void CNetMsg::Init(void)
{
    if(!this->MsgData)
        this->MsgData = g_netmsgpool.Get(false);
	
    this->MsgType       = 0;
    this->MsgData       = g_netmsgpool.Get(false);
    this->MsgLength     = 0;
    this->MsgPointer    = 0;
}

void CNetMsg::Init(__tagMessageType msg_type)
{
    this->Init();
    this->MsgType = msg_type;
    this->__ls(msg_type);
}

void CNetMsg::Init(CNetMsg const &net_msg)
{
    this->Init();
    this->MsgType        = net_msg.MsgType;
    this->MsgLength      = net_msg.MsgLength;
    this->MsgPointer     = net_msg.MsgPointer;
    memcpy(this->MsgData, net_msg.MsgData, net_msg.MsgLength);
}

void CNetMsg::Read(void *dest, int len)
{
    if(len <= 0)
        return;

    if(!this->CanRead(len))
        return;

    memcpy((char *)dest, (char *)(this->MsgData + this->MsgPointer), len);
    this->MsgPointer += len;
}

void CNetMsg::Write(void *src, int len)
{
    if(len <= 0)
        return;

    if(!this->CanWrite(len))
        return;


    memcpy(this->MsgData + this->MsgPointer, src, len);
    this->MsgPointer += len;

    if(this->MsgPointer > this->MsgLength)
        this->MsgLength = this->MsgPointer;
}

void CNetMsg::WriteRaw(void *write, int len)
{
    this->Init(*(char *)write);
    this->Write((char *)(((char *)write) + 1), len - 1);
    this->MsgLength = len;
    this->MsgPointer = 0;
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
