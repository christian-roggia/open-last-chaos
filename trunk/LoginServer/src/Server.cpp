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

int last_desc = 0;
CServer gserver;
struct in_addr bind_addr;

CServer::CServer(void)
{
    this->p_path = this->GetServerPath();
    this->p_socket = -1;
    this->p_unk_desc1 = 0;
    this->p_messenger_desc = 0;
    this->p_connector_descs = 0;
    FD_ZERO(&this->p_readfds);
    FD_ZERO(&this->p_writefds);
    FD_ZERO(&this->p_exceptfds);
    memset(this->p_unk_array4, 0, 1024);
    this->p_max_players = 0;
    this->p_unk_char1 = 0;
    this->p_unk_char2 = 1;
    this->p_unk_char3 = 0;
    this->p_connecting_connector = 0;
    this->p_connecting_messenger = false;
    this->p_unk_dword1 = 0;
    this->p_unk_dword2 = 0;
    this->p_unk_dword3 = 0;
    this->p_array_connectors = 0;
    mysql_init(&this->mysql_user_db);
    mysql_init(&this->mysql_data_db);
    mysql_init(&this->mysql_auth_db);
    this->p_unk_dword5 = 0;
    this->p_min_client_ver = 0;
    this->p_max_client_ver = 0;
}

CServer::~CServer()
{
    if(this->p_path)
        delete [] this->p_path;
    if(this->p_connector_descs)
        delete [] this->p_connector_descs;
    if(this->p_connecting_connector)
        delete [] this->p_connecting_connector;
    if(this->p_array_connectors)
        delete [] this->p_array_connectors;
}

char *CServer::GetServerPath(void)
{
    char *s_path;

    s_path = getcwd(0, 0x200);
    strcat(s_path, "/");

    return s_path;
}

bool CServer::LoadSettingFile(void)
{
    char filename[128];

    printf("Load setting file....\n");
    sprintf(filename, "%s%s", this->p_path, "newStobm.bin");

    if(!this->p_conf_file.Load(filename, false))
        return false;

    if(this->p_conf_file.Find("Server", "No"))
        strcpy(g_buf, this->p_conf_file.Find("Server", "No"));

    if (!strlen(g_buf))
        return false;

    this->p_server_no = atoi(g_buf);
    strcmp(this->p_conf_file.Find("Server", "AllowExternalIP"), "FALSE") ? this->p_allow_external_ip = false : this->p_allow_external_ip = true;

    return true;
}

bool CServer::ConnectDB(void)
{
    if(!mysql_real_connect(&this->mysql_user_db, this->p_conf_file.Find("User DB", "IP"), this->p_conf_file.Find("User DB", "User"), this->p_conf_file.Find("User DB", "Password"), this->p_conf_file.Find("User DB", "DBName"), 3306, NULL, 0))
        return false;

    if(!mysql_real_connect(&this->mysql_data_db, this->p_conf_file.Find("Data DB", "IP"), this->p_conf_file.Find("Data DB", "User"), this->p_conf_file.Find("Data DB", "Password"), this->p_conf_file.Find("Data DB", "DBName"), 0, 0, 0))
        return false;

    if (!mysql_real_connect(&this->mysql_auth_db, this->p_conf_file.Find("Auth DB", "IP"), this->p_conf_file.Find("Auth DB", "User"), this->p_conf_file.Find("Auth DB", "Password"), this->p_conf_file.Find("Auth DB", "DBName"), 0, 0, 0))
        return false;

    return true;
}

void CServer::DisconnectDB(void)
{
    mysql_close(&this->mysql_user_db);
    mysql_close(&this->mysql_auth_db);
}

