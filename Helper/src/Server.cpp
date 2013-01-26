/******************************************************************************************
  Copyright 2013 Andrea Ragusa

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

#include "Server.hpp"

int g_Shutdown;
int last_desc;
CServer gserver;
CConfigFile g_configfile;
struct in_addr g_bindaddr;

CServer::CServer()
{
//    int v1; // [sp+4Ch] [bp-8h]@1
//    CMsgList *v2; // [sp+50h] [bp-4h]@1

//    CMsgList::CMsgList(&this->MsgList);
//    CConfigFile::CConfigFile(&this->ConfigFile);
//    CGuildList::CGuildList(&this->GuildList);
    this->fdesc = -1;
    this->NewDesc = 0;
    this->dword8 = 0;
    FD_ZERO(&this->m_readfds);
    FD_ZERO(&this->m_writefds);
    FD_ZERO(&this->m_exceptfds);
    FD_ZERO(&this->m_unkfds);
    /*
    memset(&this->m_readfds, 0, 1024u);
    memset(&this->m_writefds, 0, 1024u);
    memset(&this->m_exceptfds, 0, 1024u);
    memset(&this->m_unkfds, 0, 1024u);
    */
//    v1 = 0;
//    v2 = &this->MsgList;
    this->MsgList.Sequence = 1;
    this->ServerPath = CServer::GetServerPath();
    this->MaxPlayers = 0;
    this->byte225C = 0;
    this->some_char[0] = 1;
    this->dword2260 = 0;
    this->dword2264 = 0;
    mysql_init(&this->stMysql);
}

void CServer::Close()
{
    CDescriptor *p_desc; // [sp+28h] [bp-8h]@1
    CDescriptor *a2; // [sp+2Ch] [bp-4h]@2

    p_desc = this->NewDesc;
    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Saving All User Data....");
    g_gamelogbuffer.__ls(end);
    while ( 1 )
    {
        a2 = p_desc;
        if ( !p_desc )
            break;
        p_desc = a2->SubDesc;
        CServer::CloseSocket(a2);
    }
    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Closing all sockets.");
    g_gamelogbuffer.__ls(end);
    close(this->fdesc);
    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Normal termination of game.");
    g_gamelogbuffer.__ls(end);
    sleep(10u);
}

void CServer::CloseSocket(CDescriptor *desc)
{

    if ( desc->some_errno <= 0 || desc->socket_ret == 17 )
    {
        if ( desc->socket_ret != 1 && desc->socket_ret != 17 )
        {
            g_gamelogbuffer.__ls(init("SYSTEM"));
            g_gamelogbuffer.__ls("Normal termination of game.");
            g_gamelogbuffer.__ls(desc->socket_ret);
            g_gamelogbuffer.__ls(end);
        }
        if ( desc->ServerDesc )
        {
            desc->ServerDesc->SubDesc = desc->SubDesc;
            if ( desc->SubDesc )
                desc->SubDesc->ServerDesc = desc->ServerDesc;
        }
        else
        {
            this->NewDesc = desc->SubDesc;
            if ( desc->SubDesc )
                desc->SubDesc->ServerDesc = 0;
        }
        desc->ServerDesc = 0;
        desc->SubDesc = 0;
        desc->CloseSocket();
        this->MsgList.RemoveServer(desc);
        if ( desc )
            //CDescriptor::_CDescriptor(desc, 3);
            delete desc;
    }
    else
    {
        desc->socket_ret = 17;
        desc->some_errno = 2;
    }
}

bool CServer::ConnectDB()
{
    char *p_dbname; // ST18_4@1
    char *p_password; // ST14_4@1
    char *p_user; // ST10_4@1
    char *p_ip; // eax@1
    bool result; // al@2

    p_dbname = this->ConfigFile.Find("Char DB", "DBName");
    p_password = this->ConfigFile.Find("Char DB", "Password");
    p_user = this->ConfigFile.Find("Char DB", "User");
    p_ip = this->ConfigFile.Find("Char DB", "IP");
    //printf("connecting to %s:%s@%s using %s\n", p_user, p_password, p_ip, p_dbname);
    if ( mysql_real_connect(&this->stMysql, p_ip, p_user, p_password, p_dbname, 0, 0, 0) )
        result = 1;
    else
        result = 0;
    return result;
}

