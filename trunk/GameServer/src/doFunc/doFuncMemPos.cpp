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

void do_MemPos(CPC *a1, CNetMsg &a2)
{
    CItem *v9; // [sp+10h] [bp-28h]@30
    int v10; // [sp+14h] [bp-24h]@29
    int v12; // [sp+2Ch] [bp-Ch]@5
    int v13; // [sp+30h] [bp-8h]@5
    unsigned v14; // [sp+36h] [bp-2h]@5
    unsigned dest; // [sp+37h] [bp-1h]@2

    if(a1->Unk76 > 0)
    {
        a2.MoveFirst();

        a2.__rs(dest);

        if(dest == 1)
        {
            *g_buf = 0;

            a2.__rs(v14);
            a2.__rs(g_buf);

            if(a1->Unk792.FindItem(&v13, &v12, gserver.Unk41128[5]->Unk0, 0, 0)) // *unk_41232
            {
                if(a1->Unk408 && a1->Unk408->Unk45)
                {
                    if(a1->Unk1332.Write(v14, a1->Unk408->Unk0, a1->Unk120.Unk0, a1->Unk120.Unk4, a1->Unk120.Unk16, g_buf))
                    {
                        CNetMsg v11;

                        MemPosWriteMsg(v11, a1, v14);

                        if(a1->Unk768)
                            a1->Unk768->WriteToOutput(v11);
                    }
                }
                else
                {
                    CNetMsg v11;

                    SysMsg(v11, 21);

                    if(a1->Unk768)
                        a1->Unk768->WriteToOutput(v11);
                }
            }
        }
        else
        {
            if(dest == 2)
            {
                a2.__rs(v14);

                v12 = a1->CanWarp();
                if(v12)
                {
                    CNetMsg v11;

                    SysMsg(v11, v12);

                    if(a1->Unk768)
                        a1->Unk768->WriteToOutput(v11);
                }
                else
                {
                    if((v14 & 0x80) == 0)
                    {
                        if(v14 <= 4)
                        {
                            if(a1->Unk1332.Unk4[v14])
                            {
                                if(a1->Unk408 && a1->Unk408->Unk0 == a1->Unk1332.Unk4[v14]->Unk0)
                                {
                                    if(a1->Unk792.FindItem(&v13, &v10, gserver.Unk41128[5]->Unk0, 0, 0)) // *unk_41232
                                    {
                                        v9 = a1->Unk792.GetItem(v13, v10);

                                        CNetMsg v11;

                                        ItemUseMsg(v11, a1, v9->tab(), v9->row(), v9->col(), v9->Unk24, 0);

                                        if(a1->Unk768)
                                            a1->Unk768->WriteToOutput(v11);

                                        a1->Unk792.Decrease(v9, 1);
                                        if(v9->Count())
                                        {
                                            ItemUpdateMsg(v11, v9, -1);

                                            if(a1->Unk768)
                                                a1->Unk768->WriteToOutput(v11);
                                        }
                                        else
                                        {
                                            ItemDeleteMsg(v11, v9);

                                            if(a1->Unk768)
                                                a1->Unk768->WriteToOutput(v11);

                                            a1->Unk792.Remove(v9, 1, 1);
                                        }

                                        a1->Unk1360 = 1;
                                        a1->Unk1364 = v14;
                                        a1->Unk1356 = 100;

                                        a1->SetPlayerState(4);

                                        WarpStartMsg(v11, a1);

                                        a1->Unk412->SendToCell(v11, a1, 1, 4);
                                    }
                                }
                                else
                                {
                                    CNetMsg v11;

                                    SysMsg(v11, 25);

                                    if(a1->Unk768)
                                        a1->Unk768->WriteToOutput(v11);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
