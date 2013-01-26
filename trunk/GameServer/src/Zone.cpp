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

#include "Zone.h"
#include "Server.h"

CZone::CZone(void)
{
    this->Unk0  = -1;
    this->Unk4  = 0;
    *this->Unk5  = 0;
    this->Unk26 = 0;
    this->Unk28 = 0;
    this->Unk32 = 0;
    this->Unk36 = 0;
    this->Unk40 = 0;
    this->Unk44 = 0;
    this->Unk52 = 0;
    this->Unk56 = 0;
    this->Unk60 = 0;
    this->Unk64 = 100;
    this->Unk68 = 100;
    this->Unk45 = 0;
}

CZone::~CZone()
{
    delete [] this->Unk36; // CHECK THIS!!!
    delete [] this->Unk32; // CHECK THIS!!!

    if(this->Unk52)
    {
        for(int k = 0; k < this->Unk48; ++k)
        {
            if(this->Unk52[k])
              delete this->Unk52[k];
        }

        if(this->Unk52)
            delete this->Unk52;

        this->Unk52 = 0;
    }

    this->Unk0  = -1;
    this->Unk4  = 0;
    *this->Unk5  = 0;
    this->Unk26 = 0;
    this->Unk28 = 0;
    this->Unk32 = 0;
    this->Unk36 = 0;

    delete [] this->Unk56; // CHECK THIS!!!

    this->Unk56 = 0;
    this->Unk60 = 0;
    this->Unk44 = 0;
    this->Unk64 = 100;
    this->Unk68 = 100;
}

