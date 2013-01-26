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

#include "InputBuffer.h"
#include "NetMsg.h"
#include "OutputBuffer.h"
#include "Log.h"
#include "DBCmd.h"
#include "Server.h"
#include "Utils.h"

#include <sys/errno.h>

// CLASS_SIZE = 224

class CDescriptor {
public:
    int Socket;                     // +0
    char Hostname[31];              // +4
    char UnkByte1;                  // +34
    CInputQueue InputQueue;         // +36 <-- Allocated in the heap
    CInputBuffer InputBuffer;       // +76 <-- Allocated in the heap
    CInputQueue InputQueue2;        // +88 <-- Allocated in the heap
    COutputBuffer OutputBuffer;     // +128 <-- Allocated in the heap
    int Unk148;                     // +148
    int Unk152;                     // +152
    int Unk156, Unk160, Unk164;     // +156, +160, +164
    bool WasErrors;                 // +168
    char Unk169;                    // +169
    char Unk170[34];                // +170
    int Unk204;                     // +204
    bool IsTester;                  // +208 // TO CHECK! <---- IsOtherLCAppclication
    int SubServerID;                // +212
    CDescriptor *NextNode;          // +216
    CDescriptor *Node;              // +220

public:
    CDescriptor(void);
    ~CDescriptor()     {}

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
