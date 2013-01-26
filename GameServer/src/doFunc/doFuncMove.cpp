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
#include "../Server.h"

void do_Move(CPC *a1, CNetMsg &a2)
{
    /* TODO */
}

/*void do_Move(CPC *a1, CNetMsg &a2)
{
    int v2; // eax@1
    int v3; // eax@1
    int v4; // eax@1
    int v5; // eax@1
    int v6; // eax@1
    int v7; // eax@1
    int v8; // eax@1
    int v9; // eax@1
    int v10; // eax@1
    __int16 v11; // fps@4
    unsigned __int8 v12; // c0@4
    char v13; // c2@4
    unsigned __int8 v14; // c3@4
    __int16 v15; // fps@5
    unsigned __int8 v16; // c0@5
    char v17; // c2@5
    unsigned __int8 v18; // c3@5
    long double v19; // fst7@6
    __int16 v20; // fps@6
    char v21; // c0@6
    char v22; // c2@6
    char v23; // c3@6
    long double v24; // fst7@7
    __int16 v25; // fps@7
    char v26; // c0@7
    char v27; // c2@7
    char v28; // c3@7
    signed int v29; // eax@12
    long double v30; // fst7@19
    float v31; // ST60_4@21
    float v33; // [sp-10h] [bp-64h]@17
    int v34; // [sp+28h] [bp-2Ch]@36
    char v35; // [sp+37h] [bp-1Dh]@1
    float v36; // [sp+38h] [bp-1Ch]@1
    float v37; // [sp+3Ch] [bp-18h]@1
    float v38; // [sp+40h] [bp-14h]@1
    float v39; // [sp+44h] [bp-10h]@1
    char dest; // [sp+48h] [bp-Ch]@1
    int v41; // [sp+4Ch] [bp-8h]@1
    unsigned __int8 v42; // [sp+52h] [bp-2h]@1
    unsigned __int8 v43; // [sp+53h] [bp-1h]@1

    CNetMsg::MoveFirst(a2);
    v2 = CNetMsg::__rs(a2, &v43);
    v3 = CNetMsg::__rs(v2, &v42);
    v4 = CNetMsg::__rs(v3, &v41);
    v5 = CNetMsg::__rs(v4, &dest);
    v6 = CNetMsg::__rs(v5, &v39);
    v7 = CNetMsg::__rs(v6, &v38);
    v8 = CNetMsg::__rs(v7, &v37);
    v9 = CNetMsg::__rs(v8, &v36);
    CNetMsg::__rs(v9, &v35);
    LOBYTE(v10) = a1;
    if(*(_DWORD *)(a1 + 408))
    {
        LOBYTE(v10) = a1;
        if(*(_DWORD *)(a1 + 412))
        {
            UNDEF(v11);
            v12 = 0.0 < v39;
            v13 = 0;
            v14 = 0.0 == v39;
            LOBYTE(v10) = v11;
            if(v12 | v14)
            {
                UNDEF(v15);
                v16 = 0.0 < v38;
                v17 = 0;
                v18 = 0.0 == v38;
                LOBYTE(v10) = v15;
                if(v16 | v18)
                {
                    v19 = (long double)**(signed int **)(*(_DWORD *)(a1 + 408) + 32);
                    UNDEF(v20);
                    v21 = v39 < v19;
                    v22 = 0;
                    v23 = v39 == v19;
                    LOBYTE(v10) = v20;
                    if(v39 < v19)
                    {
                        v24 = (long double)*(signed int *)(*(_DWORD *)(*(_DWORD *)(a1 + 408) + 32) + 4);
                        UNDEF(v25);
                        v26 = v38 < v24;
                        v27 = 0;
                        v28 = v38 == v24;
                        LOBYTE(v10) = v25;
                        if(v38 < v24)
                        {
                            if(v35 >= 0)
                            {
                                LOBYTE(v10) = v35;
                                if(v35 < 2 * *(_DWORD *)(*(_DWORD *)(a1 + 408) + 28))
                                {
                                    if(*(_DWORD *)(a1 + 732) <= 0)
                                    {
                                        v29 = **(_DWORD **)(a1 + 408);
                                        if(v29 != 2)
                                        {
                                            if(v29 < 2 || v29 > 6 || v29 < 5)
                                            {
                                                v33 = CArea::GetHeight(*(_DWORD *)(a1 + 412), *(_BYTE *)(a1 + 136), v39, v38);
                                                if(a1 && *(_DWORD *)(a1 + 412))
                                                    v30 = CArea::GetHeight(
                                                                    *(_DWORD *)(a1 + 412),
                                                                    *(_BYTE *)(a1 + 136),
                                                                    *(float *)(a1 + 120),
                                                                    *(float *)(a1 + 124));
                                                else
                                                    v30 = 0.0;
                                                v31 = v30;
                                                GetDistance(*(float *)(a1 + 120), v39, *(float *)(a1 + 124), v38, v31, v33);
                                            }
                                        }
                                    }
                                    LOBYTE(v10) = v42;
                                    if(v42 != 2)
                                    {
                                        if((signed int)v42 > 2)
                                        {
                                            if(v42 != 3)
                                                return v10;
                                            LOBYTE(v10) = CPC::ResetPlayerState(a1, 2);
                                        }
                                        else
                                        {
                                            LOBYTE(v10) = CPC::SetPlayerState(a1, 2);
                                        }
                                    }
                                    if(v43)
                                    {
                                        if(v43 == 1)
                                        {
                                            LOBYTE(v10) = a1;
                                            v34 = *(_DWORD *)(a1 + 412);
                                            if(v34)
                                            {
                                                v10 = CArea::FindCharInCell(v34, a1, v41, v43, 0);
                                                if(v10)
                                                {
                                                    if(*(_DWORD *)v10 != 1)
                                                        v10 = 0;
                                                    if(v10)
                                                    {
                                                        *(float *)(v10 + 120) = v39;
                                                        *(float *)(v10 + 124) = v38;
                                                        *(float *)(v10 + 132) = v36;
                                                        *(_BYTE *)(v10 + 136) = v35;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        LOBYTE(v10) = a1;
                                        if(*(_WORD *)(a1 + 76) > 0)
                                        {
                                            LOBYTE(v10) = (*(int (__cdecl **)(int))(*(_DWORD *)(a1 + 460) + 12))(a1);
                                            if((_BYTE)v10)
                                            {
                                                *(float *)(a1 + 120) = v39;
                                                *(float *)(a1 + 124) = v38;
                                                *(float *)(a1 + 132) = v36;
                                                *(_BYTE *)(a1 + 136) = v35;
                                                if(*(_DWORD *)(a1 + 416))
                                                    LOBYTE(v10) = CRoom::MoveChar(*(_DWORD *)(a1 + 416), a1, v35, v39, v38, v37, v36, v42, 0);
                                                else
                                                    LOBYTE(v10) = CArea::MoveChar(*(_DWORD *)(a1 + 412), a1, v35, v39, v38, v37, v36, v42, 0);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return v10;
}*/

