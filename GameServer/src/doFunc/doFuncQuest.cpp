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

void do_Quest(CPC *a1, CNetMsg &a2)
{
    /* TODO */
}

/*void do_Quest(CPC *a1, CNetMsg &a2)
{
    signed int result; // eax@1
    char dest; // [sp+17h] [bp-1h]@2

    result = a1;
    if(*(_WORD *)(a1 + 76) > 0)
    {
        CNetMsg::MoveFirst(a2);
        result = CNetMsg::__rs(a2, &dest);
        switch(dest)
        {
            case 1:
                result = do_QuestRequest(a1, a2);
                break;
            case 4:
                result = do_QuestStart(a1, a2);
                break;
            case 8:
                result = do_QuestGiveUp(a1, a2);
                break;
            case 7:
                result = do_QuestPrize(a1, a2);
                break;
            case 5:
                result = do_QuestComplete(a1, a2);
                break;
            default:
                return result;
        }
    }
    return result;
}

signed void do_QuestRequest(CPC *a1, CNetMsg &a2)
{
    int v2; // eax@1
    signed int result; // eax@2
    int v4; // ST28_4@20
    const char *v5; // eax@20
    int v6; // eax@20
    int v7; // eax@20
    int v8; // eax@20
    int v9; // eax@55
    int v10; // [sp+30h] [bp-84h]@96
    int v11; // [sp+44h] [bp-70h]@66
    int v12; // [sp+48h] [bp-6Ch]@62
    int v13; // [sp+4Ch] [bp-68h]@62
    int v14; // [sp+50h] [bp-64h]@61
    int n; // [sp+54h] [bp-60h]@52
    int v16; // [sp+58h] [bp-5Ch]@40
    char v17; // [sp+5Fh] [bp-55h]@33
    int m; // [sp+60h] [bp-54h]@33
    void *v19; // [sp+64h] [bp-50h]@31
    uint32_t src; // [sp+68h] [bp-4Ch]@20
    int l; // [sp+6Ch] [bp-48h]@20
    int v22; // [sp+70h] [bp-44h]@20
    void *s; // [sp+74h] [bp-40h]@20
    int v24; // [sp+78h] [bp-3Ch]@20
    int v25; // [sp+7Ch] [bp-38h]@20
    int j; // [sp+8Ch] [bp-28h]@6
    int i; // [sp+90h] [bp-24h]@1
    int v28; // [sp+94h] [bp-20h]@1
    int v29; // [sp+98h] [bp-1Ch]@1
    int v30; // [sp+9Ch] [bp-18h]@1
    int v31; // [sp+A0h] [bp-14h]@1
    int v32; // [sp+A4h] [bp-10h]@1
    int k; // [sp+A8h] [bp-Ch]@1
    int dest; // [sp+ACh] [bp-8h]@1
    char v35; // [sp+B3h] [bp-1h]@1

    CNetMsg::MoveFirst(a2);
    v2 = CNetMsg::__rs(a2, &v35);
    CNetMsg::__rs(v2, &dest);
    k = 0;
    v32 = 0;
    v31 = *(_DWORD *)(a1 + 140) - 1;
    v30 = *(_DWORD *)(a1 + 140) + 1;
    v29 = *(_DWORD *)(a1 + 144) - 1;
    v28 = *(_DWORD *)(a1 + 144) + 1;
    for(i = v31; ; ++i)
    {
        result = i;
        if(i > v30)
            break;
        if(i >= 0 && i < *(_DWORD *)(*(_DWORD *)(a1 + 412) + 12))
        {
            for(j = v29; j <= v28; ++j)
            {
                if(j >= 0 && j < *(_DWORD *)(*(_DWORD *)(a1 + 412) + 16))
                {
                    for(k = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(a1 + 412) + 28) + 4 * i) + 16 * j);
                                k;
                                k = *(_DWORD *)(k + 404))
                    {
                        if(*(_DWORD *)k == 1 && *(_DWORD *)(k + 468) == dest)
                        {
                            v32 = k;
                            break;
                        }
                    }
                }
            }
        }
    }
    if(v32)
    {
        v4 = dest;
        init((int)&v25, (int)"QUEST REQUEST");
        v5 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v25);
        v6 = (int)CLogBuffer::__ls(v5, (const char *)(a1 + 8));
        v7 = CLogBuffer::__ls(v6, (int (__cdecl *)(_DWORD))delim);
        v8 = (int)CLogBuffer::__ls((char *)v7, v4);
        CLogBuffer::__ls(v8, end);
        v24 = *(_DWORD *)(v32 + 728) + 10;
        s = (void *)__builtin_vec_new(4 * v24);
        memset(s, -1, 4 * v24);
        v22 = __builtin_vec_new(4 * v24);
        memset((void *)v22, -1, 4 * v24);
        src = 0;
        for(l = 0; l <= 9; ++l)
        {
            if(*(_DWORD *)(4 * l + a1 + 1900)
                && *(_DWORD *)(4 * l + a1 + 1900)
                && *(_BYTE *)(l + a1 + 1940)
                && *(_BYTE *)(l + a1 + 1950)
                && *(_DWORD *)(**(_DWORD **)(4 * l + a1 + 1900) + 20) == **(_DWORD **)(v32 + 464))
            {
                *((_DWORD *)s + src) = 5;
                *(_DWORD *)(v22 + 4 * src++) = ***(_DWORD ***)(4 * l + a1 + 1900);
            }
        }
        for(l = 0; l < *(_DWORD *)(v32 + 728); ++l)
        {
            v19 = CQuestProtoList::FindProto(gserver.Unk452228, *(_DWORD *)(4 * l + v32 + 528));
            if(v19)
            {
                if(*((_DWORD *)v19 + 2))
                    goto LABEL_107;
                v17 = 0;
                for(m = 0; m <= 99 && *(_DWORD *)(4 * m + a1 + 1964) != -1; ++m)
                {
                    if(*(_DWORD *)(4 * m + a1 + 1964) == *(_DWORD *)v19)
                    {
                        v17 = 1;
                        break;
                    }
                }
                if(!v17)
                {
LABEL_107:
                    v16 = CQuestList::FindQuest(a1 + 1900, *(_DWORD *)v19);
                    if(v16 == -1)
                    {
                        if(*((_DWORD *)v19 + 6) <= *(_DWORD *)(a1 + 60) && *((_DWORD *)v19 + 7) >= *(_DWORD *)(a1 + 60))
                        {
                            if(*((_DWORD *)v19 + 8) == -1 || *((_DWORD *)v19 + 8) == *(_BYTE *)(a1 + 477))
                            {
                                v17 = 1;
                                for(m = 0; m <= 4; ++m)
                                {
                                    if(*((_DWORD *)v19 + m + 9) != -1)
                                    {
                                        for(n = 0; n <= 1; ++n)
                                        {
                                            if(n)
                                            {
                                                if(n == 1)
                                                {
                                                    v9 = a1 + 880;
                                                }
                                                else
                                                {
                                                    if(n == 2)
                                                        v9 = a1 + 968;
                                                    else
                                                        v9 = 0;
                                                }
                                            }
                                            else
                                            {
                                                v9 = a1 + 792;
                                            }
                                            v14 = v9;
                                            if(v9)
                                            {
                                                if(CInventory::FindItem(v14, (int)&v13, (int)&v12, *((_DWORD *)v19 + m + 9), 0, 0))
                                                {
                                                    v11 = CInventory::GetItem(v14, v13, v12);
                                                    if(v11)
                                                    {
                                                        if(*((_DWORD *)v19 + m + 14) > CItem::Count(v11))
                                                            v17 = 0;
                                                    }
                                                    else
                                                    {
                                                        v17 = 0;
                                                    }
                                                    break;
                                                }
                                                if(n == 1)
                                                {
                                                    v17 = 0;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                                if(v17)
                                {
                                    if(*((_DWORD *)v19 + 1) != 3 && *((_DWORD *)v19 + 1) != 4)
                                        goto LABEL_108;
                                    v12 = 0;
                                    if(*((_DWORD *)v19 + 1) == 3)
                                    {
                                        result = CServer::FindZone((int)&gserver, 2);
                                        v11 = result;
                                        if(result == -1)
                                            return result;
                                        v12 = 72 * v11 + gserver.Unk452196;
                                    }
                                    result = (signed int)v19;
                                    if(*((_DWORD *)v19 + 1) == 4)
                                    {
                                        result = CServer::FindZone((int)&gserver, 5);
                                        v11 = result;
                                        if(result == -1)
                                            return result;
                                        result = 72 * v11 + gserver.Unk452196;
                                        v12 = 72 * v11 + gserver.Unk452196;
                                    }
                                    if(!v12)
                                        return result;
                                    for(m = 0; m < *(_DWORD *)(v12 + 40) && *(_BYTE *)(*(_DWORD *)(v12 + 36) + 80 * m); ++m)
                                        ;
                                    if(m != *(_DWORD *)(v12 + 40))
                                    {
LABEL_108:
                                        if(*(_DWORD *)v19 != 27
                                            && *(_DWORD *)v19 != 28
                                            && *(_DWORD *)v19 != 29
                                            && *((_DWORD *)s + src) == -1)
                                        {
                                            *((_DWORD *)s + src) = 3;
                                            *(_DWORD *)(v22 + 4 * src++) = *(_DWORD *)v19;
                                        }
                                    }
                                }
                                else
                                {
                                    *((_DWORD *)s + src) = 2;
                                    *(_DWORD *)(v22 + 4 * src++) = *(_DWORD *)v19;
                                }
                            }
                            else
                            {
                                *((_DWORD *)s + src) = 1;
                                *(_DWORD *)(v22 + 4 * src++) = *(_DWORD *)v19;
                            }
                        }
                        else
                        {
                            *((_DWORD *)s + src) = 0;
                            *(_DWORD *)(v22 + 4 * src++) = *(_DWORD *)v19;
                        }
                    }
                    else
                    {
                        if(!*(_BYTE *)(v16 + a1 + 1950))
                        {
                            *((_DWORD *)s + src) = 4;
                            *(_DWORD *)(v22 + 4 * src++) = *(_DWORD *)v19;
                        }
                    }
                }
            }
        }
        CNetMsg::CNetMsg((int)&v10);
        QuestNPCListMsg((int)&v10, src, (int)s, v22);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v10);
        if(s && s)
            __builtin_vec_delete(s);
        if(v22 && v22)
            __builtin_vec_delete(v22);
        result = CNetMsg::_CNetMsg((int)&v10, 2);
    }
    return result;
}

void do_QuestStart(CPC *a1, CNetMsg &a2)
{
    int v2; // eax@1
    int result; // eax@4
    int v4; // eax@39
    __int64 v5; // qax@57
    signed int v6; // ST88_4@89
    const char *v7; // eax@89
    int v8; // eax@89
    int v9; // eax@89
    int v10; // eax@89
    signed int v11; // eax@91
    int v12; // eax@108
    __int64 v13; // qax@126
    signed int v14; // ST70_4@130
    const char *v15; // eax@130
    int v16; // eax@130
    int v17; // eax@130
    int v18; // eax@130
    int v19; // eax@130
    int v20; // eax@130
    __int64 v21; // ST70_8@137
    signed int v22; // ST58_4@137
    signed int v23; // ST40_4@137
    const char *v24; // ST28_4@137
    const char *v25; // ST10_4@137
    const char *v26; // eax@137
    int v27; // eax@137
    int v28; // eax@137
    int v29; // eax@137
    int v30; // eax@137
    int v31; // eax@137
    int v32; // eax@137
    int v33; // eax@137
    int v34; // eax@137
    int v35; // eax@137
    int v36; // eax@137
    int v37; // eax@137
    signed int v38; // ST88_4@143
    const char *v39; // eax@143
    int v40; // eax@143
    int v41; // eax@143
    int v42; // eax@143
    __int64 v43; // ST70_8@163
    signed int v44; // ST58_4@163
    signed int v45; // ST40_4@163
    const char *v46; // ST28_4@163
    const char *v47; // ST10_4@163
    const char *v48; // eax@163
    int v49; // eax@163
    int v50; // eax@163
    int v51; // eax@163
    int v52; // eax@163
    int v53; // eax@163
    int v54; // eax@163
    int v55; // eax@163
    int v56; // eax@163
    int v57; // eax@163
    int v58; // eax@163
    int v59; // eax@163
    __int64 v60; // ST70_8@180
    signed int v61; // ST58_4@180
    signed int v62; // ST40_4@180
    const char *v63; // ST28_4@180
    const char *v64; // ST10_4@180
    const char *v65; // eax@180
    int v66; // eax@180
    int v67; // eax@180
    int v68; // eax@180
    int v69; // eax@180
    int v70; // eax@180
    int v71; // eax@180
    int v72; // eax@180
    int v73; // eax@180
    int v74; // eax@180
    int v75; // eax@180
    int v76; // eax@180
    __int64 v77; // ST70_8@197
    signed int v78; // ST58_4@197
    signed int v79; // ST40_4@197
    const char *v80; // ST28_4@197
    const char *v81; // ST10_4@197
    const char *v82; // eax@197
    int v83; // eax@197
    int v84; // eax@197
    int v85; // eax@197
    int v86; // eax@197
    int v87; // eax@197
    int v88; // eax@197
    int v89; // eax@197
    int v90; // eax@197
    int v91; // eax@197
    int v92; // eax@197
    int v93; // eax@197
    char v94; // [sp+20h] [bp-84h]@160
    int v95; // [sp+34h] [bp-70h]@125
    int v96; // [sp+38h] [bp-6Ch]@124
    char v97; // [sp+3Fh] [bp-65h]@122
    int v98; // [sp+40h] [bp-64h]@103
    int v99; // [sp+54h] [bp-50h]@57
    int v100; // [sp+68h] [bp-3Ch]@52
    int v101; // [sp+6Ch] [bp-38h]@46
    int v102; // [sp+70h] [bp-34h]@46
    int v103; // [sp+74h] [bp-30h]@45
    int j; // [sp+78h] [bp-2Ch]@36
    int v105; // [sp+7Ch] [bp-28h]@19
    int i; // [sp+80h] [bp-24h]@11
    void *v107; // [sp+84h] [bp-20h]@5
    char v108; // [sp+88h] [bp-1Ch]@1
    int dest; // [sp+9Ch] [bp-8h]@1
    char v110; // [sp+A3h] [bp-1h]@1

    CNetMsg::CNetMsg((int)&v108);
    CNetMsg::MoveFirst(a2);
    v2 = CNetMsg::__rs(a2, &v110);
    CNetMsg::__rs(v2, &dest);
    if(*(_DWORD *)(a1 + 1960) <= 9)
    {
        v107 = CQuestProtoList::FindProto(gserver.Unk452228, dest);
        if(!v107)
            return CNetMsg::_CNetMsg((int)&v108, 2);
        if(*((_DWORD *)v107 + 3) == 2 && *((_DWORD *)v107 + 4) != *(_DWORD *)(a1 + 60))
            return CNetMsg::_CNetMsg((int)&v108, 2);
        if(!*((_DWORD *)v107 + 2))
        {
            for(i = 0; i <= 99 && *(_DWORD *)(4 * i + a1 + 1964) != -1; ++i)
            {
                if(*(_DWORD *)(4 * i + a1 + 1964) == *(_DWORD *)v107)
                {
                    QuestErrorMsg((int)&v108, 0);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                    return CNetMsg::_CNetMsg((int)&v108, 2);
                }
            }
        }
        v105 = CQuestList::FindQuest(a1 + 1900, *(_DWORD *)v107);
        if(v105 == -1)
        {
            if(*((_DWORD *)v107 + 6) <= *(_DWORD *)(a1 + 60) && *((_DWORD *)v107 + 7) >= *(_DWORD *)(a1 + 60))
            {
                if(*((_DWORD *)v107 + 8) == -1 || *((_DWORD *)v107 + 8) == *(_BYTE *)(a1 + 477))
                {
                    for(i = 0; i <= 4; ++i)
                    {
                        if(*((_DWORD *)v107 + i + 9) != -1)
                        {
                            for(j = 0; j <= 1; ++j)
                            {
                                if(j)
                                {
                                    if(j == 1)
                                    {
                                        v4 = a1 + 880;
                                    }
                                    else
                                    {
                                        if(j == 2)
                                            v4 = a1 + 968;
                                        else
                                            v4 = 0;
                                    }
                                }
                                else
                                {
                                    v4 = a1 + 792;
                                }
                                v103 = v4;
                                if(v4)
                                {
                                    if(CInventory::FindItem(v103, (int)&v102, (int)&v101, *((_DWORD *)v107 + i + 9), 0, 0))
                                    {
                                        v100 = CInventory::GetItem(v103, v102, v101);
                                        if(v100)
                                        {
                                            if(*((_DWORD *)v107 + i + 14) > CItem::Count(v100))
                                            {
                                                QuestErrorMsg((int)&v108, 4);
                                                if(*(_DWORD *)(a1 + 768))
                                                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                                                return CNetMsg::_CNetMsg((int)&v108, 2);
                                            }
                                            CNetMsg::CNetMsg((int)&v99);
                                            CInventory::Decrease(v103, v100, *((_DWORD *)v107 + i + 14));
                                            v5 = CItem::Count(v100);
                                            if(SHIDWORD(v5) <= 0 && (HIDWORD(v5) || !(_DWORD)v5))
                                            {
                                                ItemDeleteMsg((int)&v99, v100);
                                                if(*(_DWORD *)(a1 + 768))
                                                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v99);
                                                CPC::RemoveItemFromQuickSlot(a1, v100);
                                                CInventory::Remove(v103, v100, 1, 1);
                                            }
                                            else
                                            {
                                                ItemUpdateMsg((int)&v99, v100, -*((_DWORD *)v107 + i + 14));
                                                if(*(_DWORD *)(a1 + 768))
                                                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v99);
                                            }
                                            CNetMsg::_CNetMsg((int)&v99, 2);
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        if(j == 1)
                                        {
                                            QuestErrorMsg((int)&v108, 4);
                                            if(*(_DWORD *)(a1 + 768))
                                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                                            return CNetMsg::_CNetMsg((int)&v108, 2);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if(*((_DWORD *)v107 + 1) != 3 && *((_DWORD *)v107 + 1) != 4)
                        goto LABEL_201;
                    v100 = 0;
                    if(*((_DWORD *)v107 + 1) == 3)
                        v100 = gserver.Unk452196 + 144;
                    if(*((_DWORD *)v107 + 1) == 4)
                        v100 = gserver.Unk452196 + 360;
                    if(!v100)
                        return CNetMsg::_CNetMsg((int)&v108, 2);
                    for(i = 0; i < *(_DWORD *)(v100 + 40) && *(_BYTE *)(*(_DWORD *)(v100 + 36) + 80 * i); ++i)
                        ;
                    if(i != *(_DWORD *)(v100 + 40))
                    {
LABEL_201:
                        v100 = CQuestProtoList::Create(gserver.Unk452228, *(_DWORD *)v107);
                        if(!v100)
                            return CNetMsg::_CNetMsg((int)&v108, 2);
                        v105 = CQuestList::AddQuest(a1 + 1900, v100);
                        if(v105 < 0)
                        {
                            __builtin_delete(v100);
                            return CNetMsg::_CNetMsg((int)&v108, 2);
                        }
                        *(_BYTE *)(v105 + a1 + 1940) = 1;
                        *(_BYTE *)(v105 + a1 + 1950) = 0;
                        v6 = **(_DWORD **)v100;
                        init((int)&v99, (int)"QUEST START");
                        v7 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v99);
                        v8 = (int)CLogBuffer::__ls(v7, (const char *)(a1 + 8));
                        v9 = CLogBuffer::__ls(v8, (int (__cdecl *)(_DWORD))delim);
                        v10 = (int)CLogBuffer::__ls((char *)v9, v6);
                        CLogBuffer::__ls(v10, end);
                        QuestStartMsg((int)&v108, *(uint32_t ***)(4 * v105 + a1 + 1900));
                        if(*(_DWORD *)(a1 + 768))
                            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                        v11 = *((_DWORD *)v107 + 1);
                        if(v11 == 5)
                        {
                            v95 = 0;
                            for(i = 0; i < unk_8104578; ++i)
                            {
                                if(!*(_DWORD *)(unk_8104580 + 212 * i + 4)
                                    && *(_DWORD *)(unk_8104580 + 212 * i + 8) == 8
                                    && !(((unsigned __int8)(*(_DWORD *)(unk_8104580 + 212 * i + 64) >> *(_BYTE *)(a1 + 477)) ^ 1) & 1))
                                {
                                    v95 = CItemList::CreateItem(gserver.Unk41208, *(_DWORD *)(unk_8104580 + 212 * i), -1, 0, 0, 1LL);
                                    break;
                                }
                            }
                            if(!v95)
                                return CNetMsg::_CNetMsg((int)&v108, 2);
                            CNetMsg::CNetMsg((int)&v98);
                            if(CInventory::AddItem(a1 + 792, v95, a1, 1, 1, -1, -1))
                            {
                                ItemAddMsg((int)&v98, v95);
                            }
                            else
                            {
                                v95 = CArea::DropItem(*(_DWORD *)(a1 + 412), v95, a1);
                                if(!v95)
                                {
                                    CNetMsg::_CNetMsg((int)&v98, 2);
                                    return CNetMsg::_CNetMsg((int)&v108, 2);
                                }
                                CNetMsg::CNetMsg((int)&v94);
                                ItemDropMsg((int)&v94, a1, v95);
                                CArea::SendToCell(
                                    *(_DWORD *)(a1 + 412),
                                    (int)&v94,
                                    *(_BYTE *)(v95 + 192),
                                    *(_DWORD *)(v95 + 196),
                                    *(_DWORD *)(v95 + 200),
                                    4);
                                *(_DWORD *)(v95 + 216) = *(_DWORD *)(a1 + 4);
                                CNetMsg::_CNetMsg((int)&v94, 2);
                            }
                            if(*(_DWORD *)(a1 + 768))
                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v98);
                            v43 = CItem::Count(v95);
                            v44 = *(_DWORD *)(v95 + 40);
                            v45 = *(_DWORD *)(v95 + 36);
                            v46 = (const char *)(v95 + 44);
                            v47 = (const char *)(*(_DWORD *)(v95 + 20) + 12);
                            init((int)&v99, (int)"ITEM_PICK", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
                            v48 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v99);
                            v49 = (int)CLogBuffer::__ls(v48, v47);
                            v50 = CLogBuffer::__ls(v49, (int (__cdecl *)(_DWORD))delim);
                            v51 = (int)CLogBuffer::__ls((const char *)v50, v46);
                            v52 = CLogBuffer::__ls(v51, (int (__cdecl *)(_DWORD))delim);
                            v53 = (int)CLogBuffer::__ls((char *)v52, v45);
                            v54 = CLogBuffer::__ls(v53, (int (__cdecl *)(_DWORD))delim);
                            v55 = (int)CLogBuffer::__ls((char *)v54, v44);
                            v56 = CLogBuffer::__ls(v55, (int (__cdecl *)(_DWORD))delim);
                            v57 = (int)CLogBuffer::__ls((char *)v56, v43);
                            v58 = CLogBuffer::__ls(v57, (int (__cdecl *)(_DWORD))delim);
                            v59 = (int)CLogBuffer::__ls((char *)v58, 0);
                            CLogBuffer::__ls(v59, end);
                            CNetMsg::_CNetMsg((int)&v98, 2);
                        }
                        else
                        {
                            if(v11 > 5)
                            {
                                if(v11 == 6)
                                {
                                    v95 = 0;
                                    for(i = 0; i < unk_8104578; ++i)
                                    {
                                        if(!*(_DWORD *)(unk_8104580 + 212 * i + 4)
                                            && *(_DWORD *)(unk_8104580 + 212 * i + 8) == 9
                                            && !(((unsigned __int8)(*(_DWORD *)(unk_8104580 + 212 * i + 64) >> *(_BYTE *)(a1 + 477)) ^ 1) & 1))
                                        {
                                            v95 = CItemList::CreateItem(gserver.Unk41208, *(_DWORD *)(unk_8104580 + 212 * i), -1, 0, 0, 1LL);
                                            break;
                                        }
                                    }
                                    if(!v95)
                                        return CNetMsg::_CNetMsg((int)&v108, 2);
                                    CNetMsg::CNetMsg((int)&v94);
                                    if(CInventory::AddItem(a1 + 792, v95, a1, 1, 1, -1, -1))
                                    {
                                        ItemAddMsg((int)&v94, v95);
                                    }
                                    else
                                    {
                                        v95 = CArea::DropItem(*(_DWORD *)(a1 + 412), v95, a1);
                                        if(!v95)
                                        {
                                            CNetMsg::_CNetMsg((int)&v94, 2);
                                            return CNetMsg::_CNetMsg((int)&v108, 2);
                                        }
                                        CNetMsg::CNetMsg((int)&v98);
                                        ItemDropMsg((int)&v98, a1, v95);
                                        CArea::SendToCell(
                                            *(_DWORD *)(a1 + 412),
                                            (int)&v98,
                                            *(_BYTE *)(v95 + 192),
                                            *(_DWORD *)(v95 + 196),
                                            *(_DWORD *)(v95 + 200),
                                            4);
                                        *(_DWORD *)(v95 + 216) = *(_DWORD *)(a1 + 4);
                                        CNetMsg::_CNetMsg((int)&v98, 2);
                                    }
                                    if(*(_DWORD *)(a1 + 768))
                                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v94);
                                    v60 = CItem::Count(v95);
                                    v61 = *(_DWORD *)(v95 + 40);
                                    v62 = *(_DWORD *)(v95 + 36);
                                    v63 = (const char *)(v95 + 44);
                                    v64 = (const char *)(*(_DWORD *)(v95 + 20) + 12);
                                    init((int)&v99, (int)"ITEM_PICK", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
                                    v65 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v99);
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
                                    v76 = (int)CLogBuffer::__ls((char *)v75, 0);
                                    CLogBuffer::__ls(v76, end);
                                    CNetMsg::_CNetMsg((int)&v94, 2);
                                }
                                else
                                {
                                    if(v11 == 7)
                                    {
                                        v95 = 0;
                                        for(i = 0; i < unk_8104578; ++i)
                                        {
                                            if(!*(_DWORD *)(unk_8104580 + 212 * i + 4)
                                                && *(_DWORD *)(unk_8104580 + 212 * i + 8) == 10
                                                && !(((unsigned __int8)(*(_DWORD *)(unk_8104580 + 212 * i + 64) >> *(_BYTE *)(a1 + 477)) ^ 1) & 1))
                                            {
                                                v95 = CItemList::CreateItem(gserver.Unk41208, *(_DWORD *)(unk_8104580 + 212 * i), -1, 0, 0, 1LL);
                                                break;
                                            }
                                        }
                                        if(!v95)
                                            return CNetMsg::_CNetMsg((int)&v108, 2);
                                        CNetMsg::CNetMsg((int)&v94);
                                        if(CInventory::AddItem(a1 + 792, v95, a1, 1, 1, -1, -1))
                                        {
                                            ItemAddMsg((int)&v94, v95);
                                        }
                                        else
                                        {
                                            v95 = CArea::DropItem(*(_DWORD *)(a1 + 412), v95, a1);
                                            if(!v95)
                                            {
                                                CNetMsg::_CNetMsg((int)&v94, 2);
                                                return CNetMsg::_CNetMsg((int)&v108, 2);
                                            }
                                            CNetMsg::CNetMsg((int)&v98);
                                            ItemDropMsg((int)&v98, a1, v95);
                                            CArea::SendToCell(
                                                *(_DWORD *)(a1 + 412),
                                                (int)&v98,
                                                *(_BYTE *)(v95 + 192),
                                                *(_DWORD *)(v95 + 196),
                                                *(_DWORD *)(v95 + 200),
                                                4);
                                            *(_DWORD *)(v95 + 216) = *(_DWORD *)(a1 + 4);
                                            CNetMsg::_CNetMsg((int)&v98, 2);
                                        }
                                        if(*(_DWORD *)(a1 + 768))
                                            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v94);
                                        v77 = CItem::Count(v95);
                                        v78 = *(_DWORD *)(v95 + 40);
                                        v79 = *(_DWORD *)(v95 + 36);
                                        v80 = (const char *)(v95 + 44);
                                        v81 = (const char *)(*(_DWORD *)(v95 + 20) + 12);
                                        init((int)&v99, (int)"ITEM_PICK", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
                                        v82 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v99);
                                        v83 = (int)CLogBuffer::__ls(v82, v81);
                                        v84 = CLogBuffer::__ls(v83, (int (__cdecl *)(_DWORD))delim);
                                        v85 = (int)CLogBuffer::__ls((const char *)v84, v80);
                                        v86 = CLogBuffer::__ls(v85, (int (__cdecl *)(_DWORD))delim);
                                        v87 = (int)CLogBuffer::__ls((char *)v86, v79);
                                        v88 = CLogBuffer::__ls(v87, (int (__cdecl *)(_DWORD))delim);
                                        v89 = (int)CLogBuffer::__ls((char *)v88, v78);
                                        v90 = CLogBuffer::__ls(v89, (int (__cdecl *)(_DWORD))delim);
                                        v91 = (int)CLogBuffer::__ls((char *)v90, v77);
                                        v92 = CLogBuffer::__ls(v91, (int (__cdecl *)(_DWORD))delim);
                                        v93 = (int)CLogBuffer::__ls((char *)v92, 0);
                                        CLogBuffer::__ls(v93, end);
                                        CNetMsg::_CNetMsg((int)&v94, 2);
                                    }
                                }
                            }
                            else
                            {
                                if(v11 == 2)
                                {
                                    for(i = 0; i <= 2; ++i)
                                    {
                                        if(*((_DWORD *)v107 + i + 19) != -1)
                                        {
                                            if(*((_DWORD *)v107 + i + 19) == 1)
                                            {
                                                v101 = 0;
                                                v101 = CItemList::CreateItem(
                                                                 gserver.Unk41208,
                                                                 *((_DWORD *)v107 + i + 22),
                                                                 -1,
                                                                 0,
                                                                 0,
                                                                 *((_DWORD *)v107 + i + 25));
                                                if(v101)
                                                {
                                                    CNetMsg::CNetMsg((int)&v98);
                                                    if(*(_DWORD *)(*(_DWORD *)(v101 + 20) + 4) != 4
                                                        || *(_DWORD *)(*(_DWORD *)(v101 + 20) + 8) && *(_DWORD *)(*(_DWORD *)(v101 + 20) + 8) != 1)
                                                    {
                                                        v12 = a1 + 792;
                                                    }
                                                    else
                                                    {
                                                        if(*(_DWORD *)(*(_DWORD *)(v101 + 20) + 4) != 4 || *(_DWORD *)(*(_DWORD *)(v101 + 20) + 8))
                                                        {
                                                            if(*(_DWORD *)(*(_DWORD *)(v101 + 20) + 4) == 4
                                                                && *(_DWORD *)(*(_DWORD *)(v101 + 20) + 8)
                                                                && *(_DWORD *)(*(_DWORD *)(v101 + 20) + 8) == 1)
                                                                v12 = a1 + 968;
                                                            else
                                                                v12 = 0;
                                                        }
                                                        else
                                                        {
                                                            v12 = a1 + 880;
                                                        }
                                                    }
                                                    v102 = v12;
                                                    if(v12)
                                                    {
                                                        v97 = 0;
                                                        if(!CInventory::AddItem(v102, v101, a1, 1, 1, -1, -1))
                                                        {
                                                            v14 = *(_DWORD *)v107;
                                                            init((int)&v99, (int)"QUEST ERROR");
                                                            v15 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v99);
                                                            v16 = (int)CLogBuffer::__ls(v15, (const char *)(a1 + 8));
                                                            v17 = CLogBuffer::__ls(v16, (int (__cdecl *)(_DWORD))delim);
                                                            v18 = (int)CLogBuffer::__ls((char *)v17, v14);
                                                            v19 = CLogBuffer::__ls(v18, (int (__cdecl *)(_DWORD))delim);
                                                            v20 = (int)CLogBuffer::__ls((char *)v19, 7);
                                                            CLogBuffer::__ls(v20, end);
                                                            QuestErrorMsg((int)&v108, 7);
                                                            CQuestList::DelQuest(a1 + 1900, a1, v100);
                                                            if(*(_DWORD *)(a1 + 768))
                                                                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                                                            if(v101)
                                                                (*(void (__cdecl **)(int, signed int))(*(_DWORD *)(v101 + 220) + 8))(v101, 3);
                                                            CNetMsg::_CNetMsg((int)&v98, 2);
                                                            return CNetMsg::_CNetMsg((int)&v108, 2);
                                                        }
                                                        if(CItem::tab(v101) == -1)
                                                        {
                                                            v97 = 1;
                                                            if(CInventory::FindItem(
                                                                         v102,
                                                                         (int)&v103,
                                                                         (int)&v96,
                                                                         *(_DWORD *)(v101 + 28),
                                                                         *(_DWORD *)(v101 + 36),
                                                                         *(_DWORD *)(v101 + 40)))
                                                            {
                                                                v95 = CInventory::GetItem(v102, v103, v96);
                                                                if(v95)
                                                                {
                                                                    v13 = CItem::Count(v101);
                                                                    ItemUpdateMsg((int)&v98, v95, v13);
                                                                }
                                                            }
                                                        }
                                                        else
                                                        {
                                                            ItemAddMsg((int)&v98, v101);
                                                        }
                                                        if(*(_DWORD *)(a1 + 768))
                                                            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v98);
                                                        v21 = CItem::Count(v101);
                                                        v22 = *(_DWORD *)(v101 + 40);
                                                        v23 = *(_DWORD *)(v101 + 36);
                                                        v24 = (const char *)(v101 + 44);
                                                        v25 = (const char *)(*(_DWORD *)(v101 + 20) + 12);
                                                        init((int)&v99, (int)"ITEM_PICK", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
                                                        v26 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v99);
                                                        v27 = (int)CLogBuffer::__ls(v26, v25);
                                                        v28 = CLogBuffer::__ls(v27, (int (__cdecl *)(_DWORD))delim);
                                                        v29 = (int)CLogBuffer::__ls((const char *)v28, v24);
                                                        v30 = CLogBuffer::__ls(v29, (int (__cdecl *)(_DWORD))delim);
                                                        v31 = (int)CLogBuffer::__ls((char *)v30, v23);
                                                        v32 = CLogBuffer::__ls(v31, (int (__cdecl *)(_DWORD))delim);
                                                        v33 = (int)CLogBuffer::__ls((char *)v32, v22);
                                                        v34 = CLogBuffer::__ls(v33, (int (__cdecl *)(_DWORD))delim);
                                                        v35 = (int)CLogBuffer::__ls((char *)v34, v21);
                                                        v36 = CLogBuffer::__ls(v35, (int (__cdecl *)(_DWORD))delim);
                                                        v37 = (int)CLogBuffer::__ls((char *)v36, 0);
                                                        CLogBuffer::__ls(v37, end);
                                                        if(v97 && v101)
                                                            (*(void (__cdecl **)(int, signed int))(*(_DWORD *)(v101 + 220) + 8))(v101, 3);
                                                        *(_DWORD *)(4 * i + v100 + 4) = *((_DWORD *)v107 + i + 25);
                                                        CNetMsg::_CNetMsg((int)&v98, 2);
                                                    }
                                                    else
                                                    {
                                                        CNetMsg::_CNetMsg((int)&v98, 2);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    if(!*(_BYTE *)(v105 + a1 + 1950))
                                    {
                                        v38 = ***(_DWORD ***)(4 * v105 + a1 + 1900);
                                        init((int)&v99, (int)"QUEST COMPLETE");
                                        v39 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v99);
                                        v40 = (int)CLogBuffer::__ls(v39, (const char *)(a1 + 8));
                                        v41 = CLogBuffer::__ls(v40, (int (__cdecl *)(_DWORD))delim);
                                        v42 = (int)CLogBuffer::__ls((char *)v41, v38);
                                        CLogBuffer::__ls(v42, end);
                                        CNetMsg::CNetMsg((int)&v98);
                                        QuestCompleteMsg((int)&v98, *(uint32_t ***)(4 * v105 + a1 + 1900));
                                        if(*(_DWORD *)(a1 + 768))
                                            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v98);
                                        *(_BYTE *)(v105 + a1 + 1950) = 1;
                                        CNetMsg::_CNetMsg((int)&v98, 2);
                                    }
                                }
                            }
                        }
                        result = CNetMsg::_CNetMsg((int)&v108, 2);
                    }
                    else
                    {
                        QuestErrorMsg((int)&v108, 6);
                        if(*(_DWORD *)(a1 + 768))
                            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                        result = CNetMsg::_CNetMsg((int)&v108, 2);
                    }
                }
                else
                {
                    QuestErrorMsg((int)&v108, 3);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                    result = CNetMsg::_CNetMsg((int)&v108, 2);
                }
            }
            else
            {
                QuestErrorMsg((int)&v108, 2);
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
                result = CNetMsg::_CNetMsg((int)&v108, 2);
            }
        }
        else
        {
            QuestErrorMsg((int)&v108, 1);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
            result = CNetMsg::_CNetMsg((int)&v108, 2);
        }
    }
    else
    {
        QuestErrorMsg((int)&v108, 5);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v108);
        result = CNetMsg::_CNetMsg((int)&v108, 2);
    }
    return result;
}

void do_QuestGiveUp(CPC *a1, CNetMsg &a2)
{
  int v2; // eax@1
  signed int v4; // eax@5
  __int64 v5; // qax@15
  signed int v6; // ST28_4@30
  const char *v7; // eax@30
  int v8; // eax@30
  int v9; // eax@30
  int v10; // eax@30
  float v11; // ST20_4@37
  float v12; // ST1C_4@37
  char v13; // [sp+2Bh] [bp-49h]@26
  int v14; // [sp+2Ch] [bp-48h]@15
  int v15; // [sp+40h] [bp-34h]@14
  int v16; // [sp+44h] [bp-30h]@13
  int v17; // [sp+48h] [bp-2Ch]@13
  int i; // [sp+4Ch] [bp-28h]@9
  int v19; // [sp+50h] [bp-24h]@3
  int v20; // [sp+54h] [bp-20h]@1
  char v21; // [sp+58h] [bp-1Ch]@1
  int dest; // [sp+6Ch] [bp-8h]@1
  char v23; // [sp+73h] [bp-1h]@1

  CNetMsg::CNetMsg((int)&v21);
  CNetMsg::MoveFirst(a2);
  v2 = CNetMsg::__rs(a2, &v23);
  CNetMsg::__rs(v2, &dest);
  v20 = CQuestList::FindQuest(a1 + 1900, dest);
  if ( v20 < 0 )
    return CNetMsg::_CNetMsg((int)&v21, 2);
  v19 = *(_DWORD *)(4 * v20 + a1 + 1900);
  if ( !v19 )
    return CNetMsg::_CNetMsg((int)&v21, 2);
  v4 = *(_DWORD *)(*(_DWORD *)v19 + 4);
  if ( v4 >= 1 && (v4 <= 2 || v4 <= 7 && v4 >= 4) )
  {
    for ( i = 0; i <= 2; ++i )
    {
      if ( *(_DWORD *)(4 * i + *(_DWORD *)v19 + 76) != -1 )
      {
        if ( *(_DWORD *)(4 * i + *(_DWORD *)v19 + 76) == 1 )
        {
          if ( CInventory::FindItem(a1 + 880, (int)&v17, (int)&v16, *(_DWORD *)(4 * i + *(_DWORD *)v19 + 88), 0, 0) )
          {
            v15 = CInventory::GetItem(a1 + 880, v17, v16);
            if ( v15 )
            {
              CNetMsg::CNetMsg((int)&v14);
              CInventory::Decrease(a1 + 880, v15, *(_DWORD *)(4 * i + v19 + 4));
              v5 = CItem::Count(v15);
              if ( SHIDWORD(v5) <= 0 && (HIDWORD(v5) || !(_DWORD)v5) )
              {
                ItemDeleteMsg((int)&v14, v15);
                if ( *(_DWORD *)(a1 + 768) )
                  CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v14);
                CPC::RemoveItemFromQuickSlot(a1, v15);
                CInventory::Remove(a1 + 880, v15, 1, 1);
              }
              else
              {
                ItemUpdateMsg((int)&v14, v15, -*(_DWORD *)(4 * i + v19 + 4));
                if ( *(_DWORD *)(a1 + 768) )
                  CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v14);
              }
              CNetMsg::_CNetMsg((int)&v14, 2);
            }
          }
        }
      }
    }
  }
  v13 = 0;
  if ( *(_DWORD *)(*(_DWORD *)v19 + 4) == 3
    || *(_DWORD *)(*(_DWORD *)v19 + 4) == 4
    || *(_DWORD *)(*(_DWORD *)v19 + 4) == 10 )
    v13 = 1;
  v6 = **(_DWORD **)v19;
  init((int)&v14, (int)"QUEST GIVEUP");
  v7 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v14);
  v8 = (int)CLogBuffer::__ls(v7, (const char *)(a1 + 8));
  v9 = CLogBuffer::__ls(v8, (int (__cdecl *)(_DWORD))delim);
  v10 = (int)CLogBuffer::__ls((char *)v9, v6);
  CLogBuffer::__ls(v10, end);
  QuestGiveUpMsg((int)&v21, (uint32_t **)v19);
  CQuestList::DelQuest(a1 + 1900, a1, v19);
  if ( *(_DWORD *)(a1 + 768) )
    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v21);
  if ( v13 )
  {
    v15 = CServer::FindZone((int)gserver, 0);
    if ( v15 == -1 )
      return CNetMsg::_CNetMsg((int)&v21, 2);
    v16 = 72 * v15 + *(_DWORD *)&gserver[452196];
    v17 = 0;
    if ( !v16 )
      return CNetMsg::_CNetMsg((int)&v21, 2);
    v11 = (long double)(signed int)GetRandom(
                                     *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v16 + 52) + 4 * v17) + 8),
                                     *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v16 + 52) + 4 * v17) + 16))
        / 2.0;
    v12 = (long double)(signed int)GetRandom(
                                     *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v16 + 52) + 4 * v17) + 4),
                                     *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v16 + 52) + 4 * v17) + 12))
        / 2.0;
    GoZone(a1, 0, **(_BYTE **)(*(_DWORD *)(v16 + 52) + 4 * v17), v12, v11);
  }
  --*(_DWORD *)(a1 + 2364);
  if ( *(_DWORD *)(a1 + 2364) <= 0 )
    *(_DWORD *)(a1 + 2364) = 0;
  return CNetMsg::_CNetMsg((int)&v21, 2);
}

void do_QuestPrize(CPC *a1, CNetMsg &a2)
{
    int v2; // eax@1
    int v3; // eax@1
    int result; // eax@2
    signed int v5; // eax@9
    signed int v6; // ST88_4@18
    const char *v7; // eax@18
    int v8; // eax@18
    int v9; // eax@18
    int v10; // eax@18
    signed int v11; // ST88_4@22
    const char *v12; // eax@22
    int v13; // eax@22
    int v14; // eax@22
    int v15; // eax@22
    signed int v16; // ST88_4@26
    const char *v17; // eax@26
    int v18; // eax@26
    int v19; // eax@26
    int v20; // eax@26
    __int64 v21; // qax@29
    int v22; // eax@43
    int v23; // eax@68
    __int64 v24; // qax@86
    __int64 v25; // ST70_8@95
    signed int v26; // ST58_4@95
    signed int v27; // ST40_4@95
    const char *v28; // ST28_4@95
    const char *v29; // ST10_4@95
    const char *v30; // eax@95
    int v31; // eax@95
    int v32; // eax@95
    int v33; // eax@95
    int v34; // eax@95
    int v35; // eax@95
    int v36; // eax@95
    int v37; // eax@95
    int v38; // eax@95
    int v39; // eax@95
    int v40; // eax@95
    int v41; // eax@95
    char v42; // [sp+23h] [bp-91h]@82
    int v43; // [sp+24h] [bp-90h]@63
    int v44; // [sp+38h] [bp-7Ch]@61
    int v45; // [sp+3Ch] [bp-78h]@85
    char v46; // [sp+43h] [bp-71h]@54
    int v47; // [sp+44h] [bp-70h]@29
    int v48; // [sp+58h] [bp-5Ch]@21
    int v49; // [sp+5Ch] [bp-58h]@18
    int v50; // [sp+6Ch] [bp-48h]@17
    int v51; // [sp+70h] [bp-44h]@17
    char v52; // [sp+74h] [bp-40h]@9
    int i; // [sp+88h] [bp-2Ch]@13
    int v54; // [sp+8Ch] [bp-28h]@3
    int v55; // [sp+90h] [bp-24h]@1
    char v56; // [sp+94h] [bp-20h]@1
    int v57; // [sp+A8h] [bp-Ch]@1
    int dest; // [sp+ACh] [bp-8h]@1
    char v59; // [sp+B3h] [bp-1h]@1

    CNetMsg::CNetMsg((int)&v56);
    CNetMsg::MoveFirst(a2);
    v2 = CNetMsg::__rs(a2, &v59);
    v3 = CNetMsg::__rs(v2, &dest);
    CNetMsg::__rs(v3, &v57);
    v55 = CQuestList::FindQuest(a1 + 1900, dest);
    if(v55 < 0)
        return CNetMsg::_CNetMsg((int)&v56, 2);
    v54 = *(_DWORD *)(4 * v55 + a1 + 1900);
    if(!v54)
        return CNetMsg::_CNetMsg((int)&v56, 2);
    if(*(_DWORD *)(*(_DWORD *)v54 + 20) != v57)
        return CNetMsg::_CNetMsg((int)&v56, 2);
    if(!*(_BYTE *)(v55 + a1 + 1950))
        return CNetMsg::_CNetMsg((int)&v56, 2);
    CNetMsg::CNetMsg((int)&v52);
    v5 = *(_DWORD *)(*(_DWORD *)v54 + 4);
    if(v5 >= 1 && (v5 <= 2 || v5 <= 7 && v5 >= 4))
    {
        for(i = 0; i <= 2; ++i)
        {
            if(*(_DWORD *)(4 * i + *(_DWORD *)v54 + 76) != -1 && *(_DWORD *)(4 * i + *(_DWORD *)v54 + 76) == 1)
            {
                if(!CInventory::FindItem(a1 + 880, (int)&v51, (int)&v50, *(_DWORD *)(4 * i + *(_DWORD *)v54 + 88), 0, 0))
                {
                    v6 = **(_DWORD **)v54;
                    init((int)&v49, (int)"QUEST FAIL");
                    v7 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v49);
                    v8 = (int)CLogBuffer::__ls(v7, (const char *)(a1 + 8));
                    v9 = CLogBuffer::__ls(v8, (int (__cdecl *)(_DWORD))delim);
                    v10 = (int)CLogBuffer::__ls((char *)v9, v6);
                    CLogBuffer::__ls(v10, end);
                    QuestFailMsg((int)&v52, (uint32_t **)v54);
                    CQuestList::DelQuest(a1 + 1900, a1, v54);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v52);
                    CNetMsg::_CNetMsg((int)&v52, 2);
                    return CNetMsg::_CNetMsg((int)&v56, 2);
                }
                v48 = CInventory::GetItem(a1 + 880, v51, v50);
                if(!v48)
                {
                    v11 = **(_DWORD **)v54;
                    init((int)&v49, (int)"QUEST FAIL");
                    v12 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v49);
                    v13 = (int)CLogBuffer::__ls(v12, (const char *)(a1 + 8));
                    v14 = CLogBuffer::__ls(v13, (int (__cdecl *)(_DWORD))delim);
                    v15 = (int)CLogBuffer::__ls((char *)v14, v11);
                    CLogBuffer::__ls(v15, end);
                    QuestFailMsg((int)&v52, (uint32_t **)v54);
                    CQuestList::DelQuest(a1 + 1900, a1, v54);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v52);
                    CNetMsg::_CNetMsg((int)&v52, 2);
                    return CNetMsg::_CNetMsg((int)&v56, 2);
                }
                if(*(_DWORD *)(4 * i + *(_DWORD *)v54 + 100) > CItem::Count(v48))
                {
                    v16 = **(_DWORD **)v54;
                    init((int)&v49, (int)"QUEST FAIL");
                    v17 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v49);
                    v18 = (int)CLogBuffer::__ls(v17, (const char *)(a1 + 8));
                    v19 = CLogBuffer::__ls(v18, (int (__cdecl *)(_DWORD))delim);
                    v20 = (int)CLogBuffer::__ls((char *)v19, v16);
                    CLogBuffer::__ls(v20, end);
                    QuestFailMsg((int)&v52, (uint32_t **)v54);
                    CQuestList::DelQuest(a1 + 1900, a1, v54);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v52);
                    CNetMsg::_CNetMsg((int)&v52, 2);
                    return CNetMsg::_CNetMsg((int)&v56, 2);
                }
                CNetMsg::CNetMsg((int)&v47);
                CInventory::Decrease(a1 + 880, v48, *(_DWORD *)(4 * i + *(_DWORD *)v54 + 100));
                v21 = CItem::Count(v48);
                if(SHIDWORD(v21) <= 0 && (HIDWORD(v21) || !(_DWORD)v21))
                {
                    ItemDeleteMsg((int)&v47, v48);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v47);
                    CPC::RemoveItemFromQuickSlot(a1, v48);
                    CInventory::Remove(a1 + 880, v48, 1, 1);
                }
                else
                {
                    ItemUpdateMsg((int)&v47, v48, -*(_DWORD *)(4 * i + *(_DWORD *)v54 + 100));
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v47);
                }
                CNetMsg::_CNetMsg((int)&v47, 2);
            }
        }
    }
    for(i = 0; i <= 4; ++i)
    {
        if(*(_DWORD *)(4 * i + *(_DWORD *)v54 + 160) != -1)
        {
            v22 = *(_DWORD *)v54 + 160;
            if(*(_DWORD *)(4 * i + v22) <= 5u)
                JUMPOUT(__CS__, off_80D374C[*(_DWORD *)(4 * i + v22)]);
        }
    }
    QuestPrizeMsg((int)&v52, (uint32_t **)v54);
    if(*(_DWORD *)(a1 + 768))
        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v52);
    if(!*(_DWORD *)(*(_DWORD *)v54 + 8))
    {
        for(i = 0; i <= 99; ++i)
        {
            if(*(_DWORD *)(4 * i + a1 + 1964) == -1)
            {
                *(_DWORD *)(4 * i + a1 + 1964) = **(_DWORD **)v54;
                break;
            }
        }
    }
    v46 = 1;
    if(*(_DWORD *)(*(_DWORD *)v54 + 4) == 3 || *(_DWORD *)(*(_DWORD *)v54 + 4) == 4)
        v46 = 0;
    CQuestList::DelQuest(a1 + 1900, a1, v54);
    if(!v46
        || (++*(_DWORD *)(a1 + 2364), *(_DWORD *)(a1 + 2364) <= 4)
        || *(_DWORD *)(a1 + 60) <= 12
        || *(_DWORD *)(a1 + 60) > 27)
        goto LABEL_99;
    *(_DWORD *)(a1 + 2364) = 0;
    v44 = CItemList::CreateItem(gserver.Unk41208, *unk_8104598, -1, 0, 0, 1LL);
    if(!v44)
    {
        CNetMsg::_CNetMsg((int)&v52, 2);
        return CNetMsg::_CNetMsg((int)&v56, 2);
    }
    CNetMsg::CNetMsg((int)&v43);
    if(*(_DWORD *)(*(_DWORD *)(v44 + 20) + 4) != 4
        || *(_DWORD *)(*(_DWORD *)(v44 + 20) + 8) && *(_DWORD *)(*(_DWORD *)(v44 + 20) + 8) != 1)
    {
        v23 = a1 + 792;
    }
    else
    {
        if(*(_DWORD *)(*(_DWORD *)(v44 + 20) + 4) != 4 || *(_DWORD *)(*(_DWORD *)(v44 + 20) + 8))
        {
            if(*(_DWORD *)(*(_DWORD *)(v44 + 20) + 4) == 4
                && *(_DWORD *)(*(_DWORD *)(v44 + 20) + 8)
                && *(_DWORD *)(*(_DWORD *)(v44 + 20) + 8) == 1)
                v23 = a1 + 968;
            else
                v23 = 0;
        }
        else
        {
            v23 = a1 + 880;
        }
    }
    v48 = v23;
    if(!v23)
    {
        CNetMsg::_CNetMsg((int)&v43, 2);
        CNetMsg::_CNetMsg((int)&v52, 2);
        return CNetMsg::_CNetMsg((int)&v56, 2);
    }
    v42 = 0;
    if(CInventory::AddItem(v48, v44, a1, 1, 1, -1, -1))
    {
        if(CItem::tab(v44) == -1)
        {
            v42 = 1;
            if(CInventory::FindItem(
                         v48,
                         (int)&v50,
                         (int)&v51,
                         *(_DWORD *)(v44 + 28),
                         *(_DWORD *)(v44 + 36),
                         *(_DWORD *)(v44 + 40)))
            {
                v45 = CInventory::GetItem(v48, v50, v51);
                if(v45)
                {
                    v24 = CItem::Count(v44);
                    ItemUpdateMsg((int)&v43, v45, v24);
                }
            }
        }
        else
        {
            ItemAddMsg((int)&v43, v44);
        }
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v43);
        v25 = CItem::Count(v44);
        v26 = *(_DWORD *)(v44 + 40);
        v27 = *(_DWORD *)(v44 + 36);
        v28 = (const char *)(v44 + 44);
        v29 = (const char *)(*(_DWORD *)(v44 + 20) + 12);
        init((int)&v49, (int)"ITEM_PICK", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
        v30 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v49);
        v31 = (int)CLogBuffer::__ls(v30, v29);
        v32 = CLogBuffer::__ls(v31, (int (__cdecl *)(_DWORD))delim);
        v33 = (int)CLogBuffer::__ls((const char *)v32, v28);
        v34 = CLogBuffer::__ls(v33, (int (__cdecl *)(_DWORD))delim);
        v35 = (int)CLogBuffer::__ls((char *)v34, v27);
        v36 = CLogBuffer::__ls(v35, (int (__cdecl *)(_DWORD))delim);
        v37 = (int)CLogBuffer::__ls((char *)v36, v26);
        v38 = CLogBuffer::__ls(v37, (int (__cdecl *)(_DWORD))delim);
        v39 = (int)CLogBuffer::__ls((char *)v38, v25);
        v40 = CLogBuffer::__ls(v39, (int (__cdecl *)(_DWORD))delim);
        v41 = (int)CLogBuffer::__ls((char *)v40, 0);
        CLogBuffer::__ls(v41, end);
        if(v42 && v44)
            (*(void (__cdecl **)(int, signed int))(*(_DWORD *)(v44 + 220) + 8))(v44, 3);
        CNetMsg::_CNetMsg((int)&v43, 2);
LABEL_99:
        CNetMsg::_CNetMsg((int)&v52, 2);
        return CNetMsg::_CNetMsg((int)&v56, 2);
    }
    v44 = CArea::DropItem(*(_DWORD *)(a1 + 412), v44, a1);
    if(v44)
    {
        CNetMsg::CNetMsg((int)&v47);
        ItemDropMsg((int)&v47, a1, v44);
        CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v47, a1, 1, 4);
        *(_DWORD *)(v44 + 216) = *(_DWORD *)(a1 + 4);
        CNetMsg::_CNetMsg((int)&v47, 2);
        CNetMsg::_CNetMsg((int)&v43, 2);
        CNetMsg::_CNetMsg((int)&v52, 2);
        result = CNetMsg::_CNetMsg((int)&v56, 2);
    }
    else
    {
        CNetMsg::_CNetMsg((int)&v43, 2);
        CNetMsg::_CNetMsg((int)&v52, 2);
        result = CNetMsg::_CNetMsg((int)&v56, 2);
    }
    return result;
}

void do_QuestComplete(CPC *a1, CNetMsg &a2)
{
    int v2; // eax@1
    int result; // eax@2
    int v4; // eax@6
    signed int v5; // ST88_4@14
    const char *v6; // eax@14
    int v7; // eax@14
    int v8; // eax@14
    int v9; // eax@14
    signed int v10; // ST88_4@18
    const char *v11; // eax@18
    int v12; // eax@18
    int v13; // eax@18
    int v14; // eax@18
    signed int v15; // ST88_4@22
    const char *v16; // eax@22
    int v17; // eax@22
    int v18; // eax@22
    int v19; // eax@22
    __int64 v20; // ST70_8@44
    signed int v21; // ST58_4@44
    signed int v22; // ST40_4@44
    const char *v23; // ST28_4@44
    const char *v24; // ST10_4@44
    const char *v25; // eax@44
    int v26; // eax@44
    int v27; // eax@44
    int v28; // eax@44
    int v29; // eax@44
    int v30; // eax@44
    int v31; // eax@44
    int v32; // eax@44
    int v33; // eax@44
    int v34; // eax@44
    int v35; // eax@44
    int v36; // eax@44
    signed int v37; // ST88_4@45
    const char *v38; // eax@45
    int v39; // eax@45
    int v40; // eax@45
    int v41; // eax@45
    signed int v42; // ST88_4@48
    signed int v43; // ST70_4@48
    signed int v44; // ST40_4@48
    const char *v45; // eax@48
    int v46; // eax@48
    int v47; // eax@48
    int v48; // eax@48
    int v49; // eax@48
    int v50; // eax@48
    int v51; // eax@48
    int v52; // eax@48
    int v53; // eax@48
    int v54; // eax@48
    signed int v55; // ST88_4@58
    const char *v56; // eax@58
    int v57; // eax@58
    int v58; // eax@58
    int v59; // eax@58
    char v60; // [sp+24h] [bp-80h]@41
    char v61; // [sp+38h] [bp-6Ch]@37
    int v62; // [sp+4Ch] [bp-58h]@17
    int v63; // [sp+50h] [bp-54h]@14
    int v64; // [sp+60h] [bp-44h]@13
    int v65; // [sp+64h] [bp-40h]@13
    char v66; // [sp+68h] [bp-3Ch]@6
    int i; // [sp+7Ch] [bp-28h]@9
    int v68; // [sp+80h] [bp-24h]@3
    int v69; // [sp+84h] [bp-20h]@1
    char v70; // [sp+88h] [bp-1Ch]@1
    int dest; // [sp+9Ch] [bp-8h]@1
    char v72; // [sp+A3h] [bp-1h]@1

    CNetMsg::CNetMsg((int)&v70);
    CNetMsg::MoveFirst(a2);
    v2 = CNetMsg::__rs(a2, &v72);
    CNetMsg::__rs(v2, &dest);
    v69 = CQuestList::FindQuest(a1 + 1900, dest);
    if(v69 < 0)
        return CNetMsg::_CNetMsg((int)&v70, 2);
    v68 = *(_DWORD *)(4 * v69 + a1 + 1900);
    if(!v68 || !*(_DWORD *)v68)
        return CNetMsg::_CNetMsg((int)&v70, 2);
    CNetMsg::CNetMsg((int)&v66);
    v4 = *(_DWORD *)(*(_DWORD *)v68 + 4);
    if(v4 == 4)
    {
        for(i = 0; i <= 2; ++i)
        {
            if(*(_DWORD *)(4 * i + *(_DWORD *)v68 + 76) != -1 && *(_DWORD *)(4 * i + *(_DWORD *)v68 + 76) == 1)
            {
                if(!CInventory::FindItem(a1 + 880, (int)&v65, (int)&v64, *(_DWORD *)(4 * i + *(_DWORD *)v68 + 88), 0, 0))
                {
                    v5 = **(_DWORD **)v68;
                    init((int)&v63, (int)"QUEST FAIL");
                    v6 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v63);
                    v7 = (int)CLogBuffer::__ls(v6, (const char *)(a1 + 8));
                    v8 = CLogBuffer::__ls(v7, (int (__cdecl *)(_DWORD))delim);
                    v9 = (int)CLogBuffer::__ls((char *)v8, v5);
                    CLogBuffer::__ls(v9, end);
                    QuestFailMsg((int)&v66, (uint32_t **)v68);
                    CQuestList::DelQuest(a1 + 1900, a1, v68);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v66);
                    CNetMsg::_CNetMsg((int)&v66, 2);
                    return CNetMsg::_CNetMsg((int)&v70, 2);
                }
                v62 = CInventory::GetItem(a1 + 880, v65, v64);
                if(!v62)
                {
                    v10 = **(_DWORD **)v68;
                    init((int)&v63, (int)"QUEST FAIL");
                    v11 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v63);
                    v12 = (int)CLogBuffer::__ls(v11, (const char *)(a1 + 8));
                    v13 = CLogBuffer::__ls(v12, (int (__cdecl *)(_DWORD))delim);
                    v14 = (int)CLogBuffer::__ls((char *)v13, v10);
                    CLogBuffer::__ls(v14, end);
                    QuestFailMsg((int)&v66, (uint32_t **)v68);
                    CQuestList::DelQuest(a1 + 1900, a1, v68);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v66);
                    CNetMsg::_CNetMsg((int)&v66, 2);
                    return CNetMsg::_CNetMsg((int)&v70, 2);
                }
                if(*(_DWORD *)(4 * i + *(_DWORD *)v68 + 100) > CItem::Count(v62))
                {
                    v15 = **(_DWORD **)v68;
                    init((int)&v63, (int)"QUEST FAIL");
                    v16 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v63);
                    v17 = (int)CLogBuffer::__ls(v16, (const char *)(a1 + 8));
                    v18 = CLogBuffer::__ls(v17, (int (__cdecl *)(_DWORD))delim);
                    v19 = (int)CLogBuffer::__ls((char *)v18, v15);
                    CLogBuffer::__ls(v19, end);
                    QuestFailMsg((int)&v66, (uint32_t **)v68);
                    CQuestList::DelQuest(a1 + 1900, a1, v68);
                    if(*(_DWORD *)(a1 + 768))
                        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v66);
                    CNetMsg::_CNetMsg((int)&v66, 2);
                    return CNetMsg::_CNetMsg((int)&v70, 2);
                }
            }
        }
        if(!*(_BYTE *)(v69 + a1 + 1950))
        {
            v55 = **(_DWORD **)v68;
            init((int)&v63, (int)"QUEST COMPLETE");
            v56 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v63);
            v57 = (int)CLogBuffer::__ls(v56, (const char *)(a1 + 8));
            v58 = CLogBuffer::__ls(v57, (int (__cdecl *)(_DWORD))delim);
            v59 = (int)CLogBuffer::__ls((char *)v58, v55);
            CLogBuffer::__ls(v59, end);
            CNetMsg::CNetMsg((int)&v60);
            QuestCompleteMsg((int)&v60, (uint32_t **)v68);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v60);
            *(_BYTE *)(v69 + a1 + 1950) = 1;
            CNetMsg::_CNetMsg((int)&v60, 2);
        }
        CNetMsg::_CNetMsg((int)&v66, 2);
        result = CNetMsg::_CNetMsg((int)&v70, 2);
    }
    else
    {
        if(v4 != 10)
        {
            CNetMsg::_CNetMsg((int)&v66, 2);
            return CNetMsg::_CNetMsg((int)&v70, 2);
        }
        v62 = 0;
        for(i = 0; i < unk_8104578; ++i)
        {
            if(*(_DWORD *)(unk_8104580 + 212 * i + 4) == 1
                && *(_DWORD *)(unk_8104580 + 212 * i + 8) == 1
                && *(_WORD *)(unk_8104580 + 212 * i + 100) == 6
                && !(((unsigned __int8)(*(_DWORD *)(unk_8104580 + 212 * i + 64) >> *(_BYTE *)(a1 + 477)) ^ 1) & 1))
            {
                v62 = CItemList::CreateItem(gserver.Unk41208, *(_DWORD *)(unk_8104580 + 212 * i), -1, 0, 0, 1LL);
                break;
            }
        }
        if(!v62)
        {
            CNetMsg::_CNetMsg((int)&v66, 2);
            return CNetMsg::_CNetMsg((int)&v70, 2);
        }
        CNetMsg::CNetMsg((int)&v61);
        if(CInventory::AddItem(a1 + 792, v62, a1, 1, 1, -1, -1))
        {
            ItemAddMsg((int)&v61, v62);
        }
        else
        {
            v62 = CArea::DropItem(*(_DWORD *)(a1 + 412), v62, a1);
            if(!v62)
            {
                CNetMsg::_CNetMsg((int)&v61, 2);
                CNetMsg::_CNetMsg((int)&v66, 2);
                return CNetMsg::_CNetMsg((int)&v70, 2);
            }
            CNetMsg::CNetMsg((int)&v60);
            ItemDropMsg((int)&v60, a1, v62);
            CArea::SendToCell(
                *(_DWORD *)(a1 + 412),
                (int)&v60,
                *(_BYTE *)(v62 + 192),
                *(_DWORD *)(v62 + 196),
                *(_DWORD *)(v62 + 200),
                4);
            *(_DWORD *)(v62 + 216) = *(_DWORD *)(a1 + 4);
            CNetMsg::_CNetMsg((int)&v60, 2);
        }
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v61);
        v20 = CItem::Count(v62);
        v21 = *(_DWORD *)(v62 + 40);
        v22 = *(_DWORD *)(v62 + 36);
        v23 = (const char *)(v62 + 44);
        v24 = (const char *)(*(_DWORD *)(v62 + 20) + 12);
        init((int)&v63, (int)"ITEM_PICK", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
        v25 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v63);
        v26 = (int)CLogBuffer::__ls(v25, v24);
        v27 = CLogBuffer::__ls(v26, (int (__cdecl *)(_DWORD))delim);
        v28 = (int)CLogBuffer::__ls((const char *)v27, v23);
        v29 = CLogBuffer::__ls(v28, (int (__cdecl *)(_DWORD))delim);
        v30 = (int)CLogBuffer::__ls((char *)v29, v22);
        v31 = CLogBuffer::__ls(v30, (int (__cdecl *)(_DWORD))delim);
        v32 = (int)CLogBuffer::__ls((char *)v31, v21);
        v33 = CLogBuffer::__ls(v32, (int (__cdecl *)(_DWORD))delim);
        v34 = (int)CLogBuffer::__ls((char *)v33, v20);
        v35 = CLogBuffer::__ls(v34, (int (__cdecl *)(_DWORD))delim);
        v36 = (int)CLogBuffer::__ls((char *)v35, 0);
        CLogBuffer::__ls(v36, end);
        if(!*(_BYTE *)(v69 + a1 + 1950))
        {
            v37 = **(_DWORD **)v68;
            init((int)&v63, (int)"QUEST COMPLETE");
            v38 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v63);
            v39 = (int)CLogBuffer::__ls(v38, (const char *)(a1 + 8));
            v40 = CLogBuffer::__ls(v39, (int (__cdecl *)(_DWORD))delim);
            v41 = (int)CLogBuffer::__ls((char *)v40, v37);
            CLogBuffer::__ls(v41, end);
            CNetMsg::CNetMsg((int)&v60);
            QuestCompleteMsg((int)&v60, (uint32_t **)v68);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v60);
            *(_BYTE *)(v69 + a1 + 1950) = 1;
            CNetMsg::_CNetMsg((int)&v60, 2);
        }
        v42 = *(_DWORD *)(*(_DWORD *)v68 + 200);
        v43 = *(_DWORD *)(*(_DWORD *)v68 + 180);
        v44 = **(_DWORD **)v68;
        init((int)&v63, (int)"QUEST PRIZE");
        v45 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v63);
        v46 = (int)CLogBuffer::__ls(v45, (const char *)(a1 + 8));
        v47 = CLogBuffer::__ls(v46, (int (__cdecl *)(_DWORD))delim);
        v48 = (int)CLogBuffer::__ls((char *)v47, v44);
        v49 = CLogBuffer::__ls(v48, (int (__cdecl *)(_DWORD))delim);
        v50 = (int)CLogBuffer::__ls((char *)v49, 1);
        v51 = CLogBuffer::__ls(v50, (int (__cdecl *)(_DWORD))delim);
        v52 = (int)CLogBuffer::__ls((char *)v51, v43);
        v53 = CLogBuffer::__ls(v52, (int (__cdecl *)(_DWORD))delim);
        v54 = (int)CLogBuffer::__ls((char *)v53, v42);
        CLogBuffer::__ls(v54, end);
        QuestPrizeMsg((int)&v66, (uint32_t **)v68);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v66);
        if(!*(_DWORD *)(*(_DWORD *)v68 + 8))
        {
            for(i = 0; i <= 99; ++i)
            {
                if(*(_DWORD *)(4 * i + a1 + 1964) == -1)
                {
                    *(_DWORD *)(4 * i + a1 + 1964) = **(_DWORD **)v68;
                    break;
                }
            }
        }
        CQuestList::DelQuest(a1 + 1900, a1, v68);
        CNetMsg::_CNetMsg((int)&v61, 2);
        CNetMsg::_CNetMsg((int)&v66, 2);
        result = CNetMsg::_CNetMsg((int)&v70, 2);
    }
    return result;
}
*/
