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

void do_PK(CPC *a1, CNetMsg &a2)
{
    /* TODO */
}

// ----->> ASSEMBLY ERROR <<----- //
/*void do_PK(CPC *a1, CNetMsg &a2)
{
    char dest; // [sp+17h] [bp-1h]@1

    a2.MoveFirst();
    a2.__rs(dest);

    if(dest == 3) do_PKRecoverItemSealed(a1, a2);
}


// local variable allocation has failed!
void do_PKRecoverItemSealed(CPC *a1, CNetMsg &a2)
{
    CInventory *v5; // eax@2
    signed int v6; // ST6C_4@13
    signed __int64 v7; // qcx@13
    int v11; // ecx@30
    int v12; // ST40_4@30 OVERLAPPED
    __int64 v13; // ST38_8@30 OVERLAPPED
    __int64 v14; // [sp+48h] [bp-2Ch]@13
    CItem *v15; // [sp+50h] [bp-24h]@9
    int dest; // [sp+58h] [bp-1Ch]@1
    char v17; // [sp+5Dh] [bp-17h]@1
    char v18; // [sp+5Eh] [bp-16h]@1
    char v19; // [sp+5Fh] [bp-15h]@1

    CNetMsg v20;

    a2.__rs(v19);
    a2.__rs(v18);
    a2.__rs(v17);
    a2.__rs(dest);

    if(v19)
    {
        if(v19 == 1)
        {
            v5 = &a1->Unk880;
        }
        else
        {
            if(v19 == 2)
                v5 = &a1->Unk968;
            else
                v5 = 0;
        }
    }
    else
    {
        v5 = &a1->Unk792;
    }

    if(v5 && (v15 = v5->GetItem(v18, v17)) != 0 && v15->Unk24 == dest && v15->Unk32 != -1 && v15->Unk40 & 0x100)
    {
        v6 = *(_WORD *)(*(_DWORD *)(v15 + 20) + 100);
        v7 = (unsigned int)v6 * 10LL * *(_WORD *)(*(_DWORD *)(v15 + 20) + 100);
        HIDWORD(v7) += (v6 >> 31) * 10 * *(_WORD *)(*(_DWORD *)(v15 + 20) + 100);
        v14 = v7;

        if(v15->Unk20->Unk4)
        {
            if(v15->Unk20->Unk4 == 1)
            {
                if(v15->Unk20->Unk8 <= 5)
                    JUMPOUT(__CS__, off_80D35B4[v15->Unk20->Unk8]);
            }
        }
        else
        {
            v14 = 2 * v7;
        }

        if(*(_DWORD *)(a1 + 1280) && v14 <= CItem::Count(*(_DWORD *)(a1 + 1280)))
        {
            if(CItem::Count(*(_DWORD *)(a1 + 1280)) == v14)
            {
                ItemDeleteMsg((int)&v20, *(_DWORD *)(a1 + 1280));
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v20);
                CPC::AddMoney(a1, -v14);
            }
            else
            {
                CPC::AddMoney(a1, -v14);
                ItemUpdateMsg((int)&v20, *(_DWORD *)(a1 + 1280), -v14);
                if(*(_DWORD *)(a1 + 768))
                    CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v20);
            }
            v11 = *(_DWORD *)(v15 + 40);
            BYTE1(v11) &= 0xFEu;
            *(_DWORD *)(v15 + 40) = v11;
            v12 = 0;
            v13 = (unsigned int)v15;
            ItemUpdateMsg((int)&v20, v15, *(__int64 *)(&v12 - 1));
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v20);
            PKRecoverItemSealMsg((int)&v20, v15);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v20);
            CPC::CalcStatus(a1, 1);
        }
        else
        {
            PKErrorMsg((int)&v20, 0);
            if(*(_DWORD *)(a1 + 768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v20);
        }
    }
    else
    {
        PKErrorMsg((int)&v20, 3);
        if(*(_DWORD *)(a1 + 768))
            CDescriptor::WriteToOutput(*(_DWORD *)(a1 + 768), (int)&v20);
    }
}
// 80B6E10: failed to expand linear variable ST40_4_31
// 80B6E10: failed to expand linear variable ST40_4_30
*/
