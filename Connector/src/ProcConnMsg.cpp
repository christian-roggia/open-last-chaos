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

#include "ProcConnMsg.h"

void ConnLogin(CDescriptor *m_desc, CNetMsg &m_msg)
{
    signed int v57;

    CNetMsg m_out_msg;
    long m_sub_server, m_server_num;
    CUser *m_user;
    char m_username[52], m_password[52], m_type, v62, v61[35];

    m_msg.MoveFirst();
    m_msg.__rs(m_type);
    m_msg.__rs(m_username);
    m_msg.__rs(m_password);
    m_msg.__rs(m_server_num);
    m_msg.__rs(m_sub_server);
    m_msg.__rs(v62);
    m_msg.__rs(v61);

    if(m_server_num != gserver.Number || m_sub_server <= 0 || m_sub_server > gserver.MaxSubServer)
    {
        g_gamelogbuffer.__ls(init("LOGIN_FAIL", m_username));
        g_gamelogbuffer.__ls("From");
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls((int)m_desc->SubServerID);
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls("No match : server no or sub no");
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls("Server");
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls((int)m_server_num);
        g_gamelogbuffer.__ls("-");
        g_gamelogbuffer.__ls((int)m_sub_server);
        g_gamelogbuffer.__ls(end);

        LoginRepMsg(m_out_msg, 1, m_username, 0);

        if(m_desc)
            m_desc->WriteToOutput(m_out_msg);

        return;
    }

    m_user = gserver.Users[m_sub_server - 1].Find(m_username);

    if(m_user)
    {
      if(v62 != 1 || m_user->Unk80 != 2)
      {
          g_gamelogbuffer.__ls(init("LOGIN_FAIL", m_username));
          g_gamelogbuffer.__ls("From");
          g_gamelogbuffer.__ls(delim);
          g_gamelogbuffer.__ls((int)m_desc->SubServerID);
          g_gamelogbuffer.__ls(delim);
          g_gamelogbuffer.__ls(3);
          g_gamelogbuffer.__ls(end);

          LoginRepMsg(m_out_msg, 3, m_username, 0);

          if(m_desc)
              m_desc->WriteToOutput(m_out_msg);
      }
      else
      {
          m_user->Unk80 = 1;

          LoginRepMsg(m_out_msg, 0, m_username, m_user);

          if(m_desc)
              m_desc->WriteToOutput(m_out_msg);
      }

      return;
    }

    v57 = ReadDB(m_username, m_password, m_server_num, m_sub_server, v61, &m_user);

    if(v57)
    {
        g_gamelogbuffer.__ls(init("LOGIN_FAIL", m_username));
        g_gamelogbuffer.__ls("From");
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls((int)m_desc->SubServerID);
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls(v57);
        g_gamelogbuffer.__ls(end);

        LoginRepMsg(m_out_msg, v57, m_username, 0);

        if(m_desc)
            m_desc->WriteToOutput(m_out_msg);

        return;
    }

    v57 = WriteDB(m_user->PortalIndex, m_server_num, m_sub_server, 0, m_user->Timestamp, m_user->Username, v61, true);

    if(v57)
    {
        g_gamelogbuffer.__ls(init("LOGIN_FAIL", m_username));
        g_gamelogbuffer.__ls("From");
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls((int)m_desc->SubServerID);
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls(v57);
        g_gamelogbuffer.__ls(end);

        LoginRepMsg(m_out_msg, v57, m_username, 0);

        if(m_desc)
            m_desc->WriteToOutput(m_out_msg);

        return;
    }

    if(gserver.Users[m_sub_server - 1].Add(m_user))
    {
        ++gserver.Users[m_sub_server - 1].Count[m_user->ZoneNum];

        if(gserver.BillingClient.IsRunning())
        {
            gserver.BillingClient.Login(0, 0, 0);
        }
        else
        {
            g_gamelogbuffer.__ls(init("NO BILLING - FREE MODE", m_username));
            g_gamelogbuffer.__ls("From");
            g_gamelogbuffer.__ls(delim);
            g_gamelogbuffer.__ls((int)m_desc->SubServerID);
            g_gamelogbuffer.__ls(delim);
            g_gamelogbuffer.__ls(end);
            m_user->Unk80 = 1;
            m_user->Unk100 = 0;
            m_user->Unk104 = 0;
            m_user->Unk108 = 0;
            m_user->Unk112 = 0;

            LoginRepMsg(m_out_msg, 0, m_username, m_user);

            if(m_desc)
                m_desc->WriteToOutput(m_out_msg);
        }

        m_user->Descriptor = m_desc;

        return;
    }

    g_gamelogbuffer.__ls(init("LOGIN_FAIL", m_username));
    g_gamelogbuffer.__ls("From");
    g_gamelogbuffer.__ls(delim);
    g_gamelogbuffer.__ls((int)m_desc->SubServerID);
    g_gamelogbuffer.__ls(delim);
    g_gamelogbuffer.__ls(4);
    g_gamelogbuffer.__ls(end);

    LoginRepMsg(m_out_msg, 4, m_username, 0);

    if(m_desc)
        m_desc->WriteToOutput(m_out_msg);
}

