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

#include "Stash.h"
#include "Server.h"

CStash::CStash(void)
{
    memset(this->Unk0, 0, 200);
}

CStash::~CStash()
{
    for(int i = 0; i <= 49; ++i)
    {
        if(this->Unk0[i])
        {
            if(this->Unk0[i])
                delete this->Unk0[i]; // CHECK THIS!!!

            this->Unk0[i] = 0;
        }
    }
}

int CStash::add(CItem *a2)
{
    if(a2)
    {
        for(int i = 0; i <= 49; ++i)
        {
            if(!this->Unk0[i])
            {
                this->Unk0[i] = a2;
                return i;
            }
        }
    }

    return -1;
}

int CStash::add(int a2, int a3, int a4, long long a5)
{
    int v7;

    if(a2 >= 0 && a5 > 0)
    {
        v7 = this->find(a2, a3, a4);

        if(v7 == -1)
        {
            for(int i = 0; i <= 49; ++i)
            {
                if(!this->Unk0[i])
                {
                    this->Unk0[i] = gserver.Unk41208.CreateItem(a2, -1, a3, a4, a5);
                    return i;
                }
            }

            return -1;
        }
        else
        {
            this->Unk0[v7]->Unk12 += a5;

            return v7;
        }
    }

    return 0;
}

int CStash::remove(int a2, long long a3)
{
    int i;

    if(a2 > 0 && a3)
    {
        for(i = 0; ; ++i)
        {
          if(i > 49)
            return -1;
          if(this->Unk0[i] && this->Unk0[i]->Unk24 == a2)
            break;
        }

        if(a3 <= this->Unk0[i]->Count())
        {
            this->Unk0[i]->Unk12 -= a3;

            if(this->Unk0[i]->Count())
            {
                return this->Unk0[i]->Count();
            }
            else
            {
                if(this->Unk0[i])
                    delete this->Unk0[i]; // CHECK THIS!!!

                this->Unk0[i] = 0;
                return 0;
            }
        }
    }

    return -2;
}

CItem *CStash::remove(int a2)
{
    CItem *v2;

    for(int i = 0; i <= 49; ++i)
    {
        if(this->Unk0[i] && this->Unk0[i]->Unk24 == a2)
        {
            v2 = this->Unk0[i];
            this->Unk0[i] = 0;

            return v2;
        }
    }

    return 0;
}

int CStash::find(int a2, int a3, int a4)
{
    for(int i = 0; i <= 49; ++i)
    {
        if(this->Unk0[i] && this->Unk0[i]->Unk28 == a2 && this->Unk0[i]->Unk36 == a3 && this->Unk0[i]->Unk40 == a4)
            return i;
    }

    return -1;
}

int CStash::find(int a2)
{
    for(int i = 0; i <= 49; ++i)
    {
        if(this->Unk0[i] && this->Unk0[i]->Unk24 == a2)
            return i;
    }

    return -1;
}

int CStash::space(void)
{
    int v3 = 0; // [sp+14h] [bp-4h]@1

    for(int i = 0; i <= 49; ++i)
    {
        if(!this->Unk0[i])
            ++v3;
    }

    return v3;
}

CItem *CStash::item(int a2)
{
    return (a2 < 0 || a2 > 49) ? 0 : this->Unk0[a2];
}

