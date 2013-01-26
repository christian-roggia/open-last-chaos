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

#include "Skill.h"
#include "Server.h"

CMagicLevelProto::CMagicLevelProto(int a2, int a3)
{
    this->Unk0 = a2;
    this->Unk4 = a3;
}

CMagicProto::CMagicProto(int a2, char a3, char a4, char a5, char a6, char a7, char a8, CMagicLevelProto **a9)
{
    this->Unk0  = a2;
    this->Unk4  = a3;
    this->Unk5  = a4;
    this->Unk6  = a5;
    this->Unk7  = a6;
    this->Unk8  = a7;
    this->Unk9  = a8;
    this->Unk12 = a9;
}

CMagicProto::~CMagicProto()
{
    if(this->Unk12)
    {
        for (int i = 0; i < this->Unk4; ++i)
        {
            delete this->Unk12[i];
            this->Unk12[i] = 0;
        }

        this->Unk12 = 0;
    }
}

CMagicLevelProto *CMagicProto::Level(char a2)
{
    return (a2 > 0 && a2 <= this->Unk4) ? this->Unk12[a2 - 1] : 0;
}

CSkillLevelProto::CSkillLevelProto(short a2, short a3, int a4, int *a5, int *a6, int a7, int a8, int *a9, char *a10, int *a11, int *a12, int *a13, char *a14, CMagicProto const **a15, char *a16)
{
    this->Unk0 = a2;
    this->Unk2 = a3;
    this->Unk4 = a4;
    for(int i = 0; i <= 1; ++i)
    {
        this->Unk8[i] = a5[i];
        this->Unk16[i] = a6[i];
    }

    this->Unk24 = a7;
    this->Unk28 = a8;

    for(int j = 0; j <= 2; ++j)
    {
        this->Unk32[j] = a9[j];
        this->Unk44[j] = a10[j];
    }

    for(int k = 0; k <= 2; ++k)
    {
        this->Unk48[k] = a11[k];
        this->Unk60[k] = a12[k];
    }

    for(int l = 0; l <= 2; ++l)
    {
        this->Unk72[l] = a13[l];
        this->Unk84[l] = a14[l]; // check a14[l] (a14[j])
    }

    for(int m = 0; m <= 2; ++m)
    {
        this->Unk88[m]  = (CMagicProto *)a15[m];
        this->Unk100[m] = a16[m];
    }
}

CSkillProto::CSkillProto(int a2, int a3, char a4, int a5, char a6, float a7, float a8, char a9, char a10, int a11, int *a12, char *a13, int a14, int a15, int a16, int a17, int a18, CSkillLevelProto **a19)
{
    this->Unk0  = a2;
    this->Unk4  = a3;
    this->Unk8  = a4;
    this->Unk12 = a5;
    this->Unk16 = a6;
    this->Unk20 = a7;
    this->Unk24 = a8;
    this->Unk28 = a9;
    this->Unk29 = a10;
    this->Unk32 = a11;
    for(int i = 0; i <= 2; ++i)
    {
        this->Unk36[i] = a12[i];
        this->Unk48[i] = a13[i];
    }
    this->Unk52 = a14;
    this->Unk56 = a15;
    this->Unk60 = a16;
    this->Unk64 = a17;
    this->Unk68 = a18;
    this->Unk72 = a19;
}

CSkillProto::~CSkillProto()
{
    if(this->Unk72)
    {
        for(int i = 0; i < this->Unk16; ++i)
        {
            delete this->Unk72[i];
            this->Unk72[i] = 0;
        }

        if(this->Unk72)
            delete this->Unk72;

        this->Unk72 = 0;
    }
}

CSkillLevelProto *CSkillProto::Level(char a2)
{
    return (a2 > 0 && a2 <= this->Unk16) ? this->Unk72[a2 - 1] : 0;
}

bool CSkillProto::IsActive(void)
{
    return (this->Unk8 >= 0) ? ((this->Unk8 <= 2) ? true : ((this->Unk8 <= 5) ? false : false)) : false;
}

