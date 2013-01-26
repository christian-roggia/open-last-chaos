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
#include "../ExchangeItems.h"
#include "../Server.h"

void do_Exchange(CPC *a1, CNetMsg &a2)
{
    unsigned char dest; // [sp+17h] [bp-1h]@4

    if(a1->Unk420)
    {
        if(!a1->Unk1328)
        {
            a2.MoveFirst();

            a2.__rs(dest);

            if(dest)
            {
                if(dest == 1)
                    do_ExchangeItem(a1, a2);
            }
            else
            {
                do_ExchangeReq(a1, a2);
            }
        }
    }
}

void do_ExchangeReq(CPC *a1, CNetMsg &a2)
{
    char v4; // [sp+16h] [bp-2h]@1
    char dest; // [sp+17h] [bp-1h]@1

    a2.MoveFirst();

    a2.__rs(dest);
    a2.__rs(v4);

    switch(v4)
    {
        case 0:
            do_ExchangeReqReq(a1, a2);
            break;
        case 1:
            do_ExchangeReqRep(a1, a2);
            break;
        case 2:
            do_ExchangeReqReject(a1, a2);
            break;
        case 5:
            do_ExchangeReqReady(a1, a2);
            break;
        case 10:
            do_ExchangeReqOK(a1, a2);
            break;
        default:
            break;
    }
}

void do_ExchangeItem(CPC *a1, CNetMsg &a2)
{
    unsigned char v4; // [sp+16h] [bp-2h]@1
    char dest; // [sp+17h] [bp-1h]@1

    a2.MoveFirst();

    a2.__rs(dest);
    a2.__rs(v4);

    if(v4)
    {
        if(v4 == 3)
            do_ExchangeItemDel(a1, a2);
    }
    else
    {
        do_ExchangeItemAdd(a1, a2);
    }
}

void do_ExchangeReqReq(CPC *a1, CNetMsg &a2)
{
    CExchangeItems *v10; // [sp+2Ch] [bp-28h]@12
    CPC *v12; // [sp+44h] [bp-10h]@3
    int v13; // [sp+48h] [bp-Ch]@1
    int dest; // [sp+4Ch] [bp-8h]@1
    char v15; // [sp+52h] [bp-2h]@1
    char v16; // [sp+53h] [bp-1h]@1

    a2.MoveFirst();

    *g_buf  = 0;
    *g_buf2 = 0;

    a2.__rs(v16);
    a2.__rs(v15);
    a2.__rs(dest);
    a2.__rs(g_buf);
    a2.__rs(v13);
    a2.__rs(g_buf2);

    if(!a1->IsSetPlayerState(64))
    {
        if(a1->Unk4 == dest)
        {
            v12 = (CPC *)a1->Unk412->FindCharInCell(a1, v13, 0, 0);
            if(v12)
            {
                if(a1->Unk1324 || v12->Unk1324)
                {
                    CNetMsg v11;

                    SysMsg(v11, 8);

                    if(a1->Unk768)
                        a1->Unk768->WriteToOutput(v11);
                }
                else
                {
                    v10 = new CExchangeItems();
                    v10->SetCharacter(a1, v12);

                    v12->Unk1324 = v10;
                    a1->Unk1324  = v10;

                    CNetMsg v11;

                    ExchangeReqMsg(v11, 0, a1, v12);

                    if(v12->Unk768)
                        v12->Unk768->WriteToOutput(v11);
                }
            }
            else
            {
                CNetMsg v11;

                SysMsg(v11, 7);

                if(a1->Unk768)
                    a1->Unk768->WriteToOutput(v11);
            }
        }
    }
}

void do_ExchangeReqRep(CPC *a1, CNetMsg &a2)
{
    CPC *v5; // [sp+28h] [bp-10h]@2
    CPC *v6; // [sp+2Ch] [bp-Ch]@2
    CExchangeItems *v7; // [sp+30h] [bp-8h]@2
    char v8; // [sp+36h] [bp-2h]@2
    char dest; // [sp+37h] [bp-1h]@2

    if(a1->Unk1324)
    {
        a2.MoveFirst();

        a2.__rs(dest);
        a2.__rs(v8);

        v7 = a1->Unk1324;
        v6 = v7->Unk4.Unk0;
        v5 = v7->Unk132.Unk0;

        if(!v7->Unk0)
        {
            v7->Unk0 = 1;

            CNetMsg v4;

            ExchangeReqMsg(v4, 1, v6, v5);

            if(v6->Unk768)
                v6->Unk768->WriteToOutput(v4);

            if(v5->Unk768)
                v5->Unk768->WriteToOutput(v4);
        }
    }
}

