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

#include "DBThread.h"
#include "Server.h"

char skillIndex_641[256];
char skillLevel_642[256];
char questIndex_643[256];
char questValue_644[256];
char questComplete_645[256];
char strSSkill_646[256];
char assistitem[256];
char assistskill[256];
char assistlevel[256];
char assistremain[256];
char assisthit0[256];
char assisthit1[256];
char assisthit2[256];

CCharDBQ::CCharDBQ(void)
{
    this->Unk400032 = 0;
    this->Unk400028 = 0;
}

CCharDBQ::~CCharDBQ()
{
    this->Unk400032 = 0;
    this->Unk400028 = 0;
}

CDescriptor *CCharDBQ::GetFromQ(void)
{
    CDescriptor *v3; // [sp+20h] [bp-Ch]@1

    CMutex(&this->Unk400000, true);
    v3 = 0;

    while(!this->IsEmpty() && !v3)
    {
        v3 = this->Unk0[this->Unk400028];
        this->Unk400028 = (this->Unk400028 + 1) / 100000;
        this->Unk400028 = (this->Unk400028 + 1) - 100000 * this->Unk400028;
    }

    return v3;
}

bool CCharDBQ::AddToQ(CDescriptor *a2)
{
    CMutex(&this->Unk400000, true);

    if(this->IsFull())
        return false;

    a2->Unk362 = 1;
    this->Unk0[this->Unk400032] = a2;
    this->Unk400032 = (this->Unk400032 + 1) / 100000;
    this->Unk400032 = (this->Unk400032 + 1) - 100000 * this->Unk400032;

    return true;
}

void CCharDBQ::EraseQ(CDescriptor *a2)
{
    int v3; // [sp+10h] [bp-Ch]@1

    CMutex(&this->Unk400000, true);

    v3 = this->Unk400028;

    while(v3 != this->Unk400032)
    {
        if(this->Unk0[v3] == a2)
            this->Unk0[v3] = 0;

        if(++v3 > 99999)
            v3 = 0;
    }
}

bool CCharDBQ::IsFull(void)
{
    return this->Unk400028 == (this->Unk400032 + 1) % 100000;
}

bool CCharDBQ::IsEmpty(void)
{
    return this->Unk400028 == this->Unk400032;
}

CDBThread::CDBThread(void)
{
    ;
}

CDBThread::~CDBThread()
{
    ;
}

bool CDBThread::CreateThread(void)
{
    char *arg;
    pthread_t newthread; // [sp+14h] [bp-4h]@1

    return (pthread_create(&newthread, 0, (void *(*)(void *))CDBThread::RunThread, arg)) ? false : true;
}

void CDBThread::RunThread(void *a1)
{
    ((CDBThread *)a1)->Run();
    pthread_exit(0);
}

void CDBThread::Run(void)
{
    int v3; // [sp+20h] [bp-8h]@1
    CDescriptor *v4; // [sp+24h] [bp-4h]@6

    v3 = 0;

    this->Unk400037 = 0;
    this->Unk400036 = 0;

    while(1)
    {
        if(this->IsEmpty())
            break;
LABEL_6:
        v4 = this->GetFromQ();
        if(v4)
        {
            CMutex(&v4->Unk164, true);
            v3 = 0;

            //if(*(_DWORD *)(v4 + 340) <= 0x19u)
            //    JUMPOUT(__CS__, off_80CE864[*(_DWORD *)(v4 + 340)]); // WHAT THE FUCK IS WRONG?

            v4->Unk362 = 0;
        }
        else
        {
            ++v3;
            if(v3 > 100)
            {
                v3 = 0;
                this->PingDB();
            }
        }
    }

    if(!this->Unk400037)
    {
        this->Wait300Millis(); // PROBABLY STATIC?
        goto LABEL_6;
    }

    this->Unk400036 = 1;
}

int CDBThread::PingDB(void)
{
    return mysql_ping(&gserver.Unk41272);
}

