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
#include "Assist.h"
#include "Character.h"
#include "NPC.h"
#include "PC.h"
#include "Skill.h"

CAssistData::CAssistData(int a2, CSkillProto const *a3, int a4, int a5, bool *src)
{
    this->Unk0  = (a2 >= 0) ? a2 : -1;
    this->Unk4  = (CSkillProto *)a3;
    this->Unk8  = a4;
    this->Unk12 = a5;
    memcpy(this->Unk16, src, 3);
    this->Unk20 = 0;
    this->Unk24 = 0;
}

CAssistList::CAssistList(void)
{
    this->Unk0 = 0;
    this->Unk4 = 0;
    this->Unk8 = 0;
    this->Unk12 = 0;
}

CAssistList::~CAssistList()
{
    CAssistData *v2; // ST24_4@2

    while(this->Unk0)
    {
        v2 = this->Unk0->Unk24;
        delete this->Unk0;
        this->Unk0 = v2;
    }

    this->Unk0 = 0;
    this->Unk4 = 0;
}

void CAssistList::Max(int a2)
{
    this->Unk8 = a2;
}

bool CAssistList::Add(int a2, CSkillProto const *a3, int a4, bool *src, int &a6)
{
    CAssistData *v9; // [sp+20h] [bp-8h]@9
    CSkillLevelProto *v10; // [sp+24h] [bp-4h]@3

    if(this->Unk12 >= this->Unk8)
        return false;

    v10 = ((CSkillProto *)a3)->Level(a4);

    if(!v10)
        return false;

    if(v10->Unk4 <= 0)
        return false;

    if(a6 == -1)
      a6 = v10->Unk4;

    v9 = new CAssistData(a2, a3, a4, a6, src);
    if(this->Unk0)
    {
        this->Unk4->Unk24 = v9;
        v9->Unk20 = this->Unk4;
        this->Unk4 = v9;
    }
    else
    {
        this->Unk4 = v9;
        this->Unk0 = v9;
    }

    ++this->Unk12;

    return true;
}

bool CAssistList::CanApply(CSkillProto const *a2, int a3)
{
    CMagicProto *v6; // [sp+2Ch] [bp-14h]@8
    CMagicProto *v7; // [sp+30h] [bp-10h]@11
    CSkillLevelProto *v8; // [sp+34h] [bp-Ch]@5
    CSkillLevelProto *v10; // [sp+3Ch] [bp-4h]@1

    v10 = ((CSkillProto *)a2)->Level(a3);

    if(v10)
        return false;

    for(CAssistData *i = this->Unk0; i; i = i->Unk24)
    {
        v8 = i->Unk4->Level(i->Unk8);
        if(v8)
        {
            for(int j = 0; j <= 2; ++j)
            {
                v6 = v8->Unk88[j];
                if(v6)
                {
                    for(int k = 0; k <= 2; ++k)
                    {
                        v7 = v10->Unk88[k];
                        if(v7 && v7->Unk0 == v6->Unk0 && v10->Unk100[k] < v8->Unk100[j])
                            return false;
                    }
                }
            }
        }
    }

    return true;
}

void CAssistList::DelDuplicate(CSkillProto const *a2, int a3, bool a4, CCharacter *a5)
{
    bool v6; // [sp+1Fh] [bp-21h]@5
    CMagicProto *v9; // [sp+28h] [bp-18h]@9
    CMagicProto *v10; // [sp+2Ch] [bp-14h]@12
    CSkillLevelProto *v11; // [sp+30h] [bp-10h]@4
    CAssistData *v12; // [sp+34h] [bp-Ch]@2
    CAssistData *v13; // [sp+38h] [bp-8h]@3
    CSkillLevelProto *v14; // [sp+3Ch] [bp-4h]@1

    v14 = ((CSkillProto *)a2)->Level(a3);

    if(v14)
    {
        v12 = this->Unk0;
        while(1)
        {
            v13 = v12;

            if(!v12)
                break;

            v12 = v12->Unk24;
            v11 = v13->Unk4->Level(v13->Unk8);

            if(v11)
            {
                v6 = false;
                for(int i = 0; i <= 2 && !v6; ++i)
                {
                    v9 = v11->Unk88[i];
                    if(v9)
                    {
                        for(int j = 0; j <= 2; ++j)
                        {
                            v10 = v14->Unk88[j];
                            if(v10 && v10->Unk0 == v9->Unk0 && v11->Unk100[i] <= v14->Unk100[j])
                            {
                                v6 = true;
                                break;
                            }
                        }
                    }
                }

                if(v6)
                    this->Del(v13, a4, a5);
            }
        }
    }
}

