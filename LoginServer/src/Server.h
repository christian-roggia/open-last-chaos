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

class CServer;

#ifndef SERVER_H
#define SERVER_H

#include "Descriptor.h"
#include "ConfigFile.h"
#include "DBCmd.h"
#include "CmdMsg.h"
#include "Log.h"
#include "Utils.h"

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

class CServer {
public:
    int p_socket;                    // + 0
    CDescriptor *p_unk_desc1;        // + 4
    CDescriptor *p_messenger_desc;   // + 8
    fd_set p_readfds;                // + 12
    fd_set p_writefds;               // + 1036
    fd_set p_exceptfds;              // + 2060
    int32_t p_unk_array4[256];       // + 3084
    CDescriptor **p_connector_descs; // + 4108
    int p_connector_count;           // + 4112
    char *p_path;                    // + 4116
    CConfigFile p_conf_file;         // + 4120
    int p_server_no;                 // + 8220
    unsigned int p_min_client_ver;   // + 8224
    unsigned int p_max_client_ver;   // + 8228
    bool p_allow_external_ip;        // + 8232
    int p_max_players;               // + 8236
    char p_unk_char1;                // + 8240 <-- server online?
    char p_unk_char2;                // + 8241 <-- gethostbyaddr?
    char p_unk_char3;                // + 8242
    int p_server_time_year;          // + 8244
    int p_server_time_month;         // + 8248
    int p_server_time_day;           // + 8252
    int p_server_time_hour;          // + 8256
    int p_server_time_min;           // + 8260
    int p_server_time_sec;           // + 8264
    int p_unk_dword1;                // + 8268
    int p_unk_dword2;                // + 8272
    int p_unk_dword3;                // + 8276
    int *p_array_connectors;         // + 8280
    int p_unk_dword5;                // + 8284
    MYSQL mysql_user_db;             // + 8288
    MYSQL mysql_data_db;             // + 8832
    MYSQL mysql_auth_db;             // + 9376
    bool *p_connecting_connector;    // + 9920
    bool p_connecting_messenger;     // + 9924
public:
    CServer(void);
    ~CServer();

    char *GetServerPath(void);
    bool LoadSettingFile(void);
    bool ConnectDB(void);
    void DisconnectDB(void);
    bool InitGame(void);
    int GetMaxPlayers(void);
    int InitSocket(void);
    int SetSendbuf(long fd);
    struct in_addr GetBindAddr(void);
    void Nonblock(int fd);
    void ServerSleep(timeval *timeout);
    int NewDescriptor(int fd);
    void CloseSocket(CDescriptor *m_desc);
    void SendOutput(CDescriptor *m_desc);
    bool DisConnectLogedIn(CDescriptor *m_to_disconnect);
    void SetServerTime(void);
    bool MakeConnectorClient(int m_num);
    void SendConnectorHeader(long m_num);
    bool MakeMessengerClient(void);
    void SendMessengerHeader(void);
    static void *ConnectorConnect(void *pt_num);
    static void *MessengerConnect(void *pt);
    void ProcConnector(CNetMsg &m_msg);
    void ProcMessenger(CNetMsg &m_msg);

    void Run(void);
    void Close(void);
    void SendConnectorReqPlayer(void);
};

extern CServer gserver;
extern struct in_addr bind_addr;
extern int last_desc;

#endif
