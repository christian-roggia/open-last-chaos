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

#include "ExchangeItems.h"
#include "Server.h"

CExchangeItemsData::CExchangeItemsData(void)
{
    this->Unk0 = 0;
    this->Unk4 = 0;
    memset(Unk8, -1, sizeof(CItem *)   * 10);
    memset(Unk48, 0, sizeof(long long) * 10);
}

void CExchangeItemsData::SetCharacter(CPC *a2)
{
    this->Unk0 = a2;
}

int CExchangeItemsData::Add(int a2, long long a3, bool *a4)
{
    signed int v5; // [sp+20h] [bp-8h]@7
    signed int v6; // [sp+20h] [bp-8h]@10
    CItem *v7; // [sp+24h] [bp-4h]@3

    if(a2 == -1)
        return -1;

    v7 = this->Unk0->Unk792.GetItem(a2);
    if(v7)
    {
        if(a3 >= 0)
        {
            v5 = this->Find(a2);
            if(v5 == -1)
            {
                if(a3 <= v7->Count())
                {
                    v6 = this->FindEmpty();
                    if(v6 >= 0)
                    {
                        ++this->Unk4;
                        this->Unk8[v6] = a2;
                        this->Unk48[v6] = a3;
                        *a4 = false;

                        return v6;
                    }
                }
            }
            else
            {
                if(a3 + this->Unk48[v5] <= v7->Count())
                {
                    this->Unk48[v5] += a3;
                    *a4 = true;

                    return v5;
                }
            }
        }
    }

    return -1;
}

int CExchangeItemsData::Del(int a2, long long a3)
{
    signed int v4; // [sp+24h] [bp-4h]@3

    if(a2 == -1)
        return -1;

    v4 = this->Find(a2);
    if(v4 == -1)
        return -1;

    if(a3 >= 0)
    {
        if(a3 <= this->Unk48[v4])
        {
            this->Unk48[v4] -= a3;
            if(!this->Unk48[v4])
            {
                this->Unk8[v4] = -1;
                --this->Unk4;
            }

            return v4;
        }
    }

    return -1;
}

int CExchangeItemsData::Find(int a2)
{
    if(a2 == -1)
        return -1;

    for(int i = 0; i <= 9; ++i)
    {
        if(this->Unk48[i] && this->Unk48[i] == a2)
            return i;
    }

    return -1;
}

int CExchangeItemsData::FindEmpty(void)
{
    for(int i = 0; i <= 9; ++i)
    {
        if(!this->Unk48[i])
            return i;
    }

    return -1;
}

CExchangeItems::CExchangeItems(void)
{
    this->Unk0 = 0;
}

void CExchangeItems::SetCharacter(CPC *a2, CPC *a3)
{
    this->Unk4.SetCharacter(a2);
    this->Unk132.SetCharacter(a3);
}

int CExchangeItems::Add(CPC *a2, int a3, long long a4, bool *a5)
{
    CExchangeItemsData *v6; // [sp+14h] [bp-4h]@6

    if(a3 == -1)
        return -1;

    if(!a2->Unk792.GetItem(a3))
        return -1;

    if(a2 == this->Unk4.Unk0)
    {
        v6 = &this->Unk4;
    }
    else
    {
        if(a2 != this->Unk132.Unk0)
            return -1;

        v6 = &this->Unk132;
    }

    return v6->Add(a3, a4, a5);
}

int CExchangeItems::Del(CPC *a2, int a3, long long a4)
{
    CExchangeItemsData *v5; // [sp+14h] [bp-4h]@6

    if(a3 == -1)
        return -1;

    if(!a2->Unk792.GetItem(a3))
        return -1;

    if(a2 == this->Unk4.Unk0)
    {
        v5 = &this->Unk4;
    }
    else
    {
        if(a2 != this->Unk132.Unk0)
            return -1;

        v5 = &this->Unk132;
    }

    return v5->Del(a3, a4);
}

int CExchangeItems::Find(CPC *a2, int a3)
{
    CExchangeItemsData *v4; // [sp+14h] [bp-4h]@2

    if(a2 == this->Unk4.Unk0)
    {
        v4 = &this->Unk4;
    }
    else
    {
        if(a2 != this->Unk132.Unk0)
            return -1;

        v4 = &this->Unk132;
    }

    return v4->Find(a3);
}

