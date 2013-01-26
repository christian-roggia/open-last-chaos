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

#include "Inventory.h"
#include "Server.h"

CInventoryRow::CInventoryRow(CInventory *a2)
{
    memset(this->Unk4, 0, 20);
    this->Unk0 = a2;
}

CInventoryRow::~CInventoryRow()
{
    for(int i = 0; i <= 4; ++i)
    {
        if(this->Unk4[i])
        {
            if(this->Unk4[i])
                delete this->Unk4[i];

            this->Unk4[i] = 0;
        }
    }
}

bool CInventoryRow::FindEmpty(int *a2)
{
    for(int i = 0; i <= 4; ++i)
    {
        if(!this->Unk4[i])
        {
            *a2 = i;
            return true;
        }
    }

    return false;
}

bool CInventoryRow::FindItem(int *a2, int a3, int a4, int a5)
{
    for(int i = 0; i <= 4; ++i)
    {
        if(this->Unk4[i] && this->Unk4[i]->Unk28 == a3 && (a4 == -1 || this->Unk4[i]->Unk36 == a4) && (a5 == -1 || this->Unk4[i]->Unk40 == a5))
        {
            *a2 = i;
            return true;
        }
    }

    return false;
}

bool CInventoryRow::FindItem(int *a2, int a3)
{
    for(int i = 0; i <= 4; ++i)
    {
        if(this->Unk4[i] && this->Unk4[i]->Unk24 == a3)
        {
            *a2 = i;
            return true;
        }
    }

    return false;
}

bool CInventoryRow::IsEmpty(void)
{
    for(int i = 0; i <= 4; ++i)
    {
        if(this->Unk4[i])
            return false;
    }

    return true;
}

bool CInventoryRow::Remove(int a2, bool a3, bool a4)
{
    if(a2 >= 0 && a2 <= 4)
    {
        if(this->Unk4[a2])
        {
            if(this->Unk0->Unk0->Unk1280 == this->Unk4[a2])
                this->Unk0->Unk0->Unk1280 = 0;

            if(a4)
            {
                this->Unk0->Unk0->RemoveItemFromQuickSlot(this->Unk4[a2]);
                if(this->Unk4[a2]->Unk32 != -1)
                {
                    CNetMsg v10;
                    ItemWearMsg(v10, this->Unk4[a2]->Unk32, 0, 0);
                    this->Unk0->Unk0->Unk1284[this->Unk4[a2]->Unk32] = 0;
                    this->Unk4[a2]->Unk32 = -1;
                }
            }

            this->Unk0->Unk0->CheckWeight(((unsigned long long)(-this->Unk4[a2]->Unk20->Unk96) * (unsigned int)(this->Unk4[a2]->Count())), 0, 1); // CHECK

            if(a3)
            {
                if(this->Unk4[a2])
                    delete this->Unk4[a2];
            }
            else
            {
                this->Unk4[a2]->Unk0 = -1;
                this->Unk4[a2]->Unk4 = -1;
                this->Unk4[a2]->Unk8 = -1;
            }
            this->Unk4[a2] = 0;
        }
    }

    return false;
}

int CInventoryRow::GetSpace(void)
{
    int v2 = 0;

    for(int i = 0; i <= 4; ++i)
    {
        if(!this->Unk4[i])
            ++v2;
    }

    return v2;
}

CInventory::CInventory(void)
{
    memset(this->Unk8, 0, 80);
}

CInventory::~CInventory()
{
    for(int i = 0; i <= 19; ++i)
    {
        if(this->Unk8[i])
        {
            if(this->Unk8[i])
                delete this->Unk8[i];

            this->Unk8[i] = 0;
        }
    }
}