void do_ExchangeReqReject(CPC *a1, CNetMsg &a2)
{
    char v7; // [sp+29h] [bp-Fh]@7
    char dest; // [sp+2Ah] [bp-Eh]@7
    char v9; // [sp+2Bh] [bp-Dh]@3
    CPC *v10; // [sp+2Ch] [bp-Ch]@2
    CPC *v11; // [sp+30h] [bp-8h]@2
    CExchangeItems *v12; // [sp+34h] [bp-4h]@2

    if(a1->Unk1324)
    {
        v12 = a1->Unk1324;
        v11 = v12->Unk4.Unk0;
        v10 = v12->Unk132.Unk0;

        if(v11 == a1)
        {
            v9 = 1;
        }
        else
        {
            if(v10 != a1)
                return;

            v9 = 0;
        }

        a2.MoveFirst();

        a2.__rs(dest);
        a2.__rs(v7);

        delete v12;

        v10->Unk1324 = 0;
        v11->Unk1324 = 0;

        CNetMsg v6;


        ExchangeReqMsg(v6, (v9 ? 3 : 4), v11, v10);

        if(v11->Unk768)
            v11->Unk768->WriteToOutput(v6);

        if(v10->Unk768)
            v10->Unk768->WriteToOutput(v6);
    }
}

void do_ExchangeReqReady(CPC *a1, CNetMsg &a2)
{
    char v7; // [sp+29h] [bp-Fh]@7
    char dest; // [sp+2Ah] [bp-Eh]@7
    char v9; // [sp+2Bh] [bp-Dh]@3
    CPC *v10; // [sp+2Ch] [bp-Ch]@2
    CPC *v11; // [sp+30h] [bp-8h]@2
    CExchangeItems *v12; // [sp+34h] [bp-4h]@2

    if(a1->Unk1324)
    {
        v12 = a1->Unk1324;
        v11 = v12->Unk4.Unk0;
        v10 = v12->Unk132.Unk0;

        if(v11 == a1)
        {
            v9 = 1;
        }
        else
        {
            if(v10 != a1)
                return;

            v9 = 0;
        }

        a2.MoveFirst();

        a2.__rs(dest);
        a2.__rs(v7);

        CNetMsg v6;

        if(v12->Unk0 != 1 && v12->Unk0 != 6 && v12->Unk0 != 7)
            return;

        if(v12->CanExchange() == 1)
        {
            ExchangeReqMsg(v6, 8, v11, v10);
            v12->Unk0 = 1;
        }
        else
        {
            if(v12->CanExchange() > 1 && v12->CanExchange() == 2)
            {
                ExchangeReqMsg(v6, 9, v11, v10);
                v12->Unk0 = 1;
            }
            else
            {
                if(v12->Unk0 == 1)
                {
                    v12->Unk0 = v9 ? 6 : 7;
                    ExchangeReqMsg(v6, v12->Unk0, v11, v10);
                }
                else
                {
                    if((v12->Unk0 != 6 || v9) && (v12->Unk0 != 7 || !v9))
                        return;

                    v12->Unk0 = 5;
                    ExchangeReqMsg(v6, v12->Unk0, v11, v10);
                }
            }
        }

        if(v11->Unk768)
            v11->Unk768->WriteToOutput(v6);

        if(v10->Unk768)
            v10->Unk768->WriteToOutput(v6);
    }
}

