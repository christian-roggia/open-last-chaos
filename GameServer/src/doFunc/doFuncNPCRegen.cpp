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

void do_NPCRegen(CPC *a1, CNetMsg &a2)
{
    int v21; // [sp+28h] [bp-30h]@9
    CNPC *v23; // [sp+30h] [bp-28h]@6
    CZone *v24; // [sp+34h] [bp-24h]@7
    float v25; // [sp+38h] [bp-20h]@1
    float v26; // [sp+3Ch] [bp-1Ch]@1
    float v27; // [sp+40h] [bp-18h]@1
    float dest; // [sp+44h] [bp-14h]@1
    int src; // [sp+48h] [bp-10h]@1
    char v30; // [sp+4Ch] [bp-Ch]@1
    int v31; // [sp+50h] [bp-8h]@1
    int v32; // [sp+54h] [bp-4h]@1

    a2.MoveFirst();

    a2.__rs(v32);
    a2.__rs(v31);
    a2.__rs(dest);
    a2.__rs(v27);
    a2.__rs(v26);
    a2.__rs(v25);
    a2.__rs(v30);
    a2.__rs(src);

    if(v32 == -1)
    {
        if(a1->Unk408->Unk0 == 2 || a1->Unk408->Unk0 == 5 || a1->Unk408->Unk0 == 6)
        {
            ++a1->Unk412->Unk72;
            if(a1->Unk412->Unk32.Unk8 >= a1->Unk412->Unk72)
            {
                v23 = gserver.Unk452200.Create(v31);
                if(v23)
                {
                    v23->Unk120.Unk0  = dest;
                    v23->Unk476       = dest;
                    v23->Unk120.Unk4  = v27;
                    v23->Unk484       = v27;
                    v23->Unk120.Unk16 = v30;
                    v23->Unk480       = v30;
                    v23->Unk120.Unk12 = v25;
                    v23->Unk120.Unk8  = v26;

                    int v24_2;

                    a1->Unk412->AddNPC(v23);
                    a1->Unk412->PointToCellNum(v23->Unk120.Unk0, v23->Unk120.Unk4, &v24_2, &v21);
                    a1->Unk412->CharToCell(v23, v23->Unk120.Unk16, v24_2, v21);

                    CNetMsg v20;

                    NPCRegenMsg(v20, v23, src);

                    a1->Unk412->SendToCell(v20, a1, 1, 4);
                }
            }
            else
            {
                int v23_2 = gserver.FindZone(0);
                if(v23_2 != -1)
                {
                    v24 = &gserver.Unk452196[v23_2];
                    GoZone(a1, 0, v24->Unk52[0]->Unk0, GetRandom(v24->Unk52[0]->Unk4, v24->Unk52[0]->Unk12) / 2.0, GetRandom(v24->Unk52[0]->Unk8, v24->Unk52[0]->Unk16) / 2.0);
                }
            }
        }
    }
}
