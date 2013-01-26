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

#include "PC.h"
#include "Server.h"

/*************************
  TODO: void CPC::GoMemPos(int a2)
  ***********************/

short levelup_stat[6][4] = {{3, 1, 1, 3}, {2, 2, 2, 2}, {1, 3, 2, 2}, {1, 3, 3, 1}, {2, 3, 1, 2}, {1, 2, 3, 2}};
short levelup_hp_0[6][8] = {{4, 0, 0, 0, 0, 0, 8, 0}, {3, 0, 0, 0, 0, 0, 11, 0}, {4, 0, 0, 0, 0, 0, 7, 0}, {3, 0, 0, 0, 0, 0, 8, 0}, {4, 0, 0, 0, 0, 0, 9, 0}, {4, 0, 0, 0, 0, 0, 8, 0}};
short levelup_mp_0[6][8] = {{0, 0, 0, 0, 8, 0, 2, 0}, {0, 0, 0, 0, 6, 0, 2, 0}, {0, 0, 0, 0, 9, 0, 2, 0}, {0, 0, 0, 0, 10, 0, 1, 0}, {0, 0, 0, 0, 7, 0, 2, 0}, {0, 0, 0, 0, 9, 0, 3, 0}};
short base_stat[6][4]    = {{0x0032, 0x0014, 0x0014, 0x0032}, {0x0026, 0x001C, 0x001C, 0x0026}, {0x0014, 0x0032, 0x0026, 0x001C}, {0x0014, 0x0032, 0x0032, 0x0014}, {0x0026, 0x0032, 0x0014, 0x001C}, {0x0014, 0x0026, 0x0032, 0x001C}};
short base_hp[6]         = {0x00B4, 0x0096, 0x006E, 0x005A, 0x0082, 0x006E};
short base_mp[6]         = {0x0044, 0x0056, 0x006C, 0x007A, 0x0038, 0x0080};
float run_speed[6]       = {0x40C66666, 0x40C00000, 0x40E00000, 0x40C00000, 0x40E00000, 0x40B00000};
float walk_speed[6]      = {0x3FC00000, 0x3FC00000, 0x3FC00000, 0x3FC00000, 0x3FC00000, 0x3FC00000};

int armors_621[] = {0, 1, 3, 4, 5, 6};
int armors_640[] = {0, 1, 3, 4, 5, 6};

CPC::CPC(void)
{
    this->Unk0    = 0;
    this->Unk468  = -1;
    this->Unk472  = 0;
    this->Unk473  = 0;
    this->Unk474  = 0;
    this->Unk475  = 0;
    this->Unk476  = 0;
    this->Unk477  = -1;
    this->Unk478  = 0;
    this->Unk479  = 0;
    memset(this->Unk516, 0, 100);
    memset(this->Unk616, 0, 100);
    this->Unk724  = 0;
    this->Unk728  = 0;
    this->Unk732  = 0;
    this->Unk736  = 0;
    this->Unk740  = 0;
    this->Unk742  = 0;
    this->Unk744  = 0;
    this->Unk746  = 0;
    this->Unk748  = 0;
    this->Unk464  = 0;
    this->Unk1852 = 0;
    this->Unk1856 = 0;
    this->Unk1860 = 0;
    this->Unk1864 = 0;
    this->Unk1868 = 0;
    this->Unk1872 = 0;
    this->Unk1876 = 0;
    this->Unk756  = 0;
    this->Unk758  = 0;
    this->Unk760  = 0;
    this->Unk762  = 0;
    this->Unk764  = 0;
    this->Unk766  = 0;
    this->Unk768  = 0;
    this->Unk772  = 6000;
    this->Unk780  = 0;
    this->Unk776  = 0;
    this->Unk784  = gserver.Unk41248;
    this->Unk788  = 0;
    this->Unk792.Init(this, 0);
    this->Unk880.Init(this, 1);
    this->Unk968.Init(this, 2);
    this->Unk1256 = 0;
    this->Unk1280 = 0;
    memset(this->Unk1284, 0, 400);
    this->Unk1324 = 0;
    this->Unk1328 = 0;
    this->Unk1368 = 0;
    this->Unk2380 = 0;
    this->Unk1884 = 0;
    this->Unk1892 = 0;
    this->Unk1888 = 0;
    this->Unk1896 = 0;
    this->Unk1356 = 0;
    this->Unk1360 = -1;
    this->Unk1364 = -1;
    this->Unk2368 = 0;
    this->Unk2372 = 0;
    this->Unk2376 = 0;
    this->Unk1880 = 0;
    this->Unk2384 = 0;
    this->Unk2388 = -1;
}

CPC::~CPC()
{
    ;
}

void CPC::SendStatus(void)
{
    CNetMsg v4;

    StatusMsg(v4, this);

    if(this->Unk768)
        this->Unk768->WriteToOutput(v4);

    this->Unk473 = 0;

    if(this->IsParty())
    {
        PartyInfoMsg(v4, this);

        for(int i = 0; i <= 7; ++i)
        {
            if(this->Unk1368->GetMember(i) && this->Unk1368->GetMember(i) != this)
            {
                if(this->Unk1368->GetMember(i)->Unk768)
                    this->Unk1368->GetMember(i)->Unk768->WriteToOutput(v4);
            }
        }
    }
}

