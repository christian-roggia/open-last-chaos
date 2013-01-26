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

#include "Area.h"
#include "Server.h"

void CArea::MobActivity(void)
{
    /* TODO */
}

/*void CArea::MobActivity(void)
{
    int result; // eax@2
    int v2; // eax@21
    signed int v3; // eax@25
    int v4; // eax@37
    int v5; // eax@37
    int v6; // edi@68
    int v7; // edi@68
    long double v8; // fst7@70
    float v9; // ST1C_4@72
    long double v10; // fst7@74
    long double v11; // fst7@74
    int v12; // edi@89
    int v13; // edi@89
    long double v14; // fst7@91
    float v15; // ST1C_4@93
    long double v16; // fst7@95
    long double v17; // fst7@95
    __int16 v18; // fps@104
    char v19; // c0@104
    char v20; // c2@104
    char v21; // c3@104
    __int16 v22; // fps@105
    char v23; // c0@105
    char v24; // c2@105
    char v25; // c3@105
    long double v26; // fst7@106
    __int16 v27; // fps@106
    char v28; // c0@106
    char v29; // c2@106
    char v30; // c3@106
    long double v31; // fst7@114
    long double v32; // fst7@118
    float v33; // ST18_4@120
    long double v34; // fst7@122
    int v35; // edi@138
    int v36; // edi@138
    int v37; // edi@152
    int v38; // edi@152
    long double v39; // fst7@154
    float v40; // ST1C_4@156
    long double v41; // fst7@158
    long double v42; // fst7@158
    int v43; // edi@160
    int v44; // edi@160
    int v45; // edi@172
    int v46; // edi@172
    long double v47; // fst7@174
    float v48; // ST1C_4@176
    long double v49; // fst7@178
    long double v50; // fst7@178
    int v51; // edi@180
    int v52; // edi@180
    int v53; // ST20_4@182
    float v54; // ST18_4@182
    float v55; // ST14_4@182
    int v56; // ST20_4@191
    float v57; // ST18_4@191
    float v58; // ST14_4@191

    int v59; // [sp-24h] [bp-DCh]@37
    int v60; // [sp-18h] [bp-D0h]@37
    int v61; // [sp-14h] [bp-CCh]@37
    float v62; // [sp-14h] [bp-CCh]@116
    int v63; // [sp-8h] [bp-C0h]@37
    float v64; // [sp+1Ch] [bp-9Ch]@176
    float v65; // [sp+20h] [bp-98h]@156
    float v66; // [sp+24h] [bp-94h]@146
    float v67; // [sp+28h] [bp-90h]@142
    float v68; // [sp+2Ch] [bp-8Ch]@120
    float v69; // [sp+30h] [bp-88h]@110
    float v70; // [sp+34h] [bp-84h]@93
    float v71; // [sp+38h] [bp-80h]@72
    int i; // [sp+3Ch] [bp-7Ch]@151
    int v73; // [sp+40h] [bp-78h]@151
    char v74; // [sp+47h] [bp-71h]@139
    float v75; // [sp+48h] [bp-70h]@68
    float v76; // [sp+4Ch] [bp-6Ch]@68
    float v77; // [sp+5Ch] [bp-5Ch]@68
    float v78; // [sp+60h] [bp-58h]@68
    unsigned int v79; // [sp+64h] [bp-54h]@68
    char v80; // [sp+6Ah] [bp-4Eh]@65
    char v81; // [sp+6Bh] [bp-4Dh]@65
    float v82; // [sp+6Ch] [bp-4Ch]@65
    float v83; // [sp+70h] [bp-48h]@65
    char v84; // [sp+76h] [bp-42h]@65
    char v85; // [sp+77h] [bp-41h]@65
    float v86; // [sp+78h] [bp-40h]@138
    float v87; // [sp+7Ch] [bp-3Ch]@57
    char v88; // [sp+80h] [bp-38h]@36
    char v89; // [sp+97h] [bp-21h]@24
    int v90; // [sp+98h] [bp-20h]@11
    int v91; // [sp+ACh] [bp-Ch]@1
    int v92; // [sp+B0h] [bp-8h]@1
    int v93; // [sp+B4h] [bp-4h]@2

    v92 = *(_DWORD *)(a1 + 48);
    v91 = 0;
    while(1)
    {
        result = v92;
        v93 = v92;
        if(!v92)
            return result;
        v92 = *(_DWORD *)(v93 + 748);
        v93 = CArea::MobTimeCheck(a1, v93);
        if(v93)
        {
            if(gserver.Unk41248 - *(_DWORD *)(v93 + 116) > 29)
            {
                if(*(_WORD *)(v93 + 76) != *(_WORD *)(v93 + 78) || *(_WORD *)(v93 + 80) != *(_WORD *)(v93 + 82))
                {
                    *(_WORD *)(v93 + 76) += *(_WORD *)(v93 + 112);
                    *(_WORD *)(v93 + 80) += *(_WORD *)(v93 + 114);
                    if(*(_WORD *)(v93 + 76) > *(_WORD *)(v93 + 78))
                        *(_WORD *)(v93 + 76) = *(_WORD *)(v93 + 78);
                    if(*(_WORD *)(v93 + 80) > *(_WORD *)(v93 + 82))
                        *(_WORD *)(v93 + 80) = *(_WORD *)(v93 + 82);
                    CNetMsg::CNetMsg((int)&v90);
                    CharStatusMsg((int)&v90, v93, 0);
                    CArea::SendToCell(a1, (int)&v90, v93, 0, 4);
                    CNetMsg::_CNetMsg((int)&v90, 2);
                }
                *(_DWORD *)(v93 + 116) = gserver.Unk41248;
            }
            if(!(*(_BYTE *)(*(_DWORD *)(v93 + 464) + 92) & 1))
            {
                if(!(*(_DWORD *)(*(_DWORD *)(v93 + 464) + 92) & 0x20))
                {
                    if(!(*(_BYTE *)(*(_DWORD *)(v93 + 464) + 92) & 0x80))
                    {
                        if(!(*(_DWORD *)(*(_DWORD *)(v93 + 464) + 92) & 0x100))
                        {
                            if(!(*(_DWORD *)(*(_DWORD *)(v93 + 464) + 92) & 0x200))
                            {
                                if(!(*(_DWORD *)(*(_DWORD *)(v93 + 464) + 92) & 0x4000))
                                {
                                    if(!(*(_WORD *)(*(_DWORD *)(v93 + 464) + 92) & 0x8000))
                                    {
                                        if(!(*(_WORD *)(*(_DWORD *)(v93 + 464) + 92) & 0x8000))
                                        {
                                            v2 = *(_DWORD *)(*(_DWORD *)(v93 + 464) + 92);
                                            if(!(v2 & 0x10000))
                                            {
                                                if(gserver.Unk41248 - *(_DWORD *)(v93 + 512) >= *(_DWORD *)(v93 + 492))
                                                {
                                                    v89 = 0;
                                                    if(*(_DWORD *)(v93 + 424))
                                                    {
                                                        v3 = *(_DWORD *)(*(_DWORD *)(v93 + 424) + 8);
                                                        if(v3 == 1)
                                                        {
                                                            if(*(_DWORD *)(**(_DWORD **)(v93 + 424) + 60)
                                                                 + *(_DWORD *)(**(_DWORD **)(v93 + 424) + 56)
                                                                 + *(_DWORD *)(*(_DWORD *)(v93 + 424) + 12) <= gserver.Unk41248)
                                                            {
                                                                CNetMsg::CNetMsg((int)&v90);
                                                                if(*(_DWORD *)(*(_DWORD *)(v93 + 424) + 20) != -1)
                                                                {
                                                                    v91 = CArea::FindCharInCell(
                                                                                    *(_DWORD *)(v93 + 412),
                                                                                    v93,
                                                                                    *(_DWORD *)(*(_DWORD *)(v93 + 424) + 20),
                                                                                    *(_DWORD *)(*(_DWORD *)(v93 + 424) + 16),
                                                                                    0);
                                                                    if(!v91 || CCharacter::IsInPeaceZone(v91))
                                                                    {
                                                                        CSkill::Cancel(*(_DWORD *)(v93 + 424));
                                                                        SkillCancelMsg((int)&v90, v93);
                                                                        CArea::SendToCell(*(_DWORD *)(v93 + 412), (int)&v90, v93, 0, 4);
                                                                    }
                                                                }
                                                                if(*(_WORD *)(v93 + 76) >= *(_WORD *)CSkillProto::Level(
                                                                                                                                                 **(_DWORD **)(v93 + 424),
                                                                                                                                                 *(_BYTE *)(*(_DWORD *)(v93 + 424) + 4))
                                                                    && *(_WORD *)(v93 + 80) >= *(_WORD *)(CSkillProto::Level(
                                                                                                                                                    **(_DWORD **)(v93 + 424),
                                                                                                                                                    *(_BYTE *)(*(_DWORD *)(v93 + 424) + 4))
                                                                                                                                            + 2))
                                                                {
                                                                    CSkill::Fire(*(_DWORD *)(v93 + 424));
                                                                    SkillFireMsg((int)&v90, v93, *(uint32_t ***)(v93 + 424), v91, 0, 0, 0);
                                                                    CArea::SendToCell(*(_DWORD *)(v93 + 412), (int)&v90, v93, 0, 4);
                                                                    v4 = CSkillProto::Level(
                                                                                 **(_DWORD **)(v93 + 424),
                                                                                 *(_BYTE *)(*(_DWORD *)(v93 + 424) + 4));
                                                                    *(_WORD *)(v93 + 76) -= *(_WORD *)v4;
                                                                    v5 = CSkillProto::Level(
                                                                                 **(_DWORD **)(v93 + 424),
                                                                                 *(_BYTE *)(*(_DWORD *)(v93 + 424) + 4));
                                                                    *(_WORD *)(v93 + 80) -= *(_WORD *)(v5 + 2);
                                                                    CharStatusMsg((int)&v90, v93, 0);
                                                                    CArea::SendToCell(*(_DWORD *)(v93 + 412), (int)&v90, v93, 0, 4);
                                                                    switch(*(_BYTE *)(**(_DWORD **)(v93 + 424) + 28))
                                                                    {
                                                                        case 0:
                                                                            ApplySkill(v93, v93, *(_DWORD *)(v93 + 424), -1);
                                                                            break;
                                                                        case 1:
                                                                            LOWORD(v61) = 0;
                                                                            ApplySkillRange(v93, v93, *(_DWORD *)(v93 + 424), v61, 1, -1, v63);
                                                                            break;
                                                                        case 2:
                                                                            ApplySkill(v93, v93, *(_DWORD *)(v93 + 424), -1);
                                                                            LOWORD(v59) = 1;
                                                                            ApplySkillRange(v93, v93, *(_DWORD *)(v93 + 424), v59, 0, -1, v60);
                                                                            break;
                                                                        case 3:
                                                                            if(v91 && *(_DWORD *)v93 == *(_DWORD *)v91)
                                                                                ApplySkill(v93, v91, *(_DWORD *)(v93 + 424), -1);
                                                                            break;
                                                                        case 4:
                                                                        case 5:
                                                                            if(v91 && *(_DWORD *)v93 != *(_DWORD *)v91)
                                                                                ApplySkill(v93, v91, *(_DWORD *)(v93 + 424), -1);
                                                                            break;
                                                                        case 6:
                                                                            if(v91)
                                                                            {
                                                                                ApplySkill(v93, v91, *(_DWORD *)(v93 + 424), -1);
                                                                                LOWORD(v59) = 0;
                                                                                ApplySkillRange(v93, v91, *(_DWORD *)(v93 + 424), v59, 1, -1, v60);
                                                                            }
                                                                            break;
                                                                        default:
                                                                            break;
                                                                    }
                                                                }
                                                                else
                                                                {
                                                                    CSkill::Cancel(*(_DWORD *)(v93 + 424));
                                                                    CNetMsg::CNetMsg((int)&v88);
                                                                    SkillCancelMsg((int)&v88, v93);
                                                                    CArea::SendToCell(*(_DWORD *)(v93 + 412), (int)&v88, v93, 0, 4);
                                                                    CNetMsg::_CNetMsg((int)&v88, 2);
                                                                }
                                                                CNetMsg::_CNetMsg((int)&v90, 2);
                                                            }
                                                            v89 = 1;
                                                            *(_DWORD *)(v93 + 512) = gserver.Unk41248;
                                                            *(_DWORD *)(v93 + 492) = 10;
                                                        }
                                                        else
                                                        {
                                                            if(v3 > 1 && v3 == 2)
                                                            {
                                                                if(*(_DWORD *)(**(_DWORD **)(v93 + 424) + 64)
                                                                     + *(_DWORD *)(**(_DWORD **)(v93 + 424) + 60)
                                                                     + *(_DWORD *)(**(_DWORD **)(v93 + 424) + 56)
                                                                     + *(_DWORD *)(*(_DWORD *)(v93 + 424) + 12) <= gserver.Unk41248)
                                                                {
                                                                    CSkill::Cancel(*(_DWORD *)(v93 + 424));
                                                                    *(_DWORD *)(v93 + 424) = 0;
                                                                    *(_DWORD *)(v93 + 512) = gserver.Unk41248;
                                                                    *(_DWORD *)(v93 + 492) = 10;
                                                                }
                                                                v89 = 1;
                                                            }
                                                        }
                                                    }
                                                    if(!v89)
                                                    {
                                                        *(_DWORD *)(v93 + 512) = gserver.Unk41248;
                                                        *(_DWORD *)(v93 + 492) = 10;
                                                        v87 = 0.0;
                                                        if(*(_DWORD *)(v93 + 396))
                                                            v91 = CheckAttackPulse(v93);
                                                        else
                                                            v91 = 0;
                                                        if(!v91)
                                                        {
                                                            if(*(_DWORD *)(*(_DWORD *)(v93 + 464) + 92) & 2)
                                                            {
                                                                if(!*(_DWORD *)(v93 + 488))
                                                                {
                                                                    v91 = CArea::FindNearestPC(a1, v93, (int)&v87);
                                                                    if(v91)
                                                                        AddAttackList(v93, v91, 2);
                                                                }
                                                            }
                                                        }
                                                        v85 = 0;
                                                        v84 = 0;
                                                        v83 = 0.0;
                                                        v82 = 0.0;
                                                        v81 = 0;
                                                        v80 = 0;
                                                        if(v91)
                                                        {
                                                            if(v91)
                                                            {
                                                                *(_BYTE *)(v93 + 497) = 1;
                                                                v83 = atan2(
                                                                                *(float *)(v91 + 124) - *(float *)(v93 + 124),
                                                                                *(float *)(v91 + 120) - *(float *)(v93 + 120));
                                                                if(CArea::IsNotBlocked(a1, v93, v91, 1))
                                                                {
                                                                    v87 = GetDistance(v93, v91);
                                                                    v75 = *(float *)(*(_DWORD *)(v93 + 464) + 312);
                                                                    if(*(_DWORD *)(v93 + 424))
                                                                        v75 = *(float *)(**(_DWORD **)(v93 + 424) + 24);
                                                                    v87 = v87 - v75;
                                                                    if(v87 <= 0.3)
                                                                    {
                                                                        v87 = 0.0;
                                                                        v84 = 1;
                                                                    }
                                                                    if(v87 >= (long double)*(float *)(v93 + 108))
                                                                        v85 = 1;
                                                                    UNDEF(v18);
                                                                    v19 = 0.3 < v87;
                                                                    v20 = 0;
                                                                    v21 = 0.3 == v87;
                                                                    if((HIBYTE(v18) & 0x45) == 1)
                                                                    {
                                                                        UNDEF(v22);
                                                                        v23 = v87 < (long double)*(float *)(v93 + 108);
                                                                        v24 = 0;
                                                                        v25 = v87 == *(float *)(v93 + 108);
                                                                        if((HIBYTE(v22) & 0x45) == 1)
                                                                        {
                                                                            v85 = 1;
                                                                            v26 = *(float *)(v93 + 108) / 2.0;
                                                                            UNDEF(v27);
                                                                            v28 = v87 < v26;
                                                                            v29 = 0;
                                                                            v30 = v87 == v26;
                                                                            if((HIBYTE(v27) & 0x45) == 1)
                                                                                *(_DWORD *)(v93 + 492) = 0;
                                                                        }
                                                                    }
                                                                    v83 = atan2(
                                                                                    *(float *)(v91 + 124) - *(float *)(v93 + 124),
                                                                                    *(float *)(v91 + 120) - *(float *)(v93 + 120));
                                                                    if(v91 && *(_DWORD *)(v91 + 412))
                                                                        v69 = CArea::GetHeight(
                                                                                        *(_DWORD *)(v91 + 412),
                                                                                        *(_BYTE *)(v91 + 136),
                                                                                        *(float *)(v91 + 120),
                                                                                        *(float *)(v91 + 124));
                                                                    else
                                                                        v69 = 0.0;
                                                                    if(v93 && *(_DWORD *)(v93 + 412))
                                                                        v31 = CArea::GetHeight(
                                                                                        *(_DWORD *)(v93 + 412),
                                                                                        *(_BYTE *)(v93 + 136),
                                                                                        *(float *)(v93 + 120),
                                                                                        *(float *)(v93 + 124));
                                                                    else
                                                                        v31 = 0.0;
                                                                    v62 = v31;
                                                                    if(v91 && *(_DWORD *)(v91 + 412))
                                                                        v32 = CArea::GetHeight(
                                                                                        *(_DWORD *)(v91 + 412),
                                                                                        *(_BYTE *)(v91 + 136),
                                                                                        *(float *)(v91 + 120),
                                                                                        *(float *)(v91 + 124));
                                                                    else
                                                                        v32 = 0.0;
                                                                    v33 = v32;
                                                                    v68 = GetDistance(
                                                                                    *(float *)(v91 + 120),
                                                                                    *(float *)(v93 + 120),
                                                                                    *(float *)(v91 + 124),
                                                                                    *(float *)(v93 + 124),
                                                                                    v33,
                                                                                    v62)
                                                                            + 0.1;
                                                                    if(v93 && *(_DWORD *)(v93 + 412))
                                                                        v34 = (v69
                                                                                 - CArea::GetHeight(
                                                                                         *(_DWORD *)(v93 + 412),
                                                                                         *(_BYTE *)(v93 + 136),
                                                                                         *(float *)(v93 + 120),
                                                                                         *(float *)(v93 + 124)))
                                                                                / v68;
                                                                    else
                                                                        v34 = (v69 - 0.0) / v68;
                                                                    v82 = asin(v34);
                                                                }
                                                                else
                                                                {
                                                                    v75 = *(float *)(v93 + 120);
                                                                    v76 = *(float *)(v93 + 124);
                                                                    v81 = 1;
                                                                    v85 = 1;
                                                                    if(*(_DWORD *)(v93 + 520) && *(_BYTE *)(v93 + 524))
                                                                        *(_DWORD *)(v93 + 516) = -*(_DWORD *)(v93 + 516);
                                                                    if(*(_DWORD *)(v93 + 520) <= 3)
                                                                    {
                                                                        if(*(_BYTE *)(v93 + 525))
                                                                            v83 = (long double)*(signed int *)(v93 + 516) * 1.5707964 + v83;
                                                                        else
                                                                            v83 = (long double)*(signed int *)(v93 + 516) * 1.5707964 / 2.0 + v83;
                                                                        *(_BYTE *)(v93 + 524) = 0;
                                                                        *(_BYTE *)(v93 + 497) = 1;
                                                                        v87 = 1.0;
                                                                        *(_DWORD *)(v93 + 492) = 0;
                                                                    }
                                                                    else
                                                                    {
                                                                        v79 = GetRandom(-3141, 3141);
                                                                        v83 = (long double)(signed int)v79 / 1000.0;
                                                                        v87 = *(float *)(v93 + 104);
                                                                        *(_BYTE *)(v93 + 497) = 0;
                                                                        CNPC::InitAIVar(v93);
                                                                    }
                                                                    v12 = v93;
                                                                    v77 = cos(v83);
                                                                    v75 = v77 * v87 + *(float *)(v12 + 120);
                                                                    v13 = v93;
                                                                    v77 = sin(v83);
                                                                    v76 = v77 * v87 + *(float *)(v13 + 124);
                                                                    v78 = CArea::GetHeight(a1, *(_BYTE *)(v93 + 136), v75, v76);
                                                                    if(v93 && *(_DWORD *)(v93 + 412))
                                                                        v14 = CArea::GetHeight(
                                                                                        *(_DWORD *)(v93 + 412),
                                                                                        *(_BYTE *)(v93 + 136),
                                                                                        *(float *)(v93 + 120),
                                                                                        *(float *)(v93 + 124));
                                                                    else
                                                                        v14 = 0.0;
                                                                    v15 = v14;
                                                                    v70 = GetDistance(v75, *(float *)(v93 + 120), v76, *(float *)(v93 + 124), v78, v15)
                                                                            + 0.1;
                                                                    if(v93 && *(_DWORD *)(v93 + 412))
                                                                    {
                                                                        v16 = CArea::GetHeight(
                                                                                        *(_DWORD *)(v93 + 412),
                                                                                        *(_BYTE *)(v93 + 136),
                                                                                        *(float *)(v93 + 120),
                                                                                        *(float *)(v93 + 124));
                                                                        v17 = (v78 - v16) / v70;
                                                                    }
                                                                    else
                                                                    {
                                                                        v17 = (v78 - 0.0) / v70;
                                                                    }
                                                                    v82 = asin(v17);
                                                                }
                                                            }
                                                        }
                                                        else
                                                        {
                                                            if(*(_DWORD *)(v93 + 488) || (signed int)GetRandom(1, 10000) <= 1500)
                                                            {
                                                                v85 = 1;
                                                                v79 = GetRandom(-3141, 3141);
                                                                v83 = (long double)(signed int)v79 / 1000.0;
                                                                v87 = *(float *)(v93 + 104);
                                                                *(_BYTE *)(v93 + 497) = 0;
                                                                v6 = v93;
                                                                v77 = cos(v83);
                                                                v78 = v77 * v87 + *(float *)(v6 + 120);
                                                                v7 = v93;
                                                                v77 = sin(v83);
                                                                v76 = v77 * v87 + *(float *)(v7 + 124);
                                                                v75 = CArea::GetHeight(a1, *(_BYTE *)(v93 + 136), v78, v76);
                                                                if(v93 && *(_DWORD *)(v93 + 412))
                                                                    v8 = CArea::GetHeight(
                                                                                 *(_DWORD *)(v93 + 412),
                                                                                 *(_BYTE *)(v93 + 136),
                                                                                 *(float *)(v93 + 120),
                                                                                 *(float *)(v93 + 124));
                                                                else
                                                                    v8 = 0.0;
                                                                v9 = v8;
                                                                v71 = GetDistance(v78, *(float *)(v93 + 120), v76, *(float *)(v93 + 124), v75, v9) + 0.1;
                                                                if(v93 && *(_DWORD *)(v93 + 412))
                                                                {
                                                                    v10 = CArea::GetHeight(
                                                                                    *(_DWORD *)(v93 + 412),
                                                                                    *(_BYTE *)(v93 + 136),
                                                                                    *(float *)(v93 + 120),
                                                                                    *(float *)(v93 + 124));
                                                                    v11 = (v75 - v10) / v71;
                                                                }
                                                                else
                                                                {
                                                                    v11 = (v75 - 0.0) / v71;
                                                                }
                                                                v82 = asin(v11);
                                                            }
                                                        }
                                                        if(!(*(_DWORD *)(*(_DWORD *)(v93 + 464) + 92) & 8)
                                                            || !(unsigned __int8)(*(int (__cdecl **)(int))(*(_DWORD *)(v93 + 460) + 12))(v93))
                                                            v85 = 0;
                                                        if(!(*(_DWORD *)(*(_DWORD *)(v93 + 464) + 92) & 4)
                                                            || !(unsigned __int8)(*(int (__cdecl **)(int))(*(_DWORD *)(v93 + 460) + 16))(v93))
                                                            v84 = 0;
                                                        if(v85)
                                                        {
                                                            *(_BYTE *)(v93 + 504) = 0;
                                                            if(*(_BYTE *)(v93 + 497))
                                                            {
                                                                if(v87 > (long double)*(float *)(v93 + 108))
                                                                    v87 = *(float *)(v93 + 108);
                                                            }
                                                            else
                                                            {
                                                                if(v87 > (long double)*(float *)(v93 + 104))
                                                                    v87 = *(float *)(v93 + 104);
                                                            }
                                                            v77 = cos(v82);
                                                            v86 = v77 * v87;
                                                            v35 = v93;
                                                            v77 = cos(v83);
                                                            v75 = v77 * v86 + *(float *)(v35 + 120);
                                                            v36 = v93;
                                                            v77 = sin(v83);
                                                            v76 = v77 * v86 + *(float *)(v36 + 124);
                                                            if(v91)
                                                                v74 = *(_BYTE *)(v91 + 136);
                                                            else
                                                                v74 = *(_BYTE *)(v93 + 136);
                                                            if(v91)
                                                                goto LABEL_163;
                                                            v67 = (long double)*(signed int *)(v93 + 508);
                                                            if(*(float *)(v93 + 476) - v75 >= 0.0)
                                                            {
                                                                if(*(float *)(v93 + 476) - v75 <= (long double)v67)
                                                                    goto LABEL_146;
                                                            }
                                                            else
                                                            {
                                                                if(-(*(float *)(v93 + 476) - v75) <= (long double)v67)
                                                                {
LABEL_146:
                                                                    v66 = (long double)*(signed int *)(v93 + 508);
                                                                    if(*(float *)(v93 + 484) - v76 >= 0.0)
                                                                    {
                                                                        if(*(float *)(v93 + 484) - v76 <= (long double)v66)
                                                                            goto LABEL_162;
                                                                    }
                                                                    else
                                                                    {
                                                                        if(-(*(float *)(v93 + 484) - v76) <= (long double)v66)
                                                                        {
LABEL_162:
                                                                            *(_DWORD *)(v93 + 500) = 0;
LABEL_163:
                                                                            if(CCharacter::IsInPeaceZone(v93))
                                                                            {
                                                                                if(v91)
                                                                                {
                                                                                    for(i = *(_DWORD *)(v93 + 396); i; i = *(_DWORD *)(i + 20))
                                                                                    {
                                                                                        if(*(_DWORD *)(i + 16) == v91)
                                                                                            *(_DWORD *)(i + 4) = 0;
                                                                                    }
                                                                                }
                                                                                v80 = 1;
                                                                                if(*(_DWORD *)(v93 + 500) <= 3)
                                                                                {
                                                                                    v83 = atan2(
                                                                                                    *(float *)(v93 + 484) - *(float *)(v93 + 124),
                                                                                                    *(float *)(v93 + 476) - *(float *)(v93 + 120));
                                                                                    v45 = v93;
                                                                                    v77 = cos(v83);
                                                                                    v75 = v77 * *(float *)(v93 + 108) + *(float *)(v45 + 120);
                                                                                    v46 = v93;
                                                                                    v77 = sin(v83);
                                                                                    v76 = v77 * *(float *)(v93 + 108) + *(float *)(v46 + 124);
                                                                                    v78 = CArea::GetHeight(a1, *(_BYTE *)(v93 + 136), v75, v76);
                                                                                    if(v93 && *(_DWORD *)(v93 + 412))
                                                                                        v47 = CArea::GetHeight(
                                                                                                        *(_DWORD *)(v93 + 412),
                                                                                                        *(_BYTE *)(v93 + 136),
                                                                                                        *(float *)(v93 + 120),
                                                                                                        *(float *)(v93 + 124));
                                                                                    else
                                                                                        v47 = 0.0;
                                                                                    v48 = v47;
                                                                                    v64 = GetDistance(
                                                                                                    v75,
                                                                                                    *(float *)(v93 + 120),
                                                                                                    v76,
                                                                                                    *(float *)(v93 + 124),
                                                                                                    v78,
                                                                                                    v48)
                                                                                            + 0.1;
                                                                                    if(v93 && *(_DWORD *)(v93 + 412))
                                                                                    {
                                                                                        v49 = CArea::GetHeight(
                                                                                                        *(_DWORD *)(v93 + 412),
                                                                                                        *(_BYTE *)(v93 + 136),
                                                                                                        *(float *)(v93 + 120),
                                                                                                        *(float *)(v93 + 124));
                                                                                        v50 = (v78 - v49) / v64;
                                                                                    }
                                                                                    else
                                                                                    {
                                                                                        v50 = (v78 - 0.0) / v64;
                                                                                    }
                                                                                    v82 = asin(v50);
                                                                                    v77 = cos(v82);
                                                                                    v86 = v77 * v87;
                                                                                    v51 = v93;
                                                                                    v77 = cos(v83);
                                                                                    v75 = v77 * v86 + *(float *)(v51 + 120);
                                                                                    v52 = v93;
                                                                                    v77 = sin(v83);
                                                                                    v76 = v77 * v86 + *(float *)(v52 + 124);
                                                                                    *(_BYTE *)(v93 + 497) = 1;
                                                                                }
                                                                                else
                                                                                {
                                                                                    CNetMsg::CNetMsg((int)&v90);
                                                                                    DisappearMsg((int)&v90, v93);
                                                                                    CArea::SendToCell(a1, (int)&v90, v93, 0, 4);
                                                                                    CArea::CharFromCell(a1, v93);
                                                                                    *(float *)(v93 + 120) = *(float *)(v93 + 476);
                                                                                    *(_BYTE *)(v93 + 136) = *(_BYTE *)(v93 + 480);
                                                                                    *(float *)(v93 + 124) = *(float *)(v93 + 484);
                                                                                    CArea::PointToCellNum(
                                                                                        a1,
                                                                                        *(float *)(v93 + 120),
                                                                                        *(float *)(v93 + 124),
                                                                                        (int)&i,
                                                                                        (int)&v73);
                                                                                    CArea::CharToCell(a1, v93, *(_BYTE *)(v93 + 136), i, v73);
                                                                                    AppearMsg((int)&v90, v93, 0);
                                                                                    CArea::SendToCell(a1, (int)&v90, v93, 0, 4);
                                                                                    CNPC::InitAIVar(v93);
                                                                                    CNetMsg::_CNetMsg((int)&v90, 2);
                                                                                }
                                                                            }
                                                                            if(*(_BYTE *)(v93 + 497))
                                                                            {
                                                                                v53 = v91;
                                                                                v54 = v83;
                                                                                v55 = CArea::GetHeight(a1, v74, v75, v76);
                                                                                if(!CArea::MoveChar(a1, v93, v74, v75, v76, v55, v54, 1, v53))
                                                                                {
                                                                                    if(v81)
                                                                                    {
                                                                                        ++*(_DWORD *)(v93 + 520);
                                                                                        *(_BYTE *)(v93 + 524) = 1;
                                                                                    }
                                                                                    if(!*(_BYTE *)(v93 + 525))
                                                                                        *(_BYTE *)(v93 + 525) = 1;
                                                                                    if(v80)
                                                                                        ++*(_DWORD *)(v93 + 500);
                                                                                    *(_BYTE *)(v93 + 504) = 1;
                                                                                }
                                                                            }
                                                                            else
                                                                            {
                                                                                v56 = v91;
                                                                                v57 = v83;
                                                                                v58 = CArea::GetHeight(a1, v74, v75, v76);
                                                                                if(!CArea::MoveChar(a1, v93, v74, v75, v76, v58, v57, 0, v56))
                                                                                    *(_BYTE *)(v93 + 504) = 1;
                                                                            }
                                                                            if(v91)
                                                                            {
                                                                                for(i = *(_DWORD *)(v93 + 396); i; i = *(_DWORD *)(i + 20))
                                                                                {
                                                                                    if(*(_DWORD *)(i + 16) == v91)
                                                                                    {
                                                                                        --*(_DWORD *)(i + 4);
                                                                                        if(*(_DWORD *)(i + 4) <= 0)
                                                                                            *(_DWORD *)(i + 4) = 0;
                                                                                    }
                                                                                }
                                                                            }
                                                                            goto LABEL_200;
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                            v80 = 1;
                                                            if(*(_DWORD *)(v93 + 500) <= 3)
                                                            {
                                                                v83 = atan2(
                                                                                *(float *)(v93 + 484) - *(float *)(v93 + 124),
                                                                                *(float *)(v93 + 476) - *(float *)(v93 + 120));
                                                                v37 = v93;
                                                                v77 = cos(v83);
                                                                v75 = v77 * *(float *)(v93 + 108) + *(float *)(v37 + 120);
                                                                v38 = v93;
                                                                v77 = sin(v83);
                                                                v76 = v77 * *(float *)(v93 + 108) + *(float *)(v38 + 124);
                                                                v78 = CArea::GetHeight(a1, *(_BYTE *)(v93 + 136), v75, v76);
                                                                if(v93 && *(_DWORD *)(v93 + 412))
                                                                    v39 = CArea::GetHeight(
                                                                                    *(_DWORD *)(v93 + 412),
                                                                                    *(_BYTE *)(v93 + 136),
                                                                                    *(float *)(v93 + 120),
                                                                                    *(float *)(v93 + 124));
                                                                else
                                                                    v39 = 0.0;
                                                                v40 = v39;
                                                                v65 = GetDistance(v75, *(float *)(v93 + 120), v76, *(float *)(v93 + 124), v78, v40)
                                                                        + 0.1;
                                                                if(v93 && *(_DWORD *)(v93 + 412))
                                                                {
                                                                    v41 = CArea::GetHeight(
                                                                                    *(_DWORD *)(v93 + 412),
                                                                                    *(_BYTE *)(v93 + 136),
                                                                                    *(float *)(v93 + 120),
                                                                                    *(float *)(v93 + 124));
                                                                    v42 = (v78 - v41) / v65;
                                                                }
                                                                else
                                                                {
                                                                    v42 = (v78 - 0.0) / v65;
                                                                }
                                                                v82 = asin(v42);
                                                                v77 = cos(v82);
                                                                v86 = v77 * v87;
                                                                v43 = v93;
                                                                v77 = cos(v83);
                                                                v75 = v77 * v86 + *(float *)(v43 + 120);
                                                                v44 = v93;
                                                                v77 = sin(v83);
                                                                v76 = v77 * v86 + *(float *)(v44 + 124);
                                                                *(_BYTE *)(v93 + 497) = 1;
                                                            }
                                                            else
                                                            {
                                                                CNetMsg::CNetMsg((int)&v90);
                                                                DisappearMsg((int)&v90, v93);
                                                                CArea::SendToCell(a1, (int)&v90, v93, 0, 4);
                                                                CArea::CharFromCell(a1, v93);
                                                                *(float *)(v93 + 120) = *(float *)(v93 + 476);
                                                                *(_BYTE *)(v93 + 136) = *(_BYTE *)(v93 + 480);
                                                                *(float *)(v93 + 124) = *(float *)(v93 + 484);
                                                                CArea::PointToCellNum(
                                                                    a1,
                                                                    *(float *)(v93 + 120),
                                                                    *(float *)(v93 + 124),
                                                                    (int)&v73,
                                                                    (int)&i);
                                                                CArea::CharToCell(a1, v93, *(_BYTE *)(v93 + 136), v73, i);
                                                                AppearMsg((int)&v90, v93, 0);
                                                                CArea::SendToCell(a1, (int)&v90, v93, 0, 4);
                                                                CNPC::InitAIVar(v93);
                                                                CNetMsg::_CNetMsg((int)&v90, 2);
                                                            }
                                                            goto LABEL_163;
                                                        }
LABEL_200:
                                                        if(*(_BYTE *)(v93 + 526))
                                                        {
                                                            v84 = 1;
                                                            *(_BYTE *)(v93 + 526) = 0;
                                                        }
                                                        if(v84)
                                                        {
                                                            CNPC::InitAIVar(v93);
                                                            if(!*(_BYTE *)(v93 + 504))
                                                            {
                                                                CNetMsg::CNetMsg((int)&v90);
                                                                MoveMsg((int)&v90, 3, v93);
                                                                *(_BYTE *)(v93 + 504) = 1;
                                                                CArea::SendToCell(a1, (int)&v90, v93, 0, 4);
                                                                CNetMsg::_CNetMsg((int)&v90, 2);
                                                            }
                                                            if(v91)
                                                            {
                                                                for(i = *(_DWORD *)(v93 + 396); i; i = *(_DWORD *)(i + 20))
                                                                {
                                                                    if(*(_DWORD *)(i + 16) == v91)
                                                                        ++*(_DWORD *)(i + 4);
                                                                }
                                                                if(!*(_DWORD *)(v93 + 424) || *(_DWORD *)(*(_DWORD *)(v93 + 424) + 8))
                                                                {
                                                                    *(_DWORD *)(v93 + 492) = 15 * *(_BYTE *)(*(_DWORD *)(v93 + 464) + 309) / 10;
                                                                    AttackChar(v93, v91, 0, *(_DWORD *)(v93 + 424), 0);
                                                                }
                                                                else
                                                                {
                                                                    CSkill::Ready(*(_DWORD *)(v93 + 424), v91);
                                                                    CNetMsg::CNetMsg((int)&v90);
                                                                    SkillReadyMsg((int)&v90, v93, *(uint32_t ***)(v93 + 424), v91);
                                                                    CArea::SendToCell(*(_DWORD *)(v93 + 412), (int)&v90, v93, 0, 4);
                                                                    *(_DWORD *)(v93 + 512) = gserver.Unk41248;
                                                                    *(_DWORD *)(v93 + 492) = 0;
                                                                    CNetMsg::_CNetMsg((int)&v90, 2);
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
}*/