int CExchangeItems::CanExchange(void)
{
    int v6; // [sp+30h] [bp-28h]@10
    int v7; // [sp+34h] [bp-24h]@10
    CItem *v8; // [sp+38h] [bp-20h]@4
    int v10; // [sp+40h] [bp-18h]@1
    int v11; // [sp+44h] [bp-14h]@1
    int v12; // [sp+48h] [bp-10h]@1
    int v13; // [sp+4Ch] [bp-Ch]@1
    int v14; // [sp+50h] [bp-8h]@1
    int v15; // [sp+54h] [bp-4h]@1

    v15 = 0;
    v14 = 0;
    v13 = 0;
    v12 = 0;
    v11 = 0;
    v10 = 0;

    for(int i = 0; i <= 9; ++i)
    {
        if(this->Unk4.Unk8[i] != -1) // *(_DWORD *)(4 * i + a1 + 12) --> *(_DWORD *)(4 * i + a1 + 4 + 8)
        {
            v8 = this->Unk4.Unk0->Unk792.GetItem(this->Unk4.Unk8[i]);

            if(!v8)
                return 1;

            if(v8->Unk20->Unk68 & 1)
            {
                if(v8->Count() == this->Unk4.Unk48[i]) // *(_QWORD *)(8 * i + a1 + 52) --> *(_QWORD *)(8 * i + a1 + 4 + 48)
                    ++v15;

                if(this->Unk4.Unk48[i] > v8->Count())
                    return 1;

                if(!this->Unk132.Unk0->Unk792.FindItem(&v7, &v6, v8->Unk28, v8->Unk36, v8->Unk40))
                    ++v12;
            }
            else
            {
                ++v15;
                ++v12;
            }

            v11 += this->Unk4.Unk48[i] * v8->Unk20->Unk96; // *(_DWORD *)(8 * i + a1 + 52) <--- NOTE THIS IS AN ARRAY OF LONG LONG ELEMENTS, BUT IS IDENTIFIED AS DWORD
        }

        if(this->Unk132.Unk8[i] != -1)
        {
            v8 = this->Unk132.Unk0->Unk792.GetItem(this->Unk132.Unk8[i]);

            if(!v8)
                return 2;

            if(v8->Unk20->Unk68 & 1)
            {
                if(v8->Count() == this->Unk132.Unk48[i])
                    ++v13;

                if(this->Unk132.Unk48[i] > v8->Count())
                    return 2;

                if(!this->Unk4.Unk0->Unk792.FindItem(&v6, &v7, v8->Unk28, v8->Unk36, v8->Unk40))
                    ++v14;
            }
            else
            {
                ++v13;
                ++v14;
            }

            v10 += this->Unk132.Unk48[i] * v8->Unk20->Unk96; // THE SAME
        }
    }

    if(this->Unk4.Unk0->Unk792.GetSpace() >= v14 - v15)
    {
        if(v10 + this->Unk4.Unk0->Unk724 - v11 < 15 * this->Unk4.Unk0->Unk728 / 10)
        {
            if(this->Unk132.Unk0->Unk792.GetSpace() >= v12 - v13)
            {
                if(v11 + this->Unk132.Unk0->Unk724 - v10 < 15 * this->Unk132.Unk0->Unk728 / 10)
                    return 0;
            }

            return 2;
        }
    }

    return 1;
}