void CServer::DisconnectDB()
{
    mysql_close(&this->stMysql);
}

struct in_addr *CServer::GetBindAddr()
{
    char *v1; // eax@1
    char *v2; // eax@3
    in_addr_t v11; // [sp+28h] [bp-4h]@3

    memset(&g_bindaddr, 0, 4u);
    v1 = this->ConfigFile.Find("Server", "IP");
    if ( strcmp(v1, "ALL") )
    {
        v2 = this->ConfigFile.Find("Server", "IP");
        v11 = inet_addr(v2);
        g_bindaddr.s_addr = v11;
    }
    else
    {
        g_bindaddr.s_addr = htonl(0);
    }
    if ( g_bindaddr.s_addr == htonl(0) )
    {
        g_gamelogbuffer.__ls(init("SYSTEM"));
        g_gamelogbuffer.__ls("Binding to all IP interfaces on this m_host.");
        g_gamelogbuffer.__ls(end);
    }
    else
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("Binding only to IP address");
        g_gamelogbuffer.__ls(inet_ntoa(g_bindaddr));
        g_gamelogbuffer.__ls(end);
    }
    return &g_bindaddr;
}

int CServer::GetMaxPlayers()
{
    int v5; // eax@9
    signed int v6; // eax@12
    struct rlimit rlimits; // [sp+30h] [bp-10h]@1
    int v27; // [sp+3Ch] [bp-4h]@1

    v27 = 0;
    if ( getrlimit(7, &rlimits) < 0 )
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("calling getrlimit");
        g_gamelogbuffer.__ls(end);
        exit(1);
    }
    rlimits.rlim_cur = rlimits.rlim_max;
    if ( setrlimit(7, &rlimits) < 0 )
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("calling setrlimit");
        g_gamelogbuffer.__ls(end);
        exit(1);
    }
    if ( rlimits.rlim_max == -1 )
    {
        v27 = 50005;
    }
    else
    {
        v5 = rlimits.rlim_max;
        if ( rlimits.rlim_max > 0xC355 )
            v5 = 50005;
        v27 = v5;
    }
    v27 -= 5;
    v6 = v27;
    if ( v27 > 50000 )
        v6 = 50000;
    v27 = v6;
    if ( v6 <= 0 )
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("Non-positive max player limit!  (Set at");
        g_gamelogbuffer.__ls(v27);
        g_gamelogbuffer.__ls("using rlimit)");
        g_gamelogbuffer.__ls(end);
        exit(1);
    }
    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Setting player limit to ");
    g_gamelogbuffer.__ls(v27);
    g_gamelogbuffer.__ls(" using rlimit.");
    g_gamelogbuffer.__ls(end);
    return v27;
}

int CServer::GetNextSeqNo()
{
    return this->MsgList.Sequence++;
}

char *CServer::GetServerPath()
{
    size_t len; // eax@1
    char *v1; // ST34_4@1
    char src[0x200]; // [sp+20h] [bp-400h]@1

    getcwd((char *)&src, 0x200u);
    strcat((char *)&src, "/");
    len = strlen(src);
    v1 = new char[len + 1];
    strcpy(v1, (char *)&src);
    return v1;
}

bool CServer::InitGame()
{
    time_t v1; // eax@1

    v1 = time(0);
    ServerSrandom(v1);
    MakeMath();
    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Finding player limit.");
    g_gamelogbuffer.__ls(end);
    this->MaxPlayers = CServer::GetMaxPlayers();
    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Opening mother connection.");
    g_gamelogbuffer.__ls(end);
    this->fdesc = CServer::InitSocket();
    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Entering game loop.");
    g_gamelogbuffer.__ls(end);
    return 1;
}