void do_ExchangeReqOK(CPC *a1, CNetMsg &a2)
{
    char v8; // [sp+29h] [bp-Fh]@7
    char dest; // [sp+2Ah] [bp-Eh]@7
    char v10; // [sp+2Bh] [bp-Dh]@3
    CPC *v11; // [sp+2Ch] [bp-Ch]@2
    CPC *v12; // [sp+30h] [bp-8h]@2
    CExchangeItems *v13; // [sp+34h] [bp-4h]@2

    if(a1->Unk1324)
    {
        v13 = a1->Unk1324;
        v12 = v13->Unk4.Unk0;
        v11 = v13->Unk132.Unk0;

        if(v12 == a1)
        {
            v10 = 1;
        }
        else
        {
            if(v11 != a1)
                return;

            v10 = 0;
        }

        a2.MoveFirst();

        a2.__rs(dest);
        a2.__rs(v8);

        CNetMsg v7;

        if(v13->Unk0 == 5)
        {
            v13->Unk0 = v10 ? 11 : 12;

            ExchangeReqMsg(v7, v13->Unk0, v12, v11);

            if(v12->Unk768)
                v12->Unk768->WriteToOutput(v7);

            if(v11->Unk768)
                v11->Unk768->WriteToOutput(v7);
        }
        else
        {
            if(v13->Unk0 == 11 && !v10 || v13->Unk0 == 12 && v10)
            {
                if(v13->CanExchange() == 1)
                {
                    ExchangeReqMsg(v7, 3, v12, v11);

                    if(v12->Unk768)
                        v12->Unk768->WriteToOutput(v7);

                    if(v11->Unk768)
                        v11->Unk768->WriteToOutput(v7);
                }
                else
                {
                    if(v13->CanExchange() > 1)
                    {
                        if(v13->CanExchange() == 2)
                        {
                            ExchangeReqMsg(v7, 4, v12, v11);

                            if(v12->Unk768)
                                v12->Unk768->WriteToOutput(v7);

                            if(v11->Unk768)
                                v11->Unk768->WriteToOutput(v7);
                        }
                    }
                    else
                    {
                        if(v13->CanExchange() == 0)
                        {
                            v13->DoExchange();

                            ExchangeReqMsg(v7, 10, v12, v11);

                            if(v12->Unk768)
                                v12->Unk768->WriteToOutput(v7);

                            if(v11->Unk768)
                                v11->Unk768->WriteToOutput(v7);
                        }
                    }
                }

                v12->SaveNow(false);
                v11->SaveNow(false);

                delete v13;

                v11->Unk1324 = 0;
                v12->Unk1324 = 0;
            }
        }
    }
}

