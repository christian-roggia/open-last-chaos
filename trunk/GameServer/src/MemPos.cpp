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

#include "MemPos.h"

CMemPosData::CMemPosData(int a2, float a3, float a4, char a5, char const *src)
{
    this->Unk0  = a2;
    this->Unk4  = a3;
    this->Unk8  = a4;
    this->Unk12 = a5;
    strcpy(this->Unk13, src);
}

CMemPos::CMemPos(void)
{
    this->Unk0 = 0;
    memset(this->Unk4, 0, 20);
}

CMemPos::~CMemPos()
{
    for(int i = 0; i <= 4; ++i)
    {
        if(this->Unk4[i])
        {
            delete this->Unk4[i];
            this->Unk4[i] = 0;
        }
    }

    this->Unk0 = 0;
}

bool CMemPos::Write(int a2, int a3, float a4, float a5, char a6, char const *src)
{
    if(a2 >= 0 && a2 <= 4)
    {
        if(this->Unk4[a2])
        {
            this->Unk4[a2]->Unk0 = a3;
            this->Unk4[a2]->Unk4 = a4;
            this->Unk4[a2]->Unk8 = a5;
            this->Unk4[a2]->Unk12 = a6;
            strcpy(this->Unk4[a2]->Unk13, src);
        }
        else
        {
            ++this->Unk0;
            this->Unk4[a2] = new CMemPosData(a3, a4, a5, a6, src);
        }

        return true;
    }

    return false;
}

bool CMemPos::Delete(int a2)
{
    if(a2 >= 0 && a2 <= 4)
    {
        if(this->Unk4[a2])
        {
            --this->Unk0;
            delete this->Unk4[a2];
            this->Unk4[a2] = 0;
        }

        return true;
    }

    return false;
}
