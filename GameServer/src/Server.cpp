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

/**********************************************************************
    TODO AS LAST
    void CServer::DecreaseTimeForPC(CPC *a2) -> FUCKING JUMP
**********************************************************************/

#include "Server.h"

struct in_addr bind_addr;
CServer gserver;
CCmdList gcmdlist;
struct timeval a_NullTime;
char g_buf[0x2000];
char g_buf2[0x2000];
char g_buf3[0x2000];
char buf[1000];
int last_desc = 0;

CServer::CServer(void)
{
    this->Unk0  = -1;
    this->Unk4  = 0;
    this->Unk8  = 0;
    this->Unk16 = 0;
    this->Unk12 = 0;
    this->Unk20 = 0;
    FD_ZERO(&this->Unk32804);
    FD_ZERO(&this->Unk33828);
    FD_ZERO(&this->Unk34852);
    FD_ZERO(&this->Unk35876);
    this->Unk36900 = this->GetServerPath();
    this->Unk41004 = -1;
    this->Unk41008 = -1;
    this->Unk41048 = 0;
    this->Unk41052 = 0;
    this->Unk41053 = 1;
    this->Unk41054 = 0;
    this->Unk41080 = -1;
    this->Unk41084 = -1;
    this->Unk41088 = -1;
    this->Unk41116 = 0;
    this->Unk41120 = 0;
    this->Unk41124 = 0;
    memset(this->Unk41128, 0, 80);
    this->Unk41248 = 0;
    this->Unk41252 = this->GetServerTime();
    this->Unk41260 = 0;
    this->Unk41264 = 0;
    this->Unk41268 = 0;
    mysql_init(&this->Unk41272);
    mysql_init(&this->Unk41816);
    this->Unk452128 = 0;
    this->Unk452129 = 0;
    this->Unk452192 = 0;
    this->Unk452196 = 0;
    this->Unk41092  = 0;
    this->Unk41096  = 0;
    this->Unk452260 = 0;
    this->Unk452261 = 0;
    this->Unk452262 = 0;
    this->Unk452263 = 0;
    this->Unk452264 = 0;
}

CServer::~CServer()
{
    if(this->Unk452196 && this->Unk452196)
        delete [] this->Unk452196; // CHECK -> ALLOCATED IN THE HEAP!

    this->Unk452196 = 0;
    this->Unk452192 = 0;

    if(this->Unk36900 && this->Unk36900)
        delete this->Unk36900;

    this->Unk36900 = 0;
}

char *CServer::GetServerPath(void)
{
    char *v1; // ST34_4@1
    char src[512]; // [sp+20h] [bp-400h]@1

    getcwd(src, 512);
    strcat(src, "/");

    v1 = (char *)malloc(strlen(src) + 1);
    strcpy(v1, src);

    return v1;
}

bool CServer::LoadSettingFile(void)
{
    char v5[512]; // [sp+24h] [bp-400h]@1

    puts("Load setting file....");
    sprintf(v5, "%s%s", this->Unk36900, "data/newStobm.bin");

    if(!this->Unk36904.Load(v5, false))
        return false;

    this->Unk41004 = atoi(this->Unk36904.Find("Server", "Number"));
    this->Unk41008 = atoi(this->Unk36904.Find("Server", "SubNumber"));
    this->Unk41100 = strcmp(this->Unk36904.Find("Server", "AllowExternalIP"), "FALSE") ? false : true;

    return true;
}

bool CServer::LoadSettings(void)
{
    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Load settings....");
    g_gamelogbuffer.__ls(end);

    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Client Version Loading...");
    g_gamelogbuffer.__ls(end);

    CDBCmd v23;

    v23.Init(&this->Unk41816);
    v23.SetQuery("SELECT a_min, a_max FROM t_clientversion");

    if(!v23.Open() || !v23.MoveFirst() || !v23.GetRec("a_min", this->Unk41092) || !v23.GetRec("a_max", this->Unk41096))
        return false;

    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Item Loading...");
    g_gamelogbuffer.__ls(end);

    this->Unk41208.Load();

    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Skill Loading...");
    g_gamelogbuffer.__ls(end);

    if(this->Unk452212.Load())
        return false;

    if(this->Unk452220.Load())
        return false;

    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Npc Loading...");
    g_gamelogbuffer.__ls(end);

    if(this->Unk452200.Load())
        return false;

    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Quest Loading...");
    g_gamelogbuffer.__ls(end);

    if(this->Unk452228.Load())
        return false;

    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Option Loading...");
    g_gamelogbuffer.__ls(end);

    if(this->Unk452236.Load())
        return false;

    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Special Skill Loading...");
    g_gamelogbuffer.__ls(end);

    if(this->Unk452244.Load())
        return false;

    this->Unk452192 = atoi(this->Unk36904.Find("Zones", "Count"));

    if(!this->Unk452192)
        return false;

    this->Unk452196 = new CZone[this->Unk452192];

    for(int j = 0; j < this->Unk452192; ++j)
    {
        if(!this->Unk452196[j].LoadZone(j))
            return false;

        if(!this->Unk452196[j].LoadShop())
            return false;

        if(!this->Unk452196[j].LoadNPC())
            return false;
    }

    return true;
}

bool CServer::ConnectDB(void)
{
    if(!mysql_real_connect(&this->Unk41272, this->Unk36904.Find("Char DB", "IP"), this->Unk36904.Find("Char DB", "User"), this->Unk36904.Find("Char DB", "Password"), this->Unk36904.Find("Char DB", "DBName"), 0, 0, 0))
        return false;

    if(!mysql_real_connect(&this->Unk41816, this->Unk36904.Find("Data DB", "IP"), this->Unk36904.Find("Data DB", "User"), this->Unk36904.Find("Data DB", "Password"), this->Unk36904.Find("Data DB", "DBName"), 0, 0, 0))
        return false;

    return true;
}

