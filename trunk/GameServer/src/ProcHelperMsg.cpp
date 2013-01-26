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

#include "Server.h"

void CServer::ProcessHelperMessage(CNetMsg &a2)
{
        /* TODO */
}

/*void CServer::ProcessHelperMessage(CNetMsg &a2)
{
    signed int v2; // eax@1
    int v3; // eax@30
    int v4; // eax@30
    int v5; // eax@30
    int v6; // eax@30
    int v7; // eax@49
    int v8; // eax@49
    int v9; // eax@49
    int v10; // eax@49
    signed int v12; // [sp+1Ch] [bp-18h]@30
    signed int v13; // [sp+1Ch] [bp-18h]@49
    unsigned __int8 v14; // [sp+23h] [bp-11h]@30
    int v15; // [sp+24h] [bp-10h]@30
    int v16; // [sp+28h] [bp-Ch]@30
    int v17; // [sp+2Ch] [bp-8h]@30
    unsigned int dest; // [sp+30h] [bp-4h]@6

    CNetMsg::MoveFirst(a2);
    v2 = *(_DWORD *)a2;
    if(*(_DWORD *)a2 == 122)
    {
        v7 = CNetMsg::__rs(a2, &v15);
        v8 = CNetMsg::__rs(v7, &v16);
        v9 = CNetMsg::__rs(v8, &v17);
        v10 = CNetMsg::__rs(v9, &dest);
        CNetMsg::__rs(v10, &v14);
        v2 = CServer::FindZone((int)&gserver, dest);
        v13 = v2;
        if(v16 == -1
            || (LOBYTE(v2) = v16, v16 == gserver.Unk41004) && (v17 == -1 || (LOBYTE(v2) = v17, v17 == gserver.Unk41008)))
        {
            if(dest == -1 || v13 != -1 && (LOBYTE(v2) = gserver.Unk452196, *(_DWORD *)(gserver.Unk452196 + 72 * v13) == dest))
            {
                LOBYTE(v2) = v14;
                if(v14 == 3)
                {
                    LOBYTE(v2) = ProcHelperWhisperNotfound(a2);
                }
                else
                {
                    if((signed int)v14 > 3)
                    {
                        if(v14 == 6)
                            LOBYTE(v2) = ProcHelperGoZoneRep(a2);
                    }
                    else
                    {
                        if(v14 == 1)
                            LOBYTE(v2) = ProcHelperWhisperRep(a2);
                    }
                }
            }
        }
    }
    else
    {
        if(v2 > 122)
        {
            if(v2 == 123)
            {
                CNetMsg::__rs(a2, &dest);
                LOBYTE(v2) = dest;
                switch(dest)
                {
                    case 2:
                        LOBYTE(v2) = ProcHelperGuildCreateRep(a2);
                        break;
                    case 3:
                        LOBYTE(v2) = ProcHelperGuildCreateNotify(a2);
                        break;
                    case 4:
                        LOBYTE(v2) = ProcHelperGuildOnlineNotify(a2);
                        break;
                    case 5:
                        LOBYTE(v2) = ProcHelperGuildMemberList(a2);
                        break;
                    case 8:
                        LOBYTE(v2) = ProcHelperGuildLoadRep(a2);
                        break;
                    case 0xA:
                        LOBYTE(v2) = ProcHelperGuildLevelUpRep(a2);
                        break;
                    case 0xB:
                        LOBYTE(v2) = ProcHelperGuildLevelUpNotify(a2);
                        break;
                    case 0xD:
                        LOBYTE(v2) = ProcHelperGuildBreakUpRep(a2);
                        break;
                    case 0xE:
                        LOBYTE(v2) = ProcHelperGuildBreakUpNotify(a2);
                        break;
                    case 0x10:
                        LOBYTE(v2) = ProcHelperGuildMemberAddNotify(a2);
                        break;
                    case 0x11:
                        LOBYTE(v2) = ProcHelperGuildMemberAddRep(a2);
                        break;
                    case 0x13:
                        LOBYTE(v2) = ProcHelperGuildMemberOutNotify(a2);
                        break;
                    case 0x14:
                        LOBYTE(v2) = ProcHelperGuildMemberOutRep(a2);
                        break;
                    case 0x16:
                        LOBYTE(v2) = ProcHelperGuildMemberKickRep(a2);
                        break;
                    case 0x17:
                        LOBYTE(v2) = ProcHelperGuildMemberKickNotify(a2);
                        break;
                    case 0x1A:
                        LOBYTE(v2) = ProcHelperGuildChangeBossRep(a2);
                        break;
                    case 0x19:
                        LOBYTE(v2) = ProcHelperGuildChangeBossNotify(a2);
                        break;
                    case 0x1C:
                        LOBYTE(v2) = ProcHelperGuildAppointOfficerRep(a2);
                        break;
                    case 0x1D:
                        LOBYTE(v2) = ProcHelperGuildAppointOfficerNotify(a2);
                        break;
                    case 0x1E:
                        LOBYTE(v2) = ProcHelperGuildChat(a2);
                        break;
                    case 0x20:
                        LOBYTE(v2) = ProcHelperGuildFireOfficerRep(a2);
                        break;
                    case 0x21:
                        LOBYTE(v2) = ProcHelperGuildFireOfficerNotify(a2);
                        break;
                    default:
                        return v2;
                }
            }
        }
        else
        {
            if(v2 == 121)
            {
                v3 = CNetMsg::__rs(a2, &dest);
                v4 = CNetMsg::__rs(v3, &v17);
                v5 = CNetMsg::__rs(v4, &v16);
                v6 = CNetMsg::__rs(v5, &v15);
                CNetMsg::__rs(v6, &v14);
                v2 = CServer::FindZone((int)&gserver, v15);
                v12 = v2;
                if(v17 == -1
                    || (LOBYTE(v2) = v17, v17 == gserver.Unk41004) && (v16 == -1 || (LOBYTE(v2) = v16, v16 == gserver.Unk41008)))
                {
                    if(v15 == -1 || v12 != -1 && (LOBYTE(v2) = gserver.Unk452196, *(_DWORD *)(gserver.Unk452196 + 72 * v12) == v15))
                    {
                        LOBYTE(v2) = v14;
                        if(v14 == 4)
                        {
                            LOBYTE(v2) = ProcHelperNoticeChat(a2, dest, v17, v16, v15);
                        }
                        else
                        {
                            if((signed int)v14 > 4)
                            {
                                if(v14 == 5)
                                    LOBYTE(v2) = ProcHelperGoZoneReq(a2, dest);
                            }
                            else
                            {
                                if(!v14)
                                    LOBYTE(v2) = ProcHelperWhisperReq(a2, dest, v17, v16, v15);
                            }
                        }
                    }
                }
            }
        }
    }
    return v2;
}

int ProcHelperWhisperReq(CNetMsg &,int,int,int,int)
{
    int v5; // eax@1
    int v6; // eax@1
    int v7; // eax@1
    int result; // eax@7
    int v9; // [sp+8h] [bp-30h]@10
    int v10; // [sp+1Ch] [bp-1Ch]@2
    int v11; // [sp+30h] [bp-8h]@1
    uint32_t dest; // [sp+34h] [bp-4h]@1

    g_buf3[0] = 0;
    g_buf2[0] = 0;
    g_buf[0] = 0;
    v5 = CNetMsg::__rs(a1, &dest);
    v6 = CNetMsg::__rs(v5, g_buf);
    v7 = CNetMsg::__rs(v6, g_buf2);
    CNetMsg::__rs(v7, g_buf3);
    v11 = CPCList::Find(gserver.Unk24, g_buf2);
    if(v11)
    {
        CNetMsg::CNetMsg((int)&v10);
        ChatWhisperMsg((int)&v10, dest, g_buf, (char *)(v11 + 8), g_buf3);
        if(*(_DWORD *)(v11 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(v11 + 768), (int)&v10);
        CNetMsg::CNetMsg((int)&v9);
        HelperRepWhisperRepMsg((int)&v9, src, a3, a4, a5, dest, g_buf, (char *)(v11 + 8), g_buf3);
        if(!gserver.Unk452130 && gserver.Unk20 && !gserver.Unk20->Unk361 && gserver.Unk20)
            CDescriptor::WriteToOutput(gserver.Unk20, (int)&v9);
        CNetMsg::_CNetMsg((int)&v9, 2);
        result = CNetMsg::_CNetMsg((int)&v10, 2);
    }
    else
    {
        CNetMsg::CNetMsg((int)&v10);
        HelperRepWhisperNotFoundMsg((int)&v10, src, a3, a4, a5, dest, g_buf);
        if(!gserver.Unk452130 && gserver.Unk20 && !gserver.Unk20->Unk361)
        {
            if(gserver.Unk20)
                CDescriptor::WriteToOutput(gserver.Unk20, (int)&v10);
        }
        result = CNetMsg::_CNetMsg((int)&v10, 2);
    }
    return result;
}

int ProcHelperNoticeChat(CNetMsg &,int,int,int,int)
{
    int i; // [sp+10h] [bp-18h]@1
    int v7; // [sp+14h] [bp-14h]@1

    g_buf[0] = 0;
    CNetMsg::__rs(a1, g_buf);
    CNetMsg::CNetMsg((int)&v7);
    SayMsg((int)&v7, 6, 0, (char *)&unk_80D0B8C, (char *)&unk_80D0B8C, g_buf);
    for(i = 0; i < gserver.Unk24.Unk32768; ++i)
    {
        if(gserver.Unk20[i + 1]
            && *(_DWORD *)(gserver.Unk20[i + 1] + 408)
            && (**(_DWORD **)(gserver.Unk20[i + 1] + 408) == a5 || a5 == -1))
        {
            if(*(_DWORD *)(gserver.Unk20[i + 1] + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(gserver.Unk20[i + 1] + 768), (int)&v7);
        }
    }
    return CNetMsg::_CNetMsg((int)&v7, 2);
}

signed int ProcHelperGoZoneReq(CNetMsg &,int,int,int,int)
{
    int v2; // eax@1
    int v3; // eax@1
    int v4; // eax@1
    int v5; // eax@1
    int v6; // eax@1
    signed int result; // eax@1
    int v8; // [sp+14h] [bp-34h]@2
    int v9; // [sp+28h] [bp-20h]@2
    int v10; // [sp+2Ch] [bp-1Ch]@1
    char v11; // [sp+30h] [bp-18h]@1
    char dest; // [sp+34h] [bp-14h]@1
    char v13; // [sp+38h] [bp-10h]@1
    int v14; // [sp+3Ch] [bp-Ch]@1
    int v15; // [sp+40h] [bp-8h]@1
    int v16; // [sp+44h] [bp-4h]@1

    v2 = CNetMsg::__rs(a1, &v16);
    v3 = CNetMsg::__rs(v2, &v15);
    v4 = CNetMsg::__rs(v3, &v14);
    v5 = CNetMsg::__rs(v4, &v13);
    v6 = CNetMsg::__rs(v5, &dest);
    CNetMsg::__rs(v6, &v11);
    result = CServer::FindZone((int)&gserver, v14);
    v10 = result;
    if(result != -1)
    {
        v9 = 72 * v10 + gserver.Unk452196;
        CNetMsg::CNetMsg((int)&v8);
        if(*(_DWORD *)(v9 + 40) <= 1)
        {
            HelperGoZoneRepMsg((int)&v8, src, *(_DWORD *)v9, 1, v16, v15, v14);
        }
        else
        {
            if(CZone::FindEmptyArea(v9) == -1)
                HelperGoZoneRepMsg((int)&v8, src, *(_DWORD *)v9, 0, v16, v15, v14);
            else
                HelperGoZoneRepMsg((int)&v8, src, *(_DWORD *)v9, 1, v16, v15, v14);
        }
        if(!gserver.Unk452130 && gserver.Unk20 && !gserver.Unk20->Unk361)
        {
            if(gserver.Unk20)
                CDescriptor::WriteToOutput(gserver.Unk20, (int)&v8);
        }
        result = CNetMsg::_CNetMsg((int)&v8, 2);
    }
    return result;
}

int ProcHelperWhisperRep(CNetMsg &,int,int,int,int)
{
    int v1; // eax@1
    int v2; // eax@1
    int v3; // eax@1
    int v4; // eax@1
    int result; // eax@1
    int v6; // [sp+8h] [bp-20h]@2
    int v7; // [sp+1Ch] [bp-Ch]@1
    char v8; // [sp+20h] [bp-8h]@1
    unsigned int dest; // [sp+24h] [bp-4h]@1

    g_buf3[0] = 0;
    g_buf2[0] = 0;
    g_buf[0] = 0;
    v1 = CNetMsg::__rs(a1, &dest);
    v2 = CNetMsg::__rs(v1, g_buf);
    v3 = CNetMsg::__rs(v2, &v8);
    v4 = CNetMsg::__rs(v3, g_buf2);
    CNetMsg::__rs(v4, g_buf3);
    result = CPCList::Find(gserver.Unk24, dest);
    v7 = result;
    if(result)
    {
        CNetMsg::CNetMsg((int)&v6);
        ChatWhisperMsg((int)&v6, dest, g_buf, g_buf2, g_buf3);
        if(*(_DWORD *)(v7 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(v7 + 768), (int)&v6);
        result = CNetMsg::_CNetMsg((int)&v6, 2);
    }
    return result;
}

int ProcHelperWhisperNotfound(CNetMsg &,int,int,int,int)
{
    int v1; // eax@1
    int result; // eax@1
    char v3; // [sp+Ch] [bp-1Ch]@2
    int v4; // [sp+20h] [bp-8h]@1
    int dest; // [sp+24h] [bp-4h]@1

    g_buf[0] = 0;
    v1 = CNetMsg::__rs(a1, &dest);
    CNetMsg::__rs(v1, g_buf);
    result = CPCList::Find(gserver.Unk24, dest);
    v4 = result;
    if(result)
    {
        CNetMsg::CNetMsg((int)&v3);
        SysWhisperNotFoundMsg((int)&v3);
        if(*(_DWORD *)(v4 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(v4 + 768), (int)&v3);
        result = CNetMsg::_CNetMsg((int)&v3, 2);
    }
    return result;
}

int ProcHelperGoZoneRep(CNetMsg &,int,int,int,int)
{
    int v1; // eax@1
    int v2; // eax@1
    int v3; // eax@1
    int v4; // eax@1
    int v5; // eax@1
    int v6; // eax@1
    int result; // eax@1
    int v8; // eax@9
    char v9; // [sp+14h] [bp-54h]@9
    int v10; // [sp+28h] [bp-40h]@5
    int v11; // [sp+2Ch] [bp-3Ch]@4
    int v12; // [sp+30h] [bp-38h]@4
    int v13; // [sp+34h] [bp-34h]@4
    int v14; // [sp+48h] [bp-20h]@1
    float v15; // [sp+4Ch] [bp-1Ch]@1
    float dest; // [sp+50h] [bp-18h]@1
    char v17; // [sp+54h] [bp-14h]@1
    uint32_t src; // [sp+58h] [bp-10h]@1
    int v19; // [sp+5Ch] [bp-Ch]@1
    int v20; // [sp+60h] [bp-8h]@1
    char v21; // [sp+67h] [bp-1h]@1

    v1 = CNetMsg::__rs(a1, &v21);
    v2 = CNetMsg::__rs(v1, &v20);
    v3 = CNetMsg::__rs(v2, &v19);
    v4 = CNetMsg::__rs(v3, &src);
    v5 = CNetMsg::__rs(v4, &v17);
    v6 = CNetMsg::__rs(v5, &dest);
    CNetMsg::__rs(v6, &v15);
    result = CPCList::Find(gserver.Unk24, v20);
    v14 = result;
    if(result)
    {
        result = **(_DWORD **)(v14 + 408);
        if(result == v19)
        {
            if(v21)
            {
                CNetMsg::CNetMsg((int)&v13);
                v11 = CServer::FindZone((int)&gserver, src);
                v12 = 72 * v11 + gserver.Unk452196;
                if(v11 != -1)
                {
                    v10 = *(_DWORD *)(v14 + 412);
                    CCharacter::SendDisappearAllInCell(v14);
                    CArea::CharFromCell(v10, v14);
                    if(*(_DWORD *)(*(_DWORD *)(v14 + 408) + 40) > 1)
                        CZone::SetDisableArea(*(_DWORD *)(v14 + 408), *(_DWORD *)(*(_DWORD *)(v14 + 412) + 8));
                    if(*(_DWORD *)(v14 + 408) != v12 && *(_DWORD *)(v14 + 1368))
                    {
                        CNetMsg::CNetMsg((int)&v9);
                        v8 = CParty::GetRequest(*(_DWORD *)(v14 + 1368));
                        if(v8 == v14)
                            PartyMsg((int)&v9, 2);
                        else
                            PartyMsg((int)&v9, 6);
                        do_Party(v14, (int)&v9);
                        CNetMsg::_CNetMsg((int)&v9, 2);
                    }
                    GoZoneMsg((int)&v13, src, 0, (char *)(v12 + 5), *(_WORD *)(v12 + 26));
                    if(*(_DWORD *)(v14 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(v14 + 768), (int)&v13);
                    *(_DWORD *)(v14 + 408) = v12;
                    *(_DWORD *)(v14 + 412) = 0;
                    *(_BYTE *)(v14 + 136) = v17;
                    *(_DWORD *)(v14 + 132) = 0;
                    *(float *)(v14 + 120) = dest;
                    *(float *)(v14 + 124) = v15;
                    *(_BYTE *)(*(_DWORD *)(v14 + 768) + 363) = 1;
                }
                result = CNetMsg::_CNetMsg((int)&v13, 2);
            }
            else
            {
                CNetMsg::CNetMsg((int)&v9);
                SysMsg((int)&v9, 22);
                if(*(_DWORD *)(v14 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(v14 + 768), (int)&v9);
                result = CNetMsg::_CNetMsg((int)&v9, 2);
            }
        }
    }
    return result;
}

//----- (08083100) --------------------------------------------------------
int __cdecl ProcHelperGuildCreateRep(int a1)
{
    int v1; // eax@1
    int result; // eax@1
    int v3; // [sp+8h] [bp-20h]@2
    int v4; // [sp+1Ch] [bp-Ch]@1
    char v5; // [sp+23h] [bp-5h]@1
    int dest; // [sp+24h] [bp-4h]@1

    v1 = CNetMsg::__rs(a1, &dest);
    CNetMsg::__rs(v1, &v5);
    result = CPCList::Find(gserver.Unk24, dest);
    v4 = result;
    if(result)
    {
        CNetMsg::CNetMsg((int)&v3);
        if(v5)
        {
            GuildErrorMsg((int)&v3, v5);
        }
        else
        {
            if(CItem::Count(*(_DWORD *)(v4 + 1280)) <= 10000)
            {
                ItemDeleteMsg((int)&v3, *(_DWORD *)(v4 + 1280));
                if(*(_DWORD *)(v4 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(v4 + 768), (int)&v3);
                CPC::AddMoney(v4, -10000LL);
            }
            else
            {
                CPC::AddMoney(v4, -10000LL);
                ItemUpdateMsg((int)&v3, *(_DWORD *)(v4 + 1280), -10000LL);
                if(*(_DWORD *)(v4 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(v4 + 768), (int)&v3);
            }
            *(_DWORD *)(v4 + 72) -= 100000;
            CPC::CalcStatus(v4, 1);
            CPC::SaveNow(v4, 0);
            GuildErrorMsg((int)&v3, 12);
        }
        if(*(_DWORD *)(v4 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(v4 + 768), (int)&v3);
        CDescriptor::WaitHelperReply(*(_DWORD *)(v4 + 768), 0);
        result = CNetMsg::_CNetMsg((int)&v3, 2);
    }
    return result;
}

//----- (08083340) --------------------------------------------------------
int __cdecl ProcHelperGuildCreateNotify(int a1)
{
    int v1; // eax@1
    int v2; // eax@1
    int v3; // eax@1
    int v4; // eax@1
    int result; // eax@1
    int v6; // eax@2
    int v7; // eax@2
    int v8; // [sp+8h] [bp-90h]@2
    int v9; // [sp+1Ch] [bp-7Ch]@1
    int v10; // [sp+20h] [bp-78h]@1
    int v11; // [sp+24h] [bp-74h]@1
    int v12; // [sp+58h] [bp-40h]@1
    char src; // [sp+5Ch] [bp-3Ch]@1
    int v14; // [sp+90h] [bp-8h]@1
    unsigned int dest; // [sp+94h] [bp-4h]@1

    v1 = CNetMsg::__rs(a1, &dest);
    v2 = CNetMsg::__rs(v1, &v14);
    v3 = CNetMsg::__rs(v2, &src);
    v4 = CNetMsg::__rs(v3, &v12);
    CNetMsg::__rs(v4, &v11);
    v10 = CGuildList::create(dest, &src, v12, (const char *)&v11);
    CGuild::level(v10, v14);
    CGuildList::add(135695132, v10);
    result = CPCList::Find(gserver.Unk24, v12);
    v9 = result;
    if(result)
    {
        v6 = CGuild::findmember(v10, v12, 0);
        CGuildMember::online(v6, 1);
        v7 = CGuild::findmember(v10, v12, 0);
        CGuildMember::SetPC(v7, v9);
        CNetMsg::CNetMsg((int)&v8);
        GuildInfoMsg((int)&v8, v9);
        if(*(_DWORD *)(v9 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(v9 + 768), (int)&v8);
        GuildListMsg((int)&v8, v9, 1);
        if(*(_DWORD *)(v9 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(v9 + 768), (int)&v8);
        GuildListMsg((int)&v8, v9, 0);
        if(*(_DWORD *)(v9 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(v9 + 768), (int)&v8);
        GuildInfoChangeMsg((int)&v8, *(_DWORD *)(v9 + 4), dest, &src, 0);
        CArea::SendToCell(*(_DWORD *)(v9 + 412), (int)&v8, v9, 0, 4);
        result = CNetMsg::_CNetMsg((int)&v8, 2);
    }
    return result;
}
// 8071B90: using guessed type _DWORD __cdecl CGuild__findmember(_DWORD, _DWORD, char);

//----- (080835D0) --------------------------------------------------------
int __cdecl ProcHelperGuildOnlineNotify(int a1)
{
    int v1; // eax@1
    int v2; // eax@1
    int result; // eax@1
    char v4; // [sp+Ch] [bp-2Ch]@6
    int v5; // [sp+20h] [bp-18h]@4
    int v6; // [sp+24h] [bp-14h]@2
    int v7; // [sp+28h] [bp-10h]@1
    char v8; // [sp+2Fh] [bp-9h]@1
    int v9; // [sp+30h] [bp-8h]@1
    int dest; // [sp+34h] [bp-4h]@1

    v1 = CNetMsg::__rs(a1, &dest);
    v2 = CNetMsg::__rs(v1, &v9);
    CNetMsg::__rs(v2, &v8);
    result = CGuildList::findguild((int *)&unk_8168B1C, dest);
    v7 = result;
    if(result)
    {
        result = CGuild::findmember(v7, v9, 0);
        v6 = result;
        if(result)
        {
            CGuildMember::online(v6, v8);
            CGuildMember::SetPC(v6, 0);
            if(v8)
            {
                v5 = CPCList::Find(gserver.Unk24, v9);
                if(v5)
                    CGuildMember::SetPC(v6, v5);
            }
            CNetMsg::CNetMsg((int)&v4);
            GuildOnlineMsg((int)&v4, v6);
            CGuild::SendToAll(v7, (int)&v4);
            result = CNetMsg::_CNetMsg((int)&v4, 2);
        }
    }
    return result;
}
// 8071B90: using guessed type _DWORD __cdecl CGuild__findmember(_DWORD, _DWORD, char);

//----- (08083740) --------------------------------------------------------
int __cdecl ProcHelperGuildMemberList(int a1)
{
    int v1; // eax@1
    int result; // eax@2
    int v3; // eax@5
    int v4; // eax@5
    int v5; // eax@5
    int v6; // eax@10
    int v7; // [sp+8h] [bp-70h]@10
    int v8; // [sp+Ch] [bp-6Ch]@10
    int v9; // [sp+10h] [bp-68h]@5
    int i; // [sp+14h] [bp-64h]@3
    int v11; // [sp+18h] [bp-60h]@1
    char v12; // [sp+1Fh] [bp-59h]@5
    int v13; // [sp+20h] [bp-58h]@5
    char src; // [sp+24h] [bp-54h]@5
    int v15; // [sp+58h] [bp-20h]@5
    int v16; // [sp+5Ch] [bp-1Ch]@1
    int dest; // [sp+60h] [bp-18h]@1
    char v18; // [sp+64h] [bp-14h]@1

    CNetMsg::CNetMsg((int)&v18);
    v1 = CNetMsg::__rs(a1, &dest);
    CNetMsg::__rs(v1, &v16);
    v11 = CGuildList::findguild((int *)&unk_8168B1C, dest);
    if(v11)
    {
        for(i = 0; i < v16; ++i)
        {
            v3 = CNetMsg::__rs(a1, &v15);
            v4 = CNetMsg::__rs(v3, &src);
            v5 = CNetMsg::__rs(v4, &v13);
            CNetMsg::__rs(v5, &v12);
            v9 = CGuild::addmember(v11, v15, &src);
            if(v13)
            {
                if(v13 == 1)
                    CGuild::appoint(v11, v9);
            }
            else
            {
                CGuild::changeboss(v11, v9);
            }
            v8 = CGuild::member(v11, v9);
            CGuildMember::online(v8, v12);
            v6 = CGuildMember::charindex(v8);
            v7 = CPCList::Find(gserver.Unk24, v6);
            if(v7)
            {
                CGuildMember::online(v8, 1);
                CGuildMember::SetPC(v8, v7);
                HelperGuildOnline((int)&v18, v8);
                if(!gserver.Unk452130 && gserver.Unk20 && !gserver.Unk20->Unk361)
                {
                    if(gserver.Unk20)
                        CDescriptor::WriteToOutput(gserver.Unk20, (int)&v18);
                }
            }
            else
            {
                CGuildMember::SetPC(v8, 0);
            }
        }
        result = CNetMsg::_CNetMsg((int)&v18, 2);
    }
    else
    {
        result = CNetMsg::_CNetMsg((int)&v18, 2);
    }
    return result;
}

//----- (080839B0) --------------------------------------------------------
char __cdecl ProcHelperGuildLoadRep(int a1)
{
    int v1; // eax@1
    int v2; // eax@1
    int v3; // eax@1
    int v5; // [sp+8h] [bp-40h]@1
    char v6; // [sp+Fh] [bp-39h]@1
    int dest; // [sp+10h] [bp-38h]@1
    char s2; // [sp+14h] [bp-34h]@1

    v1 = CNetMsg::__rs(a1, &s2);
    v2 = CNetMsg::__rs(v1, &dest);
    CNetMsg::__rs(v2, &v6);
    v3 = CServer::FindConnectIdName((int)&gserver, &s2, 0);
    v5 = v3;
    if(v3)
    {
        v3 = *(_DWORD *)(*(_DWORD *)(v3 + 372) + 4);
        if(v3 == dest)
            LOBYTE(v3) = CDescriptor::WaitHelperReply(v5, 0);
    }
    return v3;
}

//----- (08083A40) --------------------------------------------------------
int __cdecl ProcHelperGuildLevelUpRep(int a1)
{
    int v1; // eax@1
    int v2; // eax@1
    int result; // eax@1
    int v4; // eax@5
    signed int v5; // [sp+18h] [bp-38h]@5
    __int64 v6; // [sp+1Ch] [bp-34h]@5
    int v7; // [sp+28h] [bp-28h]@4
    int v8; // [sp+3Ch] [bp-14h]@1
    int v9; // [sp+40h] [bp-10h]@1
    char v10; // [sp+47h] [bp-9h]@1
    int v11; // [sp+48h] [bp-8h]@1
    int dest; // [sp+4Ch] [bp-4h]@1

    v1 = CNetMsg::__rs(a1, &dest);
    v2 = CNetMsg::__rs(v1, &v11);
    CNetMsg::__rs(v2, &v10);
    v9 = CGuildList::findguild((int *)&unk_8168B1C, dest);
    result = CPCList::Find(gserver.Unk24, v11);
    v8 = result;
    if(result && v9)
    {
        CNetMsg::CNetMsg((int)&v7);
        if(v10)
        {
            GuildErrorMsg((int)&v7, v10);
        }
        else
        {
            v6 = 2147483647LL;
            v5 = 2147483647;
            v4 = CGuild::level(v9);
            if(v4 == 3)
            {
                v6 = 250000LL;
                v5 = 60;
            }
            else
            {
                if(v4 > 3)
                {
                    if(v4 == 4)
                    {
                        v6 = 500000LL;
                        v5 = 120;
                    }
                    else
                    {
                        if(v4 == 5)
                        {
                            v6 = 1000000LL;
                            v5 = 240;
                        }
                    }
                }
                else
                {
                    if(v4 == 2)
                    {
                        v6 = 50000LL;
                        v5 = 30;
                    }
                }
            }
            if(CItem::Count(*(_DWORD *)(v8 + 1280)) <= v6)
            {
                ItemDeleteMsg((int)&v7, *(_DWORD *)(v8 + 1280));
                if(*(_DWORD *)(v8 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(v8 + 768), (int)&v7);
                CPC::AddMoney(v8, -v6);
            }
            else
            {
                CPC::AddMoney(v8, -v6);
                ItemUpdateMsg((int)&v7, *(_DWORD *)(v8 + 1280), -v6);
                if(*(_DWORD *)(v8 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(v8 + 768), (int)&v7);
            }
            *(_DWORD *)(v8 + 72) -= 10000 * v5;
            CPC::CalcStatus(v8, 1);
            CPC::SaveNow(v8, 0);
            GuildErrorMsg((int)&v7, 13);
        }
        if(*(_DWORD *)(v8 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(v8 + 768), (int)&v7);
        CDescriptor::WaitHelperReply(*(_DWORD *)(v8 + 768), 0);
        result = CNetMsg::_CNetMsg((int)&v7, 2);
    }
    return result;
}

//----- (08083DC0) --------------------------------------------------------
int __cdecl ProcHelperGuildLevelUpNotify(int a1)
{
    int v1; // eax@1
    int result; // eax@1
    int v3; // [sp+8h] [bp-20h]@2
    int v4; // [sp+1Ch] [bp-Ch]@1
    int v5; // [sp+20h] [bp-8h]@1
    unsigned int dest; // [sp+24h] [bp-4h]@1

    v1 = CNetMsg::__rs(a1, &dest);
    CNetMsg::__rs(v1, &v5);
    result = CGuildList::findguild((int *)&unk_8168B1C, dest);
    v4 = result;
    if(result)
    {
        CGuild::level(v4, v5);
        CNetMsg::CNetMsg((int)&v3);
        GuildLevelInfoMsg((int)&v3, dest, v5);
        CGuild::SendToAll(v4, (int)&v3);
        result = CNetMsg::_CNetMsg((int)&v3, 2);
    }
    return result;
}

//----- (08083EA0) --------------------------------------------------------
int __cdecl ProcHelperGuildBreakUpRep(int a1)
{
    int v1; // eax@1
    int v3; // [sp+8h] [bp-20h]@1
    char v4; // [sp+Fh] [bp-19h]@1
    int dest; // [sp+10h] [bp-18h]@1
    char v6; // [sp+14h] [bp-14h]@1

    CNetMsg::CNetMsg((int)&v6);
    v1 = CNetMsg::__rs(a1, &dest);
    CNetMsg::__rs(v1, &v4);
    v3 = CPCList::Find(gserver.Unk24, dest);
    if(v3)
    {
        if(v4)
            GuildErrorMsg((int)&v6, v4);
        else
            GuildErrorMsg((int)&v6, 14);
        if(*(_DWORD *)(v3 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(v3 + 768), (int)&v6);
        CDescriptor::WaitHelperReply(*(_DWORD *)(v3 + 768), 0);
    }
    return CNetMsg::_CNetMsg((int)&v6, 2);
}

//----- (08083FC0) --------------------------------------------------------
int __cdecl ProcHelperGuildBreakUpNotify(int a1)
{
    int v1; // ST10_4@1
    int v2; // eax@1
    int v4; // [sp+Ch] [bp-1Ch]@1
    int v5; // [sp+20h] [bp-8h]@1
    int dest; // [sp+24h] [bp-4h]@1

    CNetMsg::__rs(a1, &dest);
    v5 = CGuildList::findguild((int *)&unk_8168B1C, dest);
    CNetMsg::CNetMsg((int)&v4);
    v1 = CGuild::name(v5);
    v2 = CGuild::index(v5);
    GuildBreakUpNotifyMsg((int)&v4, v2, (char *)v1);
    CPCList::SendToAll(gserver.Unk24, (int)&v4);
    CGuildList::Remove(135695132, v5);
    return CNetMsg::_CNetMsg((int)&v4, 2);
}

//----- (080840B0) --------------------------------------------------------
int __cdecl ProcHelperGuildMemberAddNotify(int a1)
{
    int v1; // eax@1
    int v2; // eax@1
    int v3; // eax@1
    int result; // eax@2
    int v5; // ST24_4@17
    int v6; // eax@17
    int v7; // [sp+14h] [bp-64h]@5
    int v8; // [sp+18h] [bp-60h]@5
    int v9; // [sp+1Ch] [bp-5Ch]@3
    int v10; // [sp+20h] [bp-58h]@1
    char v11; // [sp+24h] [bp-54h]@1
    char src; // [sp+28h] [bp-50h]@1
    int v13; // [sp+5Ch] [bp-1Ch]@1
    unsigned int dest; // [sp+60h] [bp-18h]@1
    int v15; // [sp+64h] [bp-14h]@1

    CNetMsg::CNetMsg((int)&v15);
    v1 = CNetMsg::__rs(a1, &dest);
    v2 = CNetMsg::__rs(v1, &v13);
    v3 = CNetMsg::__rs(v2, &src);
    CNetMsg::__rs(v3, &v11);
    v10 = CGuildList::findguild((int *)&unk_8168B1C, dest);
    if(v10)
    {
        v9 = CGuild::addmember(v10, v13, &src);
        if(v9 == -1)
        {
            result = CNetMsg::_CNetMsg((int)&v15, 2);
        }
        else
        {
            v8 = CGuild::member(v10, v9);
            CGuildMember::online(v8, 0);
            GuildMemberAddMsg((int)&v15, dest, v13, &src);
            CGuild::SendToAll(v10, (int)&v15);
            v7 = CPCList::Find(gserver.Unk24, v13);
            if(v7)
            {
                CGuildMember::online(v8, 1);
                CGuildMember::SetPC(v8, v7);
                *(_DWORD *)(v7 + 2376) = 0;
                GuildInfoMsg((int)&v15, v7);
                if(*(_DWORD *)(v7 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(v7 + 768), (int)&v15);
                GuildListMsg((int)&v15, v7, 1);
                if(*(_DWORD *)(v7 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(v7 + 768), (int)&v15);
                GuildListMsg((int)&v15, v7, 0);
                if(*(_DWORD *)(v7 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(v7 + 768), (int)&v15);
                HelperGuildOnline((int)&v15, v8);
                if(!gserver.Unk452130 && gserver.Unk20 && !gserver.Unk20->Unk361)
                {
                    if(gserver.Unk20)
                        CDescriptor::WriteToOutput(gserver.Unk20, (int)&v15);
                }
                v5 = CGuildMember::pos(v8);
                v6 = CGuild::name(v10);
                GuildInfoChangeMsg((int)&v15, v13, dest, (char *)v6, v5);
                CArea::SendToCell(*(_DWORD *)(v7 + 412), (int)&v15, v7, 0, 4);
            }
            else
            {
                CGuildMember::SetPC(v8, 0);
            }
            result = CNetMsg::_CNetMsg((int)&v15, 2);
        }
    }
    else
    {
        result = CNetMsg::_CNetMsg((int)&v15, 2);
    }
    return result;
}

//----- (080843F0) --------------------------------------------------------
int __cdecl ProcHelperGuildMemberAddRep(int a1)
{
    int v1; // eax@1
    int v2; // eax@1
    int v3; // eax@1
    int v5; // [sp+Ch] [bp-2Ch]@1
    int v6; // [sp+10h] [bp-28h]@1
    char v7; // [sp+17h] [bp-21h]@1
    int v8; // [sp+18h] [bp-20h]@1
    int v9; // [sp+1Ch] [bp-1Ch]@1
    char dest; // [sp+20h] [bp-18h]@1
    char v11; // [sp+24h] [bp-14h]@1

    CNetMsg::CNetMsg((int)&v11);
    v1 = CNetMsg::__rs(a1, &dest);
    v2 = CNetMsg::__rs(v1, &v9);
    v3 = CNetMsg::__rs(v2, &v8);
    CNetMsg::__rs(v3, &v7);
    v6 = CPCList::Find(gserver.Unk24, v9);
    v5 = CPCList::Find(gserver.Unk24, v8);
    if(v7)
        GuildErrorMsg((int)&v11, v7);
    else
        GuildErrorMsg((int)&v11, 19);
    if(v5)
    {
        if(*(_DWORD *)(v5 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(v5 + 768), (int)&v11);
        *(_DWORD *)(v5 + 2372) = 0;
    }
    if(v6)
        *(_DWORD *)(v6 + 2372) = 0;
    CDescriptor::WaitHelperReply(*(_DWORD *)(v6 + 768), 0);
    CDescriptor::WaitHelperReply(*(_DWORD *)(v5 + 768), 0);
    return CNetMsg::_CNetMsg((int)&v11, 2);
}

//----- (08084580) --------------------------------------------------------
int __cdecl ProcHelperGuildMemberOutNotify(int a1)
{
    int v1; // eax@1
    int v2; // eax@1
    int result; // eax@2
    int v4; // eax@6
    int v5; // ST20_4@6
    int v6; // eax@6
    int v7; // esi@6
    int v8; // eax@6
    time_t timer; // [sp+28h] [bp-5Ch]@6
    int v10; // [sp+2Ch] [bp-58h]@3
    int v11; // [sp+30h] [bp-54h]@1
    int v12; // [sp+34h] [bp-50h]@1
    int v13; // [sp+68h] [bp-1Ch]@1
    unsigned int dest; // [sp+6Ch] [bp-18h]@1
    int v15; // [sp+70h] [bp-14h]@1

    CNetMsg::CNetMsg((int)&v15);
    v1 = CNetMsg::__rs(a1, &dest);
    v2 = CNetMsg::__rs(v1, &v13);
    CNetMsg::__rs(v2, &v12);
    v11 = CGuildList::findguild((int *)&unk_8168B1C, dest);
    if(v11)
    {
        v10 = CGuild::findmember(v11, v13, 0);
        if(v10)
        {
            GuildMemberOutMsg((int)&v15, dest, v13, (char *)&v12);
            CGuild::SendToAll(v11, (int)&v15);
            if(CGuildMember::GetPC(v10))
            {
                v4 = CGuildMember::charindex(v10);
                GuildInfoChangeMsg((int)&v15, v4, 0xFFFFFFFFu, (char *)&unk_80D0B8C, 0x63u);
                v5 = CGuildMember::GetPC(v10);
                v6 = CGuildMember::GetPC(v10);
                CArea::SendToCell(*(_DWORD *)(v6 + 412), (int)&v15, v5, 0, 4);
                v7 = CGuildMember::GetPC(v10);
                *(_DWORD *)(v7 + 2376) = time(&timer) / 86400;
                v8 = CGuildMember::GetPC(v10);
                CPC::SaveNow(v8, 0);
            }
            CGuild::removemember(v11, v10);
            result = CNetMsg::_CNetMsg((int)&v15, 2);
        }
        else
        {
            result = CNetMsg::_CNetMsg((int)&v15, 2);
        }
    }
    else
    {
        result = CNetMsg::_CNetMsg((int)&v15, 2);
    }
    return result;
}
// 8071B90: using guessed type _DWORD __cdecl CGuild__findmember(_DWORD, _DWORD, char);

//----- (080847D0) --------------------------------------------------------
int __cdecl ProcHelperGuildMemberOutRep(int a1)
{
    int v1; // eax@1
    int v2; // eax@1
    int v4; // [sp+14h] [bp-24h]@1
    char v5; // [sp+1Bh] [bp-1Dh]@1
    int v6; // [sp+1Ch] [bp-1Ch]@1
    char dest; // [sp+20h] [bp-18h]@1
    char v8; // [sp+24h] [bp-14h]@1

    CNetMsg::CNetMsg((int)&v8);
    v1 = CNetMsg::__rs(a1, &dest);
    v2 = CNetMsg::__rs(v1, &v6);
    CNetMsg::__rs(v2, &v5);
    v4 = CPCList::Find(gserver.Unk24, v6);
    if(v4)
    {
        if(v5)
            GuildErrorMsg((int)&v8, v5);
        else
            GuildErrorMsg((int)&v8, 21);
        if(*(_DWORD *)(v4 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(v4 + 768), (int)&v8);
        CDescriptor::WaitHelperReply(*(_DWORD *)(v4 + 768), 0);
    }
    return CNetMsg::_CNetMsg((int)&v8, 2);
}

//----- (08084900) --------------------------------------------------------
int __cdecl ProcHelperGuildMemberKickRep(int a1)
{
    int v1; // eax@1
    int v2; // eax@1
    int v3; // eax@1
    int v5; // [sp+10h] [bp-28h]@1
    char v6; // [sp+17h] [bp-21h]@1
    char v7; // [sp+18h] [bp-20h]@1
    int v8; // [sp+1Ch] [bp-1Ch]@1
    char dest; // [sp+20h] [bp-18h]@1
    char v10; // [sp+24h] [bp-14h]@1

    CNetMsg::CNetMsg((int)&v10);
    v1 = CNetMsg::__rs(a1, &dest);
    v2 = CNetMsg::__rs(v1, &v8);
    v3 = CNetMsg::__rs(v2, &v7);
    CNetMsg::__rs(v3, &v6);
    v5 = CPCList::Find(gserver.Unk24, v8);
    if(v5)
    {
        if(v6)
            GuildErrorMsg((int)&v10, v6);
        else
            GuildErrorMsg((int)&v10, 24);
        if(*(_DWORD *)(v5 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(v5 + 768), (int)&v10);
        CDescriptor::WaitHelperReply(*(_DWORD *)(v5 + 768), 0);
    }
    return CNetMsg::_CNetMsg((int)&v10, 2);
}

//----- (08084A40) --------------------------------------------------------
int __cdecl ProcHelperGuildMemberKickNotify(int a1)
{
    int v1; // eax@1
    int v2; // eax@1
    int result; // eax@2
    int v4; // eax@5
    int v5; // [sp+Ch] [bp-2Ch]@5
    int v6; // [sp+10h] [bp-28h]@3
    int v7; // [sp+14h] [bp-24h]@1
    int src; // [sp+18h] [bp-20h]@1
    int v9; // [sp+1Ch] [bp-1Ch]@1
    unsigned int dest; // [sp+20h] [bp-18h]@1
    int v11; // [sp+24h] [bp-14h]@1

    CNetMsg::CNetMsg((int)&v11);
    v1 = CNetMsg::__rs(a1, &dest);
    v2 = CNetMsg::__rs(v1, &v9);
    CNetMsg::__rs(v2, &src);
    v7 = CGuildList::findguild((int *)&unk_8168B1C, dest);
    if(v7)
    {
        v6 = CGuild::findmember(v7, src, 0);
        if(v6)
        {
            v4 = CGuildMember::name(v6);
            GuildMemberKickMsg((int)&v11, dest, v9, src, (char *)v4);
            CGuild::SendToAll(v7, (int)&v11);
            CGuild::removemember(v7, v6);
            v5 = CPCList::Find(gserver.Unk24, src);
            if(v5)
            {
                GuildInfoChangeMsg((int)&v11, src, 0xFFFFFFFFu, (char *)&unk_80D0B8C, 0x63u);
                CArea::SendToCell(*(_DWORD *)(v5 + 412), (int)&v11, v5, 0, 4);
            }
            result = CNetMsg::_CNetMsg((int)&v11, 2);
        }
        else
        {
            result = CNetMsg::_CNetMsg((int)&v11, 2);
        }
    }
    else
    {
        result = CNetMsg::_CNetMsg((int)&v11, 2);
    }
    return result;
}
// 8071B90: using guessed type _DWORD __cdecl CGuild__findmember(_DWORD, _DWORD, char);

//----- (08084C10) --------------------------------------------------------
int __cdecl ProcHelperGuildChangeBossNotify(int a1)
{
    int v1; // eax@1
    int v2; // eax@1
    int result; // eax@2
    int v4; // eax@5
    int v5; // eax@6
    int v6; // ST20_4@6
    int v7; // eax@6
    int v8; // eax@10
    int v9; // ST20_4@10
    int v10; // eax@10
    int v11; // [sp+Ch] [bp-2Ch]@7
    int v12; // [sp+10h] [bp-28h]@3
    int v13; // [sp+14h] [bp-24h]@1
    uint32_t src; // [sp+18h] [bp-20h]@1
    int v15; // [sp+1Ch] [bp-1Ch]@1
    unsigned int dest; // [sp+20h] [bp-18h]@1
    int v17; // [sp+24h] [bp-14h]@1

    CNetMsg::CNetMsg((int)&v17);
    v1 = CNetMsg::__rs(a1, &dest);
    v2 = CNetMsg::__rs(v1, &v15);
    CNetMsg::__rs(v2, &src);
    v13 = CGuildList::findguild((int *)&unk_8168B1C, dest);
    if(v13)
    {
        v12 = CGuild::findmember(v13, src, 0);
        if(v12)
        {
            v4 = CGuildMember::listindex(v12);
            CGuild::changeboss(v13, v4);
            GuildChangeBossMsg((int)&v17, dest, v15, src);
            CGuild::SendToAll(v13, (int)&v17);
            if(CGuildMember::GetPC(v12))
            {
                v5 = CGuild::name(v13);
                GuildInfoChangeMsg((int)&v17, src, dest, (char *)v5, 0);
                v6 = CGuildMember::GetPC(v12);
                v7 = CGuildMember::GetPC(v12);
                CArea::SendToCell(*(_DWORD *)(v7 + 412), (int)&v17, v6, 0, 4);
            }
            v11 = CGuild::findmember(v13, v15, 0);
            if(v11)
            {
                if(CGuildMember::GetPC(v11))
                {
                    v8 = CGuild::name(v13);
                    GuildInfoChangeMsg((int)&v17, v15, dest, (char *)v8, 2u);
                    v9 = CGuildMember::GetPC(v11);
                    v10 = CGuildMember::GetPC(v11);
                    CArea::SendToCell(*(_DWORD *)(v10 + 412), (int)&v17, v9, 0, 4);
                }
                result = CNetMsg::_CNetMsg((int)&v17, 2);
            }
            else
            {
                result = CNetMsg::_CNetMsg((int)&v17, 2);
            }
        }
        else
        {
            result = CNetMsg::_CNetMsg((int)&v17, 2);
        }
    }
    else
    {
        result = CNetMsg::_CNetMsg((int)&v17, 2);
    }
    return result;
}
// 8071B90: using guessed type _DWORD __cdecl CGuild__findmember(_DWORD, _DWORD, char);

//----- (08084EC0) --------------------------------------------------------
int __cdecl ProcHelperGuildChangeBossRep(int a1)
{
    int v1; // eax@1
    int v2; // eax@1
    int v3; // eax@1
    int v5; // [sp+10h] [bp-28h]@1
    char v6; // [sp+17h] [bp-21h]@1
    char v7; // [sp+18h] [bp-20h]@1
    int v8; // [sp+1Ch] [bp-1Ch]@1
    char dest; // [sp+20h] [bp-18h]@1
    char v10; // [sp+24h] [bp-14h]@1

    CNetMsg::CNetMsg((int)&v10);
    v1 = CNetMsg::__rs(a1, &dest);
    v2 = CNetMsg::__rs(v1, &v8);
    v3 = CNetMsg::__rs(v2, &v7);
    CNetMsg::__rs(v3, &v6);
    v5 = CPCList::Find(gserver.Unk24, v8);
    if(v5)
    {
        if(v6)
            GuildErrorMsg((int)&v10, v6);
        else
            GuildErrorMsg((int)&v10, 25);
        if(*(_DWORD *)(v5 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(v5 + 768), (int)&v10);
        CDescriptor::WaitHelperReply(*(_DWORD *)(v5 + 768), 0);
    }
    return CNetMsg::_CNetMsg((int)&v10, 2);
}

//----- (08085000) --------------------------------------------------------
int __cdecl ProcHelperGuildAppointOfficerRep(int a1)
{
    int v1; // eax@1
    int v2; // eax@1
    int v3; // eax@1
    int v5; // [sp+10h] [bp-28h]@1
    char v6; // [sp+17h] [bp-21h]@1
    char v7; // [sp+18h] [bp-20h]@1
    int v8; // [sp+1Ch] [bp-1Ch]@1
    char dest; // [sp+20h] [bp-18h]@1
    char v10; // [sp+24h] [bp-14h]@1

    CNetMsg::CNetMsg((int)&v10);
    v1 = CNetMsg::__rs(a1, &dest);
    v2 = CNetMsg::__rs(v1, &v8);
    v3 = CNetMsg::__rs(v2, &v7);
    CNetMsg::__rs(v3, &v6);
    v5 = CPCList::Find(gserver.Unk24, v8);
    if(v5)
    {
        if(v6)
            GuildErrorMsg((int)&v10, v6);
        else
            GuildErrorMsg((int)&v10, 27);
        if(*(_DWORD *)(v5 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(v5 + 768), (int)&v10);
        CDescriptor::WaitHelperReply(*(_DWORD *)(v5 + 768), 0);
    }
    return CNetMsg::_CNetMsg((int)&v10, 2);
}*/