CPC *CArea::FindNearestPC(CNPC *a2, float *a3)
{
    return 0; // TODO
}

/*CPC *CArea::FindNearestPC(CNPC *a2, float *a3)
{
    int v3; // eax@1
    int v4; // eax@4
    int v5; // eax@6
    int v6; // eax@9
    int v8; // [sp+24h] [bp-30h]@15
    int i; // [sp+28h] [bp-2Ch]@13
    int v10; // [sp+2Ch] [bp-28h]@11
    float v11; // [sp+34h] [bp-20h]@11
    int v12; // [sp+3Ch] [bp-18h]@11
    int v13; // [sp+40h] [bp-14h]@8
    int v14; // [sp+44h] [bp-10h]@6
    int v15; // [sp+48h] [bp-Ch]@3
    int v16; // [sp+4Ch] [bp-8h]@1
    int v17; // [sp+50h] [bp-4h]@1

    CArea::PointToCellNum(a1, *(float *)(a2 + 120), *(float *)(a2 + 124), (int)&v17, (int)&v16);
    v3 = v17 - 4;
    if(v17 - 4 < 0)
        v3 = 0;
    v15 = v3;
    if(v17 + 4 >= *(_DWORD *)(a1 + 12))
        v4 = *(_DWORD *)(a1 + 12) - 1;
    else
        v4 = v17 + 4;
    v14 = v4;
    v5 = v16 - 4;
    if(v16 - 4 < 0)
        v5 = 0;
    v13 = v5;
    if(v16 + 4 >= *(_DWORD *)(a1 + 16))
        v6 = *(_DWORD *)(a1 + 16) - 1;
    else
        v6 = v16 + 4;
    v12 = v6;
    v11 = *(float *)(*(_DWORD *)(a2 + 464) + 68);
    v10 = v15;
LABEL_12:
    if(v10 <= v14)
    {
        for(i = v13; ; ++i)
        {
            if(i > v12)
            {
                ++v10;
                goto LABEL_12;
            }
            v8 = *(_DWORD *)(16 * i + *(_DWORD *)(*(_DWORD *)(a1 + 28) + 4 * v10));
            while(v8)
            {
                if(*(_DWORD *)v8 || *(_WORD *)(v8 + 76) <= 0 || *(_BYTE *)(v8 + 474))
                {
LABEL_26:
                    v8 = *(_DWORD *)(v8 + 404);
                }
                else
                {
                    if(CPC::IsSetPlayerState(v8, 64))
                    {
                        v8 = *(_DWORD *)(v8 + 404);
                    }
                    else
                    {
                        if(v11 <= GetDistance(v8, a2))
                            goto LABEL_26;
                        if(CArea::IsNotBlocked(a1, a2, v8, 0))
                        {
                            *(float *)a3 = GetDistance(v8, a2);
                            return v8;
                        }
                        v8 = *(_DWORD *)(v8 + 404);
                    }
                }
            }
        }
    }
    return 0;
}*/