void CPC::SendInventory(char a2)
{
    int v3[3] = {0, 1, 2}; // [sp+18h] [bp-2Ch]@1
    CNetMsg v8;
    char v9 = a2; // [sp+43h] [bp-1h]@1

    for(int i = 0; i <= 2; ++i)
    {
        for(int j = 0; j <= 19; ++j)
        {
            if(InventoryMsg(v8, this, v9, v3[i], j))
            {
                if(this->Unk768)
                    this->Unk768->WriteToOutput(v8);
            }
        }
    }
}

void CPC::SendQuickSlot(void)
{
    CNetMsg v3;

    for(int i = 0; i <= 2; ++i)
    {
        QuickSlotListMsg(v3, this, i);
        if(this->Unk768)
            this->Unk768->WriteToOutput(v3);
    }
}

void CPC::Send(CNetMsg &a2)
{
    if(this->Unk472 && this->Unk768 && a2.MsgLength)
    {
        if(this->Unk768)
            this->Unk768->WriteToOutput(a2);

        gserver.SendOutput(this);
    }
}

bool CPC::AddMoney(long long a2)
{
    int v4; // [sp+1Ch] [bp-Ch]@19
    int v5; // [sp+20h] [bp-8h]@19
    CItem *v6; // [sp+24h] [bp-4h]@11

    if(!a2)
        return true;

    if(a2 < 0)
    {
        if(!this->Unk1280)
            return false;

        this->Unk792.Decrease(this->Unk1280, -a2);
        if(this->Unk1280->Count() <= 0)
        {
            this->Unk792.Remove(this->Unk1280, 1, 1);
            this->Unk1280 = 0;
        }
        return true;
    }

    v6 = gserver.Unk41208.CreateItem(gserver.Unk41208.Unk12->Unk0, -1, 0, 0, a2); // *unk_8104584

    if(!v6)
        return false;

    if(this->Unk792.AddItem(v6, this, 0, 1, -1, -1))
    {
        if(v6->tab() >= 0)
        {
            this->Unk1280 = v6;
        }
        else
        {
            if(!this->Unk1280 && this->Unk792.FindItem(&v5, &v4, gserver.Unk41208.Unk12->Unk0, 0, 0)) // *unk_8104584
                this->Unk1280 = this->Unk792.GetItem(v5, v4);

            if(v6)
                delete v6;
        }
        return true;
    }

    if(v6)
        delete v6;

    return false;
}

void CPC::AddExpSP(long long src, int a3)
{
    CNetMsg v14; // [sp+50h] [bp-14h]@1

    if(src < 0 || a3 < 0)
    {
        src = 0;
        a3 = 0;
    }

    if(this->Unk148.Unk40[23]) // 281 = 148 + 40 + 23 * 4 + 1 <---------------------------------------------- CHECK
        src = 12 * src / 10;

    if(this->Unk148.Unk40[23]) // 282 = 148 + 40 + 23 * 4 + 2 <---------------------------------------------- CHECK
        a3 = 13 * a3 / 10;

    this->Unk64 += src;
    this->Unk72 += a3;

    CNetMsg v13; // [sp+3Ch] [bp-28h]@8
    ExpSPMsg(v13, src, a3);

    if(this->Unk768)
        this->Unk768->WriteToOutput(v13);

    if(this->Unk72 > 2000000000)
        this->Unk72 = 2000000000;

    if(GetLevelupExp(this->Unk60) <= this->Unk64 && this->Unk60 <= 80)
    {
        do
        {
            g_gamelogbuffer.__ls(init("LEVEL UP", this->Unk8, this->Unk768->Unk4));
            g_gamelogbuffer.__ls(this->Unk60);
            g_gamelogbuffer.__ls(" ==> ");
            g_gamelogbuffer.__ls(this->Unk60 + 1);
            g_gamelogbuffer.__ls(end);

            this->Unk64 -= GetLevelupExp(this->Unk60);
            ++this->Unk60;
            ++this->Unk740;

            StatPointRemainMsg(v14, this);

            if(this->Unk768)
                this->Unk768->WriteToOutput(v14);

            this->LevelUp(1);
        }
        while(GetLevelupExp(this->Unk60) <= this->Unk64);

        this->CalcStatus(1);
        this->Restore();
    }
}

void CPC::Restore(void)
{
    this->Unk76 = this->Unk78;
    this->Unk80 = this->Unk82;
    this->Unk473 = 1; // ALIVE?
}

