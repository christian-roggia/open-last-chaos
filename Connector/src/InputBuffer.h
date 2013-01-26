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

#ifndef INPUTBUFFER_H
#define INPUTBUFFER_H

#include "Utils.h"
#include "NetMsg.h"
#include "MemPool.h"
#include "Mutex.h"

class CInputBuffer {
private:
    unsigned char *p_pool;  // + 0
    int p_point;            // + 4

public:
    CInputBuffer(void);
    ~CInputBuffer();

    void Clear(void);
    char *GetPoint(void);
    int GetRemain(void);
    void SetPoint(long new_point);
    int GetMessage(CNetMsg &net_msg);
};

extern CMemPool<unsigned char, 50600> g_inbufpool;

/********************************************************************************
 * Queue
 ********************************************************************************/

class CInputQueue : public CMutexObject {
public:
    CInputQueue(void) { this->p_current_node = 0; this->p_node = 0; }
    ~CInputQueue() { this->Clear(); }

    void Clear(void);
    void Add(CNetMsg &net_msg);
    bool Get(CNetMsg &net_msg);
    bool IsEmpty(void) { return this->p_node == 0; }

    class CNode : public CNetMsg {
    public:
        CNode *p_sub_node;  // + 20
    public:
        CNode(CNetMsg &met_msg) { this->Init(met_msg); this->p_sub_node = 0; }
        ~CNode() {}
    };
private:
    CMutexObject p_mutex;                // + 0
    CInputQueue::CNode *p_node;          // + 28
    CInputQueue::CNode *p_current_node;  // + 32
};

#endif