void CServer::DisconnectDB(bool a2)
{
    if(a2)
        mysql_close(&this->Unk41272);
    else
        mysql_close(&this->Unk41816);
}

bool CServer::CreateDBThread(void)
{
    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("DB-Thread Initialized...");
    g_gamelogbuffer.__ls(end);

    return this->Unk42360.CreateThread();
}

bool CServer::InitGame(void)
{
    ServerSrandom(time(0));
    MakeMath();
    InitExp();

    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Finding player limit.");
    g_gamelogbuffer.__ls(end);

    this->Unk41048 = this->GetMaxPlayers();

    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Opening mother connection.");
    g_gamelogbuffer.__ls(end);

    this->Unk0 = this->InitSocket();

    if(!this->MakeMessengerClient() && this->Unk12)
    {
        this->Unk12->CloseSocket();

        if(this->Unk12)
            delete this->Unk12;

        this->Unk12 = 0;
    }

    if(!this->MakeBillingClient() && this->Unk16)
    {
        this->Unk16->CloseSocket();

        if(this->Unk16)
            delete this->Unk16;

        this->Unk16 = 0;
    }

    if(!this->MakeHelperClient() && this->Unk20)
    {
        this->Unk452252.Reset();
        this->Unk20->CloseSocket();

        if(this->Unk20)
            delete this->Unk20;

        this->Unk20 = 0;
    }

    this->SetHeaders();
    this->SendMessengerHeader();
    this->SendHelperHeader();
    this->SendBillingHeader();

    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Entering game loop.");
    g_gamelogbuffer.__ls(end);

    return true;
}

int CServer::GetMaxPlayers(void)
{
    struct rlimit rlimits; // [sp+30h] [bp-10h]@1
    const char *src; // [sp+38h] [bp-8h]@1
    int v26; // [sp+3Ch] [bp-4h]@1

    v26 = 0;
    src = "rlimit";

    if(getrlimit(7, &rlimits) < 0)
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("calling getrlimit");
        g_gamelogbuffer.__ls(end);

        exit(1);
    }

    rlimits.rlim_cur = rlimits.rlim_max;

    if(setrlimit(7, &rlimits) < 0)
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("calling setrlimit");
        g_gamelogbuffer.__ls(end);

        exit(1);
    }

    v26 = (rlimits.rlim_max == -1) ? 50005 : ((rlimits.rlim_max > 50000) ? 50005 : rlimits.rlim_max);
    v26 = (v26 > 50000) ? 50000 : v26 - 5;

    if(v26 <= 0)
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("Non-positive max player limit!    (Set at");
        g_gamelogbuffer.__ls(v26);
        g_gamelogbuffer.__ls("using");
        g_gamelogbuffer.__ls(src);
        g_gamelogbuffer.__ls(").");
        g_gamelogbuffer.__ls(end);

        exit(1);
    }

    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Setting player limit to");
    g_gamelogbuffer.__ls(v26);
    g_gamelogbuffer.__ls("using");
    g_gamelogbuffer.__ls(src);
    g_gamelogbuffer.__ls(".");
    g_gamelogbuffer.__ls(end);

    return v26;
}

int CServer::InitSocket(void)
{
    struct linger v11; // [sp+1Ch] [bp-30h]@7
    int optval; // [sp+34h] [bp-18h]@4
    struct sockaddr_in s; // [sp+38h] [bp-14h]@9
    int fd; // [sp+48h] [bp-4h]@1

    fd = socket(2, 1, 0);

    if(fd < 0)
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("Error creating socket");
        g_gamelogbuffer.__ls(end);

        exit(1);
    }

    optval = 1;

    if(setsockopt(fd, 1, 2, &optval, 4) < 0)
    {
        puts("SYSERR: setsockopt REUSEADDR");
        exit(1);
    }

    this->SetSendbuf(fd);

    v11.l_onoff = 0;
    v11.l_linger = 0;

    if(setsockopt(fd, 1, 13, &v11, sizeof(struct linger)) < 0)
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("setsockopt SO_LINGER");
        g_gamelogbuffer.__ls(end);
    }

    memset(&s, 0, 16);

    s.sin_family = 2;
    s.sin_port = htons(atoi(gserver.Unk36904.Find("Server", "Port")));
    s.sin_addr.s_addr = this->GetBindAddr().s_addr;

    if(bind(fd, (const struct sockaddr *)&s, 16) < 0)
    {
        puts("SYSERR: bind");
        close(fd);
        fclose(fopen(".shutdown", "w"));

        exit(1);
    }

    this->Nonblock(fd);
    listen(fd, 57);

    strcpy(this->Unk41012, this->Unk36904.Find("Server", "IP"));
    this->Unk41044 = atoi(this->Unk36904.Find("Server", "Port"));

    return fd;
}

int CServer::SetSendbuf(int a2)
{
    int optval = 12288; // [sp+24h] [bp-4h]@1

    if(setsockopt(a2, SOL_SOCKET, SO_SNDBUF, &optval, sizeof(optval)) >= 0) // 1, 7, 4
        return 0;

    g_gamelogbuffer.__ls(init("SYS_ERR"));
    g_gamelogbuffer.__ls("setsockopt SNDBUF");
    g_gamelogbuffer.__ls(end);

    return -1;
}

struct in_addr CServer::GetBindAddr(void)
{
    memset(&bind_addr, 0, 4);

    bind_addr.s_addr = inet_addr(this->Unk36904.Find("Server", "IP"));

    if(bind_addr.s_addr == htonl(0)) // CHECK
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

void CServer::Nonblock(int a2)
{
    if(fcntl(a2,  F_SETFL, fcntl(a2, F_GETFL, 0) | O_NONBLOCK) < 0)
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("Fatal error executing nonblock (CServer.cpp)");
        g_gamelogbuffer.__ls(end);

        exit(1);
    }
}

