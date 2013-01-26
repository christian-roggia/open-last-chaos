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
#include "NetMsg.hpp"
#include "common.hpp"

class CInputBuffer
{
public:
    CInputBuffer();
    void Clear();
    signed int GetMessage(CNetMsg &netmsg);
    uint8_t *GetPoint();
    int GetRemain();
    void SetPoint(int point);
    ~CInputBuffer();
private:
    unsigned char *mempool;
    int32_t bufseek;
};

class CInputQueue
{
public:
    CInputQueue();
    void Add(CNetMsg &netmsg);
    void Clear();
    bool Get(CNetMsg &netmsg);
    bool IsEmpty();
    ~CInputQueue();
    class CNode
    {
        public:
        CNetMsg netmsg;
        CNode *subnode;

        CNode(CNetMsg &netmsg) {this->netmsg.Init(netmsg); this->subnode = 0;};
        ~CNode() {delete [] &this->netmsg; delete [] this;};
    };
    private:
    CMutexObject MutexObj;
    CNode *curnode;
    CNode *node;
};
extern CMemPool<unsigned char, 50600> g_inbufpool;