bool CDBThread::UpdateChar(CDescriptor *a2)
{
    CInventory *v18; // eax@37
    //short v21; // ax@77
    //short v22; // dx@77
    short v23; // ST5A_2@77
    int v24; // eax@92
    CItem *v28; // [sp+1Ch] [bp-104Ch]@73
    signed int v29; // [sp+1Ch] [bp-104Ch]@90
    CItem *v30; // [sp+20h] [bp-1048h]@51
    CInventory *v34; // [sp+2Ch] [bp-103Ch]@43
    int v35[2]; // [sp+30h] [bp-1038h]@32
    char v38; // [sp+3Fh] [bp-1029h]@32
    //int v39; // [sp+40h] [bp-1028h]@3
    int v40; // [sp+44h] [bp-1024h]@119
    int i; // [sp+1060h] [bp-8h]@15
    CPC *v42; // [sp+1064h] [bp-4h]@1

    v42 = a2->Unk372;

    if(!v42)
        return 0;

    CDBCmd v39;

    v39.Init(&gserver.Unk41272);

    strcpy(this->Unk405160, "UPDATE t_characters SET ");
    strcat(this->Unk405160, "a_exp=");
    IntCat(this->Unk405160, v42->Unk64, 1);
    strcat(this->Unk405160, ", a_str=");
    IntCat(this->Unk405160, v42->Unk756, 1);
    strcat(this->Unk405160, ", a_dex=");
    IntCat(this->Unk405160, v42->Unk758, 1);
    strcat(this->Unk405160, ", a_int=");
    IntCat(this->Unk405160, v42->Unk760, 1);
    strcat(this->Unk405160, ", a_con=");
    IntCat(this->Unk405160, v42->Unk762, 1);
    strcat(this->Unk405160, ", a_statpt_remain=");
    IntCat(this->Unk405160, v42->Unk740, 1);
    strcat(this->Unk405160, ", a_statpt_str=");
    IntCat(this->Unk405160, v42->Unk742, 1);
    strcat(this->Unk405160, ", a_statpt_dex=");
    IntCat(this->Unk405160, v42->Unk744, 1);
    strcat(this->Unk405160, ", a_statpt_con=");
    IntCat(this->Unk405160, v42->Unk748, 1);
    strcat(this->Unk405160, ", a_statpt_int=");
    IntCat(this->Unk405160, v42->Unk746, 1);
    strcat(this->Unk405160, ", a_hp=");
    IntCat(this->Unk405160, v42->Unk76, 1);
    strcat(this->Unk405160, ", a_max_hp=");
    IntCat(this->Unk405160, v42->Unk764, 1);
    strcat(this->Unk405160, ", a_mp=");
    IntCat(this->Unk405160, v42->Unk80, 1);
    strcat(this->Unk405160, ", a_max_mp=");
    IntCat(this->Unk405160, v42->Unk766, 1);
    strcat(this->Unk405160, ", a_level=");
    IntCat(this->Unk405160, v42->Unk60, 1);
    strcat(this->Unk405160, ", a_skill_point=");
    IntCat(this->Unk405160, v42->Unk72, 1);
    strcat(this->Unk405160, ", a_blood_point=");
    IntCat(this->Unk405160, v42->Unk752, 1);
    strcat(this->Unk405160, ", a_datestamp='");
    this->GetDateStr(this->Unk409256); // STATIC
    strcat(this->Unk405160, this->Unk409256);
    strcat(this->Unk405160, "'");
    strcat(this->Unk405160, ", a_was_x=");
    FloatCat(this->Unk405160, v42->Unk120.Unk0, 4, 1);
    strcat(this->Unk405160, ", a_was_z=");
    FloatCat(this->Unk405160, v42->Unk120.Unk4, 4, 1);
    strcat(this->Unk405160, ", a_was_h=");
    FloatCat(this->Unk405160, ((v42 && v42->Unk412) ? v42->Unk412->GetHeight(v42->Unk120.Unk16, v42->Unk120.Unk0, v42->Unk120.Unk4) : 0.0), 4, 1);
    strcat(this->Unk405160, ", a_was_r=");
    FloatCat(this->Unk405160, v42->Unk120.Unk12, 4, 1);
    strcat(this->Unk405160, ", a_was_zone=");
    IntCat(this->Unk405160, ((v42->Unk408) ? v42->Unk408->Unk0 : -1), 1);
    strcat(this->Unk405160, ", a_was_area=");
    IntCat(this->Unk405160, ((v42->Unk412) ? v42->Unk412->Unk8 : -1), 1);
    strcat(this->Unk405160, ", a_was_yLayer=");
    IntCat(this->Unk405160, v42->Unk120.Unk16, 1);
    strcat(this->Unk405160, ", a_silence_pulse=");
    IntCat(this->Unk405160, (v42->Unk784 - gserver.Unk41248 >= 0 ? v42->Unk784 - gserver.Unk41248 : 0), 1);
    strcat(this->Unk405160, ", a_pkpenalty=");
    IntCat(this->Unk405160, v42->Unk1852, 1);
    strcat(this->Unk405160, ", a_pkcount=");
    IntCat(this->Unk405160, v42->Unk1856, 1);
    strcat(this->Unk405160, ", a_pkrecover=");
    IntCat(this->Unk405160, v42->Unk1860, 1);
    strcat(this->Unk405160, ", a_pkpenaltyhp=");
    IntCat(this->Unk405160, v42->Unk1868, 1);
    strcat(this->Unk405160, ", a_pkpenaltymp=");
    IntCat(this->Unk405160, v42->Unk1872, 1);
    strcat(this->Unk405160, ", a_guildoutdate=");
    IntCat(this->Unk405160, v42->Unk2376, 1);
    strcat(this->Unk405160, ", a_active_skill_index='");
    strcat(this->Unk405160, v42->Unk480.GetIndexString(this->Unk409256));
    strcat(this->Unk405160, "', a_active_skill_level='");
    strcat(this->Unk405160, v42->Unk480.GetLevelString(this->Unk409256));
    strcat(this->Unk405160, "'");
    strcat(this->Unk405160, ", a_passive_skill_index='");
    strcat(this->Unk405160, v42->Unk492.GetIndexString(this->Unk409256));
    strcat(this->Unk405160, "', a_passive_skill_level='");
    strcat(this->Unk405160, v42->Unk492.GetLevelString(this->Unk409256));
    strcat(this->Unk405160, "'");
    strcat(this->Unk405160, ", a_etc_skill_index='");
    strcat(this->Unk405160, v42->Unk504.GetIndexString(this->Unk409256));
    strcat(this->Unk405160, "', a_etc_skill_level='");
    strcat(this->Unk405160, v42->Unk504.GetLevelString(this->Unk409256));
    strcat(this->Unk405160, "'");
    strcat(this->Unk405160, ", a_wearing='");
    i = 0;
    *this->Unk409256 = 0;
    while(i <= 9)
    {
        if(v42->Unk1284[i])
            IntCat(this->Unk409256, v42->Unk1284[i]->Unk28, 1);
        else
            IntCat(this->Unk409256, -1, 1);
        ++i;
    }
    strcat(this->Unk405160, this->Unk409256);
    strcat(this->Unk405160, "'");
    strcat(this->Unk405160, ", a_sskill='");
    strcat(this->Unk405160, v42->Unk716.GetString(this->Unk409256));
    strcat(this->Unk405160, "'");
    strcat(this->Unk405160, ", a_quest_index='");
    strcat(this->Unk405160, v42->Unk1900.GetIndexString(this->Unk409256));
    strcat(this->Unk405160, "', a_quest_value='");
    strcat(this->Unk405160, v42->Unk1900.GetValueString(this->Unk409256));
    strcat(this->Unk405160, "', a_quest_complete='");
    strcat(this->Unk405160, v42->Unk1900.GetCompleteIndexString(this->Unk409256));
    strcat(this->Unk405160, "'");
    strcat(this->Unk405160, " WHERE a_index=");
    IntCat(this->Unk405160, v42->Unk4, 1);

    v39.SetQuery(this->Unk405160);
    v39.BeginTrans(); // CHECK this->Unk405160

    if(v39.Update())
        v39.Commit();
    else
        v39.Rollback();

    strcpy(this->Unk405160, "DELETE FROM t_assist WHERE a_char_index=");
    IntCat(this->Unk405160, v42->Unk4, 0);

    v39.SetQuery(this->Unk405160);
    v39.BeginTrans();

    if(v39.Update())
        v39.Commit();
    else
        v39.Rollback();

    strcpy(this->Unk405160, "INSERT INTO t_assist (a_char_index, a_help_item, a_help_skill, a_help_level, a_help_remain, a_help_hit0, a_help_hit1, a_help_hit2, a_curse_item, a_curse_skill, a_curse_level, a_curse_remain, a_curse_hit0, a_curse_hit1, a_curse_hit2) VALUES (");
    IntCat(this->Unk405160, v42->Unk4, 1);
    strcat(this->Unk405160, ",");
    v42->Unk148.GetListString(true, assistitem, assistskill, assistlevel, assistremain, assisthit0, assisthit1, assisthit2);
    StrCat(this->Unk405160, "'");
    strcat(this->Unk405160, assistitem);
    strcat(this->Unk405160, "',");
    StrCat(this->Unk405160, "'");
    strcat(this->Unk405160, assistskill);
    strcat(this->Unk405160, "',");
    StrCat(this->Unk405160, "'");
    strcat(this->Unk405160, assistlevel);
    strcat(this->Unk405160, "',");
    StrCat(this->Unk405160, "'");
    strcat(this->Unk405160, assistremain);
    strcat(this->Unk405160, "',");
    StrCat(this->Unk405160, "'");
    strcat(this->Unk405160, assisthit0);
    strcat(this->Unk405160, "',");
    StrCat(this->Unk405160, "'");
    strcat(this->Unk405160, assisthit1);
    strcat(this->Unk405160, "',");
    StrCat(this->Unk405160, "'");
    strcat(this->Unk405160, assisthit2);
    strcat(this->Unk405160, "',");
    v42->Unk148.GetListString(false, assistitem, assistskill, assistlevel, assistremain, assisthit0, assisthit1, assisthit2);
    StrCat(this->Unk405160, "'");
    strcat(this->Unk405160, assistitem);
    strcat(this->Unk405160, "',");
    StrCat(this->Unk405160, "'");
    strcat(this->Unk405160, assistskill);
    strcat(this->Unk405160, "',");
    StrCat(this->Unk405160, "'");
    strcat(this->Unk405160, assistlevel);
    strcat(this->Unk405160, "',");
    StrCat(this->Unk405160, "'");
    strcat(this->Unk405160, assistremain);
    strcat(this->Unk405160, "',");
    StrCat(this->Unk405160, "'");
    strcat(this->Unk405160, assisthit0);
    strcat(this->Unk405160, "',");
    StrCat(this->Unk405160, "'");
    strcat(this->Unk405160, assisthit1);
    strcat(this->Unk405160, "',");
    StrCat(this->Unk405160, "'");
    strcat(this->Unk405160, assisthit2);
    strcat(this->Unk405160, "')");

    v39.SetQuery(this->Unk405160);
    v39.BeginTrans();

    if(v39.Update())
        v39.Commit();
    else
        v39.Rollback();

    strcpy(this->Unk405160, "DELETE FROM t_inven");
    IntCat0(this->Unk405160, v42->Unk4 % 10, 2, 0);
    strcat(this->Unk405160, " WHERE a_char_idx=");
    IntCat(this->Unk405160, v42->Unk4, 0);

    v39.SetQuery(this->Unk405160);
    v39.BeginTrans();

    if(v39.Update())
    {
        v38 = 1;

        v35[0] = 0;
        v35[1] = 1;
        v35[2] = 2;

        for(int i = 0; v38 && i <= 2; ++i)
        {
            if(v35[i] == 0)
            {
                if(v35[i] == 1)
                {
                    v18 = &v42->Unk880;
                }
                else
                {
                    if(v35[i] == 2)
                        v18 = &v42->Unk968;
                    else
                        v18 = 0;
                }
            }
            else
            {
                v18 = &v42->Unk792;
            }

            v34 = v18;

            for(int j = 0; v38 && j <= 19; ++j)
            {
                if(v34->Unk8[j])
                {
                    strcpy(this->Unk405160, "INSERT INTO t_inven");
                    IntCat0(this->Unk405160, v42->Unk4 % 10, 2, 0);
                    strcat(this->Unk405160, " (a_char_idx, a_tab_idx, a_row_idx,");
                    strcat(this->Unk405160, " a_item_idx0, a_plus0, a_wear_pos0, a_flag0, a_used0, a_serial0, a_count0,");
                    strcat(this->Unk405160, " a_item0_option0, a_item0_option1, a_item0_option2, a_item0_option3, a_item0_option4,");
                    strcat(this->Unk405160, " a_item_idx1, a_plus1, a_wear_pos1, a_flag1, a_used1, a_serial1, a_count1,");
                    strcat(this->Unk405160, " a_item1_option0, a_item1_option1, a_item1_option2, a_item1_option3, a_item1_option4,");
                    strcat(this->Unk405160, " a_item_idx2, a_plus2, a_wear_pos2, a_flag2, a_used2, a_serial2, a_count2,");
                    strcat(this->Unk405160, " a_item2_option0, a_item2_option1, a_item2_option2, a_item2_option3, a_item2_option4,");
                    strcat(this->Unk405160, " a_item_idx3, a_plus3, a_wear_pos3, a_flag3, a_used3, a_serial3, a_count3,");
                    strcat(this->Unk405160, " a_item3_option0, a_item3_option1, a_item3_option2, a_item3_option3, a_item3_option4,");
                    strcat(this->Unk405160, " a_item_idx4, a_plus4, a_wear_pos4, a_flag4, a_used4, a_serial4, a_count4,");
                    strcat(this->Unk405160, " a_item4_option0, a_item4_option1, a_item4_option2, a_item4_option3, a_item4_option4)");
                    strcat(this->Unk405160, " VALUES (");
                    IntCat(this->Unk405160, v42->Unk4, 0);
                    strcat(this->Unk405160, ",");
                    IntCat(this->Unk405160, v35[i], 1);
                    strcat(this->Unk405160, ",");
                    IntCat(this->Unk405160, j, 1);

                    for(int k = 0; k <= 4; ++k)
                    {
                        if(v34->Unk8[j]->Unk4[k])
                        {
                            v30 = v34->Unk8[j]->Unk4[k];
                            strcat(this->Unk405160, ",");
                            IntCat(this->Unk405160, v30->Unk28, 1);
                            strcat(this->Unk405160, ",");
                            IntCat(this->Unk405160, v30->Unk36, 1);
                            strcat(this->Unk405160, ",");
                            IntCat(this->Unk405160, v30->Unk32, 1);
                            strcat(this->Unk405160, ",");
                            IntCat(this->Unk405160, v30->Unk40, 1);
                            strcat(this->Unk405160, ",");
                            IntCat(this->Unk405160, v30->Unk64, 1);
                            strcat(this->Unk405160, ", '");
                            strcat(this->Unk405160, v30->Unk44);
                            strcat(this->Unk405160, "',");
                            IntCat(this->Unk405160, v30->Count(), 1);

                            for(int l = 0; l <= 4; ++l)
                            {
                                strcat(this->Unk405160, ",");
                                if(v30->Unk68[l].Unk8 <= 0)
                                {
                                    IntCat(this->Unk405160, 0, 1);
                                }
                                else
                                {
                                    v30->Unk68[l].SetDBValue();
                                    IntCat(this->Unk405160, v30->Unk68[l].Unk16, 1);
                                }
                            }
                        }
                        else
                        {
                            strcat(this->Unk405160, ", -1, 0, -1, 0, -1, "", 0, 0, 0, 0, 0, 0");
                        }
                    }

                    strcat(this->Unk405160, ")");

                    v39.SetQuery(this->Unk405160);
                    if(!v39.Update())
                        v38 = 0;
                }
            }
        }

        if(v38)
            v39.Commit();
        else
            v39.Rollback();
    }
    else
    {
        v39.Rollback();
    }

    if(a2->Unk372->Unk1256)
    {
        a2->Unk372->Unk1256 = 0;
        strcpy(this->Unk405160, "DELETE FROM t_stash");
        IntCat0(this->Unk405160, v42->Unk768->Unk0 % 10, 2, 0);
        strcat(this->Unk405160, " WHERE a_user_idx=");
        IntCat(this->Unk405160, v42->Unk768->Unk0, 0);

        v39.SetQuery(this->Unk405160);
        v39.BeginTrans();

        if(v39.Update())
        {
            v38 = 1;
            for(i = 0; i <= 49 && v38; ++i)
            {
                v28 = v42->Unk1056.item(i);
                if(v28)
                {
                    strcpy(this->Unk405160, "INSERT INTO t_stash");
                    IntCat0(this->Unk405160, v42->Unk768->Unk0 % 10, 2, 0);
                    strcat(this->Unk405160, " (a_user_idx,a_item_idx,a_plus,a_flag,a_serial,a_count,a_used,a_item_option0,a_item_option1,a_item_option2,a_item_option3,a_item_option4) VALUES (");
                    IntCat(this->Unk405160, v42->Unk768->Unk0, 0);
                    strcat(this->Unk405160, ", ");
                    IntCat(this->Unk405160, v28->Unk28, 0);
                    strcat(this->Unk405160, ", ");
                    IntCat(this->Unk405160, v28->Unk36, 0);
                    strcat(this->Unk405160, ", ");
                    IntCat(this->Unk405160, v28->Unk40, 0);
                    strcat(this->Unk405160, ", ");
                    strcat(this->Unk405160, "'");
                    strcat(this->Unk405160, v28->Unk44);
                    strcat(this->Unk405160, "', ");
                    IntCat(this->Unk405160, v28->Count(), 0);
                    strcat(this->Unk405160, ", ");
                    IntCat(this->Unk405160, v28->Unk64, 0);

                    for(int m = 0; m <= 4; ++m)
                    {
                        if(v28->Unk68[m].Unk8 <= 0)
                        {
                            strcat(this->Unk405160, ", ");
                            IntCat(this->Unk405160, 0, 1);
                        }
                        else
                        {
                            //HIBYTE(v21) = (char)v28->Unk68[m].Unk4; // 72 = 68 + 4
                            //LOBYTE(v21) = 0;
                            //v22 = (short)v28->Unk68[m].Unk8; // 76 = 68 + 8
                            //HIBYTE(v22) = 0;
                            //v23 = v22 | v21;

                            v23 = ((v28->Unk68[m].Unk4 >> 8) & 0xFF00) | ((v28->Unk68[m].Unk8 >> 0) & 0x00FF); // OBVIOUSLY FUCKING CHECK

                            strcat(this->Unk405160, ", ");
                            IntCat(this->Unk405160, v23, 1);
                        }
                    }

                    strcat(this->Unk405160, ")");

                    v39.SetQuery(this->Unk405160);
                    if(!v39.Update())
                        v38 = 0;
                }
            }

            if(v38)
                v39.Commit();
            else
                v39.Rollback();
        }
        else
        {
            v39.Rollback();
        }
    }

    strcpy(this->Unk405160, "DELETE FROM t_quickslot");
    IntCat0(this->Unk405160, v42->Unk4 % 10, 2, 0);
    strcat(this->Unk405160, " WHERE a_char_idx=");
    IntCat(this->Unk405160, v42->Unk4, 0);

    v39.SetQuery(this->Unk405160);
    v39.BeginTrans();

    if(v39.Update())
    {
        v38 = 1;
        for(i = 0; ; ++i)
        {
            if(i > 2)
            {
                if(v38)
                    v39.Commit();
                else
                    v39.Rollback();

                goto LABEL_111;
            }

            v29 = 0;
            *this->Unk400040 = 0;

            while(v29 <= 9)
            {
                v24 = v42->Unk1372[i].Unk0[v29];
                if(!v24)
                {
                    IntCat(this->Unk400040, v42->Unk1372[i].Unk0[v29], 0); // 1372
                    IntCat(this->Unk400040, v42->Unk1372[i].Unk40[v29], 1); // 1412 = 1372 + 40
                    goto LABEL_104;
                }

                if(v24 <= 0)
                    goto LABEL_130;

                if(v24 == 1)
                {
                    IntCat(this->Unk400040, v42->Unk1372[i].Unk0[v29], 0); // 1372
                    IntCat(this->Unk400040, v42->Unk1372[i].Unk80[v29], 1); // 1452 = 1372 + 80
                    goto LABEL_104;
                }

                if(v24 == 2)
                {
                    if(v42->Unk1372[i].Unk120[v29]) // 1492 = 1372 + 120
                    {
                        IntCat(this->Unk400040, v42->Unk1372[i].Unk0[v29], 0); // 1372
                        IntCat(this->Unk400040, v42->Unk1372[i].Unk120[v29]->row(), 1); // 1492 = 1372 + 120
                        IntCat(this->Unk400040, v42->Unk1372[i].Unk120[v29]->col(), 1); // 1492 = 1372 + 120
                    }
                    else
                    {
                        IntCat(this->Unk400040, -1, 0);
                    }
                }
                else
                {
LABEL_130:
                    IntCat(this->Unk400040, v42->Unk1372[i].Unk0[v29], 0); // 1372
                }
LABEL_104:
                StrCat(this->Unk400040, &byte_80CE84C);
                ++v29;
            }

            strcpy(this->Unk405160, "INSERT INTO t_quickslot");
            IntCat0(this->Unk405160, v42->Unk4 % 10, 2, 0);
            strcat(this->Unk405160, " (a_char_idx, a_page_idx, a_slot) VALUES (");
            IntCat(this->Unk405160, v42->Unk4, 0);
            strcat(this->Unk405160, ", ");
            IntCat(this->Unk405160, i, 0);
            strcat(this->Unk405160, ", '");
            strcat(this->Unk405160, this->Unk400040);
            strcat(this->Unk405160, "')");

            v39.SetQuery(this->Unk405160);

            if(!v39.Update())
                v38 = 0;
        }
    }

    v39.Rollback();

LABEL_111:
    strcpy(this->Unk405160, "UPDATE t_mempos SET");

    for(int i = 0; i <= 4; ++i)
    {
        if(i)
            strcat(this->Unk405160, ", ");

        if(v42->Unk1332.Unk4[i]) // 1336
        {
            StrCat(this->Unk405160, "a_mem_");
            IntCat(this->Unk405160, i, 0);
            StrCat(this->Unk405160, "='");
            IntCat(this->Unk405160, v42->Unk1332.Unk4[i]->Unk0, 0);
            FloatCat(this->Unk405160, v42->Unk1332.Unk4[i]->Unk4, 4, 1);
            FloatCat(this->Unk405160, v42->Unk1332.Unk4[i]->Unk8, 4, 1);
            IntCat(this->Unk405160, v42->Unk1332.Unk4[i]->Unk12, 1);
            StrCat(this->Unk405160, v42->Unk1332.Unk4[i]->Unk13);
            StrCat(this->Unk405160, "'");
        }
        else
        {
            StrCat(this->Unk405160, "a_mem_");
            IntCat(this->Unk405160, i, 0);
            StrCat(this->Unk405160, "=""");
        }
    }

    StrCat(this->Unk405160, "WHERE a_char_idx=");
    IntCat(this->Unk405160, v42->Unk4, 0);
    v39.SetQuery(this->Unk405160);
    v39.Update();

    if(v40 <= 0)
    {
        strcpy(this->Unk405160, "INSERT INTO t_mempos (a_char_idx, a_mem_0, a_mem_1, a_mem_2, a_mem_3, a_mem_4) VALUES (");
        IntCat(this->Unk405160, v42->Unk4, 0);
        for(int i = 0; i <= 4; ++i)
        {
            strcat(this->Unk405160, ", '");
            if(v42->Unk1332.Unk4[i]) // 1336
            {
                IntCat(this->Unk405160, v42->Unk1332.Unk4[i]->Unk0, 0);
                FloatCat(this->Unk405160, v42->Unk1332.Unk4[i]->Unk4, 4, 1);
                FloatCat(this->Unk405160, v42->Unk1332.Unk4[i]->Unk8, 4, 1);
                IntCat(this->Unk405160, v42->Unk1332.Unk4[i]->Unk12, 1);
                StrCat(this->Unk405160, v42->Unk1332.Unk4[i]->Unk13);
                StrCat(this->Unk405160, "'");
            }
            else
            {
                strcat(this->Unk405160, "'");
            }
        }

        StrCat(this->Unk405160, ")");
        v39.SetQuery(this->Unk405160);
        v39.Update();
    }

    return true;
}