bool CServer::MakeBillingClient(void)
{
    struct sockaddr_in s; // [sp+18h] [bp-10h]@12

    if(this->Unk16 && this->Unk16->Unk361)
    {
        this->Unk16->CloseSocket();

        if(this->Unk16)
            delete this->Unk16;

        this->Unk16 = 0;
    }

    this->Unk16 = new CDescriptor();

    if((this->Unk16->Unk192 = socket(2, 1, 6)) < 0)
    {
        puts("SYSERR: Error opening network connection : Winsock error");
        return false;
    }

    if(this->Unk16->Unk192 <= 0)
        return false;

    memset(&s, 0, 16);
    s.sin_family = 2;
    s.sin_addr.s_addr = inet_addr(this->Unk36904.Find("Connector Server", "IP"));
    s.sin_port = htons(atoi(this->Unk36904.Find("Connector Server", "Port")));

    if(!connect(this->Unk16->Unk192, (const struct sockaddr *)&s, 16) >= 0)
    {
        puts("SYSERR: Cannot connect Connector Server!!!");
        return false;
    }

    this->Unk16->Unk320 = 0;
    this->Unk16->Unk352 = -1;
    this->Nonblock(this->Unk16->Unk192);
    this->SetSendbuf(this->Unk16->Unk192);

    return true;
}

void CServer::SetHeaders(void)
{
    int v3; // [sp+3Ch] [bp-8h]@1
    int *v4; // [sp+40h] [bp-4h]@1

    v4 = (int *)malloc(sizeof(int) * this->Unk452192);
    v3 = 0;

    for(int i = 0; i < this->Unk452192; ++i)
    {
        if(!this->Unk452196[i].Unk4)
            v4[v3++] = this->Unk452196[i].Unk0;
    }

    MsgrConnectMsg  (this->Unk452132, 600, this->Unk41004, this->Unk41008, v3, v4);
    ConnConnectMsg  (this->Unk452152, 600, this->Unk41004, this->Unk41008, v3, v4);
    HelperConnectMsg(this->Unk452172, 600, this->Unk41004, this->Unk41008, v3, v4);

    if(v4)
        delete v4;
}

void CServer::SendBillingHeader(void)
{
    if(this->Unk16 && !this->Unk16->Unk361)
    {
        if(this->Unk16)
            this->Unk16->WriteToOutput(this->Unk452152);

        if(this->Unk16->Unk192 >= 0 && this->Unk16->Unk280.GetNextPoint())
        {
            if(this->Unk16->ProcessOutput() < 0)
            {
                g_gamelogbuffer.__ls(init("SYS_ERR"));
                g_gamelogbuffer.__ls("Connector Disconnected...");
                g_gamelogbuffer.__ls(end);

                this->Unk16->Unk361 = true;
            }
        }
    }
}

void CServer::ServerSleep(timeval *a2)
{
    if(select(0, 0, 0, 0, a2) >= 0)
        return;

    if(errno != EINTR) // 4
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("Select sleep!!");
        g_gamelogbuffer.__ls(end);

        exit(1);
    }
}

int CServer::NewDescriptor(int fd)
{
    char *v8; // [sp+2Ch] [bp-20h]@6
    struct sockaddr addr; // [sp+30h] [bp-1Ch]@1
    CDescriptor *v10; // [sp+40h] [bp-Ch]@5
    socklen_t addr_len; // [sp+44h] [bp-8h]@1
    int v12; // [sp+48h] [bp-4h]@1

    addr_len = 16;
    v12 = accept(fd, &addr, &addr_len);

    if(v12 == -1)
        return -1;

    this->Nonblock(v12);

    if(this->SetSendbuf(v12) < 0)
    {
        close(v12);
        return 0;
    }

    v10 = new CDescriptor();

    if(!this->Unk41053 && (v8 = (char *)gethostbyaddr(&addr.sa_data[2], 4, 2)) != 0)
    {
        strncpy(v10->Unk196, v8, 30);
        v10->Unk196[30] = 0;
    }
    else
    {
        if(!this->Unk41053)
        {
            g_gamelogbuffer.__ls(init("SYS_ERR"));
            g_gamelogbuffer.__ls("gethostbyaddr");
            g_gamelogbuffer.__ls(end);
        }

        strncpy(v10->Unk196, inet_ntoa(*(struct in_addr *)&addr.sa_data[2]), 30);
        v10->Unk196[30] = 0;
    }

    v10->Unk192 = v12;
    v10->Unk320 = 0;
    v10->Unk324 = this->Unk41248;
    v10->Unk340 = 23;

    ++last_desc;

    if(last_desc == 100000000)
        last_desc = 1;

    v10->Unk352 = last_desc;

    if(this->Unk4)
        this->Unk4->Unk376 = v10;

    v10->Unk380 = this->Unk4;
    v10->Unk376 = 0;
    this->Unk4 = v10;

    return 0;
}

