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

class COutputBuffer;

#ifndef OUTPUTBUFFER_H
#define OUTPUTBUFFER_H

#include "Utils.h"
#include "NetMsg.h"
#include "MemPool.h"

class COutputBuffer {
public:
    unsigned char *p_mempool;   // + 0
    int p_remain;               // + 4
    int p_net_msg;              // + 12
public:
    COutputBuffer();
    ~COutputBuffer();

    void Clear(void)                    { this->p_remain = 0; }
    bool Add(CNetMsg &m_msg);
    char *GetNextPoint(void)            { return this->p_remain ? (char *)this->p_mempool : 0; }
    int GetRemain(void)                 { return this->p_remain; }
    bool Update(int a2);
};

extern CMemPool<unsigned char, 303600> g_outbufpool;

#endif // OUTPUTBUFFER_H
