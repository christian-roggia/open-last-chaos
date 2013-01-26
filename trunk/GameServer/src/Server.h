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

#include "Battle.h"
#include "Cmd.h"
#include "CmdMsg.h"
#include "ConfigFile.h"
#include "doFunc.h"
#include "DBCmd.h"
#include "DBThread.h"
#include "Descriptor.h"
#include "Exp.h"
#include "Guild.h"
#include "Item.h"
#include "NetMsg.h"
#include "NPCProto.h"
#include "Party.h"
#include "Option.h"
#include "Quest.h"
#include "Room.h"
#include "Skill.h"
#include "SSkill.h"
#include "Utils.h"
#include "Zone.h"

#include <sys/time.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
#include <arpa/inet.h>
#include <mysql/mysql.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/time.h>

class CServer;

extern struct in_addr bind_addr; // bind_addr_618 -> bind_addr.618
extern CServer gserver; // 0x080FA480
extern CCmdList gcmdlist;
extern struct timeval a_NullTime;
extern char g_buf[0x2000];
extern char g_buf2[0x2000];
extern char g_buf3[0x2000];
extern char buf[1000]; // buf_570 -> buf.570
extern int last_desc; // last_desc_637 -> last_desc.637

class CServer {
public:
    int Unk0; // MainSocket
    CDescriptor *Unk4;
    long Unk8;
    CDescriptor *Unk12; // MessengerClientDesc
    CDescriptor *Unk16; // BillingClientDesc
    CDescriptor *Unk20; // HelperClientDesc
    CPCList Unk24;
    fd_set Unk32804;
    fd_set Unk33828;
    fd_set Unk34852;
    fd_set Unk35876;
    char *Unk36900;
    CConfigFile Unk36904;
    int Unk41004; // Number
    int Unk41008; // SubNumber
    char Unk41012[32]; // ServerIP - check length
    int Unk41044; // ServerPort
    int Unk41048; // MaxPlayers
    char Unk41052;
    char Unk41053;
    char Unk41054;
    int Unk41056; // Year
    int Unk41060; // Month
    int Unk41064; // Day
    int Unk41068; // Hour
    int Unk41072; // Minute
    int Unk41076; // Second
    int Unk41080;
    int Unk41084;
    int Unk41088;
    int Unk41092; // MinClientVersion
    int Unk41096; // MaxClientVersion
    bool Unk41100; // AllowExternalIP
    struct timeval Unk41104;
    int Unk41112; // CHECK INT
    char Unk41116;
    CDescriptor *Unk41120;
    CDescriptor *Unk41124;
    CDescriptor *Unk41128[20];
    int Unk41248;
    long long Unk41252;
    int Unk41260;
    int Unk41264;
    int Unk41268;
    MYSQL Unk41272; // CharDB
    MYSQL Unk41816; // DataDB
    CItemList Unk41208;
    CDBThread Unk42360;
    bool Unk452128; // isConnetingBillingClient
    char Unk452129;
    char Unk452130;
    CNetMsg Unk452132;
    CNetMsg Unk452152;
    CNetMsg Unk452172;
    int Unk452192; // ZonesCount
    CZone *Unk452196; // Zones
    CNPCProtoList Unk452200;
    CMagicProtoList Unk452212;
    CSkillProtoList Unk452220;
    CQuestProtoList Unk452228;
    COptionProtoList Unk452236;
    CSSkillProtoList Unk452244;
    CGuildList Unk452252;
    bool Unk452260;
	bool Unk452261;
    bool Unk452262; // LattoStatus
    bool Unk452263; // NewYearStatus
    bool Unk452264; // ValentinesDayStatus
public:
    CServer(void);
    ~CServer();

    static char *GetServerPath(void);
    bool LoadSettingFile(void);
    bool LoadSettings(void);
    bool ConnectDB(void);
    void DisconnectDB(bool a2);
    bool CreateDBThread(void);
    bool InitGame(void);
    static int GetMaxPlayers(void);
    int InitSocket(void);
    static int SetSendbuf(int a2);
    struct in_addr GetBindAddr(void);
    static void Nonblock(int a2);
    bool MakeBillingClient(void);
    void SetHeaders(void);
    void SendBillingHeader(void);
    static void ServerSleep(timeval *a2);
    int NewDescriptor(int fd);
    void CloseSocket(CDescriptor *a2);
    void SendOutput(CDescriptor *a2);
    void SendOutput(CCharacter *a2);
    bool DisConnectLogedIn(CDescriptor *a2);
    void CommandInterpreter(CDescriptor *a2, CNetMsg &a3);
    CDescriptor *FindConnectIdName(char *s2, CDescriptor *a3);
    void CharPrePlay(CDescriptor *a2);
    static void BillingConnect(void *a1);
    void DecreaseTimeForPC(CPC *a2);
    long long GetServerTime(void);
    bool MakeMessengerClient(void);
    bool MakeHelperClient(void);
    void SendMessengerHeader(void);
    void SendHelperHeader(void);
    int FindZone(int a2);

    void Run(void);
    void Close(void);
    void HeartBeat(void);
    static void MessengerConnect(void *a1);
    static void HelperConnect(void *a1);

    void ProcessBilling(CNetMsg &a2);
    void ProcessHelperMessage(CNetMsg &a2);
    void ProcessMessengerMessage(CNetMsg &a2);
};

int InitFDSET(int a1, CDescriptor *a2, fd_set *a3, fd_set *a4, fd_set *a5);

#endif // SERVER_H
