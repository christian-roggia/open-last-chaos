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

#ifndef BATTLE_H
#define BATTLE_H

#include "Area.h"
#include "CmdMsg.h"
#include "Global.h"
#include "NPC.h"
#include "PC.h"
#include "Server.h"
#include "Skill.h"

bool AttackMob(CPC *a1, CNPC *a2, _tagDamageType a2_1, CSkill *a3, int a4);
bool AttackChar(CNPC *a1, CPC *a2, _tagDamageType a3, CSkill *a4, int a5);
bool AttackPvP(CPC *a1, CPC *a2, _tagDamageType a3, CSkill *a4, int a5);
bool AttackNPC(CNPC *a1, CNPC *a2, _tagDamageType a3, CSkill *a4, int a5);

void ProcDeathPC(CPC *a1, bool a2);
bool CheckInNearCellExt(CCharacter *a1, CCharacter *a2);

char GetHitType(CCharacter *a1, CCharacter *a2, _tagDamageType a3);
int  SelectHitType(CCharacter *a1, CCharacter *a2, _tagDamageType a3, char a4, CMagicProto *a5, CMagicLevelProto *a6);
int  GetDamage(CCharacter *a1, CCharacter *a2, _tagDamageType a3, char a4, CMagicProto *a5, CMagicLevelProto *a6);

CAttackChar *FindMaxDamage(CNPC *a1);
CCharacter *FindPreferencePC(CNPC *a1, int *a2);

void DivisionExpSPParty(CParty *a1, CNPC *a2);
void DivisionExpSP(CNPC *a1);
void DivisionPartyMoney(CPC *a1, CItem *a2);

void GetItemRandomParty(CPC *a1, CItem *a2);
CAttackChar *GetMaxHateTarget(CNPC *a1);
CCharacter *CheckAttackPulse(CNPC *a1);

void AddAttackList(CCharacter *a1, CCharacter *a2, int a3);
void DelAttackList(CCharacter *a1);

void AddRaList(CPC *a1, CPC *a2);
void DelRaList(CPC *a1, bool a2);
bool IsRaList(CPC *a1, CPC *a2);

void FindFamilyInNear(CPC *a1, CNPC *a2);
bool GetSkillPrototypes(CSkillProto const *a1, int a2, int a3, CSkillLevelProto const **a4, CMagicProto const **a5, CMagicLevelProto const **a6);
void ApplyHate(CPC *a1, CNPC *a2, char a3, int a4);
void ApplyDamage(CCharacter *a1, CCharacter *a2, _tagDamageType a3, CSkillProto *a4, int a5, char a6);
void CalcPKPoint(CPC *a1, CPC *a2);

#endif // BATTLE_H