bool CZone::LoadZone(int a2)
{
    char *v17; // [sp+94h] [bp-210B4h]@60
    //char v18[6]; // [sp+9Ah] [bp-210AEh]@21
    char *v19; // [sp+A0h] [bp-210A8h]@21
    char v20[256]; // [sp+   A4h] [bp-210A4h]@19
    char v21[256]; // [sp+  1A4h] [bp-20FA4h]@52
    char v22[256]; // [sp+  2A4h] [bp-20EA4h]@54
    char v23[256]; // [sp+  3A4h] [bp-20DA4h]@56
    char v24[256]; // [sp+  4A4h] [bp-20CA4h]@58
    char v25[256]; // [sp+  5A4h] [bp-20BA4h]@62
    char v26[256]; // [sp+  6A4h] [bp-20AA4h]@62
    char v27[256]; // [sp+  7A4h] [bp-209A4h]@62
    char v28[256]; // [sp+  8A4h] [bp-208A4h]@62
    char v29[0xF700]; // [sp+  9A4h] [bp-207A4h]@62
    // strange allocation
    char s[0x10000]; //  [sp+100A4h] [bp-110A4h]@17
    // strange allocation
    int v31; //       [sp+200A4h] [bp-10A4h]@13
    int v32; //       [sp+200A8h] [bp-10A0h]@11
    char *nptr; //    [sp+210D0h] [bp-78h]@4
    char src[256]; //      [sp+210D4h] [bp-74h]@4

    char v18_0;
    char v18_1;
    char *v18_2;

    if(a2 < 0 || a2 >= gserver.Unk452192)
        return false;

    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Loading zone ");

    sprintf(src, "Zone_%d", a2);
    nptr = gserver.Unk36904.Find(src, "No");

    if(!nptr)
        return false;

    this->Unk0 = atoi(nptr);

    g_gamelogbuffer.__ls(this->Unk0);
    g_gamelogbuffer.__ls(end);

    CDBCmd v33;

    v33.Init(&gserver.Unk41816);
    strcpy(g_buf, "SELECT * FROM t_zonedata WHERE a_zone_index=");
    IntCat(g_buf, this->Unk0, 0);
    v33.SetQuery(g_buf);

    if(!v33.Open() || !v33.MoveFirst())
        return false;

    nptr = gserver.Unk36904.Find(src, "Remote");
    if(nptr && strcmp(nptr, "FALSE"))
    {
        this->Unk4 = 1;
        nptr =gserver.Unk36904.Find(src, "Remote_IP");

        if(!nptr)
            return false;

        strcpy(this->Unk5, nptr);
        nptr = gserver.Unk36904.Find(src, "Remote_Port");

        if(!nptr)
            return false;

        this->Unk26 = atoi(nptr);
    }
    else
    {
        this->Unk4 = 0;

        if(!v33.GetRec("a_width", v32))
            return false;

        if(!v33.GetRec("a_height", v31))
            return false;

        if(!v33.GetRec("a_ylayer", this->Unk28))
            return false;

        if(!v33.GetRec("a_attrmap", s, 1))
            return false;

        if(!v33.GetRec("a_heightmap", v20, 1))
            return false;

        v19 = s;
        v18_2 = v20;

        this->Unk32 = new CMapAttr[this->Unk28]; // CHECK THIS!!!

        for(int j = 0; j < this->Unk28; ++j)
        {
            v19 = AnyOneArg(v19, g_buf, 0);
            v18_2 = AnyOneArg(v18_2, g_buf2, 0);

            if(!this->Unk32[j].Load(a2, j, v32, v31, g_buf, g_buf2))
                return false;
        }

        if(!v33.GetRec("a_areacount", this->Unk40))
            return false;

        if(this->Unk40 <= 0)
            return false;

        this->Unk36 = new CArea[this->Unk40]; // CHECK THIS!!!

        for(int j = 0; j < this->Unk40; ++j)
            this->Unk36[j].Init(this, j, v32, v31, this->Unk28);
    }

    if(!v33.GetRec("a_canusemempos", v18_1))
        return false;

    this->Unk45 = v18_1 ? 1 : 0;

    if(!v33.GetRec("a_poscount", v18_0)) // check char or int
        return false;

    if(!v33.GetRec("a_posylayer", v20, true))
        return false;

    if(!v33.GetRec("a_posleft",   v21, true))
        return false;

    if(!v33.GetRec("a_postop",    v22, true))
        return false;

    if(!v33.GetRec("a_posright",  v23, true))
        return false;

    if(!v33.GetRec("a_posbottom", v24, true))
        return false;

    v18_2 = v20;
    v19 = v21;
    char *v31_c, *v32_c; // FUCKING OPTIMIZATION
    v31_c = v22; // v31_c = v31 --> (int) == (char *)
    v32_c = v23; // v32_c = v32 --> (int) == (char *)
    v17 = v24;
    this->Unk48 = v18_0;
    this->Unk52 = (SUnkStruct **)malloc(sizeof(SUnkStruct *) * this->Unk48);

    for(int j = 0; j < this->Unk48; ++j)
    {
        // *(_DWORD *)(this->Unk52 + 4 * j) = (char *)malloc(20); // struct?
        this->Unk52[j] = new SUnkStruct();

        v18_2   = AnyOneArg(v18_2,  v25, false);
        v19     = AnyOneArg(v19,    v26, false);
        v31_c   = AnyOneArg(v31_c,  v27, false); // v31_c = v31 --> (int) == (char *)
        v32_c   = AnyOneArg(v32_c,  v28, false); // v32_c = v32 --> (int) == (char *)
        v17     = AnyOneArg(v17,    v29, false);

        this->Unk52[j]->Unk0  = atoi(v25);
        this->Unk52[j]->Unk4  = atof(v26) + atof(v26); // STRANGE ---> CHECK
        this->Unk52[j]->Unk8  = atof(v27) + atof(v27);
        this->Unk52[j]->Unk12 = atof(v28) + atof(v28);
        this->Unk52[j]->Unk16 = atof(v29) + atof(v29);
    }

    return true;
}

bool CZone::LoadNPC(void)
{
    if(this->Unk4)
        return true;

    for(int i = 0; i < this->Unk40; ++i)
        this->Unk36[i].LoadNPC();

    if(this->Unk40 == 1)
        this->Unk36[0].SetEnable();

    return true;
}