void CPC::InitStat(void)
{
    short v5; // ST1E_2@3
    short v6; // ST1C_2@3
    short v7; // ST1A_2@3
    short v8; // ST18_2@3

    if(this->Unk477 <= 5)
    {
        if(this->Unk477 >= 0)
        {
            v5 = (this->Unk60 - 1) * levelup_stat[this->Unk477][0] + this->Unk742;
            v6 = (this->Unk60 - 1) * levelup_stat[this->Unk477][1] + this->Unk744;
            v7 = (this->Unk60 - 1) * levelup_stat[this->Unk477][2] + this->Unk746;
            v8 = (this->Unk60 - 1) * levelup_stat[this->Unk477][3] + this->Unk748;
            this->Unk756 = v5 + base_stat[this->Unk477][0];
            this->Unk84 = v5 + base_stat[this->Unk477][0];
            this->Unk758 = v6 + base_stat[this->Unk477][1];
            this->Unk86 = v6 + base_stat[this->Unk477][1];
            this->Unk760 = v7 + base_stat[this->Unk477][2];
            this->Unk88 = v7 + base_stat[this->Unk477][2];
            this->Unk762 = v8 + base_stat[this->Unk477][3];
            this->Unk90 = v8 + base_stat[this->Unk477][3];
            this->Unk764 = levelup_hp_0[this->Unk477][6] * v8 + levelup_hp_0[this->Unk477][4] * v7 + levelup_hp_0[this->Unk477][1] * v6 + levelup_hp_0[this->Unk477][0] * v5 + base_hp[this->Unk477];
            this->Unk78 = levelup_hp_0[this->Unk477][6] * v8 + levelup_hp_0[this->Unk477][4] * v7 + levelup_hp_0[this->Unk477][1] * v6 + levelup_hp_0[this->Unk477][0] * v5 + base_hp[this->Unk477];
            this->Unk766 = levelup_mp_0[this->Unk477][6] * v8 + levelup_mp_0[this->Unk477][4] * v7 + levelup_mp_0[this->Unk477][2] * v6 + levelup_mp_0[this->Unk477][0] * v5 + base_mp[this->Unk477];
            this->Unk82 = levelup_mp_0[this->Unk477][6] * v8 + levelup_mp_0[this->Unk477][4] * v7 + levelup_mp_0[this->Unk477][2] * v6 + levelup_mp_0[this->Unk477][0] * v5 + base_mp[this->Unk477];
            this->Unk104 = walk_speed[this->Unk477];
            this->Unk108 = run_speed[this->Unk477];
        }
    }
}

void CPC::LevelUp(bool a2)
{
    CInventory *v3; // eax@41
    CItem *v23; // [sp+4Ch] [bp-48h]@58
    int v24; // [sp+50h] [bp-44h]@57
    int v25; // [sp+54h] [bp-40h]@57
    char v26; // [sp+5Bh] [bp-39h]@55
    int src; // [sp+78h] [bp-1Ch]@3

    CNetMsg v32;

    this->InitStat();
    this->CalcStatus(1);

    if(a2)
    {
        EffectEtcMsg(v32, this, 0);
        this->Unk412->SendToCell(v32, this, 1, 4);
    }

    src = 0;
    for(int i = 0; i < gserver.Unk452228.Unk4; ++i)
    {
        if(gserver.Unk452228.Unk0[i].Unk12 == 2 && gserver.Unk452228.Unk0[i].Unk16 == this->Unk60 && gserver.Unk452228.Unk0[i].Unk24 <= this->Unk60 && gserver.Unk452228.Unk0[i].Unk28 >= this->Unk60 && (gserver.Unk452228.Unk0[i].Unk32 == -1 || gserver.Unk452228.Unk0[i].Unk32 == this->Unk477))
        {
            if(gserver.Unk452228.Unk0[i].Unk0 != 42)
            {
                if(gserver.Unk452228.Unk0[i].Unk0 != 45)
                    ++src;
            }
        }
    }

    if(src > 0)
    {
        int *v29 = (int *)malloc(sizeof(int *) * src);
        int v28 = 0;

        for(int i = 0; i < gserver.Unk452228.Unk4; ++i)
        {
            if(gserver.Unk452228.Unk0[i].Unk12 == 2 && gserver.Unk452228.Unk0[i].Unk16 == this->Unk60 && gserver.Unk452228.Unk0[i].Unk24 <= this->Unk60 && gserver.Unk452228.Unk0[i].Unk28 >= this->Unk60 && (gserver.Unk452228.Unk0[i].Unk32 == -1 || gserver.Unk452228.Unk0[i].Unk32 == this->Unk477))
                v29[v28++] = gserver.Unk452228.Unk0[i].Unk0;
        }

        CNetMsg v27;

        QuestCreateListMsg(v27, src, v29);
        if(this->Unk768)
            this->Unk768->WriteToOutput(v27);
    }

    if(this->Unk60 > 12 && this->Unk60 <= 27)
    {
        CItem *v28 = gserver.Unk41208.CreateItem(gserver.Unk41208.Unk32->Unk0, -1, 0, 0, 1); // *unk_8104598

        if(!v28)
            return;

        CNetMsg v27;

        if((v28->Unk20->Unk4 != 4 || v28->Unk20->Unk8) && v28->Unk20->Unk8 != 1)
        {
            v3 = &this->Unk792;
        }
        else
        {
            if(v28->Unk20->Unk4 != 4 || v28->Unk20->Unk8)
            {
                if(v28->Unk20->Unk4 == 4 && v28->Unk20->Unk8 && v28->Unk20->Unk8 == 1)
                    v3 = &this->Unk968;
                else
                    v3 = 0;
            }
            else
            {
                v3 = &this->Unk880;
            }
        }

        CInventory *v29 = v3;

        if(!v3)
            return;

        v26 = 0;
        if(v29->AddItem(v28, this, 1, 1, -1, -1))
        {
            if(v28->tab() == -1)
            {
                v26 = 1;
                if(v29->FindItem(&v25, &v24, v28->Unk28, v28->Unk36, v28->Unk40))
                {
                    v23 = v29->GetItem(v25, v24);

                    if(v23)
                        ItemUpdateMsg(v27, v23, v28->Count());
                }
            }
            else
            {
                ItemAddMsg(v27, v28);
            }
        }
        else
        {
            v28 = this->Unk412->DropItem(v28, this);

            if(!v28)
                return;

            CNetMsg v22;

            ItemDropMsg(v22, this, v28);
            this->Unk412->SendToCell(v22, this, 1, 4);
            v28->Unk216 = this->Unk4;
        }

        if(this->Unk768)
            this->Unk768->WriteToOutput(v27);

        g_gamelogbuffer.__ls(init("ITEM_PICK", this->Unk8, this->Unk768->Unk4));
        g_gamelogbuffer.__ls(v28->Unk20->Unk12);
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls(v28->Unk44);
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls(v28->Unk36);
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls(v28->Unk40);
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls(v28->Count());
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls(0);
        g_gamelogbuffer.__ls(end);

        if(v26 && v28)
            delete v28; // (*(void (__cdecl **)(int, signed int))(*(_DWORD *)(v28 + 220) + 8))(v28, 3);
    }
}