void do_ExchangeItemAdd(CPC *a1, CNetMsg &a2)
{
    int v11; // [sp+24h] [bp-44h]@39
    bool v12; // [sp+2Bh] [bp-3Dh]@39
    int v13; // [sp+2Ch] [bp-3Ch]@30
    int v14; // [sp+30h] [bp-38h]@30
    CItem *v15; // [sp+34h] [bp-34h]@31
    long long v16; // [sp+38h] [bp-30h]@19
    int v17; // [sp+40h] [bp-28h]@19
    long long dest; // [sp+44h] [bp-24h]@19
    int v19; // [sp+4Ch] [bp-1Ch]@19
    char v20; // [sp+52h] [bp-16h]@19
    char v21; // [sp+53h] [bp-15h]@19
    CPC *v22; // [sp+54h] [bp-14h]@7
    CPC *v23; // [sp+58h] [bp-10h]@7
    CExchangeItems *v24; // [sp+5Ch] [bp-Ch]@7
    char v25; // [sp+63h] [bp-5h]@3
    CPC *v26; // [sp+64h] [bp-4h]@3

    if(a1->Unk1324)
    {
        if(a1->Unk1324->Unk4.Unk0 == a1)
        {
            v26 = a1->Unk1324->Unk132.Unk0;
            v25 = 1;
        }
        else
        {
            if(a1->Unk1324->Unk132.Unk0 != a1)
                return;

            v26 = a1->Unk1324->Unk4.Unk0;
            v25 = 0;
        }

        v24 = a1->Unk1324;
        v23 = v24->Unk4.Unk0;
        v22 = v24->Unk132.Unk0;

        if(v24->Unk0 == 6)
        {
            if(v25)
                return;
        }
        else
        {
            if(v24->Unk0 > 6)
            {
                if(v24->Unk0 != 7 || !v25)
                    return;
            }
            else
            {
                if(v24->Unk0 != 1)
                    return;
            }
        }

        a2.MoveFirst();

        a2.__rs(v21);
        a2.__rs(v20);
        a2.__rs(v19);
        a2.__rs(dest);

        v17 = v24->Find(a1, v19);
        v16 = 0;

        if(v17 != -1)
            v16 = v25 ? v24->Unk4.Unk48[v17] : v24->Unk132.Unk48[v17];

        if(v17 != -1 || (!v25 || (v24->Unk4.Unk4 <= 9)) && (v25 || (v24->Unk132.Unk4 <= 9)))
        {
            if(a1->Unk792.FindItem(&v14, &v13, v19))
            {
                v15 = a1->Unk792.GetItem(v14, v13);
                if(v15)
                {
                    if(v17 != -1 || (dest <= v15->Count()))
                    {
                        if(v17 == -1 || (v16 + dest <= v15->Count()))
                        {
                            if(v15->Unk20->Unk68 & 8)
                            {
                                if(v15->Unk32 == -1)
                                {
                                    v11 = v24->Add(a1, v19, dest, &v12);
                                    if(v11 != -1)
                                    {
                                        CNetMsg v10;

                                        if(v12)
                                        {
                                            if(v25)
                                                ExchangeItemMsg(v10, 6, v15, v24->Unk4.Unk48[v11]);
                                            else
                                                ExchangeItemMsg(v10, 7, v15, v24->Unk132.Unk48[v11]);
                                        }
                                        else
                                        {
                                            ExchangeItemMsg(v10, (v25 ? 1 : 2), v15, dest);
                                        }

                                        if(v23->Unk768)
                                            v23->Unk768->WriteToOutput(v10);

                                        if(v22->Unk768)
                                            v22->Unk768->WriteToOutput(v10);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void do_ExchangeItemDel(CPC *a1, CNetMsg &a2)
{
    int v10; // [sp+30h] [bp-38h]@31
    long long v11; // [sp+34h] [bp-34h]@27
    CItem *v13; // [sp+3Ch] [bp-2Ch]@21
    int v14; // [sp+40h] [bp-28h]@19
    long long dest; // [sp+44h] [bp-24h]@19
    int v16; // [sp+4Ch] [bp-1Ch]@19
    char v17; // [sp+52h] [bp-16h]@19
    char v18; // [sp+53h] [bp-15h]@19
    CPC *v19; // [sp+54h] [bp-14h]@7
    CPC *v20; // [sp+58h] [bp-10h]@7
    CExchangeItems *v21; // [sp+5Ch] [bp-Ch]@7
    char v22; // [sp+63h] [bp-5h]@3
    CPC *v23; // [sp+64h] [bp-4h]@3

    if(a1->Unk1324)
    {
        if(a1->Unk1324->Unk4.Unk0 == a1)
        {
            v23 = a1->Unk1324->Unk132.Unk0;
            v22 = 1;
        }
        else
        {
            if(a1->Unk1324->Unk132.Unk0 != a1)
                return;

            v23 = a1->Unk1324->Unk4.Unk0;
            v22 = 0;
        }

        v21 = a1->Unk1324;
        v20 = v21->Unk4.Unk0;
        v19 = v21->Unk132.Unk0;

        if(v21->Unk0 == 6)
        {
            if(v22)
                return;
        }
        else
        {
            if(v21->Unk0 > 6)
            {
                if(v21->Unk0 != 7 || !v22)
                    return;
            }
            else
            {
                if(v21->Unk0 != 1)
                    return;
            }
        }

        a2.MoveFirst();

        a2.__rs(v18);
        a2.__rs(v17);
        a2.__rs(v16);
        a2.__rs(dest);

        v14 = v21->Find(a1, v16);
        if(v14 != -1)
        {
            if(v22)
            {
                v13 = v21->Unk4.Unk0->Unk792.GetItem(v21->Unk4.Unk8[v14]);
            }
            else
            {
                v13 = v21->Unk132.Unk0->Unk792.GetItem(v21->Unk132.Unk8[v14]);
            }

            if(v13)
            {
                v11 = v22 ? v21->Unk4.Unk48[v14] : v21->Unk132.Unk48[v14];

                if(dest <= v11) // SHIT FOR LONG LONG
                {
                    v10 = v21->Del(a1, v16, dest);

                    CNetMsg v9;

                    if(v10 == -1)
                    {
                        return;
                    }
                    else
                    {
                        if((!v22 || v21->Unk4.Unk48[v10]) && (v22 || v21->Unk132.Unk48[v10]))
                        {
                            if(v22)
                                ExchangeItemMsg(v9, 6, v13, v21->Unk4.Unk48[v10]);
                            else
                                ExchangeItemMsg(v9, 7, v13, v21->Unk132.Unk48[v10]);
                        }
                        else
                        {
                            ExchangeItemMsg(v9, (v22 ? 4 : 5), v13, 0);
                        }

                        if(v20->Unk768)
                            v20->Unk768->WriteToOutput(v9);

                        if(v19->Unk768)
                            v19->Unk768->WriteToOutput(v9);
                    }
                }
            }
        }
    }
}
