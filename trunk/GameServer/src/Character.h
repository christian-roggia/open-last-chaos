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

#ifndef CHARACTER_H
#define CHARACTER_H

#include "Area.h"
#include "Assist.h"
#include "Cell.h"
#include "Global.h"
#include "Pos.h"
#include "Skill.h"
#include "Room.h"
#include "Zone.h"

class CPC;

class CCharacter;
class CAttackChar;
class CRaChar;

/********************************************************************
CCharacter::`vtbl'{
    0x00000000 = +0  = NOTHING,
    0x080CAD20 = +4  = __tf10CCharacter,
    0x08059970 = +8  = CCharacter::~CCharacter(void),
    0x08059EE0 = +12 = CCharacter::CanMove(void),
    0x08059F30 = +16 = CCharacter::CanAttack(void),
    0x08059F80 = +20 = CCharacter::CanSpell(void),
    0x080CA7C4 = +24 = __pure_virtual,
    0x080CA7C4 = +28 = __pure_virtual,
    0x080CA7C4 = +32 = __pure_virtual,
    0x080CA7C4 = +36 = __pure_virtual,
    0x00000000 = +40 = NOTHING,
}
********************************************************************/

class CCharacter {
public:
    int Unk0; // ClassType (-1 = CCharacter, 0 = CPC, 1 = CNPC)
    int Unk4;
    char Unk8[52]; // Nickname
    int Unk60; // Level
    long long Unk64; // Unk68 ---> EXP
    int Unk72; // SP (?)
    short Unk76, Unk78, Unk80, Unk82, Unk84, Unk86, Unk88, Unk90, Unk92, Unk94, Unk96, Unk98, Unk100;
    char Unk102, Unk103;
    float Unk104; // WalkSpeed
    float Unk108; // RunSpeed
    short Unk112, Unk114;
    int Unk116;
    CPos Unk120;
    int Unk140, Unk144;
    CAssist Unk148;
    CAttackChar *Unk396;
    CCharacter *Unk400, *Unk404; // NOT SURE
    CZone *Unk408;
    CArea *Unk412;
    CRoom *Unk416;
    char Unk420;
    CSkill *Unk424;
    short Unk428, Unk430, Unk432, Unk434, Unk436, Unk438, Unk440, Unk442, Unk444, Unk446, Unk448, Unk450, Unk452, Unk454, Unk456, Unk458;
    // Unk460 -----> Virtual Table
public:
    CCharacter(void);
    virtual ~CCharacter(void);

    void SetVisible(void);
    void SendDisappearAllInCell(void);
    bool CanApplySkill(CSkillProto const *a2, CSkillLevelProto const *a3);
    virtual bool CanMove(void);
    virtual bool CanAttack(void);
    virtual bool CanSpell(void);
    void ApplyAssistData(_tagAssistValue *a2, _tagAssistValue *a3);
    bool IsInPeaceZone(void);
    void Move(float a2, float a3, float a4, float a5, int a6);
    void InitPointsToMax(void);

    // Pure Virtual Functions
    virtual int GetAttackLevel(void)  = 0; // short or int?
    virtual int GetDefenseLevel(void) = 0; // short or int?
    virtual char GetAttackType(CSkillProto const *a2) = 0;
    virtual float GetSize(void) = 0;
};

class CAttackChar {
public:
    int Unk0;
    int Unk4;
    long Unk8;
    char Unk12;
    CCharacter *Unk16;
    CAttackChar *Unk20;
    CAttackChar *Unk24; // 90% SURE
public:
    CAttackChar(void)
    {
        this->Unk16 = 0;
        this->Unk16 = 0;
        this->Unk16 = 0;
        this->Unk20 = 0;
        this->Unk24 = 0;
        this->Unk0  = 0;
        this->Unk4  = 0;
        this->Unk8  = 0;
        this->Unk12 = 0;
    }

    ~CAttackChar()
    {
        ;
    }
};

class CRaChar {
public:
    CPC *Unk0;
    int  Unk4;
    char Unk8; // (bool)
    CRaChar *Unk12, *Unk16; // PreviousNode, NextNode
public:
    CRaChar(void)
    {
        this->Unk0 = 0;
        this->Unk4 = 0;
        this->Unk8 = 0;
    }

    ~CRaChar()
    {
        ;
    }
};

#endif // CHARACTER_H