void CPC::RemoveItemFromQuickSlot(CItem *a2)
{
    for(int i = 0; i <= 2; ++i)
    {
        for(int j = 0; j <= 9; ++j)
        {
            if(a2 == this->Unk1372[i].Unk120[j]) // *(_DWORD *)(160 * i + 4 * j + a1 + 1492)
            {
                this->Unk1372[i].Unk120[j] = 0;
                this->Unk1372[i].Unk0[j] = -1; // *(_DWORD *)(160 * i + 4 * j + a1 + 1372)

                CNetMsg v3;
                QuickSlotAddMsg(v3, this, i, j);

                if(this->Unk768)
                    this->Unk768->WriteToOutput(v3);
            }
        }
    }
}

void CPC::SetMaxWeight(void)
{
    this->Unk728 = 20 * (this->Unk84 + 300);
}

bool CPC::CheckWeight(long long a2, bool a3, bool a4)
{
    long long v6; // [sp+34h] [bp+Ch]@7

    if(!a4)
        a3 = 0;
    if(a2)
    {
        if(a2 < 0)
            a4 = 0;
        v6 = this->Unk724 + a2;
        if(v6 <= 15 * this->Unk728 / 10)
        {
            this->Unk724 = v6;
            this->CalcStatus(true);

            if((signed int)v6 - this->Unk728 > 0 && a3)
            {
                CNetMsg v5;

                SysMsg(v5, 36);
                if(this->Unk768)
                    this->Unk768->WriteToOutput(v5);
            }
            this->Unk473 = 1;
            return true;
        }

        if(a3)
        {
            CNetMsg v5;

            SysMsg(v5, 16);
            if(this->Unk768)
                this->Unk768->WriteToOutput(v5);
        }

        if(a4)
        {
            return false;
        }
        else
        {
            this->Unk724 = v6;
            this->CalcStatus(1);

            if((signed int)v6 - this->Unk728 > 0 && a3)
            {
                CNetMsg v5;

                SysMsg(v5, 36);
                if(this->Unk768)
                    this->Unk768->WriteToOutput(v5);
            }

            this->Unk473 = 1;
        }
    }

    return true;
}

void CPC::RecoverPC(void)
{
    int v2; // ST24_4@9
    int v3; // ST20_4@9
    signed int v5; // [sp+10h] [bp-8h]@3
    signed int v6; // [sp+14h] [bp-4h]@3

    if(this->Unk76 != this->Unk78 || this->Unk80 != this->Unk82)
    {
        v6 = this->Unk112;
        v5 = this->Unk114;

        if(this->IsSetPlayerState(2) || gserver.Unk41248 - this->Unk788 <= 29 || this->Unk424)
        {
            v6 = 1;
            v5 = 1;
        }
        else
        {
            if(!this->IsSetPlayerState(1))
            {
                v6 /= 4;
                v5 /= 4;
            }
        }

        v2 = this->Unk148.Unk40[20] + this->Unk616[10] * (this->Unk516[10] + v6) / 10000 + this->Unk516[10] + v6; // 228 - 148 = 40 + 80, 556 - 516 = 40, 656 - 616 = 40
        v3 = this->Unk148.Unk40[21] + this->Unk616[11] * (this->Unk516[11] + v5) / 10000 + this->Unk516[11] + v5; // 232 - 148 = 40 + 80 + 4, 560 - 516 = 40 + 4, 660 - 616 = 40 + 4

        this->Unk76 += this->Unk148.Unk140[20] * v2 / 10000 + v2; // 328 - 148 = 140 + 80
        this->Unk80 += this->Unk148.Unk140[21] * v3 / 10000 + v3; // 332 - 148 = 140 + 80 + 4

        if(this->Unk76 > this->Unk78)
            this->Unk76 = this->Unk78;

        if(this->Unk80 > this->Unk82)
            this->Unk80 = this->Unk82;

        this->Unk473 = 1;
    }
}

void CPC::GoMemPos(int a2)
{
    //if(this->Unk1332.Unk4[a2]) // a1 + Unk1336
    //    GoZone(this, this->Unk1332.Unk4[a2]->Unk0, this->Unk1332.Unk4[a2]->Unk12, this->Unk1332.Unk4[a2]->Unk4, this->Unk1332.Unk4[a2]->Unk8);
}

