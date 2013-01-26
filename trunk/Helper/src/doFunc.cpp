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

#include "doFunc.hpp"

void HelperWhisperNotfoundMsg(CNetMsg &netmsg, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, const char *a7)
{
    netmsg.Init(122);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
    netmsg.__ls(a4);
    netmsg.__ls(a5);
    netmsg.__ls(a6);
    netmsg.__ls(a7);
}

void HelperWhisperRepMsg(CNetMsg &netmsg, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, const char *a7,  const char *a8, const char *a9)
{
    netmsg.Init(122);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
    netmsg.__ls(a4);
    netmsg.__ls(a5);
    netmsg.__ls(1u);
    netmsg.__ls(a6);
    netmsg.__ls(a7);
    netmsg.__ls(a8);
    netmsg.__ls(a9);

}

void HelperGoZoneRepMsg(CNetMsg &netmsg, int32_t a2, int32_t a3, int32_t a4, int32_t a5, char a6, int32_t a7, int32_t a8, int32_t a9, int32_t a10, float f1, float f2)
{
    netmsg.Init(122);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
    netmsg.__ls(a4);
    netmsg.__ls(a5);
    netmsg.__ls(6u);
    netmsg.__ls(a6);
    netmsg.__ls(a7);
    netmsg.__ls(a8);
    netmsg.__ls(a9);

}

void HelperGuildCreateRepMsg(CNetMsg &netmsg, int a2, _tagGuildErrorType a3)
{
    netmsg.Init(122);
    netmsg.__ls(2);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
}

void HelperGuildCreateNotifyMsg(CNetMsg &netmsg, CGuild *guild)
{
    netmsg.Init(123);
    netmsg.__ls(3);
    netmsg.__ls(guild->index() );
    netmsg.__ls(guild->level() );
    netmsg.__ls(guild->name() );
    netmsg.__ls(guild->boss()->charindex() );
    netmsg.__ls(guild->boss()->name() );
}

void HelperGuildOnlineNotifyMsg(CNetMsg &netmsg, CGuildMember *guildmember)
{

    netmsg.Init(123);
    netmsg.__ls(4);
    netmsg.__ls(guildmember->guild()->index() );
    netmsg.__ls(guildmember->charindex() );
    netmsg.__ls(guildmember->online() );
}

void HelperGuildMemberListMsg(CNetMsg &netmsg, CGuild *guild)
{
    CGuildMember *gmember;
    int i;

    netmsg.Init(123);
    netmsg.__ls(5);
    netmsg.__ls(guild->index() );
    netmsg.__ls(guild->membercount() );

    for ( i = 0; i <= 29; ++i )
    {
        if ( ( gmember = guild->member(i) ) )
        {
            netmsg.__ls(gmember->charindex() );
            netmsg.__ls(gmember->name() );
            netmsg.__ls(gmember->pos() );
            netmsg.__ls(gmember->online() );
        }
    }
}

void HelperGuildLoadRepMsg(CNetMsg &netmsg, const char *a2, int32_t a3, _tagGuildErrorType a4)
{
    netmsg.Init(123);
    netmsg.__ls(8);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
    netmsg.__ls(a4);
}

void HelperGuildLevelUpRepMsg(CNetMsg &netmsg, int32_t a2, int32_t a3, _tagGuildErrorType a4)
{
    netmsg.Init(123);
    netmsg.__ls(10);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
    netmsg.__ls(a4);
}

void HelperGuildLevelUpNotifyMsg(CNetMsg &netmsg, int32_t a2, int32_t a3)
{
    netmsg.Init(123);
    netmsg.__ls(11);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
}

void HelperGuildBreakUpRepMsg(CNetMsg &netmsg, int32_t a2, _tagGuildErrorType a3)
{
    netmsg.Init(123);
    netmsg.__ls(13);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
}

void HelperGuildBreakUpNotifyMsg(CNetMsg &netmsg, int a2)
{
    netmsg.Init(123);
    netmsg.__ls(14);
    netmsg.__ls(a2);
}

void HelperGuildMemberAddRepMsg(CNetMsg &netmsg, int32_t a2, int32_t a3, int32_t a4, _tagGuildErrorType a5)
{
    netmsg.Init(123);
    netmsg.__ls(17);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
    netmsg.__ls(a4);
    netmsg.__ls(a5);
}

void HelperGuildMemberAddNotifyMsg(CNetMsg &netmsg, int32_t a2, int32_t a3, const char *a4, int32_t a5)
{
    netmsg.Init(123);
    netmsg.__ls(16);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
    netmsg.__ls(a4);
    netmsg.__ls(a5);
}

void HelperGuildMemberOutRepMsg(CNetMsg &netmsg, int32_t a2, int32_t a3, _tagGuildErrorType a4)
{
    netmsg.Init(123);
    netmsg.__ls(20);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
    netmsg.__ls(a4);
}

void HelperGuildMemberOutNotifyMsg(CNetMsg &netmsg, int32_t a2, int32_t a3, const char *a4)
{
    netmsg.Init(123);
    netmsg.__ls(19);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
    netmsg.__ls(a4);
}

void HelperGuildMemberKickRepMsg(CNetMsg &netmsg, int32_t a2, int32_t a3, int32_t a4, _tagGuildErrorType a5)
{
    netmsg.Init(123);
    netmsg.__ls(22);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
    netmsg.__ls(a4);
    netmsg.__ls(a5);
}

void HelperGuildMemberKickNotifyMsg(CNetMsg &netmsg, int32_t a2, int32_t a3, int32_t a4)
{
    netmsg.Init(123);
    netmsg.__ls(23);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
    netmsg.__ls(a4);
}

void HelperGuildChangeBossRepMsg(CNetMsg &netmsg, int32_t a2, int32_t a3, int32_t a4, _tagGuildErrorType a5)
{
    netmsg.Init(123);
    netmsg.__ls(26);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
    netmsg.__ls(a4);
    netmsg.__ls(a5);
}

void HelperGuildChangeBossNotifyMsg(CNetMsg &netmsg, int32_t a2, int32_t a3, int32_t a4)
{
    netmsg.Init(123);
    netmsg.__ls(25);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
    netmsg.__ls(a4);
}

void HelperGuildAppointOfficerRepMsg(CNetMsg &netmsg, int32_t a2, int32_t a3, int32_t a4, _tagGuildErrorType a5)
{
    netmsg.Init(123);
    netmsg.__ls(28);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
    netmsg.__ls(a4);
    netmsg.__ls(a5);
}

void HelperGuildAppointOfficerNotifyMsg(CNetMsg &netmsg, int32_t a2, int32_t a3, int32_t a4)
{
    netmsg.Init(123);
    netmsg.__ls(29);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
    netmsg.__ls(a4);
}

void HelperGuildFireOfficerRepMsg(CNetMsg &netmsg, int32_t a2, int32_t a3, int32_t a4, _tagGuildErrorType a5)
{
    netmsg.Init(123);
    netmsg.__ls(32);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
    netmsg.__ls(a4);
    netmsg.__ls(a5);
}

void HelperGuildFireOfficerNotifyMsg(CNetMsg &netmsg, int32_t a2, int32_t a3, int32_t a4)
{
    netmsg.Init(123);
    netmsg.__ls(33);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
    netmsg.__ls(a4);
}
