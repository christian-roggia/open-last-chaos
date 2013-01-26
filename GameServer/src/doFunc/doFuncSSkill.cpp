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

#include "../doFunc.h"
#include "../Server.h"

void do_SSkill(CPC *a1, CNetMsg &a2)
{
    CSSkill *v4; // [sp+28h] [bp-30h]@34
    int v5; // [sp+2Ch] [bp-2Ch]@20
    CSSkill *v6; // [sp+30h] [bp-28h]@20
    CSSkillProto *v8; // [sp+38h] [bp-20h]@7
    int dest; // [sp+50h] [bp-8h]@3
    char v11; // [sp+57h] [bp-1h]@2

    if(a1->Unk76 <= 0 || (a2.MoveFirst(), a2.__rs(v11), v11 != 1))
        return;

    a2.__rs(dest);

    CNetMsg v9;

    if(dest <= 0)
    {
        SSkillLearnErrorMsg(v9, 4);

        if(a1->Unk768)
            a1->Unk768->WriteToOutput(v9);

        return;
    }

    v8 = gserver.Unk452244.FindProto(dest);

    if(!v8)
    {
        SSkillLearnErrorMsg(v9, 4);

        if(a1->Unk768)
            a1->Unk768->WriteToOutput(v9);

        return;
    }

    for(CSSkillNode *i = a1->Unk716.Unk0; i; i = i->Unk4)
    {
        if(i->Unk0->Unk0->Unk8 == v8->Unk8 && i->Unk0->Unk0->Unk16 != -1 && i->Unk0->Unk0->Unk16 > v8->Unk16)
        {
            SSkillLearnErrorMsg(v9, 4);

            if(a1->Unk768)
                a1->Unk768->WriteToOutput(v9);

            return;
        }
    }

    v6 = a1->Unk716.Find(dest);
    v5 = 1;

    if(v6)
    {
        if(v6->Unk4 >= v6->Unk0->Unk12)
            return;

        v5 = v6->Unk4 + 1;
    }

    if(v8->Unk20[v5-1] > a1->Unk60)
    {
        SSkillLearnErrorMsg(v9, 0);

        if(a1->Unk768)
            a1->Unk768->WriteToOutput(v9);

        return;
    }

    if(10000 * v8->Unk40[v5-1] > a1->Unk72)
    {
        SSkillLearnErrorMsg(v9, 1);

        if(a1->Unk768)
            a1->Unk768->WriteToOutput(v9);

        return;
    }

    if(v8->Unk60 != -1 && !v6)
    {
        v4 = a1->Unk716.Find(v8->Unk60);

        if(!v4)
        {
            SSkillLearnErrorMsg(v9, 2);

            if(a1->Unk768)
                a1->Unk768->WriteToOutput(v9);

            return;
        }

        if(v8->Unk64 > v4->Unk4)
        {
            SSkillLearnErrorMsg(v9, 3);

            if(a1->Unk768)
                a1->Unk768->WriteToOutput(v9);

            return;
        }
    }

    CSSkillNode *v4_1 = a1->Unk716.Unk0, *i;

    while(1)
    {
        i = v4_1;

        if(!v4_1)
            break;

        v4_1 = i->Unk4;

        if(i->Unk0->Unk0->Unk16 != -1 && i->Unk0->Unk0->Unk8 == v8->Unk8 && i->Unk0->Unk0->Unk16 < v8->Unk16)
        {
            CNetMsg v3;

            SSkillRemoveMsg(v3, i->Unk0);

            if(a1->Unk768)
                a1->Unk768->WriteToOutput(v3);

            if(!a1->Unk716.Remove(i->Unk0))
            {
                SSkillLearnErrorMsg(v9, 4);

                if(a1->Unk768)
                    a1->Unk768->WriteToOutput(v9);

                return;
            }
        }
    }

    if(v6)
    {
        if(v6->Unk4 >= v6->Unk0->Unk12)
        {
            SSkillLearnErrorMsg(v9, 4);

            if(a1->Unk768)
                a1->Unk768->WriteToOutput(v9);

            return;
        }

        ++v6->Unk4;

        a1->Unk72 -= 10000 * v8->Unk40[v5-1];
        a1->Unk473 = 1;

        CNetMsg v3;

        SSkillLearnMsg(v3, v6);

        if(a1->Unk768)
            a1->Unk768->WriteToOutput(v3);

        return;
    }

    v6 = gserver.Unk452244.Create(dest, 1);

    if(v6)
    {
        if(a1->Unk716.Add(v6))
        {
            a1->Unk72 -= 10000 * v8->Unk40[v5-1];
            a1->Unk473 = 1;

            CNetMsg v3;

            SSkillLearnMsg(v3, v6);

            if(a1->Unk768)
                a1->Unk768->WriteToOutput(v3);

            return;
        }

        SSkillLearnErrorMsg(v9, 4);

        if(a1->Unk768)
            a1->Unk768->WriteToOutput(v9);
    }
    else
    {
        SSkillLearnErrorMsg(v9, 4);

        if(a1->Unk768)
            a1->Unk768->WriteToOutput(v9);
    }
}

