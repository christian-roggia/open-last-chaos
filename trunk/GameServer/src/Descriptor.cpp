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

#include "Descriptor.h"

#include "PC.h"
#include "Server.h"

CDescriptor::CDescriptor(void)
{
    this->Unk0 = -1;
    *this->Unk4 = 0;
    *this->Unk66 = 0;
    this->Unk117 = 0;
    this->Unk120 = 0;
    this->Unk192 = 0;
    memset(this->Unk196, 0, 31);
    this->Unk300 = 0;
    this->Unk304 = 0;
    this->Unk308 = 0;
    this->Unk312 = 0;
    this->Unk316 = 0;
    this->Unk320 = 0;
    this->Unk328 = 0;
    this->Unk324 = 0;
    this->Unk332 = -1;
    this->Unk336 = -1;
    this->Unk340 = 0;
    this->Unk344 = 0;
    this->Unk348 = 0;
    this->Unk352 = 0;
    this->Unk356 = 0;
    this->Unk360 = 1;
    this->Unk361 = 0;
    this->Unk362 = 0;
    this->Unk363 = 0;
    this->Unk364 = 0;
    this->Unk372 = 0;
    this->Unk376 = 0;
    this->Unk380 = 0;
}

CDescriptor::~CDescriptor(void)
{
    if(this->Unk372 && this->Unk372)
        delete this->Unk372;

    *this->Unk66  = 0;
    this->Unk372 = 0;
}

void CDescriptor::CloseSocket(void)
{
    close(this->Unk192);
    this->FlushQueues();
}

void CDescriptor::FlushQueues(void)
{
    this->Unk228.Clear();
    this->Unk240.Clear();
    this->Unk280.Clear();
}

void CDescriptor::WriteToOutput(CNetMsg &a2)
{
    if(!a2.MsgType || this->Unk361 || this->Unk340 == 1)
        return;

    if(this->Unk280.Add(a2))
    {
        this->ProcessOutput();
        return;
    }

    if(this->Unk372)
    {
        g_gamelogbuffer.__ls(init("OUTPUT OVERFLOW", this->Unk372->Unk8, this->Unk4));
    }
    else
    {
        if(*this->Unk4)
            g_gamelogbuffer.__ls(init("OUTPUT OVERFLOW", this->Unk4));
        else
            g_gamelogbuffer.__ls(init("OUTPUT OVERFLOW"));
    }

    g_gamelogbuffer.__ls(end);
    this->Unk361 = true;
}

int CDescriptor::ProcessOutput(void)
{
    char *v3; // [sp+1Ch] [bp-8h]@1
    int v4; // [sp+20h] [bp-4h]@2

    while(1)
    {
        v3 = this->Unk280.GetNextPoint();

        if(!v3)
            return 0;

        v4 = this->WriteToDescriptor(this->Unk192, v3, this->Unk280.GetRemain());

        if(v4 < 0)
            break;

        if(!v4 || this->Unk280.Update(v4))
            return 0;
    }

    if(this->Unk372)
        this->Unk372->Unk472 = 0;

    this->Unk361 = true;

    return -1;
}

int CDescriptor::WriteToDescriptor(int a2, char const *a3, int a4)
{
    int v9; // [sp+24h] [bp-4h]@3

    if(!a4)
        return 0;

    v9 = write(a2, a3, a4);

    if(v9 > 0)
        return v9;

    if(!v9)
        return -1;

    if(errno == EAGAIN || errno == EAGAIN) // NOSENSE -> 11, 11
        return 0;

    if(errno == ECONNRESET) // 104
        return -1;

    g_gamelogbuffer.__ls(init("SYS_ERR"));
    g_gamelogbuffer.__ls("WriteToDescriptor : no =");
    g_gamelogbuffer.__ls((int)errno);
    g_gamelogbuffer.__ls(end);
}