void CExchangeItems::DoExchange(void)
{
    CItem *v49[10]; // [sp+14h] [bp-84h]@21
    CItem *s[10]; // [sp+3Ch] [bp-5Ch]@21
    int v51; // [sp+64h] [bp-34h]@42
    int j; // [sp+7Ch] [bp-1Ch]@5
    int k; // [sp+80h] [bp-18h]@4
    int i; // [sp+94h] [bp-4h]@1

    g_gamelogbuffer.__ls(init("ITEM_EXCHANGE", this->Unk4.Unk0->Unk8, this->Unk4.Unk0->Unk768->Unk4));

    for(i = 0; i <= 9; ++i)
    {
        if(this->Unk4.Unk8[i] != -1)
        {
            CItem *k_0 = this->Unk4.Unk0->Unk792.GetItem(this->Unk4.Unk8[i]);
            if(k_0)
            {
                g_gamelogbuffer.__ls(k_0->Unk20->Unk12);
                g_gamelogbuffer.__ls(delim);
                g_gamelogbuffer.__ls(k_0->Unk44);
                g_gamelogbuffer.__ls(delim);
                g_gamelogbuffer.__ls(k_0->Unk36);
                g_gamelogbuffer.__ls(delim);
                g_gamelogbuffer.__ls(k_0->Unk40);
                g_gamelogbuffer.__ls(delim);
                g_gamelogbuffer.__ls(this->Unk4.Unk48[i]);
                g_gamelogbuffer.__ls(delim);
                g_gamelogbuffer.__ls(k_0->Unk168);

                for(j = 0; j < k_0->Unk168; ++j)
                {
                    if(k_0->Unk68[j].Unk0)
                    {
                        g_gamelogbuffer.__ls(delim);
                        g_gamelogbuffer.__ls(k_0->Unk68[j].Unk4);
                        g_gamelogbuffer.__ls(delim);
                        g_gamelogbuffer.__ls(k_0->Unk68[j].Unk8);
                    }
                }
            }
        }
    }

    g_gamelogbuffer.__ls(" <=> ");
    g_gamelogbuffer.__ls(this->Unk132.Unk0->Unk8);
    g_gamelogbuffer.__ls(delim);
    g_gamelogbuffer.__ls(this->Unk132.Unk0->Unk768->Unk4); // CHECK CHAR *

    for(i = 0; i <= 9; ++i)
    {
        if(this->Unk132.Unk8[i] != -1)
        {
            CItem *j_0 = this->Unk132.Unk0->Unk792.GetItem(this->Unk132.Unk8[i]);
            if(j_0)
            {
                g_gamelogbuffer.__ls(j_0->Unk20->Unk12);
                g_gamelogbuffer.__ls(delim);
                g_gamelogbuffer.__ls(j_0->Unk44);
                g_gamelogbuffer.__ls(delim);
                g_gamelogbuffer.__ls(j_0->Unk36);
                g_gamelogbuffer.__ls(delim);
                g_gamelogbuffer.__ls(j_0->Unk40);
                g_gamelogbuffer.__ls(delim);
                g_gamelogbuffer.__ls(this->Unk132.Unk48[i]);
                g_gamelogbuffer.__ls(delim);
                g_gamelogbuffer.__ls(j_0->Unk168);

                for(k = 0; k < j_0->Unk168; ++k)
                {
                    if(j_0->Unk68[k].Unk0)
                    {
                        g_gamelogbuffer.__ls(delim);
                        g_gamelogbuffer.__ls(j_0->Unk68[k].Unk4);
                        g_gamelogbuffer.__ls(delim);
                        g_gamelogbuffer.__ls(j_0->Unk68[k].Unk8);
                    }
                }
            }
        }
    }

    g_gamelogbuffer.__ls(end);

    CNetMsg v52;

    memset(s, 0, 40);
    memset(v49, 0, 40);

    for(i = 0; i <= 9; ++i)
    {
        CItem *j_2 = this->Unk4.Unk0->Unk792.GetItem(this->Unk4.Unk8[i]);
        if(j_2)
        {
            if(j_2->Unk20->Unk68 & 1 && j_2->Count() > this->Unk4.Unk48[i])
            {
                this->Unk4.Unk0->Unk792.Decrease(j_2, this->Unk4.Unk48[i]);
                ItemUpdateMsg(v52, j_2, -this->Unk4.Unk48[i]);
                s[i] = gserver.Unk41208.CreateItem(j_2->Unk28, -1, j_2->Unk36, j_2->Unk40, this->Unk4.Unk48[i]);
            }
            else
            {
                ItemDeleteMsg(v52, j_2);
                this->Unk4.Unk0->Unk792.Remove(j_2, 0, 1);

                s[i] = j_2;
            }

            if(this->Unk4.Unk0->Unk768)
                this->Unk4.Unk0->Unk768->WriteToOutput(v52);
        }

        j_2 = this->Unk132.Unk0->Unk792.GetItem(this->Unk132.Unk8[i]);
        if(j_2)
        {
            if(j_2->Unk20->Unk68 & 1 && j_2->Count() > this->Unk132.Unk48[i])
            {
                this->Unk132.Unk0->Unk792.Decrease(j_2, this->Unk132.Unk48[i]);
                ItemUpdateMsg(v52, j_2, -this->Unk132.Unk48[i]);
                v49[i] = gserver.Unk41208.CreateItem(j_2->Unk28, -1, j_2->Unk36, j_2->Unk40, this->Unk132.Unk48[i]);
            }
            else
            {
                ItemDeleteMsg(v52, j_2);
                this->Unk132.Unk0->Unk792.Remove(j_2, 0, 1);
                v49[i] = j_2;
            }

            if(this->Unk132.Unk0->Unk768)
                this->Unk132.Unk0->Unk768->WriteToOutput(v52);
        }
    }

    for(i = 0; i <= 9; ++i)
    {
        CItem *j_1 = s[i];
        if(j_1)
        {
            this->Unk132.Unk0->Unk792.AddItem(j_1, this->Unk132.Unk0, 0, 1, -1, -1);
            if(j_1->tab() >= 0)
            {
                ItemAddMsg(v52, j_1);
            }
            else
            {
                this->Unk132.Unk0->Unk792.FindItem(&k, &v51, j_1->Unk28, j_1->Unk36, j_1->Unk40);

                if(j_1)
                    delete j_1;

                j_1 = this->Unk132.Unk0->Unk792.GetItem(k, v51);
                ItemUpdateMsg(v52, j_1, this->Unk4.Unk48[i]);
            }

            if(this->Unk132.Unk0->Unk768)
                this->Unk132.Unk0->Unk768->WriteToOutput(v52);
        }

        j_1 = v49[i];
        if(j_1)
        {
            this->Unk4.Unk0->Unk792.AddItem(j_1, this->Unk4.Unk0, 0, 1, -1, -1);
            if(j_1->tab() >= 0)
            {
                ItemAddMsg(v52, j_1);
            }
            else
            {
                this->Unk4.Unk0->Unk792.FindItem(&k, &v51, j_1->Unk28, j_1->Unk36, j_1->Unk40);

                if(j_1)
                    delete j_1;

                j_1 = this->Unk4.Unk0->Unk792.GetItem(k, v51);
                ItemUpdateMsg(v52, j_1, this->Unk132.Unk48[i]);
            }

            if(this->Unk4.Unk0->Unk768)
                this->Unk4.Unk0->Unk768->WriteToOutput(v52);
        }
    }
}