void ProcHelperGuildAppointOfficerNotify(CNetMsg &a1)
{
    CGuildMember *v8; // [sp+10h] [bp-28h]@3
    CGuild *v9; // [sp+14h] [bp-24h]@1
    uint32_t src; // [sp+18h] [bp-20h]@1
    char v11; // [sp+1Ch] [bp-1Ch]@1
    unsigned int dest; // [sp+20h] [bp-18h]@1
    CNetMsg v13;

    a1.__rs(dest);
    a1.__rs(v11);
    a1.__rs(src);

    v9 = gserver.Unk452252.findguild(dest);
    if(!v9) return;

    v8 = v9->findmember(src, 0);
    if(!v8) return;

    v9->appoint(v8->listindex());
    GuildAppointOfficerMsg(dest, src);
    v9->SendToAll(v13);

    if(!v8->GetPC()) return;

    GuildInfoChangeMsg(v13, src, dest, v9->name(), 1);
    v8->GetPC()->Unk412->SendToCell(v13, v8->GetPC(), 0, 4);
}

void ProcHelperGuildChat(CNetMsg &a1)
{
    CGuild *v5; // [sp+14h] [bp-54h]@1
    int v6; // [sp+18h] [bp-50h]@1
    uint32_t src; // [sp+4Ch] [bp-1Ch]@1
    int dest; // [sp+50h] [bp-18h]@1
    CNetMsg v9;

    a1.__rs(dest);
    a1.__rs(src);
    a1.__rs(v6);
    a1.__rs(g_buf);

    SayMsg(v9, 2, src, (char *)&v6, "", g_buf);

    v5 = gserver.Unk452252.findguild(dest);
    if(v5) v5->SendToAll(v9);
}

