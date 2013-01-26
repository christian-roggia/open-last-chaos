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

#ifndef CMD_H
#define CMD_H

#include "doFunc.h"
#include "NetMsg.h"
#include "Global.h"
#include "PC.h"

class CCmd;
class CCmdList;

class CCmd {
public:
    __tagMessageType Unk0;             // +0  <------- Type
    long Unk4;                         // +4
    bool Unk8;                         // +8  <------- AllowPlayer
    void (*Unk12)(CPC *,CNetMsg &);    // +12 <------- FunctionPTR

public:
    CCmd(void) {}
    ~CCmd()    {}
};

class CCmdList {
public:
    CCmd *Unk0[200];    // +0   <------- CmdList
    long Unk800;        // +800 <------- CmdCount

public:
    CCmdList(void);
    ~CCmdList();

    bool Add(__tagMessageType a2, void (*a3)(CPC *,CNetMsg &), int a4, bool a5);
    void Sort(void);
    int  Find(CPC *a2, __tagMessageType a3);
    void Run(int a2, CPC *a3, CNetMsg &a4);
};

int CmdComp(void const *a1, void const *a2);

#endif
