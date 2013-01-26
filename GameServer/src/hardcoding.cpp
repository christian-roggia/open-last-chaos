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

#include "hardcoding.h"

CQuickSlot::CQuickSlot(void)
{
    memset(this->Unk0,  -1, 40);
    memset(this->Unk40, -1, 40);
    memset(this->Unk80, -1, 40);
    memset(this->Unk120, 0, 40);
}

CShop::CShop(void)
{
    this->Unk0  = -1;
    this->Unk16 = 0.0;
    this->Unk12 = 0.0;
    this->Unk8  = 0.0;
    this->Unk4  = 0.0;
    this->Unk20 = 0;
    this->Unk28 = 0;
    this->Unk24 = 0;
    this->Unk32 = 0;
    this->Unk36 = 0;
}

CShop::~CShop()
{
    if(this->Unk32 && this->Unk32) // DOUBLE CHECK -> ?
        delete [] this->Unk32;

    this->Unk32 = 0;
}

bool CShop::ThersIsItem(int a2)
{
    for(int i = 0; i < this->Unk36; ++i)
    {
        if(this->Unk32[i] == a2)
            return true;
    }

    return false;
}


CPos::CPos(void)
{
    this->Unk12 = 0.0;
    this->Unk8  = 0.0;
    this->Unk4  = 0.0;
    this->Unk0  = 0.0;
    this->Unk16 = 0;
}

CPos::CPos(float a2, float a3, float a4, float a5, int a6)
{
    this->Unk0  = a2;
    this->Unk4  = a3;
    this->Unk8  = a4;
    this->Unk12 = a5;
    this->Unk16 = *(char *)&a6;
}

void CPos::__as(CPos const &a2)
{
    this->Unk0  = a2.Unk0;
    this->Unk4  = a2.Unk4;
    this->Unk8  = a2.Unk8;
    this->Unk12 = a2.Unk12;
    this->Unk16 = a2.Unk16;
}
