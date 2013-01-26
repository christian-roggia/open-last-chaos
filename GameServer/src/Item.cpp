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

#include "Item.h"
#include "Server.h"

CItem::CItem(void)
{
    this->Unk20 = 0;
    this->Unk0 = -1;
    this->Unk4 = -1;
    this->Unk8 = -1;
    this->Unk24 = -1;
    this->Unk28 = -1;
    this->Unk32 = -1;
    this->Unk36 = 0;
    this->Unk40 = 0;
    memset(this->Unk44, 0, 20);
    this->Unk12 = 0;
    this->Unk64 = -1;
    this->Unk172 = 0;
    this->Unk176.__as(CPos(0.0, 0.0, 0.0, 0.0, 0));
    this->Unk196 = -100;
    this->Unk200 = -100;
    this->Unk204 = 0;
    this->Unk208 = 0;
    this->Unk212 = 0;
    this->Unk216 = -1;
    this->Unk168 = 0;
}

CItem::~CItem()
{
    this->Unk20 = 0;
}

int CItem::tab(void)
{
    return this->Unk0;
}

int CItem::row(void)
{
    return this->Unk4;
}

int CItem::col(void)
{
    return this->Unk8;
}

long long CItem::Count(void)
{
    return this->Unk12;
}

bool CItem::IsRangeWeapon(void)
{
    return !this->Unk20->Unk4 && this->Unk20->Unk8 == 6;
}

bool CItem::IsMagicWeapon(void)
{
    return !this->Unk20->Unk4 && (this->Unk20->Unk8 == 5 || this->Unk20->Unk8 == 2);
}

bool CItem::IsWeaponType(void)
{
    return (this->Unk20->Unk4) ? false : (this->Unk20->Unk8 <= 7 && this->Unk20->Unk8 >= 0);
}

bool CItem::IsArmorType(void)
{
    return (this->Unk20->Unk4 == 1) ? (this->Unk20->Unk8 <= 5 && this->Unk20->Unk8 >= 0) : false;
}

bool CItem::IsAccessary(void)
{
    return this->Unk20->Unk4 == 5;
}

CItemProto::CItemProto(void)
{
    this->Unk0   = -1;
    this->Unk4   = -1;
    this->Unk8   = -1;
    *this->Unk12  = 0;
    this->Unk64  = 0;
    this->Unk68  = 0;
    this->Unk72  = -1;
    this->Unk76  = 0;
    this->Unk80  = 0;
    this->Unk84  = 0;
    this->Unk88  = 0;
    this->Unk92  = 0;
    this->Unk96  = 0;
    this->Unk100 = 0;
    this->Unk104 = 0;
    this->Unk108 = -1;
    memset(this->Unk112, -1, 40);
    memset(this->Unk152, 0, 40);
    this->Unk192 = -1;
    this->Unk196 = 0;
    this->Unk200 = -1;
    this->Unk204 = 0;
}

CItemProto::~CItemProto()
{
    ;
}

CItemList::CItemList(void)
{
    this->Unk8  = 0;
    this->Unk4  = 1;
    this->Unk0  = 0;
    this->Unk12 = 0;
    this->Unk16 = 0;
    this->Unk20 = 0;
    this->Unk24 = 0;
    this->Unk28 = 0;
    this->Unk32 = 0;
}

CItemList::~CItemList()
{
    if(this->Unk8 && this->Unk8)
        delete [] this->Unk8; // CHECK

    this->Unk8 = 0;
    this->Unk0 = 0;
}