void CServer::CloseSocket(CDescriptor *a2)
{
    if(this->Unk41120 == a2)
    {
        this->Unk41120 = 0;
        this->Unk41116 = 0;
    }

    if(this->Unk41124)
        this->Unk41124 = 0;

    for(int i = 0; i <= 19; ++i)
    {
        if(this->Unk41128[i] == a2)
            this->Unk41128[i] = 0;
    }

    if((!a2->Unk340 || a2->Unk340 == 25) && a2->Unk372 && a2->Unk372->Unk2368)
    {
        CNetMsg v69;

        a2->Unk372->Unk2368->online(0);
        HelperGuildOnline(v69, a2->Unk372->Unk2368);
        a2->Unk372->Unk2368->SetPC(0);

        if(!gserver.Unk452130 && gserver.Unk20 && !gserver.Unk20->Unk361 && this->Unk20)
            this->Unk20->WriteToOutput(v69);
    }

    if(a2->Unk340 || !a2->Unk372)
    {
        if(a2->Unk348 != -1 && a2->Unk348 && a2->Unk340 != 17)
        {
            a2->Unk340 = 17;
            a2->Unk348 = 2;

            g_gamelogbuffer.__ls(init("DISCONNECT", "No Play", a2->Unk4));
            g_gamelogbuffer.__ls(a2->Unk340);
            g_gamelogbuffer.__ls(delim);
            g_gamelogbuffer.__ls(a2->Unk120);
            g_gamelogbuffer.__ls(delim);
            g_gamelogbuffer.__ls(a2->Unk117);
            g_gamelogbuffer.__ls(end);

            a2->Unk120 = 1;
            a2->Unk117 = 1;
            a2->Unk360 = 0;

            this->Unk42360.AddToQ(a2);

            return;
        }

        if(a2->Unk340 != 1 && a2->Unk340 != 17)
        {
            g_gamelogbuffer.__ls(init("SYS_ERR", a2->Unk4));
            g_gamelogbuffer.__ls(a2->Unk340);
            g_gamelogbuffer.__ls(delim);
            g_gamelogbuffer.__ls(a2->Unk120);
            g_gamelogbuffer.__ls(delim);
            g_gamelogbuffer.__ls(a2->Unk117);
            g_gamelogbuffer.__ls(end);
        }
    }
    else
    {
        if(this->Unk24.Playing(a2->Unk372))
        {
            CNetMsg v69;

            a2->Unk372->Unk472 = 0;
            this->Unk24.Remove(a2->Unk372);

            if(a2->Unk372->Unk2372)
            {
                CPC *v68 = gserver.Unk24.Find(a2->Unk372->Unk2372);

                if(v68)
                {
                    if(v68->Unk2372 == a2->Unk372->Unk4)
                    {
                        v68->Unk2372 = 0;
                        GuildRegistCancelMsg(v69, 1);
                    }
                }
            }

            DisappearMsg(v69, a2->Unk372);

            if(a2->Unk372->Unk416)
            {
                CRoom *v68 = a2->Unk372->Unk416;
                v68->SendToCell(v69, a2->Unk372, 0);
                v68->CharFromCell(a2->Unk372);
            }
            else
            {
                CArea *v68 = a2->Unk372->Unk412;

                if(v68)
                {
                    v68->SendToCell(v69, a2->Unk372, 0, 4);
                    v68->CharFromCell(a2->Unk372);
                }
                else
                {
                    g_gamelogbuffer.__ls(init("SYS_ERROR", a2->Unk372->Unk8, a2->Unk4));
                    g_gamelogbuffer.__ls("Playing But No Area!!! : ");
                    g_gamelogbuffer.__ls(end);
                }
            }

            if(!a2->Unk363 && a2->Unk372->Unk408->Unk40 > 1)
            {
                a2->Unk372->Unk408->SetDisableArea(a2->Unk372->Unk412->Unk8);
                a2->Unk372->Unk408 = 72 * gserver.FindZone(0) + gserver.Unk452196;
                a2->Unk372->Unk412 = a2->Unk372->Unk408->Unk36;
                a2->Unk372->Unk416 = 0;
                a2->Unk372->Unk120.Unk16 = a2->Unk372->Unk408->Unk52[0]->Unk0;
                a2->Unk372->Unk120.Unk12 = 0;

                int v68 = 10;

                do
                {
                    --v68;

                    if(v68 == -1)
                        break;

                    a2->Unk372->Unk120.Unk0 = GetRandom(a2->Unk372->Unk408->Unk52[0]->Unk4, a2->Unk372->Unk408->Unk52[0]->Unk12) / 2.0;
                    a2->Unk372->Unk120.Unk4 = GetRandom(a2->Unk372->Unk408->Unk52[0]->Unk8, a2->Unk372->Unk408->Unk52[0]->Unk16) / 2.0;
                }
                while(a2->Unk372->Unk412->GetAttr(a2->Unk372->Unk120.Unk16, a2->Unk372->Unk120.Unk0, a2->Unk372->Unk120.Unk4) == -1);
            }

            a2->Unk340 = 17;

            if(a2->Unk372->Unk1324)
            {
                CNetMsg v65;

                ExchangeReqMsg(v65, 2, 0, 0);
                do_Exchange(a2->Unk372, v65);
            }

            if(a2->Unk372->Unk1368)
            {
                CNetMsg v65;

                if(a2->Unk372->Unk1368->GetRequest() == a2->Unk372)
                    PartyMsg(v65, 2);
                else
                    PartyMsg(v65, 6);

                do_Party(a2->Unk372, v65);
            }

            if(a2->Unk372->Unk1328)
            {
                delete a2->Unk372->Unk1328;
                a2->Unk372->Unk1328 = 0;

                CNetMsg v65;

                PersonalShopChangeMsg(v65, a2->Unk372);

                if(a2->Unk372->Unk412)
                    a2->Unk372->Unk412->SendToCell(v65, a2->Unk372, 0, 4);
            }

            g_gamelogbuffer.__ls(init("HAVE_MONEY", a2->Unk372->Unk8, a2->Unk4));
            g_gamelogbuffer.__ls(a2->Unk372->Unk1280 ? a2->Unk372->Unk1280->Count() : 0);
            g_gamelogbuffer.__ls(end);

            for(int i = 0; i <= 9; ++i)
            {
                if(a2->Unk372->Unk1284[i])
                {
                    CItem *v68 = a2->Unk372->Unk1284[i];

                    g_gamelogbuffer.__ls(init("WEAR ITEM", a2->Unk372->Unk8, a2->Unk4));
                    g_gamelogbuffer.__ls(v68->Unk28);
                    g_gamelogbuffer.__ls(delim);
                    g_gamelogbuffer.__ls(v68->Unk20->Unk12);
                    g_gamelogbuffer.__ls(delim);
                    g_gamelogbuffer.__ls(v68->Unk44);
                    g_gamelogbuffer.__ls(delim);
                    g_gamelogbuffer.__ls(v68->Unk36);
                    g_gamelogbuffer.__ls(delim);
                    g_gamelogbuffer.__ls(v68->Unk40);
                    g_gamelogbuffer.__ls(delim);
                    g_gamelogbuffer.__ls(v68->Unk168);

                    for(int j = 0; j < v68->Unk168; ++j)
                    {
                        if(v68->Unk68[j].Unk0)
                        {
                            g_gamelogbuffer.__ls(delim);
                            g_gamelogbuffer.__ls(v68->Unk68[j].Unk4);
                            g_gamelogbuffer.__ls(delim);
                            g_gamelogbuffer.__ls(v68->Unk68[j].Unk8);
                        }
                    }

                    g_gamelogbuffer.__ls(end);
                }
            }

            g_gamelogbuffer.__ls(init("DISCONNECT", a2->Unk372->Unk8, a2->Unk4));
            g_gamelogbuffer.__ls(end);

            a2->Unk120 = 1;
            a2->Unk117 = 1;
            a2->Unk360 = 0;

            this->Unk42360.AddToQ(a2);

            return;
        }

        g_gamelogbuffer.__ls(init("SYS_ERR", a2->Unk372->Unk8, a2->Unk4));
        g_gamelogbuffer.__ls("Cannot save DATA : ");
        g_gamelogbuffer.__ls(a2->Unk340);
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls(a2->Unk120);
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls(a2->Unk117);
        g_gamelogbuffer.__ls(end);
    }

    if(a2->Unk340 != 17 || a2->Unk360 || !a2->Unk117 && a2->Unk120 <= 0)
    {
        if(!a2->Unk362)
        {
            if(a2->Unk360)
            {
                if(!gserver.Unk452128 && gserver.Unk16 && !gserver.Unk16->Unk361)
                {
                    if(a2->Unk372 && a2->Unk372->Unk408 && a2->Unk372->Unk408->Unk4)
                    {
                        CNetMsg v65;

                        ConnPlayingMsg(v65, a2, 1);

                        if(this->Unk16)
                            this->Unk16->WriteToOutput(v65);
                    }
                    else
                    {
                        if(a2->Unk4 && a2->Unk348 != -1)
                        {
                            CNetMsg v65;

                            ConnLogoutMsg(v65, a2->Unk4);

                            if(this->Unk16)
                                this->Unk16->WriteToOutput(v65);
                        }
                    }
                }

                if(a2->Unk376)
                {
                    a2->Unk376->Unk380 = a2->Unk380;

                    if(a2->Unk380)
                        a2->Unk380->Unk376 = a2->Unk376;
                }
                else
                {
                    this->Unk4 = a2->Unk380;

                    if(a2->Unk380)
                        a2->Unk380->Unk376 = 0;
                }

                a2->Unk376 = 0;
                a2->Unk380 = 0;

                a2->CloseSocket();

                if(a2)
                    delete a2;
            }
        }
    }
}

