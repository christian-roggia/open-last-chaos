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

#include "PersonalShop.h"

CPersonalShop::CPersonalShop(char a2, char *src)
{
    this->Unk0 = a2;
    strcpy(this->Unk1, src);
    memset(this->Unk104, -1, 40);
    memset(this->Unk144, 0, 0x50);
    memset(this->Unk224, 0, 0x50);
    memset(this->Unk304, -1, 20);
    memset(this->Unk324, 0, 40);
    this->Unk364 = 0;
}

bool CPersonalShop::AddItem(bool a2, int a3, long long a4, long long a5)
{
    signed int i; // [sp+14h] [bp-4h]@2
    signed int j; // [sp+14h] [bp-4h]@9

    if(a2)
    {
        for(i = 0; i <= 9 && this->Unk104[i] != -1; ++i);
        if(i == 10)
        {
            return false;
        }
        else
        {
            this->Unk104[i] = a3;
            this->Unk144[i] = a4;
            this->Unk224[i] = a5;
            return true;
        }
    }
    else
    {
        for(j = 0; j <= 4 && this->Unk304[j] != -1; ++j);
        if(j == 5)
        {
            return false;
        }
        else
        {
            this->Unk304[j] = a3;
            this->Unk324[j] = a4;
            this->Unk364 = a5;
            return true;
        }
    }
}

int CPersonalShop::FindItem(bool a2, int a3)
{
    if(a2)
    {
        for(int i = 0; i <= 9; ++i)
        {
            if(this->Unk104[i] == a3)
                return i;
        }
    }
    else
    {
        for(int j = 0; j <= 4; ++j)
        {
            if(this->Unk304[j] == a3)
                return j;
        }
    }
    return -1;
}

void CPersonalShop::RemoveNormalItem(int a2, long long a3)
{
    for(int i = 0; i <= 9; ++i)
    {
        if(this->Unk104[i] == a2)
        {
            this->Unk144[i] -= a3;
            if(this->Unk144[i] <= 0)
            {
                this->Unk104[i] = -1;
                this->Unk144[i] = 0;
                this->Unk224[i] = 0;
            }

            if(!this->GetNormalCount())
            {
                if(!this->GetPackageCount())
                    this->Unk0 = 0;
            }
            return;
        }
    }
}

void CPersonalShop::RemovePackage(void)
{
    memset(this->Unk304, -1, 20);
    memset(this->Unk324, 0, 40);
    this->Unk364 = 0;
    this->Unk0 = this->GetNormalCount() ? 5 : 0;
}

char CPersonalShop::GetNormalCount(void)
{
    char v3; // [sp+17h] [bp-1h]@1

    v3 = 0;
    for(int i = 0; i <= 9; ++i)
    {
        if(this->Unk104[i] != -1)
            ++v3;
    }
    return v3;
}

int CPersonalShop::GetNextNormalItem(int a2)
{
    int v3; // [sp+Ch] [bp+Ch]@1

    v3 = a2 + 1;
    if(v3 >= 0)
    {
        while(v3 <= 9)
        {
            if(this->Unk104[v3] != -1)
                return v3;
            ++v3;
        }
    }

    return -1;
}

int CPersonalShop::GetPackageCount(void)
{
    char v3; // [sp+17h] [bp-1h]@1

    v3 = 0;
    for(int i = 0; i <= 4; ++i)
    {
        if(this->Unk304[i] != -1)
            ++v3;
    }
    return v3;
}

int CPersonalShop::GetNextPackageItem(int a2)
{
    int v3; // [sp+Ch] [bp+Ch]@1

    v3 = a2 + 1;
    if(v3 >= 0)
    {
        while(v3 <= 4)
        {
            if(this->Unk304[v3] != -1)
                return v3;
            ++v3;
        }
    }
    return -1;
}

char CPersonalShop::GetType(void)
{
    return this->Unk0;
}

char *CPersonalShop::GetName(void)
{
    return this->Unk1;
}

int CPersonalShop::GetNormalItemIndex(int a2)
{
    return (a2 < 0 || a2 > 9) ? -1 : this->Unk104[a2];
}

long long CPersonalShop::GetNormalItemCount(int a2)
{
    return (a2 < 0 || a2 > 9) ? -1 : this->Unk144[a2];
}

long long CPersonalShop::GetNormalItemPrice(int a2)
{
    return (a2 < 0 || a2 > 9) ? -1 : this->Unk224[a2];
}

long long CPersonalShop::GetPackagePrice(void)
{
    return this->Unk364;
}

long long CPersonalShop::GetPackageItemIndex(int a2)
{
    return (a2 < 0 || a2 > 4) ? -1 : this->Unk304[a2];
}

long long CPersonalShop::GetPackageItemCount(int a2)
{
    return (a2 < 0 || a2 > 4) ? 0 : this->Unk324[a2];
}