void ConnLogout(CDescriptor *m_desc, CNetMsg &m_msg)
{
    CUser *m_user = 0;
    char m_username[55], m_type;

    m_msg.MoveFirst();
    m_msg.__rs(m_type);
    m_msg.__rs(m_username);

    if(m_desc->IsTester)
    {
        for(long i = 0; ; ++i)
        {
            if(i < gserver.MaxSubServer)
            {
              m_user = gserver.Users[i].Find(m_username);
              if(!m_user)
                  continue;
            }

            break;
        }
    }
    else
    {
        m_user = gserver.Users[m_desc->SubServerID - 1].Find(m_username);
    }

    if(m_user)
    {
        gserver.ProcessLogout(m_user);
    }
    else
    {
        g_gamelogbuffer.__ls(init("SYS_ERR", m_username));
        g_gamelogbuffer.__ls("From");
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls((int)m_desc->SubServerID);
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls("Not Found User");
        g_gamelogbuffer.__ls(end);

        if(gserver.BillingClient.IsRunning())
            gserver.BillingClient.Logout(0);

        if(!WriteDB(m_username))
        {
            g_gamelogbuffer.__ls(init("SYS_ERR", m_username));
            g_gamelogbuffer.__ls("From");
            g_gamelogbuffer.__ls(delim);
            g_gamelogbuffer.__ls((int)m_desc->SubServerID);
            g_gamelogbuffer.__ls(delim);
            g_gamelogbuffer.__ls("Cannot Update DB for Logout");
            g_gamelogbuffer.__ls(end);
        }
    }
}

void ConnBLogin(CDescriptor *m_desc, CNetMsg &m_msg)
{
    CUser *m_user = 0;
    char m_type, m_unk2[20], m_username[55];

    m_msg.MoveFirst();
    m_msg.__rs(m_type);
    m_msg.__rs(m_username);
    m_msg.__rs(m_unk2);

    if(m_desc->IsTester)
    {
        for(long i = 0; ; ++i)
        {
            if(i < gserver.MaxSubServer)
            {
                m_user = gserver.Users[i].Find(m_username);

                if(!m_user)
                    continue;
            }

            break;
        }
    }
    else
    {
        m_user = gserver.Users[m_desc->SubServerID - 1].Find(m_username);
    }

    if(!m_user)
    {
        g_gamelogbuffer.__ls(init("SYS_ERR", m_username));
        g_gamelogbuffer.__ls("From");
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls((int)m_desc->SubServerID);
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls("BLogin");
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls("Not Found User");
        g_gamelogbuffer.__ls(end);
    }

    if(gserver.BillingClient.IsRunning())
        gserver.BillingClient.Login(0, 0, 0);
}

void ConnBLogout(CDescriptor *m_desc, CNetMsg &m_msg)
{
    CUser *m_user = 0;
    char m_username[55], m_type;

    m_msg.MoveFirst();
    m_msg.__rs(m_type);
    m_msg.__rs(m_username);

    if(m_desc->IsTester)
    {
        for(long i = 0; ; ++i)
        {
            if(i < gserver.MaxSubServer)
            {
                m_user = gserver.Users[i].Find(m_username);

                if(!m_user)
                    continue;
            }

            break;
        }
    }
    else
    {
        m_user = gserver.Users[m_desc->SubServerID - 1].Find(m_username);
    }

    if(!m_user)
    {
        g_gamelogbuffer.__ls(init("SYS_ERR", m_username));
        g_gamelogbuffer.__ls("From");
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls((int)m_desc->SubServerID);
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls("BLogout");
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls("Not Found User");
        g_gamelogbuffer.__ls(end);
    }

    if(gserver.BillingClient.IsRunning())
        gserver.BillingClient.Logout(0);
}