void do_GoZone(CPC *a1, CNetMsg &a2)
{
    int v6; // [sp+14h] [bp-24h]@13
    CZone *v7; // [sp+18h] [bp-20h]@15
    int v8; // [sp+1Ch] [bp-1Ch]@1
    int dest; // [sp+20h] [bp-18h]@1

    CNetMsg v10;

    a2.MoveFirst();

    a2.__rs(dest);
    a2.__rs(v8);

    if(a1->Unk408->Unk0 != 2 || dest != 2)
    {
        if(a1->Unk408->Unk0 != 5 || dest != 5)
        {
            if(a1->Unk408->Unk0 != 6 || dest != 6)
            {
                if(a1->Unk408->Unk0 != 8 || dest != 8)
                {
                    v6 = gserver.FindZone(dest);

                    if(v6 == -1)
                        return;

                    v7 = &gserver.Unk452196[v6];
                    if(v8 >= 0 && v8 < v7->Unk48)
                    {
                        if(a1->Unk408->Unk0 == 6)
                        {
                            if(!dest)
                                v8 = 2;
                        }

                        GoZone(a1, dest, v7->Unk52[v8]->Unk0, (GetRandom(v7->Unk52[v8]->Unk4, v7->Unk52[v8]->Unk12) / 2.0), (GetRandom(v7->Unk52[v8]->Unk8, v7->Unk52[v8]->Unk16) / 2.0));
                    }
                }
            }
        }
    }
}