int CDescriptor::ProcessInput(void)
{
    signed int v8; // eax@13
    char v9; // [sp+26h] [bp-2Eh]@11
    char v10; // [sp+27h] [bp-2Dh]@11
    int v13; // [sp+4Ch] [bp-8h]@7
    char v14; // [sp+53h] [bp-1h]@1

    v14 = 0;
    while(this->Unk228.GetRemain() > 0)
    {
        v13 = this->PerformSocketRead(this->Unk192, this->Unk228.GetPoint(), this->Unk228.GetRemain());

        if(v13 < 0)
            return -1;

        if(!v13)
            return 0;

        this->Unk228.SetPoint(v13);

        CNetMsg v11;

        v10 = 0;
        v9 = 0;

        while(!v10)
        {
            v8 = this->Unk228.GetMessage(v11);
            if(v8)
            {
                if(v8 > 0)
                {
                    if(v8 == 1)
                        v10 = 1;
                }
                else
                {
                    if(v8 == -1)
                    {
                        v9 = 1;
                        v10 = 1;
                    }
                }
            }
            else
            {
                this->Unk240.Add(v11);
                v14 = 1;
            }
        }

        if(v9 || v14)
            return -1;
    }

    if(this->Unk372)
    {
        g_gamelogbuffer.__ls(init("SYS_WARN", this->Unk372->Unk8, this->Unk4));
        g_gamelogbuffer.__ls("input overflow");
        g_gamelogbuffer.__ls(end);
    }
    else
    {
        g_gamelogbuffer.__ls(init("SYS_WARN", this->Unk4));
        g_gamelogbuffer.__ls("input overflow");
        g_gamelogbuffer.__ls(end);
    }

    return -1;
}

int CDescriptor::PerformSocketRead(int a2, char *a3, unsigned int a4)
{
    int v4 = read(a2, a3, a4);

    if(v4 > 0)
        return v4;

    if(!v4)
        return -1;

    if(errno == EINTR || errno == EAGAIN || errno == EAGAIN || errno == EWOULDBLOCK) // 4, 11, 11, 35
        return 0;

    return -1;
}

bool CDescriptor::GetLogin(CNetMsg &a2)
{
    size_t v44; // [sp+3Ch] [bp-98h]@13
    size_t v45; // [sp+3Ch] [bp-98h]@18
    char v47[50]; // [sp+50h] [bp-84h]@5
    char src[50]; // [sp+84h] [bp-50h]@5
    unsigned char v51 = 0; // [sp+BBh] [bp-19h]@5
    int dest = 0; // [sp+BCh] [bp-18h]@5

    //CNetMsg v53; <- NOT USED

    a2.MoveFirst();

    if(a2.MsgType != 3)
        throw 5; // __tagMsgFailType.WrongLoginType = 5;

    if(gserver.Unk24.Unk32772 > 8192) // 32796
        throw 0;

    *src = 0; // byte_80CFE56
    memset(src + 1, 0, 49);
    *v47 = 0; // byte_80CFE56
    memset(v47 + 1, 0, 49);

    a2.__rs(dest);  // (int)
    a2.__rs(v51);   // (unsigned char)
    a2.__rs(src);   // (char *)
    a2.__rs(v47);   // (char *)

    TrimString(src);
    TrimString(v47);

    g_gamelogbuffer.__ls(init("LOGIN REQ", src));
    g_gamelogbuffer.__ls("VERSION");
    g_gamelogbuffer.__ls(delim);
    g_gamelogbuffer.__ls(dest);
    g_gamelogbuffer.__ls(delim);
    g_gamelogbuffer.__ls("MODE");
    g_gamelogbuffer.__ls(delim);
    g_gamelogbuffer.__ls(v51);
    g_gamelogbuffer.__ls(delim);
    g_gamelogbuffer.__ls("IP");
    g_gamelogbuffer.__ls(delim);
    g_gamelogbuffer.__ls(this->Unk196);
    g_gamelogbuffer.__ls(end);

    if(dest < gserver.Unk41092 || dest > gserver.Unk41096)
    {
        g_gamelogbuffer.__ls(init("INVALID_VERSION", src));
        g_gamelogbuffer.__ls(dest);
        g_gamelogbuffer.__ls(end);

        throw 1;
    }

    this->Unk356 = v51 ? 1 : 0;

    if(strinc(src, "'"))
        throw 2;

    v44 = strlen(src);
    if(v44 <= 2 || v44 > 20)
        throw 2;

    strcpy(this->Unk4, src);
    if(strinc(v47, "'"))
        throw 3;

    v45 = strlen(v47);
    if(v45 <= 3 || v45 > 20)
        throw 3;

    strcpy(this->Unk35, v47);

    if(gserver.FindConnectIdName(this->Unk4, this))
        throw 4;

    if(!CheckIP(this->Unk196))
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("BLOCK IP");
        g_gamelogbuffer.__ls(this->Unk196);
        g_gamelogbuffer.__ls(end);

        throw 37;
    }

    this->Unk117 = 1;
    this->Unk340 = 30;

    return true;
}

