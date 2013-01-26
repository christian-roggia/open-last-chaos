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
#include "Descriptor.hpp"
#include "Guild.hpp"
#include "DBCmd.hpp"
#include "Server.hpp"

void do_CommandCharacterDelete(CNetMsg &netmsg, CDescriptor *desc);
void do_CommandGuildAppointOfficerReq(CNetMsg &netmsg, CDescriptor *desc);
void do_CommandGuildBreakUpReq(CNetMsg &netmsg, CDescriptor *desc);
void do_CommandGuildBreakUpReq_real(CDescriptor *desc, int src, int a3);
void do_CommandGuildChangeBossReq(CNetMsg &netmsg, CDescriptor *desc);
void do_CommandGuildChat(CNetMsg &netmsg, CDescriptor *desc);
void do_CommandGuildCreateReq(CNetMsg &netmsg, CDescriptor *desc);
void do_CommandGuildFireOfficerReq(CNetMsg &netmsg, CDescriptor *desc);
void do_CommandGuildLevelUpReq(CNetMsg &netmsg, CDescriptor *desc);
void do_CommandGuildLoadReq(CNetMsg &netmsg, CDescriptor *desc);
void do_CommandGuildMemberAddReq(CNetMsg &netmsg, CDescriptor *desc);
void do_CommandGuildMemberKickReq(CNetMsg &netmsg, CDescriptor *desc);
void do_CommandGuildMemberOutReq(CNetMsg &netmsg, CDescriptor *desc);
void do_CommandGuildMemberOutReq_real(CDescriptor *desc, int gindex, int gcharindex);
void do_CommandGuildOnline(CNetMsg &netmsg, CDescriptor *desc);
void do_CommandShutdown(CNetMsg &netmsg, CDescriptor *desc);
