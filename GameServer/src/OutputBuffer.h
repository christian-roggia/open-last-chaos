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

#ifndef OUTPUTBUFFER_H
#define OUTPUTBUFFER_H

#include "Utils.h"
#include "NetMsg.h"
#include "MemPool.h"

/***********************************
TODO: COutputBuffer::`vtbl'
************************************/

class COutputBuffer;

class COutputBuffer {
public:
    unsigned char *MemoryPool;      // + 0
    int Pointer;                    // + 4
    int NetMsgCount;                // + 12
public:
    COutputBuffer();
    ~COutputBuffer();

    void Clear(void)                    { this->Pointer = 0; }
    bool Add(CNetMsg &m_msg);
    char *GetNextPoint(void)            { return this->Pointer ? (char *)this->MemoryPool : 0; }
    int GetRemain(void)                 { return this->Pointer; }
    bool Update(int a2);
};

extern CMemPool<unsigned char, 303600> g_outbufpool;

#endif // OUTPUTBUFFER_H
