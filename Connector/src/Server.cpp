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

#include "Server.h"

CServer::CServer(void)
{
    this->ServerSocket          = -1;
    this->ClientDescriptors     = 0;
    FD_ZERO(&this->ReadFDS);
    FD_ZERO(&this->WriteFDS);
    FD_ZERO(&this->ExceptFDS);
    memset(this->p_unk_array4, 0, 1024);
    this->ServerPath            = this->GetServerPath();
    this->MaxPlayers            = 0;
    this->MaxSubServer          = 0;
    this->Shutdowned            = false;
    this->WriteShutDown         = false;
    this->DoNotUseGetHostByAddr = true;
    this->Unk1                  = 0;
    this->ConnectCount          = 6000;
    this->ConnectMax            = 2400;
    mysql_init(&this->UserSQL);
    mysql_init(&this->AuthSQL);
    this->HeartBeats            = 0;
}

CServer::~CServer(void)
{
    if(this->ServerPath && this->ServerPath)
        delete this->ServerPath;
}

char *CServer::GetServerPath(void)
{
    char *m_path;

    m_path = getcwd(0, 0x200);
    strcat(m_path, "/");

    return m_path;
}

bool CServer::LoadSettingFile(void)
{
    char m_filename[256];

    puts("Loading Setting File...");
    sprintf(m_filename, "%s%s", this->ServerPath, "newStobm.bin");
    
    if(this->Configs.Load(m_filename, false))
    {
        this->Number       = atoi(this->Configs.Find("Server", "Number"));
        this->MaxSubServer = atoi(this->Configs.Find("Server", "MaxSubServer"));
        return this->MaxSubServer > 0;
    }
    
    return false;
}

bool CServer::ConnectDB(void)
{
    if(mysql_real_connect(&this->UserSQL, this->Configs.Find("User DB", "IP"), this->Configs.Find("User DB", "User"), this->Configs.Find("User DB", "Password"), this->Configs.Find("User DB", "DBName"), 0, 0, 0) &&
       mysql_real_connect(&this->AuthSQL, this->Configs.Find("Auth DB", "IP"), this->Configs.Find("Auth DB", "User"), this->Configs.Find("Auth DB", "Password"), this->Configs.Find("Auth DB", "DBName"), 0, 0, 0))
        return true;
    
    return false;
}

bool CServer::InitGame(void)
{
    this->Users = new CUserList[this->MaxSubServer];

    ServerSrandom(time(0));
    MakeMath();
    this->InitUserData();
    
    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Finding Connection Limit");
    g_gamelogbuffer.__ls(end);
    
    this->MaxPlayers   = this->GetMaxPlayers();
    
    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Initialize Server Socket");
    g_gamelogbuffer.__ls(end);
    
    this->ServerSocket = this->InitSocket();
    
    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Entering Connector Loop");
    g_gamelogbuffer.__ls(end);
    
    return 1;
}

void CServer::InitUserData(void)
{
    CDBCmd m_user;

    strcpy(g_buf, "UPDATE t_users SET a_zone_num=-1 WHERE a_server_num=");
    IntCat(g_buf, this->Number, false);
    
    m_user.Init(&this->UserSQL);
    m_user.SetQuery(g_buf);
    m_user.Update();
}

int CServer::GetMaxPlayers(void)
{
    struct rlimit m_rlimits;
    int m_player_limit = 0;
    const char *_limit = "rlimit";
     
    if(getrlimit(7, &m_rlimits) < 0)
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("Calling getrlimit()");
        g_gamelogbuffer.__ls(end);
        exit(1);
    }
    
    m_rlimits.rlim_cur = m_rlimits.rlim_max;
    if(setrlimit(7, &m_rlimits) < 0)
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("Calling setrlimit()");
        g_gamelogbuffer.__ls(end);
        exit(1);
    }
    
    if((signed long)m_rlimits.rlim_max == -1)
    {
        m_player_limit = 50005;
    }
    else
    {
        m_player_limit = m_rlimits.rlim_max;
                
        if(m_rlimits.rlim_max > 0xC355)
            m_player_limit = 50005;
    }
    
    m_player_limit -= 5;
    if(m_player_limit > 50000)
            m_player_limit = 50000;
    
    if(m_player_limit <= 0)
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("Non-positive max player limit!    (Set at");
        g_gamelogbuffer.__ls(m_player_limit);
        g_gamelogbuffer.__ls("using");
        g_gamelogbuffer.__ls(_limit);
        g_gamelogbuffer.__ls(").");
        g_gamelogbuffer.__ls(end);
        exit(1);
    }
    
    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Setting player limit to");
    g_gamelogbuffer.__ls(m_player_limit);
    g_gamelogbuffer.__ls("using");
    g_gamelogbuffer.__ls(_limit);
    g_gamelogbuffer.__ls(".");
    g_gamelogbuffer.__ls(end);
    
    return m_player_limit;
}