int CServer::InitSocket()
{
    char *port; // eax@9
    int iport; // ax@9
    FILE *v9; // ST44_4@10
    int v11; // [sp+1Ch] [bp-30h]@7
    int v12; // [sp+20h] [bp-2Ch]@7
    int optval; // [sp+34h] [bp-18h]@4
    sockaddr_in sockaddr; // [sp+38h] [bp-14h]@9
    int fd; // [sp+48h] [bp-4h]@1

    fd = socket(2, 1, 0);
    if ( fd < 0 )
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("Error creating socket");
        g_gamelogbuffer.__ls(end);
        exit(1);
    }
    optval = 1;
    if ( setsockopt(fd, 1, 2, &optval, sizeof(optval)) < 0 )
    {
        puts("SYSERR: setsockopt REUSEADDR");
        exit(1);
    }
    CServer::SetSendbuf(fd);
    v11 = 0;
    v12 = 0;
    if ( setsockopt(fd, 1, 13, &v11, 8u) < 0 )
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("setsockopt SO_LINGER");
        g_gamelogbuffer.__ls(end);
    }
    memset(&sockaddr, 0, 16u);
    sockaddr.sin_family = 2;
    #warning g_configfile che cazzo di fine fa?
    //port = g_configfile.Find("Server", "Port");
    port = this->ConfigFile.Find("Server", "Port");
    //printf("port %s\n",port);
    iport = atoi(port);
    sockaddr.sin_port = htons(iport);
    sockaddr.sin_addr.s_addr = CServer::GetBindAddr()->s_addr;
    if ( bind(fd, (const struct sockaddr *)&sockaddr, 0x10u) < 0 )
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("bind");
        g_gamelogbuffer.__ls(end);
        close(fd);
        v9 = fopen(".shutdown", "w");
        fclose(v9);
        exit(1);
    }
    CServer::Nonblock(fd);
    listen(fd, 57);
    return fd;
}


bool CServer::LoadSettingFile()
{
    bool result; // al@2
    char filename[255]; // [sp+24h] [bp-400h]@1

    puts("Load setting file....");
    sprintf(filename, "%s%s", this->ServerPath, "newStobm.bin");
    //printf("%s%s\n", this->MsgList.ServerPath, "newStobm.bin");
    if ( this->ConfigFile.Load(filename) )
        result = 1;
    else
        result = 0;
    return result;
}

bool CServer::LoadSettings()
{
    bool result; // al@2
    int v10; // [sp+20h] [bp-20D0h]@8
    int v11; // [sp+24h] [bp-20CCh]@8
    char src; // [sp+28h] [bp-20C8h]@8
    int v13; // [sp+5Ch] [bp-2094h]@8
    int v15; // [sp+64h] [bp-208Ch]@5
    char s; // [sp+68h] [bp-2088h]@5
    int v17; // [sp+9Ch] [bp-2054h]@5
    CGuild *t_guild;

    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls( "Load settings....");
    g_gamelogbuffer.__ls(end);
    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Load Guild....");
    g_gamelogbuffer.__ls(end);
    CDBCmd dbcmd;
    dbcmd.Init(&this->stMysql);
    dbcmd.SetQuery("SELECT * FROM t_guild WHERE a_enable=1 ORDER BY a_index");
    if ( dbcmd.Open() )
    {
        CDBCmd t_dbcmd;
        t_dbcmd.Init(&this->stMysql);
        while ( dbcmd.MoveNext() )
        {
            dbcmd.GetRec("a_index", &v17);
            dbcmd.GetRec("a_name", &s, 1);
            dbcmd.GetRec("a_level", &v15);
            t_guild = this->GuildList.create(v17, &s, v15);
            this->GuildList.add(t_guild);
            sprintf(g_buf, "SELECT * FROM t_guildmember WHERE a_guild_index=%d", v17);
            t_dbcmd.SetQuery(g_buf);
            if ( !t_dbcmd.Open() )
            {
                g_gamelogbuffer.__ls(init("SYS_ERR"));
                g_gamelogbuffer.__ls("Cannot load guild");
                g_gamelogbuffer.__ls(end);
                //CDBCmd::_CDBCmd(&t_dbcmd, 2);
                //CDBCmd::_CDBCmd(&dbcmd, 2);
                return 0;
            }
            while ( t_dbcmd.MoveNext() )
            {
                t_dbcmd.GetRec("a_char_index", &v13);
                t_dbcmd.GetRec("a_char_name", &src, 1);
                t_dbcmd.GetRec("a_pos", &v11);
                v10 = t_guild->addmember(v13, &src);
                if ( v11 )
                {
                    if ( v11 == 1 )
                        t_guild->appoint(v10);
                }
                else
                {
                    t_guild->changeboss(v10);
                                            }
                                        }
                                    }
                                    //CDBCmd::_CDBCmd(&t_dbcmd, 2);
                                    //CDBCmd::_CDBCmd(&dbcmd, 2);
                                    result = 1;
    }
    else
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("Cannot load guild");
        g_gamelogbuffer.__ls(end);
        //CDBCmd::_CDBCmd(&dbcmd, 2);
        result = 0;
    }
    return result;
}