CNPC *CArea::MobTimeCheck(CNPC *a2)
{
    if(a2)
    {
        a2->Unk148.DecreaseTime();
        a2->Unk148.DecreaseTime();

        if(!a2->Unk488)
            return a2;

        if(a2->Unk488 <= 0)
            return 0;

        if(--a2->Unk488 <= 0)
        {
            CNetMsg v3;

            AppearMsg(v3, a2, 1);
            this->SendToCell(v3, a2, false, 4);
        }

        return a2;
    }

    return 0;
}

void CArea::AddNPC(CNPC *a2)
{
    if(a2->Unk468 >= 0)
    {
        if(this->Unk48)
            this->Unk48->Unk744 = a2;

        a2->Unk748  = this->Unk48;
        a2->Unk744  = 0;
        this->Unk48 = a2;
        a2->Unk408  = this->Unk4;
        a2->Unk412  = this;
        ++this->Unk52;
    }
}

void CArea::DelNPC(CNPC *a2)
{
    if(a2->Unk412 == this)
    {
        if(a2->Unk744)
        {
            a2->Unk744->Unk748 = a2->Unk748;
            if(a2->Unk748)
                a2->Unk748->Unk744 = a2->Unk744;
        }
        else
        {
            this->Unk48 = a2->Unk748;
            if(a2->Unk748)
                a2->Unk748->Unk744 = 0;
        }

        a2->Unk744 = 0;
        a2->Unk748 = 0;

        if(a2->Unk752)
        {
            a2->Unk752->Unk36 = gserver.Unk41248;
            a2->Unk752->Unk32 = 0;
        }

        a2->Unk408 = 0;
        a2->Unk412 = 0;
        a2->DeleteNPC();
        --this->Unk52;
    }
}

