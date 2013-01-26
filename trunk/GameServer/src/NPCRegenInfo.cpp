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

#include "NPCRegenInfo.h"

CNPCRegenInfo::CNPCRegenInfo(void)
{
    this->Unk0  = -1;
    this->Unk4  = -1;
    this->Unk24 = 0;
    this->Unk36 = 0;
    this->Unk8  = 0;
    this->Unk12 = 0;
    this->Unk16 = 0;
    this->Unk20 = 0;
    this->Unk24 = 0;
    this->Unk32 = 0;
    this->Unk40 = 0;
    this->Unk28 = 0;
}

CNPCRegenInfo::~CNPCRegenInfo()
{
    ;
}

CNPCRegenList::CNPCRegenList(void)
{
    this->Unk0  = -1;
    this->Unk4  = 0;
    this->Unk8  = 0;
    this->Unk12 = 0;
}

CNPCRegenList::~CNPCRegenList()
{
    delete [] this->Unk4; // CHECK THIS!!!

    this->Unk4 = 0;
    this->Unk8 = 0;
}

void CNPCRegenList::SetCount(int a2)
{
  delete [] this->Unk4; // CHECK THIS!!!

  this->Unk4  = 0;
  this->Unk8  = a2;
  this->Unk12 = 0;

  if(a2)
      this->Unk4 = new CNPCRegenInfo[a2]; // CHECK THIS!!!
}

void CNPCRegenList::AddRegenInfo(int a2, int a3, float a4, int a5, float a6, float a7, int a8, int a9)
{
    if(this->Unk12 < this->Unk8)
    {
        this->Unk4[this->Unk12].Unk0 = a2;
        this->Unk4[this->Unk12].Unk4 = a9;
        this->Unk4[this->Unk12].Unk24 = a3;
        this->Unk4[this->Unk12].Unk8 = a4;
        this->Unk4[this->Unk12].Unk12 = a5;
        this->Unk4[this->Unk12].Unk16 = a6;
        this->Unk4[this->Unk12].Unk20 = a7;
        this->Unk4[this->Unk12].Unk28 = a8;
        this->Unk4[this->Unk12].Unk32 = 0;
        this->Unk4[this->Unk12++].Unk36 = 0;
    }
}

void CNPCRegenList::AddRegenInfo(CNPCRegenInfo *src)
{
    if(this->Unk12 < this->Unk8)
        memcpy(&this->Unk4[this->Unk12++], &src, sizeof(CNPCRegenInfo));
}

void CNPCRegenList::Init(void)
{
    delete [] this->Unk4; // CHECK THIS!!!

    this->Unk4  = 0;
    this->Unk8  = 0;
    this->Unk0  = -1;
    this->Unk4  = 0;
    this->Unk8  = 0;
    this->Unk12 = 0;
}