int CServer::InitSocket(void)
{
    struct sockaddr_in m_sockaddr;
    long m_optval = 1;
    long fd = socket(2, 1, 0);
    struct linger m_linger;
    
    if(fd < 0)
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("Create server socket");
        g_gamelogbuffer.__ls(end);
        exit(1);
    }
    
    if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &m_optval, 4) < 0)
    {
        puts("Error: setsockopt(): REUSEADDR");
        exit(1);
    }
    
    this->SetSendbuf(fd);
    m_linger.l_onoff  = 0;
    m_linger.l_linger = 0;
    
    if(setsockopt(fd, SOL_SOCKET, SO_LINGER, &m_linger, 8) < 0)
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("setsockopt(): SO_LINGER");
        g_gamelogbuffer.__ls(end);
    }
    
    memset(&m_sockaddr, 0, 16);
    m_sockaddr.sin_family = 2;
    m_sockaddr.sin_port   = htons(atoi(this->Configs.Find("Server", "Port")));
    m_sockaddr.sin_addr   = this->GetBindAddr();
    
    if(bind(fd, (struct sockaddr *)&m_sockaddr, 16) < 0)
    {
        puts("Error: bind");
        close(fd);
        exit(1);
    }
    
    this->Nonblock(fd);
    listen(fd, 57);
	
    return fd;
}

int CServer::SetSendbuf(int fd)
{
    long m_optval = 12288;
    
    if(setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &m_optval, 4) >= 0)
        return 0;
    
    puts("Error: setsockopt(): SNDBUF");
    return -1;
}

struct in_addr CServer::GetBindAddr(void)
{
    memset(&bind_addr, 0, 4);
    
    if(strcmp(this->Configs.Find("Server", "IP"), "ALL"))
        bind_addr.s_addr = inet_addr(this->Configs.Find("Server", "IP"));
    else
        bind_addr.s_addr = htonl(0);
    
    if(bind_addr.s_addr == htonl(0))
    {
        g_gamelogbuffer.__ls(init("SYSTEM"));
        g_gamelogbuffer.__ls("Binding to all IP interfaces on this m_host.");
        g_gamelogbuffer.__ls(end);
    }
    else
    {
        g_gamelogbuffer.__ls(init("SYSTEM"));
        g_gamelogbuffer.__ls("Binding only to IP address ");
        g_gamelogbuffer.__ls(inet_ntoa(bind_addr));
        g_gamelogbuffer.__ls(end);
    }
    
    return bind_addr;
}

void CServer::Nonblock(int fd)
{
    if(fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK) < 0)
    {
        g_gamelogbuffer.__ls(init("SYSTEM"));
        g_gamelogbuffer.__ls("SYSERR: Fatal error executing nonblock (CServer.cpp)");
        g_gamelogbuffer.__ls(end);

        exit(1);
    }
}

void CServer::ServerSleep(timeval *timeout)
{
    if(select(0, 0, 0, 0, timeout) < 0)
    {
        if(errno != 4)
        {
            g_gamelogbuffer.__ls(init("SYS_ERR"));
            g_gamelogbuffer.__ls("Select sleep!!");
            g_gamelogbuffer.__ls(end);

            exit(1);
        }
    }
}