void CServer::SendOutput(CDescriptor *a2)
{
    if(a2 && !a2->Unk361 && a2->Unk280.GetNextPoint() && FD_ISSET(a2->Unk192, &this->Unk33828)) // _bittest
    {
        if(a2->ProcessOutput() < 0)
            a2->Unk361 = true;
    }
}

void CServer::SendOutput(CCharacter *a2)
{
    if(a2->Unk0 == 0)
        this->SendOutput(((CPC *)a2)->Unk768);
}

bool CServer::DisConnectLogedIn(CDescriptor *a2)
{
    CDescriptor *v6; // [sp+20h] [bp-8h]@1
    CDescriptor *v7; // [sp+24h] [bp-4h]@2

    v6 = this->Unk4;

    do
    {
        v7 = v6;

        if(!v6)
            return false;

        v6 = v7->Unk380;
    }
    while(v7 == a2 || strcasecmp(v7->Unk4, a2->Unk4) || v7->Unk340 == 23);

    if(v7->Unk340 || !this->Unk24.Playing(v7->Unk372))
    {
        if(v7->Unk340 != 17)
            v7->Unk340 = 1;
    }
    else
    {
        g_gamelogbuffer.__ls(init("DISCONNECT", v7->Unk372->Unk8, v7->Unk4));
        g_gamelogbuffer.__ls("Duplication");
        g_gamelogbuffer.__ls(end);

        this->CloseSocket(v7);
    }

    return true;
}

void CServer::CommandInterpreter(CDescriptor *a2, CNetMsg &a3)
{
    int v11; // [sp+20h] [bp-8h]@2
    CPC *v12; // [sp+24h] [bp-4h]@1

    v12 = a2->Unk372;

    if(!v12)
        return;

    v11 = gcmdlist.Find(v12, a3.MsgType);
    if(v11 < 0)
    {
        g_gamelogbuffer.__ls(init("SYS_WARN", a2->Unk372->Unk8, a2->Unk4));
        g_gamelogbuffer.__ls("Invalid command");
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls(a3.MsgType);
        g_gamelogbuffer.__ls(end);

        return;
    }

    if(this->Unk41248 - a2->Unk324 > 9)
    {
        if(a2->Unk328 > 5)
        {
            if(a2->Unk372)
                g_gamelogbuffer.__ls(init("HACK COMMAND", a2->Unk372->Unk8, a2->Unk4));
            else
                g_gamelogbuffer.__ls(init("HACK COMMAND", a2->Unk4));

            g_gamelogbuffer.__ls(a2->Unk328);
            g_gamelogbuffer.__ls(end);
        }

        a2->Unk324 = this->Unk41248;
        a2->Unk328 = 0;
    }

    ++a2->Unk328;
    gcmdlist.Run(v11, v12, a3);
}