signed int ReadDB(char const *m_username, char const *m_password, int a3, int a4, char const *a5, CUser **m_new_user)
{
    CDBCmd m_cmd;
    int m_idx;
    bool v12 = true;
    int m_user_code;

    strcpy(g_buf, "SELECT user_code FROM bg_user WHERE user_id='");
    strcat(g_buf, m_username);
    strcat(g_buf, "' AND passwd='");
    strcat(g_buf, m_password);
    strcat(g_buf, "'");

    m_cmd.Init(&gserver.AuthSQL);
    m_cmd.SetQuery(g_buf);

    if(!m_cmd.Open())
        return 1;

    if(m_cmd.AffectedRows <= 0 || !m_cmd.MoveFirst())
        return 2;

    m_cmd.GetRec("user_code", m_user_code);
    strcpy(g_buf, "SELECT a_portal_index, a_zone_num, a_timestamp, a_enable FROM t_users WHERE a_idname='");
    strcat(g_buf, m_username);
    strcat(g_buf, "'");

    m_cmd.Init(&gserver.UserSQL);
    m_cmd.SetQuery(g_buf);

    if(!m_cmd.Open())
      return 1;

    if(m_cmd.AffectedRows > 0 && m_cmd.MoveNext())
    {
        m_cmd.GetRec("a_portal_index", m_idx);

        if(m_idx == m_user_code)
        {
            v12 = false;
        }
        else
        {
            strcpy(g_buf, "UPDATE t_users SET a_idname='");
            strcat(g_buf, m_username);
            strcat(g_buf, "_CS");
            IntCat(g_buf, (long long)time(0), false);
            strcat(g_buf, "', a_end_date=NOW() WHERE a_portal_index=");
            IntCat(g_buf, m_idx, false);

            m_cmd.SetQuery(g_buf);

            if(!m_cmd.Update())
                return 2;

            v12 = true;
        }
    }

    if(v12)
    {
        strcpy(g_buf, "INSERT INTO t_users (a_idname, a_passwd, a_portal_index, a_regi_date, a_end_date) VALUES ('");
        strcat(g_buf, m_username);
        strcat(g_buf, "', '");
        strcat(g_buf, m_password);
        strcat(g_buf, "', ");
        IntCat(g_buf, m_user_code, false);
        strcat(g_buf, ", NOW(), NOW())");

        m_cmd.SetQuery(g_buf);

        if(!m_cmd.Update())
            return 3;

        (*m_new_user) = new CUser(m_user_code, m_username, a3, a4, a5);

        return 0;
    }

    if(m_cmd.GetRec("a_zone_num", m_idx))
    {
        if(atoi(m_cmd.GetRec("a_enable")) > 1)
            return 5;

        if(m_idx >= 0)
            return 3;

        (*m_new_user) = new CUser(m_user_code, m_username, a3, a4, a5);
        m_cmd.GetRec("a_timestamp", (*m_new_user)->Timestamp);

        return 0;
    }

    return 1;
}

signed int WriteDB(int a1, int a2, int a3, int a4, int a5, char const *src, char const *a7, bool a8)
{
    CDBCmd m_cmd;

    strcpy(g_buf, "UPDATE t_users SET a_end_date=NOW(), a_server_num=");
    IntCat(g_buf, a2, false);
    strcat(g_buf, ", a_subnum=");
    IntCat(g_buf, a3, false);
    strcat(g_buf, ", a_zone_num=");
    IntCat(g_buf, a4, false);
    strcat(g_buf, ", a_timestamp=");
    IntCat(g_buf, a5, false);
    strcat(g_buf, " WHERE a_portal_index=");
    IntCat(g_buf, a1, false);

    if(a8)
        strcat(g_buf, " AND a_zone_num=-1");

    m_cmd.Init(&gserver.UserSQL);
    m_cmd.SetQuery(g_buf);

    if(!m_cmd.Update())
        return 1;

    if(m_cmd.AffectedRows <= 0)
        return 3;

    if(src && *src && a7 && *a7)
    {
        strcpy(g_buf, "INSERT INTO t_connect_log (a_idname, a_date, a_ip) VALUES ('");
        strcat(g_buf, src);
        strcat(g_buf, "', NOW(), '");
        strcat(g_buf, a7);
        strcat(g_buf, "')");

        m_cmd.SetQuery(g_buf);
        m_cmd.Update();
    }

    return 0;
}

