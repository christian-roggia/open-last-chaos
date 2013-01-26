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

void do_Produce(CPC *a1, CNetMsg &a2)
{
    /* TODO */
}

/*void do_Produce(CPC *a1, CNetMsg &a2)
{
    CCharacter *v8; // [sp+10h] [bp-18h]@3
    CCharacter *v9; // [sp+14h] [bp-14h]@3
    CArea *v10; // [sp+18h] [bp-10h]@2
    int v11; // [sp+1Ch] [bp-Ch]@2
    int dest; // [sp+20h] [bp-8h]@2
    char v13; // [sp+25h] [bp-3h]@2
    char v14; // [sp+26h] [bp-2h]@2
    char v15; // [sp+27h] [bp-1h]@2

    if(a1->Unk76 <= 0) return;

    a2.MoveFirst();

    a2.__rs(v15);
    a2.__rs(v14);
    a2.__rs(dest);
    a2.__rs(v13);
    a2.__rs(v11);

    v10 = a1->Unk412;
    if(!v10) return;

    v9 = v10->FindCharInCell(a1, dest, v14, 0);
    v8 = v10->FindCharInCell(a1, v11, v13, 0);

    if(!v9 || !v8) return;
    if(((CPC *)v9)->IsSetPlayerState(64)) return;
    if(v14 || v13 != 1) return;

    Produce(v9, v8, v15);
}

void Produce(CPC *a1, CNPC *a2, _tagProduceKind a3)
{
    int result; // eax@1
    int v4; // eax@125
    __int64 v5; // qax@143
    __int64 v6; // ST70_8@148
    signed int v7; // ST58_4@148
    signed int v8; // ST40_4@148
    const char *v9; // ST28_4@148
    const char *v10; // ST10_4@148
    const char *v11; // eax@148
    int v12; // eax@148
    int v13; // eax@148
    int v14; // eax@148
    int v15; // eax@148
    int v16; // eax@148
    int v17; // eax@148
    int v18; // eax@148
    int v19; // eax@148
    int v20; // eax@148
    int v21; // eax@148
    int v22; // eax@148
    unsigned int v23; // eax@173
    char v24; // [sp+28h] [bp-B0h]@151
    int v25; // [sp+3Ch] [bp-9Ch]@148
    int l; // [sp+4Ch] [bp-8Ch]@142
    int v27; // [sp+50h] [bp-88h]@141
    int v28; // [sp+54h] [bp-84h]@141
    char v29; // [sp+5Bh] [bp-7Dh]@139
    unsigned int v30; // [sp+5Ch] [bp-7Ch]@113
    int k; // [sp+60h] [bp-78h]@105
    int v32; // [sp+64h] [bp-74h]@105
    unsigned int v33; // [sp+68h] [bp-70h]@105
    int v34; // [sp+6Ch] [bp-6Ch]@105
    int v35; // [sp+70h] [bp-68h]@105
    int v36; // [sp+74h] [bp-64h]@105
    int v37; // [sp+78h] [bp-60h]@105
    int v38; // [sp+7Ch] [bp-5Ch]@105
    char v39[20]; // [sp+80h] [bp-58h]@105
    int v40; // [sp+94h] [bp-44h]@72
    int v41; // [sp+98h] [bp-40h]@72
    int i; // [sp+9Ch] [bp-3Ch]@61
    char v43; // [sp+A3h] [bp-35h]@51
    int j; // [sp+A4h] [bp-34h]@51
    int v45; // [sp+A8h] [bp-30h]@51
    int v46; // [sp+ACh] [bp-2Ch]@44
    int v47; // [sp+C0h] [bp-18h]@15

    if(a2->Unk464->Unk92 & 0x400)
    {
        if(a3) return;
    }
    else
    {
        if(a2->Unk464->Unk92 & 0x800)
        {
            if(a3 != 1) return;
        }
        else
        {
            if(!a2->Unk464->Unk92 & 0x1000 || a3 != 2) return;
        }
    }

    CNetMsg v48;
    if(!a1->Unk1292)
    {
        SysMsg(v48, 29);
        if(a1->Unk768) a1->Unk768->WriteToOutput(v48);
        return;
    }

    v47 = a1->Unk1292;
    if(*(_DWORD *)(*(_DWORD *)(v47 + 20) + 4)
        || *(_DWORD *)(*(_DWORD *)(v47 + 20) + 8) != 8
        && *(_DWORD *)(*(_DWORD *)(v47 + 20) + 8) != 9
        && *(_DWORD *)(*(_DWORD *)(v47 + 20) + 8) != 10)
    {
        SysMsg(v48, 30);
        if(a1->Unk768) a1->Unk768->WriteToOutput(v48);
        return;
    }

    if(a3 == 1)
    {
        if(*(_DWORD *)(*(_DWORD *)(v47 + 20) + 8) != 9)
        {
            SysMsg(v48, 31);
            if(*(_DWORD *)(a1->Unk768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v48);
            return;
        }
    }
    else
    {
        if(a3 > 1)
        {
            if(a3 == 2 && *(_DWORD *)(*(_DWORD *)(v47 + 20) + 8) != 10)
            {
                SysMsg(v48, 31);
                if(*(_DWORD *)(a1->Unk768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v48);
                return;
            }
        }
        else
        {
            if(!a3 && *(_DWORD *)(*(_DWORD *)(v47 + 20) + 8) != 8)
            {
                SysMsg(v48, 31);
                if(*(_DWORD *)(a1->Unk768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v48);
                return;
            }
        }
    }

    if(*(_DWORD *)(*(_DWORD *)(v47 + 20) + 72) == -1 || *(_DWORD *)(v47 + 64) > 0)
    {
        v45 = 0;
        j = *(_DWORD *)(a2->Unk396);
        v43 = 0;
        while(j)
        {
            ++v45;
            if(*(_DWORD *)(j + 16) == a1)
                v43 = 1;
            j = *(_DWORD *)(j + 20);
        }
        if(v43 || v45 <= 3)
        {
            for(i = 0; i <= 9; ++i)
            {
                if(*(_DWORD *)(4 * i + a1->Unk1900)
                    && *(_DWORD *)(4 * i + a1->Unk1900)
                    && *(_BYTE *)(i + a1->Unk1940)
                    && (*(_DWORD *)(**(_DWORD **)(4 * i + a1->Unk1900) + 4) == 1
                     || *(_DWORD *)(**(_DWORD **)(4 * i + a1->Unk1900) + 4) == 5
                     || *(_DWORD *)(**(_DWORD **)(4 * i + a1->Unk1900) + 4) == 6
                     || *(_DWORD *)(**(_DWORD **)(4 * i + a1->Unk1900) + 4) == 7))
                    CQuest::QuestUpdateData(*(int ***)(4 * i + a1->Unk1900), a1);
            }
            v41 = *(_DWORD *)(a1->Unk716);
            v40 = 0;
            while(v41)
            {
                if(a3 == 1)
                {
                    if(*(_DWORD *)(**(_DWORD **)v41 + 8) == 1)
                        v40 = *(_DWORD *)v41;
                }
                else
                {
                    if(a3 > 1)
                    {
                        if(a3 == 2 && *(_DWORD *)(**(_DWORD **)v41 + 8) == 2)
                            v40 = *(_DWORD *)v41;
                    }
                    else
                    {
                        if(!a3 && !*(_DWORD *)(**(_DWORD **)v41 + 8))
                            v40 = *(_DWORD *)v41;
                    }
                }
                v41 = *(_DWORD *)(v41 + 4);
            }
            if(v40)
            {
                if(*(_DWORD *)(*(_DWORD *)(v47 + 20) + 72) != -1)
                {
                    --*(_DWORD *)(v47 + 64);
                    CNetMsg::CNetMsg((int)&v46);
                    ItemUpdateMsg((int)&v46, v47, 0LL);
                    if(*(_DWORD *)(a1->Unk768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v46);
                    CNetMsg::_CNetMsg((int)&v46, 2);
                }
                *(_WORD *)(a2->Unk76) -= *(_WORD *)(*(_DWORD *)(v47 + 20) + 76);
                *(_DWORD *)(a2->Unk740) += *(_DWORD *)(*(_DWORD *)(v47 + 20) + 76);
                if(*(_WORD *)(a2->Unk76) <= 0)
                    *(_WORD *)(a2->Unk76) = 0;
                AddAttackList(a1, a2, 0);
                for(j = *(_DWORD *)(a2->Unk396); j; j = *(_DWORD *)(j + 20))
                {
                    if(*(_DWORD *)(j + 16) == a1)
                    {
                        *(_DWORD *)j += *(_DWORD *)(*(_DWORD *)(v47 + 20) + 76);
                        *(_DWORD *)(j + 8) = gserver.Unk41248;
                        break;
                    }
                }
                CNetMsg::CNetMsg((int)&v46);
                EffectProduceMsg__FR7CNetMsgP10CCharacterT115_tagProduceKind((int)&v46, a1, a2, a3);
                CArea::SendToCell(*(_DWORD *)(a1->Unk412), (int)&v46, a1, 1, 4);
                if(!(*(_DWORD *)j % 5))
                {
                    *(_DWORD *)j = 0;
                    v34 = *(_DWORD *)(4 * (*(_BYTE *)(v40 + 4) - 1) + *(_DWORD *)v40 + 68);
                    v35 = *(_DWORD *)(4 * (*(_BYTE *)(v40 + 4) - 1) + *(_DWORD *)v40 + 88)
                            + *(_DWORD *)(4 * (*(_BYTE *)(v40 + 4) - 1) + *(_DWORD *)v40 + 68);
                    v36 = *(_DWORD *)(4 * (*(_BYTE *)(v40 + 4) - 1) + *(_DWORD *)v40 + 88)
                            + *(_DWORD *)(4 * (*(_BYTE *)(v40 + 4) - 1) + *(_DWORD *)v40 + 68)
                            + *(_DWORD *)(4 * (*(_BYTE *)(v40 + 4) - 1) + *(_DWORD *)v40 + 108);
                    v37 = *(_DWORD *)(4 * (*(_BYTE *)(v40 + 4) - 1) + *(_DWORD *)v40 + 108)
                            + *(_DWORD *)(4 * (*(_BYTE *)(v40 + 4) - 1) + *(_DWORD *)v40 + 88)
                            + *(_DWORD *)(4 * (*(_BYTE *)(v40 + 4) - 1) + *(_DWORD *)v40 + 68)
                            + *(_DWORD *)(4 * (*(_BYTE *)(v40 + 4) - 1) + *(_DWORD *)v40 + 128);
                    v38 = *(_DWORD *)(4 * (*(_BYTE *)(v40 + 4) - 1) + *(_DWORD *)v40 + 128)
                            + *(_DWORD *)(4 * (*(_BYTE *)(v40 + 4) - 1) + *(_DWORD *)v40 + 108)
                            + *(_DWORD *)(4 * (*(_BYTE *)(v40 + 4) - 1) + *(_DWORD *)v40 + 88)
                            + *(_DWORD *)(4 * (*(_BYTE *)(v40 + 4) - 1) + *(_DWORD *)v40 + 68)
                            + *(_DWORD *)(4 * (*(_BYTE *)(v40 + 4) - 1) + *(_DWORD *)v40 + 148);
                    memcpy(v39, &v34, sizeof(v39));
                    v33 = GetRandom(1, 10000);
                    v32 = 0;
                    for(k = 0; k <= 4; ++k)
                    {
                        if(*(_DWORD *)(4 * k + *(_DWORD *)(a2->Unk464) + 268) != -1)
                        {
                            if(*(_DWORD *)(*(_DWORD *)(a2->Unk464) + 92) & 0x2000)
                                *(_DWORD *)&v39[4 * k] = 30 * *(_DWORD *)&v39[4 * k] / 100;
                            if((unsigned __int8)CArea::GetAttr(
                                                                            *(_DWORD *)(a2->Unk412),
                                                                            *(_BYTE *)(a2->Unk136),
                                                                            *(float *)(a2->Unk120),
                                                                            *(float *)(a2->Unk124)) == 20)
                                *(_DWORD *)&v39[4 * k] = 60 * *(_DWORD *)&v39[4 * k] / 100;
                            if((signed int)v33 <= *(_DWORD *)&v39[4 * k])
                            {
                                v30 = 1;
                                if(unk_8168B24)
                                    v30 = 2;
                                v32 = CItemList::CreateItem(
                                                gserver.Unk41208,
                                                *(_DWORD *)(4 * k + *(_DWORD *)(a2->Unk464) + 268),
                                                -1,
                                                0,
                                                0,
                                                (signed int)v30);
                                break;
                            }
                        }
                    }
                    if(v32 && *(_DWORD *)(*(_DWORD *)(v32 + 20) + 4) == 4 && *(_DWORD *)(*(_DWORD *)(v32 + 20) + 8) == 6)
                    {
                        CNetMsg::CNetMsg((int)&v34);
                        if(*(_DWORD *)(*(_DWORD *)(v32 + 20) + 4) != 4
                            || *(_DWORD *)(*(_DWORD *)(v32 + 20) + 8) && *(_DWORD *)(*(_DWORD *)(v32 + 20) + 8) != 1)
                        {
                            v4 = a1->Unk792;
                        }
                        else
                        {
                            if(*(_DWORD *)(*(_DWORD *)(v32 + 20) + 4) != 4 || *(_DWORD *)(*(_DWORD *)(v32 + 20) + 8))
                            {
                                if(*(_DWORD *)(*(_DWORD *)(v32 + 20) + 4) == 4
                                    && *(_DWORD *)(*(_DWORD *)(v32 + 20) + 8)
                                    && *(_DWORD *)(*(_DWORD *)(v32 + 20) + 8) == 1)
                                    v4 = a1->Unk968;
                                else
                                    v4 = 0;
                            }
                            else
                            {
                                v4 = a1->Unk880;
                            }
                        }
                        v30 = v4;
                        if(!v4)
                        {
                            CNetMsg::_CNetMsg((int)&v34, 2);
                            CNetMsg::_CNetMsg((int)&v46, 2);
                            return CNetMsg::_CNetMsg((int)&v48, 2);
                        }
                        v29 = 0;
                        if(CInventory::AddItem(v30, v32, a1, 1, 1, -1, -1))
                        {
                            if(CItem::tab(v32) == -1)
                            {
                                v29 = 1;
                                if(CInventory::FindItem(
                                             v30,
                                             (int)&v28,
                                             (int)&v27,
                                             *(_DWORD *)(v32 + 28),
                                             *(_DWORD *)(v32 + 36),
                                             *(_DWORD *)(v32 + 40)))
                                {
                                    l = CInventory::GetItem(v30, v28, v27);
                                    if(l)
                                    {
                                        v5 = CItem::Count(v32);
                                        ItemUpdateMsg((int)&v34, l, v5);
                                    }
                                }
                            }
                            else
                            {
                                ItemAddMsg((int)&v34, v32);
                            }
                            if(*(_DWORD *)(a1->Unk768))
                                CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v34);
                            v6 = CItem::Count(v32);
                            v7 = *(_DWORD *)(v32 + 40);
                            v8 = *(_DWORD *)(v32 + 36);
                            v9 = (const char *)(v32 + 44);
                            v10 = (const char *)(*(_DWORD *)(v32 + 20) + 12);
                            init((int)&v25, (int)"ITEM_PICK", a1->Unk8, *(_DWORD *)(a1->Unk768) + 4);
                            v11 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v25);
                            v12 = (int)CLogBuffer::__ls(v11, v10);
                            v13 = CLogBuffer::__ls(v12, (int (__cdecl *)(_DWORD))delim);
                            v14 = (int)CLogBuffer::__ls((const char *)v13, v9);
                            v15 = CLogBuffer::__ls(v14, (int (__cdecl *)(_DWORD))delim);
                            v16 = (int)CLogBuffer::__ls((char *)v15, v8);
                            v17 = CLogBuffer::__ls(v16, (int (__cdecl *)(_DWORD))delim);
                            v18 = (int)CLogBuffer::__ls((char *)v17, v7);
                            v19 = CLogBuffer::__ls(v18, (int (__cdecl *)(_DWORD))delim);
                            v20 = (int)CLogBuffer::__ls((char *)v19, v6);
                            v21 = CLogBuffer::__ls(v20, (int (__cdecl *)(_DWORD))delim);
                            v22 = (int)CLogBuffer::__ls((char *)v21, 0);
                            CLogBuffer::__ls(v22, end);
                        }
                        else
                        {
                            v32 = CArea::DropItem(*(_DWORD *)(a2->Unk412), v32, a2);
                            if(!v32)
                            {
                                CNetMsg::_CNetMsg((int)&v34, 2);
                                CNetMsg::_CNetMsg((int)&v46, 2);
                                return CNetMsg::_CNetMsg((int)&v48, 2);
                            }
                            CNetMsg::CNetMsg((int)&v24);
                            ItemDropMsg((int)&v24, a2, v32);
                            CArea::SendToCell(*(_DWORD *)(a2->Unk412), (int)&v24, a2, 1, 4);
                            *(_DWORD *)(v32 + 216) = *(_DWORD *)(a1->Unk4);
                            CNetMsg::_CNetMsg((int)&v24, 2);
                        }
                        if(v29)
                        {
                            if(v32)
                                (*(void (__cdecl **)(int, signed int))(*(_DWORD *)(v32 + 220) + 8))(v32, 3);
                            v32 = 0;
                        }
                        CNetMsg::CNetMsg((int)&v24);
                        if(a3 == 1)
                        {
                            EffectEtcMsg((int)&v24, a1, 3);
                        }
                        else
                        {
                            if(a3 > 1)
                            {
                                if(a3 == 2)
                                    EffectEtcMsg((int)&v24, a1, 4);
                            }
                            else
                            {
                                if(!a3)
                                    EffectEtcMsg((int)&v24, a1, 2);
                            }
                        }
                        CArea::SendToCell(*(_DWORD *)(a1->Unk412), (int)&v24, a1, 1, 4);
                        CNetMsg::_CNetMsg((int)&v24, 2);
                        CNetMsg::_CNetMsg((int)&v34, 2);
                    }
                }
                if(*(_WORD *)(a2->Unk76) <= 0)
                {
                    if(*(_DWORD *)(*(_DWORD *)(a2->Unk464) + 92) & 0x2000)
                    {
                        *(_WORD *)(a2->Unk76) = *(_WORD *)(a1->Unk78);
                    }
                    else
                    {
                        for(l = 0; l <= 3; ++l)
                        {
                            if(*(_DWORD *)(*(_DWORD *)(a2->Unk464) + 264) > 0)
                            {
                                v27 = 0;
                                v30 = GetRandom(0, 19);
                                if(*(_DWORD *)(4 * v30 + *(_DWORD *)(a2->Unk464) + 104) != -1)
                                {
                                    v23 = GetRandom(1, 10000);
                                    if((signed int)v23 <= *(_DWORD *)(4 * v30 + *(_DWORD *)(a2->Unk464) + 184))
                                        v27 = CArea::DropItem(
                                                        *(_DWORD *)(a2->Unk412),
                                                        *(_DWORD *)(4 * v30 + *(_DWORD *)(a2->Unk464) + 104),
                                                        a2,
                                                        0,
                                                        0,
                                                        1LL,
                                                        1);
                                }
                                if(v27)
                                {
                                    CNetMsg::CNetMsg((int)&v24);
                                    ItemDropMsg((int)&v24, a2, v27);
                                    CArea::SendToCell(
                                        *(_DWORD *)(a2->Unk412),
                                        (int)&v24,
                                        *(_BYTE *)(v27 + 192),
                                        *(_DWORD *)(v27 + 196),
                                        *(_DWORD *)(v27 + 200),
                                        4);
                                    *(_DWORD *)(v27 + 216) = -1;
                                    CNetMsg::_CNetMsg((int)&v24, 2);
                                }
                            }
                        }
                        DelAttackList(a2);
                        CArea::CharFromCell(*(_DWORD *)(a1->Unk412), a2);
                        CArea::DelNPC(*(_DWORD *)(a1->Unk412), a2);
                    }
                }
                CNetMsg::_CNetMsg((int)&v46, 2);
                result = CNetMsg::_CNetMsg((int)&v48, 2);
            }
            else
            {
                SysMsg((int)&v48, 34);
                if(*(_DWORD *)(a1->Unk768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v48);
                result = CNetMsg::_CNetMsg((int)&v48, 2);
            }
        }
        else
        {
            SysMsg((int)&v48, 33);
            if(*(_DWORD *)(a1->Unk768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v48);
            result = CNetMsg::_CNetMsg((int)&v48, 2);
        }
    }
    else
    {
        CNetMsg::CNetMsg((int)&v46);
        ItemWearMsg((int)&v46, 2, 0, v47);
        if(*(_DWORD *)(a1->Unk768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v46);
        WearingMsg((int)&v46, a1, 2, 0xFFFFFFFFu);
        CArea::SendToCell(*(_DWORD *)(a1->Unk412), (int)&v46, a1, 0, 4);
        ItemDeleteMsg((int)&v46, v47);
        if(*(_DWORD *)(a1->Unk768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v46);
        CInventory::Remove(a1->Unk792, v47, 1, 1);
        v47 = 0;
        SysMsg((int)&v48, 32);
        if(*(_DWORD *)(a1->Unk768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v48);
        CNetMsg::_CNetMsg((int)&v46, 2);
        result = CNetMsg::_CNetMsg((int)&v48, 2);
    }
    return result;
}
// 80BCCF0: using guessed type char var_58[20];
*/