void CPC::CalcStatus(bool a2)
{
    this->Unk78 = this->Unk764;
    this->Unk82 = this->Unk766;
    this->Unk84 = this->Unk756;
    this->Unk86 = this->Unk758;
    this->Unk88 = this->Unk760;
    this->Unk90 = this->Unk762;
    this->Unk108 = run_speed[this->Unk477];
    this->Unk104 = walk_speed[this->Unk477];
    this->Unk102 = 20;
    this->Unk103 = 0;

    // CHECK THIS PART :/

    switch(this->Unk477)
    {
        case 0:
            this->Unk736 = 2.3;
            this->Unk112 = ((0x66666667 * (this->Unk60 + 120) >> 32) >> 2) - (this->Unk60 + 120) >> 31;
            this->Unk114 = (this->Unk60 + 120) / 10;
            break;
        case 1:
            this->Unk736 = 2.3;
            this->Unk112 = ((0x66666667 * (this->Unk60 + 120) >> 32) >> 2) - ((this->Unk60 + 120) >> 31);
            this->Unk114 = (this->Unk60 + 120) / 10;
            break;
        case 2:
            this->Unk736 = 20.0;
            this->Unk112 = ((0x66666667 * (this->Unk60 + 120) >> 32) >> 2) - ((this->Unk60 + 120) >> 31);
            this->Unk114 = (this->Unk60 + 180) / 10;
            break;
        case 3:
            this->Unk736 = 15.0;
            this->Unk112 = ((0x66666667 * (this->Unk60 + 80) >> 32) >> 2) - ((this->Unk60 + 80) >> 31);
            this->Unk114 = (this->Unk60 + 240) / 10;
            break;
        case 4:
            this->Unk736 = 2.3;
            this->Unk112 = ((0x66666667 * (this->Unk60 + 80) >> 32) >> 2) - ((this->Unk60 + 80) >> 31);
            this->Unk114 = (this->Unk60 + 120) / 10;
            break;
        case 5:
            this->Unk736 = 2.3;
            this->Unk112 = ((0x66666667 * (this->Unk60 + 80) >> 32) >> 2) - ((this->Unk60 + 80) >> 31);
            this->Unk114 = (this->Unk60 + 120) / 10;
            break;
        default:
            break;
    }

    this->Unk428 = 0;
    this->Unk430 = 0;
    this->Unk432 = 0;
    this->Unk434 = 0;
    this->Unk436 = 0;
    this->Unk438 = 0;
    this->Unk440 = 0;
    this->Unk442 = 0;
    this->Unk444 = 0;
    this->Unk446 = 0;
    this->Unk448 = 0;
    this->Unk450 = 0;
    this->Unk452 = 0;
    this->Unk454 = 0;
    this->Unk456 = 0;
    this->Unk458 = 0;

    this->ApplyItemValue(a2);
    this->ApplyPassiveSkill();
    this->SetMaxWeight();

    if(this->Unk724 > this->Unk728)
    {
        this->Unk86 -= (this->Unk724 - this->Unk728) / 30;
        if(this->Unk86 < 0)
            this->Unk86 = 0;
    }

    this->Unk148.Apply();
    if(!this->Unk1284[2]) // a1 + 1292
        this->Unk102 = 20;
    this->Unk473 = 1;
}

bool CPC::UseStatPoint(_tagStatPointUseType a2, short *a3)
{
    if(this->Unk740 <= 0)
        return false;

    if(a2 == 1)
    {
        ++this->Unk744;
        ++this->Unk758;
        *a3 = 1;
    }
    else
    {
        if(a2 > 1)
        {
            if(a2 == 2)
            {
                ++this->Unk746;
                ++this->Unk760;
                *a3 = 1;
            }
            else
            {
                if(a2 != 3)
                    return false;
                ++this->Unk748;
                ++this->Unk762;
                *a3 = 1;
            }
        }
        else
        {
            if(a2)
                return false;

            ++this->Unk742;
            ++this->Unk756;
            *a3 = 1;
        }
    }

    this->InitStat();
    --this->Unk740;
    this->CalcStatus(1);

    return true;
}

void CPC::ApplyItemValue(bool a2)
{
    CItem *v9; // [sp+24h] [bp-4h]@1
    CItem *v10; // [sp+24h] [bp-4h]@13
    CItem *v11; // [sp+24h] [bp-4h]@24

    v9 = this->Unk1284[2]; //v9 = *(_DWORD *)(a1 + 1292);

    this->Unk96 = 0;
    this->Unk94 = 0;
    this->Unk92 = 0;

    if(v9)
    {
        if(!(v9->Unk40 & 0x100))
        {
            if(v9->IsRangeWeapon())
                this->Unk94 = pow(1.059999942779541, v9->Unk36) * v9->Unk20->Unk76;
            else
                this->Unk92 = pow(1.059999942779541, v9->Unk36) * v9->Unk20->Unk76;

            this->Unk96 = pow(1.059999942779541, v9->Unk36) * v9->Unk20->Unk80;
            this->Unk102 = v9->Unk20->Unk84;

            for(int i = 0; i <= 4; ++i)
            {
                if(v9->Unk68[i].Unk8 > 0) // *(_DWORD *)(20 * i + v9 + 76) -> *(_DWORD *)(20 * i + v9 + 68 + 8)
                    v9->Unk68[i].ApplyOptionValue(this);
            }
        }
    }

    this->Unk98  = 0;
    this->Unk100 = 0;

    for(int j = 0; j <= 5; ++j)
    {
        v10 = this->Unk1284[armors_621[j]];

        if(v10)
        {
            if(v10->IsArmorType())
            {
                if(!(v10->Unk40 & 0x100))
                {
                    this->Unk98  += pow(1.059999942779541, v10->Unk36) * v10->Unk20->Unk76;
                    this->Unk100 += pow(1.059999942779541, v10->Unk36) * v10->Unk20->Unk80;

                    for(int k = 0; k <= 2; ++k)
                    {
                        if(v10->Unk68[k].Unk8 > 0) // *(_DWORD *)(20 * k + v10 + 76) -> *(_DWORD *)(20 * k + v10 + 68 + 8)
                            v10->Unk68[k].ApplyOptionValue(this);
                    }
                }
            }
        }
    }

    for(int l = 0; l <= 2; ++l)
    {
        v11 = this->Unk1284[l + 7];
        if(v11)
        {
            if(!(v11->Unk40 & 0x100))
            {
                for(int m = 0; m <= 4; ++m)
                {
                    if(v11->Unk20->Unk72 != -1)
                    {
                        if(v11->Unk68[m].Unk8 <= 0) // *(_DWORD *)(20 * m + v11 + 76) -> *(_DWORD *)(20 * m + v11 + 68 + 8)
                            continue;

                        if(v11->Unk64 <= 0)
                            continue;
                    }
                    v11->Unk68[m].ApplyOptionValue(this);
                }
            }
        }
    }

    if(a2)
        this->Unk473 = 1;
}