bool CDescriptor::StartGame(CNetMsg &a2)
{
    int dest = 0; // [sp+2Ch] [bp-8h]@1
    char v7 = 0; // [sp+33h] [bp-1h]@1

    a2.MoveFirst();

    a2.__rs(v7);    // unsigned ? (char)
    a2.__rs(dest);  // unsigned ? (int)

    if(v7 != 2)
        return false;

    if(this->Unk372)
    {
        if(this->Unk372)
            delete this->Unk372;

        this->Unk372 = 0;
    }

    this->Unk372 = new CPC();
    this->Unk372->Unk4 = dest;
    this->Unk372->Unk768 = this;
    this->Unk117 = 1;
    this->Unk340 = 22;

    return true;
}

bool CDescriptor::CharNew(CNetMsg &a2)
{
    signed int v9; // [sp+2Ch] [bp-58h]@19
    signed int v10; // [sp+30h] [bp-54h]@19

    char v12 = 1; // [sp+49h] [bp-3Bh]@1
    char v13 = 1; // [sp+4Ah] [bp-3Ah]@1
    char v14 = -1; // [sp+4Bh] [bp-39h]@1
    char src[50]; // [sp+4Ch] [bp-38h]@1
    char dest = 0; // [sp+83h] [bp-1h]@1

    a2.MoveFirst();

    *src = 0; // byte_80CFE56
    memset(src + 1, 0, 49);

    a2.__rs(dest);  // (char)
    a2.__rs(src);   // (char *)
    a2.__rs(v14);   // (char)
    a2.__rs(v13);   // (char)
    a2.__rs(v12);   // (char)

    if(dest)
        return false;

    if(this->Unk372)
    {
        if(this->Unk372)
            delete this->Unk372;

        this->Unk372 = 0;
    }

    this->Unk372 = new CPC();

    if(strlen(src) <= 3 || strlen(src) > 0x10 || strinc(src, "'") || strinc(src, " "))
    {
        CNetMsg v11;

        FailMsg(v11, 2);

        if(this)
            this->WriteToOutput(v11);

        return false;
    }

    strcpy(this->Unk372->Unk8, src);
    strcpy(this->Unk66, src);

    v10 = 0;
    v9 = 0;

    switch(v14)
    {
        case 0:
            v10 = 3;
            v9 = 3;
            break;
        case 3:
            v10 = 3;
            v9 = 3;
            break;
        case 2:
            v10 = 3;
            v9 = 3;
            break;
        case 1:
            v10 = 3;
            v9 = 3;
            break;
        case 4:
            v10 = 3;
            v9 = 3;
            break;
        case 5:
            v10 = 3;
            v9 = 3;
            break;
        default:
            break;
    }

    if(v13 <= 0 || v13 > v10 || v12 <= 0 || v12 > v9)
    {
        CNetMsg v11;

        FailMsg(v11, 11);

        if(this)
            this->WriteToOutput(v11);

        return false;
    }

    this->Unk372->Unk477 = v14;
    this->Unk372->Unk478 = v13;
    this->Unk372->Unk479 = v12;
    this->Unk372->Unk60  = 1;

    this->Unk372->LevelUp(0);

    this->Unk117 = 1;
    this->Unk340 = 20;

    return true;
}

bool CDescriptor::CharDel(CNetMsg &a2)
{
    int dest = 0; // [sp+2Ch] [bp-8h]@1
    char v7 = 0; // [sp+33h] [bp-1h]@1

    a2.MoveFirst();

    a2.__rs(v7);    // (char)
    a2.__rs(dest);  // (int)

    if(v7 != 1)
        return false;

    if(this->Unk372)
    {
        if(this->Unk372)
            delete this->Unk372;
        this->Unk372 = 0;
    }

    this->Unk372 = new CPC();
    this->Unk372->Unk4 = dest;
    this->Unk117 = 1;
    this->Unk340 = 21;

    return true;
}