bool CSkillProto::IsPassive(void)
{
    switch(this->Unk8)
    {
    case 0:
    case 1:
    case 2:
    case 4:
    case 5:
        return false;
        break;
    case 3:
        return true;
        break;
    default:
        return false;
        break;
    }
}

CMagicProtoList::CMagicProtoList(void)
{
    this->Unk0 = 0;
    this->Unk4 = 0;
}

CMagicProtoList::~CMagicProtoList()
{
    if(this->Unk0)
    {
        for(int i = 0; i < this->Unk4; ++i) // CHECK this->Unk4 (this->Unk0)
        {
            if(this->Unk0[i])
                delete this->Unk0[i];

            this->Unk0[i] = 0;
        }

        if(this->Unk0)
            delete this->Unk0;

        this->Unk0 = 0;
    }
}

bool CMagicProtoList::Load(void)
{
    int v10, v11;
    CMagicLevelProto **v12;
    char v13, v13_1, v13_2, v13_3, v14, v15;
    int v16, v17, v18;
    CDBCmd v19, v20;

    v20.Init(&gserver.Unk41816);
    v19.Init(&gserver.Unk41816);
    v20.SetQuery("SELECT * FROM t_magic ORDER BY a_index");

    if(!v20.Open())
        return false;

    this->Unk4 = v20.AffectedRows;
    if(this->Unk4)
    {
        this->Unk0 = (CMagicProto **)malloc(sizeof(CMagicProto **) * this->Unk4);
        memset(this->Unk0, 0, sizeof(CMagicProto **) * this->Unk4);
        v18 = 0;

        while(v20.MoveNext())
        {
          v20.GetRec("a_index",      v16);
          v20.GetRec("a_maxlevel",   v15);
          v20.GetRec("a_type",       v14);
          v20.GetRec("a_subtype",    v13_3);
          v20.GetRec("a_damagetype", v13_2);
          v20.GetRec("a_hittype",    v13_1);
          v20.GetRec("a_attribute",  v13);
          sprintf(g_buf, "SELECT * FROM t_magicLevel WHERE a_index=%d ORDER BY a_level", v16);
          v19.SetQuery(g_buf);

          if(!v19.Open())
              return false;

          v12 = (CMagicLevelProto **)malloc(sizeof(CMagicLevelProto **) * v15);
          memset(v12, 0, sizeof(CMagicLevelProto **) * v15);
          v17 = 0;

          while(v19.MoveNext())
          {
              v19.GetRec("a_power",   v11);
              v19.GetRec("a_hitrate", v10);
              v12[v17] = new CMagicLevelProto(v11, v10);
              ++v17;
          }

          this->Unk0[v18] = new CMagicProto(v16, v15, v14, v13_3, v13_2, v13_1, v13, v12);
          ++v18;
        }
    }

    return true;
}

CMagicProto *CMagicProtoList::Find(int a2)
{
    int v3, v4, v5;

    v5 = 0;
    v4 = this->Unk4 - 1;

    while(v5 <= v4)
    {
        v3 = (v4 + v5) / 2;
        if(this->Unk0[(v4 + v5) / 2]->Unk0 == a2)
            return this->Unk0[v3];

        if(this->Unk0[v3]->Unk0 >= a2)
            v4 = v3 - 1;
        else
            v5 = v3 + 1;
    }

    return 0;
}

CSkill::CSkill(CSkillProto const *a2, char a3)
{
    this->Unk0  = a2;
    this->Unk4  = a3;
    this->Unk8  = 0;
    this->Unk12 = 0;
    this->Unk16 = -1;
    this->Unk20 = -1;
}

bool CSkill::IsReady(CCharacter *a2)
{
    return (this->Unk8) ? false : ((this->Unk0) ? gserver.Unk41248 - this->Unk12 >= a2->Unk103 + this->Unk0->Unk68 : false);
}

