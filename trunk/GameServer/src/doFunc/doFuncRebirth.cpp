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

#warning JUMPOUT skipped in doFuncRebirth

void do_Rebirth(CPC *a1, CNetMsg &a2)
{
    CZone *v6; // [sp+3Ch] [bp-Ch]@9
    int v7; // [sp+40h] [bp-8h]@3
    int v8; // [sp+44h] [bp-4h]@3

    if(a1->Unk76 <= 0)
    {
        if(a1->Unk408)
        {
            v8 = 0;
            v7 = 0;

            //if(a1->Unk408->Unk0 <= 8)
            //    JUMPOUT(__CS__, off_80D3784[a1->Unk408->Unk0]);

            v8 = 0;
            v7 = 0;

            a1->Unk76 = a1->Unk764 / 2;
            if(a1->Unk80 < a1->Unk766 / 2)
                a1->Unk80 = a1->Unk766 / 2;

            CNetMsg v5;

            RebirthMsg(v5, a1);

            if(a1->Unk412)
                a1->Unk412->SendToCell(v5, a1, 1, 4);

            a1->ResetPlayerState(15);
            a1->CalcStatus(1);
            a1->Unk473 = 1;

            v6 = &gserver.Unk452196[gserver.FindZone(v8)];
            GoZone(a1, v8, v6->Unk52[0]->Unk0, GetRandom(v6->Unk52[0]->Unk4, v6->Unk52[0]->Unk12) / 2.0, GetRandom(v6->Unk52[0]->Unk8, v6->Unk52[0]->Unk16) / 2.0);
        }
    }
}
