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

#ifndef NPC_H
#define NPC_H

#include "Battle.h"
#include "Character.h"
#include "NPCProto.h"
#include "Skill.h"

/***********************************
CNPC::`vtbl'
{
    0x00000000 = +0  = NOTHING,
    0x080CCD00 = +4  = __tf4CNPC,
    0x08078EC0 = +8  = CNPC::~CNPC(void),
    0x08059EE0 = +12 = CCharacter::CanMove(void),
    0x08059F30 = +16 = CCharacter::CanAttack(void),
    0x08059F80 = +20 = CCharacter::CanSpell(void),
    0x08079120 = +24 = CNPC::GetDefenseLevel(void),
    0x08079140 = +28 = CNPC::GetDefenseLevel(void),
    0x08079160 = +32 = CNPC::GetAttackType(CSkillProto const *),
    0x080CCD50 = +36 = CNPC::GetSize(void),
    0x00000000 = +0  = NOTHING
}
************************************/

class CNPC;

class CNPC : public CCharacter {
public:
    CNPCProto *Unk464;
    long Unk468, Unk472;
    float Unk476;
    int Unk480;
    float Unk484;
    long Unk488, Unk492;
    char Unk496, Unk497;
    long Unk500;
    char Unk504;
    long Unk508, Unk512, Unk516, Unk520;
    char Unk524, Unk525, Unk526;
    long Unk528[50];
    int Unk728;
    CSkill *Unk732[2];
    long Unk740;
    CNPC *Unk744, *Unk748;
    CNPCRegenInfo *Unk752; // NOT INT
public:
    CNPC(void);
    ~CNPC();

    void DeleteNPC(void);
    void InitAIVar(void);
    void ResetStat(void);
    int GetAttackLevel(void);
    int GetDefenseLevel(void);
    char GetAttackType(CSkillProto const *a2);
    float GetSize(void);
};

#endif // NPC_H