bool CInventory::AddItem(CItem *a2, CPC *a3, bool a4, bool a5, int a6, int a7)
{
    CItem *v16; // [sp+3Ch] [bp-1Ch]@11
    int v17; // [sp+40h] [bp-18h]@10
    int v18; // [sp+44h] [bp-14h]@10

    if(a2)
    {
        if(this->GetItem(a2->Unk24))
            return true;

        if(this->GetItemBySerial(a2->Unk44))
        {
            a2->Unk0 = -1;
            a2->Unk4 = -1;
            a2->Unk8 = -1;

            return true;
        }
    }

    if(!a5)
        a4 = false;

    if(a2 && a2->Unk20->Unk68 & 1 && this->FindItem(&v18, &v17, a2->Unk28, a2->Unk36, a2->Unk40) && (v16 = this->GetItem(v18, v17)) != 0)
    {
        if(this->Unk0->CheckWeight(a2->Unk20->Unk96 * a2->Unk12, a4, a5)) // CHECK *(_DWORD *)(a2->Unk20 + 96) * a2->Unk12
        {
            v16->Unk12 += a2->Unk12;
            a2->Unk0 = -1;
            a2->Unk4 = -1;
            a2->Unk8 = -1;

            if(v16->Unk28 == gserver.Unk41208.Unk12->Unk0) // *unk_8104584
                this->Unk0->Unk1280 = v16;

            return true;
        }

        return false;
    }
    else
    {
        if(a6 >= 0 && a6 <= 19 && a7 >= 0 && a7 <= 4)
        {
            if(this->Unk8[a6] && this->Unk8[a6]->Unk4[a7])
                return false;
        }
        else
        {
            if(!this->FindEmpty(&a6, &a7))
                return false;
        }

        if(a2)
        {
            if(!this->Unk0->CheckWeight(a2->Unk12 * a2->Unk20->Unk96, a4, a5)) // CHECK a2->Unk12 * *(_DWORD *)(a2->Unk20 + 96)
                return false;

            a2->Unk0 = this->Unk4;
            a2->Unk4 = a6;
            a2->Unk8 = a7;
        }

        if(!this->Unk8[a6])
            this->Unk8[a6] = new CInventoryRow(this);

        this->Unk8[a6]->Unk4[a7] = a2;
        if(a2 && a2->Unk28 == gserver.Unk41208.Unk12->Unk0) // *unk_8104584
            this->Unk0->Unk1280 = a2;
    }

    return true;
}

bool CInventory::Decrease(CItem *a2, long long a3)
{
    if(a2 && a2->Unk0 == this->Unk4 && this->GetItem(a2->Unk4, a2->Unk8) == a2)
    {
        a2->Unk12 -= a3;
        this->Unk0->CheckWeight(a3 * - a2->Unk20->Unk96, 0, 1);

        return true;
    }

    return false;
}

bool CInventory::FindEmpty(int *a2, int *a3)
{
    int i;

    for(i = 0; this->Unk8[i]; ++i)
    {
        if(i > 19)
            return false;

        if(this->Unk8[i]->FindEmpty(a3))
        {
            *a2 = i;
            return true;
        }
    }

    this->Unk8[i] = new CInventoryRow(this);
    *a2 = i;
    *a3 = 0;

    return true;
}

CItem *CInventory::GetItem(int a2, int a3)
{
    if(a2 >= 0 && a2 <= 19 && a3 >= 0 && a3 <= 4)
    {
        if(this->Unk8[a2])
        {
            if(this->Unk8[a2]->Unk4[a3])
                return this->Unk8[a2]->Unk4[a3];
        }
    }

    return 0;
}

bool CInventory::FindItem(int *a2, int *a3, int a4, int a5, int a6)
{
    for(int i = 0; i <= 19; ++i)
    {
        if(this->Unk8[i] && this->Unk8[i]->FindItem(a3, a4, a5, a6))
        {
            *a2 = i;
            return true;
        }
    }

    return false;
}

bool CInventory::FindItem(int *a2, int *a3, int a4)
{
    for(int i = 0; i <= 19; ++i)
    {
        if(this->Unk8[i] && this->Unk8[i]->FindItem(a3, a4))
        {
            *a2 = i;
            return true;
        }
    }

    return false;
}

bool CInventory::Swap(int a2, int a3, int a4, int a5, int a6, int a7)
{
    CItem *v8; // [sp+14h] [bp-8h]@1
    CItem *v9; // [sp+18h] [bp-4h]@1

    v9 = this->GetItem(a2, a3);
    v8 = this->GetItem(a5, a6);

    if((a4 == -1 || (v9 && v9->Unk24 == a4)) && (a4 != -1 || !v9) && ((a7 == -1 || v8) && v8->Unk24 == a7) && (a7 != -1 || !v8))
    {
        if(v9 == v8)
            return true;

        this->Remove(a2, a3, 0, 0);
        this->Remove(a5, a6, 0, 0);
        this->AddItem(v9, this->Unk0, 0, 0, a5, a6);
        this->AddItem(v8, this->Unk0, 0, 0, a2, a3);

        return true;
    }

    return false;
}

