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

#include "Descriptor.h"
#include "NetMsg.h"
#include "Utils.h"
#include "User.h"

class CUser;

typedef unsigned char _tagMsgConnErrorCode;

void LoginRepMsg(CNetMsg &m_msg, _tagMsgConnErrorCode m1, char const *m2, CUser *m3);
void PlayerRepMsg(CNetMsg &m_msg);
void PreopenGiftErrorMsg(CNetMsg &m_msg, int m1, int m2, _tagMsgConnErrorCode m3);
void StashStateMsg(CNetMsg &m_msg, int m1, int m2, char m3, char m4);
void StashCheckPasswordMsg(CNetMsg &m_msg, int m1, int m2, char m3);
void StashChangePasswordMsg(CNetMsg &m_msg, int m1, int m2, char const *m3, char m4);
void StashSealMsg(CNetMsg &m_msg, int m1, int m2, char m3);

extern char g_buf[0x2000];
extern char g_buf2[0x2000];
extern char g_buf3[0x2000];

#endif
