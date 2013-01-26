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

#include "Descriptor.h"

CDescriptor::CDescriptor(void)
{
    this->MainSocket = -1;
    memset(this->Username, 0, 21);
    memset(this->Password, 0, 21);
    this->Unk66 = 0;
    this->Number = 0;
    this->MaxSubNumber = 0;
    this->ConnectorsUnk = 0;
    this->ConnectorsID = 0;
    this->ConnectorsIP = 0;
    this->ConnectorsUnk2 = 0;
    this->Socket = 0;
    memset(this->Hostname, 0, 31);
    this->Unk252 = -1;
    this->SocketPhase = 0;
    this->FailedAttempts = 0;
    this->WasErrors = 0;
    this->NextNode = 0;
    this->PreviousNode = 0;
}

CDescriptor::~CDescriptor()
{
    this->Unk66 = 0;
    
    if(this->ConnectorsID)
        delete this->ConnectorsID;
    
    if(this->ConnectorsUnk)
        delete this->ConnectorsUnk;
    
    if(this->ConnectorsIP)
        delete this->ConnectorsIP;
    
    if(this->ConnectorsUnk2)
        delete this->ConnectorsUnk2;
}

void CDescriptor::CloseSocket(void)
{
    close(this->Socket);
    this->FlushQueues();
}

void CDescriptor::FlushQueues(void)
{
    InputBuffer.Clear();
    InputQueue.Clear();
    OutputBuffer.Clear();
}

void CDescriptor::WriteToOutput(CNetMsg &net_msg)
{
    if(!&net_msg)
        return;
    
    if(this->OutputBuffer.Add(net_msg))
    {
        this->ProcessOutput();
        return;
    }

    g_gamelogbuffer.__ls(init("OUTPUT OVERFLOW"));
    g_gamelogbuffer.__ls(end);
    this->WasErrors = true;
}

int CDescriptor::ProcessOutput(void)
{
    char *m_next_point;
    long m_written_desc = 0;

    do
    {
        m_next_point = this->OutputBuffer.GetNextPoint();
        if(!m_next_point)
            return 0;
        
        m_written_desc = this->WriteToDescriptor(this->Socket, m_next_point, this->OutputBuffer.GetRemain());
        
        if(m_written_desc < 0)
        {
            this->WasErrors = true;
            return -1;
        }
    }
    while(m_written_desc && !this->OutputBuffer.Update(m_written_desc));
    
    return 0;
}

int CDescriptor::WriteToDescriptor(long p_fd, char const *p_buf, long p_bytes)
{
    int m_write;

    if(!p_bytes)
        return 0;
    
    m_write = write(p_fd, p_buf, p_bytes);
    
    if(m_write > 0)
        return m_write;
    
    if (!m_write)
        return -1;
    
    if(errno == 11)
        return 0;
    
    if(errno != 104)
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("WriteToDescriptor : no =");
        g_gamelogbuffer.__ls(errno);
        g_gamelogbuffer.__ls(end);
    }
    
    return -1;
}

int CDescriptor::ProcessInput(void)
{
    bool r_finished = false, r_finished2 = false, m_message_fail = false;
    int m_bytes = 0, m_get_message = 0;
    CNetMsg net_msg;

    do
    {
        if(this->InputBuffer.GetRemain() <= 0)
        {
            g_gamelogbuffer.__ls(init("SYS_WARN"));
            g_gamelogbuffer.__ls("m_input overflow");
            g_gamelogbuffer.__ls(end);
            
            return -1;
        }
        
        m_bytes = this->PerformSocketRead(this->Socket, this->InputBuffer.GetPoint(), this->InputBuffer.GetRemain());

        if(m_bytes < 0)
            return -1;
        
        if(!m_bytes)
            return 0;
        
        this->InputBuffer.SetPoint(m_bytes);
        
        
        r_finished2 = false;
        m_message_fail = false;
        
        while(!r_finished2)
        {
            m_get_message = this->InputBuffer.GetMessage(net_msg);
            
            if(m_get_message)
            {
                if(m_get_message > 0)
                {
                    if(m_get_message == 1)
                        r_finished2 = true;
                }
                else
                {
                    if(m_get_message == -1)
                    {
                        m_message_fail = true;
                        r_finished2 = true;
                    }
                }
            }
            else
            {
                this->InputQueue.Add(net_msg);
                r_finished = true;
            }
        }
        
        if(m_message_fail)
            return -1;
    }
    while(!r_finished);
    
    return 1;
}

