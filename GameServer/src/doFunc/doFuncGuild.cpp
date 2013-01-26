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

#include "../doFunc.h"

void do_Guild(CPC *a1, CNetMsg &a2)
{
    /* TODO */
}

/*void do_Guild(CPC *a1, CNetMsg &a2)
{
    int result; // eax@1
    char dest; // [sp+17h] [bp-1h]@1

    CNetMsg::MoveFirst(a2);
    result = CNetMsg::__rs(a2, &dest);
    switch(dest)
    {
        case 1:
            result = do_GuildCreate(a1, a2);
            break;
        case 5:
            result = do_GuildLevelUp(a1);
            break;
        case 7:
            result = do_GuildBreakUp(a1);
            break;
        case 9:
            result = do_GuildRegistReq(a1, a2);
            break;
        case 0xA:
            result = do_GuildRegistAllow(a1, a2);
            break;
        case 0xB:
            result = do_GuildRegistCancel(a1, a2);
            break;
        case 0xC:
            result = do_GuildOutReq(a1, a2);
            break;
        case 0x10:
            result = do_GuildKick(a1, a2);
            break;
        case 0xD:
            result = do_GuildChangeBoss(a1, a2);
            break;
        case 0xE:
            result = do_GuildAppointOfficer(a1, a2);
            break;
        case 0xF:
            result = do_GuildFireOfficer(a1, a2);
            break;
        default:
            return result;
    }
    return result;
}
// 80A5660: using guessed type _DWORD __cdecl do_GuildLevelUp(_DWORD);
// 80A6210: using guessed type _DWORD __cdecl do_GuildRegistAllow(_DWORD, _DWORD);

//----- (080A5220) --------------------------------------------------------
int __cdecl do_GuildCreate(int a1, int a2)
{
    int result; // eax@5
    size_t v3; // [sp+Ch] [bp-4Ch]@1
    char s; // [sp+10h] [bp-48h]@1
    char v5; // [sp+41h] [bp-17h]@1
    char v6; // [sp+44h] [bp-14h]@1

    CNetMsg::CNetMsg((int)&v6);
    CNetMsg::__rs(a2, g_buf);
    strncpy(&s, g_buf, 0x32u);
    v5 = 0;
    v3 = strlen(&s);
    if((signed int)v3 > 1 && (signed int)v3 <= 16)
    {
        if(strchr(&s, 39) || strchr(&s, 92) || strchr(&s, 34) || strchr(&s, 37) || strchr(&s, 95))
        {
            GuildErrorMsg((int)&v6, 2);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v6);
            result = CNetMsg::_CNetMsg((int)&v6, 2);
        }
        else
        {
            if(*(_DWORD *)(a1 + 60) > 9)
            {
                if(*(_DWORD *)(a1 + 72) > 99999)
                {
                    if(*(_DWORD *)(a1 + 1280) && CItem::Count(*(_DWORD *)(a1 + 1280)) > 9999)
                    {
                        if(!*(_DWORD *)(a1 + 2368) || CGuildMember::pos(*(_DWORD *)(a1 + 2368)))
                        {
                            if(gserver.Unk452130 || !gserver.Unk20 || gserver.Unk20->Unk361)
                            {
                                GuildErrorMsg((int)&v6, 7);
                                if(*(_DWORD *)(a1 + 768))
                                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v6);
                            }
                            else
                            {
                                HelperGuildCreateReqMsg((int)&v6, a1, &s);
                                if(gserver.Unk20)
                                    CDescriptor::WriteToOutput(gserver.Unk20, (int)&v6);
                                CDescriptor::WaitHelperReply(*(_DWORD *)(a1 + 768), 1);
                            }
                            result = CNetMsg::_CNetMsg((int)&v6, 2);
                        }
                        else
                        {
                            GuildErrorMsg((int)&v6, 3);
                            if(*(_DWORD *)(a1 + 768))
                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v6);
                            result = CNetMsg::_CNetMsg((int)&v6, 2);
                        }
                    }
                    else
                    {
                        GuildErrorMsg((int)&v6, 6);
                        if(*(_DWORD *)(a1 + 768))
                            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v6);
                        result = CNetMsg::_CNetMsg((int)&v6, 2);
                    }
                }
                else
                {
                    GuildErrorMsg((int)&v6, 5);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v6);
                    result = CNetMsg::_CNetMsg((int)&v6, 2);
                }
            }
            else
            {
                GuildErrorMsg((int)&v6, 4);
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v6);
                result = CNetMsg::_CNetMsg((int)&v6, 2);
            }
        }
    }
    else
    {
        GuildErrorMsg((int)&v6, 2);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v6);
        result = CNetMsg::_CNetMsg((int)&v6, 2);
    }
    return result;
}

//----- (080A5660) --------------------------------------------------------
#error "80A5B15: positive sp value has been found (funcsize=332)"

//----- (080A5B20) --------------------------------------------------------
int __cdecl do_GuildBreakUp(int a1)
{
    int result; // eax@4
    int v2; // eax@5
    int v3; // eax@5
    char v4; // [sp+14h] [bp-14h]@1

    CNetMsg::CNetMsg((int)&v4);
    if(*(_DWORD *)(a1 + 2368))
    {
        v2 = CGuildMember::guild(*(_DWORD *)(a1 + 2368));
        v3 = CGuild::boss(v2);
        if(CGuildMember::charindex(v3) == *(_DWORD *)(a1 + 4))
        {
            if(gserver.Unk452130 || !gserver.Unk20 || gserver.Unk20->Unk361)
            {
                GuildErrorMsg((int)&v4, 10);
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v4);
            }
            else
            {
                HelperGuildBreakUpReqMsg((int)&v4, a1);
                if(gserver.Unk20)
                    CDescriptor::WriteToOutput(gserver.Unk20, (int)&v4);
                CDescriptor::WaitHelperReply(*(_DWORD *)(a1 + 768), 1);
            }
            result = CNetMsg::_CNetMsg((int)&v4, 2);
        }
        else
        {
            GuildErrorMsg((int)&v4, 10);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v4);
            result = CNetMsg::_CNetMsg((int)&v4, 2);
        }
    }
    else
    {
        GuildErrorMsg((int)&v4, 9);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v4);
        result = CNetMsg::_CNetMsg((int)&v4, 2);
    }
    return result;
}

//----- (080A5D10) --------------------------------------------------------
int __cdecl do_GuildRegistReq(int a1, int a2)
{
    int v2; // eax@1
    int v3; // eax@1
    int result; // eax@5
    int v5; // eax@40
    int v6; // [sp+2Ch] [bp-28h]@15
    time_t timer; // [sp+30h] [bp-24h]@2
    int v8; // [sp+34h] [bp-20h]@1
    int v9; // [sp+38h] [bp-1Ch]@1
    int dest; // [sp+3Ch] [bp-18h]@1
    char v11; // [sp+40h] [bp-14h]@1

    CNetMsg::CNetMsg((int)&v11);
    v2 = CNetMsg::__rs(a2, &dest);
    v3 = CNetMsg::__rs(v2, &v9);
    CNetMsg::__rs(v3, &v8);
    if(*(_DWORD *)(a1 + 2376) && time(&timer) / 86400 < *(_DWORD *)(a1 + 2376) + 7)
    {
        GuildErrorMsg((int)&v11, 31);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v11);
        result = CNetMsg::_CNetMsg((int)&v11, 2);
    }
    else
    {
        if(v9 != *(_DWORD *)(a1 + 4) && v8 == *(_DWORD *)(a1 + 4))
        {
            timer = CGuildList::findguild((int *)&unk_8168B1C, dest);
            if(timer)
            {
                v6 = CGuild::findmember(timer, v9, 0);
                if(v6)
                {
                    if(CGuildMember::pos(v6) == 2)
                    {
                        GuildErrorMsg((int)&v11, 15);
                        if(*(_DWORD *)(a1 + 768))
                            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v11);
                        result = CNetMsg::_CNetMsg((int)&v11, 2);
                    }
                    else
                    {
                        if(CGuildMember::GetPC(v6))
                        {
                            if(*(_DWORD *)(CGuildMember::GetPC(v6) + 2372)
                                && *(_DWORD *)(CGuildMember::GetPC(v6) + 2372) != *(_DWORD *)(a1 + 4))
                            {
                                GuildErrorMsg((int)&v11, 16);
                                if(*(_DWORD *)(a1 + 768))
                                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v11);
                                result = CNetMsg::_CNetMsg((int)&v11, 2);
                            }
                            else
                            {
                                if(*(_DWORD *)(a1 + 2372) && *(_DWORD *)(a1 + 2372) != CGuildMember::charindex(v6))
                                {
                                    GuildErrorMsg((int)&v11, 17);
                                    if(*(_DWORD *)(a1 + 768))
                                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v11);
                                    result = CNetMsg::_CNetMsg((int)&v11, 2);
                                }
                                else
                                {
                                    *(_DWORD *)(CGuildMember::GetPC(v6) + 2372) = *(_DWORD *)(a1 + 4);
                                    *(_DWORD *)(a1 + 2372) = CGuildMember::charindex(v6);
                                    if(*(_DWORD *)(a1 + 768))
                                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), a2);
                                    if(*(_DWORD *)(CGuildMember::GetPC(v6) + 768))
                                    {
                                        v5 = CGuildMember::GetPC(v6);
                                        CDescriptor::WriteToOutput(*(_DWORD *)(v5 + 768), a2);
                                    }
                                    result = CNetMsg::_CNetMsg((int)&v11, 2);
                                }
                            }
                        }
                        else
                        {
                            GuildErrorMsg((int)&v11, 15);
                            if(*(_DWORD *)(a1 + 768))
                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v11);
                            result = CNetMsg::_CNetMsg((int)&v11, 2);
                        }
                    }
                }
                else
                {
                    GuildErrorMsg((int)&v11, 15);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v11);
                    result = CNetMsg::_CNetMsg((int)&v11, 2);
                }
            }
            else
            {
                GuildErrorMsg((int)&v11, 15);
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v11);
                result = CNetMsg::_CNetMsg((int)&v11, 2);
            }
        }
        else
        {
            GuildErrorMsg((int)&v11, 1);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v11);
            result = CNetMsg::_CNetMsg((int)&v11, 2);
        }
    }
    return result;
}
// 8071B90: using guessed type _DWORD __cdecl CGuild__findmember(_DWORD, _DWORD, char);

//----- (080A6210) --------------------------------------------------------
#error "80A68B5: positive sp value has been found (funcsize=468)"

//----- (080A68C0) --------------------------------------------------------
signed int __cdecl do_GuildRegistCancel(signed int a1, int a2)
{
    signed int result; // eax@1
    int v3; // [sp+14h] [bp-4h]@2

    result = a1;
    if(*(_DWORD *)(a1 + 2372))
    {
        v3 = CPCList::Find(gserver.Unk24, *(_DWORD *)(a1 + 2372));
        if(v3)
        {
            if(*(_DWORD *)(v3 + 2372) == *(_DWORD *)(a1 + 4))
            {
                *(_DWORD *)(v3 + 2372) = 0;
                if(*(_DWORD *)(v3 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(v3 + 768), a2);
            }
        }
        *(_DWORD *)(a1 + 2372) = 0;
        result = a1;
        if(*(_DWORD *)(a1 + 768))
            result = CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), a2);
    }
    return result;
}

//----- (080A6980) --------------------------------------------------------
int __cdecl do_GuildOutReq(int a1, int a2)
{
    int result; // eax@4
    int v3; // [sp+8h] [bp-20h]@5
    int v4; // [sp+Ch] [bp-1Ch]@1
    unsigned int dest; // [sp+10h] [bp-18h]@1
    int v6; // [sp+14h] [bp-14h]@1

    CNetMsg::CNetMsg((int)&v6);
    CNetMsg::__rs(a2, &dest);
    v4 = CGuildList::findguild((int *)&unk_8168B1C, dest);
    if(v4)
    {
        v3 = CGuild::findmember(v4, *(_DWORD *)(a1 + 4), 0);
        if(v3)
        {
            if(CGuildMember::pos(v3))
            {
                if(gserver.Unk452130 || !gserver.Unk20 || gserver.Unk20->Unk361)
                {
                    GuildErrorMsg((int)&v6, 7);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v6);
                    result = CNetMsg::_CNetMsg((int)&v6, 2);
                }
                else
                {
                    HelperGuildOutReqMsg((int)&v6, dest, *(_DWORD *)(a1 + 4));
                    if(gserver.Unk20)
                        CDescriptor::WriteToOutput(gserver.Unk20, (int)&v6);
                    CDescriptor::WaitHelperReply(*(_DWORD *)(a1 + 768), 1);
                    result = CNetMsg::_CNetMsg((int)&v6, 2);
                }
            }
            else
            {
                GuildErrorMsg((int)&v6, 20);
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v6);
                result = CNetMsg::_CNetMsg((int)&v6, 2);
            }
        }
        else
        {
            GuildErrorMsg((int)&v6, 9);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v6);
            result = CNetMsg::_CNetMsg((int)&v6, 2);
        }
    }
    else
    {
        GuildErrorMsg((int)&v6, 9);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v6);
        result = CNetMsg::_CNetMsg((int)&v6, 2);
    }
    return result;
}
// 8071B90: using guessed type _DWORD __cdecl CGuild__findmember(_DWORD, _DWORD, char);

//----- (080A6C20) --------------------------------------------------------
int __cdecl do_GuildKick(int a1, int a2)
{
    int v2; // eax@1
    int result; // eax@4
    int v4; // [sp+14h] [bp-24h]@17
    int v5; // [sp+18h] [bp-20h]@1
    int v6; // [sp+1Ch] [bp-1Ch]@1
    unsigned int dest; // [sp+20h] [bp-18h]@1
    int v8; // [sp+24h] [bp-14h]@1

    CNetMsg::CNetMsg((int)&v8);
    v2 = CNetMsg::__rs(a2, &dest);
    CNetMsg::__rs(v2, &v6);
    v5 = CGuildList::findguild((int *)&unk_8168B1C, dest);
    if(v5)
    {
        if(*(_DWORD *)(a1 + 2368))
        {
            if(CGuildMember::guild(*(_DWORD *)(a1 + 2368)) == v5)
            {
                if(CGuildMember::pos(*(_DWORD *)(a1 + 2368)) == 2)
                {
                    GuildErrorMsg((int)&v8, 10);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v8);
                    result = CNetMsg::_CNetMsg((int)&v8, 2);
                }
                else
                {
                    v4 = CGuild::findmember(v5, v6, 0);
                    if(v4)
                    {
                        if(CGuildMember::pos(v4))
                        {
                            if(gserver.Unk452130 || !gserver.Unk20 || gserver.Unk20->Unk361)
                            {
                                GuildErrorMsg((int)&v8, 7);
                                if(*(_DWORD *)(a1 + 768))
                                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v8);
                                result = CNetMsg::_CNetMsg((int)&v8, 2);
                            }
                            else
                            {
                                HelperGuildKickReqMsg((int)&v8, dest, *(_DWORD *)(a1 + 4), v6);
                                if(gserver.Unk20)
                                    CDescriptor::WriteToOutput(gserver.Unk20, (int)&v8);
                                CDescriptor::WaitHelperReply(*(_DWORD *)(a1 + 768), 1);
                                result = CNetMsg::_CNetMsg((int)&v8, 2);
                            }
                        }
                        else
                        {
                            GuildErrorMsg((int)&v8, 23);
                            if(*(_DWORD *)(a1 + 768))
                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v8);
                            result = CNetMsg::_CNetMsg((int)&v8, 2);
                        }
                    }
                    else
                    {
                        GuildErrorMsg((int)&v8, 22);
                        if(*(_DWORD *)(a1 + 768))
                            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v8);
                        result = CNetMsg::_CNetMsg((int)&v8, 2);
                    }
                }
            }
            else
            {
                GuildErrorMsg((int)&v8, 9);
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v8);
                result = CNetMsg::_CNetMsg((int)&v8, 2);
            }
        }
        else
        {
            GuildErrorMsg((int)&v8, 9);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v8);
            result = CNetMsg::_CNetMsg((int)&v8, 2);
        }
    }
    else
    {
        GuildErrorMsg((int)&v8, 22);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v8);
        result = CNetMsg::_CNetMsg((int)&v8, 2);
    }
    return result;
}
// 8071B90: using guessed type _DWORD __cdecl CGuild__findmember(_DWORD, _DWORD, char);

//----- (080A6FF0) --------------------------------------------------------
int __cdecl do_GuildChangeBoss(int a1, int a2)
{
    int v2; // eax@1
    int v3; // eax@1
    int result; // eax@4
    int v5; // [sp+Ch] [bp-2Ch]@17
    int v6; // [sp+10h] [bp-28h]@9
    int v7; // [sp+14h] [bp-24h]@5
    int v8; // [sp+18h] [bp-20h]@1
    int v9; // [sp+1Ch] [bp-1Ch]@1
    unsigned int dest; // [sp+20h] [bp-18h]@1
    int v11; // [sp+24h] [bp-14h]@1

    CNetMsg::CNetMsg((int)&v11);
    v2 = CNetMsg::__rs(a2, &dest);
    v3 = CNetMsg::__rs(v2, &v9);
    CNetMsg::__rs(v3, &v8);
    if(*(_DWORD *)(a1 + 4) == v9)
    {
        v7 = CGuildList::findguild((int *)&unk_8168B1C, dest);
        if(v7)
        {
            v6 = CGuild::findmember(v7, v9, 0);
            if(v6)
            {
                if(CGuildMember::pos(v6))
                {
                    GuildErrorMsg((int)&v11, 10);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v11);
                    result = CNetMsg::_CNetMsg((int)&v11, 2);
                }
                else
                {
                    v5 = CGuild::findmember(v7, v8, 0);
                    if(v5)
                    {
                        if(CGuildMember::pos(v5))
                        {
                            if(gserver.Unk452130 || !gserver.Unk20 || gserver.Unk20->Unk361)
                            {
                                GuildErrorMsg((int)&v11, 7);
                                if(*(_DWORD *)(a1 + 768))
                                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v11);
                                result = CNetMsg::_CNetMsg((int)&v11, 2);
                            }
                            else
                            {
                                HelperGuildChangeBossReqMsg((int)&v11, dest, v9, v8);
                                if(gserver.Unk20)
                                    CDescriptor::WriteToOutput(gserver.Unk20, (int)&v11);
                                CDescriptor::WaitHelperReply(*(_DWORD *)(a1 + 768), 1);
                                result = CNetMsg::_CNetMsg((int)&v11, 2);
                            }
                        }
                        else
                        {
                            GuildErrorMsg((int)&v11, 1);
                            if(*(_DWORD *)(a1 + 768))
                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v11);
                            result = CNetMsg::_CNetMsg((int)&v11, 2);
                        }
                    }
                    else
                    {
                        GuildErrorMsg((int)&v11, 22);
                        if(*(_DWORD *)(a1 + 768))
                            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v11);
                        result = CNetMsg::_CNetMsg((int)&v11, 2);
                    }
                }
            }
            else
            {
                GuildErrorMsg((int)&v11, 10);
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v11);
                result = CNetMsg::_CNetMsg((int)&v11, 2);
            }
        }
        else
        {
            GuildErrorMsg((int)&v11, 9);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v11);
            result = CNetMsg::_CNetMsg((int)&v11, 2);
        }
    }
    else
    {
        GuildErrorMsg((int)&v11, 10);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v11);
        result = CNetMsg::_CNetMsg((int)&v11, 2);
    }
    return result;
}
// 8071B90: using guessed type _DWORD __cdecl CGuild__findmember(_DWORD, _DWORD, char);

//----- (080A73D0) --------------------------------------------------------
int __cdecl do_GuildAppointOfficer(int a1, int a2)
{
    int v2; // eax@1
    int result; // eax@4
    int v4; // [sp+Ch] [bp-2Ch]@21
    int v5; // [sp+10h] [bp-28h]@13
    signed int i; // [sp+14h] [bp-24h]@5
    int v7; // [sp+18h] [bp-20h]@1
    int v8; // [sp+1Ch] [bp-1Ch]@1
    unsigned int dest; // [sp+20h] [bp-18h]@1
    int v10; // [sp+24h] [bp-14h]@1

    CNetMsg::CNetMsg((int)&v10);
    v2 = CNetMsg::__rs(a2, &dest);
    CNetMsg::__rs(v2, &v8);
    v7 = CGuildList::findguild((int *)&unk_8168B1C, dest);
    if(v7)
    {
        for(i = 0; i <= 1 && CGuild::officer(v7, i); ++i)
            ;
        if(i == 2)
        {
            GuildErrorMsg((int)&v10, 28);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v10);
            result = CNetMsg::_CNetMsg((int)&v10, 2);
        }
        else
        {
            v5 = CGuild::findmember(v7, *(_DWORD *)(a1 + 4), 0);
            if(v5)
            {
                if(CGuildMember::pos(v5))
                {
                    GuildErrorMsg((int)&v10, 10);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v10);
                    result = CNetMsg::_CNetMsg((int)&v10, 2);
                }
                else
                {
                    v4 = CGuild::findmember(v7, v8, 0);
                    if(v4)
                    {
                        if(CGuildMember::pos(v4) == 2)
                        {
                            if(gserver.Unk452130 || !gserver.Unk20 || gserver.Unk20->Unk361)
                            {
                                GuildErrorMsg((int)&v10, 7);
                                if(*(_DWORD *)(a1 + 768))
                                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v10);
                                result = CNetMsg::_CNetMsg((int)&v10, 2);
                            }
                            else
                            {
                                HelperGuildAppointOfficerReqMsg((int)&v10, dest, *(_DWORD *)(a1 + 4), v8);
                                if(gserver.Unk20)
                                    CDescriptor::WriteToOutput(gserver.Unk20, (int)&v10);
                                CDescriptor::WaitHelperReply(*(_DWORD *)(a1 + 768), 1);
                                result = CNetMsg::_CNetMsg((int)&v10, 2);
                            }
                        }
                        else
                        {
                            GuildErrorMsg((int)&v10, 26);
                            if(*(_DWORD *)(a1 + 768))
                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v10);
                            result = CNetMsg::_CNetMsg((int)&v10, 2);
                        }
                    }
                    else
                    {
                        GuildErrorMsg((int)&v10, 22);
                        if(*(_DWORD *)(a1 + 768))
                            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v10);
                        result = CNetMsg::_CNetMsg((int)&v10, 2);
                    }
                }
            }
            else
            {
                GuildErrorMsg((int)&v10, 10);
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v10);
                result = CNetMsg::_CNetMsg((int)&v10, 2);
            }
        }
    }
    else
    {
        GuildErrorMsg((int)&v10, 9);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v10);
        result = CNetMsg::_CNetMsg((int)&v10, 2);
    }
    return result;
}
// 8071B90: using guessed type _DWORD __cdecl CGuild__findmember(_DWORD, _DWORD, char);

//----- (080A77E0) --------------------------------------------------------
int __cdecl do_GuildFireOfficer(int a1, int a2)
{
    int v2; // eax@1
    int result; // eax@4
    int v4; // [sp+10h] [bp-28h]@13
    int v5; // [sp+14h] [bp-24h]@5
    int v6; // [sp+18h] [bp-20h]@1
    int v7; // [sp+1Ch] [bp-1Ch]@1
    unsigned int dest; // [sp+20h] [bp-18h]@1
    int v9; // [sp+24h] [bp-14h]@1

    CNetMsg::CNetMsg((int)&v9);
    v2 = CNetMsg::__rs(a2, &dest);
    CNetMsg::__rs(v2, &v7);
    v6 = CGuildList::findguild((int *)&unk_8168B1C, dest);
    if(v6)
    {
        v5 = CGuild::findmember(v6, *(_DWORD *)(a1 + 4), 0);
        if(v5)
        {
            if(CGuildMember::pos(v5))
            {
                GuildErrorMsg((int)&v9, 10);
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v9);
                result = CNetMsg::_CNetMsg((int)&v9, 2);
            }
            else
            {
                v4 = CGuild::findmember(v6, v7, 0);
                if(v4)
                {
                    if(CGuildMember::pos(v4) == 1)
                    {
                        if(gserver.Unk452130 || !gserver.Unk20 || gserver.Unk20->Unk361)
                        {
                            GuildErrorMsg((int)&v9, 7);
                            if(*(_DWORD *)(a1 + 768))
                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v9);
                            result = CNetMsg::_CNetMsg((int)&v9, 2);
                        }
                        else
                        {
                            HelperGuildFireOfficerReqMsg((int)&v9, dest, *(_DWORD *)(a1 + 4), v7);
                            if(gserver.Unk20)
                                CDescriptor::WriteToOutput(gserver.Unk20, (int)&v9);
                            CDescriptor::WaitHelperReply(*(_DWORD *)(a1 + 768), 1);
                            result = CNetMsg::_CNetMsg((int)&v9, 2);
                        }
                    }
                    else
                    {
                        GuildErrorMsg((int)&v9, 29);
                        if(*(_DWORD *)(a1 + 768))
                            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v9);
                        result = CNetMsg::_CNetMsg((int)&v9, 2);
                    }
                }
                else
                {
                    GuildErrorMsg((int)&v9, 22);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v9);
                    result = CNetMsg::_CNetMsg((int)&v9, 2);
                }
            }
        }
        else
        {
            GuildErrorMsg((int)&v9, 10);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v9);
            result = CNetMsg::_CNetMsg((int)&v9, 2);
        }
    }
    else
    {
        GuildErrorMsg((int)&v9, 9);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v9);
        result = CNetMsg::_CNetMsg((int)&v9, 2);
    }
    return result;
}
// 8071B90: using guessed type _DWORD __cdecl CGuild__findmember(_DWORD, _DWORD, char);
*/