bool WriteDB(char const *m_idname)
{
    CDBCmd m_cmd;

    strcpy(g_buf, "UPDATE t_users SET a_end_date=NOW(), a_zone_num=");
    IntCat(g_buf, -1, false);
    strcat(g_buf, " WHERE a_idname='");
    strcat(g_buf, m_idname);
    strcat(g_buf, "'");

    m_cmd.Init(&gserver.UserSQL);
    m_cmd.SetQuery(g_buf);

    return m_cmd.Update();
}

void ConnPlayerReq(CDescriptor *m_desc, CNetMsg &m_msg)
{
    CNetMsg m_player_rep_msg;

    PlayerRepMsg(m_player_rep_msg);

    if(m_desc)
        m_desc->WriteToOutput(m_player_rep_msg);
}

void ConnPlaying(CDescriptor *m_desc, CNetMsg &m_msg)
{
    CUser *m_user;
    char m_unk1, m_username[55], m_type;
    long m_new_zone_num;

    m_msg.MoveFirst();
    m_msg.__rs(m_type);
    m_msg.__rs(m_username);
    m_msg.__rs(m_unk1);
    m_msg.__rs(m_new_zone_num);

    if(m_desc->SubServerID <= 0)
    {
        g_gamelogbuffer.__ls(init("SYS_ERR", m_username));
        g_gamelogbuffer.__ls("From");
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls((int)m_desc->SubServerID);
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls("No match server or subno");
        g_gamelogbuffer.__ls(end);
    }

    m_user = gserver.Users[m_desc->SubServerID - 1].Find(m_username);

    if(!m_user)
    {
        g_gamelogbuffer.__ls(init("SYS_ERR", m_username));
        g_gamelogbuffer.__ls("From");
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls((int)m_desc->SubServerID);
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls("Change playing state: Not Found User");
        g_gamelogbuffer.__ls(end);
    }

    g_gamelogbuffer.__ls(init("CHANGE_STATE", m_username));
    g_gamelogbuffer.__ls("From");
    g_gamelogbuffer.__ls(delim);
    g_gamelogbuffer.__ls((int)m_desc->SubServerID);
    g_gamelogbuffer.__ls(delim);
    g_gamelogbuffer.__ls(m_unk1 ? "CHANGE_SERVER" : "PLAYING");
    g_gamelogbuffer.__ls(delim);
    g_gamelogbuffer.__ls((int)m_user->ZoneNum);
    g_gamelogbuffer.__ls(delim);
    g_gamelogbuffer.__ls((int)m_new_zone_num);
    g_gamelogbuffer.__ls(end);

    --gserver.Users[m_desc->SubServerID - 1].Count[m_user->ZoneNum];
    ++gserver.Users[m_desc->SubServerID - 1].Count[m_new_zone_num];

    m_user->Unk80 = m_unk1 ? 2 : 1;
    m_user->ZoneNum = m_new_zone_num;
    m_user->Unk92 = 0;

    WriteDB(m_user->PortalIndex, m_user->ServerNum, m_user->SubServerNum, m_user->ZoneNum, m_user->Timestamp, 0, 0, 0);
}

void ConnPreopenGift(CDescriptor *m_desc, CNetMsg &m_msg)
{
    ;
}

void ConnLevelupPoint(CDescriptor *m_desc, CNetMsg &m_msg)
{
    ;
}

