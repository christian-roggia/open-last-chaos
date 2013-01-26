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

#ifndef CMDMSG_H
#define CMDMSG_H

#include "NetMsg.h"
#include "Utils.h"

class CDescriptor;
typedef unsigned char __tagMsgFailType;

void FailMsg(CNetMsg &net_msg, __tagMsgFailType tag);
void LogoutReqMsg(CNetMsg &net_msg, int a1, int a2, int a3, CDescriptor *m_desc);
void PlayerReqMsg(CNetMsg &net_msg);
void PlayerNumMsg(CNetMsg &net_msg, int a2, int a3, int a4);
void ConLogoutReqMsg(CNetMsg &net_msg, char *data);

extern char g_buf[0x2000];
extern char g_buf2[0x2000];
extern char g_buf3[0x2000];

#endif
