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

#ifndef QUEST_H
#define QUEST_H

#include "DBCmd.h"
//#include "PC.h"

class CNPC;
class CPC;

class CQuestProto;
class CQuestProtoList;
class CQuest;
class CQuestList;

class CQuestProto {
public:
    int Unk0, Unk4, Unk8, Unk12, Unk16, Unk20, Unk24, Unk28, Unk32;
    int Unk36[5], Unk56[5], Unk76[3], Unk88[3], Unk100[3], Unk112[3][2], Unk160[5], Unk180[5], Unk200[5];
public:
    CQuestProto(void);
};

class CQuestProtoList {
public:
    CQuestProto *Unk0;
    int Unk4;
public:
    CQuestProtoList(void);
    ~CQuestProtoList();

    bool Load(void);
    CQuestProto *FindProto(int a2);
    static int CompIndex(void const *a1, void const *a2);
    CQuest *Create(int a2);
};

class CQuest {
public:
    CQuestProto *Unk0;
    int Unk4[3];
public:
    CQuest(CQuestProto *a2);

    int QuestUpdateData(CPC *a2, CNPC *a3);
};

class CQuestList {
public:
    CQuest *Unk0[10];           // +0
    char Unk40[10], Unk50[10];  // +40, +50
    int Unk60;                  // +60
    int Unk64[100];
    long Unk464;
public:
    CQuestList(void);
    ~CQuestList();

    int AddQuest(CQuest *a2);
    int FindQuest(int a2);
    bool DelQuest(CPC *a2, CQuest *a3);
    char *GetIndexString(char *dest);
    char *GetValueString(char *dest);
    char *GetCompleteIndexString(char *dest);
    void CheckComplete(CPC *a2);
};

#endif // QUEST_H
