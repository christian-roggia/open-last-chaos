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

#include "Cell.h"
#include "Character.h"
#include "PC.h"

CCell::CCell(void)
{
    this->Unk0 = 0;
    this->Unk4 = 0;
    this->Unk8 = 0;
    this->Unk12 = 0;
}

void CCell::CharToCell(CCharacter *a2)
{
    if(a2->Unk140 < 0)
    {
        if(this->Unk0)
            this->Unk0->Unk400 = a2;

        a2->Unk404 = this->Unk0;
        a2->Unk400 = 0;
        this->Unk0 = a2;

        if(a2->Unk0 == 1)
        {
            ++this->Unk8;
        }
        else
        {
            if(!a2->Unk0)
                ++this->Unk12;
        }
    }
}

void CCell::CharFromCell(CCharacter *a2)
{
    if(a2->Unk140 >= 0)
    {
        if(a2->Unk400)
        {
            a2->Unk400->Unk404 = a2->Unk404;

            if(a2->Unk404)
                a2->Unk404->Unk400 = a2->Unk400;
        }
        else
        {
            this->Unk0 = a2->Unk404;

            if(a2->Unk404)
                a2->Unk404->Unk400 = 0;
        }

        a2->Unk400 = 0;
        a2->Unk404 = 0;

        if(a2->Unk0 == 1)
        {
            --this->Unk8;
        }
        else
        {
            if(!a2->Unk0)
                --this->Unk12;
        }
    }
}

bool CCell::Send(CNetMsg &a2, CPC *a3)
{
    CCharacter *v4, *v5;

    v4 = this->Unk0;

    while(1)
    {
        v5 = v4;

        if(!v4)
            break;

        v4 = v4->Unk404;

        if(v5 != a3 && !v5->Unk0)
        {
            if(((CPC *)v5)->Unk768)
                ((CPC *)v5)->Unk768->WriteToOutput(a2);
        }
    }

    return 1;
}

void CCell::ItemToCell(CItem *a2)
{
    if(a2->Unk196 < 0)
    {
        if(this->Unk4)
            this->Unk4->Unk204 = a2;

        a2->Unk208 = this->Unk4;
        a2->Unk204 = 0;
        this->Unk4 = a2;
    }
}

void CCell::ItemFromCell(CItem *a2)
{
    if(a2->Unk196 >= 0)
    {
        if(a2->Unk204)
        {
            a2->Unk204->Unk208 = a2->Unk208;

            if(a2->Unk208)
                a2->Unk208->Unk204 = a2->Unk204;
        }
        else
        {
            this->Unk4 = a2->Unk208;

            if(a2->Unk208)
                a2->Unk208->Unk204 = 0;
        }

        a2->Unk204 = 0;
        a2->Unk208 = 0;
    }
}