void CSkill::Ready(CCharacter *a2)
{
    this->Unk8 = 1;
    this->Unk12 = gserver.Unk41248;

    if(a2)
    {
        this->Unk16 = a2->Unk0;
        this->Unk20 = a2->Unk4;
    }
    else
    {
        this->Unk16 = -1;
        this->Unk20 = -1;
    }
}

void CSkill::Fire(void)
{
    this->Unk8 = 2;
}

void CSkill::Cancel(void)
{
    this->Unk8 = 0;
    this->Unk16 = -1;
    this->Unk20 = -1;
}

CSkillProtoList::CSkillProtoList(void)
{
    this->Unk0 = 0;
    this->Unk4 = 0;
}

CSkillProtoList::~CSkillProtoList()
{
    if(this->Unk0)
    {
        for(int i = 0; i < this->Unk4; ++i)
        {
            if(this->Unk0[i])
                delete this->Unk0[i];

            this->Unk0[i] = 0;
        }

        if(this->Unk0)
            delete this->Unk0;

        this->Unk0 = 0;
    }
}

bool CSkillProtoList::Load(void)
{
    CMagicProto *v10[3];
    char v13[3];
    int v14[3];
    char v17[3];
    int v18[3], v21[3], v24[3];
    char v27[3];
    int v28[3], v31, v32, v33[2], v35[2], v37;
    short v38, v38_2;
    CSkillLevelProto **v39;
    int v40, v41, v42, v43, v44;
    char v45[3];
    int v46[3], v49;
    char v50, v50_1;
    float v50_2, v51;
    char v52;
    int v52_1;
    char v53;
    int v53_1, v54, v55, v56;

    CDBCmd v57, v58;

    v58.Init(&gserver.Unk41816);
    v57.Init(&gserver.Unk41816);
    v58.SetQuery("SELECT * FROM t_skill ORDER BY a_index");

    if(!v58.Open())
        return false;

    this->Unk4 = v58.AffectedRows;
    if(this->Unk4)
    {
        this->Unk0 = (CSkillProto **)malloc(sizeof(CSkillProto **) * this->Unk4);
        memset(this->Unk0, 0, sizeof(CSkillProto **) * this->Unk4);
    }
    v56 = 0;

    while(v58.MoveNext())
    {
        v58.GetRec("a_index",          v54);
        v58.GetRec("a_job",            v53_1);
        v58.GetRec("a_type",           v53);
        v58.GetRec("a_flag",           v52_1);
        v58.GetRec("a_maxLevel",       v52);
        v58.GetRec("a_appRange",       v51);
        v58.GetRec("a_fireRange",      v50_2);
        v58.GetRec("a_targetType",     v50_1);
        v58.GetRec("a_targetNum",      v50);
        v58.GetRec("a_useState",       v49);
        v58.GetRec("a_useMagicIndex1", v46[0]);
        v58.GetRec("a_useMagicLevel1", v45[0]);
        v58.GetRec("a_useMagicIndex2", v46[1]);
        v58.GetRec("a_useMagicLevel2", v45[1]);
        v58.GetRec("a_useMagicIndex3", v46[2]);
        v58.GetRec("a_useMagicLevel3", v45[2]);
        v58.GetRec("a_appState",       v44);
        v58.GetRec("a_readyTime",      v43);
        v58.GetRec("a_stillTime",      v42);
        v58.GetRec("a_fireTime",       v41);
        v58.GetRec("a_reuseTime",      v40);
        sprintf(g_buf, "SELECT * FROM t_skillLevel WHERE a_index=%d ORDER BY a_level", v54);
        v57.SetQuery(g_buf);

        if(!v57.Open())
            return false;

        v39 = (CSkillLevelProto **)malloc(sizeof(CSkillLevelProto **) * v52);
        memset(v39, 0, sizeof(CSkillLevelProto **) * v52);
        v55 = 0;

        while(v57.MoveNext())
        {
            v57.GetRec("a_needHP",           v38_2);
            v57.GetRec("a_needMP",           v38);
            v57.GetRec("a_durtime",          v37);
            v57.GetRec("a_needItemIndex1",   v35[0]);
            v57.GetRec("a_needItemCount1",   v33[0]);
            v57.GetRec("a_needItemIndex2",   v35[1]);
            v57.GetRec("a_needItemCount2",   v33[1]);
            v57.GetRec("a_learnLevel",       v32);
            v57.GetRec("a_learnSP",          v31);
            v57.GetRec("a_learnSkillIndex1", v28[0]);
            v57.GetRec("a_learnSkillLevel1", v27[0]);
            v57.GetRec("a_learnSkillIndex2", v28[1]);
            v57.GetRec("a_learnSkillLevel2", v27[1]);
            v57.GetRec("a_learnSkillIndex3", v28[2]);
            v57.GetRec("a_learnSkillLevel3", v27[2]);
            v57.GetRec("a_learnItemIndex1",  v24[0]);
            v57.GetRec("a_learnItemCount1",  v21[0]);
            v57.GetRec("a_learnItemIndex2",  v24[1]);
            v57.GetRec("a_learnItemCount2",  v21[1]);
            v57.GetRec("a_learnItemIndex3",  v24[2]);
            v57.GetRec("a_learnItemCount3",  v21[2]);
            v57.GetRec("a_appMagicIndex1",   v18[0]);
            v57.GetRec("a_appMagicLevel1",   v17[0]);
            v57.GetRec("a_appMagicIndex2",   v18[1]);
            v57.GetRec("a_appMagicLevel2",   v17[1]);
            v57.GetRec("a_appMagicIndex3",   v18[2]);
            v57.GetRec("a_appMagicLevel3",   v17[2]);
            v57.GetRec("a_magicIndex1",      v14[0]);
            v57.GetRec("a_magicLevel1",      v13[0]);
            v57.GetRec("a_magicIndex2",      v14[1]);
            v57.GetRec("a_magicLevel2",      v13[1]);
            v57.GetRec("a_magicIndex3",      v14[2]);
            v57.GetRec("a_magicLevel3",      v13[2]);
            v10[0] = gserver.Unk452212.Find(v14[0]);
            v10[1] = gserver.Unk452212.Find(v14[1]);
            v10[2] = gserver.Unk452212.Find(v14[2]);
            v39[v55] = new CSkillLevelProto(v38_2, v38, v37, v35, v33, v32, v31, v28, v27, v24, v21, v18, v17, (const CMagicProto **)v10, v13);
            ++v55;
        }

        this->Unk0[v56] = new CSkillProto(v54, v53_1, v53, v52_1, v52, v51, v50_2, v50_1, v50, v49, v46, v45, v44, v43, v42, v41, v40, v39);
        ++v56;
    }

    return true;
}

