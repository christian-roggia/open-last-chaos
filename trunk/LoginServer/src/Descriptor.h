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

class CDescriptor;

#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include "InputBuffer.h"
#include "NetMsg.h"
#include "OutputBuffer.h"
#include "Log.h"
#include "DBCmd.h"
#include "Server.h"
#include "Utils.h"

#include <sys/errno.h>

class CDescriptor {
public:
    int MainSocket;                 // + 0
    char Username[21];              // + 4
    char Password[21];              // + 35
    char Unk66;                     // + 66
    int Number;                     // + 120
    int MaxSubNumber;               // + 124
    int *ConnectorsID;              // + 128
    int *ConnectorsUnk;             // + 132
    char **ConnectorsIP;            // + 136
    int *ConnectorsUnk2;            // + 140
    int Socket;                     // + 144
    char Hostname[31];              // + 148
    char Unk178;                    // + 178
    CInputBuffer InputBuffer;       // + 180 <-- Allocated in the heap
    CInputQueue InputQueue;         // + 192 <-- Allocated in the heap
    COutputBuffer OutputBuffer;     // + 232 <-- Allocated in the heap
    int Unk252;                     // + 252
    int SocketPhase;                // + 256
    int FailedAttempts;             // + 260
    bool WasErrors;                 // + 264
    CDescriptor *NextNode;          // + 268
    CDescriptor *PreviousNode;      // + 272

public:
    CDescriptor(void);
    ~CDescriptor();

    void CloseSocket(void);
    void FlushQueues(void);
    void WriteToOutput(CNetMsg &net_msg);
    int ProcessOutput(void);
    int WriteToDescriptor(long p_fd, char const *p_buf, long p_bytes);
    int ProcessInput(void);
    int PerformSocketRead(long p_fd, char *p_buf, unsigned long p_bytes);
    bool GetLogin(CNetMsg &net_msg);
};

#endif