int CServer::NewDescriptor(int fd)
{
    long m_socket;
    socklen_t addr_len;
    struct sockaddr addr;
    const char *m_host;
    CDescriptor *m_desc;

    addr_len = 16;
    m_socket = accept(fd, &addr, &addr_len);

    if(m_socket == -1)
        return -1;

    this->Nonblock(m_socket);

    if(this->SetSendbuf(m_socket) < 0)
    {
        close(m_socket);
        return 0;
    }

    m_desc = new CDescriptor();

    if(!this->DoNotUseGetHostByAddr && (m_host = *(const char **)gethostbyaddr(&addr.sa_data[2], 4, 2)) != 0)
    {
        strncpy(m_desc->Hostname, m_host, 30);
        m_desc->UnkByte1 = 0;
    }
    else
    {
        if(!this->DoNotUseGetHostByAddr)
        {
            g_gamelogbuffer.__ls(init("SYS_ERR"));
            g_gamelogbuffer.__ls("gethostbyaddr()");
            g_gamelogbuffer.__ls(end);
        }

        strncpy(m_desc->Hostname, inet_ntoa(*(struct in_addr *)&addr.sa_data[2]), 30);
        m_desc->UnkByte1 = 0;
    }

    m_desc->Socket = m_socket;
    m_desc->Unk152 = 23;

    if(++last_desc == 100000000)
        last_desc = 1;

    if(this->ClientDescriptors)
        this->ClientDescriptors->NextNode = m_desc;

    m_desc->Node = this->ClientDescriptors;
    m_desc->NextNode = 0;
    this->ClientDescriptors = m_desc;

    return 0;
}

void CServer::CloseSocket(CDescriptor *m_desc)
{
    g_gamelogbuffer.__ls(init("DISCONNECT", m_desc->Hostname));
    g_gamelogbuffer.__ls(end);

    if(!m_desc->IsTester && m_desc->SubServerID > 0)
    {
        for(long i = 0; i <= this->Users[m_desc->SubServerID - 1].UserMaxRange; ++i)
        {
            if(this->Users[m_desc->SubServerID - 1].Users[i])
            {
                if(this->Users[m_desc->SubServerID - 1].Users[i]->Descriptor == m_desc)
                {
                    CNetMsg m_msg;

                    m_msg.Init(111);
                    m_msg.__ls(2);
                    m_msg.__ls(this->Users[m_desc->SubServerID - 1].Users[i]->Username);

                    ConnLogout(m_desc, m_msg);
                }
            }
        }
    }

    if(m_desc->NextNode)
    {
        m_desc->NextNode->Node = m_desc->Node;

        if(m_desc->Node)
            m_desc->Node->NextNode = m_desc->NextNode;
    }
    else
    {
        this->ClientDescriptors = m_desc->Node;

        if(m_desc->Node)
            m_desc->Node->NextNode = 0;
    }

    m_desc->NextNode = 0;
    m_desc->Node = 0;

    m_desc->CloseSocket();

    if(m_desc)
        delete m_desc;
}

void CServer::SendOutput(CDescriptor *m_desc)
{
    if(m_desc && !m_desc->WasErrors && m_desc->OutputBuffer.GetNextPoint() && FD_ISSET(m_desc->Socket, &this->WriteFDS))
    {
        if(m_desc->ProcessOutput() < 0)
            m_desc->WasErrors = true;
    }
}

bool CServer::DisConnectLogedIn(CDescriptor *)
{
    CDescriptor *m_next_node, *m_current_node;

    m_current_node = this->ClientDescriptors;

    while(1)
    {
        m_next_node = m_current_node;

        if(!m_current_node)
            break;

        m_current_node = m_current_node->Node;
        m_next_node->Unk152 = 1;
    }

    return false;
}