CSkillProto *CSkillProtoList::Find(int a2)
{
    int v3, v4, v5;

    v5 = 0;
    v4 = this->Unk4 - 1;

    while(v5 <= v4)
    {
        v3 = (v4 + v5) / 2;

        if(this->Unk0[(v4 + v5) / 2]->Unk0 == a2)
            return this->Unk0[v3];

        if(this->Unk0[v3]->Unk0 >= a2)
            v4 = v3 - 1;
        else
            v5 = v3 + 1;
    }

    return 0;
}

CSkill *CSkillProtoList::Create(int a2, int a3)
{
    CSkillProto *v7 = this->Find(a2);

    if(v7)
    {
        if(v7->Level(a3))
            return new CSkill(v7, a3);
    }

    return 0;
}

CSkillListNode::CSkillListNode(CSkill *a2)
{
    this->Unk0 = a2;
    this->Unk8 = 0;
    this->Unk4 = 0;
}

CSkillListNode *CSkillListNode::prev(void)
{
    return this->Unk4;
}

void CSkillListNode::prev(CSkillListNode *a2)
{
    this->Unk4 = a2;
}

CSkillListNode *CSkillListNode::next(void)
{
    return this->Unk8;
}

void CSkillListNode::next(CSkillListNode *a2)
{
    this->Unk8 = a2;
}