struct UnkStructNetMsg // 20, Y ISN'T FUCKING 24?
{
    int Unk0;
    CNetMsg Unk4;
};

// CHECK CONSTRUCTOR ARRAY UnkStructNetMsg (_._Q39CDBThread36OnUserDB__9CDBThreadP11CDescriptor.0_13__tagCharSlot.618)
// CHECK DESTRUCTOR ARRAY UnkStructNetMsg  (__Q39CDBThread36OnUserDB__9CDBThreadP11CDescriptor.0_13__tagCharSlot.619)
bool CDBThread::OnUserDB(CDescriptor *a2)
{
    CItemProto *v28; // [sp+2Ch] [bp-10CCh]@27
    char *v31; // [sp+34h] [bp-10C4h]@23
    int v32[10]; // [sp+38h] [bp-10C0h]@27
    int i; // [sp+1080h] [bp-78h]@10

    if(a2->Unk356 == 1)
    {
        CNetMsg v36;

        DBCharEndMsg(v36);
        a2->Unk124.Add(v36);

        return true;
    }

    if(a2->Unk361)
        return false;

    if(!a2->Unk4 && a2->Unk0 >= 0)
        return false;

    UnkStructNetMsg v35[4];

    for(i = 0; i <= 3; ++i)
        v35[i].Unk0 = -1;

    CDBCmd v33;

    v33.Init(&gserver.Unk41272);

    strcpy(this->Unk405160, "SELECT * FROM t_characters WHERE a_user_index=");
    IntCat(this->Unk405160, a2->Unk0, 0);
    StrCat(this->Unk405160, "AND a_server=");
    IntCat(this->Unk405160, gserver.Unk41004, 0);
    StrCat(this->Unk405160, "AND a_enable=1 ORDER BY a_index");

    v33.SetQuery(this->Unk405160);
    if(!v33.Open())
        return false;

    for(i = 0; v33.MoveNext() && i <= 3; ++i)
    {
        v33.GetRec("a_index", v35[i].Unk0);
        v31 = (char *)v33.GetRec("a_wearing");

        for(int j = 0; j <= 9; ++j)
        {
            strcpy(this->Unk409256, "-1");
            v31 = AnyOneArg(v31, this->Unk409256, 0);

            if(j > 0 && j <= 6)
            {
                v32[j-1] = atoi(this->Unk409256);
                v28 = gserver.Unk41208.FindIndex(v32[j-1]);

                if(!v28 || v28->Unk108 < 0 || v28->Unk108 > 9)
                    v32[j-1] = -1;
            }
        }

        DBCharExistMsg(v35[i].Unk4, v35[i].Unk0, v33.GetRec("a_name"), atoi(v33.GetRec("a_job")),
                       atoi(v33.GetRec("a_hair_style")), atoi(v33.GetRec("a_face_style")),
                       atoi(v33.GetRec("a_level")), atoll(v33.GetRec("a_exp")),
                       atoi(v33.GetRec("a_skill_point")), atoi(v33.GetRec("a_hp")),
                       atoi(v33.GetRec("a_max_hp")), atoi(v33.GetRec("a_mp")),
                       atoi(v33.GetRec("a_max_mp")), v32);
    }

    if(i > 0)
    {
        for(int k = 0; k < i; ++k)
        {
            if(v35[k].Unk0 != -1)
                a2->Unk124.Add(v35[k].Unk4);
        }
    }

    CNetMsg v36;

    DBCharEndMsg(v36);
    a2->Unk124.Add(v36);

    return true;
}

