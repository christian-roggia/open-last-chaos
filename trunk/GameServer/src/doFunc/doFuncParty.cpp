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

void do_Party(CPC *a1, CNetMsg &a2)
{
    /* TODO */
}

/*void do_Party(CPC *a1, CNetMsg &a2)
{
    int result; // eax@1
    unsigned __int8 dest; // [sp+17h] [bp-1h]@2

    result = a1;
    if(*(_BYTE *)(a1 + 420))
    {
        CNetMsg::MoveFirst(a2);
        CNetMsg::__rs(a2, &dest);
        result = dest;
        switch(dest)
        {
            case 0u:
                result = do_PartyInvite(a1, a2);
                break;
            case 1u:
                result = do_PartyAllow(a1);
                break;
            case 2u:
                result = do_PartyReject(a1);
                break;
            case 6u:
                result = do_PartyQuit(a1);
                break;
            case 7u:
                result = do_PartyKick(a1, a2);
                break;
            case 0xBu:
                result = do_PartyAssistInfo(a1, a2);
                break;
            default:
                return result;
        }
    }
    return result;
}

//----- (080B73F0) --------------------------------------------------------
int __cdecl do_PartyInvite(int a1, int a2)
{
    int v2; // eax@1
    int v3; // ebx@3
    __int64 *v4; // eax@3
    char v5; // al@5
    int v6; // esi@6
    __int64 *v7; // eax@6
    int v8; // ST50_4@8
    __int64 *v9; // eax@8
    int v10; // ST4C_4@10
    __int64 *v11; // eax@10
    signed int v12; // eax@12
    int v13; // ST48_4@15
    __int64 *v14; // eax@15
    int v15; // ST44_4@16
    __int64 *v16; // eax@16
    int v17; // ST38_4@18
    int v18; // eax@18
    char v21; // [sp+40h] [bp-20h]@20
    int v22; // [sp+54h] [bp-Ch]@7
    int dest; // [sp+58h] [bp-8h]@1
    char v24; // [sp+5Fh] [bp-1h]@1

    v2 = CNetMsg::__rs(a2, &v24);
    CNetMsg::__rs(v2, &dest);
    if(*(_DWORD *)(a1 + 1368) && CParty::GetMember(*(_DWORD *)(a1 + 1368), 0) != a1)
    {
        v3 = __eh_alloc(4);
        *(_DWORD *)v3 = 1;
        v4 = _tf21_tagMsgPartyErrorType();
        __cp_push_exception(v3, v4, 0);
        __throw();
    }
    if(*(_DWORD *)(a1 + 1368))
    {
        v5 = CParty::GetPartyType(*(_DWORD *)(a1 + 1368));
        if(v5 != v24)
        {
            v6 = __eh_alloc(4);
            *(_DWORD *)v6 = 5;
            v7 = _tf21_tagMsgPartyErrorType();
            __cp_push_exception(v6, v7, 0);
            __throw();
        }
    }
    v22 = CArea::FindCharInCell(*(_DWORD *)(a1 + 412), a1, dest, 0, 1);
    if(!v22)
    {
        v8 = __eh_alloc(4);
        *(_DWORD *)v8 = 0;
        v9 = _tf21_tagMsgPartyErrorType();
        __cp_push_exception(v8, v9, 0);
        __throw();
    }
    if(*(_DWORD *)(v22 + 1368))
    {
        v10 = __eh_alloc(4);
        *(_DWORD *)v10 = 3;
        v11 = _tf21_tagMsgPartyErrorType();
        __cp_push_exception(v10, v11, 0);
        __throw();
    }
    if(!*(_DWORD *)(a1 + 1368))
    {
        v17 = __builtin_new(44);
        v18 = CParty::CParty(v17, v24, a1, v22);
        *(_DWORD *)(v22 + 1368) = v18;
        *(_DWORD *)(a1 + 1368) = v18;
        goto LABEL_20;
    }
    v12 = CParty::Request(*(_DWORD *)(a1 + 1368), v22);
    if(v12 == -1)
    {
        v13 = __eh_alloc(4);
        *(_DWORD *)v13 = 2;
        v14 = _tf21_tagMsgPartyErrorType();
        __cp_push_exception(v13, v14, 0);
        __throw();
        goto LABEL_16;
    }
    if(v12 == 1)
    {
LABEL_16:
        v15 = __eh_alloc(4);
        *(_DWORD *)v15 = 4;
        v16 = _tf21_tagMsgPartyErrorType();
        __cp_push_exception(v15, v16, 0);
        __throw();
    }
LABEL_20:
    CNetMsg::CNetMsg((int)&v21);
    PartyInviteMsg((int)&v21, a1);
    if(*(_DWORD *)(a1 + 768))
        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v21);
    if(*(_DWORD *)(v22 + 768))
        CDescriptor::WriteToOutput(*(_DWORD *)(v22 + 768), (int)&v21);
    return CNetMsg::_CNetMsg((int)&v21, 2);
}
// 804969C: using guessed type int __cdecl __cp_push_exception(_DWORD, _DWORD, _DWORD);
// 80498AC: using guessed type int __throw(void);
// 8049BCC: using guessed type int __cdecl __builtin_delete(_DWORD);
// 8049BFC: using guessed type int __cdecl __builtin_new(_DWORD);
// 8049C7C: using guessed type int __cdecl __eh_alloc(_DWORD);

//----- (080B7900) --------------------------------------------------------
int __cdecl do_PartyAllow(int a1)
{
    int result; // eax@1
    int v2; // eax@8
    char v3; // ST18_1@9
    int v4; // eax@9
    char v5; // [sp+14h] [bp-34h]@3
    char v6; // [sp+28h] [bp-20h]@3
    int i; // [sp+3Ch] [bp-Ch]@3
    int v8; // [sp+40h] [bp-8h]@3
    int v9; // [sp+44h] [bp-4h]@2

    result = a1;
    if(*(_DWORD *)(a1 + 1368))
    {
        v9 = *(_DWORD *)(a1 + 1368);
        result = CParty::GetRequest(v9);
        if(result == a1)
        {
            v8 = CParty::Allow(v9);
            CNetMsg::CNetMsg((int)&v6);
            CNetMsg::CNetMsg((int)&v5);
            PartyAddMsg((int)&v6, a1, v8 == 0);
            for(i = 0; i <= 7; ++i)
            {
                if(CParty::GetMember(v9, i) && i != v8)
                {
                    if(*(_DWORD *)(CParty::GetMember(v9, i) + 768))
                    {
                        v2 = CParty::GetMember(v9, i);
                        CDescriptor::WriteToOutput(*(_DWORD *)(v2 + 768), (int)&v6);
                    }
                    v3 = i == 0;
                    v4 = CParty::GetMember(v9, i);
                    PartyAddMsg((int)&v5, v4, v3);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v5);
                }
            }
            CNetMsg::_CNetMsg((int)&v5, 2);
            result = CNetMsg::_CNetMsg((int)&v6, 2);
        }
    }
    return result;
}

//----- (080B7B00) --------------------------------------------------------
int __cdecl do_PartyReject(int a1)
{
    int result; // eax@1
    int v2; // eax@11
    char v3; // [sp+8h] [bp-20h]@4
    int v4; // [sp+1Ch] [bp-Ch]@4
    int v5; // [sp+20h] [bp-8h]@4
    int v6; // [sp+24h] [bp-4h]@4

    result = a1;
    if(*(_DWORD *)(a1 + 1368))
    {
        result = CParty::GetRequest(*(_DWORD *)(a1 + 1368));
        if(result)
        {
            v6 = *(_DWORD *)(a1 + 1368);
            v5 = CParty::GetMember(v6, 0);
            v4 = CParty::GetRequest(v6);
            CNetMsg::CNetMsg((int)&v3);
            if(v4 == a1)
            {
                PartyMsg((int)&v3, 4);
            }
            else
            {
                if(CParty::GetMember(v6, 0) == a1)
                    PartyMsg((int)&v3, 3);
            }
            if(*(_DWORD *)(v5 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(v5 + 768), (int)&v3);
            if(*(_DWORD *)(CParty::GetRequest(v6) + 768))
            {
                v2 = CParty::GetRequest(v6);
                CDescriptor::WriteToOutput(*(_DWORD *)(v2 + 768), (int)&v3);
            }
            if(CParty::Reject(v6))
            {
                CParty::End(v6);
                if(v6)
                    CParty::_CParty(v6, 3);
            }
            result = CNetMsg::_CNetMsg((int)&v3, 2);
        }
    }
    return result;
}

//----- (080B7CC0) --------------------------------------------------------
int __cdecl do_PartyQuit(int a1)
{
    int result; // eax@1
    int v2; // eax@9
    int v3; // eax@13
    int v4; // eax@24
    signed int i; // [sp+8h] [bp-20h]@5
    signed int j; // [sp+8h] [bp-20h]@20
    char v7; // [sp+Ch] [bp-1Ch]@2
    char v8; // [sp+23h] [bp-5h]@2
    int v9; // [sp+24h] [bp-4h]@2

    result = a1;
    if(*(_DWORD *)(a1 + 1368))
    {
        v9 = *(_DWORD *)(a1 + 1368);
        v8 = CParty::Del(v9, a1);
        CNetMsg::CNetMsg((int)&v7);
        if(v8)
        {
            PartyMsg((int)&v7, 8);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v7);
            for(i = 0; i <= 7; ++i)
            {
                if(CParty::GetMember(v9, i))
                {
                    if(*(_DWORD *)(CParty::GetMember(v9, i) + 768))
                    {
                        v2 = CParty::GetMember(v9, i);
                        CDescriptor::WriteToOutput(*(_DWORD *)(v2 + 768), (int)&v7);
                    }
                }
            }
            if(CParty::GetRequest(v9))
            {
                PartyMsg((int)&v7, 3);
                if(*(_DWORD *)(CParty::GetRequest(v9) + 768))
                {
                    v3 = CParty::GetRequest(v9);
                    CDescriptor::WriteToOutput(*(_DWORD *)(v3 + 768), (int)&v7);
                }
                CParty::Reject(v9);
            }
            CParty::End(v9);
            if(v9)
                CParty::_CParty(v9, 3);
        }
        else
        {
            PartyDelMsg((int)&v7, 0, a1);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v7);
            for(j = 0; j <= 7; ++j)
            {
                if(CParty::GetMember(v9, j) && *(_DWORD *)(CParty::GetMember(v9, j) + 768))
                {
                    v4 = CParty::GetMember(v9, j);
                    CDescriptor::WriteToOutput(*(_DWORD *)(v4 + 768), (int)&v7);
                }
            }
        }
        result = CNetMsg::_CNetMsg((int)&v7, 2);
    }
    return result;
}

//----- (080B7F80) --------------------------------------------------------
int __cdecl do_PartyKick(int a1, int a2)
{
    int result; // eax@1
    signed int v3; // eax@6
    int v4; // eax@17
    int v5; // eax@21
    int v6; // eax@32
    signed int i; // [sp+Ch] [bp-2Ch]@13
    signed int j; // [sp+Ch] [bp-2Ch]@28
    int v9; // [sp+14h] [bp-24h]@6
    int dest; // [sp+18h] [bp-20h]@6
    int v11; // [sp+1Ch] [bp-1Ch]@2
    int v12; // [sp+20h] [bp-18h]@2
    char v13; // [sp+24h] [bp-14h]@2

    result = a1;
    if(*(_DWORD *)(a1 + 1368))
    {
        CNetMsg::CNetMsg((int)&v13);
        v12 = *(_DWORD *)(a1 + 1368);
        v11 = CParty::GetMember(v12, 0);
        if(v11 == a1)
        {
            CNetMsg::__rs(a2, &dest);
            v3 = CParty::FindByIndex(v12, dest);
            v9 = CParty::GetMember(v12, v3);
            if(v9)
            {
                if(CParty::Del(v12, v9))
                {
                    PartyMsg((int)&v13, 8);
                    if(*(_DWORD *)(v9 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(v9 + 768), (int)&v13);
                    for(i = 0; i <= 7; ++i)
                    {
                        if(CParty::GetMember(v12, i) && *(_DWORD *)(CParty::GetMember(v12, i) + 768))
                        {
                            v4 = CParty::GetMember(v12, i);
                            CDescriptor::WriteToOutput(*(_DWORD *)(v4 + 768), (int)&v13);
                        }
                    }
                    if(CParty::GetRequest(v12))
                    {
                        PartyMsg((int)&v13, 3);
                        if(*(_DWORD *)(CParty::GetRequest(v12) + 768))
                        {
                            v5 = CParty::GetRequest(v12);
                            CDescriptor::WriteToOutput(*(_DWORD *)(v5 + 768), (int)&v13);
                        }
                        CParty::Reject(v12);
                    }
                    CParty::End(v12);
                    if(v12)
                        CParty::_CParty(v12, 3);
                }
                else
                {
                    PartyDelMsg((int)&v13, 1, v9);
                    if(*(_DWORD *)(v9 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(v9 + 768), (int)&v13);
                    for(j = 0; j <= 7; ++j)
                    {
                        if(CParty::GetMember(v12, j) && *(_DWORD *)(CParty::GetMember(v12, j) + 768))
                        {
                            v6 = CParty::GetMember(v12, j);
                            CDescriptor::WriteToOutput(*(_DWORD *)(v6 + 768), (int)&v13);
                        }
                    }
                }
                result = CNetMsg::_CNetMsg((int)&v13, 2);
            }
            else
            {
                PartyErrorMsg((int)&v13, 0);
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v13);
                result = CNetMsg::_CNetMsg((int)&v13, 2);
            }
        }
        else
        {
            PartyErrorMsg((int)&v13, 6);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v13);
            result = CNetMsg::_CNetMsg((int)&v13, 2);
        }
    }
    return result;
}

//----- (080B8340) --------------------------------------------------------
int __cdecl do_PartyAssistInfo(int a1, int a2)
{
    int result; // eax@1
    int v3; // eax@6
    char v4; // [sp+Ch] [bp-1Ch]@6
    int i; // [sp+20h] [bp-8h]@2
    int dest; // [sp+24h] [bp-4h]@2

    result = a1;
    if(*(_DWORD *)(a1 + 1368))
    {
        result = CNetMsg::__rs(a2, &dest);
        for(i = 0; i <= 7; ++i)
        {
            result = CParty::GetMember(*(_DWORD *)(a1 + 1368), i);
            if(result)
            {
                result = *(_DWORD *)(CParty::GetMember(*(_DWORD *)(a1 + 1368), i) + 4);
                if(result == dest)
                {
                    CNetMsg::CNetMsg((int)&v4);
                    v3 = CParty::GetMember(*(_DWORD *)(a1 + 1368), i);
                    PartyAssistInfoMsg((int)&v4, v3);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v4);
                    return CNetMsg::_CNetMsg((int)&v4, 2);
                }
            }
        }
    }
    return result;
}
*/