CSkill *CSkillListNode::skill(void)
{
    return this->Unk0;
}

void CSkillListNode::skill(CSkill *a2)
{
    this->Unk0 = a2;
}

CSkillList::CSkillList(void)
{
    this->Unk4 = 0;
    this->Unk0 = 0;
    this->Unk8 = 0;
}

CSkillList::~CSkillList()
{
    CSkillListNode *v2;

    this->Unk8 = 0;
    while(this->Unk0)
    {
        v2 = this->Unk0->next();
        delete this->Unk0;
        this->Unk0 = v2;
    }
    this->Unk4 = 0;
    this->Unk0 = 0;
}

bool CSkillList::Add(CSkill *&a2)
{
    CSkillListNode *v5; // [sp+28h] [bp-8h]@3
    CSkill *v6; // [sp+2Ch] [bp-4h]@1

    v6 = this->Find(a2->Unk0->Unk0);
    if(v6)
    {
        v6->Unk4 = a2->Unk4;
        delete a2;
        a2 = v6;
    }
    else
    {
        v5 = new CSkillListNode(a2);
        if(this->Unk0)
        {
            this->Unk4->next(v5);
            v5->prev(this->Unk4);
            this->Unk4 = v5;
            ++this->Unk8;
        }
        else
        {
            this->Unk4 = v5;
            this->Unk0 = v5;
            this->Unk8 = 1;
        }
    }

    return true;
}

CSkill *CSkillList::Find(int a2)
{
    for(CSkillListNode *i = this->Unk0; i; i = i->next())
    {
        if(i->skill()->Unk0->Unk0 == a2) // CHECK THIS
            return i->skill();
    }

    return 0;
}

int CSkillList::count(void)
{
    return this->Unk8;
}

char *CSkillList::GetIndexString(char *dest)
{
    *dest = 0;

    for(CSkillListNode *i = this->Unk0; i; i = i->next())
        IntCat(dest, i->skill()->Unk0->Unk0, 1); // CHECK THIS

    return dest;
}

char *CSkillList::GetLevelString(char *dest)
{
    *dest = 0;

    for(CSkillListNode *i = this->Unk0; i; i = i->next())
        IntCat(dest, i->skill()->Unk4, 1);

    return dest;
}

CSkillListNode *CSkillList::GetHeadPosition(void)
{
    return this->Unk0;
}

CSkill *CSkillList::GetNext(void *&a2)
{
    CSkillListNode *v3; // [sp+14h] [bp-4h]@1

    v3 = (CSkillListNode *)&a2; // *a2
    if(a2)
    {
        a2 = v3->next();
        return v3->skill();
    }
    else
    {
        a2 = 0;
        return 0;
    }
}

