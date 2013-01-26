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

#ifndef PROCCONNMSG_H
#define PROCCONNMSG_H

#include "DBCmd.h"
#include "Descriptor.h"
#include "NetMsg.h"
#include "Utils.h"

class CDescriptor;
class CUser;

void ConnLogin(CDescriptor *m_desc, CNetMsg &m_msg);
void ConnLogout(CDescriptor *m_desc, CNetMsg &m_msg);
void ConnBLogin(CDescriptor *m_desc, CNetMsg &m_msg);
void ConnBLogout(CDescriptor *m_desc, CNetMsg &m_msg);

signed int ReadDB(char const *a1, char const *a2, int a3, int a4, char const *a5, CUser **a6);
signed int WriteDB(int a1, int a2, int a3, int a4, int a5, char const *src, char const *a7, bool a8);
bool WriteDB(char const *m_idname);

void ConnPlayerReq(CDescriptor *m_desc, CNetMsg &m_msg);
void ConnPlaying(CDescriptor *m_desc, CNetMsg &m_msg);
void ConnPreopenGift(CDescriptor *m_desc, CNetMsg &m_msg);
void ConnLevelupPoint(CDescriptor *m_desc, CNetMsg &m_msg);
void ConnStashState(CDescriptor *m_desc, CNetMsg &m_msg);
void ConnStashCheckPassword(CDescriptor *m_desc, CNetMsg &m_msg);
void ConnStashChangePassword(CDescriptor *m_desc, CNetMsg &m_msg);
void ConnStashSeal(CDescriptor *m_desc, CNetMsg &m_msg);

#endif