void ConnStashState(CDescriptor *m_desc, CNetMsg &m_msg)
{
    CDBCmd m_cmd;
    CNetMsg m_out_msg;
    CUser *m_user;
    char m_stash[54];
    int m_unk1 = -1, m_unk2 = -1;

    if(!m_desc->IsTester)
    {
        if(m_desc->SubServerID > 0)
        {
            m_msg.__rs(m_unk2);
            m_msg.__rs(m_unk1);

            m_user = gserver.Users[m_desc->SubServerID - 1].Find(m_unk2);

            if(m_user)
            {
                strcpy(g_buf, "SELECT a_stash_passwd, a_stash_sealed FROM t_users WHERE a_portal_index=");
                IntCat(g_buf, m_unk2, true);

                m_cmd.Init(&gserver.UserSQL);
                m_cmd.SetQuery(g_buf);

                if(m_cmd.Open() && m_cmd.MoveFirst())
                {
                    memset(m_stash, 0, 51);

                    if(m_cmd.GetRec("a_stash_passwd", m_stash + 1, true) && m_cmd.GetRec("a_stash_sealed", (int &)m_stash))
                    {
                        StashStateMsg(m_out_msg, m_unk2, m_unk1, strlen(m_stash + 1) != 0, *m_stash);

                        if(m_desc)
                            m_desc->WriteToOutput(m_out_msg);
                    }
                    else
                    {
                        StashStateMsg(m_out_msg, m_unk2, m_unk1, -1, -1);

                        if(m_desc)
                            m_desc->WriteToOutput(m_out_msg);
                    }
                }
                else
                {
                    StashStateMsg(m_out_msg, m_unk2, m_unk1, -1, -1);

                    if(m_desc)
                        m_desc->WriteToOutput(m_out_msg);
                }
            }
        }
    }
}

void ConnStashCheckPassword(CDescriptor *m_desc, CNetMsg &m_msg)
{
    CNetMsg m_out_msg;
    CDBCmd m_cmd;
    CUser *m_user;
    char m_stash[54];
    int m_unk1 = -1, m_unk2 = -1;

    g_buf2[0] = 0;

    m_msg.__rs(m_unk2);
    m_msg.__rs(m_unk1);
    m_msg.__rs(g_buf2);

    m_user = gserver.Users[m_desc->SubServerID - 1].Find(m_unk2);

    if(m_user)
    {
        strcpy(g_buf, "SELECT a_stash_passwd, a_stash_sealed FROM t_users WHERE a_portal_index=");
        IntCat(g_buf, m_unk2, true);

        m_cmd.Init(&gserver.UserSQL);
        m_cmd.SetQuery(g_buf);

        if(m_cmd.Open() && m_cmd.MoveFirst())
        {
            memset(m_stash, 0, 51);

            if(m_cmd.GetRec("a_stash_passwd", m_stash + 1, true) && m_cmd.GetRec("a_stash_sealed", (int &)m_stash))
            {
                if(*m_stash)
                {
                    StashCheckPasswordMsg(m_out_msg, m_unk2, m_unk1, 2);

                    if(m_desc)
                        m_desc->WriteToOutput(m_out_msg);
                }
                else
                {
                    if(strcmp(m_stash + 1, g_buf2))
                    {
                        StashCheckPasswordMsg(m_out_msg, m_unk2, m_unk1, 1);

                        if(m_desc)
                            m_desc->WriteToOutput(m_out_msg);
                    }
                    else
                    {
                        StashCheckPasswordMsg(m_out_msg, m_unk2, m_unk1, 0);

                        if(m_desc)
                            m_desc->WriteToOutput(m_out_msg);
                    }
                }
            }
            else
            {
                StashCheckPasswordMsg(m_out_msg, m_unk2, m_unk1, 2);

                if(m_desc)
                    m_desc->WriteToOutput(m_out_msg);
            }
        }
        else
        {
            StashCheckPasswordMsg(m_out_msg, m_unk2, m_unk1, 2);

            if(m_desc)
                m_desc->WriteToOutput(m_out_msg);
        }
    }
}