void ApplyMagic(CCharacter *a1, CCharacter *a2, CSkill *a3, int a4)
{
    //char v20; // [sp+1Ch] [bp-4Ch]@66
    CCharacter *v21; // [sp+30h] [bp-38h]@32
    //int v22; // [sp+34h] [bp-34h]@27
    CMagicLevelProto *v24; // [sp+58h] [bp-10h]@7
    CMagicProto *v25; // [sp+5Ch] [bp-Ch]@6
    CSkillLevelProto *v26; // [sp+60h] [bp-8h]@2
    CSkillProto *v27; // [sp+64h] [bp-4h]@1

    v27 = a3->Unk0;
    if(!v27) return;

    v26 = v27->Level(a3->Unk4);
    if(!v26) return;

    if(a4 < 0 || a4 > 2) return;

    v25 = v26->Unk88[a4];
    if(!v25) return;

    v24 = v25->Level(v26->Unk100[a4]);
    if(!v24) return;

    CNetMsg v23;
    if(SelectHitType(a1, a2, 2, 5, v25, v24) != 4) return;

    if(v25->Unk5 == 5)
    {
        switch(v25->Unk6)
        {
            case 0:
                a2->Unk148.Cure(0, v26->Unk100[a4]);
                break;
            case 1:
                a2->Unk148.Cure(1, v26->Unk100[a4]);
                break;
            case 2:
                a2->Unk148.Cure(2, v26->Unk100[a4]);
                break;
            case 3:
                a2->Unk148.Cure(3, v26->Unk100[a4]);
                break;
            case 4:
                a2->Unk148.Cure(4, v26->Unk100[a4]);
                break;
            case 5:
                a2->Unk148.Cure(5, v26->Unk100[a4]);
                break;
            case 6:
                if(a2->Unk76 <= 0)
                {
                    if(!a2->Unk0)
                    {
                        v21 = a2;
                        ((CPC *)a2)->CalcStatus(true);
                    }

                    if(v25->Unk7)
                    {
                        a2->Unk76 = v24->Unk0 * a2->Unk78 / 10000;
                        if(a2->Unk80 < a2->Unk82 / 2)
                            a2->Unk80 = v24->Unk0 * a2->Unk82 / 10000;
                    }
                    else
                    {
                        a2->Unk76 = v24->Unk0;
                        if(a2->Unk80 < a2->Unk82 / 2)
                            a2->Unk80 = v24->Unk0;
                    }

                    CNetMsg v20;

                    RebirthMsg(v20, a2);
                    if(a2->Unk412) a2->Unk412->SendToCell(v20, a2, 1, 4);
                }
                break;
            default:
                break;
        }
    }
    else
    {
        if(v25->Unk5 > 5)
        {
            if(v25->Unk5 == 6)
            {
                if(v25->Unk6)
                {
                    if(v25->Unk6 == 1)
                    {
                        if(a2->Unk424)
                        {
                            if(a2->Unk424->Unk8 == 1)
                            {
                                a2->Unk424->Cancel();
                                a2->Unk424 = 0;

                                SkillCancelMsg(v23, a2);
                                if(a2->Unk412) a2->Unk412->SendToCell(v23, a2, 1, 4);
                            }
                        }
                    }
                }
            }
        }
        else
        {
            if(v25->Unk5 == 4 && a2->Unk76 > 0)
            {
                if(v25->Unk6)
                {
                    if(v25->Unk6 == 1)
                    {
                        if(v25->Unk7 == 1)
                        {
                            g_gamelogbuffer.__ls(init("SYS_ERR"));
                            g_gamelogbuffer.__ls("INVALID MAGIC DATA");
                            g_gamelogbuffer.__ls(delim);
                            g_gamelogbuffer.__ls(v25->Unk0);
                            g_gamelogbuffer.__ls(end);
                            return;
                        }

                        if(v25->Unk7 > 1)
                        {
                            if(v25->Unk7 == 2)
                                a2->Unk80 += v24->Unk0 * a2->Unk82 / 10000;
                        }
                        else
                        {
                            if(!v25->Unk7)
                                a2->Unk80 += v24->Unk0;
                        }

                        if(a2->Unk80 > a2->Unk82)
                            a2->Unk80 = a2->Unk82;

                        if(a2->Unk0)
                        {
                            v21 = a2;
                            CharStatusMsg(v23, a2, 0);
                            v21->Unk412->SendToCell(v23, v21, 0, 4);
                        }
                        else
                        {
                            v21 = a2;
                            ((CPC *)a2)->Unk473 = 1;
                        }
                    }
                }
                else
                {
                    if(v25->Unk7 == 1)
                    {
                        g_gamelogbuffer.__ls(g_gamelogbuffer, init("SYS_ERR"));
                        g_gamelogbuffer.__ls("INVALID MAGIC DATA");
                        g_gamelogbuffer.__ls(delim);
                        g_gamelogbuffer.__ls(v25->Unk0);
                        g_gamelogbuffer.__ls(end);
                        return;
                    }

                    if(v25->Unk7 > 1)
                    {
                        if(v25->Unk7 == 2)
                            a2->Unk76 += v24->Unk0 * a2->Unk78 / 10000;
                    }
                    else
                    {
                        if(!v25->Unk7)
                            a2->Unk76 += v24->Unk0;
                    }

                    if(a2->Unk76 > a2->Unk78)
                        a2->Unk76 = a2->Unk78;

                    if(a2->Unk0)
                    {
                        v21 = a2;
                        CharStatusMsg(v23, a2, 0);
                        v21->Unk412->SendToCell(v23, v21, 0, 4);
                    }
                    else
                    {
                        v21 = a2;
                        ((CPC *)a2)->Unk473 = 1;
                    }
                }
            }
        }
    }
}