void CArea::MobRegen(void)
{
    int v4; // [sp+24h] [bp-14h]@13
    int v5; // [sp+28h] [bp-10h]@13
    CNPC *v6; // [sp+2Ch] [bp-Ch]@8
    CNPCRegenInfo *v7; // [sp+30h] [bp-8h]@3

    for(int i = 0; i < this->Unk32.Unk8; ++i)
    {
        v7 = &this->Unk32.Unk4[i];
        if(v7 && v7->Unk36 && gserver.Unk41248 - v7->Unk36 >= v7->Unk24 && (v7->Unk28 == -1 || v7->Unk40 < v7->Unk28))
        {
            v6 = gserver.Unk452200.Create(v7->Unk0);
            if(v6)
            {
                v6->Unk120.Unk0 = v7->Unk8;
                v6->Unk120.Unk16 = v7->Unk12;
                v6->Unk120.Unk4 = v7->Unk16;
                v6->Unk120.Unk12 = (v6->Unk464->Unk92 & 4) ? (GetRandom(0, 62831) / 10000) : v7->Unk20;
                v6->Unk120.Unk12 = GetRandom(0, 62831) / 10000;
                v6->Unk476 = v6->Unk120.Unk0;
                v6->Unk480 = v6->Unk120.Unk16;
                v6->Unk484 = v6->Unk120.Unk4;
                v6->Unk116 = gserver.Unk41248;
                v6->Unk740 = 0;
                v6->Unk752 = v7;
                v7->Unk32 = 1;
                ++v7->Unk40;
                v7->Unk36 = 0;

                v6->InitPointsToMax();

                v6->Unk488 = 30;

                this->AddNPC(v6);
                this->PointToCellNum(v6->Unk120.Unk0, v6->Unk120.Unk4, &v5, &v4);
                this->CharToCell(v6, v6->Unk120.Unk16, v5, v4);
            }
            else
            {
                v7->Unk28 = 0;
            }
        }
    }
}
