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

#ifndef PC_H
#define PC_H

/**********************************************************************
  WAITING FOR CSSkillList CLASS + CParty CLASS
**********************************************************************/

#include "Character.h"
#include "CmdMsg.h"
#include "Descriptor.h"
#include "ExchangeItems.h"
#include "Guild.h"
#include "hardcoding.h"
#include "Inventory.h"
#include "MemPos.h"
#include "NetMsg.h"
#include "Party.h"
#include "PersonalShop.h"
#include "Quest.h"
#include "Skill.h"
#include "SSkill.h"
#include "Stash.h"

class CPC;
class CExchangeItems;

extern short levelup_stat[6][4];
extern short levelup_hp_0[6][8];
extern short levelup_mp_0[6][8];
extern short base_stat[6][4];
extern short base_hp[6];
extern short base_mp[6];
extern float run_speed[6];
extern float walk_speed[6];
extern int armors_621[];
extern int armors_640[];

/************************************************************************
TODO: CPCList::`vtbl'

CPC::`vtbl'
{
    0x00000000 = +0  = NOTHING,
    0x080CDAB0 = +4  = __tf3CPC,
    0x0807C960 = +8  = CPC::~CPC(void),
    0x0807FB70 = +12 = CPC::CanMove(void),
    0x0807FBE0 = +16 = CPC::CanAttack(void),
    0x0807FC70 = +20 = CPC::CanSpell(void),
    0x0807F8B0 = +24 = CPC::GetAttackLevel(void),
    0x0807F8F0 = +28 = CPC::GetDefenseLevel(void),
    0x0807F9E0 = +32 = CPC::GetAttackType(CSkillProto const *),
    0x080CDC50 = +36 = CPC::GetSize(void),
    0x00000000 = +40 = NOTHING
}
************************************************************************/

class CPC : public CCharacter { // C_LENGTH = 2392
public:
    // long Unk460; `vtbl'
    int Unk464; // PlayerState - CHECK
    int Unk468; // Index ?
    char Unk472, Unk473;
    bool Unk474; // Immortal
    char Unk475, Unk476, Unk477, Unk478, Unk479;
    CSkillList Unk480; // ActiveSkills
    CSkillList Unk492; // PassiveSkills
    CSkillList Unk504; // OtherSkills
    _tagAssistValue Unk516[25], Unk616[25];
    CSSkillList Unk716;
    int Unk724;
    int Unk728; // MaxWeight
    long Unk732, Unk736;
    short Unk740, Unk742, Unk744, Unk746, Unk748;
    int Unk752; // Added By Battle.cpp <-- TO CHECK TYPE INT
    short Unk756, Unk758, Unk760, Unk762, Unk764, Unk766;
    CDescriptor *Unk768;
    long Unk772, Unk776, Unk780;
    int Unk784; // NOT SURE -> CDBThread
    int Unk788;
    CInventory Unk792, Unk880, Unk968;
    CStash Unk1056;
    char Unk1256;
    CNetMsg Unk1260;
    CItem *Unk1280; // Money ?
    CItem *Unk1284[10];
    CExchangeItems *Unk1324;
    CPersonalShop *Unk1328;
    CMemPos Unk1332;
    long Unk1356, Unk1360, Unk1364;
    CParty *Unk1368;
    CQuickSlot Unk1372[3]; // 3 or 2?
    int Unk1852, Unk1856, Unk1860, Unk1864, Unk1868, Unk1872, Unk1876; // FROM CDBThread
    CRaChar *Unk1880;
    long Unk1884, Unk1888, Unk1892, Unk1896;
    CQuestList Unk1900;
    CGuildMember *Unk2368;
    int Unk2372;
    int Unk2376; // FROM CDBThread
    char Unk2380;
    long Unk2384, Unk2388;
public:
    CPC(void);
    ~CPC();

    void SendStatus(void);
    void SendInventory(char a2);
    void SendQuickSlot(void);
    void Send(CNetMsg &a2);
    bool AddMoney(long long a2);
    void AddExpSP(long long src, int a3);
    void Restore(void);
    void InitStat(void);
    void LevelUp(bool a2);
    void RemoveItemFromQuickSlot(CItem *a2);
    void SetMaxWeight(void);
    bool CheckWeight(long long a2, bool a3, bool a4);
    void RecoverPC(void);
    void GoMemPos(int a2);
    void CalcStatus(bool a2);
    bool UseStatPoint(_tagStatPointUseType a2, short *a3);
    void ApplyItemValue(bool a2);
    int SettingItemOption(void);
    int CanWarp(void);
    CSkill *FindSkill(int a2);
    void ApplyPassiveSkill(void);
    int GetAttackLevel(void);
    int GetDefenseLevel(void);
    char GetAttackType(CSkillProto const *a2);
    char GetPKName(void);
    bool CanMove(void);
    bool CanAttack(void);
    bool CanSpell(void);
    int CanChange(void);
    bool IsSetPlayerState(int a2);
    void SetPlayerState(int a2);
    void ResetPlayerState(int a2);
    void TogglePlayerState(int a2);
    int GetPlayerState(void);
    float GetSize(void);
    bool IsParty(void);
    void SaveNow(bool a2);
};

//CPCList::`vtbl'{00000000 080CE140 080CDF40 00000000}

class CPCList {
public:
    CPC *Unk0[8192];
    int Unk32768;
    int Unk32772;
    // long Unk32776; // Virtual Table
public:
    CPCList(void);
    virtual ~CPCList();

    CPC *Find(int a2);
    CPC *Find(char const *a2);
    int  Add(CPC *a2);
    void Remove(CPC *a2);
    bool Playing(CPC *a2);

    void SendToAll(CNetMsg &a2);
};

#endif // PC_H
