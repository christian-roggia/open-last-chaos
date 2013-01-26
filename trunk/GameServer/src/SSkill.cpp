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

#include "SSkill.h"
#include "Server.h"

CSSkillProto::CSSkillProto(void)
{
    this->Unk0  = 0;
    this->Unk4  = -1;
    this->Unk8  = -1;
    this->Unk12 = 0;
    this->Unk16 = -1;
    memset(this->Unk20,  0, 20);
    memset(this->Unk40,  0, 20);
    memset(this->Unk68,  0, 20);
    memset(this->Unk88,  0, 20);
    memset(this->Unk108, 0, 20);
    memset(this->Unk128, 0, 20);
    memset(this->Unk148, 0, 20);
    this->Unk60 = 0;
    this->Unk64 = 0;
}

CSSkill::CSSkill(CSSkillProto *a2, char a3)
{
    if(a2)
    {
        this->Unk0 = a2;
        this->Unk4 = a3;
    }
}

CSSkillProtoList::CSSkillProtoList(void)
{
    this->Unk0 = 0;
    this->Unk4 = 0;
}

CSSkillProtoList::~CSSkillProtoList()
{
    delete [] this->Unk0;
    this->Unk0 = 0;
}

bool CSSkillProtoList::Load(void)
{
    CDBCmd v8;

    v8.Init(&gserver.Unk41816);
    v8.SetQuery("SELECT * FROM t_special_skill WHERE a_enable=1 ORDER BY a_index");

    if(v8.Open())
    {
        this->Unk4 = v8.AffectedRows;
        this->Unk0 = new CSSkillProto[this->Unk4]; // CHECK THIS!!!

        if(v8.MoveFirst())
        {
            for(int i = 0; i < this->Unk4; ++i)
            {
                v8.GetRec("a_index", this->Unk0[i].Unk0);
                v8.GetRec("a_job", this->Unk0[i].Unk4);
                v8.GetRec("a_type", this->Unk0[i].Unk8);
                v8.GetRec("a_max_level", this->Unk0[i].Unk12);
                v8.GetRec("a_preference", this->Unk0[i].Unk16);
                for(int j = 0; j <= 4; ++j)
                {
                    strcpy(g_buf, "a_level");
                    IntCat(g_buf, j, 0);
                    strcat(g_buf, "_need_level");
                    v8.GetRec(g_buf, this->Unk0[i].Unk20[j]);
                    strcpy(g_buf, "a_level");
                    IntCat(g_buf, j, 0);
                    strcat(g_buf, "_need_sp");
                    v8.GetRec(g_buf, this->Unk0[i].Unk40[j]);
                    strcpy(g_buf, "a_level");
                    IntCat(g_buf, j, 0);
                    strcat(g_buf, "_num0");
                    v8.GetRec(g_buf, this->Unk0[i].Unk68[j]);
                    strcpy(g_buf, "a_level");
                    IntCat(g_buf, j, 0);
                    strcat(g_buf, "_num1");
                    v8.GetRec(g_buf, this->Unk0[i].Unk88[j]);
                    strcpy(g_buf, "a_level");
                    IntCat(g_buf, j, 0);
                    strcat(g_buf, "_num2");
                    v8.GetRec(g_buf, this->Unk0[i].Unk108[j]);
                    strcpy(g_buf, "a_level");
                    IntCat(g_buf, j, 0);
                    strcat(g_buf, "_num3");
                    v8.GetRec(g_buf, this->Unk0[i].Unk128[j]);
                    strcpy(g_buf, "a_level");
                    IntCat(g_buf, j, 0);
                    strcat(g_buf, "_num4");
                    v8.GetRec(g_buf, this->Unk0[i].Unk148[j]);
                }
                v8.GetRec("a_need_sskill", this->Unk0[i].Unk60);
                v8.GetRec("a_need_sskill_level", this->Unk0[i].Unk64);
                v8.MoveNext();
            }
        }

        return true;
    }

    return false;
}

CSSkillProto *CSSkillProtoList::FindProto(int a2)
{
    CSSkillProto key; // CSSkillProto key = a2; ???
    key.Unk0 = a2; // NOT SURE!!
    return (CSSkillProto *)bsearch(&key, this->Unk0, this->Unk4, sizeof(CSSkillProto), CSSkillProtoList::CompIndex);
}

CSSkill *CSSkillProtoList::Create(int a2, int a3)
{
    CSSkillProto *v7 = this->FindProto(a2);

    if(v7)
    {
        return new CSSkill(v7, a3);
    }
    return 0;
}

CSSkillList::CSSkillList(void)
{
    this->Unk4 = 0;
    this->Unk0 = 0;
}

CSSkillList::~CSSkillList()
{
    CSSkillNode *v2; // ST24_4@3

    this->Unk4 = 0;
    while(this->Unk0)
    {
        v2 = this->Unk0->Unk4;
        delete this->Unk0;
        this->Unk0 = v2;
    }

    this->Unk0 = 0;
}

bool CSSkillList::Add(CSSkill *a2)
{
    CSSkillNode *v5; // [sp+14h] [bp-4h]@3

    if(a2)
    {
        v5 = new CSSkillNode(a2);
        if(this->Unk0)
            this->Unk0->Unk8 = v5;
        v5->Unk4 = this->Unk0;
        v5->Unk8 = 0;
        this->Unk0 = v5;
        ++this->Unk4;

        return true;
    }

    return false;
}

bool CSSkillList::Remove(CSSkill *a2)
{
    CSSkillNode *i;

    if(a2)
    {
        for(i = this->Unk0; i->Unk0->Unk0->Unk0 != a2->Unk0->Unk0; i = i->Unk4)
        {
            if(!i)
                return false;
        }

        if(i->Unk8)
        {
            i->Unk8->Unk4 = i->Unk4;
            if(i->Unk4)
                i->Unk4->Unk8 = i->Unk8;
        }
        else
        {
            this->Unk0 = i->Unk4;
            if(i->Unk4)
                i->Unk4->Unk8 = 0;
        }

        i->Unk8 = 0;
        i->Unk4 = 0;
        --this->Unk4;
        delete i;

        return true;
    }

    return false;
}

CSSkill *CSSkillList::Find(int a2)
{
    for(CSSkillNode *i = this->Unk0; i; i = i->Unk4)
    {
        if(i->Unk0->Unk0->Unk0 == a2)
            return i->Unk0; // *(_DWORD ***)i ----> NOT SURE!
    }

    return 0;
}

char *CSSkillList::GetString(char *dest)
{
    *dest = 0;
    for(CSSkillNode *i = this->Unk0; i; i = i->Unk4)
    {
        IntCat(dest, i->Unk0->Unk0->Unk0, true);
        IntCat(dest, i->Unk0->Unk4, true);
    }

    return dest;
}
