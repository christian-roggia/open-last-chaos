/******************************************************************************************
  Copyright 2013 Andrea Ragusa

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

#include "MemPool.hpp"
#include "common.hpp"
#include "NetMsg.hpp"

#ifndef OUTPUTBUFFER_H
#define OUTPUTBUFFER_H

class COutputBuffer {
public:
    bool Add(CNetMsg &net_msg);
    COutputBuffer();
    void Clear();
    unsigned char *GetNextPoint();
    int GetRemain();
    uint8_t Update(int a2);
    ~COutputBuffer();
private:
    int bufseek;
    unsigned char *mempool;
    int netmsg;
};

#endif

extern CMemPool<unsigned char, 303600> g_outbufpool;
