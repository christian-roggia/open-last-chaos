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

#ifndef SERVER
#define SERVER

#include "common.hpp"
#include "Descriptor.hpp"
#include "CmdMsg.hpp"
#include "ConfigFile.hpp"
#include "Utils.hpp"
#include "Random.hpp"
#include "DBCmd.hpp"

#include <cstdlib>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
#include <sys/cdefs.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include <fcntl.h>
#include <netdb.h>
#include <cstdlib>

class CServer
{
public:
    CServer();
    void Close();
    void CloseSocket(CDescriptor *desc);
    bool ConnectDB();
    void DisconnectDB();
    struct in_addr *GetBindAddr();
    int GetMaxPlayers();
    int GetNextSeqNo();
    char *GetServerPath();
    bool InitGame();
    int InitSocket();
    bool LoadSettingFile();
    bool LoadSettings();
    int NewDescriptor(int fd);
    void Nonblock(int fd);
    void ProcTimeout(CMsgListNode *msglistnode);
    void SendOutput(CDescriptor *desc);
    void SendToAllGameServer(CNetMsg &netmsg);
    void ServerSleep(timeval *timeout);
    signed int SetSendbuf(int fd);
    int SetServerTime();
    void Run();
    void CommandInterpreter(CDescriptor *desc, CNetMsg &netmsg);
    ~CServer();


private:
    _DWORD fdesc;
    CDescriptor *NewDesc;
    _DWORD dword8;
    fd_set m_readfds;
    fd_set m_writefds;
    fd_set m_exceptfds;
    fd_set m_unkfds;
    CMsgList MsgList;
    CConfigFile ConfigFile;
    MYSQL stMysql;
    int MaxPlayers;
    char some_char[4];
        char *ServerPath;
    int some_time[6];
    _BYTE byte225C;
    _DWORD dword2260;
    _DWORD dword2264;
    CGuildList GuildList;

};

#endif

extern int g_Shutdown;
extern int last_desc;
extern CServer gserver;
extern CConfigFile g_configfile;
extern struct in_addr g_bindaddr;