CDescriptor *CServer::FindConnectIdName(char *s2, CDescriptor *a3)
{
    CDescriptor *v4; // [sp+10h] [bp-8h]@2
    CDescriptor *v5; // [sp+10h] [bp-8h]@9
    CDescriptor *v6; // [sp+14h] [bp-4h]@3
    CDescriptor *v7; // [sp+14h] [bp-4h]@10

    if(a3)
    {
        v5 = this->Unk4;

        while(1)
        {
            v7 = v5;

            if(!v5)
                break;

            v5 = v5->Unk380;

            if(v7 != a3 && v7->Unk340 != 1  && v7->Unk340 != 17 && !v7->Unk361 && !strcasecmp(v7->Unk4, s2))
                return v7;
        }
    }
    else
    {
        v4 = this->Unk4;

        while(1)
        {
            v6 = v4;

            if(!v4)
                break;

            v4 = v4->Unk380;

            if(!v6->Unk361 && !strcasecmp(v6->Unk4, s2))
                return v6;
        }
    }

    return 0;
}

void CServer::CharPrePlay(CDescriptor *a2)
{
    CItem *v12; // [sp+38h] [bp-38h]@38
    int v13; // [sp+3Ch] [bp-34h]@37
    int v14; // [sp+40h] [bp-30h]@37
    CGuildMember *v15; // [sp+44h] [bp-2Ch]@21
    int v17; // [sp+4Ch] [bp-24h]@11
    int v18; // [sp+50h] [bp-20h]@9
    int i; // [sp+54h] [bp-1Ch]@4
    CArea *v20; // [sp+58h] [bp-18h]@4

    a2->Unk372->Unk472 = 1;
    a2->Unk372->ResetPlayerState(-1);
    a2->Unk372->Unk2372 = 0;

    CNetMsg v21;

    if(a2->Unk372->Unk76 <= 0)
    {
        a2->Unk372->Unk76 = a2->Unk372->Unk764 / 2;
        if(a2->Unk372->Unk80 < a2->Unk372->Unk766 / 2)
            a2->Unk372->Unk80 = a2->Unk372->Unk766 / 2;
    }

    v20 = a2->Unk372->Unk412;
    for(i = 0; i <= 9; ++i)
    {
        if(a2->Unk372->Unk1900.Unk0[i] && a2->Unk372->Unk1900.Unk0[i]->Unk0->Unk4 == 10 && a2->Unk372->Unk1900.Unk40[i]) // FUCKING CHECK
        {
            v18 = gserver.FindZone(6);
            if(v18 == -1)
            {
                a2->Unk361 = 1;
                return;
            }

            a2->Unk372->Unk408 = 72 * v18 + gserver.Unk452196;
            v17 = a2->Unk372->Unk408->SetEnableArea();
            if(v17 == -1)
            {
                a2->Unk361 = 1;
                return;
            }

            a2->Unk372->Unk412 = &a2->Unk372->Unk408->Unk36[v17]; // CHECK THIS <----------------------------------------------------------------
            v20 = a2->Unk372->Unk412;
            a2->Unk372->Unk120.Unk16 = a2->Unk372->Unk408->Unk52[0]->Unk0;
            a2->Unk372->Unk120.Unk12 = 0;
            a2->Unk372->Unk120.Unk0 = a2->Unk372->Unk408->Unk52[0]->Unk4 / 2;
            a2->Unk372->Unk120.Unk4 = a2->Unk372->Unk408->Unk52[0]->Unk8 / 2;

            break;
        }
    }

    this->Unk24.Add(a2->Unk372);
    v20->PointToCellNum(a2->Unk372->Unk120.Unk0, a2->Unk372->Unk120.Unk4, &v17, &v18);
    v20->CharToCell(a2->Unk372, a2->Unk372->Unk120.Unk16, v17, v18);
    AtMsg(v21, a2->Unk372);

    if(a2)
        a2->WriteToOutput(v21);

    a2->Unk372->SendStatus();
    EnvTimeMsg(v21);

    if(a2)
        a2->WriteToOutput(v21);

    if(a2->Unk372->Unk2368)
        a2->Unk372->Unk2368 = 0;

    v15 = this->Unk452252.findmember(a2->Unk372->Unk4);
    if(v15)
    {
        if(a2->Unk372->Unk2368)
        {
            a2->Unk372->Unk2368 = 0;
            a2->Unk372->Unk2368 = v15;
        }
        else
        {
            a2->Unk372->Unk2368 = v15;

            v15->online(1);
            v15->SetPC(a2->Unk372);

            HelperGuildOnline(v21, v15);

            if(!gserver.Unk452130 && gserver.Unk20 && !gserver.Unk20->Unk361 && this->Unk20)
                this->Unk20->WriteToOutput(v21);
        }

        GuildInfoMsg(v21, a2->Unk372);

        if(a2)
            a2->WriteToOutput(v21);

        GuildListMsg(v21, a2->Unk372, 1);

        if(a2)
            a2->WriteToOutput(v21);

        GuildListMsg(v21, a2->Unk372, 0);

        if(a2)
            a2->WriteToOutput(v21);
    }

    StatPointRemainMsg(v21, a2->Unk372);

    if(a2)
        a2->WriteToOutput(v21);

    if(a2->Unk372->Unk968.FindItem(&v14, &v13, 507, 0, 0))
    {
        v12 = a2->Unk372->Unk968.GetItem(v14, v13);
        if(v12)
        {
            a2->Unk372->Unk968.Remove(v12, 0, 1);
            if(!a2->Unk372->Unk792.AddItem(v12, a2->Unk372, 0, 0, -1, -1))
            {
                v12 = a2->Unk372->Unk412->DropItem(v12, a2->Unk372);
                if(v12)
                {
                    CNetMsg v11;

                    ItemDropMsg(v11, a2->Unk372, v12);
                    a2->Unk372->Unk412->SendToCell(v11, a2->Unk372, 1, 4);
                    v12->Unk216 = a2->Unk372->Unk4;

                    if(a2->Unk372->Unk768)
                        a2->Unk372->Unk768->WriteToOutput(v11);
                }
            }
        }
    }

    a2->Unk372->SendInventory(0);
    QuestPCListMsg(v21, a2->Unk372);

    if(a2)
        a2->WriteToOutput(v21);

    a2->Unk372->Unk1900.CheckComplete(a2->Unk372);
    SkillListMsg(v21, a2->Unk372);

    if(a2)
        a2->WriteToOutput(v21);

    SSkillListMsg(v21, a2->Unk372);

    if(a2)
        a2->WriteToOutput(v21);

    a2->Unk372->SendQuickSlot();
    MemPosListMsg(v21, a2->Unk372);

    if(a2)
        a2->WriteToOutput(v21);

    AssistListMsg(v21, a2->Unk372);

    if(a2)
        a2->WriteToOutput(v21);

    AppearMsg(v21, a2->Unk372, 1);
    v20->SendToCell(v21, a2->Unk372, 0, 4);
    v20->SendCellInfo(a2->Unk372);
    EffectEtcMsg(v21, a2->Unk372, 1);
    v20->SendToCell(v21, a2->Unk372, 1, 4);

    g_gamelogbuffer.__ls(init("JOIN", a2->Unk372->Unk8, a2->Unk4));
    g_gamelogbuffer.__ls(a2->Unk372->Unk408->Unk0);
    g_gamelogbuffer.__ls(delim);
    g_gamelogbuffer.__ls(a2->Unk196);
    g_gamelogbuffer.__ls(end);

    a2->Unk372->Unk772 = 6000;
    a2->Unk372->Unk780 = 0;
    a2->Unk372->Unk776 = 0;
    a2->SetHackCheckPulse();
    a2->Unk340 = 0;
}