void ApplySkill(CCharacter *a1, CCharacter *a2, CSkill *a3, int a4)
{
    CMagicProto *v7; // [sp+Ch] [bp-2Ch]@21
    char v8; // [sp+13h] [bp-25h]@17
    int v9; // [sp+14h] [bp-24h]@8
    char src[2]; // [sp+18h] [bp-20h]@6
    char v11; // [sp+1Ah] [bp-1Eh]@17
    CSkillLevelProto *v13; // [sp+30h] [bp-8h]@4
    CSkillProto *v14; // [sp+34h] [bp-4h]@2

    if(a2->Unk0 || !*(_BYTE *)(a2->Unk474))
    {
        v14 = a3->Unk0;
        if(v14)
        {
            v13 = v14->Level(a3->Unk4);
            if(v13)
            {
                if(v14)
                {
                    CNetMsg src;
                    EffectSkillMsg(src, a2, v14);
                    a2->Unk412->SendToCell(src, a2, 1, 4);
                }

                if(a2->CanApplySkill(v14, v13))
                {
                    v9 = 0;
                    if(v14->Unk8 == 1)
                    {
                        v9 = 1;
                    }
                    else
                    {
                        if(v14->Unk8 > 1)
                        {
                            if(v14->Unk8 == 2)
                                v9 = 2;
                        }
                        else
                        {
                            if(!v14->Unk8)
                                v9 = 0;
                        }
                    }

                    src = 0;
                    v11 = 0;
                    v8  = 0;

                    for(int i = 0; i <= 2 && !v8; ++i)
                    {
                        v7 = v13->Unk88[i];
                        if(v7)
                        {
                            if(v7->Level(v13->Unk100[i]))
                            {
                                if(a4 >= 0)
                                {
                                    src[i] = 1;
                                }
                                else
                                {
                                    src[i] = SelectHitType(a1, a2, 2, 5, v7, v7->Level(v13->Unk100[i])) == 4;
                                }

                                switch(v7->Unk5)
                                {
                                    case 3:
                                        if(a1->Unk0)
                                        {
                                            if(a2->Unk0)
                                            {
                                                if(AttackNPC(a1, a1, v9, a3, i))
                                                    v8 = 1;
                                            }
                                            else
                                            {
                                                if(AttackChar(a1, a2, v9, a3, i))
                                                    v8 = 1;
                                            }
                                        }
                                        else
                                        {
                                            if(a2->Unk0)
                                            {
                                                if(AttackMob(a1, a2, v9, a3, i))
                                                    v8 = 1;
                                            }
                                            else
                                            {
                                                if(AttackPvP(a1, a2, v9, a3, i))
                                                    v8 = 1;
                                            }
                                        }
                                        break;
                                    case 0:
                                    case 1:
                                    case 2:
                                    case 4:
                                    case 5:
                                    case 6:
                                        ApplyMagic(a1, a2, a3, i);
                                        break;
                                    default:
                                        continue;
                                }
                            }
                        }
                    }

                    if(!v8) a2->Unk148.Add(a4, v14, a3->Unk4, src, 1, -1);
                }
            }
        }
    }
}

