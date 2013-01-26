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

void do_Chat(CPC *a1, CNetMsg &a2)
{
    char v15[900]; // [sp+20h] [bp-468h]@4
    char src; // [sp+3B8h] [bp-D0h]@2
    char dest; // [sp+41Ch] [bp-6Ch]@2
    char v20; // [sp+480h] [bp-8h]@2
    char v21; // [sp+487h] [bp-1h]@2

    if(a1->Unk140 >= 0)
    {
        a2.MoveFirst();

        *g_buf  = 0;
        *g_buf2 = 0;

        a2.__rs(v21);
        a2.__rs(v20);
        a2.__rs(dest);
        a2.__rs(src);
        a2.__rs(g_buf2);

        strcpy(g_buf, &dest);
        TrimString(g_buf);
        strcpy(&dest, g_buf);
        strcpy(g_buf, &src);
        TrimString(g_buf);
        strcpy(&src, g_buf);
        strcpy(g_buf, g_buf2);
        TrimString(g_buf);
        strcpy(g_buf2, g_buf);

        if(strlen(g_buf2))
        {
            if(a1->Unk475)
            {
                CNetMsg v17;

                *v15 = 0;
                memset(v15 + 1, 0, 899);

                switch(v21)
                {
                    case 0:
                        strcpy(v15, "SAY: ");
                        strcat(v15, a1->Unk8);
                        strcat(v15, ": ");
                        strcat(v15, g_buf2);
                        goto LABEL_12;
                    case 5:
                        strcpy(v15, "SHOUT: ");
                        strcat(v15, a1->Unk8);
                        strcat(v15, ": ");
                        strcat(v15, g_buf2);
                        goto LABEL_12;
                    case 3:
                        strcpy(v15, "TRADE: ");
                        strcat(v15, a1->Unk8);
                        strcat(v15, ": ");
                        strcat(v15, g_buf2);
                        goto LABEL_12;
                    case 4:
                        strcpy(v15, "WHISPER: ");
                        strcat(v15, a1->Unk8);
                        strcat(v15, " => ");
                        strcat(v15, &src);
                        strcat(v15, ": ");
                        strcat(v15, g_buf2);
                        goto LABEL_12;
                    case 1:
                        strcpy(v15, "PARTYCHAT: ");
                        strcat(v15, a1->Unk8);
                        strcat(v15, ": ");
                        strcat(v15, g_buf2);
                        goto LABEL_12;
                    case 2:
                        strcpy(v15, "GUILDCHAT: ");
                        strcat(v15, a1->Unk8);
                        strcat(v15, ": ");
                        strcat(v15, g_buf2);
LABEL_12:
                        if(strlen(v15))
                        {
                            SayMsg(v17, 6, 0, "", "", v15);
                            for(int i = 0; i <= 19; ++i)
                            {
                                if(gserver.Unk41128[i])
                                {
                                    if(gserver.Unk41128[i])
                                        gserver.Unk41128[i]->WriteToOutput(v17);
                                }
                            }

                            g_gamelogbuffer.__ls(init("CHAT MONITOR", a1->Unk8, a1->Unk768->Unk4));
                            g_gamelogbuffer.__ls(v15);
                            g_gamelogbuffer.__ls(end);
                        }
                        goto LABEL_21;
                    default:
                        break;
                }
            }
            else
            {
LABEL_21:
                if(gserver.Unk41248 - a1->Unk784 > 0)
                {
                    CNetMsg v15;
                    CNetMsg v16;

                    switch(v21)
                    {
                        case 0:
                            SayMsg(v15, 0, a1->Unk4, a1->Unk8, "", g_buf2);
                            a1->Unk412->SendToCell(v15, a1->Unk120.Unk16, a1->Unk140, a1->Unk144, 4);
                            break;
                        case 3:
                        case 5:
                            SayMsg(v15, v21, a1->Unk4, a1->Unk8, "", g_buf2);
                            a1->Unk412->SendToCell(v15, a1->Unk120.Unk16, a1->Unk140, a1->Unk144, 8);
                            break;
                        case 4:
                            MsgrWhisperReqMsg(v16, 0, gserver.Unk41004, gserver.Unk41008, a1->Unk4, a1->Unk8, &src, g_buf2);
                            if(!gserver.Unk452129 && gserver.Unk12 && !gserver.Unk12->Unk361 && gserver.Unk12)
                                gserver.Unk12->WriteToOutput(v16);
                            break;
                        case 1:
                            if(a1->IsParty())
                            {
                                for(int i = 0; i <= 7; ++i)
                                {
                                    if(a1->Unk1368->GetMember(i) && a1->Unk1368->GetMember(i)->Unk768)
                                        a1->Unk1368->GetMember(i)->Unk768->WriteToOutput(a2);
                                }
                            }
                            break;
                        case 2:
                            if(a1->Unk2368 && !gserver.Unk452130 && gserver.Unk20 && !gserver.Unk20->Unk361)
                            {
                                HelperGuildChat(v16, a1->Unk2368->guild()->index(), a1->Unk4, a1->Unk8, g_buf2);
                                if(gserver.Unk20)
                                    gserver.Unk20->WriteToOutput(v16);
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}