int CServer::NewDescriptor(int fd)
{
    int result; // eax@2
    char *v7; // eax@9
    const char **v9; // [sp+2Ch] [bp-20h]@6
    struct sockaddr_in addr; // [sp+30h] [bp-1Ch]@1
    socklen_t addr_len; // [sp+44h] [bp-8h]@1
    int newsockfd; // [sp+48h] [bp-4h]@1

    addr_len = 16;
    newsockfd = accept(fd, (struct sockaddr *)&addr, &addr_len);
    if ( newsockfd == -1 )
    {
        result = -1;
    }
    else
    {
        CServer::Nonblock(newsockfd);
        if ( CServer::SetSendbuf(newsockfd) >= 0 )
        {
            //v3 = (CDescriptor *)__builtin_new(196);
            //CDescriptor::CDescriptor(v3);
            //p_desc = v4;
            CDescriptor *p_desc = new CDescriptor;
            if ( !this->some_char[0] && (v9 = (const char **)gethostbyaddr(&addr.sin_addr, 4u, 2)) != 0 )
            {
                strncpy(p_desc->NormalIP, *v9, 30u);
                p_desc->NormalIP[30] = 0;
            }
            else
            {
                if ( !this->some_char[0] )
                {
                    g_gamelogbuffer.__ls(init("SYS_ERR"));
                    g_gamelogbuffer.__ls("gethostbyaddr");
                    g_gamelogbuffer.__ls(end);
                }
                v7 = inet_ntoa(addr.sin_addr);
                strncpy(p_desc->NormalIP, v7, 30u);
                p_desc->NormalIP[30] = 0;
            }
            p_desc->SocketDesc = newsockfd;
            p_desc->socket_ret = 23;
            ++last_desc;
            if ( last_desc == 100000000 )
                last_desc = 1;
            p_desc->Lastfd = last_desc;
            if ( this->NewDesc )
                this->NewDesc->ServerDesc = p_desc;
            p_desc->SubDesc = this->NewDesc;
            p_desc->ServerDesc = 0;
            this->NewDesc = p_desc;
            result = 0;
        }
        else
        {
            close(newsockfd);
            result = 0;
        }
    }
    return result;
}

void CServer::Nonblock(int fd)
{
    int v4; // [sp+24h] [bp-4h]@1

    v4 = fcntl(fd, 3, 0);
    BYTE1(v4) |= 8u;
    if ( fcntl(fd, 4, v4) < 0 )
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("Fatal error executing nonblock (CServer.cpp)");
        g_gamelogbuffer.__ls(end);
        exit(1);
    }
}

