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

#ifndef SSKILL_H
#define SSKILL_H

#include "DBCmd.h"

#include <memory.h>

class CSSkillProto;
class CSSkill;
class CSSkillProtoList;
class CSSkillNode;
class CSSkillList;

class CSSkillProto {
public:
    int Unk0; // Index
    int Unk4; // Job
    int Unk8; // Type
    int Unk12; // MaxLevel
    int Unk16; // Preference
    int Unk20[5]; // LevelKNeedLevel
    int Unk40[5]; // LevelKNeedSP
    int Unk60; // NeedSSkill
    int Unk64; // NeedSSkillLevel
    int Unk68[5]; // LevelKNum0
    int Unk88[5]; // LevelKNum1
    int Unk108[5]; // LevelKNum2
    int Unk128[5]; // LevelKNum3
    int Unk148[5]; // LevelKNum4
public:
    CSSkillProto(void);
};

class CSSkill {
public:
    CSSkillProto *Unk0;
    char Unk4;
public:
    CSSkill(CSSkillProto *a2, char a3);
};

class CSSkillProtoList {
public:
    CSSkillProto *Unk0; // SpecialSkillArray
    int Unk4; // SpecialSkillCount
public:
    CSSkillProtoList(void);
    ~CSSkillProtoList();

    bool Load(void);
    CSSkillProto *FindProto(int a2);
    CSSkill *Create(int a2, int a3);
    static int CompIndex(void const *a1, void const *a2)
    {
        return ((CSSkillProto *)a1)->Unk0 - ((CSSkillProto *)a2)->Unk0;
    }
};

class CSSkillNode {
public:
    CSSkill *Unk0; // SSkillNode
    CSSkillNode *Unk4; // NextNode
    CSSkillNode *Unk8; // PreviousNode
public:
    CSSkillNode(CSSkill *a2)
    {
        this->Unk0 = a2;
        this->Unk8 = 0;
        this->Unk4 = 0;
    }
};

class CSSkillList {
public:
    CSSkillNode *Unk0; // SSkillNodes
    int Unk4; // SSkillNodeCount
public:
    CSSkillList(void);
    ~CSSkillList();

    bool Add(CSSkill *a2);
    bool Remove(CSSkill *a2);
    CSSkill *Find(int a2);
    char *GetString(char *dest);
};

#endif // SSKILL_H
