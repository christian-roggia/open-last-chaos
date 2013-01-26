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

#include "Option.h"
#include "PC.h"
#include "Server.h"

COptionProto::COptionProto(void)
{
    this->Unk0 = 0;
    this->Unk4 = -1;
    memset(this->Unk8 , 0, 28);
    memset(this->Unk36, 0, 28);
    this->Unk64 = 0;
    this->Unk68 = 0;
    this->Unk72 = 0;
}

COptionProtoList::COptionProtoList(void)
{
    this->Unk0 = 0;
    this->Unk4 = 0;
}

COptionProtoList::~COptionProtoList()
{
    if(this->Unk0 && this->Unk0)
        delete [] this->Unk0;
    this->Unk0 = 0;
    this->Unk4 = 0;
}

bool COptionProtoList::Load(void)
{
    char *v6; // [sp+58h] [bp-103Ch]@9
    char *v7; // [sp+5Ch] [bp-1038h]@9
    char *nptr = 0; // [sp+60h] [bp-1034h]@13
    int v9; // [sp+6Ch] [bp-1028h]@9

    CDBCmd v11;

    v11.Init(&gserver.Unk41816);
    v11.SetQuery("SELECT * FROM t_option ORDER BY a_index");

    if(!v11.Open())
        return false;

    this->Unk4 = v11.AffectedRows;
    this->Unk0 = new COptionProto[this->Unk4]; // TO CHECK!!

    if(v11.MoveFirst())
    {
        optionLevel_537[0] = 0;
        optionProb_538[0] = 0;

        for(int i = 0; i < this->Unk4; ++i)
        {
            v11.GetRec("a_index",   this->Unk0[i].Unk0);
            v11.GetRec("a_type",    this->Unk0[i].Unk4);

            v7 = optionLevel_537;
            v6 = optionProb_538;

            v11.GetRec("a_level",   optionLevel_537, 1);
            v11.GetRec("a_prob",    optionProb_538, 1);

            v9 = 0;
            while(*v7 && *v6)
            {
                v7 = AnyOneArg(v7, nptr, false);
                this->Unk0[i].Unk8[v9] = atoi(nptr);
                v6 = AnyOneArg(v6, nptr, false);
                this->Unk0[i].Unk36[v9] = atoi(nptr);
            }

            v11.GetRec("a_weapon_type",     this->Unk0[i].Unk64);
            v11.GetRec("a_wear_type",       this->Unk0[i].Unk68);
            v11.GetRec("a_accessory_type",  this->Unk0[i].Unk72);
            v11.MoveNext();
        }
    }

    return true;
}

COptionProto *COptionProtoList::FindProto(int a2)
{
    COptionProto key;
    key.Unk4 = a2;

    return (COptionProto *)bsearch(&key, this->Unk0, this->Unk4, sizeof(COptionProto), COptionProtoList::CompIndex);
}

int COptionProtoList::CompIndex(void const *a1, void const *a2)
{
    return ((COptionProto *)a1)->Unk4 - ((COptionProto *)a2)->Unk4;
}

COption::COption(void)
{
    this->Unk0  = 0;
    this->Unk4  = -1;
    this->Unk8  = 0;
    this->Unk12 = 0;
    this->Unk16 = 0;
}

void COption::MakeOptionValue(COptionProto *a2, int a3, int a4)
{
    signed int v5; // [sp+1Ch] [bp-2Ch]@10
    unsigned int v6; // [sp+20h] [bp-28h]@9
    int v8[4]; // [sp+28h] [bp-20h]@2
    int v12[4]; // [sp+38h] [bp-10h]@2

    if(a2)
    {
        this->Unk0 = a2;
        this->Unk4 = a2->Unk4;

        v8[0] = this->Unk0->Unk36[3];
        v8[1] = this->Unk0->Unk36[2] + this->Unk0->Unk36[3];
        v8[2] = this->Unk0->Unk36[2] + this->Unk0->Unk36[3] + this->Unk0->Unk36[1];
        v8[3] = this->Unk0->Unk36[1] + this->Unk0->Unk36[2] + this->Unk0->Unk36[3] + this->Unk0->Unk36[0];
        v12[0] = v8[0];
        v12[1] = v8[1];
        v12[2] = v8[2];
        v12[3] = v8[3];

        if(!a4)
            a4 = 1;

        for(int i = 0; i <= 3; ++i)
        {
            v8[i] = v12[i] * a3 / a4;

            if(v12[i] * a3 / a4 > limit_548[i])
                v8[i] = limit_548[i];
        }

        v6 = GetRandom(1, 10000);
        v5 = (v6 > (unsigned int)v8[2]) ? ((v6 > (unsigned int)v8[3]) ? 1 : 2) : 3;

        if(a2->Unk4 > 25 && v5 > 3)
            v5 = 3;

        this->Unk8 = v5;
        this->Unk12 = this->Unk0->Unk8[(v5 - 1)];
    }
}

// ABSOLUTELY TO CHECK
void COption::ApplyOptionValue(CPC *a2)
{
    /*if(a2->Unk477 <= 5 && a2->Unk477 >= 0 && this->Unk4 >= 0)
    {
        if(this->Unk4 <= 0x23u)
            JUMPOUT(__CS__, off_80D0684[this->Unk4]);
    }*/
}

void COption::GetDBValue(short a2)
{
    this->Unk16 = a2;
    this->Unk4 = (signed short)(a2 >> 8);
    this->Unk8 = (unsigned char)a2;

    if(this->Unk8 <= 0)
        this->Unk4 = -1;
}

void COption::SetDBValue(void)
{
    this->Unk16 = 0;
    this->Unk16 |= (this->Unk4 >> 8); // HIBYTE(v2) = (char)this->Unk4; LOBYTE(v2) = 0;
    this->Unk16 |= (this->Unk8 >> 8); // v3 = (short)this->Unk8; HIBYTE(v3) = 0;
}

int limit_548[4] = {100, 600, 2600, 6600};
char optionLevel_537[255];
char optionProb_538[255];