void CServer::BillingConnect(void *a1)
{
    (*((CServer *)a1)).Unk452128 = true;

    while(!(*((CServer *)a1)).MakeBillingClient())
    {
        if((*((CServer *)a1)).Unk16)
            (*((CServer *)a1)).Unk16->Unk361 = true;

        sleep(2);
    }

    (*((CServer *)a1)).SendBillingHeader();
    (*((CServer *)a1)).Unk452128 = false;

    pthread_exit(0);
}

void CServer::DecreaseTimeForPC(CPC *a2)
{
    int v3; // eax@58
    CZone *v4; // eax@61
    CRaChar *src; // [sp+30h] [bp-20h]@6
    CRaChar *v7; // [sp+34h] [bp-1Ch]@7
    char v8; // [sp+3Bh] [bp-15h]@6

    --a2->Unk772;
    if(a2->IsSetPlayerState(16))
    {
        if(a2->Unk1864 <= 0)
        {
            a2->ResetPlayerState(24);
            a2->Unk1864 = 0;
            CNetMsg v9;
            ActionMsg(v9, a2, 0, 23);
            a2->Unk412->SendToCell(v9, a2, 1, 4);
        }
        else
        {
            --a2->Unk1864;
        }
    }

    if(a2->IsSetPlayerState(32))
    {
        v8 = 0;
        src = a2->Unk1880;

        while(1)
        {
            v7 = src;

            if(!src)
                break;

            src = v7->Unk12;

            if(v7->Unk8)
            {
                --v7->Unk4;
                if(v7->Unk4 > 0)
                {
                    if(v7->Unk4 == 50)
                    {
                        v8 = 1;
                        CNetMsg v9;

                        RightAttackMsg(v9, v7->Unk0, 1);

                        if(a2->Unk768)
                            a2->Unk768->WriteToOutput(v9);

                        if(v7->Unk0->Unk768)
                            v7->Unk0->Unk768->WriteToOutput(v9);
                    }
                    else
                    {
                        v8 = 1;
                    }
                }
                else
                {
                    DelRaList(v7->Unk0, 0);
                }
            }
        }

        if(!v8)
            a2->ResetPlayerState(32);
    }

    if(a2->IsSetPlayerState(64))
    {
        if(a2->Unk2388 != -1)
        {
            --a2->Unk2384;

            if(a2->Unk2384 <= 0)
            {
                a2->Unk2384 = 0;
                a2->Unk2388 = -1;
                a2->ResetPlayerState(64);

                CNetMsg v9;

                ChangeStopMsg(v9, a2);
                a2->Unk412->SendToCell(v9, a2, 1, 4);
            }
        }
    }

    if(a2->Unk1860)
    {
        if(a2->Unk412)
        {
            --a2->Unk1860;

            if(a2->Unk1860 <= 0)
            {
                if(a2->Unk1852 < 0)
                {
                    ++a2->Unk1852;

                    CNetMsg v9;

                    CharStatusMsg(v9, a2, 0);
                    a2->Unk412->SendToCell(v9, a2, 0, 4);
                    a2->Unk473 = 1;
                }

                if(a2->Unk1852 >= 0)
                    a2->Unk1860 = 0;
                else
                    a2->Unk1860 = 36000;
            }
        }
    }

    if(a2->Unk424 && (a2->Unk76 <= 0 || a2->Unk424->Unk8 == 2 && this->Unk41248 - a2->Unk424->Unk12 > a2->Unk424->Unk0->Unk64 + a2->Unk424->Unk0->Unk60 + a2->Unk424->Unk0->Unk56)) // CHECK || + &&
    {
        a2->Unk424->Cancel();
        a2->Unk424 = 0;
    }

    a2->Unk148.DecreaseTime();

    if(a2->Unk76 > 0 && this->Unk41248 - a2->Unk116 > 29)
    {
        a2->RecoverPC();
        a2->Unk116 = this->Unk41248;
    }

    if(a2->Unk1884 > 0)
    {
        if(a2->Unk76 > 0)
        {
            --a2->Unk1884;
            if(!(a2->Unk1884 % 10))
            {
                a2->Unk76 += a2->Unk1888;

                if(a2->Unk76 > a2->Unk78)
                    a2->Unk76 = a2->Unk78;

                a2->Unk473 = 1;
            }
        }
        else
        {
            a2->Unk1884 = 0;
        }
    }

    if(a2->Unk1892 > 0)
    {
        if(a2->Unk76 > 0)
        {
            --a2->Unk1892;
            if(!(a2->Unk1892 % 10))
            {
                a2->Unk80 += a2->Unk1896;

                if(a2->Unk80 > a2->Unk82)
                    a2->Unk80 = a2->Unk82;

                a2->Unk473 = 1;
            }
        }
        else
        {
            a2->Unk1892 = 0;
        }
    }

    if(a2->Unk1356 > 0)
    {
        if(a2->Unk76 > 0)
        {
            --a2->Unk1356;
            if(a2->Unk1356 <= 0)
            {
                CNetMsg v9;

                WarpEndMsg(v9, a2);
                a2->Unk412->SendToCell(v9, a2, 1, 4);
                v3 = a2->Unk1360;

                if(v3)
                {
                    if(v3 == 1)
                        a2->GoMemPos(a2->Unk1364);
                }
                else
                {
                    int v7_1 = 0; // CHECK
                    v4 = a2->Unk408;

                    //if(v4->Unk0 <= 7)
                    //    JUMPOUT(__CS__, off_80D1560[v4->Unk0]);

                    int src_1 = 0; // CHECK

                    CNetMsg v5;

                    GoZoneMsg(v5, src_1, v7_1, "", 0);
                    do_GoZone(a2, v5);
                }

                a2->Unk1356 = 0;
                a2->Unk1360 = -1;
                a2->Unk1364 = -1;
                a2->ResetPlayerState(7);
            }
        }
        else
        {
            a2->Unk1356 = 0;
            a2->Unk1360 = -1;
            a2->Unk1364 = -1;
            a2->ResetPlayerState(7);
        }
    }
}

