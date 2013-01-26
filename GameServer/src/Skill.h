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

#ifndef SKILL_H
#define SKILL_H

#include "CmdMsg.h"
#include "DBCmd.h"

class CCharacter;

class CMagicLevelProto;
class CMagicProto;
class CSkillLevelProto;
class CSkillProto;
class CMagicProtoList;
class CSkill;
class CSkillProtoList;
class CSkillListNode;
class CSkillList;

class CMagicLevelProto {
public:
    int Unk0, Unk4;
public:
    CMagicLevelProto(int a2, int a3);
};

class CMagicProto {
public:
    int Unk0;
    char Unk4, Unk5, Unk6, Unk7, Unk8, Unk9;
    CMagicLevelProto **Unk12;
public:
    CMagicProto(int a2, char a3, char a4, char a5, char a6, char a7, char a8, CMagicLevelProto **a9);
    ~CMagicProto();

    CMagicLevelProto *Level(char a2);
};

class CSkillLevelProto {
public:
    short Unk0, Unk2;
    int Unk4, Unk8[2], Unk16[2], Unk24, Unk28, Unk32[3];
    char Unk44[3];
    int Unk48[3], Unk60[3], Unk72[3];
    char Unk84[3];
    CMagicProto *Unk88[3];
    char Unk100[3];
public:
    CSkillLevelProto(short a2, short a3, int a4, int *a5, int *a6, int a7, int a8, int *a9, char *a10, int *a11, int *a12, int *a13, char *a14, CMagicProto const **a15, char *a16);
};

class CSkillProto {
public:
    int Unk0, Unk4;
    char Unk8;
    int Unk12;
    char Unk16;
    float Unk20, Unk24;
    char Unk28, Unk29;
    int Unk32;
    int Unk36[3];
    char Unk48[3];
    int Unk52, Unk56, Unk60, Unk64, Unk68;
    CSkillLevelProto **Unk72;
public:
    CSkillProto(int a2, int a3, char a4, int a5, char a6, float a7, float a8, char a9, char a10, int a11, int *a12, char *a13, int a14, int a15, int a16, int a17, int a18, CSkillLevelProto **a19);
    ~CSkillProto();

    CSkillLevelProto *Level(char a2);
    bool IsActive(void);
    bool IsPassive(void);
};

class CMagicProtoList {
public:
    CMagicProto **Unk0;
    int Unk4;
public:
    CMagicProtoList(void);
    ~CMagicProtoList();

    bool Load(void);
    CMagicProto *Find(int a2);
};

class CSkill {
public:
    CSkillProto const *Unk0;
    char Unk4;
    int Unk8;
    int Unk12;
    long Unk16, Unk20;
public:
    CSkill(CSkillProto const *a2, char a3);

    bool IsReady(CCharacter *a2);
    void Ready(CCharacter *a2);
    void Fire(void);
    void Cancel(void);
};

class CSkillProtoList {
public:
    CSkillProto **Unk0;
    int Unk4;
public:
    CSkillProtoList(void);
    ~CSkillProtoList();

    bool Load(void);
    CSkillProto *Find(int a2);
    CSkill *Create(int a2, int a3);
};

class CSkillListNode {
public:
    CSkill *Unk0;
    CSkillListNode *Unk4, *Unk8;
public:
    CSkillListNode(CSkill *a2);

    CSkillListNode *prev(void);
    void prev(CSkillListNode *a2);
    CSkillListNode *next(void);
    void next(CSkillListNode *a2);
    CSkill *skill(void);
    void skill(CSkill *a2);
};

class CSkillList {
public:
    CSkillListNode *Unk0, *Unk4;
    int Unk8;
public:
    CSkillList(void);
    ~CSkillList();

    bool Add(CSkill *&a2);
    CSkill *Find(int a2);
    int count(void);
    char *GetIndexString(char *dest);
    char *GetLevelString(char *dest);
    CSkillListNode *GetHeadPosition(void);
    CSkill *GetNext(void *&a2);
};

#endif // SKILL_H