int itemsForTitan_631[3][7]  = {{72, 2, 12, 3, 4, 8, 0}, {0 , 1, 2, 3, 5, 6, -1}, {1, 1, 1, 1, 1, 1, 100}};
int itemsForKnight_632[3][8] = {{75, 34, 48, 38, 49, 39, 41, 0}, {0, 1, 2, 3, 4, 5, 6, -1}, {1, 1, 1, 1, 1, 1, 1, 100}};
int itemsForHealer_633[3][7] = {{78, 26, 50, 28, 30, 32, 0}, {0, 1, 2, 3, 5, 6, -1}, {1, 1, 1, 1, 1, 1, 100}};
int itemsForMage_634[3][7] = {{24, 266, 356, 18, 22, 20, 0}, {0, 1, 2, 3, 5, 6, -1}, {1, 1, 1, 1, 1, 1, 100}};

bool CDBThread::OnNewCharDB(CDescriptor *a2)
{
    int v19; // [sp+40h] [bp-1728h]@33
    CItemProto *v21; // [sp+44h] [bp-1724h]@33
    char v23[32]; // [sp+4Ch] [bp-171Ch]@35
    char v24[400]; // [sp+6Ch] [bp-16FCh]@31
    char s[400]; // [sp+1FCh] [bp-156Ch]@31
    char v26[400]; // [sp+38Ch] [bp-13DCh]@31
    char dest[400]; // [sp+51Ch] [bp-124Ch]@31
    int v28; // [sp+6ACh] [bp-10BCh]@31
    int v29; // [sp+6B0h] [bp-10B8h]@31
    int v30; // [sp+6B4h] [bp-10B4h]@31
    int v31; // [sp+6B8h] [bp-10B0h]@19
    int *v32; // [sp+6BCh] [bp-10ACh]@19
    int *v33; // [sp+6C0h] [bp-10A8h]@19
    int *v34; // [sp+6C4h] [bp-10A4h]@19
    int v35; // [sp+6C8h] [bp-10A0h]@19
    bool v36; // [sp+6CFh] [bp-1099h]@7
    char src[100]; // [sp+6E4h] [bp-1084h]@5

    if(a2->Unk361 || !a2->Unk372)
        return false;

    CDBCmd v39;

    v39.Init(&gserver.Unk41272);
    this->BackSlash(src, a2->Unk372->Unk8);

    strcpy(this->Unk405160, "SELECT a_index FROM t_characters WHERE a_name='");
    strcat(this->Unk405160, src);
    strcat(this->Unk405160, "' AND a_server=");
    IntCat(this->Unk405160, gserver.Unk41004, 0);

    v39.SetQuery(this->Unk405160);
    v39.Open();

    if(v39.AffectedRows > 0)
    {
        CNetMsg v37;

        FailMsg(v37, 10);
        a2->Unk124.Add(v37);

        return false;
    }

    strcpy(this->Unk405160, "SELECT a_index FROM t_characters WHERE a_user_index=");
    IntCat(this->Unk405160, a2->Unk0, 0);
    strcat(this->Unk405160, " AND a_server=");
    IntCat(this->Unk405160, gserver.Unk41004, 0);
    strcat(this->Unk405160, " AND a_enable=1");

    v39.SetQuery(this->Unk405160);
    v36 = true;

    if(!v39.Open())
        throw 11;

    if(v39.AffectedRows > 3)
        throw 12;

    this->GetDateStr(this->Unk409256);
    v39.BeginTrans();

    strcpy(this->Unk405160, "INSERT INTO t_characters (a_user_index, a_server, a_name, a_was_x, a_was_z, a_was_h, a_was_r, a_was_zone, a_was_area, a_active_skill_index, a_active_skill_level, a_passive_skill_index, a_passive_skill_level, a_etc_skill_index, a_etc_skill_level, a_wearing, a_quest_index, a_quest_value, a_sskill, a_datestamp, a_createdate, a_job, a_hair_style, a_face_style, a_str, a_dex, a_int, a_con, a_hp, a_max_hp, a_mp, a_max_mp, a_skill_point) VALUES (");
    IntCat(this->Unk405160, a2->Unk0, 1);
    strcat(this->Unk405160, ",");
    IntCat(this->Unk405160, gserver.Unk41004, 1);
    strcat(this->Unk405160, ",");
    StrCat(this->Unk405160, "'");
    strcat(this->Unk405160, src);
    strcat(this->Unk405160, "',");
    StrCat(this->Unk405160, "0.0000, 0.0000, 0.0000, 0.0000, -1, -1,");

    switch(a2->Unk372->Unk477)
    {
        case 0:
            StrCat(this->Unk405160, "' 1', ' 1', "", "", "", "",");
            StrCat(this->Unk405160, " ' 72 2 12 3 -1 4 8', ");
            break;
        case 1:
            StrCat(this->Unk405160, "' 14', ' 1', "", "", "", "",");
            StrCat(this->Unk405160, " ' 75 34 48 38 49 39 41', ");
            break;
        case 2:
            StrCat(this->Unk405160, "' 27 31', ' 1 1', "", "", "", "",");
            StrCat(this->Unk405160, " ' 78 26 50 28 -1 30 32', ");
            break;
        case 3:
            StrCat(this->Unk405160, "' 53', ' 1', "", "", "", "",");
            StrCat(this->Unk405160, " '24 266 356 18 -1 22 20', ");
            break;
        default:
            StrCat(this->Unk405160, """, "", "", "", "", "",");
            StrCat(this->Unk405160, " "", ");
            break;
    }

    strcat(this->Unk405160, "' 45', ' 0 0 0', ");
    strcat(this->Unk405160, "' 1 1 5 1 9 1 13 1 18 1 23 1 44 1', '");
    strcat(this->Unk405160, this->Unk409256);
    strcat(this->Unk405160, "', '");
    strcat(this->Unk405160, this->Unk409256);
    strcat(this->Unk405160, "',");
    IntCat(this->Unk405160, a2->Unk372->Unk477, 1);
    strcat(this->Unk405160, ",");
    IntCat(this->Unk405160, a2->Unk372->Unk478, 1);
    strcat(this->Unk405160, ",");
    IntCat(this->Unk405160, a2->Unk372->Unk479, 1);
    strcat(this->Unk405160, ",");
    IntCat(this->Unk405160, a2->Unk372->Unk84, 1);
    strcat(this->Unk405160, ",");
    IntCat(this->Unk405160, a2->Unk372->Unk86, 1);
    strcat(this->Unk405160, ",");
    IntCat(this->Unk405160, a2->Unk372->Unk88, 1);
    strcat(this->Unk405160, ",");
    IntCat(this->Unk405160, a2->Unk372->Unk90, 1);
    strcat(this->Unk405160, ",");
    IntCat(this->Unk405160, a2->Unk372->Unk764, 1);
    strcat(this->Unk405160, ",");
    IntCat(this->Unk405160, a2->Unk372->Unk764, 1);
    strcat(this->Unk405160, ",");
    IntCat(this->Unk405160, a2->Unk372->Unk766, 1);
    strcat(this->Unk405160, ",");
    IntCat(this->Unk405160, a2->Unk372->Unk766, 1);
    strcat(this->Unk405160, ",");
    IntCat(this->Unk405160, 250000, 1);
    strcat(this->Unk405160, ")");

    v39.SetQuery(this->Unk405160);

    if(!v39.Update())
        throw 14;

    v35 = v39.insertid();
    v34 = 0;
    v33 = 0;
    v32 = 0;
    v31 = 0;

    if(a2->Unk372->Unk477 == 1)
    {
        v34 = itemsForKnight_632[0];
        v33 = itemsForKnight_632[1];
        v32 = itemsForKnight_632[2];
        v31 = 8;
        goto LABEL_31;
    }

    if(a2->Unk372->Unk477 > 1)
    {
        if(a2->Unk372->Unk477 == 2)
        {
            v34 = itemsForHealer_633[0];
            v33 = itemsForHealer_633[1];
            v32 = itemsForHealer_633[2];
            v31 = 7;
            goto LABEL_31;
        }

        if(a2->Unk372->Unk477 == 3)
        {
            v34 = itemsForMage_634[0];
            v33 = itemsForMage_634[1];
            v32 = itemsForMage_634[2];
            v31 = 7;
            goto LABEL_31;
        }
    }
    else
    {
        if(a2->Unk372->Unk477 == 0)
        {
            v34 = itemsForTitan_631[0];
            v33 = itemsForTitan_631[1];
            v32 = itemsForTitan_631[2];
            v31 = 7;
            goto LABEL_31;
        }
    }

    v31 = 0;
LABEL_31:
    v28 = 0;
    v29 = 0;
    v30 = 0;

    strcpy(dest, "INSERT INTO t_inven");
    IntCat0(dest, v35 % 10, 2, 0);
    strcat(dest, " (a_char_idx, a_tab_idx, a_row_idx");

    strcpy(v26, ") VALUES (");
    IntCat(v26, v35, 0);
    strcat(v26, ", 0, 0");

    *s = 0;
    *v24 = 0;

    for(int i = 0; i < v31; ++i)
    {
        v21 = gserver.Unk41208.FindIndex(v34[i]);
        v19 = -1;

        if(v21)
            v19 = v21->Unk72;

        strcat(s, ", a_item_idx");
        IntCat(s, v28, 0);
        strcat(s, ", ");
        strcat(s, "a_plus");
        IntCat(s, v28, 0);
        strcat(s, ", ");
        strcat(s, "a_wear_pos");
        IntCat(s, v28, 0);
        strcat(s, ", ");
        strcat(s, "a_flag");
        IntCat(s, v28, 0);
        strcat(s, ", ");
        strcat(s, "a_serial");
        IntCat(s, v28, 0);
        strcat(s, ", ");
        strcat(s, "a_count");
        IntCat(s, v28, 0);
        strcat(s, ", ");
        strcat(s, "a_used");
        IntCat(s, v28, 0);
        strcat(v24, ", ");
        IntCat(v24, v34[i], 0);
        strcat(v24, ", ");
        IntCat(v24, 0, 0);
        strcat(v24, ", ");
        IntCat(v24, v33[i], 0);
        strcat(v24, ", ");
        IntCat(v24, 0, 0);
        strcat(v24, ", '");
        GetSerial(v23, v34[i]);
        strcat(v24, v23);
        strcat(v24, "', ");
        IntCat(v24, v32[i], 0);
        strcat(v24, ", ");
        IntCat(v24, v19, 0);

        ++v28;
        if(v28 == 5)
        {
            ++v29;
            v28 = 0;

            strcpy(this->Unk405160, dest);
            strcat(this->Unk405160, s);
            strcat(this->Unk405160, v26);
            strcat(this->Unk405160, v24);
            strcat(this->Unk405160, ")");

            v39.SetQuery(this->Unk405160);
            if(!v39.Update())
                throw 14;

            strcpy(v26, ") VALUES (");
            IntCat(v26, v35, 0);
            strcat(v26, ", 0, ");
            IntCat(v26, v29, 0);

            *s = 0;
            *v24 = 0;
        }
    }

    if(strlen(s))
    {
        ++v29;
        v28 = 0;

        strcpy(this->Unk405160, dest);
        strcat(this->Unk405160, s);
        strcat(this->Unk405160, v26);
        strcat(this->Unk405160, v24);
        strcat(this->Unk405160, ")");

        v39.SetQuery(this->Unk405160);
        if(!v39.Update())
            throw 14;
    }

    strcpy(this->Unk405160, "INSERT INTO t_quickslot");
    IntCat0(this->Unk405160, v35 % 10, 2, 0);
    StrCat(this->Unk405160, "(a_char_idx, a_page_idx, a_slot) VALUES (");
    IntCat(this->Unk405160, v35, 0);
    StrCat(this->Unk405160, ", 0, ");

    switch(a2->Unk372->Unk477)
    {
        case 0:
            strcat(this->Unk405160, "' 0 1");
            break;
        case 1:
            strcat(this->Unk405160, "' 0 14");
            break;
        case 2:
            strcat(this->Unk405160, "' 0 27 0 31");
            break;
        case 3:
            strcat(this->Unk405160, "' 0 53");
            break;
        default:
            strcat(this->Unk405160, "'");
            break;
    }

    StrCat(this->Unk405160, "1 4 1 5 1 6 1 7 1 3')");

    v39.SetQuery(this->Unk405160);
    if(!v39.Update())
        throw 14;

    for(int j = 1; j <= 2; ++j)
    {
        strcpy(this->Unk405160, "INSERT INTO t_quickslot");
        IntCat0(this->Unk405160, v35 % 10, 2, 0);
        StrCat(this->Unk405160, "(a_char_idx, a_page_idx) VALUES(");
        IntCat(this->Unk405160, v35, 0);
        StrCat(this->Unk405160, ",");
        IntCat(this->Unk405160, j, 1);
        StrCat(this->Unk405160, ")");

        v39.SetQuery(this->Unk405160);
        if(!v39.Update())
            throw 14;
    }

    v39.Commit();

    CNetMsg v37;

    DBSuccessMsg(v37);
    a2->Unk124.Add(v37);

    return v36;
}

bool CDBThread::OnDelCharDB(CDescriptor *a2)
{
    if(a2->Unk361)
        return false;

    CDBCmd v4;

    v4.Init(&gserver.Unk41272);
    this->GetDateStr(this->Unk409256);

    strcpy(this->Unk400040, "UPDATE t_characters SET a_enable=0, a_datestamp='");
    strcat(this->Unk400040, this->Unk409256);
    strcat(this->Unk400040, "' WHERE a_user_index=");
    IntCat(this->Unk400040, a2->Unk0, 0);
    strcat(this->Unk400040, " AND a_server=");
    IntCat(this->Unk400040, gserver.Unk41004, 0);
    strcat(this->Unk400040, " AND a_index=");
    IntCat(this->Unk400040, a2->Unk372->Unk4, 0);
    strcat(this->Unk400040, " AND a_enable=1");

    v4.SetQuery(this->Unk400040);
    if(!v4.Update())
    {
        CNetMsg v3;

        FailMsg(v3, 14);
        a2->Unk124.Add(v3);

        return false;
    }

    if(v4.AffectedRows <= 0)
    {
        CNetMsg v3;

        FailMsg(v3, 13);
        a2->Unk124.Add(v3);

        return false;
    }

    CNetMsg v3;

    DBSuccessMsg(v3);
    a2->Unk124.Add(v3);

    return true;
}

/*bool CDBThread::OnPlayCharDB(CDescriptor *a2)
{
    int v7; // eax@177
    int v8; // eax@241
    int v9; // eax@256

    char v10[152]; // [sp+98h] [bp-1400h]@256
    float v11; // [sp+130h] [bp-1368h]@256
    float v12; // [sp+134h] [bp-1364h]@256
    char nptr[256]; // [sp+138h] [bp-1360h]@256
    int v14; // [sp+238h] [bp-1260h]@191
    int n; // [sp+23Ch] [bp-125Ch]@191
    int v16; // [sp+240h] [bp-1258h]@189
    int v17; // [sp+244h] [bp-1254h]@189
    int m; // [sp+248h] [bp-1250h]@189
    __int64 v19; // [sp+24Ch] [bp-124Ch]@164
    const char src[20]; // [sp+254h] [bp-1244h]@163
    CItem *v21; // [sp+268h] [bp-1230h]@123
    int v22; // [sp+26Ch] [bp-122Ch]@117
    int v23; // [sp+270h] [bp-1228h]@115
    int v24; // [sp+274h] [bp-1224h]@113
    int v25; // [sp+278h] [bp-1220h]@111
    int v26; // [sp+27Ch] [bp-121Ch]@107
    CSSkillList *v27; // [sp+280h] [bp-1218h]@93
    CSSkillList *v28; // [sp+284h] [bp-1214h]@94
    char v29[5]; // [sp+28Bh] [bp-120Dh]@85
    int l; // [sp+290h] [bp-1208h]@78
    CQuest *v31; // [sp+294h] [bp-1204h]@78
    CQuestProto *v32; // [sp+298h] [bp-1200h]@77
    int i; // [sp+29Ch] [bp-11FCh]@77
    char v34; // [sp+2A3h] [bp-11F5h]@68
    CSkill *v35; // [sp+2A4h] [bp-11F4h]@49
    char *v36; // [sp+2A8h] [bp-11F0h]@49
    CSkill *v37; // [sp+2ACh] [bp-11ECh]@49
    int v38; // [sp+2B0h] [bp-11E8h]@44
    short v39[4]; // [sp+2B4h] [bp-11E4h]@171
    char *v40; // [sp+2C4h] [bp-11D4h]@29
    unsigned int v41; // [sp+2C8h] [bp-11D0h]@23
    char *v42; // [sp+2CCh] [bp-11CCh]@21
    int v43; // [sp+2D0h] [bp-11C8h]@11
    char v44; // [sp+2D7h] [bp-11C1h]@11
    int v45; // [sp+2D8h] [bp-11C0h]@9
    int v46; // [sp+2DCh] [bp-11BCh]@9
    int v47; // [sp+2E0h] [bp-11B8h]@9
    int v48; // [sp+2E4h] [bp-11B4h]@7
    int v49; // [sp+2E8h] [bp-11B0h]@149
    CPC *v50; // [sp+1304h] [bp-194h]@4
    char v51; // [sp+130Bh] [bp-18Dh]@3
    char dest[128]; // [sp+130Ch] [bp-18Ch]@156
    char s1[256]; // [sp+138Ch] [bp-10Ch]@49
    char *s; // [sp+148Ch] [bp-Ch]@237
    int k; // [sp+1490h] [bp-8h]@86
    int j; // [sp+1494h] [bp-4h]@11

    if(a2->Unk361) return false;

    v51 = 0;
    if(strlen(a2->Unk372->Unk8))
    {
        v51 = 1;
        v50 = new CPC();

        v50->Unk4 = a2->Unk372->Unk4;
        v50->Unk768 = a2->Unk372->Unk768;

        if(a2->Unk372) delete a2->Unk372;

        a2->Unk372 = v50;
    }

    CDBCmd v48;

    v48.Init(&gserver.Unk41272);

    strcpy(this->Unk405160, "SELECT * FROM t_characters WHERE a_user_index=");
    IntCat(this->Unk405160, *(_DWORD *)a2, 0);
    strcat(this->Unk405160, " AND a_server=");
    IntCat(this->Unk405160, gserver.Unk41004, 0);
    strcat(this->Unk405160, " AND a_index=");
    IntCat(this->Unk405160, a2->Unk372->Unk4, 0);
    strcat(this->Unk405160, " AND a_enable=1");

    v48.SetQuery(this->Unk405160);
    v48.Open();

    if(v48.MoveNext())
    {
        v50 = a2->Unk372;
        v48.GetRec("a_name", v50->Unk8, 1);
        v48.GetRec("a_index", v50->Unk4);
        v48.GetRec("a_level", v50->Unk60);
        v48.GetRec("a_skill_point", v50->Unk72);
        v48.GetRec("a_admin", v50->Unk732);
        v48.GetRec("a_was_x", v50->Unk120);
        v48.GetRec("a_was_z", v50->Unk124);
        v48.GetRec("a_was_r", v50->Unk132);
        v48.GetRec("a_blood_point", v50->Unk752);
        v48.GetRec("a_job", v50->Unk477);
        v48.GetRec("a_hair_style", v50->Unk478);
        v48.GetRec("a_face_style", v50->Unk479);
        v48.GetRec("a_exp", v50->Unk64);
        v48.GetRec("a_str", v50->Unk756);
        v50->Unk84 = v50->Unk756;
        v48.GetRec("a_dex", v50->Unk758);
        v50->Unk86 = v50->Unk758;
        v48.GetRec("a_int", v50->Unk760);
        v50->Unk88 = v50->Unk760;
        v48.GetRec("a_con", v50->Unk762);
        v50->Unk90 = v50->Unk762;
        v48.GetRec("a_statpt_remain", v50->Unk740);
        v48.GetRec("a_statpt_str", v50->Unk742);
        v48.GetRec("a_statpt_dex", v50->Unk744);
        v48.GetRec("a_statpt_int", v50->Unk746);
        v48.GetRec("a_statpt_con", v50->Unk748);
        v48.GetRec("a_hp", v50->Unk76);
        v48.GetRec("a_max_hp", v50->Unk764);
        v48.GetRec("a_mp", v50->Unk80);
        v48.GetRec("a_max_mp", v50->Unk766);
        v48.GetRec("a_silence_pulse", v50->Unk784);
        v50->Unk784 += gserver.Unk41248;
        v48.GetRec("a_pkpenalty", v50->Unk1852);
        v48.GetRec("a_pkcount", v50->Unk1856);
        v48.GetRec("a_pkrecover", v50->Unk1860);
        v48.GetRec("a_pkpenaltyhp", v50->Unk1868);
        v48.GetRec("a_pkpenaltymp", v50->Unk1872);
        v48.GetRec("a_guildoutdate", v50->Unk2376);
        v48.GetRec("a_was_zone", (int)&v47);
        v48.GetRec("a_was_area", (int)&v46);
        v48.GetRec("a_was_yLayer", (int)&v45);

        if(a2->Unk356 != 1)
        {
            v47 = -1;
            v46 = -1;
            v45 = -1;
        }

        v44 = 0;
        v43 = -1;
        j = gserver.FindZone(v47);

        if(j != -1)
        {
            if(gserver.Unk452196[j].Unk4) v43 = j;
            v44 = 1;
        }

        if(!v44)
        {
            v47 = 0;
            j = gserver.FindZone(0);
            v44 = 1;
        }

        if(v44)
        {
            if(v47 >= 0 && v47 < gserver.Unk452192)
            {
                if(v45 >= 0 && v45 <= 2 * (gserver.Unk452196[v47].Unk28 - 1))
                {
                    v40 = gserver.FindZone(v47);

                    if(v40 == -1) v40 = gserver.FindZone(0);

                    v50->Unk408 = &gserver.Unk452196[v40];
                    v50->Unk412 = v50->Unk408->Unk36;
                    v50->Unk416 = 0;

                    if(v46)
                    {
                        v50->Unk120.Unk16 = v50->Unk408->Unk52[0]->Unk0;
                        v50->Unk120.Unk12 = 0;

                        v42 = 10;
                        do
                        {
                            if(--v42 == -1) break;

                            v41 = GetRandom(v50->Unk408->Unk52[0]->Unk4, v50->Unk408->Unk52[0]->Unk12);
                            v50->Unk120.Unk0 = v41 / 2.0;

                            v41 = GetRandom(v50->Unk408->Unk52[0]->Unk8, v50->Unk408->Unk52[0]->Unk16);
                            v50->Unk120.Unk4 = v41 / 2.0;
                        }
                        while(v50->Unk412->GetAttr(v50->Unk120.Unk16, v50->Unk120.Unk0, v50->Unk120.Unk4) == -1);
                    }
                    v50->Unk120.Unk16 = v45;
                }
                else
                {
                    v42 = gserver.FindZone(v47);
                    if(v42 == -1) v42 = gserver.FindZone(0);

                    v50->Unk408 = &gserver.Unk452196[v42];
                    v50->Unk412 = v50->Unk408->Unk36;
                    v50->Unk416 = 0;
                    v50->Unk120.Unk16 = v50->Unk408->Unk52[0]->Unk8;
                    v50->Unk120.Unk12 = 0;

                    v40 = 10;
                    do
                    {
                        if(--v40 == -1) break;

                        v41 = GetRandom(v50->Unk408->Unk52[2]->Unk4, v50->Unk408->Unk52[2]->Unk12);
                        v50->Unk120.Unk0 = v41 / 2.0;

                        v41 = GetRandom(v50->Unk408->Unk52[2]->Unk8, v50->Unk408->Unk52[2]->Unk16);
                        v50->Unk120.Unk4 = v41 / 2.0;
                    }
                    while(v50->Unk412->GetAttr(v50->Unk412, v50->Unk120.Unk16, v50->Unk120.Unk0, v50->Unk120.Unk4) == -1);
                }
            }
            else
            {
                v50->Unk408 = &gserver.Unk452196[gserver.FindZone(0)];
                v50->Unk412 = v50->Unk408->Unk36;
                v50->Unk416 = 0;
                v50->Unk120.Unk16 = v50->Unk408->Unk52[0]->Unk0;
                v50->Unk120.Unk12 = 0;

                v42 = 10;
                do
                {
                    if(--v42 == -1) break;

                    v41 = GetRandom(v50->Unk408->Unk52[0]->Unk4, v50->Unk408->Unk52[0]->Unk12);
                    v50->Unk120.Unk0 = v41 / 2.0;
                    v41 = GetRandom(v50->Unk408->Unk52[0]->Unk8, v50->Unk408->Unk52[0]->Unk16);
                    v50->Unk120.Unk4 = v41 / 2.0;
                }
                while(v50->Unk412->GetAttr(v50->Unk120.Unk16, v50->Unk120.Unk0, v50->Unk120.Unk4) == -1);
            }

            if(v50->Unk408->Unk4)
                v43 = 0x38E38E39 * (v50->Unk408 - gserver.Unk452196) >> 3;
            else
                v43 = -1;

            if(v43 == -1)
            {
                v40 = skillIndex_641;
                v42 = skillLevel_642;

                *skillIndex_641 = 0;
                *skillLevel_642 = 0;

                v48.GetRec("a_active_skill_index", skillIndex_641, true);
                v48.GetRec("a_active_skill_level", skillLevel_642, true);

                while(*v40 && *v42)
                {
                    v40 = AnyOneArg(v40, s1, false);
                    v37 = atoi(s1);
                    v42 = AnyOneArg(v42, s1, false);
                    v36 = atoi(s1);
                    v35 = gserver.Unk452220.Create(v37, v36);
                    if(v35)
                    {
                        if(v35->Unk0->IsActive())
                        {
                            v50->Unk480.Add(v35);
                        }
                        else
                        {
                            if(v35->Unk0->IsPassive())
                                v50->Unk492.Add(v35);
                            else
                                v50->Unk504.Add(v35);
                        }
                    }
                }

                v40 = skillIndex_641;
                v42 = skillLevel_642;

                *skillIndex_641 = 0;
                *skillLevel_642 = 0;

                v48.GetRec("a_passive_skill_index", skillIndex_641, true);
                v48.GetRec("a_passive_skill_level", skillLevel_642, true);

                while(*v40 && *v42)
                {
                    v40 = AnyOneArg(v40, s1, false);
                    v35 = atoi(s1);
                    v42 = AnyOneArg(v42, s1, false);
                    v36 = atoi(s1);
                    v37 = gserver.Unk452220.Create(v35, v36);
                    if(v37)
                    {
                        if(v37->Unk0->IsActive())
                        {
                            v50->Unk480.Add(v37);
                        }
                        else
                        {
                            if(v37->Unk0->IsPassive())
                                v50->Unk492.Add(v37);
                            else
                                v50->Unk504.Add(v37);
                        }
                    }
                }

                v40 = skillIndex_641;
                v42 = skillLevel_642;

                *skillIndex_641 = 0;
                *skillLevel_642 = 0;

                v48.GetRec("a_etc_skill_index", skillIndex_641, true);
                v48.GetRec("a_etc_skill_level", skillLevel_642, true);

                while(*v40 && *v42)
                {
                    v40 = AnyOneArg(v40, s1, false);
                    v35 = atoi(s1);
                    v42 = AnyOneArg(v42, s1, false);
                    v36 = atoi(s1);
                    v37 = gserver.Unk452220.Create(v35, v36);
                    if(v37)
                    {
                        if(v37->Unk0->IsActive())
                        {
                            v50->Unk480.Add(v37);
                        }
                        else
                        {
                            if(v37->Unk0->IsPassive())
                                v50->Unk492.Add(v37);
                            else
                                v50->Unk504.Add(v37);
                        }
                    }
                }

                *questIndex_643    = 0;
                *questValue_644    = 0;
                *questComplete_645 = 0;

                v35 = questIndex_643;
                v36 = questValue_644;
                v37 = questComplete_645;

                v48.GetRec("a_quest_index", questIndex_643, true);
                v48.GetRec("a_quest_value", questValue_644, true);
                v48.GetRec("a_quest_complete", questComplete_645, true);

                v34 = 0;
                while(*v35)
                {
                    v35 = AnyOneArg(v35, s1, false);
                    i = atoi(s1);
                    CQuestProto *v32 = gserver.Unk452228.FindProto(i);
                    if(v32)
                    {
                        v31 = new CQuest(v32);
                        l = v50->Unk1900.AddQuest(v31);
                        if(l != -1)
                        {
                            if(v32->Unk4 == 10) v34 = 1;

                            for(i = 0; *v36 && i <= 2; ++i)
                            {
                                v36 = AnyOneArg(v36, s1, false);
                                v50->Unk1900.Unk0[l]->Unk4[i] = atoi(s1);
                            }

                            v50->Unk1900.Unk40[l] = 1;
                        }
                    }
                }

                k = 0;
                while(*v37)
                {
                    v37 = AnyOneArg(v37, s1, 0);
                    j = atoi(s1);
                    v50->Unk1900.Unk64[k++] = j;
                }

                *strSSkill_646 = 0;

               char *v29_1 = strSSkill_646; // v29[1]

                v48.GetRec("a_sskill", strSSkill_646, true);

                while(*v29_1)
                {
                    v29_1 = AnyOneArg(v29_1, s1, 0);
                    l = atoi(s1);
                    v29_1 = AnyOneArg(v29_1, s1, 0);
                    v31 = atoi(s1);

                    CSSkillProto *v32 = gserver.Unk452244.FindProto(l);
                    if(v32)
                    {
                        CSSkill *i_0 = new CSSkill(v32, v31); // i
                        if(i_0)
                        {
                            bool v29_0 = true;
                            v27 = &v50->Unk716;

                            while(1)
                            {
                                v28 = v27;

                                if(!v27) break;

                                v27 = v27->Unk4;
                                if(i_0->Unk0->Unk16 != -1 && v28->Unk0->Unk0->Unk0->Unk8 == i_0->Unk0->Unk8) // CHECK
                                {
                                    if(v28->Unk0->Unk0->Unk0->Unk16 < i_0->Unk0->Unk16) // CHECK
                                    {
                                        if(v28->Unk0->Unk0->Unk0->Unk16 < i_0->Unk0->Unk16) // CHECK
                                            v50->Unk716.Remove(v28->Unk0->Unk0);
                                    }
                                    else
                                    {
                                        v29_0 = false;
                                    }
                                }
                            }

                            if(v29_0) v50->Unk716.Add(i);
                        }
                    }
                }

                v50->SetMaxWeight();

                strcpy(this->Unk405160, "SELECT * FROM t_assist WHERE a_char_index=");
                IntCat(this->Unk405160, v50->Unk4, 0);
                v48.SetQuery(this->Unk405160);
				
                if(v48.Open() && v48.MoveFirst())
                {
                    v48.GetRec("a_help_item", assistitem, 1);
                    v27 = (int)assistitem;
                    v48.GetRec("a_help_skill", assistskill, 1);
                    l = (int)assistskill;
                    v48.GetRec("a_help_level", assistlevel, 1);
                    v31 = (int)assistlevel;
                    v48.GetRec("a_help_remain", assistremain, 1);
                    v32 = assistremain;
                    v48.GetRec("a_help_hit0", assisthit0, 1);
                    v28 = (int)assisthit0;
                    v48.GetRec("a_help_hit1", assisthit1, 1);
                    i = (int)assisthit1;
                    v48.GetRec("a_help_hit2", assisthit2, 1);

                    v26 = (int)assisthit2;
                    bool v29_0 = false;

                    while(!v29_0)
                    {
                        *this->Unk400040 = 0;
                        v27 = AnyOneArg(v27, this->Unk400040, 0);
                        if(!*this->Unk400040)
                        {
                            v29_0 = true;
                            break;
                        }

                        v25 = atoi(this->Unk400040);
                        *this->Unk400040 = 0;
                        l = AnyOneArg(l, this->Unk400040, 0);
                        if(!*this->Unk400040)
                        {
                            v29_0 = true;
                            break;
                        }

                        v24 = atoi(this->Unk400040);
                        *this->Unk400040 = 0;
                        v31 = AnyOneArg(v31, this->Unk400040, 0);
                        if(!*this->Unk400040)
                        {
                            v29_0 = true;
                            break;
                        }

                        v23 = atoi(this->Unk400040);
                        *this->Unk400040 = 0;
                        v32 = (void *)AnyOneArg((int)v32, this->Unk400040, 0);
                        if(!*this->Unk400040)
                        {
                            v29_0 = true;
                            break;
                        }

                        v22 = atoi(this->Unk400040);
                        *this->Unk400040 = 0;
                        v28 = AnyOneArg(v28, this->Unk400040, 0);
                        if(!*this->Unk400040)
                        {
                            v29_0 = true;
                            break;
                        }

                        LOBYTE(v38) = atoi(this->Unk400040) != 0;
                        *this->Unk400040 = 0;
                        i = AnyOneArg(i, this->Unk400040, 0);
                        if(!*this->Unk400040)
                        {
                            v29_0 = true;
                            break;
                        }

                        BYTE1(v38) = atoi(this->Unk400040) != 0;
                        *this->Unk400040 = 0;
                        v26 = AnyOneArg(v26, this->Unk400040, 0);
                        if(!*this->Unk400040)
                        {
                            v29_0 = true;
                            break;
                        }

                        BYTE2(v38) = atoi(this->Unk400040) != 0;
                        v21 = CSkillProtoList::Find(gserver.Unk452220, v24);
                        if(v21 && (v25 <= 0 || gserver.Unk41208.FindIndex(v25)))
                            v50->Unk148.Add(v25, v21, v23, &v38, 0, v22);
                    }

                    v48.GetRec("a_curse_item", assistitem, 1);
                    v27 = (int)assistitem;
                    v48.GetRec("a_curse_skill", assistskill, 1);
                    l = (int)assistskill;
                    v48.GetRec("a_curse_level", assistlevel, 1);
                    v31 = (int)assistlevel;
                    v48.GetRec("a_curse_remain", assistremain, 1);
                    v32 = assistremain;
                    v48.GetRec("a_curse_hit0", assisthit0, 1);
                    v28 = (int)assisthit0;
                    v48.GetRec("a_curse_hit1", assisthit1, 1);
                    i = (int)assisthit1;
                    v48.GetRec("a_curse_hit2", assisthit2, 1);

                    v26 = (int)assisthit2;
                    v29_0 = false;

                    while(!v29_0)
                    {
                        *this->Unk400040 = 0;
                        v27 = AnyOneArg(v27, this->Unk400040, 0);
                        if(!*this->Unk400040)
                        {
                            v29_0 = true;
                            break;
                        }

                        v25 = atoi(this->Unk400040);
                        *this->Unk400040 = 0;
                        l = AnyOneArg(l, this->Unk400040, 0);
                        if(!*this->Unk400040)
                        {
                            v29_0 = true;
                            break;
                        }

                        v24 = atoi(this->Unk400040);
                        *this->Unk400040 = 0;
                        v31 = AnyOneArg(v31, this->Unk400040, 0);
                        if(!*this->Unk400040)
                        {
                            v29_0 = true;
                            break;
                        }

                        v23 = atoi(this->Unk400040);
                        *this->Unk400040 = 0;
                        v32 = (void *)AnyOneArg((int)v32, this->Unk400040, 0);
                        if(!*this->Unk400040)
                        {
                            v29_0 = true;
                            break;
                        }

                        v22 = atoi(this->Unk400040);
                        *this->Unk400040 = 0;
                        v28 = AnyOneArg(v28, this->Unk400040, 0);
                        if(!*this->Unk400040)
                        {
                            v29_0 = true;
                            break;
                        }

                        LOBYTE(v38) = atoi(this->Unk400040) != 0;
                        *this->Unk400040 = 0;
                        i = AnyOneArg(i, this->Unk400040, 0);
                        if(!*this->Unk400040)
                        {
                            v29_0 = true;
                            break;
                        }

                        BYTE1(v38) = atoi(this->Unk400040) != 0;
                        *this->Unk400040 = 0;
                        v26 = AnyOneArg(v26, this->Unk400040, 0);
                        if(!*this->Unk400040)
                        {
                            v29_0 = true;
                            break;
                        }

                        BYTE2(v38) = atoi(this->Unk400040) != 0;
                        v21 = gserver.Unk452220.Find(v24);
                        if(v21 && (v25 <= 0 || gserver.Unk41208.FindIndex(v25)))
                            v50->Unk148.Add(v25, v21, v23, &v38, 0, v22);
                    }
                }

                strcpy(this->Unk405160, "SELECT * FROM t_inven");
                IntCat0(this->Unk405160, v50->Unk4 % 10, 2, 0);
                StrCat(this->Unk405160, "WHERE a_char_idx=");
                IntCat(this->Unk405160, v50->Unk4, 0);
                StrCat(this->Unk405160, "ORDER BY a_tab_idx, a_row_idx");
                v48.SetQuery(this->Unk405160);

                if(v48.Open())
                {
                    for(int j = 0; j < v49 && v48.MoveNext(); ++j)
                    {
                        if(v48.GetRec("a_tab_idx", v21) && v48.GetRec("a_row_idx", v22))
                        {
                            for(int k = 0; k <= 4; ++k)
                            {
                                dest = 0;
                                IntCat(dest, k, 0);
                                strcpy(s1, "a_item_idx");
                                strcat(s1, dest);
                                if(v48.GetRec(s1, (int)&v23))
                                {
                                    if(v23 >= 0)
                                    {
                                        strcpy(s1, "a_wear_pos");
                                        strcat(s1, dest);
                                        if(v48.GetRec(s1, (int)v29))
                                        {
                                            strcpy(s1, "a_plus");
                                            strcat(s1, dest);
                                            if(v48.GetRec(s1, (int)&v24))
                                            {
                                                strcpy(s1, "a_flag");
                                                strcat(s1, dest);
                                                if(v48.GetRec(s1, (int)&v25))
                                                {
                                                    strcpy(s1, "a_used");
                                                    strcat(s1, dest);
                                                    if(v48.GetRec(s1, (int)&v26))
                                                    {
                                                        strcpy(s1, "a_serial");
                                                        strcat(s1, dest);
                                                        if(v48.GetRec(s1, (char *)src, 1))
                                                        {
                                                            strcpy(s1, "a_count");
                                                            strcat(s1, dest);
                                                            if(v48.GetRec(s1, 19))
                                                            {
                                                                if(v19 > 0)
                                                                {
                                                                    for(l = 0; l <= 4; ++l)
                                                                    {
                                                                        dest = 0;
                                                                        IntCat(dest, k, 0);
                                                                        strcpy(s1, "a_item");
                                                                        strcat(s1, dest);
                                                                        dest = 0;
                                                                        IntCat(dest, l, 0);
                                                                        strcat(s1, "_option");
                                                                        strcat(s1, dest);
                                                                        v48.GetRec(s1, v39[l]);
                                                                    }

                                                                    v31 = gserver.Unk41208.CreateDBItem(v23, v29[0], v24, v25, v26, src, v19, v39);
                                                                    if(v31)
                                                                    {
                                                                        v32 = (void *)v21;
                                                                        v28 = v22;
                                                                        i = k;
                                                                        if(v23 == *unk_8104594 || v23 == *unk_8104598)
                                                                        {
                                                                            v32 = 0;
                                                                            v28 = -1;
                                                                            i = -1;
                                                                        }
                                                                        if(v32)
                                                                        {
                                                                            if(v32 == (void *)1)
                                                                            {
                                                                                v7 = v50->Unk880;
                                                                            }
                                                                            else
                                                                            {
                                                                                if(v32 == (void *)2)
                                                                                    v7 = v50->Unk968;
                                                                                else
                                                                                    v7 = 0;
                                                                            }
                                                                        }
                                                                        else
                                                                        {
                                                                            v7 = v50->Unk792;
                                                                        }
                                                                        v27 = v7;
                                                                        if(v7)
                                                                        {
                                                                            if(CInventory::AddItem(v27, v31, v50, 0, 0, v28, i))
                                                                            {
                                                                                if(CItem::tab(v31) == -1)
                                                                                {
                                                                                    m = *(_DWORD *)(v31 + 28);
                                                                                    v17 = *(_DWORD *)(v31 + 36);
                                                                                    v16 = *(_DWORD *)(v31 + 40);
                                                                                    if(v31)
                                                                                        (*(void (__cdecl **)(int, signed int))(*(_DWORD *)(v31 + 220) + 8))(
                                                                                            v31,
                                                                                            3);
                                                                                    v31 = 0;
                                                                                    if(CInventory::FindItem(v27, (int)&n, (int)&v14, m, v17, v16))
                                                                                        v31 = CInventory::GetItem(v27, n, v14);
                                                                                }
                                                                                if(v31)
                                                                                {
                                                                                    if(*(_BYTE *)(v31 + 32) >= 0
                                                                                        && *(_BYTE *)(v31 + 32) <= 9
                                                                                        && !*(_DWORD *)(4 * *(_BYTE *)(v31 + 32) + v50->Unk1284))
                                                                                        *(_DWORD *)(4 * *(_BYTE *)(v31 + 32) + v50->Unk1284) = v31;
                                                                                    if(*(_DWORD *)(*(_DWORD *)(v31 + 20) + 4) == 4
                                                                                        && *(_DWORD *)(*(_DWORD *)(v31 + 20) + 8) == 5
                                                                                        && !*(_DWORD *)(v50->Unk1280))
                                                                                        *(_DWORD *)(v50->Unk1280) = v31;
                                                                                }
                                                                            }
                                                                            else
                                                                            {
                                                                                if(v31)
                                                                                    (*(void (__cdecl **)(int, signed int))(*(_DWORD *)(v31 + 220) + 8))(v31, 3);
                                                                                v31 = 0;
                                                                            }
                                                                        }
                                                                        else
                                                                        {
                                                                            if(v31)
                                                                                (*(void (__cdecl **)(_DWORD, _DWORD))(*(_DWORD *)(v31 + 220) + 8))(v31, 3);
                                                                            v31 = 0;
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

                strcpy(this->Unk405160, "SELECT * FROM t_stash");
                IntCat0(this->Unk405160, v50->Unk768->Unk0 % 10, 2, 0);
                StrCat(this->Unk405160, "WHERE a_user_idx=");
                IntCat(this->Unk405160, v50->Unk768->Unk0, 0);
                StrCat(this->Unk405160, "ORDER BY a_index");
                v48.SetQuery(this->Unk405160);

                if(v48.Open())
                {
                    for(int j = 0; j < v49 && v48.MoveNext(); ++j)
                    {
                        if(v48.GetRec("a_item_idx", v14) && v14 >= 0 && v48.GetRec("a_plus", n) && v48.GetRec("a_flag", v16) && v48.GetRec("a_serial", src, 1) && v48.GetRec("a_count", v19) && v19 > 0 && v48.GetRec("a_used", v17))
                        {
                            for(int m = 0; m <= 4; ++m)
                            {
                                strcpy(dest, "a_item_option");
                                IntCat(dest, m, 0);
                                v48.GetRec(dest, v39[m]);
                            }

                            v21 = gserver.Unk41208.CreateDBItem(v14, -1, n, v16, v17, src, v19, v39);
                            if(v21)
                            {
                                if(v50->Unk1056.add(v21) != -1) v21 = 0;
                            }
                        }
                    }
                }

                strcpy(this->Unk405160, "SELECT * FROM t_quickslot");
                IntCat0(this->Unk405160, *(_DWORD *)(v50->Unk4) % 10, 2, 0);
                StrCat(this->Unk405160, "WHERE a_char_idx=");
                IntCat(this->Unk405160, *(_DWORD *)(v50->Unk4), 0);
                StrCat(this->Unk405160, "ORDER BY a_char_idx, a_page_idx");
                v48.SetQuery(this->Unk405160);

                if(v48.Open())
                {
                    for(j = 0; j < v49 && v48.MoveNext(); ++j)
                    {
                        v48.GetRec("a_page_idx", v14);
                        s = v48.GetRec("a_slot");
                        for(n = 0; *s && n <= 9; ++n)
                        {
                            s = AnyOneArg(s, s1, 0);
                            v50->Unk1372[v14].Unk0[n] = atoi(s1);
                            v8 = v50->Unk1372[v14].Unk0[n];
                            if(v8)
                            {
                                if(v8 > 0)
                                {
                                    if(v8 == 1)
                                    {
                                        s = AnyOneArg(s, s1, 0);
                                        v50->Unk1372[v14].Unk80[n] = atoi(s1);
                                    }
                                    else
                                    {
                                        if(v8 == 2)
                                        {
                                            s = AnyOneArg(s, s1, 0);
                                            v16 = atoi(s1);
                                            s = AnyOneArg(s, s1, 0);
                                            v17 = atoi(s1);
                                            v50->Unk1372[v14].Unk120[n] = v50->Unk792.GetItem(v16, v17);
                                            if(!v50->Unk1372[v14].Unk120[n])
                                                v50->Unk1372[v14].Unk0[n] = -1;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                s = AnyOneArg(s, s1, 0);
                                v50->Unk1372[v14].Unk40[n] = atoi(s1);
                            }
                        }
                    }
                }

                strcpy(this->Unk405160, "SELECT * FROM t_mempos WHERE a_char_idx=");
                IntCat(this->Unk405160, v50->Unk4, 0);
                v48.SetQuery(this->Unk405160);

                if(v48.Open() && v48.MoveNext())
                {
                    for(j = 0; j <= 4; ++j)
                    {
                        strcpy(s1, "a_mem_");
                        IntCat(s1, j, 0);
                        s = v48.GetRec(s1);
                        if(strlen(s) > 6)
                        {
                            s = AnyOneArg(s, nptr, 0);
                            v16 = atoi(nptr);
                            *nptr = 0;

                            s = AnyOneArg(s, nptr, 0);
                            v12 = atof(nptr);
                            *nptr = 0;

                            s = AnyOneArg(s, nptr, 0);
                            v11 = atof(nptr);
                            *nptr = 0;

                            s = AnyOneArg(s, nptr, 0);
                            int _v29 = atoi(nptr); // v29[0]
                            nptr = 0;

                            char *v9_0 = SkipSpaces(s); // v9
                            strcpy(v10, v9_0);
                            nptr = 0;

                            v17 = gserver.FindZone(v16);
                            if(v17 >= 0)
                            {
                                if(gserver.Unk452196[v17].Unk45)
                                    v50->Unk1332.Write(j, v16, v12, v11, _v29, v10);
                            }
                        }
                    }
                }

                v50->CalcStatus(false);
                v50->InitStat();
                v50->CalcStatus(false);

                CNetMsg src;

                if(v34)
                    DBOKMsg(src, 6);
                else
                    DBOKMsg(src, v50->Unk408->Unk0);

                a2->Unk124.Add(src);
                v50->Unk476 = 1;

                return true;
            }
            else
            {
                CNetMsg v38;

                DBOtherServerMsg(v38, gserver.Unk452196[v43].Unk0, gserver.Unk452196[v43].Unk5, gserver.Unk452196[v43].Unk26);
                a2->Unk124.Add(v38);

                return true;
            }
        }
    }

    return false;
}*/

void CDBThread::BackSlash(char *a1,char const *a2)
{
    while(*a2)
    {
        *a1++ = *a2;

        if(*a2 == 92)
            *a1++ = 92;

        ++a2;
    }

    *a1 = 0;
}

void CDBThread::GetDateStr(char *a1)
{
    int v3[11]; // [sp+8h] [bp-30h]@1
    time_t timer; // [sp+34h] [bp-4h]@1

    timer = time(0);
    memcpy(v3, localtime(&timer), 44);

    *a1 = 0;

    IntCat0(a1, v3[5] + 1900, 4, 0);
    strcat(a1, "/");
    IntCat0(a1, v3[4] + 1, 2, 0);
    strcat(a1, "/");
    IntCat0(a1, v3[3], 2, 0);
    strcat(a1, " ");
    IntCat0(a1, v3[2], 2, 0);
    strcat(a1, ":");
    IntCat0(a1, v3[1], 2, 0);
    strcat(a1, ":");
    IntCat0(a1, v3[0], 2, 0);
}

void CDBThread::TrimString(char *s)
{
    size_t v1; // [sp+10h] [bp-8h]@11
    const char *i; // [sp+14h] [bp-4h]@2

    if(!s) return;

    for(i = s; *i && (*i == 32 || *i > 8 && *i <= 13); ++i);
    while(*i) *s++ = *i++;

    while(1)
    {
        v1 = strlen(s);

        if(!v1 || (s[v1 - 1] != 32 && (s[v1 - 1] <= 8 || s[v1 - 1] > 13))) break;

        s[v1 - 1] = 0;
    }
}

void CDBThread::Wait300Millis(void)
{
    struct timeval timeout; // [sp+1Ch] [bp-8h]@1

    timeout.tv_sec = 0;
    timeout.tv_usec = 300000;

    select(0, 0, 0, 0, &timeout);
}