bool CAssistList::DecreaseTime(CCharacter *a2, int *a3)
{
    int v3; // ecx@37
    int v4; // ecx@47
    int v5; // ecx@57
    int v6; // ecx@67

    int v8; // [sp+24h] [bp-24h]@5
    bool v9; // [sp+2Bh] [bp-1Dh]@5
    CMagicLevelProto *v10; // [sp+2Ch] [bp-1Ch]@10
    CMagicProto *v11; // [sp+30h] [bp-18h]@9
    CSkillLevelProto *v12; // [sp+34h] [bp-14h]@4
    CSkillProto *v13; // [sp+38h] [bp-10h]@3
    CAssistData *v14; // [sp+3Ch] [bp-Ch]@1
    CAssistData *v15; // [sp+40h] [bp-8h]@2
    bool v16; // [sp+47h] [bp-1h]@1

    v16 = 0;
    v14 = this->Unk0;

    while(1)
    {
        v15 = v14;

        if(!v14)
          return v16;

        v14 = v14->Unk24;
        v13 = v15->Unk4;

        if(v13)
        {
            v12 = v13->Level(v15->Unk8);

            if(v12)
            {
                v8 = 0;
                v9 = 0;

                while(v8 <= 2 && !v9)
                {
                    v11 = v12->Unk88[v8];

                    if(v11)
                    {
                        v10 = v11->Level(v12->Unk100[v8]);

                        if(v10)
                        {
                            if(v12->Unk88[v8]->Unk5 == 2)
                            {
                                switch(v12->Unk88[v8]->Unk6)
                                {
                                case 0:
                                  if(a2->Unk76 > 1)
                                  {
                                      if(v11->Unk7 == 2)
                                        a2->Unk78 -= v10->Unk0 * (signed int)a2->Unk78 / 10000;
                                      else
                                        a2->Unk78 -= v10->Unk0;
                                      if(a2->Unk78 < 0)
                                        a2->Unk78 = 1;
                                      *a3 |= 1;
                                  }
                                  break;
                                case 5:
                                  if(a2->Unk78 > 1)
                                  {
                                      if(v11->Unk7 == 2)
                                        a2->Unk78 -= v10->Unk0 * (signed int)a2->Unk78 / 10000;
                                      else
                                        a2->Unk78 -= v10->Unk0;
                                      if(a2->Unk78 < 0)
                                        a2->Unk78 = 1;
                                      *a3 |= 0x20;
                                  }
                                  break;
                                case 9:
                                  if(a2->Unk78 < a2->Unk78)
                                  {
                                      if(v11->Unk7 == 2)
                                        a2->Unk78 += v10->Unk0 * (signed int)a2->Unk78 / 10000;
                                      else
                                        a2->Unk78 += v10->Unk0;
                                      if(a2->Unk78 > a2->Unk78)
                                        a2->Unk78 = a2->Unk78;
                                      if(a2->Unk78 < 0)
                                        a2->Unk78 = 1;
                                      //v3 = *a3;
                                      //BYTE1(v3) |= 2;
                                      //*a3 = v3;
                                      *a3 |= 0x200;
                                  }
                                  break;
                                case 10:
                                  if(a2->Unk80 < a2->Unk82)
                                  {
                                      if(v11->Unk7 == 2)
                                        a2->Unk80 += v10->Unk0 * (signed int)a2->Unk82 / 10000;
                                      else
                                        a2->Unk80 += v10->Unk0;
                                      if(a2->Unk80 > a2->Unk82)
                                        a2->Unk80 = a2->Unk82;
                                      if(a2->Unk80 < 0)
                                        a2->Unk80 = 0;
                                      //v4 = *a3;
                                      //BYTE1(v4) |= 4;
                                      //*a3 = v4;
                                      *a3 |= 0x400;
                                  }
                                  break;
                                case 12:
                                  if(a2->Unk78 < a2->Unk78)
                                  {
                                      if(v11->Unk7 == 2)
                                        a2->Unk78 += v10->Unk0 * (signed int)a2->Unk78 / 10000;
                                      else
                                        a2->Unk78 += v10->Unk0;
                                      if(a2->Unk78 > a2->Unk78)
                                      {
                                        a2->Unk78 = a2->Unk78;
                                        v9 = 1;
                                      }
                                      if(a2->Unk78 < 0)
                                      {
                                        a2->Unk78 = 1;
                                        v9 = 1;
                                      }
                                      //v5 = *a3;
                                      //BYTE1(v5) |= 0x10;
                                      //*a3 = v5;
                                      *a3 |= 0x1000;
                                  }
                                  break;
                                case 13:
                                  if(a2->Unk80 < a2->Unk82)
                                  {
                                      if(v11->Unk7 == 2)
                                        a2->Unk80 += v10->Unk0 * (signed int)a2->Unk82 / 10000;
                                      else
                                        a2->Unk80 += v10->Unk0;
                                      if(a2->Unk80 > a2->Unk82)
                                      {
                                        a2->Unk80 = a2->Unk82;
                                        v9 = 1;
                                      }
                                      if(a2->Unk80 < 0)
                                      {
                                        a2->Unk80 = 0;
                                        v9 = 1;
                                      }
                                      //v6 = *a3;
                                      //BYTE1(v6) |= 0x20;
                                      //*a3 = v6;
                                      *a3 |= 0x2000;
                                  }
                                  break;
                                case 1:
                                case 2:
                                case 3:
                                case 4:
                                case 6:
                                case 7:
                                case 8:
                                case 11:
                                case 14:
                                  break;
                                }
                            }
                        }
                    }
                    ++v8;
                }

                v15->Unk12 -= 10;
                if(v15->Unk12 <= 0 || v9)
                {
                    this->Del(v15, 1, a2);
                    v16 = 1;
                }
            }
        }
    }
}

