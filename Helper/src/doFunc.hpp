/******************************************************************************************
  Copyright 2013 Andrea Ragusa

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

#include "common.hpp"
#include "NetMsg.hpp"
#include "Guild.hpp"

#define _tagGuildErrorType char
#define _tagGuildPositionType char

#ifndef __DOFUNC
#define __DOFUNC

void HelperWhisperNotfoundMsg(CNetMsg &, int32_t, int32_t, int32_t, int32_t, int32_t, const char *);
void HelperWhisperRepMsg(CNetMsg &, int32_t, int32_t, int32_t, int32_t, int32_t, const char *,  const char *, const char *);
void HelperGoZoneRepMsg(CNetMsg &, int32_t, int32_t, int32_t, int32_t, char, int32_t, int32_t, int32_t, int32_t, float, float);
void HelperGuildCreateRepMsg(CNetMsg &, int, _tagGuildErrorType);
void HelperGuildCreateNotifyMsg(CNetMsg &, CGuild *);
void HelperGuildOnlineNotifyMsg(CNetMsg &, CGuildMember *);
void HelperGuildMemberListMsg(CNetMsg &, CGuild *);
void HelperGuildLoadRepMsg(CNetMsg &, const char *, int32_t, _tagGuildErrorType);
void HelperGuildLevelUpRepMsg(CNetMsg &, int32_t, int32_t, _tagGuildErrorType);
void HelperGuildLevelUpNotifyMsg(CNetMsg &, int32_t, int32_t);
void HelperGuildBreakUpRepMsg(CNetMsg &, int32_t, _tagGuildErrorType);
void HelperGuildBreakUpNotifyMsg(CNetMsg &, int32_t);
void HelperGuildMemberAddRepMsg(CNetMsg &, int32_t, int32_t, int32_t, _tagGuildErrorType);
void HelperGuildMemberAddNotifyMsg(CNetMsg &, int32_t, int32_t, const char *, int32_t);
void HelperGuildMemberOutRepMsg(CNetMsg &, int32_t, int32_t, _tagGuildErrorType);
void HelperGuildMemberOutNotifyMsg(CNetMsg &, int32_t, int32_t, const char *);
void HelperGuildMemberKickRepMsg(CNetMsg &, int32_t, int32_t, int32_t, _tagGuildErrorType);
void HelperGuildMemberKickNotifyMsg(CNetMsg &, int32_t, int32_t, int32_t);
void HelperGuildChangeBossRepMsg(CNetMsg &, int32_t, int32_t, int32_t, _tagGuildErrorType);
void HelperGuildChangeBossNotifyMsg(CNetMsg &, int32_t, int32_t, int32_t);
void HelperGuildAppointOfficerRepMsg(CNetMsg &, int32_t, int32_t, int32_t, _tagGuildErrorType);
void HelperGuildAppointOfficerNotifyMsg(CNetMsg &, int32_t, int32_t, int32_t);
void HelperGuildFireOfficerRepMsg(CNetMsg &, int32_t, int32_t, int32_t, _tagGuildErrorType);
void HelperGuildFireOfficerNotifyMsg(CNetMsg &, int32_t, int32_t, int32_t);

#endif
