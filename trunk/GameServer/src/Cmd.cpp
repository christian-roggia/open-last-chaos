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

#include "Cmd.h"

CCmdList::CCmdList(void)
{
    this->Unk800 = 0;

    this->Add(15, do_Chat,         0, true );
    this->Add(12, do_Move,         0, false);
    this->Add(18, do_GoZone,       0, false);
    this->Add(13, do_Attack,       0, false);
    this->Add(16, do_Item,         0, false);
    this->Add(20, do_Exchange,     0, false);
    this->Add(21, do_MemPos,       0, false);
    this->Add(23, do_GM,           1, true );
    this->Add(24, do_Party,        0, false);
    this->Add(25, do_QuickSlot,    0, false);
    this->Add(26, do_NPCRegen,     0, false);
    this->Add(27, do_Skill,        0, false);
    this->Add(30, do_Rebirth,      0, false);
    this->Add(33, do_Action,       0, false);
    this->Add(35, do_Quest,        0, false);
    this->Add(36, do_UseStatPoint, 0, false);
    this->Add(37, do_Warp,         0, true );
    this->Add(38, do_Pulse,        0, true );
    this->Add(39, do_Produce,      0, false);
    this->Add(40, do_SSkill,       0, false);
    this->Add(41, do_PK,           0, false);
    this->Add(43, do_Event,        0, false);
    this->Add(44, do_PersonalShop, 0, false);
    this->Add(46, do_Stash,        0, false);
    this->Add(42, do_Guild,        0, false);
    this->Add(47, do_Change,       0, false);

    this->Sort();
}

CCmdList::~CCmdList()
{
    for(long i = 0; i < this->Unk800; ++i)
    {
        if(this->Unk0[i])
            delete this->Unk0[i];

        this->Unk0[i] = 0;
    }
}

bool CCmdList::Add(__tagMessageType a2, void (*a3)(CPC *,CNetMsg &), int a4, bool a5)
{
    if(this->Unk800 <= 199)
    {
        this->Unk0[this->Unk800] = new CCmd();
        this->Unk0[this->Unk800]->Unk0    = a2;
        this->Unk0[this->Unk800]->Unk12   = a3;
        this->Unk0[this->Unk800]->Unk4    = a4;
        this->Unk0[this->Unk800++]->Unk8  = a5;

        return true;
    }

    return false;
}

int CmdComp(void const *a1, void const *a2)
{
    return ((CCmd *)a1)->Unk0 - ((CCmd *)a2)->Unk0;
}

void CCmdList::Sort(void)
{
    qsort(this->Unk0, this->Unk800, 4, CmdComp);
}

int CCmdList::Find(CPC *a2, __tagMessageType a3)
{
    int v4; // [sp+1Ch] [bp-Ch]@1
    int v5; // [sp+20h] [bp-8h]@2
    int v6; // [sp+24h] [bp-4h]@1

    v6 = 0;
    v4 = this->Unk800;

    while(1)
    {
        v5 = (v4 + v6) / 2;
        if(this->Unk0[(v4 + v6) / 2]->Unk0 == a3)
            break;

        if(v5 - v6 <= 0)
            return -1;

        if(this->Unk0[(v4 + v6) / 2]->Unk0 - a3 <= 0)
            v6 = (v4 + v6) / 2;
        else
            v4 = (v4 + v6) / 2;
    }

    return (a2->Unk732 < this->Unk0[v5]->Unk4) ? -1 : ((v4 + v6) / 2);
}

// CHECK THE RETURN OF THIS FUNCTION
void CCmdList::Run(int a2, CPC *a3, CNetMsg &a4)
{
    if(this->Unk0[a2]->Unk8 || a3->IsSetPlayerState(4) == false)
        this->Unk0[a2]->Unk12(a3, a4);
}