bool CServer::InitGame(void)
{
    CDBCmd db_cmd;

    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Client Version Loading...");
    g_gamelogbuffer.__ls(end);
    
    db_cmd.Init(&this->mysql_data_db);
    db_cmd.SetQuery("SELECT a_min, a_max FROM t_clientversion");
    
    if(!db_cmd.Open() || !db_cmd.MoveFirst() || !db_cmd.GetRec("a_min", this->p_min_client_ver) || !db_cmd.GetRec("a_max", this->p_max_client_ver))
        return false;

    db_cmd.Close();
    
    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Finding player limit.");
    g_gamelogbuffer.__ls(end);
    
    this->p_max_players = this->GetMaxPlayers();
    
    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Opening mother connection.");
    g_gamelogbuffer.__ls(end);
    
    this->p_socket = this->InitSocket();
    
    if(!this->MakeMessengerClient())
    {
        if(this->p_messenger_desc)
        {
            this->p_messenger_desc->CloseSocket();
            
            if(this->p_messenger_desc)
                delete this->p_messenger_desc;
            
            this->p_messenger_desc = 0;
        }
    }
    
    this->SendMessengerHeader();
    this->p_connector_count = atoi(this->p_conf_file.Find("Connector Server", "Count"));
    
    if(!this->p_connector_count)
        return false;

    this->p_connector_descs = (CDescriptor **)calloc(4 * this->p_connector_count, 1);
    this->p_connecting_connector = (bool *)malloc(this->p_connector_count);
    this->p_array_connectors = (int *)malloc(4 * this->p_connector_count);
    
    for(int i = 0; i < this->p_connector_count; ++i)
    {
        this->p_connecting_connector[i] = false;
        this->p_array_connectors[i] = 0;
        
        if (!this->MakeConnectorClient(i))
        {
            if(this->p_connector_descs[i])
            {
                this->p_connector_descs[i]->CloseSocket();
                
                if(this->p_connector_descs[i])
                    delete this->p_connector_descs[i];
                
                this->p_connector_descs[i] = 0;
            }
        }
        
        this->SendConnectorHeader(i);
    }
    
    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Entering Login Server...");
    g_gamelogbuffer.__ls(end);
    
    return true;
}

int CServer::GetMaxPlayers(void)
{
    struct rlimit m_rlimits;
    int m_player_limit = 0;
    const char *_limit = "rlimit";
    
    if(getrlimit(7, &m_rlimits) < 0)
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("calling getrlimit");
        g_gamelogbuffer.__ls(end);
        exit(1);
    }
    
    m_rlimits.rlim_cur = m_rlimits.rlim_max;
    if(setrlimit(7, &m_rlimits) < 0)
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("calling setrlimit");
        g_gamelogbuffer.__ls(end);
        exit(1);
    }
    
    if((signed int)m_rlimits.rlim_max == -1)
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
    
    if (m_player_limit <= 0)
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("Non-positive max player limit!    (Set at ");
        g_gamelogbuffer.__ls(m_player_limit);
        g_gamelogbuffer.__ls(" using ");
        g_gamelogbuffer.__ls(_limit);
        g_gamelogbuffer.__ls(").");
        g_gamelogbuffer.__ls(end);
        exit(1);
    }
    
    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Setting player limit to ");
    g_gamelogbuffer.__ls(m_player_limit);
    g_gamelogbuffer.__ls(" using ");
    g_gamelogbuffer.__ls(_limit);
    g_gamelogbuffer.__ls(".");
    g_gamelogbuffer.__ls(end);
    
    return m_player_limit;
}

int CServer::InitSocket(void)
{
    long optval = 1;
    int fd = socket(2, 1, 0);
    struct sockaddr_in addr;
    FILE *f_shut;
    
    if(fd < 0)
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("Error creating socket");
        g_gamelogbuffer.__ls(end);
        exit(1);
    }
    
    if(setsockopt(fd, 1, 2, &optval, 4) < 0)
    {
        printf("SYSERR: setsockopt REUSEADDR");
        exit(1);
    }
    
    this->SetSendbuf(fd);
    optval = 0;
    
    if(setsockopt(fd, 1, 13, &optval, 8) < 0)
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("setsockopt SO_LINGER");
        g_gamelogbuffer.__ls(end);
    }
    
    /* SOCKET STRUCT */
    memset((void *)&addr, 0, 16);
    addr.sin_family = 2;
    addr.sin_port = htons(atoi(this->p_conf_file.Find("Server", "Port")));
    addr.sin_addr = this->GetBindAddr();
    
    if(bind(fd, (struct sockaddr*)&addr, 16) < 0)
    {
        printf("SYSERR: bind\n");
        close(fd);
        f_shut = fopen(".shutdown", "w");
        fclose(f_shut);
        exit(1);
    }
    
    this->Nonblock(fd);
    listen(fd, 57);
    
    return fd;
}