bool CZone::LoadShop(void)
{
    int v12; // [sp+50h] [bp-2858h]@15
    char dest[47]; // [sp+54h] [bp-2854h]@15
    char s; // [sp+83h] [bp-2825h]@15
    int v19; // [sp+1874h] [bp-1034h]@13

    if(this->Unk4)
        return true;

    delete [] this->Unk56; // CHECK THIS!!!

    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Shop Loading Zone ");
    g_gamelogbuffer.__ls(this->Unk0);
    g_gamelogbuffer.__ls(end);

    CDBCmd v20;
    v20.Init(&gserver.Unk41816);
    strcpy(g_buf, "SELECT * FROM t_shop WHERE a_zone_num = ");
    IntCat(g_buf, this->Unk0, 1);
    StrCat(g_buf, "ORDER BY a_keeper_idx");
    v20.SetQuery(g_buf);
    v20.Open();

    this->Unk60 = v20.AffectedRows;
    if(this->Unk60 <= 0)
        return true;

    this->Unk56 = new CShop[this->Unk60]; // CHECK THIS!!!

    v19 = 0;

    CDBCmd v17;
    v17.Init(&gserver.Unk41816);

    while(v20.MoveNext())
    {
        v20.GetRec("a_keeper_idx", this->Unk56[v19].Unk0);
        v20.GetRec("a_sell_rate", this->Unk56[v19].Unk24);
        v20.GetRec("a_buy_rate", this->Unk56[v19].Unk28);
        v20.GetRec("a_pos_x", this->Unk56[v19].Unk4);
        v20.GetRec("a_pos_z", this->Unk56[v19].Unk8);
        v20.GetRec("a_pos_r", this->Unk56[v19].Unk12);
        v20.GetRec("a_pos_h", this->Unk56[v19].Unk16);
        v20.GetRec("a_y_layer", this->Unk56[v19].Unk20);

        memcpy(&dest, "SELECT * FROM t_shopitem where a_keeper_idx = ", 47);
        memset(&s, 0, 2001);
        IntCat(&dest, this->Unk56[v19].Unk0, 0);
        StrCat(&dest, "ORDER BY a_item_idx");
        v17.SetQuery(&dest);
        v17.Open();
        this->Unk56[v19].Unk36 = v17.AffectedRows;
        this->Unk56[v19].Unk32 = (int *)malloc(sizeof(int *) * this->Unk56[v19].Unk36);
        v12 = 0;

        while(v17.MoveNext())
            this->Unk56[v19].Unk32[v12++] = atoi(v17.GetRec("a_item_idx"));

        ++v19;
    }

    return true;
}

int CZone::SetEnableArea(void)
{
    int i;

    for (i = 0; i < this->Unk40 && this->Unk36[i].Unk0; ++i);
    if(i != this->Unk40)
    {
        this->Unk36[i].SetEnable();
        return i;
    }

    return -1;
}

void CZone::SetDisableArea(int a2)
{
    if(a2 >= 0)
    {
        if(a2 < this->Unk40)
            this->Unk36[a2].SetDisable();
    }
}

CShop *CZone::FindShop(int a2)
{
    CShop key = *(CShop *)a2;

    return *(CShop **)bsearch(&key, this->Unk56, this->Unk60, sizeof(CShop), CZone::CompIndex);
}

void CZone::ChangeWeather(void)
{
    char v3; // [sp+23h] [bp-5h]@1

    v3 = this->Unk44;
    switch(this->Unk44)
    {
    case 0:
        if(!GetRandom(0, 5))
            this->Unk44 = 1;
        break;
    case 1:
        this->Unk44 = (GetRandom(0, 2) == 1) ? 2 : 0;
        break;
    case 2:
        this->Unk44 = GetRandom(0, 1) ? 3 : 1;
        break;
    case 3:
        this->Unk44 = GetRandom(0, 1) ? 4 : 2;
        break;
    case 4:
        if(!GetRandom(0, 1))
            this->Unk44 = 3;
        break;
    default:
        this->Unk44 = 2;
        break;
    }

    if(v3 != this->Unk44)
    {
        for(int i = 0; i < this->Unk40; ++i)
        {
            CNetMsg v2;

            EnvWeatherMsg(v2, this->Unk0);
            this->Unk36[i].SendToAllClient(v2);
        }
    }
}

void CZone::ChangeTaxRate(int a2, int a3)
{
    this->Unk64 = a2;
    this->Unk68 = a3;

    for(long i = 0; i < this->Unk60; ++i)
    {
        this->Unk56[i].Unk24 = this->Unk64;
        this->Unk56[i].Unk28 = this->Unk68;
    }
}

int CZone::FindEmptyArea(void)
{
    for(long i = 0; i < this->Unk40; ++i)
    {
        if(!this->Unk36[i].Unk0)
            return i;
    }

    return -1;
}

int CZone::CompIndex(void const *m_index1, void const *m_index2)
{
    return ((CZone *)m_index1)->Unk0 - ((CZone *)m_index2)->Unk0;
}