int CPC::SettingItemOption(void)
{
    int v3; // ST1C_4@24 OVERLAPPED
    CItem *v4; // ST14_8@24 OVERLAPPED
    unsigned int v7; // [sp+30h] [bp-28h]@20
    int v9; // [sp+38h] [bp-20h]@1
    int v10[7]; // [sp+3Ch] [bp-1Ch]@16

    v9 = 0;
    for(int i = 0; i <= 6; ++i)
    {
        if(!this->Unk1284[i])
            continue;

        if(this->Unk1284[i]->IsWeaponType())
        {
            if(this->Unk1284[i]->Unk168 > 4 || this->Unk1284[i]->Unk20->Unk8 == 8 || this->Unk1284[i]->Unk20->Unk8 == 9 || this->Unk1284[i]->Unk20->Unk8 == 10)
                continue;
        }
        else
        {
            if(this->Unk1284[i]->IsArmorType() && this->Unk1284[i]->Unk168 > 2)
                continue;
        }

        if(!(this->Unk1284[i]->Unk40 & 0x80) && (this->Unk1284[i]->IsWeaponType() || this->Unk1284[i]->IsArmorType()))
            v10[v9++] = i;
    }

    if(v9)
    {
        v7 = GetRandom(0, v9 - 1);
        if(this->Unk1284[v10[v7]])
        {
            this->Unk1284[v10[v7]]->Unk40 = this->Unk1284[v10[v7]]->Unk40 | 0x80; // LOBYTE(v2) = *(_DWORD *)(this->Unk1284[v10[v7]] + 40) | 0x80;
            CNetMsg v6;

            SysBloodItemMsg(v6, this->Unk1284[v10[v7]]->Unk28); // CHECK TYPE INT

            if(this->Unk768)
                this->Unk768->WriteToOutput(v6);

            v3 = 0;
            v4 = this->Unk1284[v10[v7]]; // *(_DWORD *)(4 * *(_DWORD *)&v10[4 * v7] + a1 + 1284)
            // int ItemUpdateMsg(CNetMsg &,CItem *,long long)
            ItemUpdateMsg(v6, this->Unk1284[v10[v7]], v4->Unk12); // *(long long *)(&v3 - 1)

            if(this->Unk768)
                this->Unk768->WriteToOutput(v6);

            return v7;
        }
    }

    return -1;
}

int CPC::CanWarp(void)
{
    if(this->Unk76 <= 0)
        return 23;

    if(this->Unk464 & 1)
        return 23;

    if(this->Unk464 & 4)
        return 24;

    if(this->Unk424)
        return 23;

    if(this->Unk1324)
        return 23;

    if(this->Unk1368 && this->Unk1368->GetMember(0) == this && this->Unk1368->GetRequest())
        return 23;

    return 0;
}

CSkill *CPC::FindSkill(int a2)
{
    CSkill *v3; // [sp+1Ch] [bp-4h]@1

    v3 = this->Unk480.Find(a2);
    if(v3)
        return v3;

    v3 = this->Unk492.Find(a2);
    if(v3)
        return v3;

    v3 = this->Unk504.Find(a2);
    if(v3)
        return v3;

    return 0;
}

