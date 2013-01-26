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

#include "CmdMsg.h"

char g_buf[0x2000];
char g_buf2[0x2000];
char g_buf3[0x2000];

void LoginRepMsg(CNetMsg &m_msg, _tagMsgConnErrorCode m1, char const *m2, CUser *m_user) // CHECKED
{
    m_msg.Init(112);
    m_msg.__ls((unsigned char)1);
    m_msg.__ls((char const *)m2);
    m_msg.__ls((unsigned char)m1);

    if(!m1)
    {
        m_msg.__ls((int)m_user->PortalIndex);
        m_msg.__ls((unsigned char)(*(char *)&m_user->Unk100));
        m_msg.__ls((int)m_user->Timestamp);
        m_msg.__ls((unsigned char)(*(char *)&m_user->Unk108));
        m_msg.__ls((unsigned char)(*(char *)&m_user->Unk112));
        m_msg.__ls((int)m_user->Unk104);
    }
}

void PlayerRepMsg(CNetMsg &m_msg) // CHECKED
{
    CDescriptor **m_descs_list;
    CDescriptor *m_current_desc;

    m_msg.Init(112);
    m_msg.__ls((unsigned char)7);
    m_msg.__ls((int)gserver.Number);
    m_msg.__ls((int)gserver.MaxSubServer);
    m_current_desc = gserver.ClientDescriptors;
    m_descs_list   = (CDescriptor **)malloc(sizeof(CDescriptor *) * gserver.MaxSubServer);
    memset(m_descs_list, 0, sizeof(CDescriptor *) * gserver.MaxSubServer);

    while(m_current_desc)
    {
        if(m_current_desc->Unk169)
            m_descs_list[m_current_desc->SubServerID - 1] = m_current_desc;

        m_current_desc = m_current_desc->Node;
    }

    for(int i = 1; i <= gserver.MaxSubServer; ++i)
    {
        m_msg.__ls((int)i);

        if(m_descs_list[i - 1])
        {
            m_msg.__ls((int)gserver.Users[m_descs_list[i - 1]->SubServerID - 1].UsersOnline);
            m_msg.__ls((char const *)m_descs_list[i - 1]->Unk170);
            m_msg.__ls((int)m_descs_list[i - 1]->Unk204);
        }
        else
        {
            m_msg.__ls((int)-1);
            m_msg.__ls((char const *)"");
            m_msg.__ls((int)0);
        }
    }
}

void PreopenGiftErrorMsg(CNetMsg &m_msg, int m1, int m2, _tagMsgConnErrorCode m3) // CHECKED
{
    m_msg.Init(112);
    m_msg.__ls((unsigned char)9);
    m_msg.__ls((int)m1);
    m_msg.__ls((int)m2);
    m_msg.__ls((char)m3);
}

void StashStateMsg(CNetMsg &m_msg, int m1, int m2, char m3, char m4) // CHECKED
{
    m_msg.Init(112);
    m_msg.__ls((unsigned char)11);
    m_msg.__ls((int)m1);
    m_msg.__ls((int)m2);
    m_msg.__ls((char)m3);
    m_msg.__ls((char)m4);
}

void StashCheckPasswordMsg(CNetMsg &m_msg, int m1, int m2, char m3) // CHECKED
{
    m_msg.Init(112);
    m_msg.__ls((char)12);
    m_msg.__ls((int)m1);
    m_msg.__ls((int)m2);
    m_msg.__ls((char const *)"");
    m_msg.__ls((char)m3);
}

void StashChangePasswordMsg(CNetMsg &m_msg, int m1, int m2, char const *m3, char m4) // CHECKED
{
    m_msg.Init(112);
    m_msg.__ls((unsigned char)13);
    m_msg.__ls((int)m1);
    m_msg.__ls((int)m2);
    m_msg.__ls((char const *)"");
    m_msg.__ls((char const *)m3);
    m_msg.__ls((char)m4);
}

void StashSealMsg(CNetMsg &m_msg, int m1, int m2, char m3) // CHECKED
{
    m_msg.Init(112);
    m_msg.__ls((unsigned char)14);
    m_msg.__ls((int)m1);
    m_msg.__ls((int)m2);
    m_msg.__ls((char)m3);
}
