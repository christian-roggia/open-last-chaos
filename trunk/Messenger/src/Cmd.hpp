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

#include "NetMsg.hpp"
#include "CmdMsg.hpp"
#include "Descriptor.hpp"
#include "Server.hpp"
#include "doFunc.hpp"

class CCmd
{
public:
    CCmd();
    ~CCmd();

    int type;
    void (*pFunc)(CNetMsg &, CDescriptor *);
    int unk;
};

class CCmdList
{
public:

    CCmdList();
    int Find(__tagMessageType);
    void Run(int val, CNetMsg &netmsg, CDescriptor *desc);
    void Add(__tagMessageType, void (*pFunc)(CNetMsg &, CDescriptor *), int unk);
    void Sort();
    ~CCmdList();

    CCmd *CmdArray[200];
    int CmdCount;
};

void do_Reply(CNetMsg &netmsg, CDescriptor *desc);
void do_Request(CNetMsg &netmsg, CDescriptor *desc);
__compar_fn_t CmdComp(void *a1, void *a2);

extern CDescriptor g_descriptor;
extern CMsgList g_msglist;
extern CCmdList gcmdlist;