void do_Warp(CPC *a1, CNetMsg &a2)
{
    char dest; // [sp+27h] [bp-1h]@1

    a2.MoveFirst();
    a2.__rs(dest);

    if(dest == 1)
    {
        a1->Unk1356 = 0;
        a1->Unk1360 = -1;
        a1->Unk1364 = -1;

        a1->ResetPlayerState(7);

        CNetMsg v3;

        WarpCancelMsg(v3, a1);
        a1->Unk412->SendToCell(v3, a1, 1, 4);
    }
}

void GoZone(CPC *a1, int a2, char a3, float a4, float a5)
{
    /* TODO */
}

/*void GoZone(CPC *a1, int a2, char a3, float a4, float a5)
{
    signed int v6; // ST28_4@31
    const char *v7; // eax@31
    int v8; // eax@31
    int v9; // eax@31
    int v10; // eax@31
    signed int v11; // ST28_4@40
    const char *v12; // eax@40
    int v13; // eax@40
    int v14; // eax@40
    int v15; // eax@40
    signed int v16; // ST28_4@44
    const char *v17; // eax@44
    int v18; // eax@44
    int v19; // eax@44
    int v20; // eax@44
    signed int v21; // ST28_4@48
    const char *v22; // eax@48
    int v23; // eax@48
    int v24; // eax@48
    int v25; // eax@48
    __int64 v26; // qax@51
    signed int v27; // ST28_4@60
    const char *v28; // eax@60
    int v29; // eax@60
    int v30; // eax@60
    int v31; // eax@60
    int v32; // ebx@73
    int v33; // esi@73
    int v34; // eax@73
    int v35; // eax@81
    char v36; // [sp+28h] [bp-7Ch]@60
    int k; // [sp+3Ch] [bp-68h]@43
    int v38; // [sp+40h] [bp-64h]@39
    int v39; // [sp+44h] [bp-60h]@31
    int i; // [sp+58h] [bp-4Ch]@19
    int j; // [sp+5Ch] [bp-48h]@19
    int v42; // [sp+60h] [bp-44h]@19
    int v43; // [sp+64h] [bp-40h]@12
    int v44; // [sp+78h] [bp-2Ch]@10
    char v45; // [sp+7Fh] [bp-25h]@9
    int v46; // [sp+80h] [bp-24h]@1
    int v47; // [sp+84h] [bp-20h]@1
    char v48; // [sp+8Ah] [bp-1Ah]@1
    char v49; // [sp+8Bh] [bp-19h]@1
    int v50; // [sp+8Ch] [bp-18h]@1
    char v51; // [sp+A3h] [bp-1h]@1

    v51 = a3;
    CNetMsg::CNetMsg((int)&v50);
    v49 = 0;
    v48 = 0;
    v47 = 0;
    DelAttackList(a1);
    v46 = 0;
    if(**(_DWORD **)(a1 + 408) == a2)
    {
        v49 = 1;
        v48 = 1;
        v47 = *(_DWORD *)(a1 + 408);
    }
    else
    {
        v46 = CServer::FindZone((int)&gserver, a2);
        if(v46 != -1)
        {
            v47 = 72 * v46 + gserver.Unk452196;
            if(*(_BYTE *)(gserver.Unk452196 + 72 * v46 + 4))
            {
                v49 = 0;
                v48 = 1;
            }
            else
            {
                v49 = 1;
                v48 = 1;
            }
        }
    }
    if(!v48)
        return CNetMsg::_CNetMsg((int)&v50, 2);
    v45 = 0;
    if(!v49)
    {
        MsgrGoZoneReqMsg((int)&v50, 0, *(_DWORD *)(a1 + 4), **(_DWORD **)(a1 + 408), *(_DWORD *)v47);
        if(!gserver.Unk452129 && gserver.Unk12 && !gserver.Unk12->Unk361 && gserver.Unk12)
            CDescriptor::WriteToOutput(gserver.Unk12, (int)&v50);
        return CNetMsg::_CNetMsg((int)&v50, 2);
    }
    v44 = *(_DWORD *)(a1 + 412);
    CCharacter::SendDisappearAllInCell(a1);
    CArea::CharFromCell(v44, a1);
    if(*(_DWORD *)(a1 + 408) != v47 && *(_DWORD *)(a1 + 1368))
    {
        CNetMsg::CNetMsg((int)&v43);
        if(CParty::GetRequest(*(_DWORD *)(a1 + 1368)) == a1)
            PartyMsg((int)&v43, 2);
        else
            PartyMsg((int)&v43, 6);
        do_Party(a1, (int)&v43);
        CNetMsg::_CNetMsg((int)&v43, 2);
    }
    v46 = -858993459 * (*(_DWORD *)(a1 + 412) - *(_DWORD *)(*(_DWORD *)(a1 + 408) + 36)) >> 4;
    if(*(_DWORD *)(a1 + 408) == v47)
    {
LABEL_93:
        *(_DWORD *)(a1 + 408) = v47;
        *(_DWORD *)(a1 + 412) = 80 * v46 + *(_DWORD *)(*(_DWORD *)(a1 + 408) + 36);
        *(_BYTE *)(a1 + 136) = v51;
        *(_DWORD *)(a1 + 132) = 0;
        *(float *)(a1 + 120) = a4;
        *(float *)(a1 + 124) = a5;
        GotoMsg((int)&v50, a1);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v50);
        if(!v45)
        {
            CArea::PointToCellNum(*(_DWORD *)(a1 + 412), *(float *)(a1 + 120), *(float *)(a1 + 124), (int)&k, (int)&v38);
            CArea::CharToCell(*(_DWORD *)(a1 + 412), a1, *(_BYTE *)(a1 + 136), k, v38);
            AppearMsg((int)&v50, a1, 1);
            CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v50, a1, 0, 4);
            CArea::SendCellInfo(*(_DWORD *)(a1 + 412), a1);
        }
        if(*(_WORD *)(a1 + 76) > 0)
        {
            EffectEtcMsg((int)&v50, a1, 1);
            CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v50, a1, 1, 4);
        }
        return CNetMsg::_CNetMsg((int)&v50, 2);
    }
    if(*(_DWORD *)(*(_DWORD *)(a1 + 408) + 40) > 1)
    {
        if(**(_DWORD **)(a1 + 408) == 8)
        {
            CArea::PointToCellNum(*(_DWORD *)(a1 + 412), *(float *)(a1 + 120), *(float *)(a1 + 124), (int)&v42, (int)&j);
            for(i = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(a1 + 412) + 28) + 4 * v42) + 16 * j);
                        i;
                        i = *(_DWORD *)(i + 404))
            {
                if(!*(_DWORD *)i && *(_DWORD *)(i + 4) != *(_DWORD *)(a1 + 4))
                    goto LABEL_66;
            }
            *(_DWORD *)(*(_DWORD *)(a1 + 412) + 76) = -1;
            CZone::SetDisableArea(*(_DWORD *)(a1 + 408), *(_DWORD *)(*(_DWORD *)(a1 + 412) + 8));
        }
        else
        {
            CZone::SetDisableArea(*(_DWORD *)(a1 + 408), *(_DWORD *)(*(_DWORD *)(a1 + 412) + 8));
            for(i = 0; i <= 9; ++i)
            {
                if(*(_DWORD *)(4 * i + a1 + 1900) && *(_BYTE *)(i + a1 + 1940) && !*(_BYTE *)(i + a1 + 1950))
                {
                    if(*(_DWORD *)(**(_DWORD **)(4 * i + a1 + 1900) + 4) == 3)
                    {
                        v6 = ***(_DWORD ***)(4 * i + a1 + 1900);
                        init((int)&v43, (int)"QUEST FAIL");
                        v7 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v43);
                        v8 = (int)CLogBuffer::__ls(v7, (const char *)(a1 + 8));
                        v9 = CLogBuffer::__ls(v8, (int (__cdecl *)(_DWORD))delim);
                        v10 = (int)CLogBuffer::__ls((char *)v9, v6);
                        CLogBuffer::__ls(v10, end);
                        CNetMsg::CNetMsg((int)&v39);
                        QuestFailMsg((int)&v39, *(uint32_t ***)(4 * i + a1 + 1900));
                        CQuestList::DelQuest(a1 + 1900, a1, *(_DWORD *)(4 * i + a1 + 1900));
                        if(*(_DWORD *)(a1 + 768))
                            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v39);
                        CNetMsg::_CNetMsg((int)&v39, 2);
                        break;
                    }
                    if(*(_DWORD *)(**(_DWORD **)(4 * i + a1 + 1900) + 4) == 4)
                    {
                        for(j = 0; j <= 2; ++j)
                        {
                            if(*(_DWORD *)(4 * j + **(_DWORD **)(4 * i + a1 + 1900) + 76) != -1
                                && *(_DWORD *)(4 * j + **(_DWORD **)(4 * i + a1 + 1900) + 76) == 1)
                            {
                                if(CInventory::FindItem(
                                             a1 + 880,
                                             (int)&v42,
                                             (int)&v38,
                                             *(_DWORD *)(4 * j + **(_DWORD **)(4 * i + a1 + 1900) + 88),
                                             0,
                                             0))
                                {
                                    k = CInventory::GetItem(a1 + 880, v42, v38);
                                    if(k)
                                    {
                                        if(*(_DWORD *)(4 * j + **(_DWORD **)(4 * i + a1 + 1900) + 100) <= CItem::Count(k))
                                        {
                                            CNetMsg::CNetMsg((int)&v39);
                                            CInventory::Decrease(a1 + 880, k, *(_DWORD *)(4 * j + **(_DWORD **)(4 * i + a1 + 1900) + 100));
                                            v26 = CItem::Count(k);
                                            if(SHIDWORD(v26) <= 0 && (HIDWORD(v26) || !(_DWORD)v26))
                                            {
                                                ItemDeleteMsg((int)&v39, k);
                                                if(*(_DWORD *)(a1 + 768))
                                                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v39);
                                                CPC::RemoveItemFromQuickSlot(a1, k);
                                                CInventory::Remove(a1 + 880, k, 1, 1);
                                            }
                                            else
                                            {
                                                ItemUpdateMsg((int)&v39, k, -*(_DWORD *)(4 * j + **(_DWORD **)(4 * i + a1 + 1900) + 100));
                                                if(*(_DWORD *)(a1 + 768))
                                                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v39);
                                            }
                                            v27 = ***(_DWORD ***)(4 * i + a1 + 1900);
                                            init((int)&v43, (int)"QUEST FAIL");
                                            v28 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v43);
                                            v29 = (int)CLogBuffer::__ls(v28, (const char *)(a1 + 8));
                                            v30 = CLogBuffer::__ls(v29, (int (__cdecl *)(_DWORD))delim);
                                            v31 = (int)CLogBuffer::__ls((char *)v30, v27);
                                            CLogBuffer::__ls(v31, end);
                                            CNetMsg::CNetMsg((int)&v36);
                                            QuestFailMsg((int)&v36, *(uint32_t ***)(4 * i + a1 + 1900));
                                            CQuestList::DelQuest(a1 + 1900, a1, *(_DWORD *)(4 * i + a1 + 1900));
                                            if(*(_DWORD *)(a1 + 768))
                                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v36);
                                            CNetMsg::_CNetMsg((int)&v36, 2);
                                            CNetMsg::_CNetMsg((int)&v39, 2);
                                        }
                                        else
                                        {
                                            v21 = ***(_DWORD ***)(4 * i + a1 + 1900);
                                            init((int)&v43, (int)"QUEST FAIL");
                                            v22 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v43);
                                            v23 = (int)CLogBuffer::__ls(v22, (const char *)(a1 + 8));
                                            v24 = CLogBuffer::__ls(v23, (int (__cdecl *)(_DWORD))delim);
                                            v25 = (int)CLogBuffer::__ls((char *)v24, v21);
                                            CLogBuffer::__ls(v25, end);
                                            CNetMsg::CNetMsg((int)&v39);
                                            QuestFailMsg((int)&v39, *(uint32_t ***)(4 * i + a1 + 1900));
                                            CQuestList::DelQuest(a1 + 1900, a1, *(_DWORD *)(4 * i + a1 + 1900));
                                            if(*(_DWORD *)(a1 + 768))
                                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v39);
                                            CNetMsg::_CNetMsg((int)&v39, 2);
                                        }
                                    }
                                    else
                                    {
                                        v16 = ***(_DWORD ***)(4 * i + a1 + 1900);
                                        init((int)&v43, (int)"QUEST FAIL");
                                        v17 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v43);
                                        v18 = (int)CLogBuffer::__ls(v17, (const char *)(a1 + 8));
                                        v19 = CLogBuffer::__ls(v18, (int (__cdecl *)(_DWORD))delim);
                                        v20 = (int)CLogBuffer::__ls((char *)v19, v16);
                                        CLogBuffer::__ls(v20, end);
                                        CNetMsg::CNetMsg((int)&v39);
                                        QuestFailMsg((int)&v39, *(uint32_t ***)(4 * i + a1 + 1900));
                                        CQuestList::DelQuest(a1 + 1900, a1, *(_DWORD *)(4 * i + a1 + 1900));
                                        if(*(_DWORD *)(a1 + 768))
                                            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v39);
                                        CNetMsg::_CNetMsg((int)&v39, 2);
                                    }
                                }
                                else
                                {
                                    v11 = ***(_DWORD ***)(4 * i + a1 + 1900);
                                    init((int)&v43, (int)"QUEST FAIL");
                                    v12 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v43);
                                    v13 = (int)CLogBuffer::__ls(v12, (const char *)(a1 + 8));
                                    v14 = CLogBuffer::__ls(v13, (int (__cdecl *)(_DWORD))delim);
                                    v15 = (int)CLogBuffer::__ls((char *)v14, v11);
                                    CLogBuffer::__ls(v15, end);
                                    CNetMsg::CNetMsg((int)&v39);
                                    QuestFailMsg((int)&v39, *(uint32_t ***)(4 * i + a1 + 1900));
                                    CQuestList::DelQuest(a1 + 1900, a1, *(_DWORD *)(4 * i + a1 + 1900));
                                    if(*(_DWORD *)(a1 + 768))
                                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v39);
                                    CNetMsg::_CNetMsg((int)&v39, 2);
                                }
                                goto LABEL_66;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
LABEL_66:
    if(*(_DWORD *)(v47 + 40) <= 1)
    {
        v46 = 0;
        goto LABEL_89;
    }
    if(*(_DWORD *)v47 == 8)
    {
        if(!*(_DWORD *)(a1 + 2368))
            return CNetMsg::_CNetMsg((int)&v50, 2);
        for(k = 0; k < *(_DWORD *)(v47 + 40); ++k)
        {
            if(*(_BYTE *)(*(_DWORD *)(v47 + 36) + 80 * k))
            {
                v32 = 80 * k;
                v33 = *(_DWORD *)(v47 + 36);
                v34 = CGuildMember::guild(*(_DWORD *)(a1 + 2368));
                if(*(_DWORD *)(v33 + v32 + 76) == CGuild::index(v34))
                {
                    v46 = k;
                    break;
                }
            }
        }
        if(k == *(_DWORD *)(v47 + 40))
        {
            v46 = CZone::SetEnableArea(v47);
            if(v46 == -1)
            {
                CNetMsg::CNetMsg((int)&v36);
                SysMsg((int)&v36, 26);
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v36);
                CNetMsg::_CNetMsg((int)&v36, 2);
                return CNetMsg::_CNetMsg((int)&v50, 2);
            }
            v35 = CGuildMember::guild(*(_DWORD *)(a1 + 2368));
            *(_DWORD *)(*(_DWORD *)(v47 + 36) + 80 * v46 + 76) = CGuild::index(v35);
        }
        goto LABEL_89;
    }
    v46 = CZone::SetEnableArea(v47);
    if(v46 != -1)
    {
LABEL_89:
        if(CPC::IsSetPlayerState(a1, 64) && *(_DWORD *)(a1 + 2388) != -1)
        {
            *(_DWORD *)(a1 + 2388) = -1;
            *(_DWORD *)(a1 + 2384) = 0;
            CPC::ResetPlayerState(a1, 64);
            CNetMsg::CNetMsg((int)&v36);
            ChangeStopMsg((int)&v36, a1);
            CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v36, a1, 1, 4);
            CNetMsg::_CNetMsg((int)&v36, 2);
        }
        CPCList::Remove(gserver.Unk24, a1);
        *(_BYTE *)(a1 + 472) = 0;
        *(_DWORD *)(*(_DWORD *)(a1 + 768) + 340) = 25;
        v45 = 1;
        *(_DWORD *)(a1 + 772) = 6000;
        *(_DWORD *)(*(_DWORD *)(a1 + 768) + 120) = 1;
        CCharDBQ::AddToQ(135285240, *(_DWORD *)(a1 + 768));
        goto LABEL_93;
    }
    CNetMsg::CNetMsg((int)&v36);
    SysMsg((int)&v36, 26);
    if(*(_DWORD *)(a1 + 768))
        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v36);
    CNetMsg::_CNetMsg((int)&v36, 2);
    return CNetMsg::_CNetMsg((int)&v50, 2);
}
*/

void GoTo(CCharacter *a1, char a2, float a3, float a4, float a5, float a6)
{
    int v7; // [sp+18h] [bp-20h]@1
    int v8; // [sp+1Ch] [bp-1Ch]@1
    CNetMsg v9; // [sp+20h] [bp-18h]@1
    char v10 = a2; // [sp+37h] [bp-1h]@1

    a1->SendDisappearAllInCell();
    a1->Unk412->CharFromCell(a1);
    a1->Move(a3, a4, a5, a6, v10);
    a1->Unk412->PointToCellNum(a3, a4, &v8, &v7);
    a1->Unk412->CharToCell(a1, v10, v8, v7);

    if(a1->Unk0 == 0)
    {
        GotoMsg(v9, (CPC *)a1);

        if(((CPC *)a1)->Unk768)
            ((CPC *)a1)->Unk768->WriteToOutput(v9);

        a1->Unk412->SendCellInfo((CPC *)a1);
    }

    AppearMsg(v9, a1, 0);

    a1->Unk412->SendToCell(v9, a1, 0, 4);
}
