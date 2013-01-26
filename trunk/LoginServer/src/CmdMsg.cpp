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
#include "Descriptor.h"

char g_buf[0x2000];
char g_buf2[0x2000];
char g_buf3[0x2000];

void FailMsg(CNetMsg &m_msg, __tagMsgFailType m_tag) // CHECKED
{
    m_msg.Init(1);
    m_msg.__ls((__tagMsgFailType)m_tag);
}

void LogoutReqMsg(CNetMsg &m_msg, int a1, int a2, int a3, CDescriptor *m_desc) // CHECKED
{
    m_msg.Init(101);
    m_msg.__ls((int)0);
    m_msg.__ls((int)a1);
    m_msg.__ls((int)a2);
    m_msg.__ls((int)a3);
    m_msg.__ls((unsigned char)6);
    m_msg.__ls((char const *)m_desc->Username);
    m_msg.__ls((char const *)m_desc->Password);
}

void PlayerReqMsg(CNetMsg &m_msg) // CHECKED
{
    m_msg.Init(111);
    m_msg.__ls((unsigned char)6);
}

void PlayerNumMsg(CNetMsg &m_msg, int a2, int a3, int m_conn_num) // CHECKED
{
    m_msg.Init(34);
    m_msg.__ls((int)a2);
    m_msg.__ls((int)a3);
    m_msg.__ls((int)gserver.p_connector_count);
    m_msg.__ls((int)(m_conn_num + 1));

    if(!gserver.p_connector_descs[m_conn_num] || gserver.p_connecting_connector[m_conn_num])
    {
        strcpy(g_buf, "Connector_");
        IntCat(g_buf, m_conn_num, false);
        m_msg.__ls((int)atoi(gserver.p_conf_file.Find(g_buf, "Number")));
        m_msg.__ls((int)atoi(gserver.p_conf_file.Find(g_buf, "MaxSubNumber")));

        for(int i = 0; i < gserver.p_connector_descs[m_conn_num]->MaxSubNumber; i++)
        {
            m_msg.__ls((int)(i + 1));
            m_msg.__ls((int)1998);
            m_msg.__ls((char const *)"");
            m_msg.__ls((int)0);
        }
    }
    else
    {
        m_msg.__ls((int)gserver.p_connector_descs[m_conn_num]->Number);
        m_msg.__ls((int)gserver.p_connector_descs[m_conn_num]->MaxSubNumber);
        
        for(int j = 0; j < gserver.p_connector_descs[m_conn_num]->MaxSubNumber; j++)
        {
            m_msg.__ls((int)gserver.p_connector_descs[m_conn_num]->ConnectorsID[j]);
            m_msg.__ls((int)(gserver.p_connector_descs[m_conn_num]->ConnectorsUnk[j] + 1999));
            m_msg.__ls((char const *)gserver.p_connector_descs[m_conn_num]->ConnectorsIP[j]);
            m_msg.__ls((int)gserver.p_connector_descs[m_conn_num]->ConnectorsUnk2[j]);
        }
    }
}

void ConLogoutReqMsg(CNetMsg &m_msg, char *m_data) // CHECKED
{
    m_msg.Init(111);
    m_msg.__ls((unsigned char)2);
    m_msg.__ls((char const *)m_data);
}