long long CServer::GetServerTime(void)
{
    struct tm *v1; // eax@1
    time_t timer; // [sp+30h] [bp-4h]@1

    timer = time(&timer);
    v1 = localtime(&timer);

    this->Unk41056 = v1->tm_year + 1900;
    this->Unk41060 = v1->tm_mon + 1;
    this->Unk41064 = v1->tm_mday;
    this->Unk41068 = v1->tm_hour;
    this->Unk41072 = v1->tm_min;
    this->Unk41076 = v1->tm_sec;

    return 60 * time(0);
}

bool CServer::MakeMessengerClient(void)
{
    struct sockaddr_in s; // [sp+18h] [bp-10h]@10

    if(this->Unk12 && this->Unk12->Unk361)
    {
        this->Unk12->CloseSocket();

        if(this->Unk12)
            delete this->Unk12;

        this->Unk12 = 0;
    }

    this->Unk12 = new CDescriptor();

    if((this->Unk12->Unk192 = socket(2, 1, 0)) < 0)
    {
        puts("SYSERR: Error opening network connection: socket error");
        return false;
    }

    memset(&s, 0, 16);
    s.sin_family = 2;
    s.sin_addr.s_addr = inet_addr(gserver.Unk36904.Find("Messenger Server", "IP"));
    s.sin_port = htons(atoi(gserver.Unk36904.Find("Messenger Server", "Port")));

    if(connect(this->Unk12->Unk192, (const struct sockaddr *)&s, 16) < 0)
    {
        puts("SYSERR: Cannot connect Messenger...");
        return false;
    }

    this->Unk12->Unk320 = 0;
    this->Unk12->Unk352 = -1;
    this->Nonblock(this->Unk12->Unk192);
    this->SetSendbuf(this->Unk12->Unk192);

    return true;
}

bool CServer::MakeHelperClient(void)
{
    struct sockaddr_in s; // [sp+18h] [bp-10h]@10

    if(this->Unk20 && this->Unk20->Unk361)
    {
        this->Unk452252.Reset();
        this->Unk20->CloseSocket();

        if(this->Unk20)
            delete this->Unk20;

        this->Unk20 = 0;
    }

    this->Unk20 = new CDescriptor();

    if((this->Unk20->Unk192 = socket(2, 1, 0)) < 0)
    {
        puts("SYSERR: Error opening network connection: socket error");
        return false;
    }

    memset(&s, 0, 16);
    s.sin_family = 2;
    s.sin_addr.s_addr = inet_addr(gserver.Unk36904.Find("Helper Server", "IP"));
    s.sin_port = htons(atoi(gserver.Unk36904.Find("Helper Server", "Port")));

    if(connect(this->Unk20->Unk192, (const struct sockaddr *)&s, 16) < 0)
    {
        puts("SYSERR: Cannot connect Helper...");
        return false;
    }

    this->Unk20->Unk320 = 0;
    this->Unk20->Unk352 = -1;
    this->Nonblock(this->Unk20->Unk192);
    this->SetSendbuf(this->Unk20->Unk192);

    return true;
}

void CServer::SendMessengerHeader(void)
{
    if(this->Unk12 && !this->Unk12->Unk361)
    {
        if(this->Unk12)
            this->Unk12->WriteToOutput(this->Unk452132);

        if(this->Unk12->Unk192 >= 0 && this->Unk12->Unk280.GetNextPoint())
        {
            if(this->Unk12->ProcessOutput() < 0)
            {
                g_gamelogbuffer.__ls(init("SYS_ERR"));
                g_gamelogbuffer.__ls("Messenger Disconnected...");
                g_gamelogbuffer.__ls(end);

                this->Unk12->Unk361 = true;
            }
        }
    }
}

void CServer::SendHelperHeader(void)
{
    if(this->Unk20 && !this->Unk20->Unk361)
    {
        if(this->Unk20)
            this->Unk20->WriteToOutput(this->Unk452172);

        if(this->Unk20->Unk192 >= 0 && this->Unk20->Unk280.GetNextPoint())
        {
            if(this->Unk20->ProcessOutput() < 0)
            {
                g_gamelogbuffer.__ls(init("SYS_ERR"));
                g_gamelogbuffer.__ls("Helper Disconnected...");
                g_gamelogbuffer.__ls(end);

                this->Unk20->Unk361 = true;
            }
        }
    }
}

int CServer::FindZone(int a2)
{
    for(int i = 0; i < this->Unk452192; ++i)
    {
        if(this->Unk452196[i].Unk0 == a2)
            return i;
    }

    return -1;
}