void ConnStashChangePassword(CDescriptor *m_desc, CNetMsg &m_msg)
{
    CNetMsg m_out_msg;
    CDBCmd m_cmd;
    CUser *m_user;
    char m_stash[54];
    int m_unk1 = -1, m_unk2 = -1;

    g_buf2[0] = 0;
    g_buf3[0] = 0;

    m_msg.__rs(m_unk2);
    m_msg.__rs(m_unk1);
    m_msg.__rs(g_buf2);
    m_msg.__rs(g_buf3);

    m_user = gserver.Users[m_desc->SubServerID - 1].Find(m_unk2);

    if(m_user)
    {
        strcpy(g_buf, "SELECT a_stash_passwd, a_stash_sealed FROM t_users WHERE a_portal_index=");
        IntCat(g_buf, m_unk2, true);

        m_cmd.Init(&gserver.UserSQL);
        m_cmd.SetQuery(g_buf);

        if(m_cmd.Open() && m_cmd.MoveFirst())
        {
            memset(m_stash, 0, 51);

            if(m_cmd.GetRec("a_stash_passwd", m_stash + 1, 1) && m_cmd.GetRec("a_stash_sealed", (int &)m_stash))
            {
                if(*m_stash)
                {
                    StashChangePasswordMsg(m_out_msg, m_unk2, m_unk1, g_buf3, 2);

                    if(m_desc)
                        m_desc->WriteToOutput(m_out_msg);
                }
                else
                {
                    if(strcmp(m_stash + 1, g_buf2))
                    {
                        StashChangePasswordMsg(m_out_msg, m_unk2, m_unk1, g_buf3, 1);

                        if(m_desc)
                            m_desc->WriteToOutput(m_out_msg);
                    }
                    else
                    {
                        strcpy(g_buf, "UPDATE t_users SET a_stash_passwd='");
                        strcat(g_buf, g_buf3);
                        strcat(g_buf, "' WHERE a_portal_index=");
                        IntCat(g_buf, m_unk2, true);
                        strcat(g_buf, " AND a_stash_sealed=");
                        IntCat(g_buf, *m_stash, true);
                        strcat(g_buf, " AND a_stash_passwd='");
                        strcat(g_buf, g_buf2);
                        strcat(g_buf, "'");
                        m_cmd.SetQuery(g_buf);

                        if(m_cmd.Update())
                        {
                            StashChangePasswordMsg(m_out_msg, m_unk2, m_unk1, g_buf3, 0);

                            if(m_desc)
                                m_desc->WriteToOutput(m_out_msg);
                        }
                        else
                        {
                            StashChangePasswordMsg(m_out_msg, m_unk2, m_unk1, g_buf3, 1);

                            if(m_desc)
                                m_desc->WriteToOutput(m_out_msg);
                        }
                    }
                }
            }
            else
            {
                StashChangePasswordMsg(m_out_msg, m_unk2, m_unk1, g_buf3, 2);

                if(m_desc)
                    m_desc->WriteToOutput(m_out_msg);
            }
        }
        else
        {
            StashChangePasswordMsg(m_out_msg, m_unk2, m_unk1, g_buf3, 2);

            if(m_desc)
                m_desc->WriteToOutput(m_out_msg);
        }
    }
}

void ConnStashSeal(CDescriptor *m_desc, CNetMsg &m_msg)
{
    CNetMsg m_out_msg;
    CDBCmd m_cmd;
    CUser *m_user;
    char m_stash = 0;
    int m_unk1 = -1, m_unk2 = -1;

    m_msg.__rs(m_unk2);
    m_msg.__rs(m_unk1);

    m_user = gserver.Users[m_desc->SubServerID - 1].Find(m_unk2);

    if(m_user)
    {
        strcpy(g_buf, "SELECT a_stash_sealed FROM t_users WHERE a_portal_index=");
        IntCat(g_buf, m_unk2, true);

        m_cmd.Init(&gserver.UserSQL);
        m_cmd.SetQuery(g_buf);

        if(m_cmd.Open() && m_cmd.MoveFirst())
        {
            if(m_cmd.GetRec("a_stash_sealed", m_stash))
            {
              if(m_stash)
              {
                  StashSealMsg(m_out_msg, m_unk2, m_unk1, 1);

                  if(m_desc)
                      m_desc->WriteToOutput(m_out_msg);
              }
              else
              {
                strcpy(g_buf, "UPDATE t_users SET a_stash_sealed=1 WHERE a_portal_index=");
                IntCat(g_buf, m_unk2, true);
                strcat(g_buf, " AND a_stash_sealed=");
                IntCat(g_buf, m_stash, true);

                m_cmd.SetQuery(g_buf);

                if(m_cmd.Update())
                {
                    StashSealMsg(m_out_msg, m_unk2, m_unk1, 0);

                    if(m_desc)
                        m_desc->WriteToOutput(m_out_msg);
                }
                else
                {
                    StashSealMsg(m_out_msg, m_unk2, m_unk1, 2);

                    if(m_desc)
                        m_desc->WriteToOutput(m_out_msg);
                }
              }
            }
            else
            {
                StashSealMsg(m_out_msg, m_unk2, m_unk1, 2);

                if(m_desc)
                    m_desc->WriteToOutput(m_out_msg);
            }
        }
        else
        {
            StashSealMsg(m_out_msg, m_unk2, m_unk1, 2);

            if(m_desc)
                m_desc->WriteToOutput(m_out_msg);
        }
    }
}
