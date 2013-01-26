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

#include "NPCProto.h"
#include "NPC.h"
#include "Server.h"

CNPCProto::CNPCProto(void)
{
    this->Unk0   = -1;
    *this->Unk4   = 0;
    this->Unk56  = 0;
    this->Unk60  = 0;
    this->Unk64  = 0;
    this->Unk68  = 0;
    this->Unk76  = 0;
    this->Unk80  = 0;
    this->Unk84  = 0;
    this->Unk88  = 0;
    this->Unk90  = 0;
    this->Unk296 = 0;
    this->Unk298 = 0;
    this->Unk300 = 0;
    this->Unk302 = 0;
    this->Unk92  = 0;
    this->Unk100 = 0;
    this->Unk102 = 0;
    this->Unk96  = -1;
    memset(this->Unk104, -1, 80);
    memset(this->Unk184,  0, 80);
    memset(this->Unk268, -1, 20);
    this->Unk264 = 0;
    this->Unk309 = 0;
    this->Unk312 = 0;
    this->Unk316 = 0;
    memset(this->Unk320, 0, 8);
    memset(this->Unk328, 0, 8);
    memset(this->Unk336, 0, 8);
    this->Unk344 = 0;
}

CNPCProto::~CNPCProto()
{
    ;
}

CNPCProtoList::CNPCProtoList(void)
{
    this->Unk0 = 0;
    this->Unk4 = 0;
    this->Unk8 = 1;
}

CNPCProtoList::~CNPCProtoList()
{
    delete [] this->Unk0; // CHECK THIS!!!

    this->Unk0 = 0;
    this->Unk4 = 0;
    this->Unk8 = 1;
}

bool CNPCProtoList::Load(void)
{
    char *v2; // STB8_4@23
    char *v8; // [sp+98h] [bp-1030h]@21
    float v9; // [sp+9Ch] [bp-102Ch]@9
    int v11; // [sp+A4h] [bp-1024h]@9

    delete [] this->Unk0; // CHECK THIS!!!

    this->Unk0 = 0;
    this->Unk4 = 0;
    this->Unk8 = 1;

    CDBCmd v12;

    v12.Init(&gserver.Unk41816);
    strcpy(g_buf, "SELECT * FROM t_npc WHERE a_enable=1 ORDER BY a_index");
    v12.SetQuery(g_buf);
    v12.Open();

    this->Unk4 = v12.AffectedRows;
    this->Unk0 = new CNPCProto[this->Unk4]; // CHECK THIS!!!

    v11 = 0;
    v9 = 1.0;
    g_buf2[0] = 0;
    g_buf3[0] = 0;

    while(v12.MoveNext())
    {
        v12.GetRec("a_index",       this->Unk0[v11].Unk0  );
        v12.GetRec("a_name_chn",    this->Unk0[v11].Unk4, true);
        v12.GetRec("a_level",       this->Unk0[v11].Unk56 );
        v12.GetRec("a_exp",         this->Unk0[v11].Unk60 );
        v12.GetRec("a_prize",       this->Unk0[v11].Unk64 );
        v12.GetRec("a_sight",       this->Unk0[v11].Unk68 );
        v12.GetRec("a_skill_point", this->Unk0[v11].Unk72 );
        v12.GetRec("a_walk_speed",  this->Unk0[v11].Unk76 );
        v12.GetRec("a_run_speed",   this->Unk0[v11].Unk80 );
        v12.GetRec("a_size",        this->Unk0[v11].Unk84 );
        v12.GetRec("a_flag",        this->Unk0[v11].Unk92 );
        v12.GetRec("a_recover_hp",  this->Unk0[v11].Unk100);
        v12.GetRec("a_recover_mp",  this->Unk0[v11].Unk102);
        v12.GetRec("a_family",      this->Unk0[v11].Unk96 );
        this->Unk0[v11].Unk264 = 0;

        for(int k = 0; k <= 19; ++k)
        {
            strcpy(g_buf, "a_item_");
            IntCat(g_buf, k, 0);
            v12.GetRec(g_buf, this->Unk0[v11].Unk104[k]);

            if(this->Unk0[v11].Unk104[k] == -1)
                break;

            strcpy(g_buf, "a_item_percent_");
            IntCat(g_buf, k, 0);
            v12.GetRec(g_buf, this->Unk0[v11].Unk184[k]);
            ++this->Unk0[v11].Unk264;
        }

        v12.GetRec("a_move_area",       this->Unk0[v11].Unk344);
        v12.GetRec("a_attack_area",     this->Unk0[v11].Unk312);
        v12.GetRec("a_str",             this->Unk0[v11].Unk288);
        v12.GetRec("a_dex",             this->Unk0[v11].Unk290);
        v12.GetRec("a_int",             this->Unk0[v11].Unk292);
        v12.GetRec("a_con",             this->Unk0[v11].Unk294);
        v12.GetRec("a_hp",              this->Unk0[v11].Unk88 );
        v12.GetRec("a_mp",              this->Unk0[v11].Unk90 );
        v12.GetRec("a_attackSpeed",     this->Unk0[v11].Unk309);
        v12.GetRec("a_attackType",      this->Unk0[v11].Unk308);
        v12.GetRec("a_attack",          this->Unk0[v11].Unk296);
        v12.GetRec("a_magic",           this->Unk0[v11].Unk298);
        v12.GetRec("a_defense",         this->Unk0[v11].Unk300);
        v12.GetRec("a_resist",          this->Unk0[v11].Unk302);
        v12.GetRec("a_attacklevel",     this->Unk0[v11].Unk304);
        v12.GetRec("a_defenselevel",    this->Unk0[v11].Unk306);
        v12.GetRec("a_scale", v9);

        this->Unk0[v11].Unk84  = this->Unk0[v11].Unk84  * v9;
        this->Unk0[v11].Unk312 = this->Unk0[v11].Unk312 * v9;

        for(int k = 0; k <= 4; ++k)
        {
            strcpy(g_buf, "a_product");
            IntCat(g_buf, k, 0);
            v12.GetRec(g_buf, this->Unk0[v11].Unk268[k]);
        }

        for(int k = 0; k <= 1; ++k)
        {
            sprintf(g_buf, "a_skill%d", k);
            if(v12.GetRec(g_buf, g_buf2, 1))
            {
                v8 = AnyOneArg(g_buf2, g_buf, false);
                if(strlen(g_buf) && atoi(g_buf) > 0)
                {
                    this->Unk0[v11].Unk320[k] = atoi(g_buf);
                    v2 = AnyOneArg(v8, g_buf, false);
                    this->Unk0[v11].Unk328[k] = atoi(g_buf);
                    AnyOneArg(v2, g_buf, false);
                    this->Unk0[v11].Unk336[k] = atoi(g_buf);
                }
                else
                {
                    this->Unk0[v11].Unk320[k] = -1;
                    this->Unk0[v11].Unk328[k] = 0;
                    this->Unk0[v11].Unk336[k] = 0;
                }
            }
        }
        ++v11;
    }

    return true;
}

