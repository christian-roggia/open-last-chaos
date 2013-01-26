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

#include "Party.h"

#include "PC.h"

CParty::CParty(char a2, CPC *a3, CPC *a4)
{
    this->Unk0    = a2;
    this->Unk8[0] = a3;
    this->Unk4    = 1;
    memset(&this->Unk8[1], 0, 28);
    this->Unk40   = a4;
    this->Unk8[0]->Unk1368 = this;
    this->Unk40->Unk1368   = this;
}

CParty::~CParty()
{
    for(int i = 0; i <= 7; ++i)
    {
        if(this->Unk8[i])
        {
            this->Unk8[i]->Unk1368 = 0;
            this->Unk8[i] = 0;
        }
    }
}

int CParty::Add(CPC *a2)
{
    int v3; // [sp+14h] [bp-4h]@3

    if(this->Unk4 <= 7)
    {
        v3 = this->Find(0);
        if(v3 != -1)
        {
            this->Unk8[v3] = a2;
            ++this->Unk4;
            a2->Unk1368 = this;
            return v3;
        }
    }

    return -1;
}

bool CParty::Del(CPC *a2)
{
    int v3; // [sp+1Ch] [bp-4h]@1

    v3 = this->Find(a2);
    if(v3 != -1)
    {
        this->Unk8[v3] = 0;
        --this->Unk4;
        a2->Unk1368 = 0;
        return !v3 || this->Unk4 <= 1;
    }

    return false;
}

int CParty::Allow(void)
{
    int v2; // [sp+14h] [bp-4h]@1

    v2 = -1;
    if(this->Unk40)
    {
        v2 = this->Add(this->Unk40);
        this->Unk40 = 0;
    }
    return v2;
}

int CParty::Request(CPC *a2)
{
    if(this->Unk4 <= 7)
    {
        if(this->Unk40)
        {
            return 1;
        }
        else
        {
            if(a2->Unk1368)
            {
                return 2;
            }
            else
            {
                this->Unk40 = a2;
                this->Unk40->Unk1368 = this;

                return 0;
            }
        }
    }

    return -1;
}

int CParty::Find(CPC *a2)
{
    for(int i = 0; i <= 7; ++i)
    {
        if(this->Unk8[i] == a2)
            return i;
    }

    return -1;
}

int CParty::FindByIndex(int a2)
{
    for(int i = 0; i <= 7; ++i)
    {
        if(this->Unk8[i] && this->Unk8[i]->Unk4 == a2)
            return i;
    }

    return -1;
}

bool CParty::Reject(void)
{
    this->Unk40->Unk1368 = 0;
    this->Unk40 = 0;

    return this->Unk4 <= 1;
}

void CParty::End(void)
{
    for(int i = 0; i <= 7; ++i)
    {
        if(this->Unk8[i])
        {
            this->Unk8[i]->Unk1368 = 0;
            this->Unk8[i] = 0;
        }
    }

    this->Unk4  = 0;
    this->Unk40 = 0;
}

CPC *CParty::GetRandomParty(int *a2)
{
    unsigned int v4; // [sp+18h] [bp-8h]@1
    CPC *v5; // [sp+1Ch] [bp-4h]@1

    v5 = 0;
    v4 = GetRandom(1, this->Unk4) - 1;

    for(int i = 0; i <= 7; ++i)
    {
        if(this->Unk8[i])
        {
            if(!v4)
            {
                v5 = this->Unk8[i];
                if(a2)
                    *a2 = i;
                return v5;
            }
            --v4;
        }
    }

    return v5;
}

void CParty::SendToInvisibleMember(CNetMsg &a2, CPC *a3)
{
    CPC *v4; // [sp+10h] [bp-8h]@4

    for(int i = 0; i <= 7; ++i)
    {
        if(!this->Unk8[i])
            continue;

        v4 = this->Unk8[i];
        if(v4->Unk140 - a3->Unk140 < 0)
        {
            if(a3->Unk140 - v4->Unk140 > 4)
                goto LABEL_12;
        }
        else
        {
            if(v4->Unk140 - a3->Unk140 > 4)
                goto LABEL_12;
        }

        if(v4->Unk144 - a3->Unk144 < 0)
        {
            if(a3->Unk144 - v4->Unk144 <= 4)
                continue;
        }
        else
        {
            if(v4->Unk144 - a3->Unk144 <= 4)
                continue;
        }
LABEL_12:
        if(v4->Unk768)
            v4->Unk768->WriteToOutput(a2);
    }
}

void CParty::SendAll(CNetMsg &a2, CPC *a3, bool a4) //int _CParty::SendAll(CNetMsg &a2, CPC *a3, bool a4) -----> THE FUCK IS THE LINE BEFORE CParty????
{
    for(int i = 0; i <= 7; ++i)
    {
        if(this->Unk8[i])
        {
            if(a4 || this->Unk8[i] != a3)
            {
                if(this->Unk8[i]->Unk768)
                    this->Unk8[i]->Unk768->WriteToOutput(a2);
            }
        }
    }
}

CPC *CParty::GetMember(int a2)
{
    return (a2 < 0 || a2 > 7) ? 0 : this->Unk8[a2];
}

char CParty::GetPartyType(void)
{
    return this->Unk0;
}

CPC *CParty::GetRequest(void)
{
    return this->Unk40;
}