void CServer::CommandInterpreter(CDescriptor *m_desc, CNetMsg &m_msg)
{
    char m_conn;

    m_msg.MoveFirst();

    if(m_msg.MsgType != 111)
    {
INVALID_COMMAND:
        m_conn = *(char *)(m_msg.MsgData + 1);

        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("Invalid Command: ");
        g_gamelogbuffer.__ls((int)m_msg.MsgType);
        g_gamelogbuffer.__ls("(");
        g_gamelogbuffer.__ls(m_conn);
        g_gamelogbuffer.__ls(")");
        g_gamelogbuffer.__ls(end);
    }

    m_msg.__rs(m_conn);

    switch(m_conn)
    {
        case 14:
            ConnStashSeal(m_desc, m_msg);
            break;
        case 13:
            ConnStashChangePassword(m_desc, m_msg);
            break;
        case 12:
            ConnStashCheckPassword(m_desc, m_msg);
            break;
        case 11:
            ConnStashState(m_desc, m_msg);
            break;
        case 10:
            ConnLevelupPoint(m_desc, m_msg);
            break;
        case 9:
            ConnPreopenGift(m_desc, m_msg);
            break;
        case 0:
            ConnLogin(m_desc, m_msg);
            break;
        case 2:
            ConnLogout(m_desc, m_msg);
            break;
        case 3:
            ConnBLogin(m_desc, m_msg);
            break;
        case 4:
            ConnBLogout(m_desc, m_msg);
            break;
        case 6:
            ConnPlayerReq(m_desc, m_msg);
            break;
        case 5:
            ConnPlaying(m_desc, m_msg);
            break;
        case 8:
            this->Shutdowned    = true;
            this->WriteShutDown = true;
            break;
        default:
            goto INVALID_COMMAND;
    }
}

long long CServer::GetServerTime(void)
{
    time_t m_timer         = time(0);
    struct tm *m_localTime = localtime(&m_timer);
	
    this->SYear  = m_localTime->tm_year + 1900;
    this->SMonth = m_localTime->tm_mon + 1;
    this->SDay   = m_localTime->tm_mday;
    this->SHour  = m_localTime->tm_hour;
    this->SMin   = m_localTime->tm_min;
    this->SSec   = m_localTime->tm_sec;
	
    return 60LL * time(0);
}

int CServer::CheckPlayers(void)
{
    CUser *m_user;
    long i;

    for(i = 0; i < this->MaxSubServer; ++i)
    {	
        for(long j = 0; j < this->Users[i].UserMaxRange; ++j)
        {
            m_user = this->Users[i].Users[j];
            if(m_user)
            {
                if(m_user->PortalIndex >= 0)
                {
                    ++m_user->Timestamp;
                    if(m_user->Unk80 != 1)
                    {
                        ++m_user->Unk92;
                        if(m_user->Unk92 > 2400)
                        {
                            g_gamelogbuffer.__ls(init("DEL_PLIST", m_user->Username));
                            g_gamelogbuffer.__ls(end);

                            this->ProcessLogout(m_user);
                        }
                    }
                }
            }
        }
    }
    return i;
}