int CDescriptor::PerformSocketRead(long p_fd, char *p_buf, unsigned long p_bytes)
{
    long m_read = read(p_fd, p_buf, p_bytes);

    if(m_read > 0)
        return m_read;
    
    if(!m_read)
        return -1;
    
    if(errno == 4 || errno == 11 || errno == 11 || errno == 35)
        return 0;
    
    return -1;
}

/*************************
CHECK TRY-TROW-EXCEPTION
**************************/

bool CDescriptor::GetLogin(CNetMsg &net_msg)
{
    int server_num = 0, subnum = 0, zone_num = 0, m_usr_code = 0;
    CDBCmd db_cmd, id_psw_cmd;
    CNetMsg m_net_msg;
    char m_username[52], m_password[55], m_query[1024];
    unsigned char m_unk = 0;
    unsigned int m_client_ver = 0;
    
    net_msg.MoveFirst();
    
    if(net_msg.p_msg_type != 3)
    {
        FailMsg(m_net_msg, 27);
        if(this)
            this->WriteToOutput(m_net_msg);
        gserver.SendOutput(this);
        return false;
    }
    
    net_msg.__rs(m_client_ver);
    net_msg.__rs(m_unk);
    net_msg.__rs(m_username);
    net_msg.__rs(m_password);

    if(m_client_ver < gserver.p_min_client_ver || m_client_ver > gserver.p_max_client_ver)
    {
        FailMsg(m_net_msg, 29);
        if(this)
            this->WriteToOutput(m_net_msg);
        gserver.SendOutput(this);
        return false;
    }

    if(strinc(m_username, "'") || strlen(m_username) <= 2 || strlen(m_username) > 20)
    {
        FailMsg(m_net_msg, 30);
        if(this)
            this->WriteToOutput(m_net_msg);
        gserver.SendOutput(this);
        return false;
    }

    if(strinc(m_password, "'") || strlen(m_password) <= 3 || strlen(m_password) > 20)
    {
        FailMsg(m_net_msg, 31);
        if(this)
            this->WriteToOutput(m_net_msg);
        gserver.SendOutput(this);
        return false;
    }

    strcpy(this->Username, m_username);
    strcpy(this->Password, m_password);
    
    memset(m_query, 0, 1024);
    sprintf(m_query, "SELECT user_code, user_id, passwd FROM bg_user WHERE user_id='%s' AND passwd='%s'", this->Username, this->Password);
    id_psw_cmd.Init(&gserver.mysql_auth_db);
    id_psw_cmd.SetQuery(m_query);

    if(!id_psw_cmd.Open() || !id_psw_cmd.MoveFirst())
    {
        FailMsg(m_net_msg, 31);
        if(this)
            this->WriteToOutput(m_net_msg);
        gserver.SendOutput(this);
        return false;
    }
    
    id_psw_cmd.GetRec("user_code", m_usr_code);
    
    memset(m_query, 0, 128);
    sprintf(m_query, "SELECT a_server_num, a_subnum, a_zone_num FROM t_users WHERE a_portal_index=%d", m_usr_code);
    db_cmd.Init(&gserver.mysql_user_db);
    db_cmd.SetQuery(m_query);

    if(db_cmd.Open() && db_cmd.MoveFirst() && db_cmd.GetRec("a_server_num", server_num) && db_cmd.GetRec("a_subnum", subnum) && db_cmd.GetRec("a_zone_num", zone_num))
    {
        if(zone_num >= 0)
        {
            LogoutReqMsg(m_net_msg, server_num, subnum, zone_num, this);
            
            if(gserver.p_messenger_desc)
                gserver.p_messenger_desc->WriteToOutput(m_net_msg);

            FailMsg(m_net_msg, 32);
            gserver.SendOutput(this);
            return false;
        }
        
        g_gamelogbuffer.__ls(init("LOGIN", m_username));
        g_gamelogbuffer.__ls(this->Hostname);
        g_gamelogbuffer.__ls(end);
        
        for(int i = 0; i < gserver.p_connector_count; ++i)
        {
            PlayerNumMsg(m_net_msg, server_num, subnum, i);
            
            if(this)
                this->WriteToOutput(m_net_msg);
            
            gserver.SendOutput(this);
        }
        
        this->SocketPhase = 0;
            return true;
    }
    else
    {
        g_gamelogbuffer.__ls(init("LOGIN", this->Username));
        g_gamelogbuffer.__ls(this->Hostname);
        g_gamelogbuffer.__ls(end);
        
        for(int j = 0; j < gserver.p_connector_count; ++j)
        {
            PlayerNumMsg(m_net_msg, -1, -1, j);
            
            if(this)
                this->WriteToOutput(m_net_msg);
            
            gserver.SendOutput(this);
        }
        
        this->SocketPhase = 0;
        return true;
    }
}
