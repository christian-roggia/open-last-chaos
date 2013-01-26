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

void do_Item(CPC *a1, CNetMsg &a2)
{
    /* TODO */
}

/*void do_Item(CPC *a1, CNetMsg &a2)
{
    char result; // al@1
    char dest; // [sp+17h] [bp-1h]@6

    result = a1;
    if(*(_WORD *)(a1 + 76) > 0)
    {
        result = a1;
        if(!*(_DWORD *)(a1 + 1324))
        {
            result = a1;
            if(!*(_DWORD *)(a1 + 424))
            {
                result = a1;
                if(!*(_DWORD *)(a1 + 1328))
                {
                    CNetMsg::MoveFirst(a2);
                    CNetMsg::__rs(a2, &dest);
                    result = dest;
                    switch(dest)
                    {
                        case 0:
                            result = do_ItemUse(a1, a2);
                            break;
                        case 1:
                            result = do_ItemTake(a1, a2);
                            break;
                        case 2:
                            result = do_ItemThrow(a1, a2);
                            break;
                        case 3:
                            result = do_ItemArrange(a1, a2);
                            break;
                        case 4:
                            result = do_ItemDelete(a1, a2);
                            break;
                        case 5:
                            result = do_ItemWear(a1, a2);
                            break;
                        case 6:
                            result = do_ItemSwap(a1, a2);
                            break;
                        case 0xC:
                            result = do_ItemBuy(a1, a2);
                            break;
                        case 0xD:
                            result = do_ItemSell(a1, a2);
                            break;
                        case 0xE:
                            result = do_ItemUpgradeReq(a1, a2);
                            break;
                        case 0x10:
                            result = do_ItemRefinReq(a1, a2);
                            break;
                        case 0x12:
                            result = do_ItemOptionAddReq(a1, a2);
                            break;
                        case 0x14:
                            result = do_ItemOptionDelReq(a1, a2);
                            break;
                        case 0x16:
                            result = do_ItemProcessReq(a1, a2);
                            break;
                        case 0x18:
                            result = do_ItemMakeReq(a1, a2);
                            break;
                        case 0x1A:
                            result = do_ItemMixReq(a1, a2);
                            break;
                        case 0x1D:
                            result = do_ItemArcaneReq(a1, a2);
                            break;
                        default:
                            return result;
                    }
                }
            }
        }
    }
    return result;
}
// 80AE180: using guessed type _DWORD __cdecl do_ItemOptionAddReq(_DWORD, _DWORD);
// 80B39A0: using guessed type _DWORD __cdecl do_ItemArcaneReq(_DWORD, _DWORD);

//----- (080A7D80) --------------------------------------------------------
int __cdecl do_ItemUse(int a1, int a2)
{
    int v2; // eax@1
    int v3; // eax@1
    int v4; // eax@1
    int v5; // eax@1
    int v6; // eax@1
    int v7; // eax@2
    __int64 v8; // qax@15
    int v9; // eax@21
    int v10; // eax@24
    __int64 v11; // qax@55
    char v13; // [sp+14h] [bp-44h]@29
    int v14; // [sp+28h] [bp-30h]@28
    int v15; // [sp+2Ch] [bp-2Ch]@13
    int v16; // [sp+30h] [bp-28h]@9
    int v17; // [sp+34h] [bp-24h]@8
    int v18; // [sp+38h] [bp-20h]@1
    int v19; // [sp+4Ch] [bp-Ch]@1
    uint32_t dest; // [sp+50h] [bp-8h]@1
    char v21; // [sp+54h] [bp-4h]@1
    char v22; // [sp+55h] [bp-3h]@1
    char v23; // [sp+56h] [bp-2h]@1
    char v24; // [sp+57h] [bp-1h]@1

    CNetMsg::MoveFirst(a2);
    v2 = CNetMsg::__rs(a2, &v24);
    v3 = CNetMsg::__rs(v2, &v23);
    v4 = CNetMsg::__rs(v3, &v22);
    v5 = CNetMsg::__rs(v4, &v21);
    v6 = CNetMsg::__rs(v5, &dest);
    CNetMsg::__rs(v6, &v19);
    CNetMsg::CNetMsg((int)&v18);
    if(v23)
    {
        if(v23 == 1)
        {
            v7 = a1 + 880;
        }
        else
        {
            if(v23 == 2)
                v7 = a1 + 968;
            else
                v7 = 0;
        }
    }
    else
    {
        v7 = a1 + 792;
    }
    v17 = v7;
    if(!v7
        || (v16 = CInventory::GetItem(v17, v22, v21)) == 0
        || *(_DWORD *)(v16 + 24) != dest
        || *(_BYTE *)(v16 + 32) != -1
        || (v15 = *(_DWORD *)(v16 + 20), *(_DWORD *)(v15 + 4) != 2) && *(_DWORD *)(v15 + 4) != 6)
        return CNetMsg::_CNetMsg((int)&v18, 2);
    v8 = CItem::Count(v16);
    if(SHIDWORD(v8) <= 0 && (HIDWORD(v8) || !(_DWORD)v8))
    {
        ItemDeleteMsg((int)&v18, v16);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v18);
        CInventory::Remove(v17, v16, 1, 1);
        return CNetMsg::_CNetMsg((int)&v18, 2);
    }
    v9 = *(_DWORD *)(v15 + 4);
    if(v9 != 2)
    {
        if(v9 == 6)
        {
            v14 = 0;
            if(*(_DWORD *)(v15 + 8) == 6)
                v14 = CSkillProtoList::Create(gserver.Unk452220, *(_DWORD *)(v15 + 76), *(_DWORD *)(v16 + 40));
            else
                v14 = CSkillProtoList::Create(gserver.Unk452220, *(_DWORD *)(v15 + 76), *(_DWORD *)(v15 + 80));
            if(!v14)
                return CNetMsg::_CNetMsg((int)&v18, 2);
            ApplySkill(a1, a1, v14, *(_DWORD *)v15);
            __builtin_delete(v14);
            CNetMsg::CNetMsg((int)&v13);
            EffectItemMsg((int)&v13, a1, v16);
            CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v13, a1, 1, 4);
            CNetMsg::_CNetMsg((int)&v13, 2);
        }
        goto LABEL_53;
    }
    v10 = *(_DWORD *)(v15 + 8);
    if(v10)
    {
        if(v10 != 5)
            goto LABEL_53;
        v14 = CPC::CanChange(a1);
        CNetMsg::CNetMsg((int)&v13);
        if(v14 != -1)
        {
            ChangeErrMsg((int)&v13, v14);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v13);
            CNetMsg::_CNetMsg((int)&v13, 2);
            return CNetMsg::_CNetMsg((int)&v18, 2);
        }
        if(*(_DWORD *)(a1 + 60) < *(_DWORD *)(v15 + 84))
        {
            ChangeErrMsg((int)&v13, 7);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v13);
            CNetMsg::_CNetMsg((int)&v13, 2);
            return CNetMsg::_CNetMsg((int)&v18, 2);
        }
        if(**(_DWORD **)(a1 + 408) != *(_DWORD *)(v15 + 88))
        {
            ChangeErrMsg((int)&v13, 8);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v13);
            CNetMsg::_CNetMsg((int)&v13, 2);
            return CNetMsg::_CNetMsg((int)&v18, 2);
        }
        DelAttackList(a1);
        *(_DWORD *)(a1 + 2384) = *(_DWORD *)(v15 + 80);
        *(_DWORD *)(a1 + 2388) = *(_DWORD *)(v15 + 76);
        CPC::SetPlayerState(a1, 64);
        ChangeStartMsg((int)&v13, a1);
        CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v13, a1, 1, 4);
        CNetMsg::_CNetMsg((int)&v13, 2);
LABEL_53:
        ItemUseMsg((int)&v18, a1, v23, v22, v21, dest, v19);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v18);
        CInventory::Decrease(v17, v16, 1LL);
        v11 = CItem::Count(v16);
        if(SHIDWORD(v11) <= 0 && (HIDWORD(v11) || !(_DWORD)v11))
        {
            ItemDeleteMsg((int)&v18, v16);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v18);
            CInventory::Remove(v17, v16, 1, 1);
        }
        else
        {
            ItemUpdateMsg((int)&v18, v16, -1LL);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v18);
        }
        return CNetMsg::_CNetMsg((int)&v18, 2);
    }
    if(*(_DWORD *)(v15 + 76))
        return CNetMsg::_CNetMsg((int)&v18, 2);
    v14 = CPC::CanWarp(a1);
    if(!v14)
    {
        *(_DWORD *)(a1 + 1360) = 0;
        *(_DWORD *)(a1 + 1364) = 0;
        *(_DWORD *)(a1 + 1356) = 100;
        CPC::SetPlayerState(a1, 4);
        CNetMsg::CNetMsg((int)&v13);
        WarpStartMsg((int)&v13, a1);
        CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v13, a1, 1, 4);
        CNetMsg::_CNetMsg((int)&v13, 2);
        goto LABEL_53;
    }
    CNetMsg::CNetMsg((int)&v13);
    SysMsg((int)&v13, v14);
    if(*(_DWORD *)(a1 + 768))
        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v13);
    CNetMsg::_CNetMsg((int)&v13, 2);
    return CNetMsg::_CNetMsg((int)&v18, 2);
}
// 8049BCC: using guessed type int __cdecl __builtin_delete(_DWORD);

//----- (080A8570) --------------------------------------------------------
int __cdecl do_ItemTake(int a1, int a2)
{
    int result; // eax@1
    int v3; // eax@2
    int v4; // eax@2
    int v5; // eax@38
    __int64 v6; // qax@56
    signed int v7; // ST88_4@67
    __int64 v8; // ST70_8@67
    signed int v9; // ST58_4@67
    signed int v10; // ST40_4@67
    const char *v11; // ST28_4@67
    const char *v12; // ST10_4@67
    const char *v13; // eax@67
    int v14; // eax@67
    int v15; // eax@67
    int v16; // eax@67
    int v17; // eax@67
    int v18; // eax@67
    int v19; // eax@67
    int v20; // eax@67
    int v21; // eax@67
    int v22; // eax@67
    int v23; // eax@67
    signed int v24; // ST88_4@70
    signed int v25; // ST70_4@70
    int v26; // eax@70
    int v27; // eax@70
    int v28; // eax@70
    int v29; // [sp+10h] [bp-98h]@62
    int k; // [sp+24h] [bp-84h]@55
    int v31; // [sp+28h] [bp-80h]@54
    int v32; // [sp+2Ch] [bp-7Ch]@54
    char v33; // [sp+33h] [bp-75h]@52
    int v34; // [sp+34h] [bp-74h]@50
    int v35; // [sp+38h] [bp-70h]@33
    int v36; // [sp+3Ch] [bp-6Ch]@33
    int v37; // [sp+40h] [bp-68h]@33
    char v38; // [sp+54h] [bp-54h]@33
    char v39; // [sp+68h] [bp-40h]@30
    int v40; // [sp+7Ch] [bp-2Ch]@13
    int v41; // [sp+80h] [bp-28h]@14
    int j; // [sp+84h] [bp-24h]@8
    int i; // [sp+88h] [bp-20h]@3
    int v44; // [sp+8Ch] [bp-1Ch]@3
    int v45; // [sp+90h] [bp-18h]@3
    int v46; // [sp+94h] [bp-14h]@3
    int v47; // [sp+98h] [bp-10h]@3
    int v48; // [sp+9Ch] [bp-Ch]@2
    int dest; // [sp+A0h] [bp-8h]@2
    char v50; // [sp+A7h] [bp-1h]@2

    result = a1;
    if(*(_BYTE *)(a1 + 420))
    {
        CNetMsg::MoveFirst(a2);
        v3 = CNetMsg::__rs(a2, &v50);
        v4 = CNetMsg::__rs(v3, &dest);
        CNetMsg::__rs(v4, &v48);
        result = *(_DWORD *)(a1 + 4);
        if(result == dest)
        {
            v47 = *(_DWORD *)(a1 + 140) - 1;
            v46 = *(_DWORD *)(a1 + 140) + 1;
            v45 = *(_DWORD *)(a1 + 144) - 1;
            v44 = *(_DWORD *)(a1 + 144) + 1;
            for(i = v47; ; ++i)
            {
                result = i;
                if(i > v46)
                    return result;
                if(i >= 0 && i < *(_DWORD *)(*(_DWORD *)(a1 + 412) + 12))
                    break;
LABEL_78:
                ;
            }
            for(j = v45; ; ++j)
            {
                if(j > v44)
                    goto LABEL_78;
                if(j >= 0 && j < *(_DWORD *)(*(_DWORD *)(a1 + 412) + 16))
                    break;
LABEL_77:
                ;
            }
            v40 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(a1 + 412) + 28) + 4 * i) + 16 * j + 4);
            while(1)
            {
                while(1)
                {
                    v41 = v40;
                    if(!v40)
                        goto LABEL_77;
                    v40 = *(_DWORD *)(v41 + 208);
                    if(*(_BYTE *)(a1 + 136) - (signed int)*(_BYTE *)(v41 + 192) < 0)
                        break;
                    if(*(_BYTE *)(a1 + 136) - (signed int)*(_BYTE *)(v41 + 192) <= 1)
                        goto LABEL_20;
                }
                if(*(_BYTE *)(v41 + 192) - (signed int)*(_BYTE *)(a1 + 136) <= 1)
                {
LABEL_20:
                    if(*(_DWORD *)(v41 + 24) == v48)
                    {
                        if(*(_DWORD *)(v41 + 28) != *unk_8104584
                            || !CPC::IsParty(a1)
                            || (unsigned __int8)CParty::GetPartyType(*(_DWORD *)(a1 + 1368)))
                        {
                            if(!CPC::IsParty(a1) || (unsigned __int8)CParty::GetPartyType(*(_DWORD *)(a1 + 1368)))
                            {
                                if(*(_DWORD *)(v41 + 216) == -1 || *(_DWORD *)(v41 + 216) == *(_DWORD *)(a1 + 4))
                                {
                                    CNetMsg::CNetMsg((int)&v39);
                                    CNetMsg::CNetMsg((int)&v38);
                                    CNetMsg::CNetMsg((int)&v37);
                                    v36 = *(_DWORD *)(v41 + 196);
                                    v35 = *(_DWORD *)(v41 + 200);
                                    ItemTakeMsg((int)&v38, a1, v41);
                                    ItemDisappearMsg((int)&v39, v41);
                                    if(*(_DWORD *)(*(_DWORD *)(v41 + 20) + 4) != 4
                                        || *(_DWORD *)(*(_DWORD *)(v41 + 20) + 8) && *(_DWORD *)(*(_DWORD *)(v41 + 20) + 8) != 1)
                                    {
                                        v5 = a1 + 792;
                                    }
                                    else
                                    {
                                        if(*(_DWORD *)(*(_DWORD *)(v41 + 20) + 4) != 4 || *(_DWORD *)(*(_DWORD *)(v41 + 20) + 8))
                                        {
                                            if(*(_DWORD *)(*(_DWORD *)(v41 + 20) + 4) == 4
                                                && *(_DWORD *)(*(_DWORD *)(v41 + 20) + 8)
                                                && *(_DWORD *)(*(_DWORD *)(v41 + 20) + 8) == 1)
                                                v5 = a1 + 968;
                                            else
                                                v5 = 0;
                                        }
                                        else
                                        {
                                            v5 = a1 + 880;
                                        }
                                    }
                                    v34 = v5;
                                    if(v5)
                                    {
                                        v33 = 0;
                                        if(CInventory::AddItem(v34, v41, a1, 1, 1, -1, -1))
                                        {
                                            if(CItem::tab(v41) == -1)
                                            {
                                                v33 = 1;
                                                if(CInventory::FindItem(
                                                             v34,
                                                             (int)&v32,
                                                             (int)&v31,
                                                             *(_DWORD *)(v41 + 28),
                                                             *(_DWORD *)(v41 + 36),
                                                             *(_DWORD *)(v41 + 40)))
                                                {
                                                    k = CInventory::GetItem(v34, v32, v31);
                                                    if(k)
                                                    {
                                                        v6 = CItem::Count(v41);
                                                        ItemUpdateMsg((int)&v37, k, v6);
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                ItemAddMsg((int)&v37, v41);
                                                if(*(_DWORD *)(v41 + 28) == *unk_8104584 && !*(_DWORD *)(a1 + 1280))
                                                    *(_DWORD *)(a1 + 1280) = v41;
                                            }
                                            *(_DWORD *)(v41 + 216) = -1;
                                            CArea::ItemFromCell(*(_DWORD *)(a1 + 412), v41);
                                            CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v38, a1, 1, 4);
                                            if(*(_DWORD *)(a1 + 768))
                                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v37);
                                            CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v39, *(_BYTE *)(a1 + 136), v36, v35, 4);
                                            v7 = *(_DWORD *)(v41 + 168);
                                            v8 = CItem::Count(v41);
                                            v9 = *(_DWORD *)(v41 + 40);
                                            v10 = *(_DWORD *)(v41 + 36);
                                            v11 = (const char *)(v41 + 44);
                                            v12 = (const char *)(*(_DWORD *)(v41 + 20) + 12);
                                            init((int)&v29, (int)"ITEM_PICK", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
                                            v13 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v29);
                                            v14 = (int)CLogBuffer::__ls(v13, v12);
                                            v15 = CLogBuffer::__ls(v14, (int (__cdecl *)(_DWORD))delim);
                                            v16 = (int)CLogBuffer::__ls((const char *)v15, v11);
                                            v17 = CLogBuffer::__ls(v16, (int (__cdecl *)(_DWORD))delim);
                                            v18 = (int)CLogBuffer::__ls((char *)v17, v10);
                                            v19 = CLogBuffer::__ls(v18, (int (__cdecl *)(_DWORD))delim);
                                            v20 = (int)CLogBuffer::__ls((char *)v19, v9);
                                            v21 = CLogBuffer::__ls(v20, (int (__cdecl *)(_DWORD))delim);
                                            v22 = (int)CLogBuffer::__ls((char *)v21, v8);
                                            v23 = CLogBuffer::__ls(v22, (int (__cdecl *)(_DWORD))delim);
                                            CLogBuffer::__ls((char *)v23, v7);
                                            for(k = 0; k < *(_DWORD *)(v41 + 168); ++k)
                                            {
                                                if(*(_DWORD *)(20 * k + v41 + 68))
                                                {
                                                    v24 = *(_DWORD *)(20 * k + v41 + 76);
                                                    v25 = *(_DWORD *)(20 * k + v41 + 72);
                                                    v26 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
                                                    v27 = (int)CLogBuffer::__ls((char *)v26, v25);
                                                    v28 = CLogBuffer::__ls(v27, (int (__cdecl *)(_DWORD))delim);
                                                    CLogBuffer::__ls((char *)v28, v24);
                                                }
                                            }
                                            CLogBuffer::__ls((int)g_gamelogbuffer, end);
                                            if(v33 && v41)
                                                (*(void (__cdecl **)(int, signed int))(*(_DWORD *)(v41 + 220) + 8))(v41, 3);
                                            CNetMsg::_CNetMsg((int)&v37, 2);
                                            CNetMsg::_CNetMsg((int)&v38, 2);
                                            result = CNetMsg::_CNetMsg((int)&v39, 2);
                                        }
                                        else
                                        {
                                            CNetMsg::CNetMsg((int)&v29);
                                            SysFullInventoryMsg((int)&v29, *(_BYTE *)(v34 + 4));
                                            if(*(_DWORD *)(a1 + 768))
                                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v29);
                                            CNetMsg::_CNetMsg((int)&v29, 2);
                                            CNetMsg::_CNetMsg((int)&v37, 2);
                                            CNetMsg::_CNetMsg((int)&v38, 2);
                                            result = CNetMsg::_CNetMsg((int)&v39, 2);
                                        }
                                    }
                                    else
                                    {
                                        CNetMsg::_CNetMsg((int)&v37, 2);
                                        CNetMsg::_CNetMsg((int)&v38, 2);
                                        result = CNetMsg::_CNetMsg((int)&v39, 2);
                                    }
                                }
                                else
                                {
                                    CNetMsg::CNetMsg((int)&v39);
                                    SysMsg((int)&v39, 15);
                                    if(*(_DWORD *)(a1 + 768))
                                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v39);
                                    result = CNetMsg::_CNetMsg((int)&v39, 2);
                                }
                            }
                            else
                            {
                                result = GetItemRandomParty(a1, v41);
                            }
                        }
                        else
                        {
                            result = DivisionPartyMoney(a1, v41);
                        }
                        return result;
                    }
                }
            }
        }
    }
    return result;
}

//----- (080A8FC0) --------------------------------------------------------
int __cdecl do_ItemWear(int a1, int a2)
{
    int v2; // eax@1
    int v3; // eax@1
    int v4; // eax@1
    int v5; // eax@1
    int v6; // eax@1
    int result; // eax@5
    int v8; // eax@15
    char v9; // [sp+Ch] [bp-5Ch]@31
    int v10; // [sp+20h] [bp-48h]@21
    int v11; // [sp+34h] [bp-34h]@29
    int v12; // [sp+38h] [bp-30h]@29
    int v13; // [sp+3Ch] [bp-2Ch]@21
    int v14; // [sp+40h] [bp-28h]@21
    int i; // [sp+44h] [bp-24h]@7
    char v16; // [sp+48h] [bp-20h]@3
    int dest; // [sp+5Ch] [bp-Ch]@1
    char v18; // [sp+63h] [bp-5h]@1
    char v19; // [sp+64h] [bp-4h]@1
    char v20; // [sp+65h] [bp-3h]@1
    char v21; // [sp+66h] [bp-2h]@1
    char v22; // [sp+67h] [bp-1h]@1

    CNetMsg::MoveFirst(a2);
    v2 = CNetMsg::__rs(a2, &v22);
    v3 = CNetMsg::__rs(v2, &v21);
    v4 = CNetMsg::__rs(v3, &v20);
    v5 = CNetMsg::__rs(v4, &v19);
    v6 = CNetMsg::__rs(v5, &v18);
    CNetMsg::__rs(v6, &dest);
    if(v21 < 0 || v21 > 10)
    {
        CNetMsg::CNetMsg((int)&v16);
        SysMsg((int)&v16, 2);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v16);
        return CNetMsg::_CNetMsg((int)&v16, 2);
    }
    if(v21 == 10)
    {
        for(i = 7; i <= 9 && *(_DWORD *)(4 * i + a1 + 1284); ++i)
            ;
        if(i == 10)
            v21 = 7;
        else
            v21 = i;
    }
    if(v20)
    {
        if(v20 == 1)
        {
            v8 = a1 + 880;
        }
        else
        {
            if(v20 == 2)
                v8 = a1 + 968;
            else
                v8 = 0;
        }
    }
    else
    {
        v8 = a1 + 792;
    }
    i = v8;
    v14 = CInventory::GetItem(v8, v19, v18);
    v13 = *(_DWORD *)(4 * v21 + a1 + 1284);
    CNetMsg::CNetMsg((int)&v16);
    CNetMsg::CNetMsg((int)&v10);
    if(dest == -1)
    {
        if(!v13)
        {
            CNetMsg::_CNetMsg((int)&v10, 2);
            return CNetMsg::_CNetMsg((int)&v16, 2);
        }
        if(*(_BYTE *)(v13 + 32) == -1)
        {
            CNetMsg::_CNetMsg((int)&v10, 2);
            return CNetMsg::_CNetMsg((int)&v16, 2);
        }
        *(_DWORD *)(4 * v21 + a1 + 1284) = 0;
        *(_BYTE *)(v13 + 32) = -1;
        ItemWearMsg((int)&v16, v21, 0, v13);
        if(v21 > 0 && v21 <= 6)
        {
            WearingMsg((int)&v10, a1, v21, 0xFFFFFFFFu);
            CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v10, a1, 0, 4);
        }
        v12 = v13;
        v11 = -1;
LABEL_42:
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v16);
        if(v12)
        {
            CPC::CalcStatus(a1, 1);
            CNetMsg::_CNetMsg((int)&v10, 2);
            result = CNetMsg::_CNetMsg((int)&v16, 2);
        }
        else
        {
            CNetMsg::_CNetMsg((int)&v10, 2);
            result = CNetMsg::_CNetMsg((int)&v16, 2);
        }
        return result;
    }
    if(v14)
    {
        if(*(_BYTE *)(v14 + 32) != -1)
        {
            CNetMsg::_CNetMsg((int)&v10, 2);
            return CNetMsg::_CNetMsg((int)&v16, 2);
        }
        if(v13)
        {
            *(_DWORD *)(4 * v21 + a1 + 1284) = 0;
            *(_BYTE *)(v13 + 32) = -1;
        }
        *(_DWORD *)(4 * v21 + a1 + 1284) = v14;
        *(_BYTE *)(v14 + 32) = v21;
        ItemWearMsg((int)&v16, v21, v14, v13);
        if(v21 > 0 && v21 <= 6)
        {
            WearingMsg((int)&v10, a1, v21, *(_DWORD *)(v14 + 28));
            CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v10, a1, 0, 4);
        }
        v12 = v14;
        v11 = 1;
        goto LABEL_42;
    }
    CNetMsg::CNetMsg((int)&v9);
    SysMsg((int)&v9, 2);
    if(*(_DWORD *)(a1 + 768))
        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v9);
    CNetMsg::_CNetMsg((int)&v9, 2);
    CNetMsg::_CNetMsg((int)&v10, 2);
    return CNetMsg::_CNetMsg((int)&v16, 2);
}

//----- (080A9570) --------------------------------------------------------
char __cdecl do_ItemSwap(int a1, int a2)
{
    int v2; // eax@1
    int v3; // eax@1
    int v4; // eax@1
    int v5; // eax@1
    int v6; // eax@1
    int v7; // eax@1
    int v8; // eax@1
    const char *v9; // ST5C_4@4
    const char *v10; // eax@4
    int v11; // eax@4
    int v12; // eax@4
    char v14; // [sp+10h] [bp-38h]@14
    int v15; // [sp+24h] [bp-24h]@4
    int v16; // [sp+34h] [bp-14h]@12
    int v17; // [sp+38h] [bp-10h]@1
    int dest; // [sp+3Ch] [bp-Ch]@1
    char v19; // [sp+42h] [bp-6h]@1
    char v20; // [sp+43h] [bp-5h]@1
    char v21; // [sp+44h] [bp-4h]@1
    char v22; // [sp+45h] [bp-3h]@1
    char v23; // [sp+46h] [bp-2h]@1
    char v24; // [sp+47h] [bp-1h]@1

    CNetMsg::MoveFirst(a2);
    v2 = CNetMsg::__rs(a2, &v24);
    v3 = CNetMsg::__rs(v2, &v23);
    v4 = CNetMsg::__rs(v3, &v22);
    v5 = CNetMsg::__rs(v4, &v21);
    v6 = CNetMsg::__rs(v5, &dest);
    v7 = CNetMsg::__rs(v6, &v20);
    v8 = CNetMsg::__rs(v7, &v19);
    CNetMsg::__rs(v8, &v17);
    if(v22 != v20 || v21 != v19 || dest != v17)
    {
        if(v23)
        {
            if(v23 == 1)
            {
                v12 = a1 + 880;
            }
            else
            {
                if(v23 == 2)
                    v12 = a1 + 968;
                else
                    v12 = 0;
            }
        }
        else
        {
            v12 = a1 + 792;
        }
        v16 = v12;
        if(v12)
        {
            LOBYTE(v12) = CInventory::Swap(v16, v22, v21, dest, v20, v19, v17);
            if((_BYTE)v12)
            {
                CNetMsg::CNetMsg((int)&v14);
                ItemSwapMsg((int)&v14, v23, v22, v21, dest, v20, v19);
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v14);
                LOBYTE(v12) = CNetMsg::_CNetMsg((int)&v14, 2);
            }
        }
    }
    else
    {
        *(_BYTE *)(a1 + 475) = 1;
        v9 = (const char *)(*(_DWORD *)(a1 + 768) + 196);
        init((int)&v15, (int)"DEBUG SWAP", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
        v10 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v15);
        v11 = (int)CLogBuffer::__ls(v10, v9);
        LOBYTE(v12) = CLogBuffer::__ls(v11, end);
    }
    return v12;
}

//----- (080A97E0) --------------------------------------------------------
int __cdecl do_ItemArrange(int a1, int a2)
{
    int v2; // eax@1
    int result; // eax@2
    char v4; // [sp+13h] [bp-25h]@14
    char v5; // [sp+14h] [bp-24h]@14
    int v6; // [sp+28h] [bp-10h]@9
    int i; // [sp+2Ch] [bp-Ch]@9
    int v8; // [sp+30h] [bp-8h]@8
    char v9; // [sp+36h] [bp-2h]@1
    char dest; // [sp+37h] [bp-1h]@1

    CNetMsg::MoveFirst(a2);
    v2 = CNetMsg::__rs(a2, &dest);
    CNetMsg::__rs(v2, &v9);
    if(v9)
    {
        if(v9 == 1)
        {
            result = a1 + 880;
        }
        else
        {
            if(v9 == 2)
                result = a1 + 968;
            else
                result = 0;
        }
    }
    else
    {
        result = a1 + 792;
    }
    v8 = result;
    if(result)
    {
        CInventory::Arrange(v8);
        v6 = -1;
        for(i = 0; i <= 19; ++i)
        {
            if(*(_DWORD *)(4 * i + v8 + 8))
                v6 = i;
        }
        CNetMsg::CNetMsg((int)&v5);
        v4 = 1;
        for(i = 0; i <= 19; ++i)
        {
            if(v6 == i)
                v4 |= 2u;
            if(InventoryMsg((int)&v5, a1, v4, v9, i))
            {
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v5);
                v4 = 0;
            }
        }
        for(i = 0; i <= 2; ++i)
        {
            QuickSlotListMsg((int)&v5, a1, i);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v5);
        }
        result = CNetMsg::_CNetMsg((int)&v5, 2);
    }
    return result;
}

//----- (080A99E0) --------------------------------------------------------
int __cdecl do_ItemDelete(int a1, int a2)
{
    int v2; // eax@1
    int v3; // eax@1
    int v4; // eax@1
    int v5; // eax@1
    int v6; // eax@1
    __int64 v7; // qax@1
    __int64 v8; // qax@21
    int v10; // [sp+Ch] [bp-2Ch]@21
    int v11; // [sp+20h] [bp-18h]@16
    int v12; // [sp+24h] [bp-14h]@15
    __int64 dest; // [sp+28h] [bp-10h]@1
    int v14; // [sp+30h] [bp-8h]@1
    char v15; // [sp+34h] [bp-4h]@1
    char v16; // [sp+35h] [bp-3h]@1
    char v17; // [sp+36h] [bp-2h]@1
    char v18; // [sp+37h] [bp-1h]@1

    CNetMsg::MoveFirst(a2);
    v2 = CNetMsg::__rs(a2, &v18);
    v3 = CNetMsg::__rs(v2, &v17);
    v4 = CNetMsg::__rs(v3, &v16);
    v5 = CNetMsg::__rs(v4, &v15);
    v6 = CNetMsg::__rs(v5, &v14);
    LODWORD(v7) = CNetMsg::__rs(v6, &dest);
    if(v17 >= 0 && v17 <= 2 && v16 >= 0 && v16 <= 19 && v15 >= 0 && v15 <= 4)
    {
        if(v17)
        {
            if(v17 == 1)
                LODWORD(v7) = a1 + 880;
            else
                LODWORD(v7) = v17 == 2 ? a1 + 968 : 0;
        }
        else
        {
            LODWORD(v7) = a1 + 792;
        }
        v12 = v7;
        if((_DWORD)v7)
        {
            LODWORD(v7) = CInventory::GetItem(v12, v16, v15);
            v11 = v7;
            if((_DWORD)v7)
            {
                LODWORD(v7) = v11;
                if(*(_DWORD *)(v11 + 24) == v14)
                {
                    v7 = CItem::Count(v11);
                    if(dest <= v7)
                    {
                        LODWORD(v7) = v11;
                        if(*(_BYTE *)(v11 + 32) == -1)
                        {
                            CInventory::Decrease(v12, v11, dest);
                            CNetMsg::CNetMsg((int)&v10);
                            v8 = CItem::Count(v11);
                            if(SHIDWORD(v8) <= 0 && (HIDWORD(v8) || !(_DWORD)v8))
                            {
                                ItemDeleteMsg((int)&v10, v11);
                                if(*(_BYTE *)(v11 + 32) >= 0 && *(_BYTE *)(v11 + 32) <= 9)
                                {
                                    *(_DWORD *)(4 * *(_BYTE *)(v11 + 32) + a1 + 1284) = 0;
                                    *(_BYTE *)(v11 + 32) = -1;
                                }
                                if(v11 == *(_DWORD *)(a1 + 1280))
                                    *(_DWORD *)(a1 + 1280) = 0;
                                CInventory::Remove(v12, v16, v15, 1, 1);
                            }
                            else
                            {
                                ItemUpdateMsg((int)&v10, v11, -dest);
                            }
                            if(*(_DWORD *)(a1 + 768))
                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v10);
                            LODWORD(v7) = CNetMsg::_CNetMsg((int)&v10, 2);
                        }
                    }
                }
            }
        }
    }
    return v7;
}

//----- (080A9CB0) --------------------------------------------------------
int __cdecl do_ItemThrow(int a1, int a2)
{
    __int64 v2; // qax@1
    int v3; // eax@2
    int v4; // eax@2
    int v5; // eax@2
    int v6; // eax@2
    int v7; // eax@2
    __int64 v8; // qax@24
    __int64 v9; // qax@31
    signed int v10; // ST88_4@50
    __int64 v11; // ST70_8@50
    signed int v12; // ST58_4@50
    signed int v13; // ST40_4@50
    const char *v14; // ST28_4@50
    const char *v15; // ST10_4@50
    const char *v16; // eax@50
    int v17; // eax@50
    int v18; // eax@50
    int v19; // eax@50
    int v20; // eax@50
    int v21; // eax@50
    int v22; // eax@50
    int v23; // eax@50
    int v24; // eax@50
    int v25; // eax@50
    int v26; // eax@50
    signed int v27; // ST88_4@53
    signed int v28; // ST70_4@53
    int v29; // eax@53
    int v30; // eax@53
    int v31; // eax@53
    int v33; // [sp+10h] [bp-58h]@50
    char v34; // [sp+20h] [bp-48h]@48
    int i; // [sp+34h] [bp-34h]@28
    int v36; // [sp+38h] [bp-30h]@24
    int v37; // [sp+4Ch] [bp-1Ch]@24
    int v38; // [sp+50h] [bp-18h]@18
    int v39; // [sp+54h] [bp-14h]@17
    __int64 dest; // [sp+58h] [bp-10h]@2
    int v41; // [sp+60h] [bp-8h]@2
    char v42; // [sp+64h] [bp-4h]@2
    char v43; // [sp+65h] [bp-3h]@2
    char v44; // [sp+66h] [bp-2h]@2
    char v45; // [sp+67h] [bp-1h]@2

    LODWORD(v2) = a1;
    if(*(_BYTE *)(a1 + 420))
    {
        CNetMsg::MoveFirst(a2);
        v3 = CNetMsg::__rs(a2, &v45);
        v4 = CNetMsg::__rs(v3, &v44);
        v5 = CNetMsg::__rs(v4, &v43);
        v6 = CNetMsg::__rs(v5, &v42);
        v7 = CNetMsg::__rs(v6, &v41);
        LODWORD(v2) = CNetMsg::__rs(v7, &dest);
        if(v44 >= 0)
        {
            if(v44 <= 2 && v43 >= 0 && v43 <= 19 && v42 >= 0 && v42 <= 4 && SHIDWORD(dest) >= 0)
            {
                if(v44)
                {
                    if(v44 == 1)
                        LODWORD(v2) = a1 + 880;
                    else
                        LODWORD(v2) = v44 == 2 ? a1 + 968 : 0;
                }
                else
                {
                    LODWORD(v2) = a1 + 792;
                }
                v39 = v2;
                if((_DWORD)v2)
                {
                    LODWORD(v2) = CInventory::GetItem(v39, v43, v42);
                    v38 = v2;
                    if((_DWORD)v2)
                    {
                        LODWORD(v2) = v38;
                        if(*(_DWORD *)(v38 + 24) == v41)
                        {
                            v2 = CItem::Count(v38);
                            if(dest <= v2)
                            {
                                LODWORD(v2) = *(_DWORD *)(*(_DWORD *)(v38 + 20) + 68) & 2;
                                if((_DWORD)v2)
                                {
                                    LODWORD(v2) = v38;
                                    if(*(_BYTE *)(v38 + 32) == -1)
                                    {
                                        v37 = 0;
                                        CNetMsg::CNetMsg((int)&v36);
                                        v8 = CItem::Count(v38);
                                        if(v8 == dest)
                                        {
                                            ItemDeleteMsg((int)&v36, v38);
                                            if(*(_BYTE *)(v38 + 32) >= 0 && *(_BYTE *)(v38 + 32) <= 9)
                                            {
                                                *(_DWORD *)(4 * *(_BYTE *)(v38 + 32) + a1 + 1284) = 0;
                                                *(_BYTE *)(v38 + 32) = -1;
                                            }
                                            if(v38 == *(_DWORD *)(a1 + 1280))
                                                *(_DWORD *)(a1 + 1280) = 0;
                                            CInventory::Remove(v39, v43, v42, 0, 1);
                                            v37 = v38;
                                            CArea::DropItem(*(_DWORD *)(a1 + 412), v38, a1);
                                        }
                                        else
                                        {
                                            v37 = CArea::DropItem(
                                                            *(_DWORD *)(a1 + 412),
                                                            *(_DWORD *)(v38 + 28),
                                                            a1,
                                                            *(_DWORD *)(v38 + 36),
                                                            *(_DWORD *)(v38 + 40),
                                                            dest,
                                                            0);
                                            if(!v37)
                                            {
                                                LODWORD(v2) = CNetMsg::_CNetMsg((int)&v36, 2);
                                                return v2;
                                            }
                                            if((*(_BYTE *)(*(_DWORD *)(v38 + 20) + 68) ^ 1) & 1)
                                            {
                                                for(i = 0; i <= 4; ++i)
                                                {
                                                    memcpy((void *)(v37 + 20 * i + 68), (const void *)(v38 + 20 * i + 68), 0x14u);
                                                    *(_DWORD *)(v37 + 168) = *(_DWORD *)(v38 + 168);
                                                }
                                            }
                                            CInventory::Decrease(v39, v38, dest);
                                            v9 = CItem::Count(v38);
                                            if(SHIDWORD(v9) <= 0 && (HIDWORD(v9) || !(_DWORD)v9))
                                            {
                                                ItemDeleteMsg((int)&v36, v38);
                                                if(*(_BYTE *)(v38 + 32) >= 0 && *(_BYTE *)(v38 + 32) <= 9)
                                                {
                                                    *(_DWORD *)(4 * *(_BYTE *)(v38 + 32) + a1 + 1284) = 0;
                                                    *(_BYTE *)(v38 + 32) = -1;
                                                }
                                                if(v38 == *(_DWORD *)(a1 + 1280))
                                                    *(_DWORD *)(a1 + 1280) = 0;
                                                CInventory::Remove(v39, v43, v42, 1, 1);
                                            }
                                            else
                                            {
                                                ItemUpdateMsg((int)&v36, v38, -dest);
                                            }
                                        }
                                        CNetMsg::CNetMsg((int)&v34);
                                        ItemDropMsg((int)&v34, a1, v37);
                                        if(*(_DWORD *)(a1 + 768))
                                            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v36);
                                        CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v34, a1, 1, 4);
                                        v10 = *(_DWORD *)(v37 + 168);
                                        v11 = CItem::Count(v37);
                                        v12 = *(_DWORD *)(v37 + 40);
                                        v13 = *(_DWORD *)(v37 + 36);
                                        v14 = (const char *)(v37 + 44);
                                        v15 = (const char *)(*(_DWORD *)(v37 + 20) + 12);
                                        init((int)&v33, (int)"ITEM_DROP", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
                                        v16 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v33);
                                        v17 = (int)CLogBuffer::__ls(v16, v15);
                                        v18 = CLogBuffer::__ls(v17, (int (__cdecl *)(_DWORD))delim);
                                        v19 = (int)CLogBuffer::__ls((const char *)v18, v14);
                                        v20 = CLogBuffer::__ls(v19, (int (__cdecl *)(_DWORD))delim);
                                        v21 = (int)CLogBuffer::__ls((char *)v20, v13);
                                        v22 = CLogBuffer::__ls(v21, (int (__cdecl *)(_DWORD))delim);
                                        v23 = (int)CLogBuffer::__ls((char *)v22, v12);
                                        v24 = CLogBuffer::__ls(v23, (int (__cdecl *)(_DWORD))delim);
                                        v25 = (int)CLogBuffer::__ls((char *)v24, v11);
                                        v26 = CLogBuffer::__ls(v25, (int (__cdecl *)(_DWORD))delim);
                                        CLogBuffer::__ls((char *)v26, v10);
                                        for(i = 0; i < *(_DWORD *)(v37 + 168); ++i)
                                        {
                                            if(*(_DWORD *)(20 * i + v37 + 68))
                                            {
                                                v27 = *(_DWORD *)(20 * i + v37 + 76);
                                                v28 = *(_DWORD *)(20 * i + v37 + 72);
                                                v29 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
                                                v30 = (int)CLogBuffer::__ls((char *)v29, v28);
                                                v31 = CLogBuffer::__ls(v30, (int (__cdecl *)(_DWORD))delim);
                                                CLogBuffer::__ls((char *)v31, v27);
                                            }
                                        }
                                        CLogBuffer::__ls((int)g_gamelogbuffer, end);
                                        CNetMsg::_CNetMsg((int)&v34, 2);
                                        LODWORD(v2) = CNetMsg::_CNetMsg((int)&v36, 2);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return v2;
}

//----- (080AA400) --------------------------------------------------------
int __cdecl do_ItemBuy(int a1, int a2)
{
    int v2; // eax@1
    int v3; // eax@1
    int v4; // eax@1
    int v5; // ebx@3
    int v6; // eax@3
    void *v7; // STA4_4@6
    int v8; // eax@6
    int v9; // ST11C_4@8
    int v10; // eax@8
    int v11; // ST114_4@12
    int v12; // eax@12
    int v13; // ST110_4@14
    int v14; // eax@14
    int v15; // eax@20
    int v16; // ST10C_4@33
    int v17; // eax@33
    int v18; // ST104_4@37
    int v19; // eax@37
    signed int v20; // STD8_4@38
    __int64 v21; // STF4_8@38
    int v22; // STEC_4@40
    int v23; // eax@40
    __int64 v24; // qax@42
    __int64 v25; // qax@44
    int v26; // STE8_4@46
    int v27; // eax@46
    int v28; // STE4_4@48
    int v29; // eax@48
    __int64 v30; // qax@53
    signed __int64 v31; // ST88_8@55
    signed __int64 v32; // ST70_8@55
    __int64 v33; // ST58_8@55
    const char *v34; // ST40_4@55
    const char *v35; // ST28_4@55
    int v36; // ST10_4@55
    char *v37; // eax@55
    int v38; // eax@55
    int v39; // eax@55
    int v40; // eax@55
    int v41; // eax@55
    int v42; // eax@55
    int v43; // eax@55
    int v44; // eax@55
    int v45; // eax@55
    int v46; // eax@55
    int v47; // eax@55
    int v48; // eax@55
    int result; // eax@66
    int v50; // [sp+7Ch] [bp-78h]@58
    int v51; // [sp+80h] [bp-74h]@57
    int v52; // [sp+84h] [bp-70h]@57
    int v53; // [sp+88h] [bp-6Ch]@55
    int v54; // [sp+98h] [bp-5Ch]@52
    int v55; // [sp+ACh] [bp-48h]@41
    int v56; // [sp+C0h] [bp-34h]@7
    void *s; // [sp+C4h] [bp-30h]@1
    int v58; // [sp+C8h] [bp-2Ch]@1
    int v59; // [sp+CCh] [bp-28h]@1
    int v60; // [sp+D0h] [bp-24h]@1
    __int64 v61; // [sp+D4h] [bp-20h]@9
    __int64 dest; // [sp+DCh] [bp-18h]@1
    int v63; // [sp+E4h] [bp-10h]@1
    int v64; // [sp+E8h] [bp-Ch]@1
    int i; // [sp+ECh] [bp-8h]@4
    char v66; // [sp+F3h] [bp-1h]@1

    CNetMsg::MoveFirst(a2);
    v63 = 0;
    v60 = 0;
    v59 = 0;
    v58 = 0;
    s = 0;
    v2 = CNetMsg::__rs(a2, &v66);
    v3 = CNetMsg::__rs(v2, &v64);
    v4 = CNetMsg::__rs(v3, &dest);
    CNetMsg::__rs(v4, &v63);
    if(v63 > 10 || v63 <= 0)
    {
        v5 = __eh_alloc(4);
        *(_DWORD *)v5 = 0;
        v6 = __tfi();
        __cp_push_exception(v5, v6, 0);
        __throw();
    }
    v59 = __builtin_vec_new(4 * v63);
    v58 = __builtin_vec_new(8 * v63);
    for(i = 0; i < v63; ++i)
    {
        v7 = (void *)(v58 + 8 * i);
        v8 = CNetMsg::__rs(a2, (void *)(v59 + 4 * i));
        CNetMsg::__rs(v8, v7);
    }
    v56 = (int)CZone::FindShop(*(_DWORD *)(a1 + 408), v64);
    if(!v56)
    {
        v9 = __eh_alloc(4);
        *(_DWORD *)v9 = 1;
        v10 = __tfi();
        __cp_push_exception(v9, v10, 0);
        __throw();
    }
    v61 = 0LL;
    s = (void *)__builtin_vec_new(4 * v63);
    memset(s, 0, 4 * v63);
    for(i = 0; i < v63; ++i)
    {
        *((_DWORD *)s + i) = CItemList::CreateItem(gserver.Unk41208, *(_DWORD *)(v59 + 4 * i), -1, 0, 0, *(_QWORD *)(v58 + 8 * i));
        if(!*((_DWORD *)s + i))
        {
            v11 = __eh_alloc(4);
            *(_DWORD *)v11 = 2;
            v12 = __tfi();
            __cp_push_exception(v11, v12, 0);
            __throw();
        }
        if(!CShop::ThersIsItem(v56, *(_DWORD *)(*((_DWORD *)s + i) + 28)))
        {
            v13 = __eh_alloc(4);
            *(_DWORD *)v13 = 6;
            v14 = __tfi();
            __cp_push_exception(v13, v14, 0);
            __throw();
        }
        if(*(_DWORD *)(*(_DWORD *)(*((_DWORD *)s + i) + 20) + 4) != 4
            || *(_DWORD *)(*(_DWORD *)(*((_DWORD *)s + i) + 20) + 8)
            && *(_DWORD *)(*(_DWORD *)(*((_DWORD *)s + i) + 20) + 8) != 1)
        {
            v15 = a1 + 792;
        }
        else
        {
            if(*(_DWORD *)(*(_DWORD *)(*((_DWORD *)s + i) + 20) + 4) != 4
                || *(_DWORD *)(*(_DWORD *)(*((_DWORD *)s + i) + 20) + 8))
            {
                if(*(_DWORD *)(*(_DWORD *)(*((_DWORD *)s + i) + 20) + 4) == 4
                    && *(_DWORD *)(*(_DWORD *)(*((_DWORD *)s + i) + 20) + 8)
                    && *(_DWORD *)(*(_DWORD *)(*((_DWORD *)s + i) + 20) + 8) == 1)
                    v15 = a1 + 968;
                else
                    v15 = 0;
            }
            else
            {
                v15 = a1 + 880;
            }
        }
        v60 = v15;
        if(!v15)
        {
            v16 = __eh_alloc(4);
            *(_DWORD *)v16 = 3;
            v17 = __tfi();
            __cp_push_exception(v16, v17, 0);
            __throw();
        }
        if(!CInventory::AddItem(v60, *((_DWORD *)s + i), a1, 0, 1, -1, -1))
        {
            if(*((_DWORD *)s + i))
                (*(void (__cdecl **)(_DWORD, signed int))(*(_DWORD *)(*((_DWORD *)s + i) + 220) + 8))(*((_DWORD *)s + i), 3);
            *((_DWORD *)s + i) = 0;
            v18 = __eh_alloc(4);
            *(_DWORD *)v18 = 4;
            v19 = __tfi();
            __cp_push_exception(v18, v19, 0);
            __throw();
        }
        v20 = *(_DWORD *)(v56 + 28) * *(_DWORD *)(*(_DWORD *)(*((_DWORD *)s + i) + 20) + 104);
        v21 = v20 / 100 * *(_QWORD *)(v58 + 8 * i);
        HIDWORD(v21) += *(_DWORD *)(v58 + 8 * i) * (v20 / 100 >> 31);
        v61 += v21;
    }
    if(v61 != dest)
    {
        v22 = __eh_alloc(4);
        *(_DWORD *)v22 = 5;
        v23 = __tfi();
        __cp_push_exception(v22, v23, 0);
        __throw();
    }
    CNetMsg::CNetMsg((int)&v55);
    if(*(_DWORD *)(a1 + 1280))
    {
        v24 = CItem::Count(*(_DWORD *)(a1 + 1280));
        if(v24 <= v61)
        {
            v25 = CItem::Count(*(_DWORD *)(a1 + 1280));
            if(v25 == v61)
            {
                ItemDeleteMsg((int)&v55, *(_DWORD *)(a1 + 1280));
                CPC::AddMoney(a1, -v61);
            }
            else
            {
                v26 = __eh_alloc(4);
                *(_DWORD *)v26 = 8;
                v27 = __tfi();
                __cp_push_exception(v26, v27, 0);
                __throw();
            }
        }
        else
        {
            CPC::AddMoney(a1, -v61);
            ItemUpdateMsg((int)&v55, *(_DWORD *)(a1 + 1280), -v61);
        }
    }
    else
    {
        v28 = __eh_alloc(4);
        *(_DWORD *)v28 = 8;
        v29 = __tfi();
        __cp_push_exception(v28, v29, 0);
        __throw();
    }
    for(i = 0; i < v63; ++i)
    {
        if(*((_DWORD *)s + i))
        {
            CNetMsg::CNetMsg((int)&v54);
            if(*(_DWORD *)(a1 + 1280))
                v30 = CItem::Count(*(_DWORD *)(a1 + 1280));
            else
                v30 = 0LL;
            v31 = v30;
            v32 = v61;
            v33 = CItem::Count(*((_DWORD *)s + i));
            v34 = (const char *)(*((_DWORD *)s + i) + 44);
            v35 = (const char *)(*(_DWORD *)(*((_DWORD *)s + i) + 20) + 12);
            v36 = v64;
            init((int)&v53, (int)"ITEM_BUY", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
            v37 = (char *)CLogBuffer::__ls(g_gamelogbuffer, (int)&v53);
            v38 = (int)CLogBuffer::__ls(v37, v36);
            v39 = CLogBuffer::__ls(v38, (int (__cdecl *)(_DWORD))delim);
            v40 = (int)CLogBuffer::__ls((const char *)v39, v35);
            v41 = CLogBuffer::__ls(v40, (int (__cdecl *)(_DWORD))delim);
            v42 = (int)CLogBuffer::__ls((const char *)v41, v34);
            v43 = CLogBuffer::__ls(v42, (int (__cdecl *)(_DWORD))delim);
            v44 = (int)CLogBuffer::__ls((char *)v43, v33);
            v45 = CLogBuffer::__ls(v44, (int (__cdecl *)(_DWORD))delim);
            v46 = (int)CLogBuffer::__ls((char *)v45, v32);
            v47 = CLogBuffer::__ls(v46, (int (__cdecl *)(_DWORD))delim);
            v48 = (int)CLogBuffer::__ls((char *)v47, v31);
            CLogBuffer::__ls(v48, end);
            if(CItem::tab(*((_DWORD *)s + i)) == -1)
            {
                if(CInventory::FindItem(
                             v60,
                             (int)&v52,
                             (int)&v51,
                             *(_DWORD *)(*((_DWORD *)s + i) + 28),
                             *(_DWORD *)(*((_DWORD *)s + i) + 36),
                             *(_DWORD *)(*((_DWORD *)s + i) + 40)))
                {
                    v50 = CInventory::GetItem(v60, v52, v51);
                    if(v50)
                        ItemUpdateMsg((int)&v54, v50, *(_QWORD *)(v58 + 8 * i));
                }
            }
            else
            {
                ItemAddMsg((int)&v54, *((_DWORD *)s + i));
            }
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v54);
            CNetMsg::_CNetMsg((int)&v54, 2);
        }
    }
    if(*(_DWORD *)(a1 + 768))
        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v55);
    result = CNetMsg::_CNetMsg((int)&v55, 2);
    if(v59 && v59)
        result = __builtin_vec_delete(v59);
    if(v58 && v58)
        result = __builtin_vec_delete(v58);
    if(s && s)
        result = __builtin_vec_delete(s);
    return result;
}
// 804969C: using guessed type int __cdecl __cp_push_exception(_DWORD, _DWORD, _DWORD);
// 804982C: using guessed type int __tfi(void);
// 80498AC: using guessed type int __throw(void);
// 8049A5C: using guessed type int __cdecl __builtin_vec_new(_DWORD);
// 8049B2C: using guessed type int __cdecl __builtin_vec_delete(_DWORD);
// 8049C7C: using guessed type int __cdecl __eh_alloc(_DWORD);

//----- (080AB3A0) --------------------------------------------------------
int __cdecl do_ItemSell(int a1, int a2)
{
    int v2; // eax@1
    int v3; // eax@1
    int v4; // eax@1
    int v5; // ebx@3
    int v6; // eax@3
    int v7; // edx@6
    int v8; // eax@6
    void *v9; // STA0_4@6
    void *v10; // ST94_4@6
    void *v11; // ST88_4@6
    int v12; // eax@6
    int v13; // eax@6
    int v14; // eax@6
    int v15; // ST124_4@11
    int v16; // eax@11
    int v17; // ST120_4@15
    int v18; // eax@15
    int v19; // eax@19
    int v20; // ST118_4@26
    int v21; // eax@26
    int v22; // eax@27
    int v23; // edx@27
    void *v24; // ecx@27
    int v25; // ST114_4@28
    int v26; // eax@28
    int v27; // ST108_4@30
    int v28; // eax@30
    int v29; // ST104_4@33
    int v30; // eax@33
    signed int v31; // STD0_4@34
    __int64 v32; // STF4_8@34
    int v33; // STEC_4@36
    int v34; // eax@36
    int v35; // STE8_4@40
    int v36; // eax@40
    signed int v37; // STA0_4@43
    signed __int64 v38; // ST88_8@43
    signed int v39; // ST70_4@43
    signed int v40; // ST58_4@43
    const char *v41; // ST40_4@43
    const char *v42; // ST28_4@43
    int v43; // ST10_4@43
    char *v44; // eax@43
    int v45; // eax@43
    int v46; // eax@43
    int v47; // eax@43
    int v48; // eax@43
    int v49; // eax@43
    int v50; // eax@43
    int v51; // eax@43
    int v52; // eax@43
    int v53; // eax@43
    int v54; // eax@43
    int v55; // eax@43
    int v56; // eax@43
    signed int v57; // STA0_4@46
    signed int v58; // ST88_4@46
    int v59; // eax@46
    int v60; // eax@46
    int v61; // eax@46
    __int64 v62; // qax@49
    signed __int64 v63; // ST94_8@51
    signed __int64 v64; // ST7C_8@51
    int v65; // eax@51
    int v66; // eax@51
    int v67; // eax@51
    int v68; // eax@51
    __int64 v69; // qax@60
    int v70; // STE0_4@64
    int v71; // eax@64
    int v72; // STDC_4@69
    int v73; // eax@69
    int v75; // [sp+44h] [bp-D0h]@53
    int v76; // [sp+90h] [bp-84h]@73
    int v77; // [sp+A4h] [bp-70h]@59
    char v78; // [sp+ABh] [bp-69h]@51
    int k; // [sp+ACh] [bp-68h]@43
    int v80; // [sp+B0h] [bp-64h]@43
    char v81; // [sp+C3h] [bp-51h]@37
    void *j; // [sp+C4h] [bp-50h]@6
    int v83; // [sp+C8h] [bp-4Ch]@1
    int v84; // [sp+DCh] [bp-38h]@1
    __int64 src; // [sp+E0h] [bp-34h]@16
    void *s; // [sp+E8h] [bp-2Ch]@1
    int v87; // [sp+ECh] [bp-28h]@1
    int v88; // [sp+F0h] [bp-24h]@1
    int v89; // [sp+F4h] [bp-20h]@1
    int v90; // [sp+F8h] [bp-1Ch]@1
    __int64 dest; // [sp+FCh] [bp-18h]@1
    int v92; // [sp+104h] [bp-10h]@1
    int v93; // [sp+108h] [bp-Ch]@1
    int i; // [sp+10Ch] [bp-8h]@4
    char v95; // [sp+113h] [bp-1h]@1

    CNetMsg::MoveFirst(a2);
    v90 = 0;
    v89 = 0;
    v88 = 0;
    v87 = 0;
    s = 0;
    v84 = 0;
    CNetMsg::CNetMsg((int)&v83);
    v2 = CNetMsg::__rs(a2, &v95);
    v3 = CNetMsg::__rs(v2, &v93);
    v4 = CNetMsg::__rs(v3, &dest);
    CNetMsg::__rs(v4, &v92);
    if(v92 > 10 || v92 <= 0)
    {
        v5 = __eh_alloc(4);
        *(_DWORD *)v5 = 0;
        v6 = __tfi();
        __cp_push_exception(v5, v6, 0);
        __throw();
    }
    v90 = __builtin_vec_new(v92);
    v89 = __builtin_vec_new(v92);
    v88 = __builtin_vec_new(v92);
    v87 = __builtin_vec_new(8 * v92);
    for(i = 0; i < v92; ++i)
    {
        *(_BYTE *)(i + v90) = -1;
        *(_BYTE *)(i + v89) = -1;
        *(_BYTE *)(i + v88) = -1;
        v7 = 8 * i;
        v8 = v87;
        *(_DWORD *)(v87 + 8 * i) = 0;
        *(_DWORD *)(v8 + v7 + 4) = 0;
        v9 = (void *)(v87 + 8 * i);
        v10 = (void *)(i + v88);
        v11 = (void *)(i + v89);
        v12 = CNetMsg::__rs(a2, (void *)(i + v90));
        v13 = CNetMsg::__rs(v12, v11);
        v14 = CNetMsg::__rs(v13, v10);
        CNetMsg::__rs(v14, v9);
        for(j = 0; (signed int)j < i; j = (char *)j + 1)
        {
            if(*(_BYTE *)(i + v90) == *((_BYTE *)j + v90) && *(_BYTE *)(i + v89) == *((_BYTE *)j + v89))
            {
                if(*(_BYTE *)(i + v88) == *((_BYTE *)j + v88))
                {
                    v15 = __eh_alloc(4);
                    *(_DWORD *)v15 = 2;
                    v16 = __tfi();
                    __cp_push_exception(v15, v16, 0);
                    __throw();
                }
            }
        }
    }
    j = CZone::FindShop(*(_DWORD *)(a1 + 408), v93);
    if(!j)
    {
        v17 = __eh_alloc(4);
        *(_DWORD *)v17 = 1;
        v18 = __tfi();
        __cp_push_exception(v17, v18, 0);
        __throw();
    }
    src = 0LL;
    s = (void *)__builtin_vec_new(4 * v92);
    memset(s, 0, 4 * v92);
    for(i = 0; i < v92; ++i)
    {
        if(*(_BYTE *)(i + v90))
        {
            if(*(_BYTE *)(i + v90) == 1)
            {
                v19 = a1 + 880;
            }
            else
            {
                if(*(_BYTE *)(i + v90) == 2)
                    v19 = a1 + 968;
                else
                    v19 = 0;
            }
        }
        else
        {
            v19 = a1 + 792;
        }
        v84 = v19;
        if(!v19)
        {
            v20 = __eh_alloc(4);
            *(_DWORD *)v20 = 2;
            v21 = __tfi();
            __cp_push_exception(v20, v21, 0);
            __throw();
        }
        v22 = CInventory::GetItem(v84, *(_BYTE *)(i + v89), *(_BYTE *)(i + v88));
        v23 = 4 * i;
        v24 = s;
        *((_DWORD *)s + i) = v22;
        if(!*(_DWORD *)((char *)v24 + v23))
        {
            v25 = __eh_alloc(4);
            *(_DWORD *)v25 = 2;
            v26 = __tfi();
            __cp_push_exception(v25, v26, 0);
            __throw();
        }
        if(*(_QWORD *)(v87 + 8 * i) > CItem::Count(*((_DWORD *)s + i)))
        {
            v27 = __eh_alloc(4);
            *(_DWORD *)v27 = 2;
            v28 = __tfi();
            __cp_push_exception(v27, v28, 0);
            __throw();
        }
        if(!(*(_DWORD *)(*(_DWORD *)(*((_DWORD *)s + i) + 20) + 68) & 0x10) || *(_BYTE *)(*((_DWORD *)s + i) + 32) != -1)
        {
            v29 = __eh_alloc(4);
            *(_DWORD *)v29 = 6;
            v30 = __tfi();
            __cp_push_exception(v29, v30, 0);
            __throw();
        }
        v31 = *((_DWORD *)j + 6) * *(_DWORD *)(*(_DWORD *)(*((_DWORD *)s + i) + 20) + 104);
        v32 = v31 / 100 * *(_QWORD *)(v87 + 8 * i);
        HIDWORD(v32) += *(_DWORD *)(v87 + 8 * i) * (v31 / 100 >> 31);
        src += v32;
    }
    if(src != dest)
    {
        v33 = __eh_alloc(4);
        *(_DWORD *)v33 = 3;
        v34 = __tfi();
        __cp_push_exception(v33, v34, 0);
        __throw();
    }
    v81 = 0;
    if(*(_DWORD *)(a1 + 1280))
        v81 = 1;
    if(!CPC::AddMoney(a1, src))
    {
        v35 = __eh_alloc(4);
        *(_DWORD *)v35 = 4;
        v36 = __tfi();
        __cp_push_exception(v35, v36, 0);
        __throw();
    }
    for(i = 0; i < v92; ++i)
    {
        v37 = *(_DWORD *)(*((_DWORD *)s + i) + 168);
        v38 = *(_QWORD *)(v87 + 8 * i);
        v39 = *(_DWORD *)(*((_DWORD *)s + i) + 40);
        v40 = *(_DWORD *)(*((_DWORD *)s + i) + 36);
        v41 = (const char *)(*((_DWORD *)s + i) + 44);
        v42 = (const char *)(*(_DWORD *)(*((_DWORD *)s + i) + 20) + 12);
        v43 = v93;
        init((int)&v80, (int)"ITEM_SELL", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
        v44 = (char *)CLogBuffer::__ls(g_gamelogbuffer, (int)&v80);
        v45 = (int)CLogBuffer::__ls(v44, v43);
        v46 = CLogBuffer::__ls(v45, (int (__cdecl *)(_DWORD))delim);
        v47 = (int)CLogBuffer::__ls((const char *)v46, v42);
        v48 = CLogBuffer::__ls(v47, (int (__cdecl *)(_DWORD))delim);
        v49 = (int)CLogBuffer::__ls((const char *)v48, v41);
        v50 = CLogBuffer::__ls(v49, (int (__cdecl *)(_DWORD))delim);
        v51 = (int)CLogBuffer::__ls((char *)v50, v40);
        v52 = CLogBuffer::__ls(v51, (int (__cdecl *)(_DWORD))delim);
        v53 = (int)CLogBuffer::__ls((char *)v52, v39);
        v54 = CLogBuffer::__ls(v53, (int (__cdecl *)(_DWORD))delim);
        v55 = (int)CLogBuffer::__ls((char *)v54, v38);
        v56 = CLogBuffer::__ls(v55, (int (__cdecl *)(_DWORD))delim);
        CLogBuffer::__ls((char *)v56, v37);
        for(k = 0; k < *(_DWORD *)(*((_DWORD *)s + i) + 168); ++k)
        {
            if(*(_DWORD *)(20 * k + *((_DWORD *)s + i) + 68))
            {
                v57 = *(_DWORD *)(20 * k + *((_DWORD *)s + i) + 76);
                v58 = *(_DWORD *)(20 * k + *((_DWORD *)s + i) + 72);
                v59 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
                v60 = (int)CLogBuffer::__ls((char *)v59, v58);
                v61 = CLogBuffer::__ls(v60, (int (__cdecl *)(_DWORD))delim);
                CLogBuffer::__ls((char *)v61, v57);
            }
        }
        if(*(_DWORD *)(a1 + 1280))
            v62 = CItem::Count(*(_DWORD *)(a1 + 1280));
        else
            v62 = 0LL;
        v63 = v62;
        v64 = src;
        v65 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
        v66 = (int)CLogBuffer::__ls((char *)v65, v64);
        v67 = CLogBuffer::__ls(v66, (int (__cdecl *)(_DWORD))delim);
        v68 = (int)CLogBuffer::__ls((char *)v67, v63);
        CLogBuffer::__ls(v68, end);
        v78 = 0;
        if(*(_BYTE *)(*(_DWORD *)(*((_DWORD *)s + i) + 20) + 68) & 1)
        {
            v78 = 1;
            if(CItem::tab(*((_DWORD *)s + i)))
            {
                if(CItem::tab(*((_DWORD *)s + i)) == 1)
                {
                    v75 = a1 + 880;
                }
                else
                {
                    if(CItem::tab(*((_DWORD *)s + i)) == 2)
                        v75 = a1 + 968;
                    else
                        v75 = 0;
                }
            }
            else
            {
                v75 = a1 + 792;
            }
            v77 = v75;
            if(v75)
            {
                CInventory::Decrease(v77, *((_DWORD *)s + i), *(_QWORD *)(v87 + 8 * i));
                v69 = CItem::Count(*((_DWORD *)s + i));
                if(SHIDWORD(v69) > 0 || !HIDWORD(v69) && (_DWORD)v69)
                {
                    ItemUpdateMsg((int)&v83, *((_DWORD *)s + i), -*(_QWORD *)(v87 + 8 * i));
                }
                else
                {
                    ItemDeleteMsg((int)&v83, *((_DWORD *)s + i));
                    if(!CInventory::Remove(v84, *((_DWORD *)s + i), 1, 1))
                    {
                        v70 = __eh_alloc(4);
                        *(_DWORD *)v70 = 5;
                        v71 = __tfi();
                        __cp_push_exception(v70, v71, 0);
                        __throw();
                    }
                }
            }
        }
        else
        {
            ItemDeleteMsg((int)&v83, *((_DWORD *)s + i));
            if(!CInventory::Remove(v84, *((_DWORD *)s + i), 1, 1))
            {
                v72 = __eh_alloc(4);
                *(_DWORD *)v72 = 5;
                v73 = __tfi();
                __cp_push_exception(v72, v73, 0);
                __throw();
            }
        }
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v83);
    }
    CNetMsg::CNetMsg((int)&v76);
    if(v81 && *(_DWORD *)(a1 + 1280))
    {
        ItemUpdateMsg((int)&v76, *(_DWORD *)(a1 + 1280), src);
    }
    else
    {
        if(*(_DWORD *)(a1 + 1280))
            ItemAddMsg((int)&v76, *(_DWORD *)(a1 + 1280));
    }
    if(*(_DWORD *)(a1 + 768))
        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v76);
    CNetMsg::_CNetMsg((int)&v76, 2);
    if(v90 && v90)
        __builtin_vec_delete(v90);
    if(v89 && v89)
        __builtin_vec_delete(v89);
    if(v88 && v88)
        __builtin_vec_delete(v88);
    if(v87 && v87)
        __builtin_vec_delete(v87);
    if(s && s)
        __builtin_vec_delete(s);
    return CNetMsg::_CNetMsg((int)&v83, 2);
}
// 804969C: using guessed type int __cdecl __cp_push_exception(_DWORD, _DWORD, _DWORD);
// 804982C: using guessed type int __tfi(void);
// 80498AC: using guessed type int __throw(void);
// 8049A5C: using guessed type int __cdecl __builtin_vec_new(_DWORD);
// 8049B2C: using guessed type int __cdecl __builtin_vec_delete(_DWORD);
// 8049C7C: using guessed type int __cdecl __eh_alloc(_DWORD);

//----- (080AC4E0) --------------------------------------------------------
int __cdecl do_ItemUpgradeReq(int a1, int a2)
{
    int v2; // eax@1
    int v3; // eax@1
    int v4; // eax@1
    int v5; // eax@1
    int v6; // eax@1
    int v7; // eax@1
    int result; // eax@1
    int v9; // edx@17
    int v10; // edx@19
    int v11; // edx@20
    signed int v12; // edx@21
    int v13; // edx@23
    signed int v14; // eax@24
    signed int v15; // ST88_4@61
    signed int v16; // ST70_4@61
    signed int v17; // ST58_4@61
    const char *v18; // ST40_4@61
    const char *v19; // ST28_4@61
    const char *v20; // eax@61
    int v21; // eax@61
    int v22; // eax@61
    int v23; // eax@61
    int v24; // eax@61
    int v25; // eax@61
    int v26; // eax@61
    int v27; // eax@61
    int v28; // eax@61
    int v29; // eax@61
    int v30; // eax@61
    signed int v31; // ST88_4@64
    signed int v32; // ST70_4@64
    int v33; // eax@64
    int v34; // eax@64
    int v35; // eax@64
    int v36; // eax@67
    int v37; // eax@67
    int v38; // eax@68
    int v39; // eax@68
    signed int v40; // ST88_4@73
    signed int v41; // ST70_4@73
    signed int v42; // ST58_4@73
    const char *v43; // ST40_4@73
    const char *v44; // ST28_4@73
    const char *v45; // eax@73
    int v46; // eax@73
    int v47; // eax@73
    int v48; // eax@73
    int v49; // eax@73
    int v50; // eax@73
    int v51; // eax@73
    int v52; // eax@73
    int v53; // eax@73
    int v54; // eax@73
    int v55; // eax@73
    signed int v56; // ST88_4@76
    signed int v57; // ST70_4@76
    int v58; // eax@76
    int v59; // eax@76
    int v60; // eax@76
    int v61; // eax@79
    int v62; // eax@79
    int v63; // eax@80
    int v64; // eax@80
    int v65; // ST7C_4@83
    int v66; // eax@83
    signed int v67; // ST88_4@93
    signed int v68; // ST70_4@93
    signed int v69; // ST58_4@93
    const char *v70; // ST40_4@93
    int v71; // eax@93
    int v72; // eax@93
    int v73; // eax@93
    int v74; // eax@93
    int v75; // eax@93
    int v76; // eax@93
    int v77; // eax@93
    int v78; // eax@93
    signed int v79; // ST88_4@96
    signed int v80; // ST70_4@96
    int v81; // eax@96
    int v82; // eax@96
    int v83; // eax@96
    int v84; // eax@99
    int v85; // eax@99
    int v86; // eax@100
    int v87; // eax@100
    int v88; // ST6C_4@105
    int v89; // eax@105
    int v90; // [sp+14h] [bp-94h]@85
    int i; // [sp+28h] [bp-80h]@61
    int v92; // [sp+2Ch] [bp-7Ch]@61
    char v93; // [sp+3Fh] [bp-69h]@52
    char v94; // [sp+40h] [bp-68h]@52
    int v95; // [sp+54h] [bp-54h]@52
    char v96; // [sp+6Bh] [bp-3Dh]@52
    int v97; // [sp+6Ch] [bp-3Ch]@29
    unsigned int v98; // [sp+70h] [bp-38h]@28
    int v99; // [sp+74h] [bp-34h]@28
    int v100; // [sp+78h] [bp-30h]@25
    int v101; // [sp+8Ch] [bp-1Ch]@11
    int v102; // [sp+90h] [bp-18h]@11
    int v103; // [sp+94h] [bp-14h]@10
    int v104; // [sp+98h] [bp-10h]@1
    int dest; // [sp+9Ch] [bp-Ch]@1
    char v106; // [sp+A3h] [bp-5h]@1
    char v107; // [sp+A4h] [bp-4h]@1
    char v108; // [sp+A5h] [bp-3h]@1
    char v109; // [sp+A6h] [bp-2h]@1
    char v110; // [sp+A7h] [bp-1h]@1

    CNetMsg::MoveFirst(a2);
    v2 = CNetMsg::__rs(a2, &v110);
    v3 = CNetMsg::__rs(v2, &v109);
    v4 = CNetMsg::__rs(v3, &v108);
    v5 = CNetMsg::__rs(v4, &dest);
    v6 = CNetMsg::__rs(v5, &v107);
    v7 = CNetMsg::__rs(v6, &v106);
    result = CNetMsg::__rs(v7, &v104);
    if(v109 >= 0)
    {
        if(v109 <= 19)
        {
            if(v108 >= 0)
            {
                if(v108 <= 4)
                {
                    if(v107 >= 0)
                    {
                        if(v107 <= 19)
                        {
                            if(v106 >= 0)
                            {
                                if(v106 <= 4)
                                {
                                    result = a1 + 792;
                                    v103 = a1 + 792;
                                    if(a1 != -792)
                                    {
                                        v102 = CInventory::GetItem(v103, v109, v108);
                                        result = CInventory::GetItem(v103, v107, v106);
                                        v101 = result;
                                        if(v102)
                                        {
                                            result = *(_DWORD *)(*(_DWORD *)(v102 + 20) + 68) & 4;
                                            if(result)
                                            {
                                                if(v101)
                                                {
                                                    result = v101;
                                                    if(*(_DWORD *)(*(_DWORD *)(v101 + 20) + 4) == 4)
                                                    {
                                                        result = v101;
                                                        if(*(_DWORD *)(*(_DWORD *)(v101 + 20) + 8) == 3)
                                                        {
                                                            result = v102;
                                                            if(*(_DWORD *)(v102 + 36) == dest)
                                                            {
                                                                result = v101;
                                                                v9 = *(_DWORD *)(v101 + 40);
                                                                LOBYTE(v9) = v9 & 0x7F;
                                                                if(v9 == v104)
                                                                {
                                                                    v10 = *(_DWORD *)(v101 + 40);
                                                                    LOBYTE(v10) = v10 & 0x7F;
                                                                    if(!v10
                                                                        || (result = v101, v11 = *(_DWORD *)(v101 + 40), LOBYTE(v11) = v11 & 0x7F, v11 > 0)
                                                                        && (result = v101, v12 = *(_DWORD *)(v101 + 40), LOBYTE(v12) = v12 & 0x7F, v12 <= 60))
                                                                    {
                                                                        v13 = *(_DWORD *)(v101 + 40);
                                                                        LOBYTE(v13) = v13 & 0x7F;
                                                                        if(v13
                                                                            && (v14 = *(_DWORD *)(v101 + 40),
                                                                                    LOBYTE(v14) = v14 & 0x7F,
                                                                                    v14 < *(_WORD *)(*(_DWORD *)(v102 + 20) + 100)))
                                                                        {
                                                                            CNetMsg::CNetMsg((int)&v100);
                                                                            SysMsg((int)&v100, 17);
                                                                            if(*(_DWORD *)(a1 + 768))
                                                                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v100);
                                                                            result = CNetMsg::_CNetMsg((int)&v100, 2);
                                                                        }
                                                                        else
                                                                        {
                                                                            v99 = 2;
                                                                            v98 = GetRandom(1, 10000);
                                                                            if(*(_DWORD *)(*(_DWORD *)(v101 + 20) + 76))
                                                                            {
                                                                                if(*(_DWORD *)(*(_DWORD *)(v101 + 20) + 76) == 1)
                                                                                {
                                                                                    v97 = 7700;
                                                                                    v97 -= *(_DWORD *)(v102 + 36) > 11 ? 4000 : 200 * *(_DWORD *)(v102 + 36);
                                                                                    if((signed int)v98 > 2000)
                                                                                    {
                                                                                        if((signed int)v98 > 2700)
                                                                                            v99 = (signed int)v98 > v97 ? 1 : 0;
                                                                                        else
                                                                                            v99 = 3;
                                                                                    }
                                                                                    else
                                                                                    {
                                                                                        v99 = 2;
                                                                                    }
                                                                                    if(v99 && *(_DWORD *)(v102 + 36) <= 2)
                                                                                        v99 = 2;
                                                                                }
                                                                            }
                                                                            else
                                                                            {
                                                                                v97 = 5000;
                                                                                if(*(_DWORD *)(v102 + 36) > 11)
                                                                                    v97 -= 4000;
                                                                                else
                                                                                    v97 -= 200 * *(_DWORD *)(v102 + 36);
                                                                                if((signed int)v98 > v97)
                                                                                {
                                                                                    if(*(_DWORD *)(v102 + 36) > 2)
                                                                                        v99 = 3;
                                                                                    else
                                                                                        v99 = 2;
                                                                                }
                                                                                else
                                                                                {
                                                                                    v99 = 0;
                                                                                }
                                                                            }
                                                                            v96 = 0;
                                                                            CNetMsg::CNetMsg((int)&v100);
                                                                            CNetMsg::CNetMsg((int)&v95);
                                                                            CNetMsg::CNetMsg((int)&v94);
                                                                            v93 = *(_BYTE *)(v102 + 32);
                                                                            if(v99 == 1)
                                                                            {
                                                                                --*(_DWORD *)(v102 + 36);
                                                                                v96 = 1;
                                                                                ItemUpgradeRepMsg((int)&v94, 1);
                                                                            }
                                                                            else
                                                                            {
                                                                                if(v99 > 1)
                                                                                {
                                                                                    if(v99 == 2)
                                                                                    {
                                                                                        v15 = *(_DWORD *)(v102 + 168);
                                                                                        v16 = *(_DWORD *)(v102 + 40);
                                                                                        v17 = *(_DWORD *)(v102 + 36);
                                                                                        v18 = (const char *)(v102 + 44);
                                                                                        v19 = (const char *)(*(_DWORD *)(v102 + 20) + 12);
                                                                                        init((int)&v92, (int)"ITEM_UPGRADE", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
                                                                                        v20 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v92);
                                                                                        v21 = (int)CLogBuffer::__ls(v20, "No change");
                                                                                        v22 = CLogBuffer::__ls(v21, (int (__cdecl *)(_DWORD))delim);
                                                                                        v23 = (int)CLogBuffer::__ls((const char *)v22, v19);
                                                                                        v24 = CLogBuffer::__ls(v23, (int (__cdecl *)(_DWORD))delim);
                                                                                        v25 = (int)CLogBuffer::__ls((const char *)v24, v18);
                                                                                        v26 = CLogBuffer::__ls(v25, (int (__cdecl *)(_DWORD))delim);
                                                                                        v27 = (int)CLogBuffer::__ls((char *)v26, v17);
                                                                                        v28 = CLogBuffer::__ls(v27, (int (__cdecl *)(_DWORD))delim);
                                                                                        v29 = (int)CLogBuffer::__ls((char *)v28, v16);
                                                                                        v30 = CLogBuffer::__ls(v29, (int (__cdecl *)(_DWORD))delim);
                                                                                        CLogBuffer::__ls((char *)v30, v15);
                                                                                        for(i = 0; i < *(_DWORD *)(v102 + 168); ++i)
                                                                                        {
                                                                                            if(*(_DWORD *)(20 * i + v102 + 68))
                                                                                            {
                                                                                                v31 = *(_DWORD *)(20 * i + v102 + 76);
                                                                                                v32 = *(_DWORD *)(20 * i + v102 + 72);
                                                                                                v33 = CLogBuffer::__ls(
                                                                                                                (int)g_gamelogbuffer,
                                                                                                                (int (__cdecl *)(_DWORD))delim);
                                                                                                v34 = (int)CLogBuffer::__ls((char *)v33, v32);
                                                                                                v35 = CLogBuffer::__ls(v34, (int (__cdecl *)(_DWORD))delim);
                                                                                                CLogBuffer::__ls((char *)v35, v31);
                                                                                            }
                                                                                        }
                                                                                        if(*(_DWORD *)(*(_DWORD *)(v101 + 20) + 76))
                                                                                        {
                                                                                            v38 = CLogBuffer::__ls(
                                                                                                            (int)g_gamelogbuffer,
                                                                                                            (int (__cdecl *)(_DWORD))delim);
                                                                                            v39 = (int)CLogBuffer::__ls((const char *)v38, "USE SPECIAL");
                                                                                            CLogBuffer::__ls(v39, end);
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            v36 = CLogBuffer::__ls(
                                                                                                            (int)g_gamelogbuffer,
                                                                                                            (int (__cdecl *)(_DWORD))delim);
                                                                                            v37 = (int)CLogBuffer::__ls((const char *)v36, "USE GENERAL");
                                                                                            CLogBuffer::__ls(v37, end);
                                                                                        }
                                                                                        ItemUpgradeRepMsg((int)&v94, 2);
                                                                                    }
                                                                                    else
                                                                                    {
                                                                                        if(v99 == 3)
                                                                                        {
                                                                                            if(v93 != -1)
                                                                                            {
                                                                                                *(_DWORD *)(4 * *(_BYTE *)(v102 + 32) + a1 + 1284) = 0;
                                                                                                ItemWearMsg((int)&v100, *(_BYTE *)(v102 + 32), 0, v102);
                                                                                                *(_BYTE *)(v102 + 32) = -1;
                                                                                                if(*(_DWORD *)(a1 + 768))
                                                                                                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v100);
                                                                                            }
                                                                                            v40 = *(_DWORD *)(v102 + 168);
                                                                                            v41 = *(_DWORD *)(v102 + 40);
                                                                                            v42 = *(_DWORD *)(v102 + 36);
                                                                                            v43 = (const char *)(v102 + 44);
                                                                                            v44 = (const char *)(*(_DWORD *)(v102 + 20) + 12);
                                                                                            init((int)&v92, (int)"ITEM_UPGRADE", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
                                                                                            v45 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v92);
                                                                                            v46 = (int)CLogBuffer::__ls(v45, "Broken");
                                                                                            v47 = CLogBuffer::__ls(v46, (int (__cdecl *)(_DWORD))delim);
                                                                                            v48 = (int)CLogBuffer::__ls((const char *)v47, v44);
                                                                                            v49 = CLogBuffer::__ls(v48, (int (__cdecl *)(_DWORD))delim);
                                                                                            v50 = (int)CLogBuffer::__ls((const char *)v49, v43);
                                                                                            v51 = CLogBuffer::__ls(v50, (int (__cdecl *)(_DWORD))delim);
                                                                                            v52 = (int)CLogBuffer::__ls((char *)v51, v42);
                                                                                            v53 = CLogBuffer::__ls(v52, (int (__cdecl *)(_DWORD))delim);
                                                                                            v54 = (int)CLogBuffer::__ls((char *)v53, v41);
                                                                                            v55 = CLogBuffer::__ls(v54, (int (__cdecl *)(_DWORD))delim);
                                                                                            CLogBuffer::__ls((char *)v55, v40);
                                                                                            for(i = 0; i < *(_DWORD *)(v102 + 168); ++i)
                                                                                            {
                                                                                                if(*(_DWORD *)(20 * i + v102 + 68))
                                                                                                {
                                                                                                    v56 = *(_DWORD *)(20 * i + v102 + 76);
                                                                                                    v57 = *(_DWORD *)(20 * i + v102 + 72);
                                                                                                    v58 = CLogBuffer::__ls(
                                                                                                                    (int)g_gamelogbuffer,
                                                                                                                    (int (__cdecl *)(_DWORD))delim);
                                                                                                    v59 = (int)CLogBuffer::__ls((char *)v58, v57);
                                                                                                    v60 = CLogBuffer::__ls(v59, (int (__cdecl *)(_DWORD))delim);
                                                                                                    CLogBuffer::__ls((char *)v60, v56);
                                                                                                }
                                                                                            }
                                                                                            if(*(_DWORD *)(*(_DWORD *)(v101 + 20) + 76))
                                                                                            {
                                                                                                v63 = CLogBuffer::__ls(
                                                                                                                (int)g_gamelogbuffer,
                                                                                                                (int (__cdecl *)(_DWORD))delim);
                                                                                                v64 = (int)CLogBuffer::__ls((const char *)v63, "USE SPECIAL");
                                                                                                CLogBuffer::__ls(v64, end);
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                v61 = CLogBuffer::__ls(
                                                                                                                (int)g_gamelogbuffer,
                                                                                                                (int (__cdecl *)(_DWORD))delim);
                                                                                                v62 = (int)CLogBuffer::__ls((const char *)v61, "USE GENERAL");
                                                                                                CLogBuffer::__ls(v62, end);
                                                                                            }
                                                                                            ItemDeleteMsg((int)&v100, v102);
                                                                                            if(*(_DWORD *)(a1 + 768))
                                                                                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v100);
                                                                                            v65 = CItem::col(v102);
                                                                                            v66 = CItem::row(v102);
                                                                                            CInventory::Remove(v103, v66, v65, 1, 1);
                                                                                            if(v93 > 0 && v93 <= 6)
                                                                                            {
                                                                                                CNetMsg::CNetMsg((int)&v90);
                                                                                                WearingMsg((int)&v90, a1, v93, 0xFFFFFFFFu);
                                                                                                CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v90, a1, 0, 4);
                                                                                                CNetMsg::_CNetMsg((int)&v90, 2);
                                                                                            }
                                                                                            ItemUpgradeRepMsg((int)&v94, 3);
                                                                                        }
                                                                                    }
                                                                                }
                                                                                else
                                                                                {
                                                                                    if(!v99)
                                                                                    {
                                                                                        ++*(_DWORD *)(v102 + 36);
                                                                                        v96 = 1;
                                                                                        ItemUpgradeRepMsg((int)&v94, 0);
                                                                                    }
                                                                                }
                                                                            }
                                                                            if(v96)
                                                                            {
                                                                                init((int)&v92, (int)"ITEM_UPGRADE", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
                                                                                CLogBuffer::__ls(g_gamelogbuffer, (int)&v92);
                                                                                if(v99)
                                                                                {
                                                                                    if(v99 == 1)
                                                                                        CLogBuffer::__ls(g_gamelogbuffer, "-1");
                                                                                }
                                                                                else
                                                                                {
                                                                                    CLogBuffer::__ls(g_gamelogbuffer, "+1");
                                                                                }
                                                                                v67 = *(_DWORD *)(v102 + 168);
                                                                                v68 = *(_DWORD *)(v102 + 40);
                                                                                v69 = *(_DWORD *)(v102 + 36);
                                                                                v70 = (const char *)(v102 + 44);
                                                                                v71 = (int)CLogBuffer::__ls(
                                                                                                         g_gamelogbuffer,
                                                                                                         (const char *)(*(_DWORD *)(v102 + 20) + 12));
                                                                                v72 = CLogBuffer::__ls(v71, (int (__cdecl *)(_DWORD))delim);
                                                                                v73 = (int)CLogBuffer::__ls((const char *)v72, v70);
                                                                                v74 = CLogBuffer::__ls(v73, (int (__cdecl *)(_DWORD))delim);
                                                                                v75 = (int)CLogBuffer::__ls((char *)v74, v69);
                                                                                v76 = CLogBuffer::__ls(v75, (int (__cdecl *)(_DWORD))delim);
                                                                                v77 = (int)CLogBuffer::__ls((char *)v76, v68);
                                                                                v78 = CLogBuffer::__ls(v77, (int (__cdecl *)(_DWORD))delim);
                                                                                CLogBuffer::__ls((char *)v78, v67);
                                                                                for(i = 0; i < *(_DWORD *)(v102 + 168); ++i)
                                                                                {
                                                                                    if(*(_DWORD *)(20 * i + v102 + 68))
                                                                                    {
                                                                                        v79 = *(_DWORD *)(20 * i + v102 + 76);
                                                                                        v80 = *(_DWORD *)(20 * i + v102 + 72);
                                                                                        v81 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
                                                                                        v82 = (int)CLogBuffer::__ls((char *)v81, v80);
                                                                                        v83 = CLogBuffer::__ls(v82, (int (__cdecl *)(_DWORD))delim);
                                                                                        CLogBuffer::__ls((char *)v83, v79);
                                                                                    }
                                                                                }
                                                                                if(*(_DWORD *)(*(_DWORD *)(v101 + 20) + 76))
                                                                                {
                                                                                    v86 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
                                                                                    v87 = (int)CLogBuffer::__ls((const char *)v86, "USE SPECIAL");
                                                                                    CLogBuffer::__ls(v87, end);
                                                                                }
                                                                                else
                                                                                {
                                                                                    v84 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
                                                                                    v85 = (int)CLogBuffer::__ls((const char *)v84, "USE GENERAL");
                                                                                    CLogBuffer::__ls(v85, end);
                                                                                }
                                                                                ItemUpdateMsg((int)&v100, v102, 0LL);
                                                                                if(*(_DWORD *)(a1 + 768))
                                                                                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v100);
                                                                            }
                                                                            if(CItem::Count(v101) <= 1)
                                                                            {
                                                                                ItemDeleteMsg((int)&v95, v101);
                                                                                v88 = CItem::col(v101);
                                                                                v89 = CItem::row(v101);
                                                                                CInventory::Remove(v103, v89, v88, 1, 1);
                                                                            }
                                                                            else
                                                                            {
                                                                                CInventory::Decrease(v103, v101, 1LL);
                                                                                ItemUpdateMsg((int)&v95, v101, -1LL);
                                                                            }
                                                                            if(*(_DWORD *)(a1 + 768))
                                                                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v95);
                                                                            if(*(_DWORD *)(a1 + 768))
                                                                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v94);
                                                                            CPC::CalcStatus(a1, 1);
                                                                            CPC::SaveNow(a1, 0);
                                                                            CNetMsg::_CNetMsg((int)&v94, 2);
                                                                            CNetMsg::_CNetMsg((int)&v95, 2);
                                                                            result = CNetMsg::_CNetMsg((int)&v100, 2);
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
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}

//----- (080AD3F0) --------------------------------------------------------
int __cdecl do_ItemRefinReq(int a1, int a2)
{
    int v2; // eax@1
    int v3; // eax@1
    int result; // eax@1
    int v5; // ecx@28
    signed int v6; // eax@28
    __int64 v7; // qax@31
    __int64 v8; // qax@33
    signed int v9; // ST88_4@63
    signed int v10; // ST70_4@63
    signed int v11; // ST58_4@63
    const char *v12; // ST40_4@63
    const char *v13; // ST28_4@63
    const char *v14; // eax@63
    int v15; // eax@63
    int v16; // eax@63
    int v17; // eax@63
    int v18; // eax@63
    int v19; // eax@63
    int v20; // eax@63
    int v21; // eax@63
    int v22; // eax@63
    signed int v23; // ST7C_4@66
    signed int v24; // ST64_4@66
    int v25; // eax@66
    int v26; // eax@66
    int v27; // eax@66
    int v28; // eax@66
    __int64 v29; // ST70_8@68
    signed int v30; // ST58_4@68
    signed int v31; // ST40_4@68
    const char *v32; // ST28_4@68
    const char *v33; // ST10_4@68
    int v34; // eax@68
    int v35; // eax@68
    int v36; // eax@68
    int v37; // eax@68
    int v38; // eax@68
    int v39; // eax@68
    int v40; // eax@68
    int v41; // eax@68
    int v42; // eax@68
    int v43; // eax@68
    int v44; // eax@68
    int v45; // ST7C_4@68
    int v46; // eax@68
    __int64 v47; // qax@71
    int v48; // [sp+20h] [bp-A4h]@70
    int v49; // [sp+24h] [bp-A0h]@69
    int v50; // [sp+28h] [bp-9Ch]@69
    int i; // [sp+2Ch] [bp-98h]@63
    int v52; // [sp+30h] [bp-94h]@60
    int v53; // [sp+44h] [bp-80h]@51
    char v54; // [sp+48h] [bp-7Ch]@51
    int v55; // [sp+5Ch] [bp-68h]@51
    char v56; // [sp+70h] [bp-54h]@51
    unsigned int v57; // [sp+84h] [bp-40h]@38
    int v58; // [sp+88h] [bp-3Ch]@38
    int v59; // [sp+8Ch] [bp-38h]@30
    int v60; // [sp+A0h] [bp-24h]@28
    char v61; // [sp+A4h] [bp-20h]@10
    int v62; // [sp+B8h] [bp-Ch]@7
    int v63; // [sp+BCh] [bp-8h]@6
    char v64; // [sp+C1h] [bp-3h]@1
    char v65; // [sp+C2h] [bp-2h]@1
    char dest; // [sp+C3h] [bp-1h]@1

    CNetMsg::MoveFirst(a2);
    v2 = CNetMsg::__rs(a2, &dest);
    v3 = CNetMsg::__rs(v2, &v65);
    result = CNetMsg::__rs(v3, &v64);
    if(v65 < 0
        || v65 > 19
        || v64 < 0
        || v64 > 4
        || (result = a1 + 792, v63 = a1 + 792, a1 == -792)
        || (result = CInventory::GetItem(v63, v65, v64), (v62 = result) == 0)
        || (result = v62, *(_BYTE *)(v62 + 32) != -1))
        return result;
    CNetMsg::CNetMsg((int)&v61);
    if(!v62 || !CItem::IsWeaponType(v62) && !CItem::IsArmorType(v62))
    {
        SysMsg((int)&v61, 18);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v61);
        return CNetMsg::_CNetMsg((int)&v61, 2);
    }
    if(*(_WORD *)(*(_DWORD *)(v62 + 20) + 100) <= 0)
    {
        SysMsg((int)&v61, 38);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v61);
        return CNetMsg::_CNetMsg((int)&v61, 2);
    }
    if(*(_DWORD *)(v62 + 36) > 0)
    {
        SysMsg((int)&v61, 20);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v61);
        return CNetMsg::_CNetMsg((int)&v61, 2);
    }
    if(*(_BYTE *)(v62 + 32) != -1)
    {
        SysMsg((int)&v61, 19);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v61);
        return CNetMsg::_CNetMsg((int)&v61, 2);
    }
    v60 = 0;
    v5 = *(_WORD *)(*(_DWORD *)(v62 + 20) + 100) - 1;
    v6 = v5 * (*(_WORD *)(*(_DWORD *)(v62 + 20) + 100) + 3) * (*(_WORD *)(*(_DWORD *)(v62 + 20) + 100) + 1) + 100;
    if(v6 < 0)
        v6 = v5 * (*(_WORD *)(*(_DWORD *)(v62 + 20) + 100) + 3) * (*(_WORD *)(*(_DWORD *)(v62 + 20) + 100) + 1) + 103;
    v60 = v6 >> 2;
    CNetMsg::CNetMsg((int)&v59);
    if(*(_DWORD *)(a1 + 1280))
    {
        v7 = CItem::Count(*(_DWORD *)(a1 + 1280));
        if(v7 > v60)
        {
            CPC::AddMoney(a1, -v60);
            ItemUpdateMsg((int)&v59, *(_DWORD *)(a1 + 1280), -v60);
            goto LABEL_38;
        }
        v8 = CItem::Count(*(_DWORD *)(a1 + 1280));
        if(v8 == v60)
        {
            ItemDeleteMsg((int)&v59, *(_DWORD *)(a1 + 1280));
            CPC::AddMoney(a1, -v60);
LABEL_38:
            v58 = 1;
            v57 = GetRandom(1, 10000);
            if(CItem::IsWeaponType(v62))
            {
                if((signed int)v57 > 9950)
                    v58 = 2;
                else
                    v58 = 0;
            }
            else
            {
                if(CItem::IsArmorType(v62))
                {
                    if((signed int)v57 > 9990)
                        v58 = 2;
                    else
                        v58 = 1;
                }
            }
            CNetMsg::CNetMsg((int)&v56);
            CNetMsg::CNetMsg((int)&v55);
            CNetMsg::CNetMsg((int)&v54);
            v53 = 0;
            if(v58)
            {
                if(v58 == 1)
                {
                    v53 = CItemList::CreateItem(gserver.Unk41208, *unk_8104588, -1, 0, *(_WORD *)(*(_DWORD *)(v62 + 20) + 100), 1LL);
                }
                else
                {
                    if(v58 == 2)
                        v53 = CItemList::CreateItem(gserver.Unk41208, *unk_810458C, -1, 0, 0, 1LL);
                }
            }
            else
            {
                v53 = CItemList::CreateItem(gserver.Unk41208, *unk_8104588, -1, 0, *(_WORD *)(*(_DWORD *)(v62 + 20) + 100), 2LL);
            }
            if(v53)
            {
                if(CInventory::AddItem(v63, v53, a1, 1, 1, -1, -1))
                {
                    v9 = *(_DWORD *)(v62 + 168);
                    v10 = *(_DWORD *)(v62 + 40);
                    v11 = *(_DWORD *)(v62 + 36);
                    v12 = (const char *)(v62 + 44);
                    v13 = (const char *)(*(_DWORD *)(v62 + 20) + 12);
                    init((int)&v52, (int)"ITEM_REFINE", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
                    v14 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v52);
                    v15 = (int)CLogBuffer::__ls(v14, v13);
                    v16 = CLogBuffer::__ls(v15, (int (__cdecl *)(_DWORD))delim);
                    v17 = (int)CLogBuffer::__ls((const char *)v16, v12);
                    v18 = CLogBuffer::__ls(v17, (int (__cdecl *)(_DWORD))delim);
                    v19 = (int)CLogBuffer::__ls((char *)v18, v11);
                    v20 = CLogBuffer::__ls(v19, (int (__cdecl *)(_DWORD))delim);
                    v21 = (int)CLogBuffer::__ls((char *)v20, v10);
                    v22 = CLogBuffer::__ls(v21, (int (__cdecl *)(_DWORD))delim);
                    CLogBuffer::__ls((char *)v22, v9);
                    for(i = 0; i < *(_DWORD *)(v62 + 168); ++i)
                    {
                        if(*(_DWORD *)(20 * i + v62 + 68))
                        {
                            v23 = *(_DWORD *)(20 * i + v62 + 76);
                            v24 = *(_DWORD *)(20 * i + v62 + 72);
                            v25 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
                            v26 = (int)CLogBuffer::__ls((char *)v25, v24);
                            v27 = CLogBuffer::__ls(v26, (int (__cdecl *)(_DWORD))delim);
                            v28 = (int)CLogBuffer::__ls((char *)v27, v23);
                            CLogBuffer::__ls(v28, (int (__cdecl *)(_DWORD))delim);
                        }
                    }
                    v29 = CItem::Count(v53);
                    v30 = *(_DWORD *)(v53 + 40);
                    v31 = *(_DWORD *)(v53 + 36);
                    v32 = (const char *)(v53 + 44);
                    v33 = (const char *)(*(_DWORD *)(v53 + 20) + 12);
                    v34 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
                    v35 = (int)CLogBuffer::__ls((const char *)v34, v33);
                    v36 = CLogBuffer::__ls(v35, (int (__cdecl *)(_DWORD))delim);
                    v37 = (int)CLogBuffer::__ls((const char *)v36, v32);
                    v38 = CLogBuffer::__ls(v37, (int (__cdecl *)(_DWORD))delim);
                    v39 = (int)CLogBuffer::__ls((char *)v38, v31);
                    v40 = CLogBuffer::__ls(v39, (int (__cdecl *)(_DWORD))delim);
                    v41 = (int)CLogBuffer::__ls((char *)v40, v30);
                    v42 = CLogBuffer::__ls(v41, (int (__cdecl *)(_DWORD))delim);
                    v43 = (int)CLogBuffer::__ls((char *)v42, v29);
                    v44 = CLogBuffer::__ls(v43, (int (__cdecl *)(_DWORD))delim);
                    CLogBuffer::__ls(v44, end);
                    ItemDeleteMsg((int)&v56, v62);
                    v45 = CItem::col(v62);
                    v46 = CItem::row(v62);
                    CInventory::Remove(v63, v46, v45, 1, 1);
                    if(CItem::tab(v53) == -1)
                    {
                        if(CInventory::FindItem(
                                     v63,
                                     (int)&v50,
                                     (int)&v49,
                                     *(_DWORD *)(v53 + 28),
                                     *(_DWORD *)(v53 + 36),
                                     *(_DWORD *)(v53 + 40)))
                        {
                            v48 = CInventory::GetItem(v63, v50, v49);
                            if(v48)
                            {
                                v47 = CItem::Count(v53);
                                ItemUpdateMsg((int)&v55, v48, v47);
                            }
                        }
                    }
                    else
                    {
                        ItemAddMsg((int)&v55, v53);
                    }
                    ItemRefineRepMsg((int)&v54, v58);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v59);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v56);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v55);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v54);
                    CPC::CalcStatus(a1, 1);
                    CPC::SaveNow(a1, 0);
                    CNetMsg::_CNetMsg((int)&v54, 2);
                    CNetMsg::_CNetMsg((int)&v55, 2);
                    CNetMsg::_CNetMsg((int)&v56, 2);
                    CNetMsg::_CNetMsg((int)&v59, 2);
                    result = CNetMsg::_CNetMsg((int)&v61, 2);
                }
                else
                {
                    CNetMsg::CNetMsg((int)&v52);
                    SysFullInventoryMsg((int)&v52, *(_BYTE *)(v63 + 4));
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v52);
                    CNetMsg::_CNetMsg((int)&v52, 2);
                    CNetMsg::_CNetMsg((int)&v54, 2);
                    CNetMsg::_CNetMsg((int)&v55, 2);
                    CNetMsg::_CNetMsg((int)&v56, 2);
                    CNetMsg::_CNetMsg((int)&v59, 2);
                    result = CNetMsg::_CNetMsg((int)&v61, 2);
                }
            }
            else
            {
                CNetMsg::_CNetMsg((int)&v54, 2);
                CNetMsg::_CNetMsg((int)&v55, 2);
                CNetMsg::_CNetMsg((int)&v56, 2);
                CNetMsg::_CNetMsg((int)&v59, 2);
                result = CNetMsg::_CNetMsg((int)&v61, 2);
            }
            return result;
        }
        SysMsg((int)&v61, 28);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v61);
        CNetMsg::_CNetMsg((int)&v59, 2);
        result = CNetMsg::_CNetMsg((int)&v61, 2);
    }
    else
    {
        SysMsg((int)&v61, 28);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v61);
        CNetMsg::_CNetMsg((int)&v59, 2);
        result = CNetMsg::_CNetMsg((int)&v61, 2);
    }
    return result;
}

//----- (080AE180) --------------------------------------------------------
#error "80AED6C: positive sp value has been found (funcsize=969)"

//----- (080AED70) --------------------------------------------------------
int __cdecl do_ItemOptionDelReq(int a1, int a2)
{
    int v2; // eax@1
    int v3; // eax@1
    int v4; // eax@1
    int v5; // eax@1
    int v6; // eax@1
    int result; // eax@11
    int v8; // ST6C_4@48
    int v9; // eax@48
    int v10; // ecx@54
    signed int v11; // ST88_4@54
    __int64 v12; // ST70_8@54
    signed int v13; // ST58_4@54
    signed int v14; // ST40_4@54
    const char *v15; // ST28_4@54
    const char *v16; // ST10_4@54
    const char *v17; // eax@54
    int v18; // eax@54
    int v19; // eax@54
    int v20; // eax@54
    int v21; // eax@54
    int v22; // eax@54
    int v23; // eax@54
    int v24; // eax@54
    int v25; // eax@54
    int v26; // eax@54
    int v27; // eax@54
    signed int v28; // ST88_4@57
    signed int v29; // ST70_4@57
    int v30; // eax@57
    int v31; // eax@57
    int v32; // eax@57
    int v33; // [sp+8h] [bp-50h]@54
    int i; // [sp+18h] [bp-40h]@51
    int v35; // [sp+1Ch] [bp-3Ch]@46
    int v36; // [sp+30h] [bp-28h]@36
    int v37; // [sp+34h] [bp-24h]@21
    int v38; // [sp+38h] [bp-20h]@17
    char v39; // [sp+3Ch] [bp-1Ch]@1
    char v40; // [sp+52h] [bp-6h]@1
    char v41; // [sp+53h] [bp-5h]@1
    char v42; // [sp+54h] [bp-4h]@1
    char v43; // [sp+55h] [bp-3h]@1
    char v44; // [sp+56h] [bp-2h]@1
    char dest; // [sp+57h] [bp-1h]@1

    CNetMsg::MoveFirst(a2);
    v2 = CNetMsg::__rs(a2, &dest);
    v3 = CNetMsg::__rs(v2, &v44);
    v4 = CNetMsg::__rs(v3, &v43);
    v5 = CNetMsg::__rs(v4, &v42);
    v6 = CNetMsg::__rs(v5, &v41);
    CNetMsg::__rs(v6, &v40);
    CNetMsg::CNetMsg((int)&v39);
    if(v44 >= 0 && v44 <= 19 && v43 >= 0 && v43 <= 4 && v41 >= 0 && v41 <= 19 && v40 >= 0 && v40 <= 4)
    {
        if(v42 >= 0 && v42 <= 6)
        {
            v38 = a1 + 792;
            if(a1 == -792)
            {
                ItemOptionDelRepMsg((int)&v39, 0, 0);
                if(vFFFFFFE8)
                    CDescriptor::WriteToOutput(vFFFFFFE8, (int)&v39);
                result = CNetMsg::_CNetMsg((int)&v39, 2);
            }
            else
            {
                v37 = CInventory::GetItem(v38, v44, v43);
                if(v37 && *(_BYTE *)(v37 + 32) == v42)
                {
                    if(v37 && (CItem::IsWeaponType(v37) || CItem::IsArmorType(v37)))
                    {
                        if(*(_DWORD *)(v37 + 168) > 2)
                        {
                            v36 = CInventory::GetItem(v38, v41, v40);
                            if(v36)
                            {
                                if(*(_DWORD *)(*(_DWORD *)(v36 + 20) + 4) == 4
                                    && *(_DWORD *)(*(_DWORD *)(v36 + 20) + 8) == 8
                                    && *(_DWORD *)(*(_DWORD *)(v36 + 20) + 76) == 1)
                                {
                                    CNetMsg::CNetMsg((int)&v35);
                                    if(CItem::Count(v36) <= 1)
                                    {
                                        ItemDeleteMsg((int)&v35, v36);
                                        v8 = CItem::col(v36);
                                        v9 = CItem::row(v36);
                                        CInventory::Remove(v38, v9, v8, 1, 1);
                                    }
                                    else
                                    {
                                        CInventory::Decrease(v38, v36, 1LL);
                                        ItemUpdateMsg((int)&v35, v36, -1LL);
                                    }
                                    if(*(_DWORD *)(a1 + 768))
                                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v35);
                                    for(i = 0; i < *(_DWORD *)(v37 + 168); ++i)
                                    {
                                        *(_DWORD *)(20 * i + v37 + 68) = 0;
                                        *(_DWORD *)(20 * i + v37 + 72) = -1;
                                        *(_DWORD *)(20 * i + v37 + 76) = 0;
                                        *(_DWORD *)(20 * i + v37 + 80) = 0;
                                        *(_WORD *)(20 * i + v37 + 84) = 0;
                                    }
                                    *(_DWORD *)(v37 + 168) = 0;
                                    v10 = *(_DWORD *)(v37 + 40);
                                    LOBYTE(v10) = v10 & 0x7F;
                                    *(_DWORD *)(v37 + 40) = v10;
                                    v11 = *(_DWORD *)(v37 + 168);
                                    v12 = CItem::Count(v37);
                                    v13 = *(_DWORD *)(v37 + 40);
                                    v14 = *(_DWORD *)(v37 + 36);
                                    v15 = (const char *)(v37 + 44);
                                    v16 = (const char *)(*(_DWORD *)(v37 + 20) + 12);
                                    init((int)&v33, (int)"ITEM_OPTION_DEL", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
                                    v17 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v33);
                                    v18 = (int)CLogBuffer::__ls(v17, v16);
                                    v19 = CLogBuffer::__ls(v18, (int (__cdecl *)(_DWORD))delim);
                                    v20 = (int)CLogBuffer::__ls((const char *)v19, v15);
                                    v21 = CLogBuffer::__ls(v20, (int (__cdecl *)(_DWORD))delim);
                                    v22 = (int)CLogBuffer::__ls((char *)v21, v14);
                                    v23 = CLogBuffer::__ls(v22, (int (__cdecl *)(_DWORD))delim);
                                    v24 = (int)CLogBuffer::__ls((char *)v23, v13);
                                    v25 = CLogBuffer::__ls(v24, (int (__cdecl *)(_DWORD))delim);
                                    v26 = (int)CLogBuffer::__ls((char *)v25, v12);
                                    v27 = CLogBuffer::__ls(v26, (int (__cdecl *)(_DWORD))delim);
                                    CLogBuffer::__ls((char *)v27, v11);
                                    for(i = 0; i < *(_DWORD *)(v37 + 168); ++i)
                                    {
                                        if(*(_DWORD *)(20 * i + v37 + 68))
                                        {
                                            v28 = *(_DWORD *)(20 * i + v37 + 76);
                                            v29 = *(_DWORD *)(20 * i + v37 + 72);
                                            v30 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
                                            v31 = (int)CLogBuffer::__ls((char *)v30, v29);
                                            v32 = CLogBuffer::__ls(v31, (int (__cdecl *)(_DWORD))delim);
                                            CLogBuffer::__ls((char *)v32, v28);
                                        }
                                    }
                                    CLogBuffer::__ls((int)g_gamelogbuffer, end);
                                    ItemUpdateMsg((int)&v35, v37, 0LL);
                                    if(*(_DWORD *)(a1 + 768))
                                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v35);
                                    ItemOptionDelRepMsg((int)&v39, v37, 4);
                                    if(*(_DWORD *)(a1 + 768))
                                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v39);
                                    CPC::CalcStatus(a1, 1);
                                    CPC::SaveNow(a1, 0);
                                    CNetMsg::_CNetMsg((int)&v35, 2);
                                    result = CNetMsg::_CNetMsg((int)&v39, 2);
                                }
                                else
                                {
                                    ItemOptionAddRepMsg((int)&v39, 0, 0);
                                    if(*(_DWORD *)(a1 + 768))
                                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v39);
                                    result = CNetMsg::_CNetMsg((int)&v39, 2);
                                }
                            }
                            else
                            {
                                ItemOptionAddRepMsg((int)&v39, 0, 0);
                                if(*(_DWORD *)(a1 + 768))
                                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v39);
                                result = CNetMsg::_CNetMsg((int)&v39, 2);
                            }
                        }
                        else
                        {
                            ItemOptionDelRepMsg((int)&v39, 0, 3);
                            if(*(_DWORD *)(a1 + 768))
                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v39);
                            result = CNetMsg::_CNetMsg((int)&v39, 2);
                        }
                    }
                    else
                    {
                        ItemOptionDelRepMsg((int)&v39, 0, 2);
                        if(*(_DWORD *)(a1 + 768))
                            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v39);
                        result = CNetMsg::_CNetMsg((int)&v39, 2);
                    }
                }
                else
                {
                    ItemOptionDelRepMsg((int)&v39, 0, 0);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v39);
                    result = CNetMsg::_CNetMsg((int)&v39, 2);
                }
            }
        }
        else
        {
            ItemOptionDelRepMsg((int)&v39, 0, 1);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v39);
            result = CNetMsg::_CNetMsg((int)&v39, 2);
        }
    }
    else
    {
        ItemOptionDelRepMsg((int)&v39, 0, 0);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v39);
        result = CNetMsg::_CNetMsg((int)&v39, 2);
    }
    return result;
}

//----- (080AF660) --------------------------------------------------------
int __cdecl do_ItemProcessReq(int a1, int a2)
{
    int v2; // eax@1
    int v3; // eax@1
    int v4; // eax@1
    int v5; // eax@1
    int v6; // ebx@4
    int v7; // eax@4
    int v8; // esi@6
    int v9; // eax@6
    int v10; // edi@9
    int v11; // eax@9
    int v12; // ST138_4@11
    int v13; // eax@11
    int v14; // ST134_4@14
    int v15; // eax@14
    int v16; // ST130_4@21
    int v17; // eax@21
    int v18; // eax@24
    int v19; // eax@24
    int v20; // eax@24
    int v21; // ST11C_4@30
    int v22; // eax@30
    int v23; // eax@32
    int v24; // ST118_4@39
    int v25; // eax@39
    int v26; // ST114_4@41
    int v27; // eax@41
    int v28; // STF4_4@47
    int v29; // eax@47
    int v30; // STE4_4@53
    int v31; // eax@53
    signed int v32; // eax@56
    signed int v33; // eax@63
    signed int v34; // eax@67
    signed int v35; // eax@71
    __int64 v36; // qax@79
    int result; // eax@84
    __int64 v38; // ST70_8@88
    signed int v39; // ST58_4@88
    signed int v40; // ST40_4@88
    const char *v41; // ST28_4@88
    const char *v42; // ST10_4@88
    const char *v43; // eax@88
    int v44; // eax@88
    int v45; // eax@88
    int v46; // eax@88
    int v47; // eax@88
    int v48; // eax@88
    int v49; // eax@88
    int v50; // eax@88
    int v51; // eax@88
    int v52; // eax@88
    int v53; // eax@88
    int v54; // STD0_4@92
    int v55; // eax@92
    __int64 v56; // qax@93
    int v57; // STCC_4@103
    int v58; // eax@103
    int v59; // STC8_4@115
    int v60; // eax@115
    int v61; // eax@119
    int v62; // STC4_4@126
    int v63; // eax@126
    int v64; // STC0_4@128
    int v65; // eax@128
    __int64 v66; // qax@129
    int v67; // STBC_4@140
    int v68; // eax@140
    int v69; // STB8_4@142
    int v70; // eax@142
    __int64 v71; // qax@147
    __int64 v72; // ST70_8@156
    signed int v73; // ST58_4@156
    signed int v74; // ST40_4@156
    const char *v75; // ST28_4@156
    const char *v76; // ST10_4@156
    const char *v77; // eax@156
    int v78; // eax@156
    int v79; // eax@156
    int v80; // eax@156
    int v81; // eax@156
    int v82; // eax@156
    int v83; // eax@156
    int v84; // eax@156
    int v85; // eax@156
    int v86; // eax@156
    int v87; // eax@156
    char v88; // [sp+B4h] [bp-A0h]@153
    int v89; // [sp+C8h] [bp-8Ch]@146
    int v90; // [sp+CCh] [bp-88h]@145
    int v91; // [sp+D0h] [bp-84h]@129
    int v92; // [sp+E4h] [bp-70h]@85
    int v93; // [sp+F8h] [bp-5Ch]@78
    int k; // [sp+FCh] [bp-58h]@77
    int v95; // [sp+100h] [bp-54h]@77
    int v96; // [sp+104h] [bp-50h]@55
    char v97; // [sp+11Bh] [bp-39h]@42
    int v98; // [sp+11Ch] [bp-38h]@38
    int v99; // [sp+120h] [bp-34h]@38
    int v100; // [sp+124h] [bp-30h]@22
    void *v101; // [sp+128h] [bp-2Ch]@5
    int v102; // [sp+12Ch] [bp-28h]@1
    int j; // [sp+130h] [bp-24h]@15
    int i; // [sp+134h] [bp-20h]@15
    int v105; // [sp+138h] [bp-1Ch]@1
    int v106; // [sp+13Ch] [bp-18h]@1
    int v107; // [sp+140h] [bp-14h]@1
    int v108; // [sp+144h] [bp-10h]@1
    int v109; // [sp+148h] [bp-Ch]@1
    int dest; // [sp+14Ch] [bp-8h]@1
    char v111; // [sp+151h] [bp-3h]@1
    char v112; // [sp+152h] [bp-2h]@1
    char v113; // [sp+153h] [bp-1h]@1

    CNetMsg::MoveFirst(a2);
    v108 = 0;
    v107 = 0;
    v106 = 0;
    v105 = 0;
    v2 = CNetMsg::__rs(a2, &v113);
    v3 = CNetMsg::__rs(v2, &v112);
    v4 = CNetMsg::__rs(v3, &v111);
    v5 = CNetMsg::__rs(v4, &dest);
    CNetMsg::__rs(v5, &v109);
    v102 = CInventory::GetItem(a1 + 792, v112, v111);
    if(!v102 || *(_DWORD *)(*(_DWORD *)(v102 + 20) + 4) != 2 || *(_DWORD *)(*(_DWORD *)(v102 + 20) + 8) != 1)
    {
        v6 = __eh_alloc(4);
        *(_DWORD *)v6 = 0;
        v7 = __tfi();
        __cp_push_exception(v6, v7, 0);
        __throw();
    }
    v101 = CItemList::FindIndex(gserver.Unk41208, dest);
    if(!v101)
    {
        v8 = __eh_alloc(4);
        *(_DWORD *)v8 = 0;
        v9 = __tfi();
        __cp_push_exception(v8, v9, 0);
        __throw();
    }
    if(*((_DWORD *)v101 + 1) != 4 || *((_DWORD *)v101 + 2) != 7)
    {
        v10 = __eh_alloc(4);
        *(_DWORD *)v10 = 0;
        v11 = __tfi();
        __cp_push_exception(v10, v11, 0);
        __throw();
    }
    if(!(*((_DWORD *)v101 + 17) & 0x40))
    {
        v12 = __eh_alloc(4);
        *(_DWORD *)v12 = 0;
        v13 = __tfi();
        __cp_push_exception(v12, v13, 0);
        __throw();
    }
    if(*(_DWORD *)(*(_DWORD *)(v102 + 20) + 76) != *((_DWORD *)v101 + 19)
        || *(_DWORD *)(*(_DWORD *)(v102 + 20) + 80) != *((_DWORD *)v101 + 20))
    {
        v14 = __eh_alloc(4);
        *(_DWORD *)v14 = 0;
        v15 = __tfi();
        __cp_push_exception(v14, v15, 0);
        __throw();
    }
    i = 0;
    j = 0;
    while(i <= 9)
    {
        if(*((_DWORD *)v101 + i + 28) != -1)
            ++j;
        ++i;
    }
    if(j != v109)
    {
        v16 = __eh_alloc(4);
        *(_DWORD *)v16 = 1;
        v17 = __tfi();
        __cp_push_exception(v16, v17, 0);
        __throw();
    }
    v108 = __builtin_vec_new(v109);
    v107 = __builtin_vec_new(v109);
    v106 = __builtin_vec_new(v109);
    v105 = __builtin_vec_new(8 * v109);
    v100 = 0;
    for(i = 0; i < v109; ++i)
    {
        v18 = CNetMsg::__rs(a2, (void *)(i + v108));
        v19 = CNetMsg::__rs(v18, (void *)(i + v107));
        v20 = CNetMsg::__rs(v19, (void *)(i + v106));
        CNetMsg::__rs(v20, (void *)(v105 + 8 * i));
        if(*(_BYTE *)(i + v108) < 0
            || *(_BYTE *)(i + v108) > 2
            || *(_BYTE *)(i + v107) < 0
            || *(_BYTE *)(i + v107) > 19
            || *(_BYTE *)(i + v106) < 0
            || *(_BYTE *)(i + v106) > 4)
        {
            v21 = __eh_alloc(4);
            *(_DWORD *)v21 = 0;
            v22 = __tfi();
            __cp_push_exception(v21, v22, 0);
            __throw();
        }
        if(*(_BYTE *)(i + v108))
        {
            if(*(_BYTE *)(i + v108) == 1)
            {
                v23 = a1 + 880;
            }
            else
            {
                if(*(_BYTE *)(i + v108) == 2)
                    v23 = a1 + 968;
                else
                    v23 = 0;
            }
        }
        else
        {
            v23 = a1 + 792;
        }
        v99 = v23;
        v98 = 0;
        if(!v23)
        {
            v24 = __eh_alloc(4);
            *(_DWORD *)v24 = 0;
            v25 = __tfi();
            __cp_push_exception(v24, v25, 0);
            __throw();
        }
        v98 = CInventory::GetItem(v99, *(_BYTE *)(i + v107), *(_BYTE *)(i + v106));
        if(!v98)
        {
            v26 = __eh_alloc(4);
            *(_DWORD *)v26 = 1;
            v27 = __tfi();
            __cp_push_exception(v26, v27, 0);
            __throw();
        }
        v97 = 0;
        for(j = 0; j <= 9; ++j)
        {
            if(*((_DWORD *)v101 + j + 28) != -1 && *(_DWORD *)(v98 + 28) == *((_DWORD *)v101 + j + 28))
            {
                if(*(_QWORD *)(v105 + 8 * i) != *((_DWORD *)v101 + j + 38))
                {
                    v28 = __eh_alloc(4);
                    *(_DWORD *)v28 = 1;
                    v29 = __tfi();
                    __cp_push_exception(v28, v29, 0);
                    __throw();
                }
                if(*((_DWORD *)v101 + j + 38) <= CItem::Count(v98))
                    v97 = 1;
                v100 += *((_DWORD *)v101 + j + 38) * *(_DWORD *)(*(_DWORD *)(v98 + 20) + 96);
            }
        }
        if(!v97)
        {
            v30 = __eh_alloc(4);
            *(_DWORD *)v30 = 1;
            v31 = __tfi();
            __cp_push_exception(v30, v31, 0);
            __throw();
        }
    }
    CNetMsg::CNetMsg((int)&v96);
    if((signed int)GetRandom(1, 10000) <= 600)
    {
        v98 = 0;
        v32 = *((_DWORD *)v101 + 19);
        if(v32 == 1)
        {
            v34 = GetRandom(0, 1) ? 502 : 504;
            v99 = v34;
        }
        else
        {
            if(v32 > 1)
            {
                if(v32 == 2)
                {
                    if(GetRandom(0, 1))
                        v35 = 496;
                    else
                        v35 = 502;
                    v99 = v35;
                }
            }
            else
            {
                if(!v32)
                {
                    if(GetRandom(0, 1))
                        v33 = 503;
                    else
                        v33 = 504;
                    v99 = v33;
                }
            }
        }
        v98 = CItemList::CreateItem(gserver.Unk41208, v99, -1, 0, 0, 1LL);
        if(v98)
        {
            v97 = 0;
            if(CInventory::AddItem(a1 + 792, v98, a1, 1, 1, -1, -1))
            {
                if(CItem::tab(v98) == -1)
                {
                    v97 = 1;
                    if(CInventory::FindItem(
                                 a1 + 792,
                                 (int)&v95,
                                 (int)&k,
                                 *(_DWORD *)(v98 + 28),
                                 *(_DWORD *)(v98 + 36),
                                 *(_DWORD *)(v98 + 40)))
                    {
                        v93 = CInventory::GetItem(a1 + 792, v95, k);
                        if(v93)
                        {
                            v36 = CItem::Count(v98);
                            ItemUpdateMsg((int)&v96, v93, v36);
                        }
                    }
                }
                else
                {
                    ItemAddMsg((int)&v96, v98);
                }
            }
            else
            {
                v98 = CArea::DropItem(*(_DWORD *)(a1 + 412), v98, a1);
                if(!v98)
                    return CNetMsg::_CNetMsg((int)&v96, 2);
                CNetMsg::CNetMsg((int)&v92);
                ItemDropMsg((int)&v92, a1, v98);
                CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v92, a1, 1, 4);
                *(_DWORD *)(v98 + 216) = *(_DWORD *)(a1 + 4);
                CNetMsg::_CNetMsg((int)&v92, 2);
            }
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v96);
            v38 = CItem::Count(v98);
            v39 = *(_DWORD *)(v98 + 40);
            v40 = *(_DWORD *)(v98 + 36);
            v41 = (const char *)(v98 + 44);
            v42 = (const char *)(*(_DWORD *)(v98 + 20) + 12);
            init((int)&v92, (int)"ITEM_PROCESS_SAMPLE", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
            v43 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v92);
            v44 = (int)CLogBuffer::__ls(v43, v42);
            v45 = CLogBuffer::__ls(v44, (int (__cdecl *)(_DWORD))delim);
            v46 = (int)CLogBuffer::__ls((const char *)v45, v41);
            v47 = CLogBuffer::__ls(v46, (int (__cdecl *)(_DWORD))delim);
            v48 = (int)CLogBuffer::__ls((char *)v47, v40);
            v49 = CLogBuffer::__ls(v48, (int (__cdecl *)(_DWORD))delim);
            v50 = (int)CLogBuffer::__ls((char *)v49, v39);
            v51 = CLogBuffer::__ls(v50, (int (__cdecl *)(_DWORD))delim);
            v52 = (int)CLogBuffer::__ls((char *)v51, v38);
            v53 = CLogBuffer::__ls(v52, (int (__cdecl *)(_DWORD))delim);
            CLogBuffer::__ls(v53, end);
            if(v97 && v98)
                (*(void (__cdecl **)(int, signed int))(*(_DWORD *)(v98 + 220) + 8))(v98, 3);
        }
    }
    if(*(_DWORD *)(a1 + 724) - v100 + *((_DWORD *)v101 + 24) > 15 * *(_DWORD *)(a1 + 728) / 10)
    {
        v54 = __eh_alloc(4);
        *(_DWORD *)v54 = 4;
        v55 = __tfi();
        __cp_push_exception(v54, v55, 0);
        __throw();
    }
    CInventory::Decrease(a1 + 792, v102, 1LL);
    v56 = CItem::Count(v102);
    if(SHIDWORD(v56) <= 0 && (HIDWORD(v56) || !(_DWORD)v56))
    {
        ItemDeleteMsg((int)&v96, v102);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v96);
        CPC::RemoveItemFromQuickSlot(a1, v102);
        CInventory::Remove(a1 + 792, v102, 1, 1);
    }
    else
    {
        ItemUpdateMsg((int)&v96, v102, -1LL);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v96);
    }
    v93 = (int)CSSkillProtoList::FindProto(gserver.Unk452244, *((_DWORD *)v101 + 48));
    if(!v93)
    {
        v57 = __eh_alloc(4);
        *(_DWORD *)v57 = 0;
        v58 = __tfi();
        __cp_push_exception(v57, v58, 0);
        __throw();
    }
    for(k = *(_DWORD *)(a1 + 716); k; k = *(_DWORD *)(k + 4))
    {
        if(*(_DWORD *)(v93 + 16) == -1)
        {
            if(***(_DWORD ***)k == *((_DWORD *)v101 + 48)
                && (signed int)*(_BYTE *)(*(_DWORD *)k + 4) >= *((_DWORD *)v101 + 49))
                break;
        }
        else
        {
            if(*(_DWORD *)(**(_DWORD **)k + 8) == *(_DWORD *)(v93 + 8)
                && *(_DWORD *)(**(_DWORD **)k + 16) >= *(_DWORD *)(v93 + 16)
                && (signed int)*(_BYTE *)(*(_DWORD *)k + 4) >= *((_DWORD *)v101 + 49))
                break;
        }
    }
    if(!k)
    {
        v59 = __eh_alloc(4);
        *(_DWORD *)v59 = 2;
        v60 = __tfi();
        __cp_push_exception(v59, v60, 0);
        __throw();
    }
    for(i = 0; i < v109; ++i)
    {
        if(*(_BYTE *)(i + v108))
        {
            if(*(_BYTE *)(i + v108) == 1)
            {
                v61 = a1 + 880;
            }
            else
            {
                if(*(_BYTE *)(i + v108) == 2)
                    v61 = a1 + 968;
                else
                    v61 = 0;
            }
        }
        else
        {
            v61 = a1 + 792;
        }
        v95 = v61;
        if(!v61)
        {
            v62 = __eh_alloc(4);
            *(_DWORD *)v62 = 0;
            v63 = __tfi();
            __cp_push_exception(v62, v63, 0);
            __throw();
        }
        v98 = CInventory::GetItem(v95, *(_BYTE *)(i + v107), *(_BYTE *)(i + v106));
        if(!v98)
        {
            v64 = __eh_alloc(4);
            *(_DWORD *)v64 = 0;
            v65 = __tfi();
            __cp_push_exception(v64, v65, 0);
            __throw();
        }
        CNetMsg::CNetMsg((int)&v91);
        CInventory::Decrease(v95, v98, *(_QWORD *)(v105 + 8 * i));
        v66 = CItem::Count(v98);
        if(SHIDWORD(v66) <= 0 && (HIDWORD(v66) || !(_DWORD)v66))
        {
            ItemDeleteMsg((int)&v91, v98);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v91);
            CPC::RemoveItemFromQuickSlot(a1, v98);
            CInventory::Remove(v95, v98, 1, 1);
        }
        else
        {
            ItemUpdateMsg((int)&v91, v98, -*(_QWORD *)(v105 + 8 * i));
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v91);
        }
        CNetMsg::_CNetMsg((int)&v91, 2);
    }
    v95 = GetRandom(1, 10000);
    if(v95 > *(_DWORD *)(4 * (*(_BYTE *)(*(_DWORD *)k + 4) - 1) + **(_DWORD **)k + 68))
    {
        v67 = __eh_alloc(4);
        *(_DWORD *)v67 = 3;
        v68 = __tfi();
        __cp_push_exception(v67, v68, 0);
        __throw();
    }
    CNetMsg::CNetMsg((int)&v91);
    v98 = 0;
    v98 = CItemList::CreateItem(gserver.Unk41208, dest, -1, 0, 0, 1LL);
    ItemProcessRepMsg((int)&v91, 5);
    if(!v98)
    {
        v69 = __eh_alloc(4);
        *(_DWORD *)v69 = 0;
        v70 = __tfi();
        __cp_push_exception(v69, v70, 0);
        __throw();
    }
    v97 = 0;
    if(CInventory::AddItem(a1 + 792, v98, a1, 1, 1, -1, -1))
    {
        if(CItem::tab(v98) == -1)
        {
            v97 = 1;
            if(CInventory::FindItem(
                         a1 + 792,
                         (int)&v99,
                         (int)&v90,
                         *(_DWORD *)(v98 + 28),
                         *(_DWORD *)(v98 + 36),
                         *(_DWORD *)(v98 + 40)))
            {
                v89 = CInventory::GetItem(a1 + 792, v99, v90);
                if(v89)
                {
                    v71 = CItem::Count(v98);
                    ItemUpdateMsg((int)&v96, v89, v71);
                }
            }
        }
        else
        {
            ItemAddMsg((int)&v96, v98);
        }
    }
    else
    {
        v98 = CArea::DropItem(*(_DWORD *)(a1 + 412), v98, a1);
        if(!v98)
        {
            CNetMsg::_CNetMsg((int)&v91, 2);
            return CNetMsg::_CNetMsg((int)&v96, 2);
        }
        CNetMsg::CNetMsg((int)&v88);
        ItemDropMsg((int)&v88, a1, v98);
        CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v88, a1, 1, 4);
        *(_DWORD *)(v98 + 216) = *(_DWORD *)(a1 + 4);
        CNetMsg::_CNetMsg((int)&v88, 2);
    }
    if(*(_DWORD *)(a1 + 768))
        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v96);
    v72 = CItem::Count(v98);
    v73 = *(_DWORD *)(v98 + 40);
    v74 = *(_DWORD *)(v98 + 36);
    v75 = (const char *)(v98 + 44);
    v76 = (const char *)(*(_DWORD *)(v98 + 20) + 12);
    init((int)&v92, (int)"ITEM_PROCESS", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
    v77 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v92);
    v78 = (int)CLogBuffer::__ls(v77, v76);
    v79 = CLogBuffer::__ls(v78, (int (__cdecl *)(_DWORD))delim);
    v80 = (int)CLogBuffer::__ls((const char *)v79, v75);
    v81 = CLogBuffer::__ls(v80, (int (__cdecl *)(_DWORD))delim);
    v82 = (int)CLogBuffer::__ls((char *)v81, v74);
    v83 = CLogBuffer::__ls(v82, (int (__cdecl *)(_DWORD))delim);
    v84 = (int)CLogBuffer::__ls((char *)v83, v73);
    v85 = CLogBuffer::__ls(v84, (int (__cdecl *)(_DWORD))delim);
    v86 = (int)CLogBuffer::__ls((char *)v85, v72);
    v87 = CLogBuffer::__ls(v86, (int (__cdecl *)(_DWORD))delim);
    CLogBuffer::__ls(v87, end);
    if(v97 && v98)
        (*(void (__cdecl **)(int, signed int))(*(_DWORD *)(v98 + 220) + 8))(v98, 3);
    if(*(_DWORD *)(a1 + 768))
        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v91);
    EffectEtcMsg((int)&v91, a1, 5);
    CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v91, a1, 1, 4);
    CNetMsg::_CNetMsg((int)&v91, 2);
    result = CNetMsg::_CNetMsg((int)&v96, 2);
    if(v108 && v108)
        result = __builtin_vec_delete(v108);
    if(v107 && v107)
        result = __builtin_vec_delete(v107);
    if(v106 && v106)
        result = __builtin_vec_delete(v106);
    if(v105 && v105)
        result = __builtin_vec_delete(v105);
    return result;
}
// 804969C: using guessed type int __cdecl __cp_push_exception(_DWORD, _DWORD, _DWORD);
// 804982C: using guessed type int __tfi(void);
// 80498AC: using guessed type int __throw(void);
// 8049A5C: using guessed type int __cdecl __builtin_vec_new(_DWORD);
// 8049B2C: using guessed type int __cdecl __builtin_vec_delete(_DWORD);
// 8049C7C: using guessed type int __cdecl __eh_alloc(_DWORD);

//----- (080B1110) --------------------------------------------------------
int __cdecl do_ItemMakeReq(int a1, int a2)
{
    int v2; // eax@1
    int v3; // eax@1
    int v4; // eax@1
    int v5; // eax@1
    int v6; // ebx@3
    int v7; // eax@3
    int v8; // esi@6
    int v9; // eax@6
    int v10; // edi@8
    int v11; // eax@8
    int v12; // ST16C_4@12
    int v13; // eax@12
    int v14; // ST168_4@14
    int v15; // eax@14
    int v16; // ST164_4@17
    int v17; // eax@17
    int v18; // ST160_4@20
    int v19; // eax@20
    int v20; // ST15C_4@23
    int v21; // eax@23
    int v22; // ST158_4@30
    int v23; // eax@30
    int v24; // eax@33
    int v25; // eax@33
    int v26; // eax@33
    int v27; // ST144_4@39
    int v28; // eax@39
    int v29; // eax@41
    int v30; // ST140_4@48
    int v31; // eax@48
    int v32; // ST13C_4@50
    int v33; // eax@50
    int v34; // ST11C_4@56
    int v35; // eax@56
    int v36; // ST10C_4@62
    int v37; // eax@62
    int v38; // STF8_4@66
    int v39; // eax@66
    int v40; // STE8_4@69
    int v41; // eax@69
    int v42; // STE4_4@71
    int v43; // eax@71
    int v44; // STE0_4@82
    int v45; // eax@82
    int v46; // eax@86
    int v47; // STDC_4@93
    int v48; // eax@93
    int v49; // STD8_4@95
    int v50; // eax@95
    __int64 v51; // qax@96
    int v52; // eax@111
    int v53; // STC0_4@112
    int v54; // eax@112
    int v55; // STBC_4@117
    int v56; // eax@117
    __int64 v57; // qax@118
    __int64 v58; // qax@131
    int result; // eax@136
    __int64 v60; // ST70_8@142
    signed int v61; // ST58_4@142
    signed int v62; // ST40_4@142
    const char *v63; // ST28_4@142
    const char *v64; // ST10_4@142
    const char *v65; // eax@142
    int v66; // eax@142
    int v67; // eax@142
    int v68; // eax@142
    int v69; // eax@142
    int v70; // eax@142
    int v71; // eax@142
    int v72; // eax@142
    int v73; // eax@142
    int v74; // eax@142
    int v75; // eax@142
    int v76; // [sp+E8h] [bp-8Ch]@137
    char v77; // [sp+FCh] [bp-78h]@137
    int v78; // [sp+110h] [bp-64h]@130
    int v79; // [sp+114h] [bp-60h]@129
    int v80; // [sp+118h] [bp-5Ch]@129
    int v81; // [sp+11Ch] [bp-58h]@96
    int v82; // [sp+130h] [bp-44h]@94
    int v83; // [sp+134h] [bp-40h]@92
    char v84; // [sp+13Bh] [bp-39h]@51
    void *v85; // [sp+13Ch] [bp-38h]@47
    int k; // [sp+140h] [bp-34h]@47
    int v87; // [sp+144h] [bp-30h]@31
    void *v88; // [sp+148h] [bp-2Ch]@7
    int v89; // [sp+14Ch] [bp-28h]@1
    int j; // [sp+150h] [bp-24h]@24
    int i; // [sp+154h] [bp-20h]@24
    int v92; // [sp+158h] [bp-1Ch]@1
    int v93; // [sp+15Ch] [bp-18h]@1
    int v94; // [sp+160h] [bp-14h]@1
    int v95; // [sp+164h] [bp-10h]@1
    int v96; // [sp+168h] [bp-Ch]@1
    int dest; // [sp+16Ch] [bp-8h]@1
    char v98; // [sp+171h] [bp-3h]@1
    char v99; // [sp+172h] [bp-2h]@1
    char v100; // [sp+173h] [bp-1h]@1

    CNetMsg::MoveFirst(a2);
    v95 = 0;
    v94 = 0;
    v93 = 0;
    v92 = 0;
    v2 = CNetMsg::__rs(a2, &v100);
    v3 = CNetMsg::__rs(v2, &v99);
    v4 = CNetMsg::__rs(v3, &v98);
    v5 = CNetMsg::__rs(v4, &dest);
    CNetMsg::__rs(v5, &v96);
    v89 = CInventory::GetItem(a1 + 792, v99, v98);
    if(!v89 || *(_DWORD *)(*(_DWORD *)(v89 + 20) + 4) != 2)
    {
        v6 = __eh_alloc(4);
        *(_DWORD *)v6 = 0;
        v7 = __tfi();
        __cp_push_exception(v6, v7, 0);
        __throw();
    }
    if(*(_DWORD *)(*(_DWORD *)(v89 + 20) + 8) != 2 && *(_DWORD *)(*(_DWORD *)(v89 + 20) + 8) != 4)
    {
        v8 = __eh_alloc(4);
        *(_DWORD *)v8 = 0;
        v9 = __tfi();
        __cp_push_exception(v8, v9, 0);
        __throw();
    }
    v88 = CItemList::FindIndex(gserver.Unk41208, dest);
    if(!v88)
    {
        v10 = __eh_alloc(4);
        *(_DWORD *)v10 = 0;
        v11 = __tfi();
        __cp_push_exception(v10, v11, 0);
        __throw();
    }
    if(*((_DWORD *)v88 + 1) && *((_DWORD *)v88 + 1) != 1 && *((_DWORD *)v88 + 1) != 6)
    {
        v12 = __eh_alloc(4);
        *(_DWORD *)v12 = 0;
        v13 = __tfi();
        __cp_push_exception(v12, v13, 0);
        __throw();
    }
    if(!(*((_DWORD *)v88 + 17) & 0x40))
    {
        v14 = __eh_alloc(4);
        *(_DWORD *)v14 = 0;
        v15 = __tfi();
        __cp_push_exception(v14, v15, 0);
        __throw();
    }
    if(*(_DWORD *)(*(_DWORD *)(v89 + 20) + 76) != *((_DWORD *)v88 + 1)
        || ((unsigned __int8)(*(_DWORD *)(*(_DWORD *)(v89 + 20) + 80) >> *((_DWORD *)v88 + 2)) ^ 1) & 1)
    {
        v16 = __eh_alloc(4);
        *(_DWORD *)v16 = 0;
        v17 = __tfi();
        __cp_push_exception(v16, v17, 0);
        __throw();
    }
    if(*((_DWORD *)v88 + 1) == 6)
    {
        if(*(_DWORD *)(*(_DWORD *)(v89 + 20) + 84) != *((_DWORD *)v88 + 21))
        {
            v18 = __eh_alloc(4);
            *(_DWORD *)v18 = 0;
            v19 = __tfi();
            __cp_push_exception(v18, v19, 0);
            __throw();
        }
    }
    else
    {
        if(*(_WORD *)(*(_DWORD *)(v89 + 20) + 100) != *((_WORD *)v88 + 50))
        {
            v20 = __eh_alloc(4);
            *(_DWORD *)v20 = 0;
            v21 = __tfi();
            __cp_push_exception(v20, v21, 0);
            __throw();
        }
    }
    i = 0;
    j = 0;
    while(i <= 9)
    {
        if(*((_DWORD *)v88 + i + 28) != -1)
            ++j;
        ++i;
    }
    if(j != v96)
    {
        v22 = __eh_alloc(4);
        *(_DWORD *)v22 = 1;
        v23 = __tfi();
        __cp_push_exception(v22, v23, 0);
        __throw();
    }
    v95 = __builtin_vec_new(v96);
    v94 = __builtin_vec_new(v96);
    v93 = __builtin_vec_new(v96);
    v92 = __builtin_vec_new(8 * v96);
    v87 = 0;
    for(i = 0; i < v96; ++i)
    {
        v24 = CNetMsg::__rs(a2, (void *)(i + v95));
        v25 = CNetMsg::__rs(v24, (void *)(i + v94));
        v26 = CNetMsg::__rs(v25, (void *)(i + v93));
        CNetMsg::__rs(v26, (void *)(v92 + 8 * i));
        if(*(_BYTE *)(i + v95) < 0
            || *(_BYTE *)(i + v95) > 2
            || *(_BYTE *)(i + v94) < 0
            || *(_BYTE *)(i + v94) > 19
            || *(_BYTE *)(i + v93) < 0
            || *(_BYTE *)(i + v93) > 4)
        {
            v27 = __eh_alloc(4);
            *(_DWORD *)v27 = 0;
            v28 = __tfi();
            __cp_push_exception(v27, v28, 0);
            __throw();
        }
        if(*(_BYTE *)(i + v95))
        {
            if(*(_BYTE *)(i + v95) == 1)
            {
                v29 = a1 + 880;
            }
            else
            {
                if(*(_BYTE *)(i + v95) == 2)
                    v29 = a1 + 968;
                else
                    v29 = 0;
            }
        }
        else
        {
            v29 = a1 + 792;
        }
        k = v29;
        v85 = 0;
        if(!v29)
        {
            v30 = __eh_alloc(4);
            *(_DWORD *)v30 = 0;
            v31 = __tfi();
            __cp_push_exception(v30, v31, 0);
            __throw();
        }
        v85 = (void *)CInventory::GetItem(k, *(_BYTE *)(i + v94), *(_BYTE *)(i + v93));
        if(!v85)
        {
            v32 = __eh_alloc(4);
            *(_DWORD *)v32 = 1;
            v33 = __tfi();
            __cp_push_exception(v32, v33, 0);
            __throw();
        }
        v84 = 0;
        for(j = 0; j <= 9; ++j)
        {
            if(*((_DWORD *)v88 + j + 28) != -1 && *((_DWORD *)v85 + 7) == *((_DWORD *)v88 + j + 28))
            {
                if(*(_QWORD *)(v92 + 8 * i) != *((_DWORD *)v88 + j + 38))
                {
                    v34 = __eh_alloc(4);
                    *(_DWORD *)v34 = 1;
                    v35 = __tfi();
                    __cp_push_exception(v34, v35, 0);
                    __throw();
                }
                if(*((_DWORD *)v88 + j + 38) <= CItem::Count((int)v85))
                    v84 = 1;
                v87 += *((_DWORD *)v88 + j + 38) * *(_DWORD *)(*((_DWORD *)v85 + 5) + 96);
                break;
            }
        }
        if(!v84)
        {
            v36 = __eh_alloc(4);
            *(_DWORD *)v36 = 1;
            v37 = __tfi();
            __cp_push_exception(v36, v37, 0);
            __throw();
        }
    }
    if(*(_DWORD *)(*(_DWORD *)(v89 + 20) + 8) == 4)
    {
        if(*(_DWORD *)(*(_DWORD *)(v89 + 20) + 88) * *((_DWORD *)v88 + 24) + *(_DWORD *)(a1 + 724) - v87 > 15 * *(_DWORD *)(a1 + 728) / 10)
        {
            v38 = __eh_alloc(4);
            *(_DWORD *)v38 = 4;
            v39 = __tfi();
            __cp_push_exception(v38, v39, 0);
            __throw();
        }
    }
    else
    {
        if(*(_DWORD *)(a1 + 724) - v87 + *((_DWORD *)v88 + 24) > 15 * *(_DWORD *)(a1 + 728) / 10)
        {
            v40 = __eh_alloc(4);
            *(_DWORD *)v40 = 4;
            v41 = __tfi();
            __cp_push_exception(v40, v41, 0);
            __throw();
        }
    }
    v85 = CSSkillProtoList::FindProto(gserver.Unk452244, *((_DWORD *)v88 + 48));
    if(!v85)
    {
        v42 = __eh_alloc(4);
        *(_DWORD *)v42 = 0;
        v43 = __tfi();
        __cp_push_exception(v42, v43, 0);
        __throw();
    }
    k = *(_DWORD *)(a1 + 716);
    for(k = *(_DWORD *)(a1 + 716); k; k = *(_DWORD *)(k + 4))
    {
        if(*((_DWORD *)v85 + 4) == -1)
        {
            if(***(_DWORD ***)k == *((_DWORD *)v88 + 48)
                && (signed int)*(_BYTE *)(*(_DWORD *)k + 4) >= *((_DWORD *)v88 + 49))
                break;
        }
        else
        {
            if(*(_DWORD *)(**(_DWORD **)k + 8) == *((_DWORD *)v85 + 2)
                && *(_DWORD *)(**(_DWORD **)k + 16) >= *((_DWORD *)v85 + 4))
                break;
        }
    }
    if(!k)
    {
        v44 = __eh_alloc(4);
        *(_DWORD *)v44 = 2;
        v45 = __tfi();
        __cp_push_exception(v44, v45, 0);
        __throw();
    }
    for(i = 0; i < v96; ++i)
    {
        if(*(_BYTE *)(i + v95))
        {
            if(*(_BYTE *)(i + v95) == 1)
            {
                v46 = a1 + 880;
            }
            else
            {
                if(*(_BYTE *)(i + v95) == 2)
                    v46 = a1 + 968;
                else
                    v46 = 0;
            }
        }
        else
        {
            v46 = a1 + 792;
        }
        v83 = v46;
        if(!v46)
        {
            v47 = __eh_alloc(4);
            *(_DWORD *)v47 = 0;
            v48 = __tfi();
            __cp_push_exception(v47, v48, 0);
            __throw();
        }
        v82 = CInventory::GetItem(v83, *(_BYTE *)(i + v94), *(_BYTE *)(i + v93));
        if(!v82)
        {
            v49 = __eh_alloc(4);
            *(_DWORD *)v49 = 0;
            v50 = __tfi();
            __cp_push_exception(v49, v50, 0);
            __throw();
        }
        CNetMsg::CNetMsg((int)&v81);
        CInventory::Decrease(v83, v82, *(_QWORD *)(v92 + 8 * i));
        v51 = CItem::Count(v82);
        if(SHIDWORD(v51) <= 0 && (HIDWORD(v51) || !(_DWORD)v51))
        {
            ItemDeleteMsg((int)&v81, v82);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v81);
            CPC::RemoveItemFromQuickSlot(a1, v82);
            CInventory::Remove(v83, v82, 1, 1);
        }
        else
        {
            ItemUpdateMsg((int)&v81, v82, -*(_QWORD *)(v92 + 8 * i));
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v81);
        }
        CNetMsg::_CNetMsg((int)&v81, 2);
    }
    if(*(_DWORD *)(*(_DWORD *)(v89 + 20) + 8) == 4)
        v82 = *(_DWORD *)(4 * (*(_BYTE *)(*(_DWORD *)k + 4) - 1) + **(_DWORD **)k + 88)
                + 250 * (*(_DWORD *)(4 * (*(_BYTE *)(*(_DWORD *)k + 4) - 1) + **(_DWORD **)k + 68) - *((_DWORD *)v88 + 21));
    else
        v82 = *(_DWORD *)(4 * (*(_BYTE *)(*(_DWORD *)k + 4) - 1) + **(_DWORD **)k + 88)
                + 250 * (*(_DWORD *)(4 * (*(_BYTE *)(*(_DWORD *)k + 4) - 1) + **(_DWORD **)k + 68) - *((_WORD *)v88 + 50));
    if(v82 > 8000)
        v82 = 8000;
    v52 = GetRandom(1, 10000);
    if(v52 > v82)
    {
        v53 = __eh_alloc(4);
        *(_DWORD *)v53 = 3;
        v54 = __tfi();
        __cp_push_exception(v53, v54, 0);
        __throw();
    }
    v83 = 0;
    if(*(_DWORD *)(*(_DWORD *)(v89 + 20) + 8) == 4)
        v83 = CItemList::CreateItem(gserver.Unk41208, dest, -1, 0, 0, *(_DWORD *)(*(_DWORD *)(v89 + 20) + 88));
    else
        v83 = CItemList::CreateItem(gserver.Unk41208, dest, -1, 0, 0, 1LL);
    if(!v83)
    {
        v55 = __eh_alloc(4);
        *(_DWORD *)v55 = 0;
        v56 = __tfi();
        __cp_push_exception(v55, v56, 0);
        __throw();
    }
    CNetMsg::CNetMsg((int)&v81);
    CInventory::Decrease(a1 + 792, v89, 1LL);
    v57 = CItem::Count(v89);
    if(SHIDWORD(v57) <= 0 && (HIDWORD(v57) || !(_DWORD)v57))
    {
        ItemDeleteMsg((int)&v81, v89);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v81);
        CPC::RemoveItemFromQuickSlot(a1, v89);
        CInventory::Remove(a1 + 792, v89, 1, 1);
    }
    else
    {
        ItemUpdateMsg((int)&v81, v89, -1LL);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v81);
    }
    v84 = 0;
    if(CInventory::AddItem(a1 + 792, v83, a1, 1, 1, -1, -1))
    {
        if(CItem::tab(v83) == -1)
        {
            v84 = 1;
            if(CInventory::FindItem(
                         a1 + 792,
                         (int)&v80,
                         (int)&v79,
                         *(_DWORD *)(v83 + 28),
                         *(_DWORD *)(v83 + 36),
                         *(_DWORD *)(v83 + 40)))
            {
                v78 = CInventory::GetItem(a1 + 792, v80, v79);
                if(v78)
                {
                    v58 = CItem::Count(v83);
                    ItemUpdateMsg((int)&v81, v78, v58);
                }
            }
        }
        else
        {
            ItemAddMsg((int)&v81, v83);
        }
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v81);
        v60 = CItem::Count(v83);
        v61 = *(_DWORD *)(v83 + 40);
        v62 = *(_DWORD *)(v83 + 36);
        v63 = (const char *)(v83 + 44);
        v64 = (const char *)(*(_DWORD *)(v83 + 20) + 12);
        init((int)&v76, (int)"ITEM_MAKE", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
        v65 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v76);
        v66 = (int)CLogBuffer::__ls(v65, v64);
        v67 = CLogBuffer::__ls(v66, (int (__cdecl *)(_DWORD))delim);
        v68 = (int)CLogBuffer::__ls((const char *)v67, v63);
        v69 = CLogBuffer::__ls(v68, (int (__cdecl *)(_DWORD))delim);
        v70 = (int)CLogBuffer::__ls((char *)v69, v62);
        v71 = CLogBuffer::__ls(v70, (int (__cdecl *)(_DWORD))delim);
        v72 = (int)CLogBuffer::__ls((char *)v71, v61);
        v73 = CLogBuffer::__ls(v72, (int (__cdecl *)(_DWORD))delim);
        v74 = (int)CLogBuffer::__ls((char *)v73, v60);
        v75 = CLogBuffer::__ls(v74, (int (__cdecl *)(_DWORD))delim);
        CLogBuffer::__ls(v75, end);
        if(v84 && v83)
            (*(void (__cdecl **)(int, signed int))(*(_DWORD *)(v83 + 220) + 8))(v83, 3);
        CNetMsg::CNetMsg((int)&v77);
        ItemMakeRepMsg((int)&v77, 6);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v77);
        EffectEtcMsg((int)&v77, a1, 6);
        CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v77, a1, 1, 4);
        CPC::SaveNow(a1, 0);
        CNetMsg::_CNetMsg((int)&v77, 2);
        result = CNetMsg::_CNetMsg((int)&v81, 2);
    }
    else
    {
        v83 = CArea::DropItem(*(_DWORD *)(a1 + 412), v83, a1);
        if(!v83)
            return CNetMsg::_CNetMsg((int)&v81, 2);
        CNetMsg::CNetMsg((int)&v77);
        ItemDropMsg((int)&v77, a1, v83);
        CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v77, a1, 1, 4);
        *(_DWORD *)(v83 + 216) = *(_DWORD *)(a1 + 4);
        CNetMsg::CNetMsg((int)&v76);
        ItemMakeRepMsg((int)&v76, 6);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v76);
        CNetMsg::_CNetMsg((int)&v76, 2);
        CNetMsg::_CNetMsg((int)&v77, 2);
        result = CNetMsg::_CNetMsg((int)&v81, 2);
    }
    if(v95 && v95)
        result = __builtin_vec_delete(v95);
    if(v94 && v94)
        result = __builtin_vec_delete(v94);
    if(v93 && v93)
        result = __builtin_vec_delete(v93);
    if(v92 && v92)
        result = __builtin_vec_delete(v92);
    return result;
}
// 804969C: using guessed type int __cdecl __cp_push_exception(_DWORD, _DWORD, _DWORD);
// 804982C: using guessed type int __tfi(void);
// 80498AC: using guessed type int __throw(void);
// 8049A5C: using guessed type int __cdecl __builtin_vec_new(_DWORD);
// 8049B2C: using guessed type int __cdecl __builtin_vec_delete(_DWORD);
// 8049C7C: using guessed type int __cdecl __eh_alloc(_DWORD);

//----- (080B2BB0) --------------------------------------------------------
int __cdecl do_ItemMixReq(int a1, int a2)
{
    int v2; // eax@1
    int v3; // eax@1
    int v5; // eax@10
    __int64 v6; // qax@29
    char v7; // cl@49
    __int64 v8; // qax@49
    int v9; // STC0_4@55
    int v10; // STB8_4@55
    signed int v11; // ecx@55
    signed int v12; // ST88_4@86
    __int64 v13; // ST70_8@86
    signed int v14; // ST58_4@86
    signed int v15; // ST40_4@86
    const char *v16; // ST28_4@86
    const char *v17; // ST10_4@86
    const char *v18; // eax@86
    int v19; // eax@86
    int v20; // eax@86
    int v21; // eax@86
    int v22; // eax@86
    int v23; // eax@86
    int v24; // eax@86
    int v25; // eax@86
    int v26; // eax@86
    int v27; // eax@86
    int v28; // eax@86
    signed int v29; // ST88_4@89
    signed int v30; // ST70_4@89
    int v31; // eax@89
    int v32; // eax@89
    int v33; // eax@89
    int v34; // [sp+40h] [bp-84h]@81
    int v35; // [sp+54h] [bp-70h]@56
    int v36; // [sp+58h] [bp-6Ch]@45
    __int64 v37; // [sp+5Ch] [bp-68h]@45
    int v38; // [sp+64h] [bp-60h]@45
    int j; // [sp+68h] [bp-5Ch]@47
    int v40; // [sp+6Ch] [bp-58h]@43
    int v41; // [sp+70h] [bp-54h]@38
    unsigned int v42; // [sp+74h] [bp-50h]@38
    int v43; // [sp+78h] [bp-4Ch]@29
    char v44; // [sp+8Fh] [bp-35h]@18
    char v45[12]; // [sp+90h] [bp-34h]@20
    int i; // [sp+9Ch] [bp-28h]@8
    int v47; // [sp+A0h] [bp-24h]@1
    char v48; // [sp+A4h] [bp-20h]@1
    char v49[4]; // [sp+B8h] [bp-Ch]@10
    char v50[5]; // [sp+BCh] [bp-8h]@10
    char v51; // [sp+C1h] [bp-3h]@1
    char v52; // [sp+C2h] [bp-2h]@1
    char dest; // [sp+C3h] [bp-1h]@1

    CNetMsg::MoveFirst(a2);
    CNetMsg::CNetMsg((int)&v48);
    v2 = CNetMsg::__rs(a2, &dest);
    v3 = CNetMsg::__rs(v2, &v52);
    CNetMsg::__rs(v3, &v51);
    v47 = CInventory::GetItem(a1 + 792, v52, v51);
    if(!v47
        || *(_DWORD *)(*(_DWORD *)(v47 + 20) + 4) != 2
        || *(_DWORD *)(*(_DWORD *)(v47 + 20) + 8) != 3
        || *(_DWORD *)(*(_DWORD *)(v47 + 20) + 76))
    {
        ItemMixRepMsg((int)&v48, 1);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v48);
        return CNetMsg::_CNetMsg((int)&v48, 2);
    }
    for(i = 0; i <= 2; ++i)
    {
        v5 = CNetMsg::__rs(a2, &v50[i]);
        CNetMsg::__rs(v5, &v49[i]);
        if(v50[i] < 0 || v50[i] > 19 || v49[i] < 0 || v49[i] > 4)
        {
            ItemMixRepMsg((int)&v48, 0);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v48);
            return CNetMsg::_CNetMsg((int)&v48, 2);
        }
    }
    v44 = 0;
    for(i = 0; i <= 2; ++i)
    {
        *(_DWORD *)&v45[4 * i] = CInventory::GetItem(a1 + 792, v50[i], v49[i]);
        if(!*(_DWORD *)&v45[4 * i]
            || !CItem::IsAccessary(*(_DWORD *)&v45[4 * i])
            || *(_BYTE *)(*(_DWORD *)&v45[4 * i] + 32) != -1)
        {
            ItemMixRepMsg((int)&v48, 2);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v48);
            return CNetMsg::_CNetMsg((int)&v48, 2);
        }
        if(*(_DWORD *)(*(_DWORD *)&v45[4 * i] + 168) == 1)
            v44 = 1;
    }
    CNetMsg::CNetMsg((int)&v43);
    CInventory::Decrease(a1 + 792, v47, 1LL);
    v6 = CItem::Count(v47);
    if(SHIDWORD(v6) <= 0 && (HIDWORD(v6) || !(_DWORD)v6))
    {
        ItemDeleteMsg((int)&v43, v47);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v43);
        CPC::RemoveItemFromQuickSlot(a1, v47);
        CInventory::Remove(a1 + 792, v47, 1, 1);
    }
    else
    {
        ItemUpdateMsg((int)&v43, v47, -1LL);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v43);
    }
    v42 = GetRandom(0, 2);
    v41 = CItemList::CreateItem(gserver.Unk41208, **(_DWORD **)(*(_DWORD *)&v45[4 * v42] + 20), -1, 0, 0, 1LL);
    if(!v41)
    {
        ItemMixRepMsg((int)&v48, 0);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v48);
        CNetMsg::_CNetMsg((int)&v43, 2);
        return CNetMsg::_CNetMsg((int)&v48, 2);
    }
    if(v44)
        v40 = GetRandom(3, 5);
    else
        v40 = GetRandom(2, 4);
    v38 = __builtin_vec_new(4 * v40);
    v37 = 0LL;
    v36 = 24;
    i = 0;
    while(i < v40)
    {
        *(_DWORD *)(v38 + 4 * i) = GetRandom(0, 23);
        for(j = 0; ; ++j)
        {
            if(j <= 23)
            {
                v7 = j
                     + *(_BYTE *)(v38 + 4 * i)
                     - 24
                     * (((signed int)((unsigned __int64)(715827883LL * (j + *(_DWORD *)(v38 + 4 * i))) >> 32) >> 2)
                        - ((j + *(_DWORD *)(v38 + 4 * i)) >> 31));
                v8 = v37 >> (v7 & 0x1F);
                if(v7 & 0x20)
                    LOBYTE(v8) = (unsigned __int64)(v37 >> (v7 & 0x1F)) >> 32;
                if(v8 & 1)
                    continue;
            }
            break;
        }
        if(j == 24)
        {
            v40 = i;
        }
        else
        {
            v9 = 4 * i;
            v10 = v38;
            v11 = j + *(_DWORD *)(v38 + 4 * i);
            *(_DWORD *)(v38 + 4 * i) = v11 / 24;
            *(_DWORD *)(v10 + v9) = v11 - 24 * *(_DWORD *)(v10 + v9);
        }
        v37 |= 1LL << *(_BYTE *)(v38 + 4 * i);
        v35 = (int)COptionProtoList::FindProto(gserver.Unk452236, *(_DWORD *)(v38 + 4 * i));
        if(v35 && !(((unsigned __int8)(*(_DWORD *)(v35 + 72) >> *(_DWORD *)(*(_DWORD *)(v41 + 20) + 8)) ^ 1) & 1))
            ++i;
    }
    for(i = 0; i < v40; ++i)
    {
        v35 = (int)COptionProtoList::FindProto(gserver.Unk452236, *(_DWORD *)(v38 + 4 * i));
        if(!v35)
        {
            ItemMixRepMsg((int)&v48, 0);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v48);
            CNetMsg::_CNetMsg((int)&v43, 2);
            return CNetMsg::_CNetMsg((int)&v48, 2);
        }
        ++*(_DWORD *)(v41 + 168);
        COption::MakeOptionValue(v41 + 20 * i + 68, v35, *(_DWORD *)(a1 + 60), v40);
    }
    if(v38)
        __builtin_vec_delete(v38);
    for(i = 0; i <= 2; ++i)
    {
        ItemDeleteMsg((int)&v43, *(_DWORD *)&v45[4 * i]);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v43);
        CPC::RemoveItemFromQuickSlot(a1, *(_DWORD *)&v45[4 * i]);
        CInventory::Remove(a1 + 792, *(_DWORD *)&v45[4 * i], 1, 1);
    }
    if(CInventory::AddItem(a1 + 792, v41, a1, 1, 1, -1, -1))
    {
        if(CItem::tab(v41) == -1)
        {
            if(v41)
                (*(void (__cdecl **)(int, signed int))(*(_DWORD *)(v41 + 220) + 8))(v41, 3);
            v41 = 0;
            CNetMsg::_CNetMsg((int)&v43, 2);
            return CNetMsg::_CNetMsg((int)&v48, 2);
        }
        ItemAddMsg((int)&v43, v41);
    }
    else
    {
        v41 = CArea::DropItem(*(_DWORD *)(a1 + 412), v41, a1);
        if(!v41)
        {
            CNetMsg::_CNetMsg((int)&v43, 2);
            return CNetMsg::_CNetMsg((int)&v48, 2);
        }
        CNetMsg::CNetMsg((int)&v34);
        ItemDropMsg((int)&v34, a1, v41);
        CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v34, a1, 1, 4);
        *(_DWORD *)(v41 + 216) = *(_DWORD *)(a1 + 4);
        ItemMixRepMsg((int)&v48, 3);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v48);
        CNetMsg::_CNetMsg((int)&v34, 2);
    }
    if(*(_DWORD *)(a1 + 768))
        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v43);
    v12 = *(_DWORD *)(v41 + 168);
    v13 = CItem::Count(v41);
    v14 = *(_DWORD *)(v41 + 40);
    v15 = *(_DWORD *)(v41 + 36);
    v16 = (const char *)(v41 + 44);
    v17 = (const char *)(*(_DWORD *)(v41 + 20) + 12);
    init((int)&v34, (int)"ITEM_MIX", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
    v18 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v34);
    v19 = (int)CLogBuffer::__ls(v18, v17);
    v20 = CLogBuffer::__ls(v19, (int (__cdecl *)(_DWORD))delim);
    v21 = (int)CLogBuffer::__ls((const char *)v20, v16);
    v22 = CLogBuffer::__ls(v21, (int (__cdecl *)(_DWORD))delim);
    v23 = (int)CLogBuffer::__ls((char *)v22, v15);
    v24 = CLogBuffer::__ls(v23, (int (__cdecl *)(_DWORD))delim);
    v25 = (int)CLogBuffer::__ls((char *)v24, v14);
    v26 = CLogBuffer::__ls(v25, (int (__cdecl *)(_DWORD))delim);
    v27 = (int)CLogBuffer::__ls((char *)v26, v13);
    v28 = CLogBuffer::__ls(v27, (int (__cdecl *)(_DWORD))delim);
    CLogBuffer::__ls((char *)v28, v12);
    for(i = 0; i < *(_DWORD *)(v41 + 168); ++i)
    {
        if(*(_DWORD *)(20 * i + v41 + 68))
        {
            v29 = *(_DWORD *)(20 * i + v41 + 76);
            v30 = *(_DWORD *)(20 * i + v41 + 72);
            v31 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
            v32 = (int)CLogBuffer::__ls((char *)v31, v30);
            v33 = CLogBuffer::__ls(v32, (int (__cdecl *)(_DWORD))delim);
            CLogBuffer::__ls((char *)v33, v29);
        }
    }
    CLogBuffer::__ls((int)g_gamelogbuffer, end);
    ItemMixRepMsg((int)&v48, 3);
    if(*(_DWORD *)(a1 + 768))
        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v48);
    CPC::SaveNow(a1, 0);
    CNetMsg::_CNetMsg((int)&v43, 2);
    return CNetMsg::_CNetMsg((int)&v48, 2);
}
// 8049A5C: using guessed type int __cdecl __builtin_vec_new(_DWORD);
// 8049B2C: using guessed type int __cdecl __builtin_vec_delete(_DWORD);
// 80B2BB0: using guessed type char var_C[4];
// 80B2BB0: using guessed type char var_8[5];
// 80B2BB0: using guessed type char var_34[12];

//----- (080B39A0) --------------------------------------------------------
#error "80B45FC: positive sp value has been found (funcsize=977)"
*/