void CServer::ProcTimeout(CMsgListNode *msglistnode)
{
    int v6; // STA0_4@2
    int v7; // ST88_4@2
    int v8; // ST58_4@2
    int v9; // ST28_4@2
    float v30; // [sp+18h] [bp-C0h]@12
    float dest; // [sp+1Ch] [bp-BCh]@12
    int a10; // [sp+20h] [bp-B8h]@12
    int a9; // [sp+24h] [bp-B4h]@12
    int a8; // [sp+28h] [bp-B0h]@12
    char v36[100]; // [sp+40h] [bp-98h]@9
    int a7; // [sp+A4h] [bp-34h]@9
    CDescriptor *newdesc; // [sp+A8h] [bp-30h]@2
    CDescriptor *c_newdesc; // [sp+ACh] [bp-2Ch]@3
    CNetMsg *p_netmsg; // [sp+C0h] [bp-18h]@1
#warning Potrebbe non essere un puntatore!
    unsigned __int8 v42; // [sp+C7h] [bp-11h]@2
    int a5; // [sp+C8h] [bp-10h]@2
    int a4; // [sp+CCh] [bp-Ch]@2
    int a3; // [sp+D0h] [bp-8h]@2
    uint32_t src; // [sp+D4h] [bp-4h]@2

    p_netmsg = &msglistnode->NetMsg;
    if ( msglistnode->NetMsg.p_msg_type == 121 )
    {
        p_netmsg->MoveFirst();
        p_netmsg->__rs(src);
        p_netmsg->__rs(a3);
        p_netmsg->__rs(a4);
        p_netmsg->__rs(a5);
        p_netmsg->__rs(v42);
        v6 = v42;
        v7 = p_netmsg->p_msg_type;
        v8 = a4;
        v9 = a3;
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("server");
        g_gamelogbuffer.__ls(" : ");
        g_gamelogbuffer.__ls(v9);
        g_gamelogbuffer.__ls(" : ");
        g_gamelogbuffer.__ls("sub");
        g_gamelogbuffer.__ls(" : ");
        g_gamelogbuffer.__ls(v8);
        g_gamelogbuffer.__ls(" : ");
        g_gamelogbuffer.__ls("messege");
        g_gamelogbuffer.__ls(" : ");
        g_gamelogbuffer.__ls(v7);
        g_gamelogbuffer.__ls(" : ");
        g_gamelogbuffer.__ls(v6);
        g_gamelogbuffer.__ls(end);
        newdesc = this->NewDesc;
        do
        {
            c_newdesc = newdesc;
            if ( !newdesc )
                break;
            newdesc = c_newdesc->SubDesc;
        }
        while ( c_newdesc != msglistnode->desc );
        if ( c_newdesc )
        {
            if ( v42 )
            {
                if ( v42 == 5 )
                {
                    p_netmsg->__rs(a7);
                    p_netmsg->__rs(a8);
                    p_netmsg->__rs(a9);
                    p_netmsg->__rs(a10);
                    p_netmsg->__rs(dest);
                    p_netmsg->__rs(v30);
                    //CNetMsg::CNetMsg(&t_netmsg);
                    CNetMsg t_netmsg;
                    HelperGoZoneRepMsg(t_netmsg, src, a3, a4, a5, 0, a7, a8, a9, a10, dest, v30);
                    if ( msglistnode->desc )
                        msglistnode->desc->WriteToOutput(t_netmsg);
                    //CNetMsg::_CNetMsg(&t_netmsg, 2);
                }
            }
            else
            {
                p_netmsg->__rs(a7);
                p_netmsg->__rs(v36);
                CNetMsg t_netmsg;
                //CNetMsg::CNetMsg(&t_netmsg);
                HelperWhisperNotfoundMsg(t_netmsg, src, a3, a4, a5, a7, v36);
                if ( msglistnode->desc )
                    msglistnode->desc->WriteToOutput(t_netmsg);
                //CNetMsg::_CNetMsg(&t_netmsg, 2);
            }
        }
        if ( msglistnode->ActualListNode )
        {
            msglistnode->ActualListNode->NewListNode = msglistnode->NewListNode;
            if ( msglistnode->NewListNode )
                msglistnode->NewListNode->ActualListNode = msglistnode->ActualListNode;
        }
        else
        {
            this->MsgList.pMsgListNode = msglistnode->NewListNode;
            if ( msglistnode->NewListNode )
                msglistnode->NewListNode->ActualListNode = 0;
        }
        msglistnode->ActualListNode = 0;
        msglistnode->NewListNode = 0;
        if ( msglistnode )
            //CMsgListNode::_CMsgListNode(msglistnode, 3);
            delete msglistnode;
    }
}