void CAssistList::Apply(_tagAssistValue *a2, _tagAssistValue *a3, int *a4)
{
    //CAssistData *result; // eax@1
    int v5; // ecx@4
    int v30; // ecx@171
    int v31; // ecx@173
    int v32; // ecx@175

    CMagicLevelProto *v35; // [sp+14h] [bp-14h]@15
    CMagicProto *v36; // [sp+18h] [bp-10h]@14
    CSkillLevelProto *v37; // [sp+1Ch] [bp-Ch]@10
    CSkillProto *v38; // [sp+20h] [bp-8h]@9

    for(CAssistData *i = this->Unk0; i; i = i->Unk24)
    {
        switch(i->Unk0)
        {
            case 391:
                *(char *)(a2 + 92) = 1;
                //v5 = *a4;
                //BYTE1(v5) |= 8;
                //*a4 = v5;
                *a4 |= 0x800;
                break;
            case 508:
                *(char *)(a2 + 93) = 1;
                break;
            case 509:
                *(char *)(a2 + 94) = 1;
                break;
            default:
                v38 = i->Unk4;
                if(v38)
                {
                    v37 = v38->Level(i->Unk8);
                    if(v37)
                    {
                        for(int j = 0; j <= 2; ++j)
                        {
                            if(i->Unk16[j])
                            {
                                v36 = v37->Unk88[j];
                                if(v36)
                                {
                                    v35 = v36->Level(v37->Unk100[j]);
                                    if(v35)
                                    {
                                        if(v36->Unk5 == 1)
                                        {
                                            switch(v36->Unk6 - 1)
                                            {
                                                case 0:
                                                    if(v36->Unk7 == 1)
                                                    {
                                                        a2[15] += v35->Unk0;
                                                    }
                                                    else
                                                    {
                                                        if(v36->Unk7 == 2)
                                                            a3[15] += v35->Unk0;
                                                    }
                                                    break;
                                                case 1:
                                                    if(v36->Unk7 == 1)
                                                    {
                                                        a2[16] += v35->Unk0;
                                                    }
                                                    else
                                                    {
                                                        if(v36->Unk7 == 2)
                                                            a3[16] += v35->Unk0;
                                                    }
                                                    break;
                                                case 2:
                                                    if(v36->Unk7 == 1)
                                                    {
                                                        a2[17] += v35->Unk0;
                                                    }
                                                    else
                                                    {
                                                        if(v36->Unk7 == 2)
                                                            a3[17] += v35->Unk0;
                                                    }
                                                    break;
                                                case 3:
                                                    if(v36->Unk7 == 1)
                                                    {
                                                        a2[18] += v35->Unk0;
                                                    }
                                                    else
                                                    {
                                                        if(v36->Unk7 == 2)
                                                            a3[18] += v35->Unk0;
                                                    }
                                                    break;
                                                case 4:
                                                    if(v36->Unk7 == 1)
                                                    {
                                                        a2[19] += v35->Unk0;
                                                    }
                                                    else
                                                    {
                                                        if(v36->Unk7 == 2)
                                                            a3[19] += v35->Unk0;
                                                    }
                                                    break;
                                                case 5:
                                                    if(v36->Unk7 == 1)
                                                    {
                                                        a2[20] += v35->Unk0;
                                                    }
                                                    else
                                                    {
                                                        if(v36->Unk7 == 2)
                                                            a3[20] += v35->Unk0;
                                                    }
                                                    break;
                                                default:
                                                    continue;
                                            }
                                        }
                                        else
                                        {
                                            if(v36->Unk5 > 1)
                                            {
                                                if(v36->Unk5 == 2)
                                                {
                                                    switch(v36->Unk6)
                                                    {
                                                        case 0:
                                                            *a4 |= 1;
                                                            break;
                                                        case 1:
                                                            *a4 |= 2;
                                                            break;
                                                        case 2:
                                                            *a4 |= 4;
                                                            break;
                                                        case 3:
                                                            *a4 |= 8;
                                                            break;
                                                        case 4:
                                                            *a4 |= 0x10;
                                                            break;
                                                        case 5:
                                                            *a4 |= 0x20;
                                                            break;
                                                        case 6:
                                                            *a4 |= 0x40;
                                                            break;
                                                        case 7:
                                                            *a4 |= 0x80;
                                                            break;
                                                        case 8:
                                                            //v30 = *a4;
                                                            //BYTE1(v30) |= 1;
                                                            //*a4 = v30;
                                                            *a4 |= 0x100;
                                                            break;
                                                        case 9:
                                                            *a4 |= 0x200;
                                                            break;
                                                        case 10:
                                                            //v31 = *a4;
                                                            //BYTE1(v31) |= 4;
                                                            //*a4 = v31;
                                                            *a4 |= 0x400;
                                                            break;
                                                        case 11:
                                                            *a4 |= 0x800;
                                                            break;
                                                        case 14:
                                                            //v32 = *a4;
                                                            //BYTE1(v32) |= 0x40;
                                                            //*a4 = v32;
                                                            *a4 |= 0x4000;
                                                            if(v36->Unk7 == 1)
                                                            {
                                                                a2[24] += v35->Unk0;
                                                            }
                                                            else
                                                            {
                                                                if(v36->Unk7 == 2)
                                                                    a3[24] += v35->Unk0;
                                                            }
                                                            break;
                                                        default:
                                                            continue;
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                if(!v36->Unk5)
                                                {
                                                    switch(v36->Unk6)
                                                    {
                                                        case 0:
                                                            if(v36->Unk7 == 1)
                                                            {
                                                                a2[0] += v35->Unk0;
                                                            }
                                                            else
                                                            {
                                                                if(v36->Unk7 == 2)
                                                                    a3[0] += v35->Unk0;
                                                            }
                                                            break;
                                                        case 1:
                                                            if(v36->Unk7 == 1)
                                                            {
                                                                a2[1] += v35->Unk0;
                                                            }
                                                            else
                                                            {
                                                                if(v36->Unk7 == 2)
                                                                    a3[1] += v35->Unk0;
                                                            }
                                                            break;
                                                        case 2:
                                                            if(v36->Unk7 == 1)
                                                            {
                                                                a2[2] += v35->Unk0;
                                                            }
                                                            else
                                                            {
                                                                if(v36->Unk7 == 2)
                                                                    a3[2] += v35->Unk0;
                                                            }
                                                            break;
                                                        case 3:
                                                            if(v36->Unk7 == 1)
                                                            {
                                                                a2[3] += v35->Unk0;
                                                            }
                                                            else
                                                            {
                                                                if(v36->Unk7 == 2)
                                                                    a3[3] += v35->Unk0;
                                                            }
                                                            break;
                                                        case 4:
                                                            if(v36->Unk7 == 1)
                                                            {
                                                                a2[4] += v35->Unk0;
                                                            }
                                                            else
                                                            {
                                                                if(v36->Unk7 == 2)
                                                                    a3[4] += v35->Unk0;
                                                            }
                                                            break;
                                                        case 5:
                                                            if(v36->Unk7 == 1)
                                                            {
                                                                a2[5] += v35->Unk0;
                                                            }
                                                            else
                                                            {
                                                                if(v36->Unk7 == 2)
                                                                    a3[5] += v35->Unk0;
                                                            }
                                                            break;
                                                        case 6:
                                                            if(v36->Unk7 == 1)
                                                            {
                                                                a2[6] += v35->Unk0;
                                                            }
                                                            else
                                                            {
                                                                if(v36->Unk7 == 2)
                                                                    a3[6] += v35->Unk0;
                                                            }
                                                            break;
                                                        case 7:
                                                            if(v36->Unk7 == 1)
                                                            {
                                                                a2[7] += v35->Unk0;
                                                            }
                                                            else
                                                            {
                                                                if(v36->Unk7 == 2)
                                                                    a3[7] += v35->Unk0;
                                                            }
                                                            break;
                                                        case 8:
                                                            if(v36->Unk7 == 1)
                                                            {
                                                                a2[8] += v35->Unk0;
                                                            }
                                                            else
                                                            {
                                                                if(v36->Unk7 == 2)
                                                                    a3[8] += v35->Unk0;
                                                            }
                                                            break;
                                                        case 9:
                                                            if(v36->Unk7 == 1)
                                                            {
                                                                a2[9] += v35->Unk0;
                                                            }
                                                            else
                                                            {
                                                                if(v36->Unk7 == 2)
                                                                    a3[9] += v35->Unk0;
                                                            }
                                                            break;
                                                        case 10:
                                                            if(v36->Unk7 == 1)
                                                            {
                                                                a2[10] += v35->Unk0;
                                                            }
                                                            else
                                                            {
                                                                if(v36->Unk7 == 2)
                                                                    a3[10] += v35->Unk0;
                                                            }
                                                            break;
                                                        case 11:
                                                            if(v36->Unk7 == 1)
                                                            {
                                                                a2[11] += v35->Unk0;
                                                            }
                                                            else
                                                            {
                                                                if(v36->Unk7 == 2)
                                                                    a3[11] += v35->Unk0;
                                                            }
                                                            break;
                                                        case 12:
                                                            if(v36->Unk7 == 1)
                                                            {
                                                                a2[12] += v35->Unk0;
                                                            }
                                                            else
                                                            {
                                                                if(v36->Unk7 == 2)
                                                                    a3[12] += v35->Unk0;
                                                            }
                                                            break;
                                                        case 13:
                                                            if(v36->Unk7 == 1)
                                                            {
                                                                a2[13] += v35->Unk0;
                                                            }
                                                            else
                                                            {
                                                                if(v36->Unk7 == 2)
                                                                    a3[13] += v35->Unk0;
                                                            }
                                                            break;
                                                        case 14:
                                                            if(v36->Unk7 == 1)
                                                            {
                                                                a2[14] += v35->Unk0;
                                                            }
                                                            else
                                                            {
                                                                if(v36->Unk7 == 2)
                                                                    a3[14] += v35->Unk0;
                                                            }
                                                            break;
                                                        case 15:
                                                            if(v36->Unk7 == 1)
                                                            {
                                                                a2[21] += v35->Unk0;
                                                            }
                                                            else
                                                            {
                                                                if(v36->Unk7 == 2)
                                                                    a3[21] += v35->Unk0;
                                                            }
                                                            break;
                                                        case 16:
                                                            if(v36->Unk7 == 1)
                                                            {
                                                                a2[22] += v35->Unk0;
                                                            }
                                                            else
                                                            {
                                                                if(v36->Unk7 == 2)
                                                                    a3[22] += v35->Unk0;
                                                            }
                                                            break;
                                                        default:
                                                            continue;
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
                break;
        }
    }
}

void CAssistList::Del(CAssistData *a2, bool a3, CCharacter *a4)
{
    if(this->Unk0 == a2)
        this->Unk0 = this->Unk0->Unk24;

    if(this->Unk4 == a2)
        this->Unk4 = this->Unk4->Unk20;

    if(a2->Unk20)
        a2->Unk20->Unk24 = a2->Unk24;

    if(a2->Unk24)
        a2->Unk24->Unk20 = a2->Unk20;

    a2->Unk20 = 0;
    a2->Unk24 = 0;

    if(a3)
    {
        CNetMsg v5;

        AssistDelMsg(v5, a4, a2->Unk0, a2->Unk4->Unk0);
        a4->Unk412->SendToCell(v5, a4, 1, 4);
        CharStatusMsg(v5, a4, 0);
        a4->Unk412->SendToCell(v5, a4, 1, 4);
    }

    delete a2;
    --this->Unk12;
}

CAssist::CAssist(void)
{
    this->Unk0 = 0;
    this->Unk4.Max(12);
    this->Unk20.Max(8);
    this->Unk244 = 0;
    this->Unk36 = 10;
    memset(this->Unk40, 0, 100);
    memset(this->Unk140, 0, 100);
    this->Unk240 = 0;
}

CAssist::~CAssist()
{
    ;
}

void CAssist::Init(CCharacter *a2)
{
    this->Unk0 = a2;
}

bool CAssist::Add(int a2, CSkillProto const * a3, int a4, bool *src, bool a6, int a7)
{
    int v11; // [sp+30h] [bp-Ch]@6
    CAssistList *v13; // [sp+38h] [bp-4h]@3

    if(this->CanApply(a3, a4))
    {
        v13 = 0;
        v13 = (a3->Unk12 & 2) ? &this->Unk4 : &this->Unk20;

        v11 = 0;
        for(int i = 0; i <= 2; ++i)
        {
            if(src[i])
            {
                if(((CSkillProto *)a3)->Level(a4)->Unk88[i])
                {
                    if(((CSkillProto *)a3)->Level(a4)->Unk88[i]->Unk5 <= 2)
                    {
                        if(((CSkillProto *)a3)->Level(a4)->Unk88[i]->Unk5 >= 0)
                            ++v11;
                    }
                }
            }
        }

        if(v11)
        {
            this->DelDuplicate(a3, a4, a6);
            if((*v13).Add(a2, a3, a4, src, a7))
            {
                this->Unk244 = this->Unk20.Unk12 + this->Unk4.Unk12;
                if(this->Unk0->Unk0)
                {
                    ((CNPC *)this->Unk0)->ResetStat();
                    this->Apply();
                }
                else
                {
                    ((CPC *)this->Unk0)->CalcStatus(true);
                }

                if(a6)
                {
                    CNetMsg v9;

                    AssistAddMsg(v9, this->Unk0, a2, a3->Unk0, a4, a7);
                    this->Unk0->Unk412->SendToCell(v9, this->Unk0, 1, 4);
                    CharStatusMsg(v9, this->Unk0, 0);
                    this->Unk0->Unk412->SendToCell(v9, this->Unk0, 1, 4);
                }
                return true;
            }
        }
    }

    return false;
}

bool CAssist::CanApply(CSkillProto const *a2, int a3)
{
    bool v4 = false;
    CSkillLevelProto *v5; // [sp+14h] [bp-4h]@3

    if(!a2)
        return false;

    v5 = ((CSkillProto *)a2)->Level(a3);
    if(!v5)
        return 0;

    if(v5->Unk4 <= 9)
        return false;

    if(this->Unk4.CanApply(a2, a3))
    {
        if(this->Unk20.CanApply(a2, a3))
            v4 = true;
    }

    return v4;
}

void CAssist::DelDuplicate(CSkillProto const *a2, int a3, bool a4)
{
    this->Unk4.DelDuplicate(a2, a3, a4, this->Unk0);
    this->Unk20.DelDuplicate(a2, a3, a4, this->Unk0);
}

bool CAssist::DecreaseTime(void)
{
    bool v4; // [sp+33h] [bp-5h]@3
    int src; // [sp+34h] [bp-4h]@3

    if(this->Unk36 <= 1)
    {
        this->Unk36 = 10;
        src = 0;

        v4 = this->Unk4.DecreaseTime(this->Unk0, &src);

        if(this->Unk20.DecreaseTime(this->Unk0, &src))
            v4 = true;

        this->Unk244 = this->Unk20.Unk12 + this->Unk4.Unk12;

        if(v4 || src)
        {
            if(this->Unk0->Unk0)
            {
                ((CNPC *)this->Unk0)->ResetStat();
                this->Apply();
            }
            else
            {
                ((CPC *)this->Unk0)->CalcStatus(true);
            }

            CNetMsg v2;

            CharStatusMsg(v2, this->Unk0, src);
            this->Unk0->Unk412->SendToCell(v2, this->Unk0, 1, 4);
        }

        return v4;
    }

    --this->Unk36;
    return false;
}

void CAssist::Apply(void)
{
    memset(this->Unk40, 0, 100);
    memset(this->Unk140, 0, 100);
    this->Unk240 = 0;
    this->Unk4.Apply(this->Unk40, this->Unk140, &this->Unk240);
    this->Unk20.Apply(this->Unk40, this->Unk140, &this->Unk240);
    this->Unk0->ApplyAssistData(this->Unk40, this->Unk140);
}

void CAssist::Clear(void)
{
    CNetMsg v2;

    while(this->Unk4.Unk0)
        this->Unk4.Del(this->Unk4.Unk0, true, this->Unk0);

    while(this->Unk20.Unk0)
        this->Unk20.Del(this->Unk20.Unk0, true, this->Unk0);

    if(this->Unk0->Unk0)
    {
        ((CNPC *)this->Unk0)->ResetStat();
        this->Apply();
    }
    else
    {
        ((CPC *)this->Unk0)->CalcStatus(true);
    }

    CharStatusMsg(v2, this->Unk0, 0);
    this->Unk0->Unk412->SendToCell(v2, this->Unk0, 1, 4);
}

void CAssist::GetListString(bool a2, char *dest, char *a4, char *a5, char *a6, char *a7, char *a8, char *a9)
{
    CAssistData *v13; // [sp+24h] [bp-4h]@2

    *a9 = 0;
    *a8 = 0;
    *a7 = 0;
    *a6 = 0;
    *a5 = 0;
    *a4 = 0;
    *dest = 0;

    v13 = (a2) ? this->Unk4.Unk0 : this->Unk20.Unk0;

    while(v13)
    {
        IntCat(dest, v13->Unk0,     true);
        IntCat(a4, v13->Unk4->Unk0, true);
        IntCat(a5, v13->Unk8,       true);
        IntCat(a6, v13->Unk12,      true);
        IntCat(a7, ((v13->Unk16[0]) ? 1 : 0), true);
        IntCat(a8, ((v13->Unk16[1]) ? 1 : 0), true);
        IntCat(a9, ((v13->Unk16[2]) ? 1 : 0), true);
        v13 = v13->Unk24;
    }
}

void CAssist::AppendAssistToNetMsg(CNetMsg &a2)
{
    a2.__ls((int )this->Unk240);
    a2.__ls((char)this->Unk244);

    for(CAssistData *i = this->Unk4.Unk0; i; i = i->Unk24)
    {
        a2.__ls((int )i->Unk0);
        a2.__ls((int )i->Unk4->Unk0);
        a2.__ls((char)i->Unk8);
        a2.__ls((int )i->Unk12);
    }

    for(CAssistData *j = this->Unk20.Unk0; j; j = j->Unk24)
    {
        a2.__ls((int )j->Unk0);
        a2.__ls((int )j->Unk4->Unk0);
        a2.__ls((char)j->Unk8);
        a2.__ls((int )j->Unk12);
    }
}

bool CAssist::Find(int a2, int a3)
{
    CSkillLevelProto *v6; // [sp+10h] [bp-8h]@3
    CSkillLevelProto *v7; // [sp+10h] [bp-8h]@14

    for(CAssistData *i = this->Unk4.Unk0; i; i = i->Unk24)
    {
        v6 = i->Unk4->Level(i->Unk8);
        if(v6)
        {
            for(int j = 0; j <= 2; ++j)
            {
                if(v6->Unk88[j] && v6->Unk88[j]->Unk0 == a2 && v6->Unk100[j] >= a3)
                    return true;
            }
        }
    }

    for(CAssistData *k = this->Unk20.Unk0; k; k = k->Unk24)
    {
        v7 = k->Unk4->Level(k->Unk8);
        if(v7)
        {
            for(int l = 0; l <= 2; ++l)
            {
                if(v7->Unk88[l] && v7->Unk88[l]->Unk0 == a2 && v7->Unk100[l] >= a3)
                    return true;
            }
        }
    }

    return false;
}

void CAssist::CancelSleep(void)
{
    this->Cure(8, 99);
}

void CAssist::Cure(int a2, int a3)
{
    CMagicProto *v6; // [sp+18h] [bp-10h]@6
    CMagicProto *v7; // [sp+18h] [bp-10h]@17
    CSkillLevelProto *v8; // [sp+1Ch] [bp-Ch]@3
    CSkillLevelProto *v9; // [sp+1Ch] [bp-Ch]@14
    CAssistData *v10; // [sp+20h] [bp-8h]@1
    CAssistData *v11; // [sp+24h] [bp-4h]@2
    CAssistData *v12; // [sp+24h] [bp-4h]@13

    v10 = this->Unk4.Unk0;
LABEL_2:
    while(1)
    {
        v11 = v10;

        if(!v10)
            break;

        v10 = v10->Unk24;
        v8 = v11->Unk4->Level(v11->Unk8);

        if(v8)
        {
            for(int i = 0; i <= 2; ++i)
            {
                v6 = v8->Unk88[i];
                if(v6 && v6->Unk5 == 2 && v6->Unk6 == a2 && v8->Unk100[i] <= a3)
                {
                    this->Unk4.Del(v11, true, this->Unk0);
                    goto LABEL_2;
                }
            }
        }
    }

LABEL_13:
    while(1)
    {
        v12 = v10;

        if(!v10)
            break;

        v10 = v10->Unk24;
        v9 = v12->Unk4->Level(v12->Unk8);

        if(v9)
        {
            for(int j = 0; j <= 2; ++j)
            {
                v7 = v9->Unk88[j];
                if(v7 && v7->Unk5 == 2 && v7->Unk6 == a2 && v9->Unk100[j] <= a3)
                {
                    this->Unk20.Del(v12, true, this->Unk0);
                    goto LABEL_13;
                }
            }
        }
    }
}