void CItemList::Load(void)
{
    int v11; // [sp+44h] [bp-1024h]@13

    delete [] this->Unk8; // CHECK

    this->Unk8 = 0;
    this->Unk0 = 0;

    CDBCmd v12;

    v12.Init(&gserver.Unk41816);
    strcpy(g_buf, "SELECT * FROM t_item WHERE a_enable=1 ORDER BY a_index");
    v12.SetQuery(g_buf);

    if(v12.Open())
    {
        if(v12.AffectedRows)
        {
            this->Unk0 = v12.AffectedRows;
            this->Unk8 = new CItemProto[this->Unk0]; // CHECK THIS TOO

            v11 = 0;
            while(v12.MoveNext())
            {
                *g_buf2 = 0;

                v12.GetRec("a_index",       this->Unk8[v11].Unk0  );
                v12.GetRec("a_type_idx",    this->Unk8[v11].Unk4  );
                v12.GetRec("a_subtype_idx", this->Unk8[v11].Unk8  );
                v12.GetRec("a_name_chn",    this->Unk8[v11].Unk12, true);
                v12.GetRec("a_job_flag",    this->Unk8[v11].Unk64 );
                v12.GetRec("a_flag",        this->Unk8[v11].Unk68 );
                v12.GetRec("a_num_0",       this->Unk8[v11].Unk76 );
                v12.GetRec("a_num_1",       this->Unk8[v11].Unk80 );
                v12.GetRec("a_num_2",       this->Unk8[v11].Unk84 );
                v12.GetRec("a_num_3",       this->Unk8[v11].Unk88 );
                v12.GetRec("a_num_4",       this->Unk8[v11].Unk92 );
                v12.GetRec("a_weight",      this->Unk8[v11].Unk96 );
                v12.GetRec("a_level",       this->Unk8[v11].Unk100);
                v12.GetRec("a_price",       this->Unk8[v11].Unk104);
                v12.GetRec("a_wearing",     this->Unk8[v11].Unk108);
                v12.GetRec("a_max_use",     this->Unk8[v11].Unk72 );

                for(int k = 0; k <= 9; ++k)
                {
                    strcpy(g_buf2, "a_need_item");
                    IntCat(g_buf2, k, 0);
                    v12.GetRec(g_buf2, this->Unk8[v11].Unk112[k]);
                    strcpy(g_buf2, "a_need_item_count");
                    IntCat(g_buf2, k, 0);
                    v12.GetRec(g_buf2, this->Unk8[v11].Unk152[k]);
                }

                v12.GetRec("a_need_sskill",         this->Unk8[v11].Unk192);
                v12.GetRec("a_need_sskill_level",   this->Unk8[v11].Unk196);
                v12.GetRec("a_need_sskill2",        this->Unk8[v11].Unk200);
                v12.GetRec("a_need_sskill_level2",  this->Unk8[v11].Unk204);

                if(this->Unk8[v11].Unk4 == 2)
                {
                    if(!this->Unk8[v11].Unk8)
                    {
                        if(this->Unk8[v11].Unk76)
                        {
                            if(this->Unk8[v11].Unk76 == 1)
                                this->Unk24 = &this->Unk8[v11]; // 212 * v11 + *(_DWORD *)(a1 + 8) <-------- CHECK!!!
                        }
                    }
                }
                else
                {
                    if(this->Unk8[v11].Unk4 == 4 && this->Unk8[v11].Unk8 == 5)
                        this->Unk12 = &this->Unk8[v11]; // 212 * v11 + *(_DWORD *)(a1 + 8) <-------- CHECK!!!
                }

                if(this->Unk8[v11].Unk0 == 85)
                {
                    this->Unk20 = &this->Unk8[v11]; // 212 * v11 + *(_DWORD *)(a1 + 8) <-------- CHECK!!!
                }
                else
                {
                    if(this->Unk8[v11].Unk0 > 85)
                    {
                        if(this->Unk8[v11].Unk0 == 141)
                        {
                            this->Unk32 = &this->Unk8[v11]; // 212 * v11 + *(_DWORD *)(a1 + 8) <-------- CHECK!!!
                        }
                        else
                        {
                            if(this->Unk8[v11].Unk0 == 142)
                                this->Unk28 = &this->Unk8[v11]; // 212 * v11 + *(_DWORD *)(a1 + 8) <-------- CHECK!!!
                        }
                    }
                    else
                    {
                        if(this->Unk8[v11].Unk0 == 84)
                            this->Unk16 = &this->Unk8[v11]; // 212 * v11 + *(_DWORD *)(a1 + 8) <-------- CHECK!!!
                    }
                }
                ++v11;
            }
        }
    }
}

CItemProto *CItemList::FindIndex(int a2)
{
    CItemProto key;
    key.Unk0 = a2;

    return (CItemProto *)bsearch(&key, this->Unk8, this->Unk0, sizeof(CItemProto), CItemList::CompIndex);
}