void CDescriptor::SetHackCheckPulse(void)
{
    this->Unk300 = gserver.Unk41248;
    this->Unk304 = 0;
    this->Unk308 = 0;
    this->Unk312 = 0;
}

bool CDescriptor::IsHackResponseTimeout(void)
{
    return gserver.Unk41248 - this->Unk300 > 3600;
}

bool CDescriptor::CheckHackPulse(int a2)
{
    bool v22; // [sp+2Bh] [bp-Dh]@4
    //int v23; // [sp+2Ch] [bp-Ch]@4
    int v24; // [sp+30h] [bp-8h]@4
    int v25; // [sp+34h] [bp-4h]@4

    this->Unk300 = gserver.Unk41248;

    if(this->Unk304 <= 0 || gserver.Unk41248 - this->Unk304 > 36000)
    {
        this->Unk304 = gserver.Unk41248;
        this->Unk308 = a2;

        return false;
    }

    v25 = gserver.Unk41248 - this->Unk304;
    v24 = a2 - this->Unk308;
    //v23 = v24 - v25;
    v22 = false;

    if(v24 - v25 > 150)
    {
        if(this->Unk372)
        {
            g_gamelogbuffer.__ls(init("HACK_PULSE", this->Unk372->Unk8, this->Unk4));
            g_gamelogbuffer.__ls(v25);
            g_gamelogbuffer.__ls(delim);
            g_gamelogbuffer.__ls(v24);
            g_gamelogbuffer.__ls(end);
        }
        else
        {
            g_gamelogbuffer.__ls(init("HACK_PULSE", this->Unk4));
            g_gamelogbuffer.__ls(v25);
            g_gamelogbuffer.__ls(delim);
            g_gamelogbuffer.__ls(v24);
            g_gamelogbuffer.__ls(end);
        }

        v22 = true;
        goto LABEL_14;
    }

    if(this->Unk312 - v24 < 0)
    {
        if(v24 - this->Unk312 > 299)
            goto LABEL_14;

        goto LABEL_13;
    }

    if(this->Unk312 - v24 <= 299)
    {
LABEL_13:
        g_gamelogbuffer.__ls(init("HACK_PACKET", this->Unk372->Unk8, this->Unk4));
        g_gamelogbuffer.__ls(v25);
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls(v24);
        g_gamelogbuffer.__ls(end);

        v22 = true;
    }

LABEL_14:
    if(v22)
    {
        this->Unk304 = gserver.Unk41248;
        this->Unk308 = a2;

        return this->IncreaseHackCount(4);
    }

    this->Unk312 = v24;

    return false;
}

bool CDescriptor::IncreaseHackCount(int a2)
{
    this->Unk316 += a2;

    if(this->Unk372)
    {
        g_gamelogbuffer.__ls(init("HACK COUNT", this->Unk372->Unk8, this->Unk4));
        g_gamelogbuffer.__ls(this->Unk316);
        g_gamelogbuffer.__ls(end);
    }
    else
    {
        g_gamelogbuffer.__ls(init("HACK COUNT", this->Unk4));
        g_gamelogbuffer.__ls(this->Unk316);
        g_gamelogbuffer.__ls(end);
    }

    if(this->Unk316 <= 10)
        return false;

    this->Unk361 = 1;

    strcpy(g_buf, "HACK USER: ");
    IntCat(g_buf, gserver.Unk41004, true);
    strcat(g_buf, "-");
    IntCat(g_buf, gserver.Unk41004, true);
    strcat(g_buf, ": ");
    strcat(g_buf, this->Unk4);
    strcat(g_buf, " : ");

    if(this->Unk372)
        strcat(g_buf, this->Unk372->Unk8);
    else
        strcat(g_buf, "No select char");

    CNetMsg v9;

    MsgrObserverMsg(v9, -1, -1, -1, -1, g_buf);

    if(!gserver.Unk452129 && gserver.Unk12 && !gserver.Unk12->Unk361)
    {
        if(gserver.Unk12)
            gserver.Unk12->WriteToOutput(v9);
    }

    return true;
}

void CDescriptor::WaitHelperReply(bool a2)
{
    if(a2)
    {
        this->Unk364 = 1;
        this->Unk368 = 0;
    }
    else
    {
        this->Unk364 = 0;
    }
}
