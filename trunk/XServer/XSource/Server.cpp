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

CServer gserver;

CServer::CServer(void)
{
    this->CurrentDirectory = this->GetServerPath();
    this->MainSocket = -1;
    this->MainDesc = 0;
    FD_ZERO(&this->ReadFDS);
    FD_ZERO(&this->WriteFDS);
    FD_ZERO(&this->ExceptFDS);
    this->ServerShutdowned = false;
    mysql_init(&this->MySQLDataDB);
    mysql_init(&this->MySQLAuthDB);
    this->MySQLNextPing = 0;
}

CServer::~CServer()
{
    if(this->CurrentDirectory)
        free(this->CurrentDirectory);
}

char *CServer::GetServerPath(void)
{
    char *s_path;

    s_path = getcwd(0, 0x200);
    strcat(s_path, "/");

    return s_path;
}

void CServer::DisconnectDB(void)
{
    mysql_close(&this->MySQLDataDB);
    mysql_close(&this->MySQLAuthDB);
}

bool CServer::InitGame(void)
{
    if((this->MainSocket = socket_tcp_bind(g_mother_ip, g_mother_port)) < 0)
    {
        sys_err(__FUNCTION__, __LINE__, "BIND: Cannot set-up the main socket on [%s:%d]!", g_mother_ip, g_mother_port);
        return false;
    }

    sys_log(0, "Mother connection binded on [%s:%d] fd: %d", g_mother_ip, g_mother_port, this->MainSocket);
	
    XMap *m = new XMap();
    m->LoadMap("maps/LC_04/");
    this->xMaps.push_back(m);

    return true;
}

void CServer::ServerSleep(timeval *timeout)
{
    if(select(0, 0, 0, 0, timeout) < 0)
    {
        if(errno != 4)
        {
            sys_err(__FUNCTION__, __LINE__, "ABORT: Impossible to call select(): %s!", strerror(errno));
            exit(1);
        }
    }
}

int CServer::NewDescriptor(int fd)
{
    int m_socket;
    struct sockaddr addr;
    const char *szHostname;

    m_socket = socket_accept(fd, &addr);

    XDESC *desc = new XDESC();

    strncpy(desc->szAddr, inet_ntoa(*(struct in_addr *)&addr.sa_data[2]), 16);
    desc->sPort = *(unsigned short *)&addr.sa_data[4];

    //if((szHostname = *(const char **)gethostbyaddr(desc->szAddr, 4, 2)) == 0) szHostname = "<unknown host>";

    sys_log(0, "New connection from %s:%u (%s) fd %d", desc->szAddr, desc->sPort, szHostname, m_socket);

    desc->Socket = m_socket;
    desc->SetPhase(IP_TYPE_AUTH);
    
    if(this->MainDesc)
        this->MainDesc->NextNode = desc;
    
    desc->PreviousNode = this->MainDesc;
    desc->NextNode = 0;
    this->MainDesc = desc;

    return 0;
}

void CServer::CloseSocket(XDESC *m_desc)
{
    if(m_desc->NextNode)
    {
        m_desc->NextNode->PreviousNode = m_desc->PreviousNode;

        if(m_desc->PreviousNode)
            m_desc->PreviousNode->NextNode = m_desc->NextNode;
    }
    else
    {
        this->MainDesc = m_desc->PreviousNode;

        if(m_desc->PreviousNode)
            m_desc->PreviousNode->NextNode = 0;
    }

    m_desc->NextNode = 0;
    m_desc->PreviousNode = 0;
    m_desc->CloseSocket();

    if(m_desc)
        delete m_desc;
}