int CServer::SetSendbuf(long fd)
{
    long optval = 0x3000;
    
    if(setsockopt(fd, 1, 7, &optval, 4) >= 0)
        return 0;
    
    g_gamelogbuffer.__ls(init("SYS_ERR"));
    g_gamelogbuffer.__ls("setsockopt SNDBUF");
    g_gamelogbuffer.__ls(end);
    
    return -1;
}

struct in_addr CServer::GetBindAddr(void)
{
    memset((void *)&bind_addr, 0, 4);
    
    if(strcmp(this->p_conf_file.Find("Server", "IP"), "ALL"))
        bind_addr.s_addr = inet_addr(this->p_conf_file.Find("Server", "IP"));
    else
        bind_addr.s_addr = htonl(0);
    
    if(bind_addr.s_addr == htonl(0))
    {
        g_gamelogbuffer.__ls(init("SYSTEM"));
        g_gamelogbuffer.__ls("Binding to all IP longerfaces on this m_host.");
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
    int v5 = fcntl(fd, F_GETFL, 0);

    if(fcntl(fd, F_SETFL, v5 | O_NONBLOCK) < 0)
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

    CDescriptor *desc = new CDescriptor();
    
    if(!this->p_unk_char2 && (m_host = *(const char **)gethostbyaddr(&addr.sa_data[2], 4, 2)) != 0)
    {
        strncpy(desc->Hostname, m_host, 30);
        desc->Unk178 = 0;
    }
    else
    {
        if(!this->p_unk_char2)
        {
            g_gamelogbuffer.__ls(init("SYS_ERR"));
            g_gamelogbuffer.__ls("gethostbyaddr");
            g_gamelogbuffer.__ls(end);
        }
        
        strncpy(desc->Hostname, inet_ntoa(*(struct in_addr *)&addr.sa_data[2]), 30);
        desc->Unk178 = 0;
    }

    desc->Socket = m_socket;
    desc->SocketPhase = 23;
    
    if(++last_desc == 100000000)
        last_desc = 1;
    
    if(this->p_unk_desc1)
        this->p_unk_desc1->NextNode = desc;
    
    desc->PreviousNode = this->p_unk_desc1;
    desc->NextNode = 0;
    this->p_unk_desc1 = desc;

    return 0;
}

void CServer::CloseSocket(CDescriptor *m_desc)
{
    if(m_desc->SocketPhase != 17)
    {
        m_desc->SocketPhase = 17;
        return;
    }

    if(m_desc->SocketPhase != 1)
    {
        if(m_desc->SocketPhase != 17)
        {
            g_gamelogbuffer.__ls(init("SYS_ERR"));
            g_gamelogbuffer.__ls("Close Socket Error :");
            g_gamelogbuffer.__ls(m_desc->SocketPhase);
            g_gamelogbuffer.__ls(end);
        }
    }

    if(m_desc->NextNode)
    {
        m_desc->NextNode->PreviousNode = m_desc->PreviousNode;

        if(m_desc->PreviousNode)
            m_desc->PreviousNode->NextNode = m_desc->NextNode;
    }
    else
    {
        this->p_unk_desc1 = m_desc->PreviousNode;

        if(m_desc->PreviousNode)
            m_desc->PreviousNode->NextNode = 0;
    }

    m_desc->NextNode = 0;
    m_desc->PreviousNode = 0;
    m_desc->CloseSocket();

    if(m_desc)
        delete m_desc;
}

void CServer::SendOutput(CDescriptor *m_desc)
{
    if(m_desc && !m_desc->WasErrors && m_desc->OutputBuffer.GetNextPoint() && FD_ISSET(m_desc->Socket, &this->p_writefds))
    {
        if(m_desc->ProcessOutput() < 0)
            m_desc->WasErrors = true;
    }
}

bool CServer::DisConnectLogedIn(CDescriptor *m_to_disconnect)
{
    CDescriptor *m_temp_desc = this->p_unk_desc1;

    while(m_temp_desc == m_to_disconnect || m_temp_desc->SocketPhase == 23);
    {
        if(!m_temp_desc)
            return false;

        m_temp_desc = m_temp_desc->PreviousNode;
    }

    if(m_temp_desc->SocketPhase != 17)
        m_temp_desc->SocketPhase = 1;

    return true;
}

void CServer::SetServerTime(void)
{
    time_t timer = time(0);
    struct tm *v3 = localtime(&timer);

    this->p_server_time_year = v3->tm_year % 100 / 62;
    this->p_server_time_year = v3->tm_year % 100 - 62 * this->p_server_time_year;
    this->p_server_time_month = v3->tm_mon + 1 / 62;
    this->p_server_time_month = v3->tm_mon + 1 - 62 * this->p_server_time_month;
    this->p_server_time_day = v3->tm_mday % 62;
    this->p_server_time_hour = v3->tm_hour % 62;
    this->p_server_time_min = v3->tm_min % 62;
    this->p_server_time_sec = v3->tm_sec % 62;
}

bool CServer::MakeConnectorClient(int m_num)
{
    char m_connector_name[20];
    long m_socket;
    struct sockaddr_in m_sockaddr;
    char m_error[50];

    if(this->p_connector_descs[m_num])
    {
        if(!this->p_connector_descs[m_num]->WasErrors)
            return 0;

        this->p_connector_descs[m_num]->CloseSocket();

        if(this->p_connector_descs[m_num])
            delete this->p_connector_descs[m_num];

        this->p_connector_descs[m_num] = 0;
    }

    this->p_connector_descs[m_num] = new CDescriptor();

    strcpy(m_connector_name, "Connector_");
    IntCat(m_connector_name, m_num, false);

    this->p_connector_descs[m_num]->Number              = atoi(this->p_conf_file.Find(m_connector_name, "Number"));
    this->p_connector_descs[m_num]->MaxSubNumber        = atoi(this->p_conf_file.Find(m_connector_name, "MaxSubNumber"));
    this->p_connector_descs[m_num]->ConnectorsUnk       = (int *)malloc(sizeof(long) * this->p_connector_descs[m_num]->MaxSubNumber);
    this->p_connector_descs[m_num]->ConnectorsUnk2      = (int *)malloc(sizeof(long) * this->p_connector_descs[m_num]->MaxSubNumber);
    this->p_connector_descs[m_num]->ConnectorsIP        = (char **)malloc(sizeof(long) * this->p_connector_descs[m_num]->MaxSubNumber);
    this->p_connector_descs[m_num]->ConnectorsID        = (int *)malloc(sizeof(long) * this->p_connector_descs[m_num]->MaxSubNumber);

    for(int i = 0; i < this->p_connector_descs[m_num]->MaxSubNumber; ++i)
    {
        this->p_connector_descs[m_num]->ConnectorsUnk[i] = -1;
        this->p_connector_descs[m_num]->ConnectorsID[i] = i + 1;
        this->p_connector_descs[m_num]->ConnectorsIP[i] = (char *)"";
        this->p_connector_descs[m_num]->ConnectorsUnk2[i] = -1;
    }

    m_socket = socket(2, 1, 6);
    this->p_connector_descs[m_num]->Socket = m_socket;

    if(m_socket < 0)
    {
        puts("SYSERR: Error opening network connection : Winsock error");
        return false;
    }

    if(this->p_connector_descs[m_num]->Socket <= 0)
        return false;

    memset((void *)&m_sockaddr, 0, 16);
    m_sockaddr.sin_family       = AF_INET;
    m_sockaddr.sin_addr.s_addr  = inet_addr(this->p_conf_file.Find(m_connector_name, "IP"));
    m_sockaddr.sin_port         = htons(atoi(this->p_conf_file.Find(m_connector_name, "Port")));

    if(connect(this->p_connector_descs[m_num]->Socket, (const struct sockaddr *)&m_sockaddr, 16) < 0)
    {
        strcpy(m_error, "SYSERR: Cannot connect Connector_");
        IntCat(m_error, m_num, 0);
        strcat(m_error, " Server!!!");
        puts(m_error);

        return false;
    }

    this->Nonblock(this->p_connector_descs[m_num]->Socket);
    this->SetSendbuf(this->p_connector_descs[m_num]->Socket);

    return true;
}

void CServer::SendConnectorHeader(long m_num)
{
    CNetMsg m_msg;
    
    m_msg.Init(110);
    m_msg.__ls((int)600);
    m_msg.__ls((int)999);
    m_msg.__ls(0);
    
    if(this->p_connector_descs[m_num] && !this->p_connector_descs[m_num]->WasErrors)
    {
        if(this->p_connector_descs[m_num])
            this->p_connector_descs[m_num]->WriteToOutput(m_msg);
        
        if(!this->p_connector_descs[m_num] || this->p_connector_descs[m_num]->Socket < 0 || this->p_connector_descs[m_num]->WasErrors)
            return;
        
        if(this->p_connector_descs[m_num]->OutputBuffer.GetNextPoint() && this->p_connector_descs[m_num]->ProcessOutput() < 0)
            this->p_connector_descs[m_num]->WasErrors = true;
        
        PlayerReqMsg(m_msg);
        
        if(this->p_connector_descs[m_num])
            this->p_connector_descs[m_num]->WriteToOutput(m_msg);
    }
}

bool CServer::MakeMessengerClient(void)
{
    long m_socket;
    struct sockaddr_in m_sockaddr;

    if(this->p_messenger_desc)
    {
        if(this->p_messenger_desc->WasErrors)
        {
            this->p_messenger_desc->CloseSocket();
            
            if(this->p_messenger_desc)
                delete this->p_messenger_desc;
                
            this->p_messenger_desc = 0;
        }
    }
    
    this->p_messenger_desc = new CDescriptor();
    
    m_socket = socket(2, 1, 0);
    this->p_messenger_desc->Socket = m_socket;
    
    if(m_socket < 0)
    {
        puts("SYSERR: Error opening network connection: socket error");
        return false;
    }
    
    memset((void *)&m_sockaddr, 0, 16);
    m_sockaddr.sin_family       = AF_INET;
    m_sockaddr.sin_addr.s_addr  = inet_addr(this->p_conf_file.Find("Messenger Server", "IP"));
    m_sockaddr.sin_port         = htons(atoi(this->p_conf_file.Find("Messenger Server", "Port")));
    
    if(connect(this->p_messenger_desc->Socket, (const struct sockaddr *)&m_sockaddr, 16) < 0)
    {
        puts("SYSERR: Cannot connect Messenger...");
        return false;
    }
    
    this->Nonblock(this->p_messenger_desc->Socket);
    this->SetSendbuf(this->p_messenger_desc->Socket);
    
    return true;
}

void CServer::SendMessengerHeader(void)
{
    CNetMsg m_msg;
    
    m_msg.Init(100);
    m_msg.__ls(600);
    m_msg.__ls(999);
    m_msg.__ls(0);
    m_msg.__ls(0);
    
    if(this->p_messenger_desc && !this->p_messenger_desc->WasErrors)
    {
        if(this->p_messenger_desc)
            this->p_messenger_desc->WriteToOutput(m_msg);
        
        if(!this->p_messenger_desc || this->p_messenger_desc->Socket < 0 || this->p_messenger_desc->WasErrors)
            return;
        
        if(this->p_messenger_desc->OutputBuffer.GetNextPoint() && this->p_messenger_desc->ProcessOutput() < 0)
            this->p_messenger_desc->WasErrors = true;
    }
}

void *CServer::ConnectorConnect(void *pt_num)
{
    long m_num = *(long *)&pt_num;
    
    gserver.p_connecting_connector[m_num] = true;
    
    while(!gserver.MakeConnectorClient(m_num))
    {
        if(gserver.p_connector_descs[m_num])
            gserver.p_connector_descs[m_num]->WasErrors = true;
        
        sleep(2);
    }
    
    gserver.SendConnectorHeader(m_num);
    gserver.p_connecting_connector[m_num] = false;
    
    pthread_exit(0);
}

void *CServer::MessengerConnect(void *pt)
{
    gserver.p_connecting_messenger = true;
    
    while(!gserver.MakeMessengerClient())
    {
        if(gserver.p_messenger_desc)
            gserver.p_messenger_desc->WasErrors = true;
        
        sleep(2);
    }
    
    gserver.SendMessengerHeader();
    gserver.p_connecting_messenger = false;
    
    pthread_exit(0);
}

void CServer::ProcConnector(CNetMsg &m_msg)
{
    int v7 = 0;
    int i;
    char m_host_ip[32];
    int v12;
    int v13;
    int v14;
    int dest;
    int v16;
    char v17;

    m_msg.MoveFirst();

    if(m_msg.p_msg_type == 112)
    {
        m_msg.__rs(v17);

        if(v17 == 7)
        {
            m_msg.__rs(dest);
            m_msg.__rs(v16);

            for(i = 0; i < this->p_connector_count; ++i)
            {
                if(this->p_connector_descs[i] && !this->p_connecting_connector[i] && dest == this->p_connector_descs[i]->Number)
                {
                    if(v16 >= this->p_connector_descs[i]->MaxSubNumber)
                        v7 = this->p_connector_descs[i]->MaxSubNumber;
                    else
                        v7 = v16;
                    break;
                }
            }
            
            if(i != this->p_connector_count)
            {
                for(int j = 0; j < v7; ++j)
                {
                    m_msg.__rs(v14);
                    m_msg.__rs(v13);
                    m_msg.__rs(m_host_ip);
                    m_msg.__rs(v12);

                    for(int k = 0; k < this->p_connector_descs[i]->MaxSubNumber; ++k)
                    {
                        if(v14 == this->p_connector_descs[i]->ConnectorsID[k])
                        {
                            this->p_connector_descs[i]->ConnectorsUnk[k] = v13;
                            this->p_connector_descs[i]->ConnectorsIP[k] = (char *)malloc(32);
                            strcpy(this->p_connector_descs[i]->ConnectorsIP[k], m_host_ip);
                            this->p_connector_descs[i]->ConnectorsUnk2[k] = v12;
                        }
                    }
                }
            }
        }
    }
}

void CServer::ProcMessenger(CNetMsg &m_msg)
{
    char *v12 = 0;
    char v13;
    char v14;
    char v15;
    char v16;
    char v17;
    char dest;

    m_msg.MoveFirst();
    m_msg.__rs(dest);
    m_msg.__rs(v17);
    m_msg.__rs(v16);
    m_msg.__rs(v15);
    m_msg.__rs(v14);
    
    if(m_msg.p_msg_type == 101)
    {
        if(v14 == 12)
        {
            this->p_unk_char1 = 1;
            this->p_unk_char3 = 1;
        }
    }
    else
    {
        if(m_msg.p_msg_type == 102 && v14 == 9)
        {
            m_msg.__rs(v13);
            m_msg.__rs(v12);
            
            g_gamelogbuffer.__ls(init("LOGIN ERROR", v12));
            g_gamelogbuffer.__ls("CANNOT DISCONNECT ALREADY CONNECTION");
            g_gamelogbuffer.__ls(end);
        }
    }
}
