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

#ifndef ASSIST_H
#define ASSIST_H

#include "Global.h"
#include "NetMsg.h"

class CArea;
class CCharacter;
class CNPC;
class CSkillProto;

class CAssistData;
class CAssistList;
class CAssist;

class CAssistData {
public:
    int Unk0;                   // +0
    CSkillProto *Unk4;          // +4
    int Unk8, Unk12;            // +8, +12
    bool Unk16[3];              // +16
    CAssistData *Unk20, *Unk24; // +20, +24
public:
    CAssistData(int a2, CSkillProto const *a3, int a4, int a5, bool *src);

};

class CAssistList {
public:
    CAssistData *Unk0, *Unk4;
    long Unk8;
    int Unk12;
public:
    CAssistList(void);
    ~CAssistList();

    void Max(int m_max);
    bool Add(int a2, CSkillProto const *a3, int a4, bool *src, int &a6);
    bool CanApply(CSkillProto const *a2, int a3);
    void DelDuplicate(CSkillProto const *a2, int a3, bool a4, CCharacter *a5);
    bool DecreaseTime(CCharacter *a2, int *a3);
    void Apply(_tagAssistValue *a2, _tagAssistValue *a3, int *a4);
    void Del(CAssistData *a2, bool a3, CCharacter *a4);

};

class CAssist {
public:
    CCharacter *Unk0;
    CAssistList Unk4, Unk20;
    int Unk36;
    _tagAssistValue Unk40[25], Unk140[25];
    int Unk240, Unk244;
public:
    CAssist(void);
    ~CAssist();

    void Init(CCharacter *a2);
    bool Add(int a2, CSkillProto const * a3, int a4, bool *src, bool a6, int a7);
    bool CanApply(CSkillProto const *a2, int a3);
    void DelDuplicate(CSkillProto const *a2, int a3, bool a4);
    bool DecreaseTime(void);
    void Apply(void);
    void Clear(void);
    void GetListString(bool a2, char *dest, char *a4, char *a5, char *a6, char *a7, char *a8, char *a9);
    void AppendAssistToNetMsg(CNetMsg &a2);
    bool Find(int a2, int a3);
    void CancelSleep(void);
    void Cure(int a2, int a3);
};

#endif // ASSIST_H
