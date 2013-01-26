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

#ifndef CMDMSG_H
#define CMDMSG_H

#include "Global.h"
#include "NetMsg.h"

class CCharacter;
class CDescriptor;
class CGuildMember;
class CItem;
class CNPC;
class CPC;
class CQuest;
class CSkill;
class CSkillProto;
class CSSkill;

void AppearMsg(CNetMsg &a1, CCharacter *a2, bool a3);
void DisappearMsg(CNetMsg &a1, CCharacter *a2);
void MoveMsg(CNetMsg &a1, __tagMsgMoveType a2, CCharacter *a3);
void StatusMsg(CNetMsg &a1, CPC *a2);
void AtMsg(CNetMsg &a1, CPC *a2);
void SayMsg(CNetMsg &a1, __tagMsgChatType a2, int a3, char const *a4, char const *a5, char const *a6);
void GotoMsg(CNetMsg &a1, CPC *a2);
void FailMsg(CNetMsg &a1, __tagMsgFailType a2);
void DamageMsg(CNetMsg &a1, CCharacter *a2, CCharacter *a3, _tagDamageType a4, int a5, short a6, char a7);
bool InventoryMsg(CNetMsg &a1, CPC *a2, char a3, int a4, int a5);
void WearingMsg(CNetMsg &a1, CPC *a2, char a3, int a4);
void ItemUseMsg(CNetMsg &a1, CPC *a2, char a3, char a4, char a5, int a6, int a7);
void ItemTakeMsg(CNetMsg &a1, CPC *a2, CItem *a3);
void ItemDeleteMsg(CNetMsg &a1, CItem *a2);
void ItemWearMsg(CNetMsg &a1, char a2, CItem *a3, CItem *a4);
void ItemSwapMsg(CNetMsg &a1, char a2, char a3, char a4, int a5, char a6, char a7, int a8);
void ItemAddMsg(CNetMsg &a1, CItem *a2);
void ItemUpdateMsg(CNetMsg &a1, CItem *a2, long long a3);
void ItemDropMsg(CNetMsg &a1, CCharacter *a2, CItem *a3);
void ItemAppearMsg(CNetMsg &a1, CItem *a2);
void ItemDisappearMsg(CNetMsg &a1, CItem *a2);
void ItemUpgradeRepMsg(CNetMsg &a1, char a2);
void ItemRefineRepMsg(CNetMsg &a1, char a2);
void ItemOptionAddRepMsg(CNetMsg &a1, CItem *a2, _tagItemOptionAddResult a3);
void ItemOptionDelRepMsg(CNetMsg &a1, CItem *a2, _tagItemOptionDelResult a3);
void ItemProcessRepMsg(CNetMsg &a1, _tagProcessResult a2);
void ItemMakeRepMsg(CNetMsg &a1, _tagMakeResult a2);
void ItemMixRepMsg(CNetMsg &a1, _tagItemMixResult a2);
void ItemArcaneRepMsg(CNetMsg &a1, _tagItemArcaneResult a2);
void ItemGetMsg(CNetMsg &a1, CPC *a2, CItem *a3);
void DBCharEndMsg(CNetMsg &a1);
void DBCharExistMsg(CNetMsg &a1, int a2, char const *a3, char a4, char a5, char a6, short a7, long long a8, int a9, short a10, short a11, short a12, short a13, int *a14);
void DBSuccessMsg(CNetMsg &a1);
void DBOtherServerMsg(CNetMsg &a1, int a2, char const *a3, int a4);
void DBOKMsg(CNetMsg &a1, int a2);
void MsgrRepWhisperNotFoundMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, int a6, char const *a7);
void ChatWhisperMsg(CNetMsg &a1, int a2, char const *a3, char const *a4, char const *a5);
void MsgrRepWhisperRepMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, int a6, char const *a7, char const *a8, char const *a9);
void SysWhisperNotFoundMsg(CNetMsg &a1);
void MsgrConnectMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, int *a6);
void MsgrWhisperReqMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, char const *a6, char const *a7, char const *a8);
void MsgrGuildChatMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, char const *a6, int a7, char const *a8);
void SysFullInventoryMsg(CNetMsg &a1, char a2);
void SysMsg(CNetMsg &a1, _tagMsgSysType a2);
void SysSkillInsuffMsg(CNetMsg &a1, char a2);
void SysSkillInvalState(CNetMsg &a1, char a2);
void SysBloodItemMsg(CNetMsg &a1, int a2);
void GoZoneMsg(CNetMsg &a1, int a2, int a3, char const *a4, int a5);
void EnvWeatherMsg(CNetMsg &a1, int a2);
void EnvTimeMsg(CNetMsg &a1);
void EnvTaxChangeMsg(CNetMsg &a1, int a2);
void ExchangeReqMsg(CNetMsg &a1, _tagMsgExchangeReqType a2, CPC *a3, CPC *a4);
void ExchangeItemMsg(CNetMsg &a1, _tagMsgExchangeItemAction a2, CItem *a3, long long a4);
void MemPosListMsg(CNetMsg &a1, CPC *a2);
void MemPosWriteMsg(CNetMsg &a1, CPC *a2, int a3);
void GMWhoAmIMsg(CNetMsg &a1, CPC *a2);
void GMCommandMsg(CNetMsg &a1, char const *a2);
void MsgrNoticeMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, char const *a6);
void MsgrLogoutReqMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, char const *a6);
void MsgrLogoutRepMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, char a6, char const *a7);
void MsgrGoZoneReqMsg(CNetMsg &a1, int a2, int a3, int a4, int a5);
void MsgrGoZoneRepMsg(CNetMsg &a1, int a2, int a3, char a4, int a5, int a6, int a7);
void MsgrEndGameReqMsg(CNetMsg &a1);
void MsgrObserverMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, char const *a6);
void MsgrDoubleEventReqMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, bool a6);
void MsgrDoubleExpEventReqMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, bool a6);
void MsgrLattoEventReqMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, bool a6, int a7, int a8, int a9);
void MsgrNewYearEventReqMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, bool a6, int a7, int a8, int a9);
void MsgrValentineEventReqMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, bool a6, int a7, int a8, int a9);
void QuickSlotAddMsg(CNetMsg &a1, CPC *a2, char a3, char a4);
void QuickSlotListMsg(CNetMsg &a1, CPC *a2, char a3);
void PartyInviteMsg(CNetMsg &a1, CPC *a2);
void PartyMsg(CNetMsg &a1, _tagMsgPartyType a2);
void PartyAddMsg(CNetMsg &a1, CPC *a2, char a3);
void PartyDelMsg(CNetMsg &a1, bool a2, CPC *a3);
void PartyInfoMsg(CNetMsg &a1, CPC *a2);
void PartyErrorMsg(CNetMsg &a1, _tagMsgPartyErrorType a2);
void PartyAssistInfoMsg(CNetMsg &a1, CPC *a2);
void ConnConnectMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, int *a6);
void ConnLoginMsg(CNetMsg &a1, CDescriptor *a2);
void ConnLogoutMsg(CNetMsg &a1, char const *a2);
void ConnPlayingMsg(CNetMsg &a1, CDescriptor *a2, __tagMsgLoginType a3);
void NPCRegenMsg(CNetMsg &a1, CNPC *a2, int a3);
void SkillListMsg(CNetMsg &a1, CPC *a2);
void SkillLearnErrorMsg(CNetMsg &a1, _tagSkillLearnErrorType a2);
void SkillLearnMsg(CNetMsg &a1, CSkill *a2);
void SkillReadyMsg(CNetMsg &a1, CCharacter *a2, CSkill *a3, CCharacter *a4);
void SkillCancelMsg(CNetMsg &a1, CCharacter *a2);
void SkillFireMsg(CNetMsg &a1, CCharacter *a2, CSkill *a3, CCharacter *a4, char a5, char *a6, int *a7);
void MsgrPlayerCountReq(CNetMsg &a1, int a2, int a3, int a4);
void MsgrPlayerCountRep(CNetMsg &a1, int a2, int a3, int a4, int a5, int a6, int a7, int *a8, int *a9, int *a10, int *a11);
void AssistAddMsg(CNetMsg &a1, CCharacter *a2, int a3, int a4, char a5, int a6);
void AssistDelMsg(CNetMsg &a1, CCharacter *a2, int a3, int a4);
void AssistListMsg(CNetMsg &a1, CPC *a2);
void CharStatusMsg(CNetMsg &a1, CCharacter *a2, int a3);
void RebirthMsg(CNetMsg &a1, CCharacter *a2);
void EffectEtcMsg(CNetMsg &a1, CCharacter *a2, _tagMsgEffectEtcType a3);
void EffectSkillMsg(CNetMsg &a1, CCharacter *a2, CSkillProto const *a3);
// void EffectProduceMsg__FR7CNetMsgP10CCharacterT115_tagProduceKind(int a1, int a2, int a3, char a4)
void EffectItemMsg(CNetMsg &a1, CCharacter *a2, CItem *a3);
void ConnRebootReqMsg(CNetMsg &a1);
void ConnPreopenGiftMsg(CNetMsg &a1, int a2, int a3, bool a4);
void ConnLevelupPointMsg(CNetMsg &a1, int a2, int a3);
void ConnStashState(CNetMsg &a1, int a2, int a3);
void ConnStashCheckPassword(CNetMsg &a1, int a2, int a3, char const *a4);
void ConnStashChangePassword(CNetMsg &a1, int a2, int a3, char const *a4, char const *a5);
void ConnStashSeal(CNetMsg &a1, int a2, int a3);
void ExpSPMsg(CNetMsg &a1, long long a2, int a3);
void QuestPCListMsg(CNetMsg &a1, CPC *a2);
void QuestNPCListMsg(CNetMsg &a1, int a2, int *a3, int *a4);
void QuestCreateListMsg(CNetMsg &a1, int a2, int *a3);
void QuestStartMsg(CNetMsg &a1, CQuest *a2);
void QuestCompleteMsg(CNetMsg &a1, CQuest *a2);
void QuestStatusMsg(CNetMsg &a1, CQuest *a2);
void QuestPrizeMsg(CNetMsg &a1, CQuest *a2);
void QuestGiveUpMsg(CNetMsg &a1, CQuest *a2);
void QuestFailMsg(CNetMsg &a1, CQuest *a2);
void QuestErrorMsg(CNetMsg &a1, _tagMsgQuestErrorType a2);
void StatPointRemainMsg(CNetMsg &a1, CPC *a2);
void StatPointUseMsg(CNetMsg &a1, CPC *a2, _tagStatPointUseType a3, short a4);
void StatPointErrorMsg(CNetMsg &a1, char a2);
void ActionMsg(CNetMsg &a1, CPC *a2, char a3, char a4);
void WarpStartMsg(CNetMsg &a1, CPC *a2);
void WarpCancelMsg(CNetMsg &a1, CPC *a2);
void WarpEndMsg(CNetMsg &a1, CPC *a2);
void SSkillListMsg(CNetMsg &a1, CPC *a2);
void SSkillLearnErrorMsg(CNetMsg &a1, _tagSSkillLearnErrorType a2);
void SSkillLearnMsg(CNetMsg &a1, CSSkill *a2);
void SSkillRemoveMsg(CNetMsg &a1, CSSkill *a2);
void PKItemSealMsg(CNetMsg &a1, CItem *a2);
void PKRecoverItemSealMsg(CNetMsg &a1, CItem *a2);
void PKErrorMsg(CNetMsg &a1, char a2);
void EventErrorMsg(CNetMsg &a1, _tagEventErrorType a2);
void EventPreopenGiftMsg(CNetMsg &a1, int a2);
void EventLattoMsg(CNetMsg &a1, _tagEventLattoType a2, int a3, int a4);
void PersonalShopErrorMsg(CNetMsg &a1, _tagPersonalShopErrorType a2);
void PersonalShopSellStartMsg(CNetMsg &a1, CPC *a2);
void PersonalShopSellListMsg(CNetMsg &a1, CPC *a2);
void PersonalShopChangeMsg(CNetMsg &a1, CPC *a2);
void PersonalShopBuyMsg(CNetMsg &a1, CNetMsg &a2, CPC *a3);
void RightAttackMsg(CNetMsg &a1, CPC *a2, _tagRightAttackType a3);
void StashIsSetPassword(CNetMsg &a1, bool a2);
void StashErrorMsg(CNetMsg &a1, _tagStashErrorType a2);
void StashListRepMsg(CNetMsg &a1, CItem const *a2, bool a3, bool a4, bool a5);
void StashKeepRepMsg(CNetMsg &a1, int a2, int *a3, long long *a4);
void StashTakeRepMsg(CNetMsg &a1, int a2, int *a3, long long *a4);
void StashChangePasswordRepMsg(CNetMsg &a1, bool a2);
void StashSealMsg(CNetMsg &a1);
void GuildErrorMsg(CNetMsg &a1, _tagGuildErrorType a2);
void GuildInfoMsg(CNetMsg &a1, CPC *a2);
void GuildListMsg(CNetMsg &a1, CPC *a2, bool a3);
void HelperShutdownMsg(CNetMsg &a1);
void HelperRepWhisperNotFoundMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, int a6, char const *a7);
void HelperRepWhisperRepMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, int a6, char const *a7, char const *a8, char const *a9);
void HelperGoZoneRepMsg(CNetMsg &a1, int a2, int a3, char a4, int a5, int a6, int a7);
void HelperGuildCreateReqMsg(CNetMsg &a1, CPC *a2, char const *a3);
void GuildOnlineMsg(CNetMsg &a1, CGuildMember *a2);
void HelperConnectMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, int *a6);
void HelperGuildOnline(CNetMsg &a1, CGuildMember *a2);
void HelperGuildLoadReq(CNetMsg &a1, char const *a2, int a3);
void HelperGuildLevelUpReqMsg(CNetMsg &,int,int);
void GuildLevelInfoMsg(CNetMsg &a1, int a2, int a3);
void HelperGuildBreakUpReqMsg(CNetMsg &a1, CPC *a2);
void GuildBreakUpNotifyMsg(CNetMsg &a1, int a2, char const *a3);
void GuildRegistCancelMsg(CNetMsg &a1, bool a2);
void HelperGuildMemberAddReqMsg(CNetMsg &a1, int a2, int a3, int a4, char const *a5);
void GuildMemberAddMsg(CNetMsg &a1, int a2, int a3, char const *a4);
void HelperGuildOutReqMsg(CNetMsg &a1, int a2, int a3);
void GuildMemberOutMsg(CNetMsg &a1, int a2, int a3, char const *a4);
void HelperGuildKickReqMsg(CNetMsg &a1, int a2, int a3, int a4);
void GuildMemberKickMsg(CNetMsg &a1, int a2, int a3, int a4, char const *a5);
void GuildInfoChangeMsg(CNetMsg &a1, int a2, int a3, char const *a4, _tagGuildPositionType a5);
void HelperGuildChangeBossReqMsg(CNetMsg &a1, int a2, int a3, int a4);
void GuildChangeBossMsg(CNetMsg &a1, int a2, int a3, int a4);
void HelperGuildAppointOfficerReqMsg(CNetMsg &a1, int a2, int a3, int a4);
void GuildAppointOfficerMsg(CNetMsg &a1, int a2, int a3);
void HelperGuildChat(CNetMsg &a1, int a2, int a3, char const *a4, char const *a5);
void HelperGuildFireOfficerReqMsg(CNetMsg &a1, int a2, int a3, int a4);
void GuildFireOfficerMsg(CNetMsg &a1, int a2, int a3);
void HelperCharDelMsg(CNetMsg &a1, int a2);
void ChangeErrMsg(CNetMsg &a1, _tagMsgChangeErrType a2);
void ChangeStartMsg(CNetMsg &a1, CPC *a2);
void ChangeStopMsg(CNetMsg &a1, CPC *a2);

#endif // CMDMSG_H
