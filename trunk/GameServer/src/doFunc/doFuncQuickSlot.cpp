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

void do_QuickSlot(CPC *a1, CNetMsg &a2)
{
    int v8; // ST50_4@32
    int v9; // ST4C_4@32
    int v10; // ST48_4@32
    CItem *v11; // ST44_4@32

    CItem *v12; // [sp+34h] [bp-20h]@19
    char v13; // [sp+38h] [bp-1Ch]@19
    char dest; // [sp+39h] [bp-1Bh]@17
    char v15; // [sp+3Ah] [bp-1Ah]@4
    char v16; // [sp+3Bh] [bp-19h]@4
    char v18; // [sp+52h] [bp-2h]@4
    char v19; // [sp+53h] [bp-1h]@1

    a2.MoveFirst();

    CNetMsg v17;

    a2.__rs(v19);

    if(v19 == 1)
    {
        a2.__rs(v18);
        a2.__rs(v16);
        a2.__rs(v15);

        if(v18 < 0 || v18 > 2 || v16 < 0 || v16 > 9)
            return;

        a1->Unk1372[v18].Unk0[v16] = v15;

        if(v15)
        {
            if(v15 > 0)
            {
                if(v15 == 1)
                {
                    a2.__rs(dest);

                    a1->Unk1372[v18].Unk40[v16]  = -1;
                    a1->Unk1372[v18].Unk80[v16]  = dest;
                    a1->Unk1372[v18].Unk120[v16] = 0;
                }
                else
                {
                    if(v15 == 2)
                    {
                        a2.__rs(dest);
                        a2.__rs(v13);

                        v12 = a1->Unk792.GetItem(dest, v13);
                        if(!v12)
                        {
                            a1->Unk1372[v18].Unk0[v16] = -1;
                            return;
                        }

                        a1->Unk1372[v18].Unk120[v16] = v12;
                    }
                }
            }
            else
            {
                if(v15 == -1)
                {
                    a1->Unk1372[v18].Unk0[v16]   = -1;
                    a1->Unk1372[v18].Unk40[v16]  = -1;
                    a1->Unk1372[v18].Unk80[v16]  = -1;
                    a1->Unk1372[v18].Unk120[v16] = 0;
                }
            }
        }
        else
        {
            a2.__rs(dest);

            a1->Unk1372[v18].Unk40[v16]  = dest;
            a1->Unk1372[v18].Unk80[v16]  = -1;
            a1->Unk1372[v18].Unk120[v16] = 0;
        }

        QuickSlotAddMsg(v17, a1, v18, v16);

        if(a1->Unk768)
            a1->Unk768->WriteToOutput(v17);
    }
    else
    {
        if(v19 == 2)
        {
            a2.__rs(v18);
            a2.__rs(v13);
            a2.__rs(dest);

            if(v18 < 0 || v18 > 2 || v13 < 0 || v13 > 9 || dest < 0 || dest > 9)
                return;

            v8  = a1->Unk1372[v18].Unk0[v13];
            v9  = a1->Unk1372[v18].Unk40[v13];
            v10 = a1->Unk1372[v18].Unk80[v13];
            v11 = a1->Unk1372[v18].Unk120[v13];

            a1->Unk1372[v18].Unk0[v13]   = a1->Unk1372[v18].Unk0[dest];
            a1->Unk1372[v18].Unk40[v13]  = a1->Unk1372[v18].Unk40[dest];
            a1->Unk1372[v18].Unk80[v13]  = a1->Unk1372[v18].Unk80[dest];
            a1->Unk1372[v18].Unk120[v13] = a1->Unk1372[v18].Unk120[dest];

            a1->Unk1372[v18].Unk0[dest]   = v8;
            a1->Unk1372[v18].Unk40[dest]  = v9;
            a1->Unk1372[v18].Unk80[dest]  = v10;
            a1->Unk1372[v18].Unk120[dest] = v11;

            QuickSlotAddMsg(v17, a1, v18, v13);

            if(a1->Unk768)
                a1->Unk768->WriteToOutput(v17);

            QuickSlotAddMsg(v17, a1, v18, dest);

            if(a1->Unk768)
                a1->Unk768->WriteToOutput(v17);
        }
    }
}