void CInventory::Arrange(void)
{
    int v2; // [sp+1Ch] [bp-1A0h]@1
    int v4; // [sp+24h] [bp-198h]@1
    CItem *v6; // [sp+28h] [bp-194h]@5
    CItem *s[100]; // [sp+2Ch] [bp-190h]@1

    memset(s, 0, 400);
    v4 = 0;
    v2 = 0;

    while(v4 <= 19)
    {
        for(int i = 0; i <= 4; ++i)
        {
            v6 = this->GetItem(v4, i);
            if(v6)
                s[v2++] = v6;
            this->Remove(v4, i, 0, 0);
        }
        ++v4;
    }

    for(int j = 0; j < v2; ++j)
        this->AddItem(s[j], this->Unk0, 0, 0, -1, -1);
}

bool CInventory::Remove(int a2, int a3, bool a4, bool a5)
{
    if(a2 >= 0 && a2 <= 19 && this->Unk8[a2])
    {
        this->Unk8[a2]->Remove(a3, a4, a5); // CHECK
        if(this->Unk8[a2]->IsEmpty())
        {
            if(this->Unk8[a2])
                delete this->Unk8[a2];

            this->Unk8[a2] = 0;
        }
        return true;
    }

    return false;
}

bool CInventory::Remove(CItem *a2, bool a3, bool a4)
{
    long long v7; // [sp+34h] [bp-14h]@8
    CItem *v8; // [sp+3Ch] [bp-Ch]@8
    int v9; // [sp+40h] [bp-8h]@7
    int v10; // [sp+44h] [bp-4h]@7

    if(a2)
    {
        if(this->Unk4 != a2->Unk0 || this->GetItem(a2->Unk4, a2->Unk8) != a2)
        {
            if(a2->Unk20->Unk68 & 1 && this->FindItem(&v10, &v9, a2->Unk28, a2->Unk36, a2->Unk40))
            {
                v8 = this->GetItem(v10, v9);
                v7 = a2->Unk12;
                if(v7 <= v8->Unk12)
                {
                    this->Unk0->CheckWeight(((unsigned long long)(-a2->Unk20->Unk96) * a2->Unk12), 0, 1); // CHECK

                    if(a3 && a2)
                        delete a2; // CHECK

                    if(v8)
                    {
                        v8->Unk12 -= v7;
                        if(v8->Unk12 <= 0) // if(*(_DWORD *)(v8 + 16) <= 0)
                        {
                            if(v8->Unk12) //if(*(_DWORD *)(v8 + 16) || !*(_DWORD *)(v8 + 12))
                            {
                                v8->Unk12 = 0;
                                if(a3)
                                    this->Remove(v8->Unk4, v8->Unk8, a3, a4);
                            }
                        }
                    }

                    return true;
                }
            }

            return false;
        }

        return this->Remove(a2->Unk4, a2->Unk8, a3, a4);
    }

    return true;
}

int CInventory::GetSpace(void)
{
    int v3; // [sp+14h] [bp-4h]@1

    v3 = 0;
    for(int i = 0; i <= 19; ++i)
        v3 += (this->Unk8[i]) ? this->Unk8[i]->GetSpace() : 5;

    return v3;
}

CItem *CInventory::GetItemBySerial(char const *s2)
{
    for(int i = 0; i <= 19; ++i)
    {
        if(this->Unk8[i])
        {
            for(int j = 0; j <= 4; ++j)
            {
                if(this->Unk8[i]->Unk4[j] && !strcmp(this->Unk8[i]->Unk4[j]->Unk44, s2))
                    return this->Unk8[i]->Unk4[j];
            }
        }
    }

    return 0;
}

CItem *CInventory::GetItem(int a2)
{
    int v3, v4;
    return (this->FindItem(&v4, &v3, a2)) ? this->GetItem(v4, v3) : 0;
}

void CInventory::Init(CPC *a2, int a3)
{
    this->Unk0 = a2;
    this->Unk4 = a3;
}