void ProcHelperGuildFireOfficerRep(CNetMsg &a1)
{
    CPC *v5; // [sp+10h] [bp-28h]@1
    char v6; // [sp+17h] [bp-21h]@1
    char v7; // [sp+18h] [bp-20h]@1
    int v8; // [sp+1Ch] [bp-1Ch]@1
    char dest; // [sp+20h] [bp-18h]@1
    CNetMsg v10;

    a1.__rs(dest);
    a1.__rs(v8);
    a1.__rs(v7);
    a1.__rs(v6);

    v5 = gserver.Unk24.Find(v8);
    if(!v5) return;

    if(v6)
        GuildErrorMsg(v10, v6);
    else
        GuildErrorMsg(v10, 30);

    if(v5->Unk768) v5->Unk768->WriteToOutput(v10);
    v5->Unk768->WaitHelperReply(0);
}

void ProcHelperGuildFireOfficerNotify(CNetMsg &a1)
{
    CGuildMember *v8; // [sp+10h] [bp-28h]@3
    CGuild *v9; // [sp+14h] [bp-24h]@1
    uint32_t src; // [sp+18h] [bp-20h]@1
    char v11; // [sp+1Ch] [bp-1Ch]@1
    unsigned int dest; // [sp+20h] [bp-18h]@1
    CNetMsg v13;
    
    a1.__rs(dest);
    a1.__rs(v11);
    a1.__rs(src);
    
    v9 = gserver.Unk452252.findguild(dest);
    if(!v9) return;

    v8 = v9->findmember(src, 0);
    if(!v8) return;

    v9->fire(v8->listindex());
    GuildFireOfficerMsg(v13, dest, src);
    v9->SendToAll(v13);

    if(!v8->GetPC()) return;

    GuildInfoChangeMsg(v13, src, dest, v9->name(), 2);
    v8->GetPC()->Unk412->SendToCell(v13, v8->GetPC(), 0, 4);
}
