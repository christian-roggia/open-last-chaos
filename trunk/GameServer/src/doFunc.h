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

#ifndef DOFUNC_H
#define DOFUNC_H

#include "CmdMsg.h"
#include "Global.h"
#include "Log.h"
#include "NetMsg.h"
#include "PC.h"

extern char *gmCmd_567[];
extern int gmLevel_568[];
extern void (*gmFunc_569[])(CPC *,char *);

void do_Action(CPC *a1, CNetMsg &a2);

void do_GM(CPC *a1, CNetMsg &a2);
void do_GMEcho(CPC *a1, char *a2);
void do_GMGoZone(CPC *a1, char *a2);
void do_GMGoto(CPC *a1, char *a2);
void do_GMItemDrop(CPC *a1, char *a2);
void do_GMCountPC(CPC *a1, char *a2);
void do_GMLoopCount(CPC *a1, char *a2);
void do_GMImmortal(CPC *a1, char *a2);
void do_GMShutdown(CPC *a1, char *a2);
void do_GMReboot(CPC *a1, char *a2);
void do_GMCountNPC(CPC *a1, char *a2);
void do_GMVisible(CPC *a1, char *a2);
void do_GMGoPC(CPC *a1, char *a2);
void do_GMGoNPC(CPC *a1, char *a2);
void do_GMLevelUP(CPC *a1, char *a2);
void do_GMKICK(CPC *a1, char *a2);
void do_GMComon(CPC *a1, char *a2);
void do_GMSummon(CPC *a1, char *a2);
void do_GMSilence(CPC *a1, char *a2);
void do_GMWhereAmI(CPC *a1, char *a2);
void do_GMQuestComplete(CPC *a1, char *a2);
void do_GMStatPoint(CPC *a1, char *a2);
void do_GMSkillPoint(CPC *a1, char *a2);
void do_GMSetRegenSec(CPC *a1, char *a2);
void do_GMNPCRegen(CPC *a1, char *a2);
void do_GMKillNPC(CPC *a1, char *a2);
void do_GMExpUp(CPC *a1, char *a2);
void do_GMBloodPoint(CPC *a1, char *a2);
void do_GMEndGame(CPC *a1, char *a2);
void do_GMObserve(CPC *a1, char *a2);
void do_GMChatMonitor(CPC *a1, char *a2);
void do_GMDoubleEvent(CPC *a1, char *a2);
void do_GMDoubleExpEvent(CPC *a1, char *a2);
void _do_GMLattoEvent(CPC *a1, char *a2);
void do_GMNewYearEvent(CPC *a1, char *a2);
void do_GMValentineEvent(CPC *a1, char *a2);

void do_Attack(CPC *a1, CNetMsg &a2);

void do_Chat(CPC *a1, CNetMsg &a2);

void do_UseStatPoint(CPC *a1, CNetMsg &a2);
void do_Pulse(CPC *a1, CNetMsg &a2);
void do_Change(CPC *a1, CNetMsg &a2);

void do_Event(CPC *a1, CNetMsg &a2);

void do_Exchange(CPC *a1, CNetMsg &a2);
void do_ExchangeReq(CPC *a1, CNetMsg &a2);
void do_ExchangeItem(CPC *a1, CNetMsg &a2);
void do_ExchangeReqReq(CPC *a1, CNetMsg &a2);
void do_ExchangeReqRep(CPC *a1, CNetMsg &a2);
void do_ExchangeReqReject(CPC *a1, CNetMsg &a2);
void do_ExchangeReqReady(CPC *a1, CNetMsg &a2);
void do_ExchangeReqOK(CPC *a1, CNetMsg &a2);
void do_ExchangeItemAdd(CPC *a1, CNetMsg &a2);
void do_ExchangeItemDel(CPC *a1, CNetMsg &a2);

void do_Guild(CPC *a1, CNetMsg &a2);

void do_Item(CPC *a1, CNetMsg &a2);

void do_MemPos(CPC *a1, CNetMsg &a2);

void do_Move(CPC *a1, CNetMsg &a2);
void do_GoZone(CPC *a1, CNetMsg &a2);
void do_Warp(CPC *a1, CNetMsg &a2);
void GoZone(CPC *a1, int a2, char a3, float a4, float a5);
void GoTo(CCharacter *a1, char a2, float a3, float a4, float a5, float a6);

void do_NPCRegen(CPC *a1, CNetMsg &a2);

void do_Party(CPC *a1, CNetMsg &a2);

void do_PersonalShop(CPC *a1, CNetMsg &a2);

void do_PK(CPC *a1, CNetMsg &a2);

void do_Produce(CPC *a1, CNetMsg &a2);
//void Produce(CPC *a1, CNPC *a2, _tagProduceKind a3);

void do_Quest(CPC *a1, CNetMsg &a2);

void do_QuickSlot(CPC *a1, CNetMsg &a2);

void do_Rebirth(CPC *a1, CNetMsg &a2);

void do_Skill(CPC *a1, CNetMsg &a2);

void do_SSkill(CPC *a1, CNetMsg &a2);

void do_Stash(CPC *a1, CNetMsg &a2);
void do_StashIsSetPassword(CPC *a1, CNetMsg &a2);
void do_StashListReq(CPC *a1, CNetMsg &a2);
void do_StashListReq_real(CPC *a1);
void do_StashKeep(CPC *a1, CNetMsg &a2);
void do_StashKeep_real(CPC *a1);
void do_StashTake(CPC *a1, CNetMsg &a2);
void do_StashTake_real(CPC *a1);
void do_StashChangePassword(CPC *a1, CNetMsg &a2);
void do_StashSeal(CPC *a1, CNetMsg &a2);

#endif // DOFUNC_H
