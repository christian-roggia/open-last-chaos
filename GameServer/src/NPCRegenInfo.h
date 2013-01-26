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

#ifndef NPCREGENINFO_H
#define NPCREGENINFO_H

#include "memory.h"

class CNPCRegenInfo;
class CNPCRegenList;

class CNPCRegenInfo {
public:
    int Unk0, Unk4;
    float Unk8;
    int Unk12; // char???
    float Unk16, Unk20;
    int Unk24, Unk28;
    char Unk32;

    long Unk36;
    int Unk40;
public:
    CNPCRegenInfo(void);
    ~CNPCRegenInfo();
};

class CNPCRegenList {
public:
    int Unk0;
    CNPCRegenInfo *Unk4;
    int Unk8; // NPCRegenListCount
    long Unk12;
public:
    CNPCRegenList(void);
    ~CNPCRegenList();

    void SetCount(int a2);
    void AddRegenInfo(int a2, int a3, float a4, int a5, float a6, float a7, int a8, int a9);
    void AddRegenInfo(CNPCRegenInfo *src);
    void Init(void);
};

#endif // NPCREGENINFO_H
