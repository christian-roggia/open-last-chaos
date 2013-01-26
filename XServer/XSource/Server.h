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

#include "XConstants.h"
#include "XDESC.h"
#include "XMap.h"
#include "DBCmd.h"
#include "log.h"
#include "socket.h"
#include "Utils.h"

#include <vector>

#define MAX_ALLOWED_PLAYERS 4096

class CServer {
public:
    int MainSocket;
    XDESC *MainDesc;
    fd_set ReadFDS;
    fd_set WriteFDS;
    fd_set ExceptFDS;
    char *CurrentDirectory;
    bool ServerShutdowned;
    int MySQLNextPing;
    MYSQL MySQLDataDB;
    MYSQL MySQLAuthDB;
    std::vector<XMap *> xMaps;

public:
    CServer(void);
    ~CServer();

    char *GetServerPath(void);
    bool LoadSettingFile(void);
    void DisconnectDB(void);
    bool InitGame(void);
    void ServerSleep(timeval *timeout);
    int NewDescriptor(int fd);
    void CloseSocket(XDESC *m_desc);
    void SendOutput(XDESC *m_desc);

    void Run(void);
    void Close(void);
};

extern CServer gserver;

#endif
