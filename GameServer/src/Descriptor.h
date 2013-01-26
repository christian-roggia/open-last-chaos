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

#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include "CmdMsg.h"
#include "InputBuffer.h"
#include "Log.h"
#include "Mutex.h"
#include "NetMsg.h"
#include "OutputBuffer.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <asm-generic/errno-base.h>
#include <asm-generic/errno.h>

class CPC;

class CDescriptor;

class CDescriptor {
public:
    int Unk0;
    char Unk4[21]; // HostIP
    char Unk35[21];
    char Unk66[51];
    char Unk117;
    int Unk120;
    CInputQueue Unk124;
    CMutexObject Unk164;
    int Unk192; // MainSocket
    char Unk196[31];
    CInputBuffer Unk228;
    CInputQueue Unk240;
    COutputBuffer Unk280;
    int Unk300;
    int Unk304;
    int Unk308;
    long Unk312;
    int Unk316; // HackCount
    long Unk320;
    int Unk324;
    short Unk328;
    int Unk332, Unk336;
    int Unk340;
    long Unk344;
    int Unk348;
    int Unk352;
    long Unk356;
    char Unk360;
    bool Unk361; // ErrorOccurred
    char Unk362;
    char Unk363;
    char Unk364;
    char Unk368; // CHECK
    CPC *Unk372;
    CDescriptor *Unk376;
    CDescriptor *Unk380;
public:
    CDescriptor(void);
    ~CDescriptor(void);

    void CloseSocket(void);
    void FlushQueues(void);
    void WriteToOutput(CNetMsg &a2);
    int ProcessOutput(void);
    static int WriteToDescriptor(int a2, char const *a3, int a4);
    int ProcessInput(void);
    static int PerformSocketRead(int a2, char *a3, unsigned int a4);

    bool GetLogin(CNetMsg &a2);
    bool StartGame(CNetMsg &a2);
    bool CharNew(CNetMsg &a2);
    bool CharDel(CNetMsg &a2);

    void SetHackCheckPulse(void);
    bool IsHackResponseTimeout(void);
    bool CheckHackPulse(int a2);
    bool IncreaseHackCount(int a2);
    void WaitHelperReply(bool a2);
};

#endif // DESCRIPTOR_H