CItem *CItemList::CreateDBItem(int a2, char a3, int a4, int a5, int a6, char const *src, long long a8, short *a9)
{
    CItem *v13; // [sp+4Ch] [bp-Ch]@7
    CItemProto *v14; // [sp+50h] [bp-8h]@5

    if(a8)
    {
        if(!a2)
            a2 = gserver.Unk41208.Unk12->Unk0; // *unk_8104584

        v14 = this->FindIndex(a2);

        if(v14)
        {
            v13 = new CItem();
            v13->Unk20 = v14;
            v13->Unk0 = -1;
            v13->Unk4 = -1;
            v13->Unk8 = -1;
            v13->Unk24 = this->GetNextVirtualIndex();
            v13->Unk28 = v14->Unk0;
            v13->Unk32 = a3;
            v13->Unk36 = a4;
            v13->Unk40 = a5;
            v13->Unk64 = a6;
            strncpy(v13->Unk44, src, 20);
            v13->Unk44[19] = 0;
            v13->Unk12 = a8;

            for(int i = 0; i <= 4; ++i)
            {
                v13->Unk68[i].GetDBValue(a9[i]);
                if(v13->Unk68[i].Unk8 > 0) // *(_DWORD *)(20 * i + v13 + 76) -> *(_DWORD *)(20 * i + v13 + 68 + 8)
                {
                    v13->Unk68[i].Unk0 = gserver.Unk452236.FindProto(v13->Unk68[i].Unk4); // CHECK
                    if(v13->Unk68[i].Unk0)
                    {
                        ++v13->Unk168;
                        // --------------------- TO FUCKING CHECK THIS ------------------- //
                        v13->Unk68[i].Unk12 = v13->Unk68[i].Unk0[v13->Unk68[i].Unk8 - 1].Unk8[0]; // *(_DWORD *)(20 * i + v13 + 80) -> *(_DWORD *)(20 * i + v13 + 68 + 12)
                    }
                }
            }
            return v13;
        }
    }

    return 0;
}

CItem *CItemList::CreateItem(int a2, char a3, int a4, int a5, long long a6)
{
    CItem *v18; // [sp+1Ch] [bp-1Ch]@7
    CItemProto *v20; // [sp+30h] [bp-8h]@5
    char v21; // [sp+37h] [bp-1h]@1

    v21 = a3;
    if(a6)
    {
        if(!a2)
            a2 = gserver.Unk41208.Unk12->Unk0; // *unk_8104584

        v20 = this->FindIndex(a2);

        if(v20)
        {
            v18 = new CItem();
            v18->Unk20 = v20;
            v18->Unk0  = -1;
            v18->Unk4  = -1;
            v18->Unk8  = -1;
            v18->Unk24 = this->GetNextVirtualIndex();
            v18->Unk28 = v20->Unk0;
            v18->Unk32 = v21;
            v18->Unk36 = a4;
            v18->Unk40 = a5;
            v18->Unk64 = v20->Unk72;
            GetSerial(v18->Unk44, v18->Unk24);

            if(v20->Unk68 & 1)
            {
                v18->Unk12 = a6;
            }
            else
            {
                v18->Unk12 = 1;
            }

            return v18;
        }
        else
        {
            g_gamelogbuffer.__ls(init("SYS_ERR"));
            g_gamelogbuffer.__ls("Can't Create Item Index");
            g_gamelogbuffer.__ls(a2);
            g_gamelogbuffer.__ls(delim);
            g_gamelogbuffer.__ls(a4);
            g_gamelogbuffer.__ls(delim);
            g_gamelogbuffer.__ls(a5);
            g_gamelogbuffer.__ls(delim);
            g_gamelogbuffer.__ls(a6);
            g_gamelogbuffer.__ls(end);
        }
    }

    return 0;
}

int CItemList::CompIndex(void const *a1, void const *a2)
{
    return ((CItemProto *)a1)->Unk0 - ((CItemProto *)a2)->Unk0;
}

int CItemList::GetNextVirtualIndex(void)
{
    if(++this->Unk4 <= 0)
        this->Unk4 = 1;

    return this->Unk4;
}

/********************************************************************************
 * Serialization Function
 ********************************************************************************/

char code62[63] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

void GetSerial(char *a1, int a2)
{
    int v3; // [sp+24h] [bp-4h]@1
    int v4; // [sp+34h] [bp+Ch]@5

    v3 = (20 * gserver.Unk41004 + gserver.Unk41008) % 62;

    if(v3 < 0)
        v3 = 0;

    a1[0] = code62[v3 % 62];
    a1[1] = code62[gserver.Unk41056 % 62];
    a1[2] = code62[gserver.Unk41060 % 62];
    a1[3] = code62[gserver.Unk41064 % 62];
    a1[4] = code62[gserver.Unk41068 % 62];
    a1[5] = code62[gserver.Unk41072 % 62];

    if(a2 < 0)
        a2 = -a2;

    v4 = a2 % 238328;

    a1[8] = code62[v4 % 62];

    v4 /= 62;
    a1[7] = code62[v4 % 62];
    a1[6] = code62[v4 / 62 % 62];
    a1[9] = 0;
}