void CServer::SavePlayersCount(void)
{
    CDBCmd m_cmd;
    int m_count_max;
    long long m_index;

    --this->ConnectCount;
    --this->ConnectMax;

    if(this->ConnectCount <= 0 || this->ConnectMax <= 0)
    {
        if(this->ConnectCount < 0)
            this->ConnectCount = 0;
        if(this->ConnectMax < 0)
            this->ConnectMax = 0;
		
        m_cmd.Init(&this->UserSQL);
		
        for(int i = 0; i < this->MaxSubServer; ++i)
        {
            for(int j = 0; j <= 19; ++j)
            {
                if(this->Users[i].Count[j] >= 0)
                {
                    if(this->ConnectCount <= 0)
                    {
                        strcpy(g_buf, "INSERT INTO t_connect_count (a_count, a_date, a_server, a_sub_num, a_zone_num) VALUES (");
                        IntCat(g_buf, (int)this->Users[i].Count[j], false);
                        strcat(g_buf, ", date_format(now(), '%Y-%m-%d %H:%i:00'), ");
                        IntCat(g_buf, this->Number, false);
                        strcat(g_buf, ", ");
                        IntCat(g_buf, (int)(i + 1), false);
                        strcat(g_buf, ", ");
                        IntCat(g_buf, (int)j, false);
                        strcat(g_buf, ")");
						
                        m_cmd.SetQuery(g_buf);
                        m_cmd.Update();
			
                        g_gamelogbuffer.__ls(init("COUNT"));
                        g_gamelogbuffer.__ls("Sub");
                        g_gamelogbuffer.__ls(delim);
                        g_gamelogbuffer.__ls((int)(i + 1));
                        g_gamelogbuffer.__ls(delim);
                        g_gamelogbuffer.__ls("Zone");
                        g_gamelogbuffer.__ls(delim);
                        g_gamelogbuffer.__ls((int)j);
                        g_gamelogbuffer.__ls(delim);
                        g_gamelogbuffer.__ls((int)this->Users[i].Count[j]);
                        g_gamelogbuffer.__ls(end);
                    }
					
                    if(this->ConnectMax <= 0)
                    {
                        strcpy(g_buf, "SELECT * FROM t_connect_max WHERE a_date=CURDATE() AND a_server=");
                        IntCat(g_buf, this->Number, false);
                        strcat(g_buf, " AND a_sub_num=");
                        IntCat(g_buf, i + 1, false);
                        strcat(g_buf, " AND a_zone_num=");
                        IntCat(g_buf, j, false);
						
                        m_cmd.SetQuery(g_buf);
						
                        if(m_cmd.Open())
                        {
                            if(m_cmd.MoveNext())
                            {
                                m_count_max = 0;
                                m_cmd.GetRec("a_index", m_index);
                                m_cmd.GetRec("a_count_max", m_count_max);
								
                                if(m_count_max < (int)this->Users[i].Count[j])
                                    m_count_max = (int)this->Users[i].Count[j];
								
                                strcpy(g_buf, "UPDATE t_connect_max SET a_count=");
                                IntCat(g_buf, (int)this->Users[i].Count[j], false);
                                strcat(g_buf, ", a_count_max=");
                                IntCat(g_buf, (int)m_count_max, false);
                                strcat(g_buf, " WHERE a_index=");
                                IntCat(g_buf, (int)m_index, false);
								
                                m_cmd.SetQuery(g_buf);
                                m_cmd.Update();
                            }
                            else
                            {
                                strcpy(g_buf, "INSERT INTO t_connect_max (a_count, a_count_max, a_date, a_server, a_sub_num, a_zone_num) VALUES (");
                                IntCat(g_buf, (int)this->Users[i].Count[j], false);
                                strcat(g_buf, ", ");
                                IntCat(g_buf, (int)this->Users[i].Count[j], false);
                                strcat(g_buf, ", CURDATE(), ");
                                IntCat(g_buf, (int)this->Number, false);
                                strcat(g_buf, ", ");
                                IntCat(g_buf, (int)(i + 1), false);
                                strcat(g_buf, ", ");
                                IntCat(g_buf, (int)j, false);
                                strcat(g_buf, ")");
								
                                m_cmd.SetQuery(g_buf);
                                m_cmd.Update();
                            }
                        }
                    }
                }
            }
        }
		
        if(this->ConnectCount <= 0)
            this->ConnectCount = 6000;

        if(this->ConnectMax <= 0)
            this->ConnectMax = 2400;
    }
}

void CServer::ProcessLogout(CUser *m_user)
{
    long m_sub_server_num;

    if(m_user)
    {
        m_sub_server_num = m_user->SubServerNum;
		
        g_gamelogbuffer.__ls(init("LOGOUT", m_user->Username));
        g_gamelogbuffer.__ls(end);
	
        --this->Users[m_sub_server_num - 1].Count[m_user->ZoneNum];
	
        if(this->BillingClient.IsRunning())
            this->BillingClient.Logout(0);
	
        if(WriteDB(m_user->PortalIndex, m_user->ServerNum, m_sub_server_num, -1, m_user->Timestamp, 0, 0, 0))
        {
            g_gamelogbuffer.__ls(init("SYS_ERR", m_user->Username));
            g_gamelogbuffer.__ls("Cannot Update DB for Logout");
            g_gamelogbuffer.__ls(end);
        }

        this->Users[m_sub_server_num - 1].Remove(m_user, true);
    }
}

/*******************************************************************************
** Global variables
*******************************************************************************/

CServer gserver;
struct in_addr bind_addr;
int last_desc = 0;
