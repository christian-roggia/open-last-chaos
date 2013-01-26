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

void do_UseStatPoint(CPC *a1, CNetMsg &a2)
{
    short v4; // [sp+Eh] [bp-1Ah]@7
    _tagStatPointUseType v6; // [sp+26h] [bp-2h]@1
    unsigned char dest; // [sp+27h] [bp-1h]@1

    CNetMsg v5;

    a2.MoveFirst();
    a2.__rs(dest); // (unsigned char &) CHECKED
    a2.__rs(v6);   // (unsigned char &) CHECKED

    if(dest != 1)
        return;

    if(a1->Unk740 <= 0)
    {
        StatPointErrorMsg(v5, 0);

        if(a1->Unk768)
            a1->Unk768->WriteToOutput(v5);

        return;
    }

    if(a1->UseStatPoint(v6, &v4))
    {
        StatPointUseMsg(v5, a1, v6, v4);

        if(a1->Unk768)
            a1->Unk768->WriteToOutput(v5);

        return;
    }

    StatPointErrorMsg(v5, 1);

    if(a1->Unk768)
        a1->Unk768->WriteToOutput(v5);

    return;
}

void do_Pulse(CPC *a1, CNetMsg &a2) // Y U NO BOOL?
{
    int dest; // [sp+14h] [bp-4h]@1

    a2.MoveFirst();
    a2.__rs(dest); // (int &) CHECKED

    a1->Unk768->CheckHackPulse(dest); // return skipped
}

void do_Change(CPC *a1, CNetMsg &a2)
{
    unsigned char dest; // [sp+27h] [bp-1h]@1

    a2.MoveFirst();
    a2.__rs(dest); // (unsigned char &) CHECKED

    if(dest != 2) return;
    if(!a1->IsSetPlayerState(64)) return;
    if(a1->Unk2388 == -1) return;

    a1->Unk2388 = -1;
    a1->Unk2384 = 0;

    a1->ResetPlayerState(64);

    CNetMsg v3;

    ChangeStopMsg(v3, a1);

    a1->Unk412->SendToCell(v3, a1, true, 4);
}