void ApplySkillRange(CCharacter *a2, CCharacter *a3, CSkill *a4, bool a5, bool a6, int a7)
{
    char v12; // [sp+1Bh] [bp-1Dh]@18
    CCharacter *k; // [sp+1Ch] [bp-1Ch]@12
    int j; // [sp+20h] [bp-18h]@7
    int i; // [sp+24h] [bp-14h]@2
    int v16; // [sp+28h] [bp-10h]@2
    int v17; // [sp+2Ch] [bp-Ch]@2
    int v18; // [sp+30h] [bp-8h]@2

    if(a3->Unk140 >= 0)
    {
        v18 = a3->Unk140 + 4;
        v17 = a3->Unk144 - 4;
        v16 = a3->Unk144 + 4;

        for(i = a3->Unk140 - 4; ; ++i)
        {
            if(i > v18) return;
            if(i >= 0 && i < a3->Unk412->Unk12) break;
LABEL_36:
            ;
        }

        for(j = v17; ; ++j)
        {
            if(j > v16) goto LABEL_36;
            if(j >= 0 && j < a3->Unk412->Unk16) break;
LABEL_35:
            ;
        }

        for(k = a3->Unk412->Unk28[i][j].Unk0; ; k = k->Unk404)
        {
            if(!k) goto LABEL_35;

            if(k->Unk120.Unk16 - a3->Unk120.Unk16 < 0)
            {
                if(a3->Unk120.Unk16 - k->Unk120.Unk16 > 1)
                    continue;
            }
            else
            {
                if(k->Unk120.Unk16 - a3->Unk120.Unk16 > 1)
                    continue;
            }

            v12 = 0;
            if(a5 && a2->Unk0 == k->Unk0) v12 = 1;

            if(a6)
            {
                if(a2->Unk0)
                {
                    if(!k->Unk0)
                        v12 = 1;
                }
                else
                {
                    if(k->Unk0 == 1)
                    {
                        v12 = 1;
                    }
                    else
                    {
                        if(!k->Unk0 && ((CPC *)a2)->IsSetPlayerState(8))
                            v12 = 1;
                    }
                }
            }

            if(v12)
            {
                //long double v8 = GetDistance(a2, k);
                //bool v9 = v8 < a4->Unk0->Unk20;
                //bool v10 = 0;
                //bool v11 = v8 == a4->Unk0->Unk20;
                //if((unsigned __int8)((a1 & 0x45) - 1) < 0x40u)

                if(GetDistance(a2, k) <= a4->Unk0->Unk20) // CHECK
                    ApplySkill(a2, k, a4, a7);
            }
        }
    }
}

void ApplySkillParty(CPC *a1, CSkill *a2, int a3)
{
    if(a1->Unk1368)
    {
        for(int i = 0; ; ++i)
        {
            if(i > 7) return;
            if(a1->Unk1368->GetMember(i))
            {
                if(a1->Unk140 - a1->Unk1368->GetMember(i)->Unk140 >= 0)
                {
                    if(a1->Unk140 - a1->Unk1368->GetMember(i)->Unk140 > 4)
                        continue;
                }
                else
                {
                    if(a1->Unk1368->GetMember(i)->Unk140 - a1->Unk140 > 4)
                        continue;
                }

                if(a1->Unk144 - a1->Unk1368->GetMember(i)->Unk144 >= 0)
                {
                    if(a1->Unk144 - a1->Unk1368->GetMember(i)->Unk144 > 4)
                        continue;

                    ApplySkill(a1, a1->Unk1368->GetMember(i), a2, a3);
                    continue;
                }

                if(a1->Unk1368->GetMember(i)->Unk144 - a1->Unk144 <= 4)
                {
                    ApplySkill(a1, a1->Unk1368->GetMember(i), a2, a3);
                    continue;
                }
            }
        }
    }

    ApplySkill(a1, a1, a2, a3);
}
