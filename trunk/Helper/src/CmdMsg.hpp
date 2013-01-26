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

#include "common.hpp"
#include "Descriptor.hpp"

class CMsgList;
class CMsgListNode;
class CMsgListNodeServerNode;

#ifndef CMDMSG
#define CMDMSG

class CMsgList
{
public:
    CMsgList();
    ~CMsgList();
    CMsgListNode *Add(int seq, bool a3, CDescriptor *desc, CNetMsg &msg);
    void Remove(CMsgListNode *node);
    void RemoveServer(CDescriptor *a2);

//private:
    CMsgListNode *pMsgListNode;
    int Sequence;
};

class CMsgListNode
{
public:
    void Add(CDescriptor *desc);
    CMsgListNode(int a2, bool a3, CDescriptor *desc, CNetMsg &msg);
    bool RemoveServer(CDescriptor *Desc);
    ~CMsgListNode();
//private:
    int unk_dword;
    char char1[4];
    CNetMsg NetMsg;
    char char2[4];
    _DWORD dword20;
    CDescriptor *desc;
    CMsgListNodeServerNode *ServerNode;
    CMsgListNode *ActualListNode;
    CMsgListNode *NewListNode;
};

class CMsgListNodeServerNode
{
public:
    CMsgListNodeServerNode(CDescriptor *desc);
//private:
    CDescriptor *desc;
    char unk_char[4];
    CMsgListNodeServerNode *servernode1;
    CMsgListNodeServerNode *servernode2;
};

#endif

extern char g_buf[0x2000];
extern char g_buf2[0x2000];
extern char g_buf3[0x2000];
