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

#include "Server.h"

void CServer::ProcessBilling(CNetMsg &a2)
{
    char v46; // [sp+22h] [bp-B2h]@121
    char v47; // [sp+23h] [bp-B1h]@121
    int v48; // [sp+24h] [bp-B0h]@79
    int v50; // [sp+2Ch] [bp-A8h]@68
    unsigned char v51; // [sp+33h] [bp-A1h]@32
    char v52[50]; // [sp+34h] [bp-A0h]@16
    char src[50]; // [sp+68h] [bp-6Ch]@16
    char s2[48]; // [sp+6Ch] [bp-68h]@110
    CPC *v61; // [sp+C0h] [bp-14h]@2
    char v62; // [sp+C7h] [bp-Dh]@2
    int v63; // [sp+C8h] [bp-Ch]@2
    int dest; // [sp+CCh] [bp-8h]@2
    char v65; // [sp+D3h] [bp-1h]@1

    a2.MoveFirst();

    a2.__rs(v65);

    switch(v65)
    {
        case 0xE:
            int dest = -1;
            v63 = -1;
            v62 = 0;

            a2.__rs(dest);
            a2.__rs(v63);
            a2.__rs(v62);

            CPC *v61 = this->Unk24.Find(v63);
            if(v61)
            {
                if(v62)
                {
                    if(v62 == 1)
                    {
                        CNetMsg v58;

                        StashErrorMsg(v58, 12);

                        if(v61->Unk768)
                            v61->Unk768->WriteToOutput(v58);
                    }
                    else
                    {
                        CNetMsg v58;

                        StashErrorMsg(v58, 11);

                        if(v61->Unk768)
                            v61->Unk768->WriteToOutput(v58);
                    }
                }
                else
                {
                    CNetMsg v59;

                    StashSealMsg(v59);

                    if(v61->Unk768)
                        v61->Unk768->WriteToOutput(v59);

                    g_gamelogbuffer.__ls(init("STASH SEALED", v61->Unk8, v61->Unk768->Unk4));
                    g_gamelogbuffer.__ls(end);
                }

                v61->Unk1260.Init();
            }
            return;
        case 0xD:
            v63 = -1;
            int v61 = -1;
            src[0] = 0;
            memset(src + 1, 0, 49);
            v52[0] = 0;
            memset(v52 + 1, 0, 49);
            v62 = 0;

            a2.__rs(v63);
            a2.__rs(v61);
            a2.__rs(src);
            a2.__rs(v52);
            a2.__rs(v62);

            CPC *dest = this->Unk24.Find(v61);
            if(dest)
            {
                if(v62)
                {
                    if(v62 == 1)
                    {
                        CNetMsg v58;

                        StashErrorMsg(v58, 4);

                        if(dest->Unk768)
                            dest->Unk768->WriteToOutput(v58);
                    }
                    else
                    {
                        CNetMsg v58;

                        StashErrorMsg(v58, 3);

                        if(dest->Unk768)
                            dest->Unk768->WriteToOutput(v58);
                    }
                }
                else
                {
                    CNetMsg v58;

                    StashChangePasswordRepMsg(v58, strlen(v52) != 0);

                    if(dest->Unk768)
                        dest->Unk768->WriteToOutput(v58);

                    g_gamelogbuffer.__ls(init("STASH CHANGE PASSWORD", dest->Unk8, dest->Unk768->Unk4));
                    g_gamelogbuffer.__ls(src);
                    g_gamelogbuffer.__ls(delim);
                    g_gamelogbuffer.__ls(v52);
                    g_gamelogbuffer.__ls(end);
                }

                dest->Unk1260.Init();
            }
            return;
        case 0xC:
            v63 = -1;
            v61 = -1;
            v52[0] = 0;
            memset(v52 + 1, 0, 49);
            v62 = 0;

            a2.__rs(v63);
            a2.__rs(v61);
            a2.__rs(v52);
            a2.__rs(v62);

            CPC *dest = this->Unk24.Find(v61);
            if(dest)
            {
                if(v62)
                {
                    if(v62 == 1)
                    {
                        CNetMsg src;

                        StashErrorMsg(src, 4);

                        if(dest->Unk768)
                            dest->Unk768->WriteToOutput(src);
                    }
                    else
                    {
                        CNetMsg src;

                        StashErrorMsg(src, 3);

                        if(dest->Unk768)
                            dest->Unk768->WriteToOutput(src);
                    }
                }
                else
                {
                    int v51 = -1;

                    dest->Unk1260.MoveFirst();

                    dest->Unk1260.__rs(v51);

                    if(v51 == 4)
                    {
                        do_StashKeep_real(dest);
                    }
                    else
                    {
                        if(v51 > 4)
                        {
                            if(v51 == 6)
                                do_StashTake_real(dest);
                        }
                        else
                        {
                            if(v51 == 2)
                                do_StashListReq_real(dest);
                        }
                    }
                }

                dest->Unk1260.Init();
            }
            return;
        case 0xB:
            v63 = -1;
            v61 = -1;
            v51 = -1;
            v62 = -1;

            a2.__rs(v63);
            a2.__rs(v61);
            a2.__rs(v51);
            a2.__rs(v62);

            CPC *dest = this->Unk24.Find(v61);
            if(dest)
            {
                if((v51 & 0x80) == 0 && v62 >= 0)
                {
                    if(v62)
                    {
                        CNetMsg v52;

                        StashErrorMsg(v52, 3);

                        if(dest->Unk768)
                            dest->Unk768->WriteToOutput(v52);
                    }
                    else
                    {
                        CNetMsg v52;

                        StashIsSetPassword(v52, v51 != 0);

                        if(dest->Unk768)
                            dest->Unk768->WriteToOutput(v52);
                    }
                }
                else
                {
                    CNetMsg v52;

                    StashErrorMsg(v52, 1);

                    if(dest->Unk768)
                        dest->Unk768->WriteToOutput(v52);
                }
            }
            return;
        case 9:
            CNetMsg v52;

            v63 = 0;
            v61 = 0;
            v51 = -1;

            a2.__rs(v63);
            a2.__rs(v61);
            a2.__rs(v51);

            if(v51)
            {
                v48 = gserver.Unk24.Find(v61);

                if(!v48)
                    return;

                CNetMsg v54;

                if(v51 == 6)
                {
                    EventErrorMsg(v54, 1);
                }
                else
                {
                    if(v51 != 7)
                        return;
                    EventErrorMsg(v54, 0);
                }

                if(v48->Unk768)
                    v48->Unk768->WriteToOutput(v54);

                return;
            }

            CPC *dest = gserver.Unk24.Find(v61);

            if(!dest || dest->Unk768->Unk0 != v63)
                goto LABEL_93;

            v50 = -1;
            v22 = dest->Unk477;

            if(v22 == 1)
            {
                v50 = 427;
            }
            else
            {
                if(v22 > 1)
                {
                    if(v22 == 2)
                    {
                        v50 = 462;
                    }
                    else
                    {
                        if(v22 == 3)
                            v50 = 461;
                    }
                }
                else
                {
                    if(!v22)
                        v50 = 460;
                }
            }

            CInventory *v49 = &dest->Unk792;
            CItem *v48 = this->Unk41208.CreateItem(v50, -1, 0, 0, 1);

            if(!v48)
            {
                EventErrorMsg(v52, 1);

                if(dest->Unk768)
                    dest->Unk768->WriteToOutput(v52);

                goto LABEL_93;
            }

            if(!v49->AddItem(v48, dest, 0, 1, -1, -1))
            {
                EventErrorMsg(v52, 2);

                if(dest->Unk768)
                    dest->Unk768->WriteToOutput(v52);

                if(v48)
                    (*(void (__cdecl **)(int, signed int))(*(_DWORD *)(v48 + 220) + 8))(v48, 3);

                v48 = 0;
LABEL_93:
                if(!gserver.Unk452128)
                {
                    if(gserver.Unk16)
                    {
                        if(!gserver.Unk16->Unk361)
                        {
                            ConnPreopenGiftMsg(v52, v63, v61, 1);
							
                            if(this->Unk16)
                                this->Unk16->WriteToOutput(v52);
                        }
                    }
                }

                return;
            }

            ItemAddMsg(v52, v48);

            if(dest->Unk768)
                dest->Unk768->WriteToOutput(v52);

            EventPreopenGiftMsg(v52, v48->Unk28);

            if(dest->Unk768)
                dest->Unk768->WriteToOutput(v52);

            g_gamelogbuffer.__ls(init("EVENT PREOPEN", dest->Unk8, dest->Unk768->Unk4));
            g_gamelogbuffer.__ls(v48->Unk28);
            g_gamelogbuffer.__ls(end);

            return;
        case 1:
            a2.__rs(s2);
            a2.__rs(v51);

            CDescriptor *v50 = this->FindConnectIdName(s2, 0);
            if(v50)
            {
                if(v51)
                {
                    v50->Unk348 = -1;
                }
                else
                {
                    v50->Unk348 = 1;
					
                    a2.__rs(v48);
                    a2.__rs(v62);
                    a2.__rs(v49);
                    a2.__rs(v47);
                    a2.__rs(v46);
                    a2.__rs(v63);

                    v50->Unk0 = v48;
                }

                CNetMsg v54;

                switch(v51)
                {
                    case 0:
                        if(v50->Unk340 && v50->Unk340 != 1 && v50->Unk340 != 17)
                            v50->Unk340 = 31;

                        break;
                    case 3:
                        g_gamelogbuffer.__ls(init("CONN_ERR", s2));
                        g_gamelogbuffer.__ls("ALREADY CONNECT");
                        g_gamelogbuffer.__ls(end);

                        MsgrLogoutReqMsg(v54, 0, -1, -1, -1, s2);

                        if(!gserver.Unk452129 && gserver.Unk12 && !gserver.Unk12->Unk361 && this->Unk12)
                            this->Unk12->WriteToOutput(v54);

                        FailMsg(v54, 18);

                        if(v50)
                            v50->WriteToOutput(v54);

                        break;
                    case 1:
                    case 4:
                        g_gamelogbuffer.__ls(init("CONN_ERR", s2));
                        g_gamelogbuffer.__ls("CONNECTOR SYSTEM ERROR");
                        g_gamelogbuffer.__ls(end);

                        FailMsg(v54, 22);

                        if(v50)
                            v50->WriteToOutput(v54);

                        break;
                    case 2:
                        g_gamelogbuffer.__ls(init("CONN_ERR", s2));
                        g_gamelogbuffer.__ls("NO MATCH");
                        g_gamelogbuffer.__ls(end);

                        FailMsg(v54, 23);

                        if(v50)
                            v50->WriteToOutput(v54);

                        break;
                    case 5:
                        g_gamelogbuffer.__ls(init("CONN_ERR", s2));
                        g_gamelogbuffer.__ls("BLOCKED USER");
                        g_gamelogbuffer.__ls(end);

                        FailMsg(v54, 24);

                        if(v50)
                            v50->WriteToOutput(v54);

                        break;
                    default:
                        FailMsg(v54, 22);

                        if(v50)
                            v50->WriteToOutput(v54);

                        break;
                }
            }
            else
            {
                g_gamelogbuffer.__ls(init("SYS_ERR"));
                g_gamelogbuffer.__ls("Connector descriptor not fount :");
                g_gamelogbuffer.__ls(s2);
                g_gamelogbuffer.__ls(": ");
                g_gamelogbuffer.__ls(v51);
                g_gamelogbuffer.__ls(end);

                if(!v51 || v51 == 3)
                {
                    CNetMsg v54;

                    ConnLogoutMsg(v54, s2);

                    if(!gserver.Unk452128 && gserver.Unk16 && !gserver.Unk16->Unk361 && this->Unk16)
                        this->Unk16->WriteToOutput(v54);
                }
            }
            return;
        default:
            return;
    }
}