void CServer::SendOutput(CDescriptor *desc)
{
  if ( desc
    && !desc->Iserr
    && desc->OutBuf.GetNextPoint()
    //&& _bittest((int *)&this->m_writefds + (desc->SocketDesc >> 5), desc->SocketDesc & 0x1F)
    && FD_ISSET(desc->SocketDesc, &this->m_writefds)
      )
  {
    if ( desc->ProcessOutput() < 0 )
      desc->Iserr = 1;
  }
}

void CServer::SendToAllGameServer(CNetMsg &netmsg)
{
  CDescriptor *p_desc;

  for ( p_desc = this->NewDesc; p_desc; p_desc = p_desc->SubDesc )
  {
    if ( p_desc->zone_count && !p_desc->socket_ret )
    {
      if ( p_desc )
        p_desc->WriteToOutput(netmsg);
    }
  }
}

void CServer::ServerSleep(timeval *timeout)
{

  if ( select(0, 0, 0, 0, timeout) < 0 && errno != 4 )
  {
    g_gamelogbuffer.__ls(init("SYS_ERR"));
    g_gamelogbuffer.__ls("Select sleep!!");
    g_gamelogbuffer.__ls(end);
    exit(1);
  }
}

signed int CServer::SetSendbuf(int fd)
{
  signed int result; // eax@2
  int optval; // [sp+24h] [bp-4h]@1

  optval = 12288;
  if ( setsockopt(fd, 1, 7, &optval, 4u) >= 0 )
  {
    result = 0;
  }
  else
  {
    g_gamelogbuffer.__ls(init("SYS_ERR"));
    g_gamelogbuffer.__ls("setsockopt SNDBUF");
    g_gamelogbuffer.__ls(end);
    result = -1;
  }
  return result;
}

int CServer::SetServerTime()
{
    #warning da controllare per benino
  CServer *v1; // ebx@1
  struct tm *v2; // eax@1
  int v3; // ST3C_4@1
  signed int v4; // ST3C_4@1
  int result; // eax@1
  time_t timer; // [sp+30h] [bp-4h]@1

  v1 = this;
  timer = time(0);
  v2 = localtime(&timer);
  v3 = v2->tm_year % 100;
  this->some_time[0] = v3 / 62;
  v1->some_time[0] = v3 - 62 * v1->some_time[0];
  v4 = v2->tm_mon + 1;
  this->some_time[1] = v4 / 62;
  v1->some_time[1] = v4 - 62 * v1->some_time[1];
  this->some_time[2] = v2->tm_mday % 62;
  this->some_time[3] = v2->tm_hour % 62;
  this->some_time[4] = v2->tm_min % 62;
  result = v2->tm_sec % 62;
  this->some_time[5] = result;
  return result;
}

CServer::~CServer()
{
  if ( this->ServerPath && this->ServerPath )
    //__builtin_vec_delete(this->MsgList.ServerPath);
    delete this->ServerPath;
  //CGuildList::_CGuildList(&this->GuildList, 2);
  //CConfigFile::_CConfigFile(&this->ConfigFile, 2);
  //CMsgList::_CMsgList(&this->MsgList, 2);
  //if ( a2 & 1 )
  //  __builtin_delete();
}