CNPC *CNPCProtoList::Create(int a2)
{
    CQuestProto *v11; // [sp+20h] [bp-20h]@11
    CNPC *v14; // [sp+28h] [bp-18h]@3
    CNPCProto *v16; // [sp+3Ch] [bp-4h]@1

    v16 = this->FindProto(a2);

    if(v16)
    {
        v14 = new CNPC();

        v14->Unk464 = v16;
        v14->Unk468 = v16->Unk0;
        v14->Unk508 = v16->Unk344;
        v14->Unk472 = v16->Unk92;
        v14->ResetStat();
        v14->Unk4   = this->Unk8++;
        strcpy(v14->Unk8, v16->Unk4);
        v14->Unk60  = v16->Unk56;
        v14->Unk64  = v16->Unk60;
        v14->InitPointsToMax();
        v14->Unk72  = v16->Unk72;
        v14->Unk516 = GetRandom(0, 1) ? 1 : -1;

        if(v14->Unk464->Unk92 & 0x100)
        {
            for(int i = 0; i < gserver.Unk452228.Unk4; ++i)
            {
                v11 = &gserver.Unk452228.Unk0[i];
                if(v11 && !v11->Unk12)
                {
                    if(v11->Unk16 == v14->Unk468)
                        v14->Unk528[v14->Unk728++] = v11->Unk0;
                }
            }
        }

        for(int j = 0; j <= 1; ++j)
        {
            if(v16->Unk320[j] > 0)
                v14->Unk732[j] = gserver.Unk452220.Create(v16->Unk320[j], v16->Unk328[j]);
        }

        return v14;
    }
    else
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("Can't Create NPC Num");
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls(a2);
        g_gamelogbuffer.__ls(end);

        return 0;
    }
}

CNPCProto *CNPCProtoList::FindProto(int a2)
{
    CNPCProto key;
    key.Unk0 = a2;

    return (CNPCProto *)bsearch(&key, this->Unk0, this->Unk4, sizeof(CNPCProto), CNPCProtoList::CompIndex);
}

int CNPCProtoList::CompIndex(void const *a1, void const *a2)
{
    return ((CNPCProto *)a1)->Unk0 - ((CNPCProto *)a2)->Unk0;
}
