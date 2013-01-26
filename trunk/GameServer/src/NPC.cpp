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

#include "NPC.h"
#include "Server.h"

CNPC::CNPC(void)
{
    this->Unk0   = 1;
    this->Unk464 = 0;
    this->Unk468 = -1;
    this->Unk508 = 0;
    this->Unk472 = 0;
    this->Unk492 = 0;
    this->Unk476 = 0;
    this->Unk480 = 0;
    this->Unk484 = 0;
    this->Unk488 = 0;
    this->Unk504 = 1;
    this->Unk744 = 0;
    this->Unk748 = 0;
    this->Unk512 = gserver.Unk41248;
    this->Unk496 = 0;
    this->Unk516 = 0;
    this->Unk520 = 0;
    this->Unk524 = 0;
    this->Unk525 = 0;
    this->Unk526 = 0;
    this->Unk500 = 0;
    this->Unk497 = 0;
    memset(this->Unk732, 0, 8);
    memset(this->Unk528, 0, 200);
    this->Unk728 = 0;
    this->Unk752 = 0;
    this->Unk740 = 0;
}

CNPC::~CNPC()
{
    this->Unk464 = 0;
    this->Unk752 = 0;
    for(int i = 0; i <= 1; ++i)
    {
        if(this->Unk732[i])
            delete this->Unk732[i];

        this->Unk732[i] = 0;
    }
    this->Unk424 = 0;
}

void CNPC::DeleteNPC(void)
{
    DelAttackList(this);

    if(this)
        delete this;
}

void CNPC::InitAIVar(void)
{
    this->Unk524 = 0;
    this->Unk520 = 0;
    this->Unk525 = 0;
}

void CNPC::ResetStat(void)
{
    this->Unk78  = this->Unk464->Unk88;
    this->Unk82  = this->Unk464->Unk90;
    this->Unk104 = this->Unk464->Unk76;
    this->Unk108 = this->Unk464->Unk80;
    this->Unk112 = this->Unk464->Unk100;
    this->Unk114 = this->Unk464->Unk102;
    this->Unk84  = this->Unk464->Unk288;
    this->Unk86  = this->Unk464->Unk290;
    this->Unk88  = this->Unk464->Unk292;
    this->Unk90  = this->Unk464->Unk294;
    this->Unk102 = this->Unk464->Unk309;
    this->Unk496 = this->Unk464->Unk308;
    if(this->Unk496)
    {
        if(this->Unk496 == 1)
            this->Unk94 = this->Unk464->Unk296;
    }
    else
    {
        this->Unk92 = this->Unk464->Unk296;
    }
    this->Unk96  = this->Unk464->Unk298;
    this->Unk98  = this->Unk464->Unk300;
    this->Unk100 = this->Unk464->Unk302;
}

int CNPC::GetAttackLevel(void)
{
    return this->Unk464->Unk304;
}

int CNPC::GetDefenseLevel(void)
{
    return this->Unk464->Unk306;
}

char CNPC::GetAttackType(CSkillProto const *a2)
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

    return this->Unk464->Unk308;
}

float CNPC::GetSize(void)
{
    return this->Unk464->Unk84;
}
