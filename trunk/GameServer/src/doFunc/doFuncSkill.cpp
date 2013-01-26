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

void do_Skill(CPC *a1, CNetMsg &a2)
{
    /* TODO */
}

/*void do_Skill(CPC *a1, CNetMsg &a2)
{
    unsigned __int8 result; // al@1
    unsigned __int8 dest; // [sp+17h] [bp-1h]@4

    result = a1;
    if(*(_WORD *)(a1 + 76) > 0)
    {
        result = CPC::IsSetPlayerState(a1, 1);
        if(!result)
        {
            CNetMsg::MoveFirst(a2);
            CNetMsg::__rs(a2, &dest);
            result = dest;
            if(dest == 2)
            {
                result = do_SkillReady(a1, a2);
            }
            else
            {
                if((signed int)dest > 2)
                {
                    if(dest == 3)
                    {
                        result = do_SkillFire(a1, a2);
                    }
                    else
                    {
                        if(dest == 4)
                            result = do_SkillCancel(a1, a2);
                    }
                }
                else
                {
                    if(dest == 1)
                        result = do_SkillLearn(a1, a2);
                }
            }
        }
    }
    return result;
}

void do_SkillLearn(CPC *a1, CNetMsg &a2)
{
    int v2; // eax@1
    int v3; // ebx@2
    __int64 *v4; // eax@2
    int v5; // eax@9
    int v6; // esi@12
    __int64 *v7; // eax@12
    int v9; // edi@16
    __int64 *v10; // eax@16
    int v11; // ST8C_4@18
    __int64 *v12; // eax@18
    int v13; // ST88_4@23
    __int64 *v14; // eax@23
    int v15; // ST7C_4@26
    __int64 *v16; // eax@26
    int v17; // ST78_4@38
    __int64 *v18; // eax@38
    __int64 v19; // qax@44
    int v20; // ST5C_4@55
    __int64 *v21; // eax@55
    signed int v22; // ST28_4@65
    signed int v23; // ST10_4@65
    char *v24; // eax@65
    int v25; // eax@65
    int v26; // eax@65
    int v27; // eax@65
    int v28; // [sp+5Ch] [bp-58h]@65
    int v29; // [sp+6Ch] [bp-48h]@22
    int v30; // [sp+70h] [bp-44h]@22
    char v31[12]; // [sp+74h] [bp-40h]@21
    int i; // [sp+80h] [bp-34h]@19
    int v33; // [sp+84h] [bp-30h]@11
    int v34; // [sp+88h] [bp-2Ch]@11
    int v35; // [sp+8Ch] [bp-28h]@8
    int v36; // [sp+90h] [bp-24h]@3
    int v37; // [sp+94h] [bp-20h]@1
    int dest; // [sp+98h] [bp-1Ch]@1
    char v39; // [sp+9Fh] [bp-15h]@1
    int v40; // [sp+A0h] [bp-14h]@1

    CNetMsg::CNetMsg((int)&v40);
    CNetMsg::MoveFirst(a2);
    v2 = CNetMsg::__rs(a2, &v39);
    CNetMsg::__rs(v2, &dest);
    v37 = CSkillProtoList::Find(gserver.Unk452220, dest);
    if(!v37)
    {
        v3 = __eh_alloc(4);
        *(_DWORD *)v3 = 4;
        v4 = _tf23_tagSkillLearnErrorType();
        __cp_push_exception(v3, v4, 0);
        __throw();
    }
    v36 = 0;
    if(CSkillProto::IsActive(v37))
    {
        v36 = a1 + 480;
    }
    else
    {
        if(CSkillProto::IsPassive(v37))
            v36 = a1 + 492;
        else
            v36 = a1 + 504;
    }
    v35 = CSkillList::Find((int *)v36, dest);
    if(v35)
        v5 = *(_BYTE *)(v35 + 4) + 1;
    else
        v5 = 1;
    v34 = v5;
    v33 = CSkillProto::Level(v37, v5);
    if(!v33)
    {
        v6 = __eh_alloc(4);
        *(_DWORD *)v6 = 4;
        v7 = _tf23_tagSkillLearnErrorType();
        __cp_push_exception(v6, v7, 0);
        __throw();
    }
    if(!((*(_DWORD *)(v37 + 4) >> *(_BYTE *)(a1 + 477)) & 1))
        return CNetMsg::_CNetMsg((int)&v40, 2);
    if(*(_DWORD *)(v33 + 24) > *(_DWORD *)(a1 + 60))
    {
        v9 = __eh_alloc(4);
        *(_DWORD *)v9 = 0;
        v10 = _tf23_tagSkillLearnErrorType();
        __cp_push_exception(v9, v10, 0);
        __throw();
    }
    if(10000 * *(_DWORD *)(v33 + 28) > *(_DWORD *)(a1 + 72))
    {
        v11 = __eh_alloc(4);
        *(_DWORD *)v11 = 1;
        v12 = _tf23_tagSkillLearnErrorType();
        __cp_push_exception(v11, v12, 0);
        __throw();
    }
    for(i = 0; i <= 2; ++i)
    {
        *(_DWORD *)&v31[4 * i] = 0;
        if(*(_DWORD *)(4 * i + v33 + 48) >= 0)
        {
            if(!CInventory::FindItem(a1 + 792, (int)&v30, (int)&v29, *(_DWORD *)(4 * i + v33 + 48), 0, 0))
            {
                v13 = __eh_alloc(4);
                *(_DWORD *)v13 = 2;
                v14 = _tf23_tagSkillLearnErrorType();
                __cp_push_exception(v13, v14, 0);
                __throw();
            }
            *(_DWORD *)&v31[4 * i] = CInventory::GetItem(a1 + 792, v30, v29);
            if(!*(_DWORD *)&v31[4 * i] || *(_DWORD *)(4 * i + v33 + 60) > CItem::Count(*(_DWORD *)&v31[4 * i]))
            {
                v15 = __eh_alloc(4);
                *(_DWORD *)v15 = 2;
                v16 = _tf23_tagSkillLearnErrorType();
                __cp_push_exception(v15, v16, 0);
                __throw();
            }
        }
    }
    for(i = 0; i <= 2; ++i)
    {
        if(*(_DWORD *)(4 * i + v33 + 32) >= 0)
        {
            v29 = CSkillProtoList::Find(gserver.Unk452220, *(_DWORD *)(4 * i + v33 + 32));
            if(CSkillProto::IsActive(v29))
                v30 = CSkillList::Find((int *)(a1 + 480), *(_DWORD *)(4 * i + v33 + 32));
            else
                v30 = CSkillProto::IsPassive(v29) ? CSkillList::Find((int *)(a1 + 492), *(_DWORD *)(4 * i + v33 + 32)) : CSkillList::Find((int *)(a1 + 504), *(_DWORD *)(4 * i + v33 + 32));
            if(!v30 || *(_BYTE *)(v30 + 4) < *(_BYTE *)(i + v33 + 44))
            {
                v17 = __eh_alloc(4);
                *(_DWORD *)v17 = 3;
                v18 = _tf23_tagSkillLearnErrorType();
                __cp_push_exception(v17, v18, 0);
                __throw();
            }
        }
    }
    *(_DWORD *)(a1 + 72) -= 10000 * *(_DWORD *)(v33 + 28);
    for(i = 0; i <= 2; ++i)
    {
        if(*(_DWORD *)&v31[4 * i] && *(_DWORD *)(4 * i + v33 + 60) > 0)
        {
            CInventory::Decrease(a1 + 792, *(_DWORD *)&v31[4 * i], *(_DWORD *)(4 * i + v33 + 60));
            v19 = CItem::Count(*(_DWORD *)&v31[4 * i]);
            if(SHIDWORD(v19) > 0 || !HIDWORD(v19) && (_DWORD)v19)
            {
                ItemUpdateMsg((int)&v40, *(_DWORD *)&v31[4 * i], -*(_DWORD *)(4 * i + v33 + 60));
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v40);
            }
            else
            {
                ItemDeleteMsg((int)&v40, *(_DWORD *)&v31[4 * i]);
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v40);
                CInventory::Remove(a1 + 792, *(_DWORD *)&v31[4 * i], 1, 1);
            }
        }
    }
    if(v35)
    {
        if(*(_BYTE *)(v35 + 4) >= *(_BYTE *)(v37 + 16))
            return CNetMsg::_CNetMsg((int)&v40, 2);
        ++*(_BYTE *)(v35 + 4);
    }
    else
    {
        v35 = CSkillProtoList::Create(gserver.Unk452220, dest, 1);
        if(!v35)
        {
            v20 = __eh_alloc(4);
            *(_DWORD *)v20 = 4;
            v21 = _tf23_tagSkillLearnErrorType();
            __cp_push_exception(v20, v21, 0);
            __throw();
        }
        if(CSkillProto::IsActive(v37))
        {
            CSkillList::Add(a1 + 480, (int ***)&v35);
        }
        else
        {
            if(CSkillProto::IsPassive(v37))
                CSkillList::Add(a1 + 492, (int ***)&v35);
            else
                CSkillList::Add(a1 + 504, (int ***)&v35);
        }
    }
    v22 = *(_BYTE *)(v35 + 4);
    v23 = **(_DWORD **)v35;
    init((int)&v28, (int)"SKILL LEARN", a1 + 8, *(_DWORD *)(a1 + 768) + 4);
    v24 = (char *)CLogBuffer::__ls(g_gamelogbuffer, (int)&v28);
    v25 = (int)CLogBuffer::__ls(v24, v23);
    v26 = CLogBuffer::__ls(v25, (int (__cdecl *)(_DWORD))delim);
    v27 = (int)CLogBuffer::__ls((char *)v26, v22);
    CLogBuffer::__ls(v27, end);
    SkillLearnMsg((int)&v40, v35);
    if(*(_DWORD *)(a1 + 768))
        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v40);
    CPC::CalcStatus(a1, 1);
    return CNetMsg::_CNetMsg((int)&v40, 2);
}

void do_SkillReady(CPC *a1, CNetMsg &a2)
{
    int result; // eax@1
    int v3; // eax@4
    int v4; // eax@4
    int v5; // eax@4
    int v6; // eax@4
    int v7; // ST54_4@19
    char v8; // al@42
    float v9; // ST50_4@52
    int v10; // [sp+18h] [bp-40h]@18
    int v11; // [sp+1Ch] [bp-3Ch]@18
    int i; // [sp+20h] [bp-38h]@15
    int v13; // [sp+24h] [bp-34h]@4
    int v14; // [sp+28h] [bp-30h]@11
    int v15; // [sp+2Ch] [bp-2Ch]@8
    int v16; // [sp+30h] [bp-28h]@4
    char v17; // [sp+37h] [bp-21h]@4
    int v18; // [sp+38h] [bp-20h]@4
    char dest; // [sp+3Ch] [bp-1Ch]@4
    char v20; // [sp+43h] [bp-15h]@4
    char v21; // [sp+44h] [bp-14h]@4

    result = a1;
    if(*(_BYTE *)(a1 + 474) || (result = a1, !*(_DWORD *)(a1 + 412)))
        return result;
    CNetMsg::CNetMsg((int)&v21);
    v13 = 0;
    CNetMsg::MoveFirst(a2);
    v3 = CNetMsg::__rs(a2, &v20);
    v4 = CNetMsg::__rs(v3, &dest);
    v5 = CNetMsg::__rs(v4, &v18);
    v6 = CNetMsg::__rs(v5, &v17);
    CNetMsg::__rs(v6, &v16);
    if(*(_DWORD *)(a1 + 424))
    {
        if(gserver.Unk41248 - *(_DWORD *)(*(_DWORD *)(a1 + 424) + 12) < *(_DWORD *)(**(_DWORD **)(a1 + 424) + 64)
                                                                                                                             + *(_DWORD *)(**(_DWORD **)(a1 + 424) + 60)
                                                                                                                             + *(_DWORD *)(**(_DWORD **)(a1 + 424) + 56)
                                                                                                                             - 5)
        {
            SysMsg((int)&v21, 9);
            goto LABEL_68;
        }
        CSkill::Cancel(*(_DWORD *)(a1 + 424));
        *(_DWORD *)(a1 + 424) = 0;
    }
    v15 = CPC::FindSkill(a1, v18);
    if(!v15 || !*(_DWORD *)v15 || (v14 = CSkillProto::Level(*(_DWORD *)v15, *(_BYTE *)(v15 + 4))) == 0)
    {
        SysMsg((int)&v21, 10);
        goto LABEL_68;
    }
    if(!CSkill::IsReady(v15, a1))
    {
        SysMsg((int)&v21, 11);
        goto LABEL_68;
    }
    if(*(_WORD *)(a1 + 76) < *(_WORD *)v14)
    {
        SysSkillInsuffMsg((int)&v21, 0);
        goto LABEL_68;
    }
    if(*(_WORD *)(a1 + 80) < *(_WORD *)(v14 + 2))
    {
        SysSkillInsuffMsg((int)&v21, 1);
        goto LABEL_68;
    }
    for(i = 0; i <= 1; ++i)
    {
        if(*(_DWORD *)(4 * i + v14 + 8) >= 0)
        {
            if(!CInventory::FindItem(a1 + 792, (int)&v11, (int)&v10, *(_DWORD *)(4 * i + v14 + 8), 0, 0)
                || (v7 = CInventory::GetItem(a1 + 792, v11, v10), *(_DWORD *)(4 * i + v14 + 16) > CItem::Count(v7)))
            {
                SysSkillInsuffMsg((int)&v21, 2);
                goto LABEL_68;
            }
        }
    }
    if(*(_BYTE *)(*(_DWORD *)v15 + 32) & 1 && *(_WORD *)(a1 + 76) > 0)
    {
        SysSkillInvalState((int)&v21, 0);
    }
    else
    {
        if(*(_DWORD *)(*(_DWORD *)v15 + 32) & 2 && !*(_DWORD *)(a1 + 1292))
        {
            SysSkillInvalState((int)&v21, 1);
        }
        else
        {
            if(*(_DWORD *)(*(_DWORD *)v15 + 32) & 0x10 && !*(_DWORD *)(a1 + 1300))
            {
                SysSkillInvalState((int)&v21, 5);
            }
            else
            {
                if(*(_DWORD *)(*(_DWORD *)v15 + 32) & 4 && *(_DWORD *)(*(_DWORD *)v15 + 32) & 0x20
                    || !(*(_DWORD *)(*(_DWORD *)v15 + 32) & 4) && !(*(_DWORD *)(*(_DWORD *)v15 + 32) & 0x20))
                {
LABEL_35:
                    if(*(_DWORD *)(*(_DWORD *)v15 + 32) & 8 && CCharacter::IsInPeaceZone(a1))
                    {
                        SysSkillInvalState((int)&v21, 3);
                    }
                    else
                    {
                        for(i = 0; i <= 2; ++i)
                        {
                            if(*(_DWORD *)(4 * i + *(_DWORD *)v15 + 36) >= 0
                                && !CAssist::Find(
                                            a1 + 148,
                                            *(_DWORD *)(4 * i + *(_DWORD *)v15 + 36),
                                            *(_BYTE *)(i + *(_DWORD *)v15 + 48)))
                            {
                                SysSkillInvalState((int)&v21, 6);
                                goto LABEL_68;
                            }
                        }
                        v8 = *(_BYTE *)(*(_DWORD *)v15 + 28);
                        if(v8 < 3 || v8 > 6 && v8 != 8)
                            goto LABEL_73;
                        v13 = CArea::FindCharInCell(*(_DWORD *)(a1 + 412), a1, v16, v17, 1);
                        if(!v13
                            || *(_BYTE *)(*(_DWORD *)v15 + 28) == 8
                            && (*(_DWORD *)v13
                             || !CPC::IsParty(a1)
                             || !CPC::IsParty(v13)
                             || *(_DWORD *)(v13 + 1368) != *(_DWORD *)(a1 + 1368)))
                        {
                            SysMsg((int)&v21, 12);
                            goto LABEL_68;
                        }
                        v9 = *(float *)(*(_DWORD *)v15 + 24) + 1.0;
                        if(GetDistance(a1, v13) <= v9)
                        {
LABEL_73:
                            CSkill::Ready(v15, v13);
                            *(_DWORD *)(a1 + 424) = v15;
                            SkillReadyMsg((int)&v21, a1, (uint32_t **)v15, v13);
                            CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v21, a1, 1, 4);
                            return CNetMsg::_CNetMsg((int)&v21, 2);
                        }
                        SysMsg((int)&v21, 14);
                    }
                    goto LABEL_68;
                }
                if(*(_DWORD *)(*(_DWORD *)v15 + 32) & 4 && !CPC::IsSetPlayerState(a1, 1))
                {
                    SysSkillInvalState((int)&v21, 4);
                }
                else
                {
                    if(!(*(_DWORD *)(*(_DWORD *)v15 + 32) & 0x20) || !CPC::IsSetPlayerState(a1, 1))
                        goto LABEL_35;
                    SysSkillInvalState((int)&v21, 2);
                }
            }
        }
    }
LABEL_68:
    if(*(_DWORD *)(a1 + 768))
        CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v21);
    return CNetMsg::_CNetMsg((int)&v21, 2);
}

void do_SkillCancel(CPC *a1, CNetMsg &a2)
{
    int result; // eax@3
    char dest; // [sp+13h] [bp-15h]@1
    char v4; // [sp+14h] [bp-14h]@1

    CNetMsg::CNetMsg((int)&v4);
    CNetMsg::MoveFirst(a2);
    CNetMsg::__rs(a2, &dest);
    if(*(_DWORD *)(a1 + 424) && *(_DWORD *)(*(_DWORD *)(a1 + 424) + 8) == 1)
    {
        CSkill::Cancel(*(_DWORD *)(a1 + 424));
        *(_DWORD *)(a1 + 424) = 0;
        SkillCancelMsg((int)&v4, a1);
        CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v4, a1, 1, 4);
        result = CNetMsg::_CNetMsg((int)&v4, 2);
    }
    else
    {
        result = CNetMsg::_CNetMsg((int)&v4, 2);
    }
    return result;
}

void do_SkillFire(CPC *a1, CNetMsg &a2)
{
    int result; // eax@1
    int v3; // eax@2
    int v4; // eax@2
    int v5; // eax@2
    int v6; // eax@2
    int v7; // eax@2
    int v8; // eax@5
    __int64 v9; // qax@51
    int v10; // [sp-24h] [bp-ACh]@47
    int v11; // [sp-18h] [bp-A0h]@47
    int v12; // [sp-14h] [bp-9Ch]@47
    int v13; // [sp-8h] [bp-90h]@0
    char v14; // [sp+2Fh] [bp-59h]@77
    int v15; // [sp+30h] [bp-58h]@23
    int v16; // [sp+34h] [bp-54h]@23
    int i; // [sp+38h] [bp-50h]@3
    int v18; // [sp+3Ch] [bp-4Ch]@2
    char v19[8]; // [sp+40h] [bp-48h]@22
    int v20; // [sp+48h] [bp-40h]@12
    uint32_t *v21; // [sp+4Ch] [bp-3Ch]@11
    int v22; // [sp+50h] [bp-38h]@10
    int v23; // [sp+54h] [bp-34h]@2
    int v24; // [sp+58h] [bp-30h]@2
    char v25; // [sp+5Fh] [bp-29h]@2
    int v26; // [sp+60h] [bp-28h]@2
    char v27; // [sp+67h] [bp-21h]@2
    int v28; // [sp+68h] [bp-20h]@2
    char dest; // [sp+6Ch] [bp-1Ch]@2
    char v30; // [sp+73h] [bp-15h]@2
    int v31; // [sp+74h] [bp-14h]@2

    result = a1;
    if(!*(_BYTE *)(a1 + 474))
    {
        CNetMsg::CNetMsg((int)&v31);
        v25 = 0;
        v24 = 0;
        v23 = 0;
        v18 = 0;
        CNetMsg::MoveFirst(a2);
        v3 = CNetMsg::__rs(a2, &v30);
        v4 = CNetMsg::__rs(v3, &dest);
        v5 = CNetMsg::__rs(v4, &v28);
        v6 = CNetMsg::__rs(v5, &v27);
        v7 = CNetMsg::__rs(v6, &v26);
        CNetMsg::__rs(v7, &v25);
        if(v25 > 0)
        {
            v24 = __builtin_vec_new(v25);
            v23 = __builtin_vec_new(4 * v25);
            for(i = 0; i < v25; ++i)
            {
                v8 = CNetMsg::__rs(a2, (void *)(i + v24));
                CNetMsg::__rs(v8, (void *)(v23 + 4 * i));
            }
        }
        if(!*(_DWORD *)(a1 + 424)
            || ***(_DWORD ***)(a1 + 424) != v28
            || *(_DWORD *)(*(_DWORD *)(a1 + 424) + 8) != 1
            || (v22 = *(_DWORD *)(a1 + 424)) == 0
            || (v21 = *(uint32_t **)v22) == 0
            || (v20 = CSkillProto::Level((int)v21, *(_BYTE *)(v22 + 4))) == 0
            || *(_DWORD *)(v22 + 20) != -1
            && ((v18 = CArea::FindCharInCell(*(_DWORD *)(a1 + 412), a1, v26, v27, 1)) == 0
             || *(_DWORD *)(v22 + 20) != v26
             || *(_DWORD *)(v22 + 16) != v27)
            || *(_WORD *)(a1 + 76) <= *(_WORD *)v20
            || *(_WORD *)(a1 + 80) < *(_WORD *)(v20 + 2))
            goto LABEL_120;
        for(i = 0; i <= 1; ++i)
        {
            *(_DWORD *)&v19[4 * i] = 0;
            if(*(_DWORD *)(4 * i + v20 + 8) >= 0)
            {
                if(!CInventory::FindItem(a1 + 792, (int)&v16, (int)&v15, *(_DWORD *)(4 * i + v20 + 8), 0, 0)
                    || (*(_DWORD *)&v19[4 * i] = CInventory::GetItem(a1 + 792, v16, v15),
                            *(_DWORD *)(4 * i + v20 + 16) > CItem::Count(*(_DWORD *)&v19[4 * i])))
                    goto LABEL_120;
            }
        }
        if(*(_BYTE *)(*(_DWORD *)v22 + 32) & 1 && *(_WORD *)(a1 + 76) > 0
            || *(_DWORD *)(*(_DWORD *)v22 + 32) & 2 && !*(_DWORD *)(a1 + 1292)
            || *(_DWORD *)(*(_DWORD *)v22 + 32) & 0x10 && !*(_DWORD *)(a1 + 1300)
            || (!(*(_DWORD *)(*(_DWORD *)v22 + 32) & 4) || !(*(_DWORD *)(*(_DWORD *)v22 + 32) & 0x20))
            && (*(_DWORD *)(*(_DWORD *)v22 + 32) & 4 || *(_DWORD *)(*(_DWORD *)v22 + 32) & 0x20)
            && (*(_DWORD *)(*(_DWORD *)v22 + 32) & 4 && !CPC::IsSetPlayerState(a1, 1)
             || *(_DWORD *)(*(_DWORD *)v22 + 32) & 0x20 && CPC::IsSetPlayerState(a1, 1))
            || *(_DWORD *)(*(_DWORD *)v22 + 32) & 8 && CCharacter::IsInPeaceZone(a1))
        {
LABEL_120:
            if(*(_DWORD *)(a1 + 424))
            {
                CSkill::Cancel(*(_DWORD *)(a1 + 424));
                *(_DWORD *)(a1 + 424) = 0;
            }
            SkillCancelMsg((int)&v31, a1);
            CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v31, a1, 1, 4);
        }
        else
        {
            for(i = 0; i <= 2; ++i)
            {
                if(*(_DWORD *)(4 * i + *(_DWORD *)v22 + 36) >= 0
                    && !CAssist::Find(a1 + 148, *(_DWORD *)(4 * i + *(_DWORD *)v22 + 36), *(_BYTE *)(i + *(_DWORD *)v22 + 48)))
                    goto LABEL_120;
            }
            CSkill::Fire(v22);
            SkillFireMsg((int)&v31, a1, (uint32_t **)v22, v18, v25, v24, v23);
            CArea::SendToCell(*(_DWORD *)(a1 + 412), (int)&v31, a1, 1, 4);
            *(_WORD *)(a1 + 76) -= *(_WORD *)v20;
            *(_WORD *)(a1 + 80) -= *(_WORD *)(v20 + 2);
            *(_BYTE *)(a1 + 473) = 1;
            for(i = 0; i <= 1; ++i)
            {
                if(*(_DWORD *)&v19[4 * i] && *(_DWORD *)(4 * i + v20 + 16) > 0)
                {
                    CInventory::Decrease(a1 + 792, *(_DWORD *)&v19[4 * i], *(_DWORD *)(4 * i + v20 + 16));
                    v9 = CItem::Count(*(_DWORD *)&v19[4 * i]);
                    if(SHIDWORD(v9) > 0 || !HIDWORD(v9) && (_DWORD)v9)
                    {
                        ItemUpdateMsg((int)&v31, *(_DWORD *)&v19[4 * i], -*(_DWORD *)(4 * i + v20 + 60));
                        if(*(_DWORD *)(a1 + 768))
                            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v31);
                    }
                    else
                    {
                        ItemDeleteMsg((int)&v31, *(_DWORD *)&v19[4 * i]);
                        if(*(_DWORD *)(a1 + 768))
                            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v31);
                        CInventory::Remove(a1 + 792, *(_DWORD *)&v19[4 * i], 1, 1);
                    }
                }
            }
            switch(*((_BYTE *)v21 + 28))
            {
                case 0:
                    ApplySkill(a1, a1, v22, -1);
                    break;
                case 1:
                    LOWORD(v12) = 0;
                    ApplySkillRange(a1, a1, v22, v12, 1, -1, v13);
                    break;
                case 2:
                    ApplySkill(a1, a1, v22, -1);
                    LOWORD(v10) = 1;
                    ApplySkillRange(a1, a1, v22, v10, 0, -1, v11);
                    break;
                case 3:
                    if(v18 && *(_DWORD *)a1 == *(_DWORD *)v18)
                        ApplySkill(a1, v18, v22, -1);
                    break;
                case 4:
                    if(v18
                        && (*(_DWORD *)a1 != *(_DWORD *)v18
                         || !*(_DWORD *)a1 && !*(_DWORD *)v18 && (CPC::IsSetPlayerState(a1, 8) || CPC::IsSetPlayerState(a1, 32))))
                        ApplySkill(a1, v18, v22, -1);
                    for(i = 0; i < v25; ++i)
                    {
                        v14 = 0;
                        v18 = CArea::FindCharInCell(*(_DWORD *)(a1 + 412), a1, *(_DWORD *)(v23 + 4 * i), *(_BYTE *)(i + v24), 1);
                        if(v18)
                        {
                            if(*(_DWORD *)a1)
                            {
                                if(!*(_DWORD *)v18)
                                    v14 = 1;
                            }
                            else
                            {
                                v15 = a1;
                                if(*(_DWORD *)v18 == 1)
                                {
                                    v14 = 1;
                                }
                                else
                                {
                                    if(!*(_DWORD *)v18 && CPC::IsSetPlayerState(v15, 8))
                                        v14 = 1;
                                }
                            }
                            if(v14)
                                ApplySkill(a1, v18, v22, -1);
                        }
                    }
                    break;
                case 5:
                    if(v18)
                    {
                        if(*(_DWORD *)a1 == *(_DWORD *)v18 || *(_DWORD *)(v18 + 60) >= *(_DWORD *)(a1 + 60))
                        {
                            if(!*(_DWORD *)a1
                                && !*(_DWORD *)v18
                                && (CPC::IsSetPlayerState(a1, 8) || CPC::IsSetPlayerState(a1, 32))
                                && *(_DWORD *)(v18 + 60) < *(_DWORD *)(a1 + 60))
                                ApplySkill(a1, v18, v22, -1);
                        }
                        else
                        {
                            ApplySkill(a1, v18, v22, -1);
                        }
                    }
                    break;
                case 6:
                    if(v18)
                    {
                        if(*(_DWORD *)a1 == *(_DWORD *)v18)
                        {
                            if(!*(_DWORD *)a1 && !*(_DWORD *)v18 && (CPC::IsSetPlayerState(a1, 8) || CPC::IsSetPlayerState(a1, 32)))
                            {
                                ApplySkill(a1, v18, v22, -1);
                                LOWORD(v10) = 1;
                                ApplySkillRange(a1, v18, v22, v10, 1, -1, v11);
                            }
                        }
                        else
                        {
                            ApplySkill(a1, v18, v22, -1);
                            LOWORD(v10) = 0;
                            ApplySkillRange(a1, v18, v22, v10, 1, -1, v11);
                        }
                    }
                    break;
                case 7:
                    ApplySkillParty(a1, v22, -1);
                    break;
                case 8:
                    if(v18)
                    {
                        if(!*(_DWORD *)v18)
                        {
                            v15 = v18;
                            if(a1 == v18
                                || *(_DWORD *)(a1 + 1368)
                                && CParty::Find(*(_DWORD *)(a1 + 1368), v15) != -1
                                && CParty::Find(*(_DWORD *)(v15 + 1368), a1) != -1)
                                ApplySkill(a1, v18, v22, -1);
                        }
                    }
                    break;
                default:
                    goto LABEL_120;
            }
        }
        if(v24)
        {
            if(v24)
                __builtin_vec_delete(v24);
            v24 = 0;
            if(v23)
                __builtin_vec_delete(v23);
            v23 = 0;
        }
        result = CNetMsg::_CNetMsg((int)&v31, 2);
    }
    return result;
}
*/
