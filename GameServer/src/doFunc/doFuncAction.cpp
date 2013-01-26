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
#include "../Area.h"
#include "../Zone.h"

void do_Action(CPC *a1, CNetMsg &a2)
{
    char v7; // [sp+32h] [bp-6h]@1
    char v8; // [sp+33h] [bp-5h]@1
    int dest; // [sp+34h] [bp-4h]@1

    CNetMsg v6;

    a2.MoveFirst();
    a2.__rs(dest); // (int &) CHECKED
    a2.__rs(v8);   // (char &) CHECKED
    a2.__rs(v7);   // (char &) CHECKED

    if(v8)
    {
        ActionMsg(v6, a1, v8, v7);
        a1->Unk412->SendToCell(v6, a1, true, 4);

        return;
    }

    if(v7 == 3)
    {
        if(a1->Unk76 <= 0 || a1->Unk1328 || a1->IsSetPlayerState(64))
            return;

        if(!a1->IsSetPlayerState(1))
        {
            if(a1->Unk424)
            {
                a1->Unk424->Cancel();
                a1->Unk424 = 0;
            }

            a1->ResetPlayerState(2);
        }

        a1->TogglePlayerState(1);
        a1->CalcStatus(true);

        ActionMsg(v6, a1, v8, v7);
        a1->Unk412->SendToCell(v6, a1, true, 4);

        return;
    }

    if(v7 != 23)
    {
        ActionMsg(v6, a1, v8, v7);
        a1->Unk412->SendToCell(v6, a1, true, 4);

        return;
    }

    if(a1->Unk76 <= 0 || a1->Unk1328)
        return;

    if(a1->Unk408->Unk0 == 8)
        return;

    if(a1->Unk60 > 15)
    {
        if(a1->IsSetPlayerState(16) || a1->IsSetPlayerState(32) || a1->IsSetPlayerState(64))
            return;

        if(a1->IsInPeaceZone())
            return;

        if(a1->IsSetPlayerState(8))
        {
            a1->SetPlayerState(16);
            a1->Unk1864 = 100;
        }
        else
        {
            a1->TogglePlayerState(8);
        }

        ActionMsg(v6, a1, v8, v7);
        a1->Unk412->SendToCell(v6, a1, true, 4);

        return;
    }

    CNetMsg v5;

    SysMsg(v5, 39);

    if(a1->Unk768)
        a1->Unk768->WriteToOutput(v5);
}