void CPC::ApplyPassiveSkill(void)
{
    CSkillListNode *v19; // [sp+10h] [bp-1Ch]@1
    CMagicLevelProto *v21; // [sp+18h] [bp-14h]@10
    CMagicProto *v22; // [sp+1Ch] [bp-10h]@9
    CSkillLevelProto *v23; // [sp+20h] [bp-Ch]@5
    CSkillProto *v24; // [sp+24h] [bp-8h]@4
    CSkill *v25; // [sp+28h] [bp-4h]@3

    memset(this->Unk516, 0, 100);
    memset(this->Unk616, 0, 100);
    v19 = this->Unk492.GetHeadPosition();
    while(v19)
    {
        v25 = this->Unk492.GetNext((void *&)v19);
        if(v25)
        {
            v24 = (CSkillProto *)v25->Unk0;
            if(v24)
            {
                v23 = v24->Level(v25->Unk4);
                if(v23)
                {
                    if(this->CanApplySkill(v24, v23))
                    {
                        for(int i = 0; i <= 2; ++i)
                        {
                            v22 = v23->Unk88[i];
                            if(v22)
                            {
                                v21 = v22->Level(v23->Unk100[i]);
                                if(v21)
                                {
                                    if(!v22->Unk5)
                                    {
                                        switch(v22->Unk6)
                                        {
                                            case 0:
                                            if(v22->Unk7 == 1)
                                                this->Unk516[0] += v21->Unk0;
                                            else if(v22->Unk7 == 2)
                                                this->Unk616[0] += v21->Unk0;
                                            break;
                                            case 1:
                                            if(v22->Unk7 == 1)
                                                this->Unk516[1] += v21->Unk0;
                                            else if(v22->Unk7 == 2)
                                                this->Unk616[1] += v21->Unk0;
                                            break;
                                            case 2:
                                            if(v22->Unk7 == 1)
                                                this->Unk516[2] += v21->Unk0;
                                            else if(v22->Unk7 == 2)
                                                this->Unk616[2] += v21->Unk0;
                                            break;
                                            case 3:
                                            if(v22->Unk7 == 1)
                                                this->Unk516[3] += v21->Unk0;
                                            else if(v22->Unk7 == 2)
                                                this->Unk616[3] += v21->Unk0;
                                            break;
                                            case 4:
                                            if(v22->Unk7 == 1)
                                                this->Unk516[4] += v21->Unk0;
                                            else if(v22->Unk7 == 2)
                                                this->Unk616[4] += v21->Unk0;
                                            break;
                                            case 5:
                                            if(v22->Unk7 == 1)
                                                this->Unk516[5] += v21->Unk0;
                                            else if(v22->Unk7 == 2)
                                                this->Unk616[5] += v21->Unk0;
                                            break;
                                            case 6:
                                            if(v22->Unk7 == 1)
                                                this->Unk516[6] += v21->Unk0;
                                            else if(v22->Unk7 == 2)
                                                this->Unk616[6] += v21->Unk0;
                                            break;
                                            case 7:
                                            if(v22->Unk7 == 1)
                                                this->Unk516[7] += v21->Unk0;
                                            else if(v22->Unk7 == 2)
                                                this->Unk616[7] += v21->Unk0;
                                            break;
                                            case 8:
                                            if(v22->Unk7 == 1)
                                                this->Unk516[8] += v21->Unk0;
                                            else if(v22->Unk7 == 2)
                                                this->Unk616[8] += v21->Unk0;
                                            break;
                                            case 9:
                                            if(v22->Unk7 == 1)
                                                this->Unk516[9] += v21->Unk0;
                                            else if(v22->Unk7 == 2)
                                                this->Unk616[9] += v21->Unk0;
                                            break;
                                            case 10:
                                            if(v22->Unk7 == 1)
                                                this->Unk516[10] += v21->Unk0;
                                            else if(v22->Unk7 == 2)
                                                this->Unk616[10] += v21->Unk0;
                                            break;
                                            case 11:
                                            if(v22->Unk7 == 1)
                                                this->Unk516[11] += v21->Unk0;
                                            else if(v22->Unk7 == 2)
                                                this->Unk616[11] += v21->Unk0;
                                            break;
                                            case 12:
                                            if(v22->Unk7 == 1)
                                                this->Unk516[12] += v21->Unk0;
                                            else if(v22->Unk7 == 2)
                                                this->Unk616[12] += v21->Unk0;
                                            break;
                                            case 13:
                                            if(v22->Unk7 == 1)
                                                this->Unk516[13] += v21->Unk0;
                                            else if(v22->Unk7 == 2)
                                                this->Unk616[13] += v21->Unk0;
                                            break;
                                            case 14:
                                            if(v22->Unk7 == 1)
                                                this->Unk516[14] += v21->Unk0;
                                            else if(v22->Unk7 == 2)
                                                this->Unk616[14] += v21->Unk0;
                                            break;
                                            case 15:
                                            if(v22->Unk7 == 1)
                                                this->Unk516[16] += v21->Unk0;
                                            else if(v22->Unk7 == 2)
                                                this->Unk616[20] += v21->Unk0;
                                            break;
                                            case 16:
                                            if(v22->Unk7 == 1)
                                                this->Unk516[21] += v21->Unk0;
                                            else if(v22->Unk7 == 2)
                                                this->Unk616[21] += v21->Unk0;
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

    this->ApplyAssistData(this->Unk516, this->Unk616);
}

int CPC::GetAttackLevel(void)
{
    return (this->Unk1284[2]) ? this->Unk1284[2]->Unk20->Unk100 : 0; // this->Unk1284[2] -> a1 + 1292
}

int CPC::GetDefenseLevel(void)
{
    bool v3 = false; // [sp+13h] [bp-5h]@1
    short v4 = 0; // [sp+14h] [bp-4h]@1

    for(int i = 0; i <= 5; ++i)
    {
        if(this->Unk1284[armors_640[i]])
        {
            if(v4 < this->Unk1284[armors_640[i]]->Unk20->Unk100)
                v4 = this->Unk1284[armors_640[i]]->Unk20->Unk100;

            v3 = true;
        }
    }

    return (!v3) ? 2 * this->Unk60 : v4;
}

char CPC::GetAttackType(CSkillProto const *a2)
{
    if(a2)
    {
        if(a2->Unk8 == 1)
            return 1;

        if(a2->Unk8 > 1)
        {
            if(a2->Unk8 == 2)
                return 2;
        }
        else
        {
            if(!a2->Unk8)
                return 0;
        }
    }

    if(!this->Unk1284[2]) // this->Unk1284[2] -> a1 + 1292
        return 0;

    if(this->Unk1284[2]->IsRangeWeapon()) // this->Unk1284[2] -> a1 + 1292
        return 1;

    if(this->Unk1284[2]->IsMagicWeapon()) // this->Unk1284[2] -> a1 + 1292
        return 2;

    return 0;
}

char CPC::GetPKName(void)
{
    if(this->Unk1856 >= -90)
        return -5;

    if(this->Unk1856 >= -70)
        return -4;

    if(this->Unk1856 >= -50)
        return -3;

    if(this->Unk1856 >= -30)
        return -2;

    if(this->Unk1856 >= -10)
        return -1;

    if(this->Unk1856 > 10)
        return 0;

    if(this->Unk1856 > 30)
        return 1;

    if(this->Unk1856 > 50)
        return 2;

    if(this->Unk1856 > 70)
        return 3;

    if(this->Unk1856 > 90)
        return 4;

    return 5;
}

bool CPC::CanMove(void)
{
    if(this->IsSetPlayerState(1) || this->IsSetPlayerState(4) || this->Unk1328)
        return 0;

    return ((CCharacter *)this)->CanMove(); // CCharacter::CanMove(a1)
}

bool CPC::CanAttack(void)
{
    if(this->IsSetPlayerState(1) || this->IsSetPlayerState(4) || this->IsSetPlayerState(2) || this->IsSetPlayerState(64))
        return 0;

    return ((CCharacter *)this)->CanAttack(); // CCharacter::CanAttack(a1)
}

bool CPC::CanSpell(void)
{
    if(this->IsSetPlayerState(1) || this->IsSetPlayerState(4) || this->IsSetPlayerState(2))
        return 0;

    return ((CCharacter *)this)->CanSpell(); // CCharacter::CanSpell(a1)
}

int CPC::CanChange(void)
{
    if(this->Unk76 <= 0)
        return 0;

    if(this->Unk464 & 1)
        return 1;

    if(this->Unk464 & 4)
        return 2;

    if(this->Unk424)
        return 3;

    if(this->Unk1324)
        return 4;

    if(this->Unk1368 && this->Unk1368->GetMember(0) == this && this->Unk1368->GetRequest())
        return 5;

    if(this->Unk464 & 8 || this->Unk464 & 0x20 || this->Unk464 & 0x10)
        return 6;

    if(gserver.Unk41248 - this->Unk788 <= 29)
        return 9;

    if(this->Unk1328)
        return 10;

    return -1;
}

bool CPC::IsSetPlayerState(int a2)
{
    return (this->Unk464 & a2) != 0;
}

void CPC::SetPlayerState(int a2)
{
    this->Unk464 |= a2;
}

void CPC::ResetPlayerState(int a2)
{
    this->Unk464 &= ~a2;
}

void CPC::TogglePlayerState(int a2)
{
    this->Unk464 ^= a2;
}

int CPC::GetPlayerState(void)
{
    return this->Unk464;
}

float CPC::GetSize(void)
{
    return 0.0;
}

bool CPC::IsParty(void)
{
    return (this->Unk1368 && this->Unk1368->GetRequest() != this) ? true : false;
}

void CPC::SaveNow(bool a2)
{
    this->Unk1256 = a2;
    this->Unk772  = 0;
}

CPCList::CPCList(void)
{
    for(int i = 0; i <= 8191; ++i)
        this->Unk0[i] = 0;

    this->Unk32768 = 0;
    this->Unk32772 = 0;
}

CPCList::~CPCList()
{
    this->Unk32772 = 0;
    this->Unk32768 = 0;
}

CPC *CPCList::Find(int a2)
{
    for(int i = 0; i < this->Unk32768; ++i)
    {
        if(this->Unk0[i] && this->Unk0[i]->Unk4 == a2)
            return this->Unk0[i];
    }

    return 0;
}

CPC *CPCList::Find(char const *a2)
{
    for(int i = 0; i < this->Unk32768; ++i)
    {
        if(this->Unk0[i] && !strcmp(this->Unk0[i]->Unk8, a2))
            return this->Unk0[i];
    }

    return 0;
}

int CPCList::Add(CPC *a2)
{
    signed int i; // [sp+14h] [bp-4h]@3

    if(this->Unk32768 <= 8191)
    {
        for(i = 0; i < this->Unk32768 && this->Unk0[i]; ++i);

        if(a2->Unk468 == i)
            return i;

        this->Unk0[i] = a2;
        a2->Unk468 = i;

        if(i == this->Unk32768)
            ++this->Unk32768;

        ++this->Unk32772;

        return i;
    }

    return -1;
}

void CPCList::Remove(CPC *a2)
{
    signed int v4; // [sp+1Ch] [bp-4h]@2

    if(this->Playing(a2))
    {
        DelAttackList(a2);
        DelRaList(a2, true);

        v4 = a2->Unk468;

        if(v4 >= 0)
        {
            if(v4 <= 8191)
            {
                this->Unk0[v4] = 0;
                a2->Unk468 = -1;

                if(v4 == this->Unk32768)
                    --this->Unk32768;

                --this->Unk32772;
            }
        }
    }
}

bool CPCList::Playing(CPC *a2)
{
    if(a2)
    {
        if(*a2->Unk8)
        {
            if(a2->Unk468 >= 0 && a2->Unk468 <= 8191)
                return this->Unk0[a2->Unk468] == a2;
        }
    }

    return false;
}

void CPCList::SendToAll(CNetMsg &a2)
{
    for(int i = 0; i < this->Unk32768; ++i)
    {
        if(this->Unk0[i])
        {
            if(this->Unk0[i]->Unk768)
                this->Unk0[i]->Unk768->WriteToOutput(a2);
        }
    }
}
