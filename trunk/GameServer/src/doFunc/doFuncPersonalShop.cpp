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

void do_PersonalShop(CPC *a1, CNetMsg &a2)
{
    /* TODO */
}

/*void do_PersonalShop(CPC *a1, CNetMsg &a2)
{
    int result; // eax@1
    unsigned __int8 dest; // [sp+17h] [bp-1h]@1

    CNetMsg::MoveFirst(a2);
    dest = -1;
    CNetMsg::__rs(a2, &dest);
    result = dest;
    if(dest == 2)
    {
        result = do_PersonalShopSellStart(a1, a2);
    }
    else
    {
        if((signed int)dest > 2)
        {
            if(dest == 3)
            {
                result = do_PersonalShopSellList(a1, a2);
            }
            else
            {
                if(dest == 4)
                    result = do_PersonalShopBuy(a1, a2);
            }
        }
        else
        {
            if(dest == 1)
                result = do_PersonalShopChange(a1, a2);
        }
    }
    return result;
}

void do_PersonalShopSellStart(CPC *a1, CNetMsg &a2)
{
    int result; // eax@1
    int v3; // eax@22
    int v4; // eax@22
    int v5; // ebx@39
    int v6; // eax@41
    int v7; // eax@41
    int v8; // eax@41
    int v9; // eax@41
    int v10; // eax@41
    __int64 v11; // qax@48
    int v12; // eax@67
    int v13; // eax@77
    int v14; // eax@77
    int v15; // eax@77
    int v16; // eax@77
    __int64 v17; // qax@84
    signed int v18; // ST68_4@102
    const char *v19; // eax@102
    int v20; // eax@102
    int v21; // eax@102
    int v22; // eax@102
    int v23; // eax@102
    char v24; // al@103
    signed int v25; // ST70_4@104
    signed int v26; // ST58_4@104
    signed int v27; // ST40_4@104
    const char *v28; // ST28_4@104
    const char *v29; // ST10_4@104
    int v30; // eax@104
    int v31; // eax@104
    int v32; // eax@104
    int v33; // eax@104
    int v34; // eax@104
    int v35; // eax@104
    int v36; // eax@104
    int v37; // eax@104
    int v38; // eax@104
    signed int v39; // ST80_4@109
    signed int v40; // ST68_4@109
    int v41; // eax@109
    int v42; // eax@109
    int v43; // eax@109
    signed int v44; // ST70_4@107
    signed int v45; // ST58_4@107
    int v46; // eax@107
    int v47; // eax@107
    int v48; // eax@107
    __int64 v49; // ST70_8@112
    int v50; // eax@112
    int v51; // eax@112
    int v52; // eax@112
    char v53; // al@113
    signed int v54; // ST70_4@114
    signed int v55; // ST58_4@114
    signed int v56; // ST40_4@114
    const char *v57; // ST28_4@114
    const char *v58; // ST10_4@114
    int v59; // eax@114
    int v60; // eax@114
    int v61; // eax@114
    int v62; // eax@114
    int v63; // eax@114
    int v64; // eax@114
    int v65; // eax@114
    int v66; // eax@114
    int v67; // eax@114
    signed int v68; // ST80_4@119
    signed int v69; // ST68_4@119
    int v70; // eax@119
    int v71; // eax@119
    int v72; // eax@119
    __int64 v73; // ST70_8@117
    int v74; // eax@117
    int v75; // [sp+10h] [bp-C8h]@102
    int k; // [sp+20h] [bp-B8h]@81
    char v77; // [sp+27h] [bp-B1h]@77
    int j; // [sp+28h] [bp-B0h]@45
    int v79; // [sp+2Ch] [bp-ACh]@41
    int v80; // [sp+30h] [bp-A8h]@41
    __int64 dest; // [sp+34h] [bp-A4h]@41
    int v82; // [sp+3Ch] [bp-9Ch]@41
    int v83; // [sp+40h] [bp-98h]@41
    char v84; // [sp+46h] [bp-92h]@41
    char v85; // [sp+47h] [bp-91h]@41
    int i; // [sp+48h] [bp-90h]@39
    int v87; // [sp+4Ch] [bp-8Ch]@39
    char v88; // [sp+53h] [bp-85h]@29
    char src; // [sp+54h] [bp-84h]@22
    char s; // [sp+55h] [bp-83h]@22
    char v91; // [sp+BFh] [bp-19h]@22
    int v92; // [sp+C0h] [bp-18h]@22
    char v93; // [sp+C4h] [bp-14h]@3

    result = a1;
    if(!*(_DWORD *)(a1 + 412))
        return result;
    if((unsigned __int8)CArea::GetAttr(
                                                    *(_DWORD *)(a1 + 412),
                                                    *(_BYTE *)(a1 + 136),
                                                    *(float *)(a1 + 120),
                                                    *(float *)(a1 + 124)) != 10)
    {
        CNetMsg::CNetMsg((int)&v93);
        PersonalShopErrorMsg((int)&v93, 7);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v93);
        return CNetMsg::_CNetMsg((int)&v93, 2);
    }
    if(*(_DWORD *)(a1 + 1324))
    {
        CNetMsg::CNetMsg((int)&v93);
        PersonalShopErrorMsg((int)&v93, 3);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v93);
        return CNetMsg::_CNetMsg((int)&v93, 2);
    }
    if(CPC::IsSetPlayerState(a1, 4))
    {
        CNetMsg::CNetMsg((int)&v93);
        PersonalShopErrorMsg((int)&v93, 3);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v93);
        return CNetMsg::_CNetMsg((int)&v93, 2);
    }
    if(*(_DWORD *)(a1 + 424))
    {
        CNetMsg::CNetMsg((int)&v93);
        PersonalShopErrorMsg((int)&v93, 1);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v93);
        return CNetMsg::_CNetMsg((int)&v93, 2);
    }
    if(*(_DWORD *)(a1 + 1328))
    {
        CNetMsg::CNetMsg((int)&v93);
        PersonalShopErrorMsg((int)&v93, 4);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v93);
        return CNetMsg::_CNetMsg((int)&v93, 2);
    }
    v92 = -1;
    v91 = -1;
    src = byte_80D3631;
    memset(&s, 0, 0x64u);
    g_buf[0] = 0;
    v3 = CNetMsg::__rs(a2, &v92);
    v4 = CNetMsg::__rs(v3, &v91);
    CNetMsg::__rs(v4, g_buf);
    TrimString(g_buf);
    if(v92 <= 0 || v91 < 0 || !(v91 & 1) || strlen(g_buf) > 0x64)
    {
        CNetMsg::CNetMsg((int)&v93);
        PersonalShopErrorMsg((int)&v93, 6);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v93);
        return CNetMsg::_CNetMsg((int)&v93, 2);
    }
    strcpy(&src, g_buf);
    v88 = -1;
    CNetMsg::__rs(a2, &v88);
    if(v88 < 0 || v88 > 10)
    {
        CNetMsg::CNetMsg((int)&v93);
        PersonalShopErrorMsg((int)&v93, 6);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v93);
        return CNetMsg::_CNetMsg((int)&v93, 2);
    }
    if(!v88 && !(v91 & 8))
    {
        CNetMsg::CNetMsg((int)&v93);
        PersonalShopErrorMsg((int)&v93, 6);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v93);
        return CNetMsg::_CNetMsg((int)&v93, 2);
    }
    v5 = __builtin_new(372);
    v87 = CPersonalShop::CPersonalShop(v5, v91, &src);
    for(i = 0; i < v88; ++i)
    {
        v85 = -1;
        v84 = -1;
        v83 = -1;
        v82 = -1;
        dest = -1LL;
        v79 = -1;
        v80 = -1;
        v6 = CNetMsg::__rs(a2, &v85);
        v7 = CNetMsg::__rs(v6, &v84);
        v8 = CNetMsg::__rs(v7, &v83);
        v9 = CNetMsg::__rs(v8, &v82);
        v10 = CNetMsg::__rs(v9, &dest);
        CNetMsg::__rs(v10, &v79);
        if(v82 == *unk_8104584)
        {
            __builtin_delete(v87);
            CNetMsg::CNetMsg((int)&v93);
            PersonalShopErrorMsg((int)&v93, 5);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v93);
            return CNetMsg::_CNetMsg((int)&v93, 2);
        }
        j = CInventory::GetItem(a1 + 792, v85, v84);
        if(!j
            || *(_DWORD *)(j + 24) != v83
            || *(_DWORD *)(j + 28) != v82
            || (v11 = CItem::Count(j), dest > v11)
            || v80 <= 0 && (v80 || !v79)
            || !(*(_DWORD *)(*(_DWORD *)(j + 20) + 68) & 8)
            || *(_BYTE *)(j + 32) != -1)
        {
            __builtin_delete(v87);
            CNetMsg::CNetMsg((int)&v93);
            PersonalShopErrorMsg((int)&v93, 6);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v93);
            return CNetMsg::_CNetMsg((int)&v93, 2);
        }
        if(CPersonalShop::FindItem(v87, 1, v83) != -1)
        {
            __builtin_delete(v87);
            CNetMsg::CNetMsg((int)&v93);
            PersonalShopErrorMsg((int)&v93, 8);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v93);
            return CNetMsg::_CNetMsg((int)&v93, 2);
        }
        if(!CPersonalShop::AddItem(v87, 1, v83, dest, SHIDWORD(dest), v79, v80))
        {
            __builtin_delete(v87);
            CNetMsg::CNetMsg((int)&v93);
            PersonalShopErrorMsg((int)&v93, 6);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v93);
            return CNetMsg::_CNetMsg((int)&v93, 2);
        }
    }
    if(v91 & 8)
    {
        v79 = -1;
        v80 = -1;
        v84 = -1;
        v12 = CNetMsg::__rs(a2, &v79);
        CNetMsg::__rs(v12, &v84);
        if(v80 <= 0 && (v80 || !v79) || v84 <= 0 || v84 > 5)
        {
            __builtin_delete(v87);
            CNetMsg::CNetMsg((int)&v93);
            PersonalShopErrorMsg((int)&v93, 6);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v93);
            return CNetMsg::_CNetMsg((int)&v93, 2);
        }
        for(j = 0; j < v84; ++j)
        {
            v85 = -1;
            v77 = -1;
            v82 = -1;
            v83 = -1;
            dest = -1LL;
            v13 = CNetMsg::__rs(a2, &v85);
            v14 = CNetMsg::__rs(v13, &v77);
            v15 = CNetMsg::__rs(v14, &v82);
            v16 = CNetMsg::__rs(v15, &v83);
            CNetMsg::__rs(v16, &dest);
            if(v83 == *unk_8104584)
            {
                __builtin_delete(v87);
                CNetMsg::CNetMsg((int)&v93);
                PersonalShopErrorMsg((int)&v93, 5);
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v93);
                return CNetMsg::_CNetMsg((int)&v93, 2);
            }
            k = CInventory::GetItem(a1 + 792, v85, v77);
            if(!k
                || *(_DWORD *)(k + 24) != v82
                || *(_DWORD *)(k + 28) != v83
                || (v17 = CItem::Count(k), dest > v17)
                || !(*(_DWORD *)(*(_DWORD *)(k + 20) + 68) & 8))
            {
                __builtin_delete(v87);
                CNetMsg::CNetMsg((int)&v93);
                PersonalShopErrorMsg((int)&v93, 6);
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v93);
                return CNetMsg::_CNetMsg((int)&v93, 2);
            }
            if(CPersonalShop::FindItem(v87, 1, v82) != -1)
            {
                __builtin_delete(v87);
                CNetMsg::CNetMsg((int)&v93);
                PersonalShopErrorMsg((int)&v93, 8);
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v93);
                return CNetMsg::_CNetMsg((int)&v93, 2);
            }
            if(CPersonalShop::FindItem(v87, 0, v82) != -1)
            {
                __builtin_delete(v87);
                CNetMsg::CNetMsg((int)&v93);
                PersonalShopErrorMsg((int)&v93, 8);
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v93);
                return CNetMsg::_CNetMsg((int)&v93, 2);
            }
            if(!CPersonalShop::AddItem(v87, 0, v82, dest, SHIDWORD(dest), v79, v80))
            {
                __builtin_delete(v87);
                CNetMsg::CNetMsg((int)&v93);
                PersonalShopErrorMsg((int)&v93, 6);
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v93);
                return CNetMsg::_CNetMsg((int)&v93, 2);
            }
        }
    }
    *(_DWORD *)(a1 + 1328) = v87;
    CNetMsg::CNetMsg((int)&v93);
    PersonalShopSellStartMsg((int)&v93, a1);
    CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v93, a1, 1, 4);
    v18 = (char)CPersonalShop::GetType(v87);
    init((int)&v75, (int)"PERSONAL SHOP START", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
    v19 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v75);
    v20 = (int)CLogBuffer::__ls(v19, "TYPE");
    v21 = CLogBuffer::__ls(v20, (int (__cdecl *)(_DWORD))delim);
    v22 = (int)CLogBuffer::__ls((char *)v21, v18);
    v23 = CLogBuffer::__ls(v22, (int (__cdecl *)(_DWORD))delim);
    CLogBuffer::__ls((const char *)v23, "ITEMS");
    j = -1;
    for(i = 0; ; ++i)
    {
        v24 = CPersonalShop::GetNormalCount(v87);
        if(i >= v24)
            break;
        j = CPersonalShop::GetNextNormalItem(v87, j);
        v82 = CPersonalShop::GetNormalItemIndex(v87, j);
        v83 = CInventory::GetItem(a1 + 792, v82);
        v25 = *(_DWORD *)(v83 + 168);
        v26 = *(_DWORD *)(v83 + 40);
        v27 = *(_DWORD *)(v83 + 36);
        v28 = (const char *)(v83 + 44);
        v29 = (const char *)(*(_DWORD *)(v83 + 20) + 12);
        v30 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
        v31 = (int)CLogBuffer::__ls((const char *)v30, v29);
        v32 = CLogBuffer::__ls(v31, (int (__cdecl *)(_DWORD))delim);
        v33 = (int)CLogBuffer::__ls((const char *)v32, v28);
        v34 = CLogBuffer::__ls(v33, (int (__cdecl *)(_DWORD))delim);
        v35 = (int)CLogBuffer::__ls((char *)v34, v27);
        v36 = CLogBuffer::__ls(v35, (int (__cdecl *)(_DWORD))delim);
        v37 = (int)CLogBuffer::__ls((char *)v36, v26);
        v38 = CLogBuffer::__ls(v37, (int (__cdecl *)(_DWORD))delim);
        CLogBuffer::__ls((char *)v38, v25);
        for(k = 0; *(_DWORD *)(v83 + 168) > 0 && k <= 4; ++k)
        {
            if(*(_DWORD *)(20 * k + v83 + 68))
            {
                v39 = *(_DWORD *)(20 * k + v83 + 76);
                v40 = *(_DWORD *)(20 * k + v83 + 72);
                v41 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
                v42 = (int)CLogBuffer::__ls((char *)v41, v40);
                v43 = CLogBuffer::__ls(v42, (int (__cdecl *)(_DWORD))delim);
                CLogBuffer::__ls((char *)v43, v39);
            }
        }
        v44 = CPersonalShop::GetNormalItemPrice(v87, j);
        v45 = CPersonalShop::GetNormalItemCount(v87, j);
        v46 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
        v47 = (int)CLogBuffer::__ls((char *)v46, v45);
        v48 = CLogBuffer::__ls(v47, (int (__cdecl *)(_DWORD))delim);
        CLogBuffer::__ls((char *)v48, v44);
    }
    if(CPersonalShop::GetType(v87) & 8)
    {
        v49 = CPersonalShop::GetPackagePrice(v87);
        v50 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
        v51 = (int)CLogBuffer::__ls((const char *)v50, "PACKAGE");
        v52 = CLogBuffer::__ls(v51, (int (__cdecl *)(_DWORD))delim);
        CLogBuffer::__ls((char *)v52, v49);
        j = -1;
        for(i = 0; ; ++i)
        {
            v53 = CPersonalShop::GetPackageCount(v87);
            if(i >= v53)
                break;
            j = CPersonalShop::GetNextPackageItem(v87, j);
            v82 = CPersonalShop::GetPackageItemIndex(v87, j);
            v83 = CInventory::GetItem(a1 + 792, v82);
            v54 = *(_DWORD *)(v83 + 168);
            v55 = *(_DWORD *)(v83 + 40);
            v56 = *(_DWORD *)(v83 + 36);
            v57 = (const char *)(v83 + 44);
            v58 = (const char *)(*(_DWORD *)(v83 + 20) + 12);
            v59 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
            v60 = (int)CLogBuffer::__ls((const char *)v59, v58);
            v61 = CLogBuffer::__ls(v60, (int (__cdecl *)(_DWORD))delim);
            v62 = (int)CLogBuffer::__ls((const char *)v61, v57);
            v63 = CLogBuffer::__ls(v62, (int (__cdecl *)(_DWORD))delim);
            v64 = (int)CLogBuffer::__ls((char *)v63, v56);
            v65 = CLogBuffer::__ls(v64, (int (__cdecl *)(_DWORD))delim);
            v66 = (int)CLogBuffer::__ls((char *)v65, v55);
            v67 = CLogBuffer::__ls(v66, (int (__cdecl *)(_DWORD))delim);
            CLogBuffer::__ls((char *)v67, v54);
            for(k = 0; *(_DWORD *)(v83 + 168) > 0 && k <= 4; ++k)
            {
                if(*(_DWORD *)(20 * k + v83 + 68))
                {
                    v68 = *(_DWORD *)(20 * k + v83 + 76);
                    v69 = *(_DWORD *)(20 * k + v83 + 72);
                    v70 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
                    v71 = (int)CLogBuffer::__ls((char *)v70, v69);
                    v72 = CLogBuffer::__ls(v71, (int (__cdecl *)(_DWORD))delim);
                    CLogBuffer::__ls((char *)v72, v68);
                }
            }
            v73 = CPersonalShop::GetPackageItemCount(v87, j);
            v74 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
            CLogBuffer::__ls((char *)v74, v73);
        }
    }
    CLogBuffer::__ls((int)g_gamelogbuffer, end);
    return CNetMsg::_CNetMsg((int)&v93, 2);
}

void do_PersonalShopSellList(CPC *a1, CNetMsg &a2)
{
    int result; // eax@1
    int v3; // [sp+Ch] [bp-1Ch]@6
    int dest; // [sp+10h] [bp-18h]@6
    char v5; // [sp+14h] [bp-14h]@3

    result = a1;
    if(*(_DWORD *)(a1 + 412))
    {
        if(*(_DWORD *)(a1 + 1328))
        {
            CNetMsg::CNetMsg((int)&v5);
            PersonalShopErrorMsg((int)&v5, 4);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v5);
            result = CNetMsg::_CNetMsg((int)&v5, 2);
        }
        else
        {
            dest = -1;
            CNetMsg::__rs(a2, &dest);
            v3 = CArea::FindCharInCell(*(_DWORD *)(a1 + 412), a1, dest, 0, 0);
            if(v3)
            {
                if(*(_DWORD *)(v3 + 1328) && CPersonalShop::GetType(*(_DWORD *)(v3 + 1328)) & 1)
                {
                    CNetMsg::CNetMsg((int)&v5);
                    PersonalShopSellListMsg((int)&v5, v3);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v5);
                    result = CNetMsg::_CNetMsg((int)&v5, 2);
                }
                else
                {
                    CNetMsg::CNetMsg((int)&v5);
                    PersonalShopErrorMsg((int)&v5, 10);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v5);
                    result = CNetMsg::_CNetMsg((int)&v5, 2);
                }
            }
            else
            {
                CNetMsg::CNetMsg((int)&v5);
                PersonalShopErrorMsg((int)&v5, 9);
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v5);
                result = CNetMsg::_CNetMsg((int)&v5, 2);
            }
        }
    }
    return result;
}

void do_PersonalShopChange(CPC *a1, CNetMsg &a2)
{
    int result; // eax@1
    int v3; // eax@14
    char v4; // [sp+Fh] [bp-19h]@14
    int dest; // [sp+10h] [bp-18h]@14
    char v6; // [sp+14h] [bp-14h]@3

    result = a1;
    if(*(_DWORD *)(a1 + 412))
    {
        if(*(_DWORD *)(a1 + 1324))
        {
            CNetMsg::CNetMsg((int)&v6);
            PersonalShopErrorMsg((int)&v6, 3);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v6);
            result = CNetMsg::_CNetMsg((int)&v6, 2);
        }
        else
        {
            if(CPC::IsSetPlayerState(a1, 4))
            {
                CNetMsg::CNetMsg((int)&v6);
                PersonalShopErrorMsg((int)&v6, 3);
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v6);
                result = CNetMsg::_CNetMsg((int)&v6, 2);
            }
            else
            {
                if(*(_DWORD *)(a1 + 424))
                {
                    CNetMsg::CNetMsg((int)&v6);
                    PersonalShopErrorMsg((int)&v6, 1);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v6);
                    result = CNetMsg::_CNetMsg((int)&v6, 2);
                }
                else
                {
                    dest = -1;
                    v4 = -1;
                    v3 = CNetMsg::__rs(a2, &dest);
                    result = CNetMsg::__rs(v3, &v4);
                    if(!v4)
                    {
                        result = a1;
                        if(*(_DWORD *)(a1 + 1328))
                        {
                            if(*(_DWORD *)(a1 + 4) == dest)
                            {
                                __builtin_delete(*(_DWORD *)(a1 + 1328));
                                *(_DWORD *)(a1 + 1328) = 0;
                                CNetMsg::CNetMsg((int)&v6);
                                PersonalShopChangeMsg((int)&v6, a1);
                                CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v6, a1, 1, 4);
                                result = CNetMsg::_CNetMsg((int)&v6, 2);
                            }
                            else
                            {
                                CNetMsg::CNetMsg((int)&v6);
                                PersonalShopErrorMsg((int)&v6, 6);
                                if(*(_DWORD *)(a1 + 768))
                                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v6);
                                result = CNetMsg::_CNetMsg((int)&v6, 2);
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}

void do_PersonalShopBuy(CPC *a1, CNetMsg &a2)
{
    int result; // eax@1
    int v3; // eax@6
    __int64 v4; // qax@22
    __int64 v5; // ST64_8@32
    __int64 v6; // ST5C_8@32
    int v7; // eax@32
    char v8; // al@39
    int v9; // eax@45
    signed int v10; // eax@49
    signed int v11; // esi@53
    __int64 v12; // ST9C_8@53
    __int64 v13; // qax@55
    int v14; // eax@63
    signed int v15; // eax@64
    int v16; // ST68_4@64
    int v17; // ST64_4@64
    __int64 v18; // ST5C_8@64
    int v19; // eax@64
    signed int v20; // esi@71
    signed int v21; // eax@75
    __int64 v22; // kr00_8@85
    int v23; // eax@89
    int v24; // eax@93
    const char *v25; // ST44_4@98
    const char *v26; // ST24_4@98
    int v27; // eax@98
    int v28; // eax@98
    int v29; // eax@98
    int v30; // eax@98
    int v31; // eax@98
    int v32; // eax@99
    int v33; // eax@100
    signed __int64 v34; // ST68_8@101
    int v35; // eax@101
    int v36; // eax@101
    int v37; // eax@101
    __int64 v38; // qax@103
    signed int v39; // ST74_4@125
    signed int v40; // ST5C_4@125
    signed int v41; // ST44_4@125
    const char *v42; // ST14_4@125
    int v43; // eax@125
    int v44; // eax@125
    int v45; // eax@125
    int v46; // eax@125
    int v47; // eax@125
    int v48; // eax@125
    int v49; // eax@125
    int v50; // eax@125
    int v51; // eax@125
    signed int v52; // ST74_4@130
    signed int v53; // ST5C_4@130
    int v54; // eax@130
    int v55; // eax@130
    int v56; // eax@130
    signed __int64 v57; // ST74_8@128
    int v58; // eax@128
    __int64 v59; // qax@134
    signed int v60; // ST74_4@156
    signed int v61; // ST5C_4@156
    signed int v62; // ST44_4@156
    const char *v63; // ST2C_4@156
    const char *v64; // ST14_4@156
    int v65; // eax@156
    int v66; // eax@156
    int v67; // eax@156
    int v68; // eax@156
    int v69; // eax@156
    int v70; // eax@156
    int v71; // eax@156
    int v72; // eax@156
    int v73; // eax@156
    signed int v74; // ST74_4@161
    signed int v75; // ST5C_4@161
    int v76; // eax@161
    int v77; // eax@161
    int v78; // eax@161
    signed __int64 v79; // ST74_8@159
    int v80; // eax@159
    __int64 v81; // qax@163
    signed int v82; // eax@171
    signed __int64 v83; // ST9C_8@174
    signed __int64 v84; // ST9C_8@174
    signed __int64 v85; // ST9C_8@177
    char v86; // al@182
    char v87; // [sp+2Ch] [bp-1FCh]@183
    int l; // [sp+40h] [bp-1E8h]@125
    int v89; // [sp+44h] [bp-1E4h]@104
    int v90; // [sp+48h] [bp-1E0h]@76
    int v91; // [sp+4Ch] [bp-1DCh]@76
    int v92; // [sp+50h] [bp-1D8h]@67
    int m; // [sp+54h] [bp-1D4h]@67
    int k; // [sp+58h] [bp-1D0h]@65
    int v95; // [sp+5Ch] [bp-1CCh]@63
    int v96; // [sp+6Ch] [bp-1BCh]@45
    __int64 dest; // [sp+70h] [bp-1B8h]@45
    char v98; // [sp+7Bh] [bp-1ADh]@33
    int j; // [sp+7Ch] [bp-1ACh]@26
    int i; // [sp+80h] [bp-1A8h]@26
    int v101; // [sp+84h] [bp-1A4h]@15
    char v102; // [sp+1FBh] [bp-2Dh]@15
    int v103; // [sp+1FCh] [bp-2Ch]@15
    int v104; // [sp+200h] [bp-28h]@6
    char v105; // [sp+207h] [bp-21h]@6
    int v106; // [sp+208h] [bp-20h]@6
    __int64 v107; // [sp+20Ch] [bp-1Ch]@6
    int v108; // [sp+214h] [bp-14h]@3

    result = a1;
    if(!*(_DWORD *)(a1 + 412))
        return result;
    if(*(_DWORD *)(a1 + 1328))
    {
        CNetMsg::CNetMsg((int)&v108);
        PersonalShopErrorMsg((int)&v108, 4);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
        return CNetMsg::_CNetMsg((int)&v108, 2);
    }
    v107 = 0LL;
    v106 = -1;
    v105 = -1;
    v3 = CNetMsg::__rs(a2, &v106);
    CNetMsg::__rs(v3, &v105);
    v104 = CArea::FindCharInCell(*(_DWORD *)(a1 + 412), a1, v106, 0, 0);
    if(!v104)
    {
        CNetMsg::CNetMsg((int)&v108);
        PersonalShopErrorMsg((int)&v108, 9);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
        return CNetMsg::_CNetMsg((int)&v108, 2);
    }
    if(!*(_DWORD *)(v104 + 1328) || !(CPersonalShop::GetType(*(_DWORD *)(v104 + 1328)) & 1))
    {
        CNetMsg::CNetMsg((int)&v108);
        PersonalShopErrorMsg((int)&v108, 10);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
        return CNetMsg::_CNetMsg((int)&v108, 2);
    }
    v103 = *(_DWORD *)(v104 + 1328);
    v102 = CPersonalShop::GetType(v103);
    CPersonalShop::CPersonalShop((int)&v101, v102, &byte_80D3630);
    if(v105)
    {
        if(!(v102 & 8))
        {
            CNetMsg::CNetMsg((int)&v108);
            PersonalShopErrorMsg((int)&v108, 11);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
            return CNetMsg::_CNetMsg((int)&v108, 2);
        }
        v107 = CPersonalShop::GetPackagePrice(v103);
        if(SHIDWORD(v107) < 0 || !*(_DWORD *)(a1 + 1280) || (v4 = CItem::Count(*(_DWORD *)(a1 + 1280)), v107 > v4))
        {
            CNetMsg::CNetMsg((int)&v108);
            PersonalShopErrorMsg((int)&v108, 12);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
            return CNetMsg::_CNetMsg((int)&v108, 2);
        }
        j = -1;
        for(i = 0; i < (char)CPersonalShop::GetPackageCount(v103); ++i)
        {
            j = CPersonalShop::GetNextPackageItem(v103, j);
            if(j == -1)
            {
                CNetMsg::CNetMsg((int)&v108);
                PersonalShopErrorMsg((int)&v108, 6);
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                return CNetMsg::_CNetMsg((int)&v108, 2);
            }
            v5 = CPersonalShop::GetPackagePrice(v103);
            v6 = CPersonalShop::GetPackageItemCount(v103, j);
            v7 = CPersonalShop::GetPackageItemIndex(v103, j);
            CPersonalShop::AddItem((int)&v101, 0, v7, v6, SHIDWORD(v6), v5, SHIDWORD(v5));
        }
    }
    v98 = -1;
    CNetMsg::__rs(a2, &v98);
    if(v98 || v105)
    {
        if(v98 >= 0 && (v8 = CPersonalShop::GetNormalCount(v103), v98 <= v8))
        {
            for(j = 0; j < v98; ++j)
            {
                i = -1;
                dest = -1LL;
                v9 = CNetMsg::__rs(a2, &i);
                CNetMsg::__rs(v9, &dest);
                v96 = CPersonalShop::FindItem(v103, 1, i);
                if(v96 == -1)
                {
                    CNetMsg::CNetMsg((int)&v108);
                    PersonalShopErrorMsg((int)&v108, 6);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                    return CNetMsg::_CNetMsg((int)&v108, 2);
                }
                v10 = CPersonalShop::GetNormalItemCount(v103, v96);
                if(dest > v10)
                {
                    CNetMsg::CNetMsg((int)&v108);
                    PersonalShopErrorMsg((int)&v108, 13);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                    return CNetMsg::_CNetMsg((int)&v108, 2);
                }
                v11 = CPersonalShop::GetNormalItemPrice(v103, v96);
                HIDWORD(v12) = (v11 >> 31) * dest
                                         + HIDWORD(dest) * v11
                                         + ((unsigned int)dest * (unsigned __int64)(unsigned int)v11 >> 32);
                LODWORD(v12) = dest * v11;
                v107 += v12;
                if(SHIDWORD(v107) < 0 || !*(_DWORD *)(a1 + 1280) || (v13 = CItem::Count(*(_DWORD *)(a1 + 1280)), v107 > v13))
                {
                    CNetMsg::CNetMsg((int)&v108);
                    PersonalShopErrorMsg((int)&v108, 12);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                    return CNetMsg::_CNetMsg((int)&v108, 2);
                }
                if(CPersonalShop::FindItem((int)&v101, 1, i) != -1 || CPersonalShop::FindItem((int)&v101, 0, i) != -1)
                {
                    CNetMsg::CNetMsg((int)&v108);
                    PersonalShopErrorMsg((int)&v108, 12);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                    init((int)&v95, (int)"HACK PERSONAL SHOP BUY", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
                    v14 = (int)CLogBuffer::__ls(g_gamelogbuffer, (int)&v95);
                    CLogBuffer::__ls(v14, end);
                    return CNetMsg::_CNetMsg((int)&v108, 2);
                }
                v15 = CPersonalShop::GetNormalItemPrice(v103, v96);
                v16 = v15 >> 31;
                v17 = v15;
                v18 = dest;
                v19 = CPersonalShop::GetNormalItemIndex(v103, v96);
                CPersonalShop::AddItem((int)&v101, 1, v19, v18, SHIDWORD(v18), v17, v16);
            }
            v96 = 0;
            i = 0;
            for(k = CPersonalShop::GetNextNormalItem((int)&v101, -1);
                        k != -1;
                        k = CPersonalShop::GetNextNormalItem((int)&v101, k))
            {
                m = CPersonalShop::GetNormalItemIndex((int)&v101, k);
                v92 = CInventory::GetItem(v104 + 792, m);
                if(!v92)
                {
                    CNetMsg::CNetMsg((int)&v108);
                    PersonalShopErrorMsg((int)&v108, 6);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                    return CNetMsg::_CNetMsg((int)&v108, 2);
                }
                v20 = CPersonalShop::GetNormalItemCount((int)&v101, k);
                if(v20 > CItem::Count(v92))
                {
                    CNetMsg::CNetMsg((int)&v108);
                    PersonalShopErrorMsg((int)&v108, 6);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                    return CNetMsg::_CNetMsg((int)&v108, 2);
                }
                v21 = CPersonalShop::GetNormalItemCount((int)&v101, k);
                v96 += *(_DWORD *)(*(_DWORD *)(v92 + 20) + 96) * v21;
                if((*(_BYTE *)(*(_DWORD *)(v92 + 20) + 68) ^ 1) & 1
                    || !CInventory::FindItem(
                                a1 + 792,
                                (int)&v91,
                                (int)&v90,
                                *(_DWORD *)(v92 + 28),
                                *(_DWORD *)(v92 + 36),
                                *(_DWORD *)(v92 + 40)))
                    ++i;
            }
            for(k = CPersonalShop::GetNextPackageItem((int)&v101, -1);
                        k != -1;
                        k = CPersonalShop::GetNextPackageItem((int)&v101, k))
            {
                v90 = CPersonalShop::GetPackageItemIndex((int)&v101, k);
                v91 = CInventory::GetItem(v104 + 792, v90);
                if(!v91)
                {
                    CNetMsg::CNetMsg((int)&v108);
                    PersonalShopErrorMsg((int)&v108, 6);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                    return CNetMsg::_CNetMsg((int)&v108, 2);
                }
                v22 = CPersonalShop::GetPackageItemCount((int)&v101, k);
                if(v22 > CItem::Count(v91))
                {
                    CNetMsg::CNetMsg((int)&v108);
                    PersonalShopErrorMsg((int)&v108, 6);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                    return CNetMsg::_CNetMsg((int)&v108, 2);
                }
                v23 = CPersonalShop::GetPackageItemCount((int)&v101, k);
                v96 += v23 * *(_DWORD *)(*(_DWORD *)(v91 + 20) + 96);
                if((*(_BYTE *)(*(_DWORD *)(v91 + 20) + 68) ^ 1) & 1
                    || !CInventory::FindItem(
                                a1 + 792,
                                (int)&v92,
                                (int)&m,
                                *(_DWORD *)(v91 + 28),
                                *(_DWORD *)(v91 + 36),
                                *(_DWORD *)(v91 + 40)))
                    ++i;
            }
            v24 = CInventory::GetSpace(a1 + 792);
            if(v24 >= i && v96 + *(_DWORD *)(a1 + 724) < 15 * *(_DWORD *)(a1 + 728) / 10)
            {
                init((int)&v95, (int)"PERSONAL SHOP BUY", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
                CLogBuffer::__ls(g_gamelogbuffer, (int)&v95);
                v25 = (const char *)(*(_DWORD *)(v104 + 768) + 4);
                v26 = (const char *)(v104 + 8);
                v27 = (int)CLogBuffer::__ls(g_gamelogbuffer, "SHOP");
                v28 = CLogBuffer::__ls(v27, (int (__cdecl *)(_DWORD))delim);
                v29 = (int)CLogBuffer::__ls((const char *)v28, v26);
                v30 = CLogBuffer::__ls(v29, (int (__cdecl *)(_DWORD))delim);
                v31 = (int)CLogBuffer::__ls((const char *)v30, v25);
                CLogBuffer::__ls(v31, (int (__cdecl *)(_DWORD))delim);
                if(v105)
                {
                    v32 = (int)CLogBuffer::__ls(g_gamelogbuffer, "PACKAGE");
                    CLogBuffer::__ls(v32, (int (__cdecl *)(_DWORD))delim);
                }
                else
                {
                    v33 = (int)CLogBuffer::__ls(g_gamelogbuffer, "NO PACKAGE");
                    CLogBuffer::__ls(v33, (int (__cdecl *)(_DWORD))delim);
                }
                v34 = v107;
                v35 = (int)CLogBuffer::__ls(g_gamelogbuffer, "NEEDMONEY");
                v36 = CLogBuffer::__ls(v35, (int (__cdecl *)(_DWORD))delim);
                v37 = (int)CLogBuffer::__ls((char *)v36, v34);
                CLogBuffer::__ls(v37, (int (__cdecl *)(_DWORD))delim);
                CLogBuffer::__ls(g_gamelogbuffer, "ITEMS");
                k = CPersonalShop::GetNextNormalItem((int)&v101, -1);
                while(k != -1)
                {
                    v90 = CPersonalShop::GetNormalItemIndex((int)&v101, k);
                    dest = CPersonalShop::GetNormalItemCount((int)&v101, k);
                    v91 = CInventory::GetItem(v104 + 792, v90);
                    *(_BYTE *)(v91 + 32) = -1;
                    CNetMsg::CNetMsg((int)&v108);
                    v38 = CItem::Count(v91);
                    if(v38 <= dest)
                    {
                        v89 = v91;
                        ItemDeleteMsg((int)&v108, v91);
                        if(*(_DWORD *)(v104 + 768))
                            CDescriptor::WriteToOutput(*(_DWORD *)(v104 + 768), (int)&v108);
                        CInventory::Remove(v104 + 792, v91, 0, 1);
                        CInventory::AddItem(a1 + 792, v89, a1, 0, 1, -1, -1);
                        if(CItem::tab(v89) >= 0)
                        {
                            ItemAddMsg((int)&v108, v89);
                            if(*(_DWORD *)(a1 + 768))
                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                        }
                        else
                        {
                            if(v89)
                                (*(void (__cdecl **)(int, signed int))(*(_DWORD *)(v89 + 220) + 8))(v89, 3);
                            CInventory::FindItem(
                                a1 + 792,
                                (int)&v92,
                                (int)&m,
                                *(_DWORD *)(v91 + 28),
                                *(_DWORD *)(v91 + 36),
                                *(_DWORD *)(v91 + 40));
                            v89 = CInventory::GetItem(a1 + 792, v92, m);
                            ItemUpdateMsg((int)&v108, v89, dest);
                            if(*(_DWORD *)(a1 + 768))
                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                        }
                    }
                    else
                    {
                        v89 = CItemList::CreateItem(
                                        gserver.Unk41208,
                                        *(_DWORD *)(v91 + 28),
                                        -1,
                                        *(_DWORD *)(v91 + 36),
                                        *(_DWORD *)(v91 + 40),
                                        dest);
                        CInventory::Decrease(v104 + 792, v91, dest);
                        ItemUpdateMsg((int)&v108, v91, -dest);
                        if(*(_DWORD *)(v104 + 768))
                            CDescriptor::WriteToOutput(*(_DWORD *)(v104 + 768), (int)&v108);
                        CInventory::AddItem(a1 + 792, v89, a1, 0, 1, -1, -1);
                        if(CItem::tab(v89) >= 0)
                        {
                            ItemAddMsg((int)&v108, v89);
                            if(*(_DWORD *)(a1 + 768))
                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                        }
                        else
                        {
                            if(v89)
                                (*(void (__cdecl **)(int, signed int))(*(_DWORD *)(v89 + 220) + 8))(v89, 3);
                            CInventory::FindItem(
                                a1 + 792,
                                (int)&v92,
                                (int)&m,
                                *(_DWORD *)(v91 + 28),
                                *(_DWORD *)(v91 + 36),
                                *(_DWORD *)(v91 + 40));
                            v89 = CInventory::GetItem(a1 + 792, v92, m);
                            ItemUpdateMsg((int)&v108, v89, dest);
                            if(*(_DWORD *)(a1 + 768))
                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                        }
                    }
                    v39 = *(_DWORD *)(v89 + 168);
                    v40 = *(_DWORD *)(v89 + 40);
                    v41 = *(_DWORD *)(v89 + 36);
                    v42 = (const char *)(*(_DWORD *)(v89 + 20) + 12);
                    v43 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
                    v44 = (int)CLogBuffer::__ls((const char *)v43, v42);
                    v45 = CLogBuffer::__ls(v44, (int (__cdecl *)(_DWORD))delim);
                    v46 = (int)CLogBuffer::__ls((const char *)v45, (const char *)(v89 + 44));
                    v47 = CLogBuffer::__ls(v46, (int (__cdecl *)(_DWORD))delim);
                    v48 = (int)CLogBuffer::__ls((char *)v47, v41);
                    v49 = CLogBuffer::__ls(v48, (int (__cdecl *)(_DWORD))delim);
                    v50 = (int)CLogBuffer::__ls((char *)v49, v40);
                    v51 = CLogBuffer::__ls(v50, (int (__cdecl *)(_DWORD))delim);
                    CLogBuffer::__ls((char *)v51, v39);
                    for(l = 0; *(_DWORD *)(v89 + 168) > 0 && l <= 4; ++l)
                    {
                        if(*(_DWORD *)(20 * l + v89 + 68))
                        {
                            v52 = *(_DWORD *)(20 * l + v89 + 76);
                            v53 = *(_DWORD *)(20 * l + v89 + 72);
                            v54 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
                            v55 = (int)CLogBuffer::__ls((char *)v54, v53);
                            v56 = CLogBuffer::__ls(v55, (int (__cdecl *)(_DWORD))delim);
                            CLogBuffer::__ls((char *)v56, v52);
                        }
                    }
                    v57 = dest;
                    v58 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
                    CLogBuffer::__ls((char *)v58, v57);
                    CPersonalShop::RemoveNormalItem(v103, v90, dest);
                    k = CPersonalShop::GetNextNormalItem((int)&v101, k);
                    CNetMsg::_CNetMsg((int)&v108, 2);
                }
                k = CPersonalShop::GetNextPackageItem((int)&v101, -1);
                while(k != -1)
                {
                    l = CPersonalShop::GetPackageItemIndex((int)&v101, k);
                    dest = CPersonalShop::GetPackageItemCount((int)&v101, k);
                    v89 = CInventory::GetItem(v104 + 792, l);
                    CNetMsg::CNetMsg((int)&v108);
                    v59 = CItem::Count(v89);
                    if(v59 <= dest)
                    {
                        v92 = v89;
                        ItemDeleteMsg((int)&v108, v89);
                        if(*(_DWORD *)(v104 + 768))
                            CDescriptor::WriteToOutput(*(_DWORD *)(v104 + 768), (int)&v108);
                        CInventory::Remove(v104 + 792, v89, 0, 1);
                        CInventory::AddItem(a1 + 792, v92, a1, 0, 1, -1, -1);
                        if(CItem::tab(v92) >= 0)
                        {
                            ItemAddMsg((int)&v108, v92);
                            if(*(_DWORD *)(a1 + 768))
                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                        }
                        else
                        {
                            if(v92)
                                (*(void (__cdecl **)(int, signed int))(*(_DWORD *)(v92 + 220) + 8))(v92, 3);
                            CInventory::FindItem(
                                a1 + 792,
                                (int)&v90,
                                (int)&v91,
                                *(_DWORD *)(v89 + 28),
                                *(_DWORD *)(v89 + 36),
                                *(_DWORD *)(v89 + 40));
                            v92 = CInventory::GetItem(a1 + 792, v90, v91);
                            ItemUpdateMsg((int)&v108, v92, dest);
                            if(*(_DWORD *)(a1 + 768))
                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                        }
                    }
                    else
                    {
                        v92 = CItemList::CreateItem(
                                        gserver.Unk41208,
                                        *(_DWORD *)(v89 + 28),
                                        -1,
                                        *(_DWORD *)(v89 + 36),
                                        *(_DWORD *)(v89 + 40),
                                        dest);
                        CInventory::Decrease(v104 + 792, v89, dest);
                        ItemUpdateMsg((int)&v108, v89, -dest);
                        if(*(_DWORD *)(v104 + 768))
                            CDescriptor::WriteToOutput(*(_DWORD *)(v104 + 768), (int)&v108);
                        CInventory::AddItem(a1 + 792, v92, a1, 0, 1, -1, -1);
                        if(CItem::tab(v92) >= 0)
                        {
                            ItemAddMsg((int)&v108, v92);
                            if(*(_DWORD *)(a1 + 768))
                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                        }
                        else
                        {
                            if(v92)
                                (*(void (__cdecl **)(int, signed int))(*(_DWORD *)(v92 + 220) + 8))(v92, 3);
                            CInventory::FindItem(
                                a1 + 792,
                                (int)&v90,
                                (int)&v91,
                                *(_DWORD *)(v89 + 28),
                                *(_DWORD *)(v89 + 36),
                                *(_DWORD *)(v89 + 40));
                            v92 = CInventory::GetItem(a1 + 792, v90, v91);
                            ItemUpdateMsg((int)&v108, v92, dest);
                            if(*(_DWORD *)(a1 + 768))
                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                        }
                    }
                    v60 = *(_DWORD *)(v92 + 168);
                    v61 = *(_DWORD *)(v92 + 40);
                    v62 = *(_DWORD *)(v92 + 36);
                    v63 = (const char *)(v92 + 44);
                    v64 = (const char *)(*(_DWORD *)(v92 + 20) + 12);
                    v65 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
                    v66 = (int)CLogBuffer::__ls((const char *)v65, v64);
                    v67 = CLogBuffer::__ls(v66, (int (__cdecl *)(_DWORD))delim);
                    v68 = (int)CLogBuffer::__ls((const char *)v67, v63);
                    v69 = CLogBuffer::__ls(v68, (int (__cdecl *)(_DWORD))delim);
                    v70 = (int)CLogBuffer::__ls((char *)v69, v62);
                    v71 = CLogBuffer::__ls(v70, (int (__cdecl *)(_DWORD))delim);
                    v72 = (int)CLogBuffer::__ls((char *)v71, v61);
                    v73 = CLogBuffer::__ls(v72, (int (__cdecl *)(_DWORD))delim);
                    CLogBuffer::__ls((char *)v73, v60);
                    for(m = 0; *(_DWORD *)(v92 + 168) > 0 && m <= 4; ++m)
                    {
                        if(*(_DWORD *)(20 * m + v92 + 68))
                        {
                            v74 = *(_DWORD *)(20 * m + v92 + 76);
                            v75 = *(_DWORD *)(20 * m + v92 + 72);
                            v76 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
                            v77 = (int)CLogBuffer::__ls((char *)v76, v75);
                            v78 = CLogBuffer::__ls(v77, (int (__cdecl *)(_DWORD))delim);
                            CLogBuffer::__ls((char *)v78, v74);
                        }
                    }
                    v79 = dest;
                    v80 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (__cdecl *)(_DWORD))delim);
                    CLogBuffer::__ls((char *)v80, v79);
                    CPersonalShop::RemovePackage(v103);
                    k = CPersonalShop::GetNextPackageItem((int)&v101, k);
                    CNetMsg::_CNetMsg((int)&v108, 2);
                }
                CLogBuffer::__ls((int)g_gamelogbuffer, end);
                v81 = CItem::Count(*(_DWORD *)(a1 + 1280));
                if(v81 <= v107)
                {
                    CNetMsg::CNetMsg((int)&v108);
                    ItemDeleteMsg((int)&v108, *(_DWORD *)(a1 + 1280));
                    CPC::AddMoney(a1, -v107);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                    CNetMsg::_CNetMsg((int)&v108, 2);
                }
                else
                {
                    CNetMsg::CNetMsg((int)&v108);
                    CPC::AddMoney(a1, -v107);
                    ItemUpdateMsg((int)&v108, *(_DWORD *)(a1 + 1280), -v107);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                    CNetMsg::_CNetMsg((int)&v108, 2);
                }
                if(v102 & 0xC)
                    v82 = 1000;
                else
                    v82 = 0;
                l = v82;
                if(*(_DWORD *)(v104 + 1280))
                {
                    CNetMsg::CNetMsg((int)&v108);
                    v83 = (unsigned int)l * v107;
                    HIDWORD(v83) += (l >> 31) * v107;
                    CPC::AddMoney(v104, v107 - v83 / 10000);
                    v84 = (unsigned int)l * v107;
                    HIDWORD(v84) += (l >> 31) * v107;
                    ItemUpdateMsg((int)&v108, *(_DWORD *)(v104 + 1280), v107 - v84 / 10000);
                    if(*(_DWORD *)(v104 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(v104 + 768), (int)&v108);
                    CNetMsg::_CNetMsg((int)&v108, 2);
                }
                else
                {
                    CNetMsg::CNetMsg((int)&v108);
                    v85 = (unsigned int)l * v107;
                    HIDWORD(v85) += (l >> 31) * v107;
                    CPC::AddMoney(v104, v107 - v85 / 10000);
                    ItemAddMsg((int)&v108, *(_DWORD *)(v104 + 1280));
                    if(*(_DWORD *)(v104 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(v104 + 768), (int)&v108);
                    CNetMsg::_CNetMsg((int)&v108, 2);
                }
                CNetMsg::CNetMsg((int)&v108);
                PersonalShopBuyMsg((int)&v108, a2, a1);
                if(*(_DWORD *)(v104 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(v104 + 768), (int)&v108);
                v86 = CPersonalShop::GetType(v103);
                if(v86 != v102)
                {
                    CNetMsg::CNetMsg((int)&v87);
                    PersonalShopChangeMsg((int)&v87, v104);
                    CArea::SendToCell(*(_DWORD *)(v104 + 412), (int)&v87, v104, 1, 4);
                    if(!(unsigned __int8)CPersonalShop::GetType(v103))
                    {
                        __builtin_delete(v103);
                        *(_DWORD *)(v104 + 1328) = 0;
                    }
                    CNetMsg::_CNetMsg((int)&v87, 2);
                }
                CPC::SaveNow(a1, 0);
                CPC::SaveNow(v104, 0);
                result = CNetMsg::_CNetMsg((int)&v108, 2);
            }
            else
            {
                CNetMsg::CNetMsg((int)&v108);
                PersonalShopErrorMsg((int)&v108, 15);
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                result = CNetMsg::_CNetMsg((int)&v108, 2);
            }
        }
        else
        {
            CNetMsg::CNetMsg((int)&v108);
            PersonalShopErrorMsg((int)&v108, 6);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
            result = CNetMsg::_CNetMsg((int)&v108, 2);
        }
    }
    else
    {
        CNetMsg::CNetMsg((int)&v108);
        PersonalShopErrorMsg((int)&v108, 6);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
        result = CNetMsg::_CNetMsg((int)&v108, 2);
    }
    return result;
}
*/
