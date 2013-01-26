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

#ifndef SERVER_H
#define SERVER_H

#include "BillingClient.h"
#include "CmdMsg.h"
#include "ConfigFile.h"
#include "DBCmd.h"
#include "Descriptor.h"
#include "Log.h"
#include "ProcConnMsg.h"
#include "Random.h"
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

class CBillingClient;
class CDescriptor;
class CUserList;

class CServer {
public:
        int ServerSocket;                                       // +0
        CDescriptor *ClientDescriptors;                         // +4
        fd_set ReadFDS;                                         // +8
        fd_set WriteFDS;                                        // +1032
        fd_set ExceptFDS;                                       // +2056
        int32_t p_unk_array4[256];                              // +3080
        char *ServerPath;                                       // +4104
        CConfigFile Configs;                                    // +4108
        CBillingClient BillingClient;                           // +8208
        int Number, MaxSubServer, MaxPlayers;                   // +8220, +8224, +8228
        bool Shutdowned, WriteShutDown, DoNotUseGetHostByAddr;  // +8232, +8233, +8234
        int SYear, SMonth, SDay, SHour, SMin, SSec;             // +8236, +8240, +8244, +8248, +8252, +8256
        int Unk1, ConnectCount, ConnectMax, HeartBeats;         // +8260, +8264, +8268, +8272
        MYSQL UserSQL, AuthSQL;                                 // +8276, +8820
        CUserList *Users;                                       // +9364
public:
        CServer(void);
        ~CServer(void);

        char *GetServerPath(void);
        bool LoadSettingFile(void);
        bool ConnectDB(void);
        bool InitGame(void);
        void InitUserData(void);
        int GetMaxPlayers(void);
        int InitSocket(void);
        int SetSendbuf(int fd);
        struct in_addr GetBindAddr(void);
        void Nonblock(int fd);
        void ServerSleep(timeval *timeout);
        int NewDescriptor(int fd);
        void CloseSocket(CDescriptor *m_desc);
        void SendOutput(CDescriptor *m_desc);
        bool DisConnectLogedIn(CDescriptor *m_to_disconnect);
        void CommandInterpreter(CDescriptor *m_desc, CNetMsg &m_msg);
        long long GetServerTime(void);
        int CheckPlayers(void);
        void SavePlayersCount(void);
        void ProcessLogout(CUser *m_user);

        void Run(void);
        void Close(void);
        void HeartBeat(void);
};

extern CServer gserver;
extern struct in_addr bind_addr;
extern int last_desc;

/********************
** TODO LoginServer:
** Nonblock ------> Varable name
** InitSocket ----> Add struct linger
**               -> sin_addr   = this->GetBindAddr()
** GetServerPath -> Check function
** SetServerTime -> Variables name
********************/

#endif
