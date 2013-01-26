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

char *gmCmd_567[] = {};
int gmLevel_568[] = {};
void (*gmFunc_569[])(CPC *,char *) = {};

void do_GM(CPC *a1, CNetMsg &a2)
{
    unsigned char dest; // [sp+4Fh] [bp-5h]@1
    int v20, v21;
    char *v22;

    a2.MoveFirst();

    a2.__rs(dest);

    if(dest)
    {
        if(dest == 1)
        {
            *buf = 0;
            a2.__rs(buf);
            *g_buf2 = 0;
            v22 = AnyOneArg(buf, g_buf2, true);

            for(int i = 0; i <= 34; ++i)
            {
                if(!strcmp(g_buf2, gmCmd_567[i]) && a1->Unk732 >= gmLevel_568[i])
                {
                    g_gamelogbuffer.__ls(init("GM COMMAND"));
                    g_gamelogbuffer.__ls(buf);
                    g_gamelogbuffer.__ls(delim);
                    g_gamelogbuffer.__ls(a1->Unk4);
                    g_gamelogbuffer.__ls(delim);
                    g_gamelogbuffer.__ls(a1->Unk8);
                    g_gamelogbuffer.__ls(end);

                    gmFunc_569[i](a1, v22);
                    break;
                }
            }

            if(strcmp(g_buf2, "pkcount"))
            {
                if(!strcmp(g_buf2, "pkpenalty"))
                {
                    AnyOneArg(v22, g_buf2, true);
                    if(strlen(g_buf2))
                    {
                        v21 = atoi(g_buf2);

                        if(v21 < -155)
                            v21 = -155;

                        if(v21 > 155)
                            v21 = 155;

                        a1->Unk1852 = v21;

                        CNetMsg v23;

                        CharStatusMsg(v23, a1, 0);
                        a1->Unk412->SendToCell(v23, a1, 0, 4);
                        a1->Unk473 = 1;
                    }
                }
            }
            else
            {
                AnyOneArg(v22, g_buf2, true);
                if(strlen(g_buf2))
                {
                    v20 = atoi(g_buf2);

                    if(v20 < -110)
                        v20 = -110;

                    if(v20 > 110)
                        v20 = 110;

                    a1->Unk1856 = v20;

                    CNetMsg v23;

                    CharStatusMsg(v23, a1, 0);
                    a1->Unk412->SendToCell(v23, a1, 0, 4);
                    a1->Unk473 = 1;
                }
            }
        }
    }
    else
    {
        CNetMsg v24;

        GMWhoAmIMsg(v24, a1);

        if(a1->Unk768)
            a1->Unk768->WriteToOutput(v24);

        g_gamelogbuffer.__ls(init("GM COMMAND"));
        g_gamelogbuffer.__ls("whoami");
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls(a1->Unk4);
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls(a1->Unk8);
        g_gamelogbuffer.__ls(delim);
        g_gamelogbuffer.__ls(a1->Unk408->Unk0);
        g_gamelogbuffer.__ls(end);
    }
}

void do_GMEcho(CPC *a1, char *a2)
{
    int v3; // [sp+24h] [bp-4h]@5
    char *v4; // [sp+34h] [bp+Ch]@4
    char *v5; // [sp+34h] [bp+Ch]@13

    *g_buf = 0;
    if(a2 && *a2)
    {
        v4 = AnyOneArg(a2, g_buf, true);
        if(strcmp(g_buf, "zone"))
        {
            if(strcmp(g_buf, "server"))
            {
                if(strcmp(g_buf, "all"))
                {
                    if(strcmp(g_buf, "subserver"))
                        return;

                    v3 = 3;
                }
                else
                {
                    v3 = 2;
                }
            }
            else
            {
                v3 = 1;
            }
        }
        else
        {
            v3 = 0;
        }

        v5 = SkipSpaces(v4);

        if(v5 && *v5)
        {
            CNetMsg v2;

            if(v3 == 1)
            {
                MsgrNoticeMsg(v2, -1, gserver.Unk41004, -1, -1, v5);
            }
            else
            {
                if(v3 > 1)
                {
                    if(v3 == 2)
                    {
                        MsgrNoticeMsg(v2, -1, -1, -1, -1, v5);
                    }
                    else
                    {
                        if(v3 == 3)
                            MsgrNoticeMsg(v2, -1, gserver.Unk41004, gserver.Unk41008, -1, v5);
                    }
                }
                else
                {
                    if(!v3)
                        MsgrNoticeMsg(v2, -1, gserver.Unk41004, gserver.Unk41008, a1->Unk408->Unk0, v5);
                }
            }

            if(!gserver.Unk452129 && gserver.Unk12 && !gserver.Unk12->Unk361)
            {
                if(gserver.Unk12)
                    gserver.Unk12->WriteToOutput(v2);
            }
        }
    }
}

void do_GMGoZone(CPC *a1, char *a2)
{
    int v9; // [sp+34h] [bp-14h]@20
    CQuest *v11; // [sp+3Ch] [bp-Ch]@10
    int v12; // [sp+40h] [bp-8h]@7
    uint32_t src; // [sp+44h] [bp-4h]@4
    char *v14; // [sp+54h] [bp+Ch]@4

    *g_buf = 0;
    if(a2)
    {
        if(*a2)
        {
            v14 = AnyOneArg(a2, g_buf, 0);
            src = atoi(g_buf);
            if(v14)
            {
                if(*v14)
                {
                    AnyOneArg(v14, g_buf, 0);
                    v12 = atoi(g_buf);
                    if(src != 6)
                    {
                        if(src != 2 && src != 5)
                        {
                            CNetMsg v7;

                            GoZoneMsg(v7, src, v12, "", 0);
                            do_GoZone(a1, v7);

                            return;
                        }

                        v11 = 0;

                        for(int i = 0; i < gserver.Unk452228.Unk4; ++i)
                        {
                            if(src == 2 && gserver.Unk452228.Unk0[i].Unk4 == 3)
                            {
                                v11 = gserver.Unk452228.Create(gserver.Unk452228.Unk0[i].Unk0);
                                break;
                            }

                            if(src == 5 && gserver.Unk452228.Unk0[i].Unk4 == 4)
                            {
                                v11 = gserver.Unk452228.Create(gserver.Unk452228.Unk0[i].Unk0);
                                break;
                            }
                        }

                        if(v11)
                        {
                            v9 = a1->Unk1900.AddQuest(v11);
                            if(v9 < 0)
                            {
                                delete v11;
                                return;
                            }

                            a1->Unk1900.Unk40[v9] = 1;
                            a1->Unk1900.Unk50[v9] = 0;

                            g_gamelogbuffer.__ls(init("QUEST START"));
                            g_gamelogbuffer.__ls(a1->Unk8);
                            g_gamelogbuffer.__ls(delim);
                            g_gamelogbuffer.__ls(v11->Unk0->Unk0);
                            g_gamelogbuffer.__ls(end);

                            CNetMsg v7;

                            QuestStartMsg(v7, a1->Unk1900.Unk0[v9]);

                            if(a1->Unk768)
                                a1->Unk768->WriteToOutput(v7);

                            CNetMsg v7_1;

                            GoZoneMsg(v7_1, src, v12, "", 0);
                            do_GoZone(a1, v7_1);

                            return;
                        }
                    }
                }
            }
        }
    }
}

void do_GMGoto(CPC *a1, char *a2)
{
    char v4; // [sp+1Bh] [bp-Dh]@10
    float v5; // [sp+1Ch] [bp-Ch]@7
    float v6; // [sp+24h] [bp-4h]@4
    char *v7; // [sp+34h] [bp+Ch]@4
    char *v8; // [sp+34h] [bp+Ch]@7

    *g_buf = 0;
    if(a2 && *a2)
    {
        v7 = AnyOneArg(a2, g_buf, 0);
        v6 = atof(g_buf);

        if(v7 && *v7)
        {
            v8 = AnyOneArg(v7, g_buf, 0);
            v5 = atof(g_buf);

            if(v8 && *v8)
            {
                AnyOneArg(v8, g_buf, 0);
                v4 = atoi(g_buf);

                if(v4 >= 0 && v4 <= 2 * (a1->Unk408->Unk28 - 1) && v6 >= 0.0 && v5 >= 0.0 && v6 < a1->Unk408->Unk32[v4/2].Unk0 && v5 < a1->Unk408->Unk32[v4/2].Unk4) // NOT SURE -> CHECK
                    GoTo(a1, v4, v6, v5, a1->Unk412->GetHeight(v4, v6, v5), a1->Unk120.Unk12);
            }
        }
    }
}

void do_GMItemDrop(CPC *a1, char *a2)
{
    COptionProto *j; // [sp+4Ch] [bp-2Ch]@33
    CItem *v28; // [sp+54h] [bp-24h]@15
    int *v29; // [sp+58h] [bp-20h]@1
    int *v30; // [sp+5Ch] [bp-1Ch]@1
    int v31; // [sp+60h] [bp-18h]@1
    long long v32; // [sp+64h] [bp-14h]@13
    int v33; // [sp+6Ch] [bp-Ch]@10
    int v34; // [sp+70h] [bp-8h]@7
    int v35; // [sp+74h] [bp-4h]@4
    char *v36; // [sp+84h] [bp+Ch]@4
    char *v37; // [sp+84h] [bp+Ch]@7
    char *v38; // [sp+84h] [bp+Ch]@10
    char *v39; // [sp+84h] [bp+Ch]@13
    char *v40; // [sp+84h] [bp+Ch]@18
    char *v41; // [sp+84h] [bp+Ch]@25

    v31 = 0;
    v30 = 0;
    v29 = 0;
    if(a2)
    {
        if(*a2)
        {
            v36 = AnyOneArg(a2, g_buf, 0);
            v35 = atoi(g_buf);
            if(v36)
            {
                if(*v36)
                {
                    v37 = AnyOneArg(v36, g_buf, 0);
                    v34 = atoi(g_buf);
                    if(v37)
                    {
                        if(*v37)
                        {
                            v38 = AnyOneArg(v37, g_buf, 0);
                            v33 = atoi(g_buf);
                            if(v38)
                            {
                                if(*v38)
                                {
                                    v39 = AnyOneArg(v38, g_buf, 0);
                                    v32 = atoll(g_buf);

                                    if(!v32)
                                        v32 = 1;

                                    v28 = a1->Unk412->DropItem(v35, a1, v34, v33, v32, 0);
                                    if(v28)
                                    {
                                        if(v39)
                                        {
                                            if(*v39)
                                            {
                                                v40 = AnyOneArg(v39, g_buf, 0);
                                                v31 = atoi(g_buf);
                                                if(v31 > 0 || v31 <= 5)
                                                {
                                                    v30 = (int *)malloc(4 * v31);
                                                    v29 = (int *)malloc(4 * v31);

                                                    for(int i = 0; i < v31; ++i)
                                                    {
                                                        if(!v40 || !*v40 || (v41 = AnyOneArg(v40, g_buf, 0), v30[i] = atoi(g_buf), !v41) || !*v41)
                                                            return;

                                                        v40 = AnyOneArg(v41, g_buf, 0);
                                                        v29[i] = atoi(g_buf);

                                                        if(v30[i] >= 0 && v30[i] <= 35 && v29[i] > 0 && v29[i] <= 6)
                                                        {
                                                            j = gserver.Unk452236.FindProto(v30[i]);
                                                            if(j)
                                                            {
                                                                v28->Unk68[i].Unk0  = j;
                                                                v28->Unk68[i].Unk4  = v30[i];
                                                                v28->Unk68[i].Unk8  = v29[i];
                                                                v28->Unk68[i].Unk12 = j->Unk8[v29[i]-1];
                                                                v28->Unk68[i].SetDBValue();

                                                                ++v28->Unk168;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }

                                        CNetMsg v25;

                                        ItemDropMsg(v25, a1, v28);
                                        a1->Unk412->SendToCell(v25, a1, 1, 4);

                                        g_gamelogbuffer.__ls(init("ITEM_LOAD", a1->Unk8));
                                        g_gamelogbuffer.__ls(v28->Unk28);
                                        g_gamelogbuffer.__ls(delim);
                                        g_gamelogbuffer.__ls(v28->Unk44);
                                        g_gamelogbuffer.__ls(delim);
                                        g_gamelogbuffer.__ls(v28->Unk36);
                                        g_gamelogbuffer.__ls(delim);
                                        g_gamelogbuffer.__ls(v28->Unk40);
                                        g_gamelogbuffer.__ls(delim);
                                        g_gamelogbuffer.__ls(v28->Count());
                                        g_gamelogbuffer.__ls(delim);
                                        g_gamelogbuffer.__ls(v28->Unk168);

                                        for(int j_1 = 0; j_1 < v31; j_1++)
                                        {
                                            g_gamelogbuffer.__ls(delim);
                                            g_gamelogbuffer.__ls(v30[j_1]);
                                            g_gamelogbuffer.__ls(delim);
                                            g_gamelogbuffer.__ls(v29[j_1]);
                                        }

                                        g_gamelogbuffer.__ls(end);

                                        if(v30 && v30)
                                            delete v30;

                                        if(v29 && v29)
                                            delete v29;
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

void do_GMCountPC(CPC *a1, char *a2)
{
    int src; // [sp+20h] [bp-8h]@1
    int v5; // [sp+24h] [bp-4h]@1

    v5 = 0;
    src = -1;

    if(a2 && *a2)
    {
        AnyOneArg(a2, g_buf, true);
        TrimString(g_buf);

        if(strlen(g_buf))
        {
            if(strcmp(g_buf, "all"))
            {
                v5 = 2;
                src = atoi(g_buf);
            }
            else
            {
                v5 = 1;
            }
        }
        else
        {
            v5 = 0;
        }
    }
    else
    {
        v5 = 0;
    }

    CNetMsg v3;

    if(v5 == 1)
    {
        MsgrPlayerCountReq(v3, -1, -1, a1->Unk4);
    }
    else
    {
        if(v5 > 1)
        {
            if(v5 != 2)
                return;

            MsgrPlayerCountReq(v3, src, -1, a1->Unk4);
        }
        else
        {
            if(v5)
                return;

            MsgrPlayerCountReq(v3, gserver.Unk41004, gserver.Unk41008, a1->Unk4);
        }
    }

    if(!gserver.Unk452129 && gserver.Unk12 && !gserver.Unk12->Unk361)
    {
        if(gserver.Unk12)
            gserver.Unk12->WriteToOutput(v3);
    }
}

void do_GMLoopCount(CPC *a1, char *a2)
{
    timeval tv;

    if(!gserver.Unk41116)
    {
        gserver.Unk41116 = 1;
        gserver.Unk41112 = 0;
        GetTimeofDay(&tv, 0);
        gserver.Unk41120 = a1->Unk768;
    }
}

void do_GMImmortal(CPC *a1, char *a2)
{
    char dest[100]; // [sp+24h] [bp-64h]@2

    if(a1->Unk474)
    {
        a1->Unk474 = 0;
        strcpy(dest, "Immortal Set Off");
    }
    else
    {
        a1->Unk474 = 1;
        DelAttackList(a1);
        strcpy(dest, "Immortal Set On");
    }

    CNetMsg v2;

    SayMsg(v2, 6, 0, "", "", dest);

    if(a1->Unk768)
        a1->Unk768->WriteToOutput(v2);
}

void do_GMShutdown(CPC *a1, char *a2)
{
    int v4; // [sp+24h] [bp-4h]@4
    char *sa; // [sp+34h] [bp+Ch]@4

    if(a2)
    {
        if(*a2)
        {
            sa = AnyOneArg(a2, g_buf, false);
            v4 = atoi(g_buf);

            TrimString(sa);

            if(gserver.Unk41084 == -1)
            {
                gserver.Unk41084 = 10 * v4;
                if(*sa)
                {
                    CNetMsg v3;

                    SayMsg(v3, 6, 0, "", "", sa);

                    for(int i = 0; i < gserver.Unk24.Unk32768; ++i)
                    {
                        if(gserver.Unk24.Unk0[i])
                        {
                            if(gserver.Unk24.Unk0[i]->Unk768)
                                gserver.Unk24.Unk0[i]->Unk768->WriteToOutput(v3);
                        }
                    }
                }
            }
        }
    }
}

void do_GMReboot(CPC *a1, char *a2)
{
    int v4; // [sp+24h] [bp-4h]@4
    char *sa; // [sp+34h] [bp+Ch]@4

    if(a2)
    {
        if(*a2)
        {
            sa = AnyOneArg(a2, g_buf, false);
            v4 = atoi(g_buf);

            TrimString(sa);

            if(gserver.Unk41080 == -1)
            {
                gserver.Unk41080 = 10 * v4;
                if(*sa)
                {
                    CNetMsg v3;

                    SayMsg(v3, 6, 0, "", "", sa);

                    for(int i = 0; i < gserver.Unk24.Unk32768; ++i)
                    {
                        if(gserver.Unk24.Unk0[i])
                        {
                            if(gserver.Unk24.Unk0[i]->Unk768)
                                gserver.Unk24.Unk0[i]->Unk768->WriteToOutput(v3);
                        }
                    }
                }
            }
        }
    }
}

void do_GMCountNPC(CPC *a1, char *a2)
{
    char dest[100]; // [sp+24h] [bp-64h]@4

    for(int i = 0; i < gserver.Unk452192; ++i)
    {
        if(gserver.Unk452196[i].Unk40 <= 1)
        {
            strcpy(dest, "Zone :");
            IntCat(dest, gserver.Unk452196[i].Unk0, 1);
            strcat(dest, " First :");
            IntCat(dest, gserver.Unk452196[i].Unk36->Unk32.Unk8, 1);
            strcat(dest, " Now :");
            IntCat(dest, gserver.Unk452196[i].Unk36->Unk52, 1);
            strcat(dest, " ShopCount :");
            IntCat(dest, gserver.Unk452196[i].Unk60, 1);

            CNetMsg v2;

            SayMsg(v2, 6, 0, "", "", dest);

            if(a1->Unk768)
                a1->Unk768->WriteToOutput(v2);
        }
    }
}

void do_GMVisible(CPC *a1, char *a2)
{
    a1->SetVisible();

    CNetMsg v2;

    if(a1->Unk420)
        SayMsg(v2, 6, 0, "", "", "Visible: ON");
    else
        SayMsg(v2, 6, 0, "", "", "Visible: OFF");

    if(a1->Unk768)
        a1->Unk768->WriteToOutput(v2);
}

void do_GMGoPC(CPC *a1, char *a2)
{
    CPC *v5; // [sp+20h] [bp-8h]@7

    if(a2 && *a2)
    {
        TrimString(a2);
        if(strcmp(a2, a1->Unk8))
        {
            for(int i = 0; i < gserver.Unk24.Unk32768; ++i)
            {
                v5 = gserver.Unk24.Unk0[i]; // gserver.Unk20[i + 1]
                if(v5 && !strcmp(v5->Unk8, a2))
                {
                    if(v5->Unk408 == a1->Unk408)
                    {
                        GoTo(a1, v5->Unk120.Unk16, v5->Unk120.Unk0, v5->Unk120.Unk4, a1->Unk412->GetHeight(v5->Unk120.Unk16, v5->Unk120.Unk0, v5->Unk120.Unk4), a1->Unk120.Unk12);
                    }
                    else
                    {
                        if(v5->Unk408->Unk0 != 2 && v5->Unk408->Unk0 != 5 && v5->Unk408->Unk0 != 6)
                        {
                            GoZone(a1, v5->Unk408->Unk0, v5->Unk120.Unk16, v5->Unk120.Unk0, v5->Unk120.Unk4);
                        }
                    }

                    return;
                }
            }

            CNetMsg v4;

            SayMsg(v4, 6, 0, "", "", "Not Found the PC");

            if(a1->Unk768)
                a1->Unk768->WriteToOutput(v4);
        }
    }
}

void do_GMGoNPC(CPC *a1, char *a2)
{
    float v10; // [sp+28h] [bp-40h]@31
    CNPC *v11; // [sp+2Ch] [bp-3Ch]@14
    CNPC *v12; // [sp+30h] [bp-38h]@27
    int v14; // [sp+38h] [bp-30h]@14
    float v15; // [sp+3Ch] [bp-2Ch]@14
    int v16; // [sp+40h] [bp-28h]@12
    int v17; // [sp+44h] [bp-24h]@12
    int v18; // [sp+48h] [bp-20h]@12
    int v19; // [sp+4Ch] [bp-1Ch]@12
    CArea *v22; // [sp+58h] [bp-10h]@12
    int v23; // [sp+5Ch] [bp-Ch]@10
    char v24; // [sp+63h] [bp-5h]@5
    char *s; // [sp+64h] [bp-4h]@4

    if(a2)
    {
        if(*a2)
        {
            TrimString(a2);
            s = a2;

            if(strlen(a2))
            {
                v24 = 0;
                while(*s)
                {
                    if(!(*(short *)(_ctype_b + 2 * *s) & 0x800))
                    {
                        v24 = 1;
                        break;
                    }
                    ++s;
                }

                v23 = -1;
                if(!v24)
                    v23 = atoi(a2);

                v22 = a1->Unk412;
                v19 = 0;
                v18 = v22->Unk12 - 1;
                v17 = 0;
                v16 = v22->Unk16 - 1;
                v14 = (v22->Unk16 < v22->Unk12) ? v22->Unk12 : v22->Unk16;
                v15 = v14 * 12.0;
                v11 = 0;

                CNetMsg v9;

                for(int i = v19; i <= v18; ++i)
                {
                    if(i >= 0 && i < v22->Unk12)
                    {
                        for(int j = v17; j <= v16; ++j)
                        {
                            if(j >= 0 && j < v22->Unk16)
                            {
                                for(CCharacter *k = v22->Unk28[i][j].Unk0; k; k = k->Unk404)
                                {
                                    if(k->Unk0 == 1)
                                    {
                                        if((v12 = (CNPC *)k, v23 == -1) && !strcmp(v12->Unk8, a2) || v23 != -1 && v12->Unk468 == v23)
                                        {
                                            v10 = GetDistance(a1, v12);

                                            //UNDEF(v3);
                                            //v4 = v10 < (long double)v15;
                                            //v5 = 0;
                                            //v6 = v10 == v15;

                                            //if((HIBYTE(v3) & 0x45) == 1)
                                            if(v15 > v10)
                                            {
                                                v15 = v10;
                                                v11 = v12;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                if(v11)
                {
                    GoTo(a1, v11->Unk120.Unk16, v11->Unk120.Unk0, v11->Unk120.Unk4, a1->Unk412->GetHeight(v11->Unk120.Unk16, v11->Unk120.Unk0, v11->Unk120.Unk4), a1->Unk120.Unk12);
                }
                else
                {
                    SayMsg(v9, 6, 0, "", "", "Not Found the NPC");
                    if(a1->Unk768)
                        a1->Unk768->WriteToOutput(v9);
                }
            }
        }
    }
}

void do_GMLevelUP(CPC *a1, char *a2)
{
    int v2; // [sp+14h] [bp-4h]@5

    if(a2 && *a2)
    {
        TrimString(a2);
        if(strlen(a2))
        {
            v2 = atoi(a2);

            if(v2 > 0 && v2 <= 80)
            {
                a1->Unk64 = 0;
                a1->Unk60 = v2;
                a1->LevelUp(true);
                a1->CalcStatus(true);
            }
        }
    }
}

void do_GMKICK(CPC *a1, char *a2)
{
    CPC *v4; // [sp+34h] [bp-4h]@5

    if(a2)
    {
        if(*a2)
        {
            TrimString(a2);
            if(strcmp(a2, a1->Unk8))
            {
                v4 = gserver.Unk24.Find(a2);
                if(v4)
                {
                    CNetMsg v3;

                    MsgrLogoutReqMsg(v3, -1, gserver.Unk41004, gserver.Unk41008, -1, v4->Unk768->Unk4);

                    if(!gserver.Unk452129 && gserver.Unk12 && !gserver.Unk12->Unk361 && gserver.Unk12)
                        gserver.Unk12->WriteToOutput(v3);

                    strcpy(g_buf, "Sending Kick: ");
                    strcat(g_buf, a2);

                    CNetMsg v2;

                    SayMsg(v2, 6, 0, "", "", g_buf);
                    if(a1->Unk768)
                        a1->Unk768->WriteToOutput(v2);
                }
                else
                {
                    strcpy(g_buf, "Not Found PC: ");
                    strcat(g_buf, a2);

                    CNetMsg v2;

                    SayMsg(v2, 6, 0, "", "", g_buf);
                    if(a1->Unk768)
                        a1->Unk768->WriteToOutput(v2);
                }
            }
        }
    }
}

void do_GMComon(CPC *a1, char *a2)
{
    CPC *v5; // [sp+20h] [bp-8h]@7

    if(a2 && *a2)
    {
        TrimString(a2);
        if(strcmp(a2, a1->Unk8))
        {
            for(int i = 0; i < gserver.Unk24.Unk32768; ++i)
            {
                v5 = gserver.Unk24.Unk0[i];
                if(v5 && !strcmp(v5->Unk8, a2))
                {
                    if(v5->Unk408 == a1->Unk408)
                    {
                        GoTo(v5, a1->Unk120.Unk12, a1->Unk120.Unk0, a1->Unk120.Unk4, v5->Unk412->GetHeight(a1->Unk120.Unk12, a1->Unk120.Unk0, a1->Unk120.Unk4), v5->Unk120.Unk12);
                    }
                    else
                    {
                        if(a1->Unk408->Unk0 != 2 && a1->Unk408->Unk0 != 5 && a1->Unk408->Unk0 != 6)
                            GoZone(v5, a1->Unk408->Unk0, a1->Unk120.Unk12, a1->Unk120.Unk0, a1->Unk120.Unk4);
                    }

                    return;
                }
            }

            CNetMsg v4;

            SayMsg(v4, 6, 0, "", "", "Not Found the PC");
            if(a1->Unk768)
                a1->Unk768->WriteToOutput(v4);
        }
    }
}

void do_GMSummon(CPC *a1, char *a2)
{
    int v3; // [sp+28h] [bp-20h]@21
    int v4; // [sp+2Ch] [bp-1Ch]@21
    CNPC *v6; // [sp+34h] [bp-14h]@12
    int v8; // [sp+3Ch] [bp-Ch]@10
    char v9; // [sp+43h] [bp-5h]@5
    char *s; // [sp+44h] [bp-4h]@4

    if(a2)
    {
        if(*a2)
        {
            TrimString(a2);
            s = a2;
            if(strlen(a2))
            {
                v9 = 0;
                while(*s)
                {
                    if(!(*(short *)(_ctype_b + 2 * *s) & 0x800))
                    {
                        v9 = 1;
                        break;
                    }
                    ++s;
                }

                v8 = -1;

                if(!v9)
                    v8 = atoi(a2);

                v6 = 0;

                if(v9)
                {
                    for(int i = 0; i < gserver.Unk452200.Unk4; ++i)
                    {
                        if(!strcmp(gserver.Unk452200.Unk0[i].Unk4, a2))
                        {
                            v6 = gserver.Unk452200.Create(gserver.Unk452200.Unk0[i].Unk0);
                            break;
                        }
                    }
                }
                else
                {
                    v6 = gserver.Unk452200.Create(v8);
                }

                if(v6)
                {
                    v6->Unk120.Unk0  = a1->Unk120.Unk0 + 2.0;
                    v6->Unk120.Unk16 = a1->Unk120.Unk16;
                    v6->Unk120.Unk4  = a1->Unk120.Unk4 + 2.0;
                    v6->Unk120.Unk12 = GetRandom(0, 62831) / 10000;

                    v6->Unk476 = v6->Unk120.Unk0;
                    v6->Unk480 = v6->Unk120.Unk16;
                    v6->Unk484 = v6->Unk120.Unk4;
                    v6->Unk752 = 0;

                    a1->Unk412->AddNPC(v6);
                    a1->Unk412->PointToCellNum(v6->Unk120.Unk0, v6->Unk120.Unk4, &v4, &v3);
                    a1->Unk412->CharToCell(v6, v6->Unk120.Unk16, v4, v3);

                    CNetMsg v2;

                    AppearMsg(v2, v6, 1);
                    a1->Unk412->SendToCell(v2, v6->Unk120.Unk16, v4, v3, 4);
                }
            }
        }
    }
}

void do_GMSilence(CPC *a1, char *a2)
{
    CPC *v2; // [sp+Ch] [bp-Ch]@7
    int v4; // [sp+14h] [bp-4h]@9
    char *v5; // [sp+24h] [bp+Ch]@4

    if(a2)
    {
        if(*a2)
        {
            v5 = AnyOneArg(a2, g_buf, 0);
            if(strlen(g_buf) > 3)
            {
                for(int i = 0; i < gserver.Unk24.Unk32768; ++i)
                {
                    v2 = gserver.Unk24.Unk0[i];
                    if(v2 && !strcmp(v2->Unk8, g_buf))
                    {
                        v5 = AnyOneArg(v5, g_buf, 0);
                        v4 = atoi(g_buf);

                        if(v4 <= 0)
                            return;

                        v2->Unk784 = 10 * v4 + gserver.Unk41248;
                    }
                }
            }
        }
    }
}

void do_GMWhereAmI(CPC *a1, char *a2)
{
    char dest; // [sp+24h] [bp-64h]@1

    strcpy(&dest, "Server No :");
    IntCat(&dest, gserver.Unk41004, 1);
    strcpy(&dest, "SubServer No :");
    IntCat(&dest, gserver.Unk41008, 1);
    strcpy(&dest, "Zone No :");
    IntCat(&dest, a1->Unk408->Unk0, 1);
    strcat(&dest, " Area No :");
    IntCat(&dest, a1->Unk412->Unk8, 1);

    CNetMsg v2;

    SayMsg(v2, 6, 0, "", "", &dest);
    if(a1->Unk768)
        a1->Unk768->WriteToOutput(v2);
}

void do_GMQuestComplete(CPC *a1, char *a2)
{
    int v10; // [sp+34h] [bp-4h]@5

    if(a2 && *a2)
    {
        TrimString(a2);
        if(strlen(a2))
        {
            v10 = atoi(a2);
            for(int i = 0; i <= 9; ++i)
            {
                if(a1->Unk1900.Unk0[i] && a1->Unk1900.Unk40[i] && !a1->Unk1900.Unk50[i] && a1->Unk1900.Unk0[i]->Unk0->Unk0 == v10)
                {
                    g_gamelogbuffer.__ls(init("QUEST COMPLETE"));
                    g_gamelogbuffer.__ls(a1->Unk8);
                    g_gamelogbuffer.__ls(delim);
                    g_gamelogbuffer.__ls(a1->Unk1900.Unk0[i]->Unk0->Unk0);
                    g_gamelogbuffer.__ls(end);

                    CNetMsg v7;

                    QuestCompleteMsg(v7, a1->Unk1900.Unk0[i]);
                    if(a1->Unk768)
                        a1->Unk768->WriteToOutput(v7);

                    a1->Unk1900.Unk50[i] = 1;
                    return;
                }
            }
        }
    }
}

void do_GMStatPoint(CPC *a1, char *a2)
{
    short v2; // [sp+8h] [bp-20h]@19
    short v3; // [sp+Ah] [bp-1Eh]@16
    short v4; // [sp+Ch] [bp-1Ch]@10
    short v4_2;
    short v6; // [sp+26h] [bp-2h]@4
    char *v7; // [sp+34h] [bp+Ch]@4
    char *v8; // [sp+34h] [bp+Ch]@10
    char *v9; // [sp+34h] [bp+Ch]@13
    char *v10; // [sp+34h] [bp+Ch]@16

    if(a2)
    {
        if(*a2)
        {
            v7 = AnyOneArg(a2, g_buf, 0);
            v6 = atoi(g_buf);

            if(v6 >= 0)
            {
                a1->Unk740 = v6;

                CNetMsg v5;

                StatPointRemainMsg(v5, a1);

                if(a1->Unk768)
                    a1->Unk768->WriteToOutput(v5);

                if(v7 && *v7)
                {
                    v8 = AnyOneArg(v7, g_buf, 0);
                    v4_2 = atoi(g_buf);

                    if(v8 && *v8)
                    {
                        v9 = AnyOneArg(v8, g_buf, 0);
                        v4 = atoi(g_buf);

                        if(v9 && *v9)
                        {
                            v10 = AnyOneArg(v9, g_buf, 0);
                            v3 = atoi(g_buf);

                            if(v10 && *v10)
                            {
                                AnyOneArg(v10, g_buf, 0);
                                v2 = atoi(g_buf);

                                if(v4 >= 0 && v4_2 >= 0 && v3 >= 0 && v2 >= 0)
                                {
                                    a1->Unk742 = v4_2;
                                    a1->Unk744 = v4;
                                    a1->Unk746 = v3;
                                    a1->Unk748 = v2;

                                    a1->InitStat();
                                    a1->CalcStatus(true);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void do_GMSkillPoint(CPC *a1, char *a2)
{
    int v2; // [sp+14h] [bp-4h]@4

    if(a2 && *a2)
    {
        v2 = atoi(a2);
        if(v2 > 0)
        {
            if(v2 > 2000000000)
                v2 = 2000000000;

            a1->Unk72 = 10000 * v2;
            a1->Unk473 = 1;
        }
    }
}

void do_GMSetRegenSec(CPC *a1, char *a2)
{
    int i; // [sp+Ch] [bp-Ch]@7
    int v3; // [sp+10h] [bp-8h]@4
    int v4; // [sp+14h] [bp-4h]@4
    char *v5; // [sp+24h] [bp+Ch]@4

    if(a2 && *a2)
    {
        v5 = AnyOneArg(a2, g_buf, 0);
        v4 = atoi(g_buf);
        AnyOneArg(v5, g_buf, 0);
        v3 = atoi(g_buf);

        if(v4 > 0 && v3 > 0)
        {
            for(i = 0; i < a1->Unk412->Unk32.Unk8; ++i)
            {
                if(a1->Unk412->Unk32.Unk4[i].Unk0 == v4)
                    a1->Unk412->Unk32.Unk4[i].Unk24 = v3;
            }
        }
    }
}

void do_GMNPCRegen(CPC *a1, char *a2)
{
    int v3; // [sp+14h] [bp-4h]@4

    if(a2 && *a2)
    {
        AnyOneArg(a2, g_buf, 0);
        v3 = atoi(g_buf);

        if(v3 > 0)
        {
            for(int i = 0; i < a1->Unk412->Unk32.Unk8; ++i)
            {
                if(a1->Unk412->Unk32.Unk4[i].Unk0 == v3)
                {
                    if(!a1->Unk412->Unk32.Unk4[i].Unk32)
                        a1->Unk412->Unk32.Unk4[i].Unk24 = 0;
                }
            }
        }
    }
}

void do_GMKillNPC(CPC *a1, char *a2)
{
    CCharacter *v3; // [sp+20h] [bp-38h]@15
    CCharacter *v4; // [sp+24h] [bp-34h]@16
    int v8; // [sp+44h] [bp-14h]@5
    int v9; // [sp+48h] [bp-10h]@5
    int v10; // [sp+4Ch] [bp-Ch]@5
    int v11; // [sp+50h] [bp-8h]@5
    int v12; // [sp+54h] [bp-4h]@4

    if(a2 && *a2)
    {
        AnyOneArg(a2, g_buf, 0);
        v12 = atoi(g_buf);
        if(v12 > 0)
        {
            v11 = a1->Unk140 - 2;
            v10 = a1->Unk140 + 2;
            v9 = a1->Unk144 - 2;
            v8 = a1->Unk144 + 2;

            CNetMsg v5;

            for(int i = v11; i <= v10; ++i)
            {
                if(i >= 0 && i < a1->Unk412->Unk12)
                {
                    for(int j = v9; j <= v8; ++j)
                    {
                        if(j >= 0 && j < a1->Unk412->Unk16)
                        {
                            v3 = a1->Unk412->Unk28[i][j].Unk0;
                            while(1)
                            {
                                v4 = v3;
                                if(!v3)
                                    break;

                                v3 = v3->Unk404;
                                if(v4->Unk0 == 1 && v12 > GetDistance(a1, v4))
                                {
                                    DamageMsg(v5, a1, v4, 0, -1, v4->Unk78, 4);
                                    v4->Unk412->SendToCell(v5, v4, 0, 4);
                                    v4->Unk76 = 0;

                                    if(v4->Unk76 <= 0)
                                    {
                                        DelAttackList(v4);
                                        a1->Unk412->CharFromCell(v4);
                                        a1->Unk412->DelNPC((CNPC *)v4);
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

void do_GMExpUp(CPC *a1, char *a2)
{
    double v6; // [sp+20h] [bp-8h]@4

    if(a2 && *a2)
    {
        v6 = atof(a2);
        if(v6 >= 0.0)
        {
            //UNDEF(v2);
            //v3 = 100.0 < v6;
            //v4 = 0;
            //v5 = 100.0 == v6;
            //if((HIBYTE(v2) & 0x45) != 1)

            if(v6 <= 100.0) // <= or > ? -> CHECK
            {
                a1->Unk64 = GetLevelupExp(a1->Unk60) * v6 / 100.0;
                a1->Unk473 = 1;
            }
        }
    }
}

void do_GMBloodPoint(CPC *a1, char *a2)
{
    int v4; // [sp+24h] [bp-4h]@3

    if(a2 && *a2)
    {
        v4 = atoi(a2);
        if(v4 >= 0 && v4 <= 5000)
        {
            a1->Unk752 = v4;
            strcpy(g_buf, "Blood points: ");
            IntCat(g_buf, a1->Unk752, 1);

            CNetMsg v3;

            SayMsg(v3, 6, 0, "", "", g_buf);
            if(a1->Unk768)
                a1->Unk768->WriteToOutput(v3);

            if(a1->Unk752 <= 0)
            {
                a1->Unk752 = 5000;
                a1->SettingItemOption();
            }
        }
    }
    else
    {
        strcpy(g_buf, "Blood points: ");
        IntCat(g_buf, a1->Unk752, 1);

        CNetMsg v3;

        SayMsg(v3, 6, 0, "", "", g_buf);
        if(a1->Unk768)
            a1->Unk768->WriteToOutput(v3);
    }
}

void do_GMEndGame(CPC *a1, char *a2)
{
    int v3; // [sp+24h] [bp-4h]@4
    char *sa; // [sp+34h] [bp+Ch]@4

    if(!a2 || !*a2)
        return;

    sa = AnyOneArg(a2, g_buf, false);
    v3 = atoi(g_buf);
    TrimString(sa);

    if(gserver.Unk41088 != -1)
        return;

    gserver.Unk41088 = 10 * v3;

    if(!*sa)
        return;

    CNetMsg v2;

    MsgrNoticeMsg(v2, -1, -1, -1, -1, sa);

    if(!gserver.Unk452129 && gserver.Unk12 && !gserver.Unk12->Unk361)
    {
        if(gserver.Unk12)
            gserver.Unk12->WriteToOutput(v2);
    }
}

void do_GMObserve(CPC *a1, char *a2)
{
    CNetMsg v2;

    if(!gserver.Unk41124)
    {
        gserver.Unk41124 = a1->Unk768;
        return;
    }

    if(gserver.Unk41124 != a1->Unk768)
    {
        strcpy(g_buf, "Change Observer: ");

        if(gserver.Unk41124->Unk372)
            strcat(g_buf, gserver.Unk41124->Unk372->Unk8);
        else
            strcat(g_buf, gserver.Unk41124->Unk4);

        strcat(g_buf, " -> ");
        strcat(g_buf, a1->Unk8);

        SayMsg(v2, 6, 0, "", "", g_buf);

        if(gserver.Unk41124)
            gserver.Unk41124->WriteToOutput(v2);

        if(a1->Unk768)
            a1->Unk768->WriteToOutput(v2);

        gserver.Unk41124 = a1->Unk768;
        return;
    }

    SayMsg(v2, 6, 0, "", "", "Observe Reset");

    if(a1->Unk768)
        a1->Unk768->WriteToOutput(v2);

    gserver.Unk41124 = 0;
}

void do_GMChatMonitor(CPC *a1, char *a2)
{
    CPC *v2; // [sp+Ch] [bp-1Ch]@25
    int i; // [sp+24h] [bp-4h]@1
    char *v5; // [sp+34h] [bp+Ch]@24

    for(i = 0; i <= 19; ++i)
    {
        if(gserver.Unk41128[i] == a1->Unk768)
        {
            if(!a2 || !*a2)
            {
                gserver.Unk41128[i] = 0;
                CNetMsg v3;

                SayMsg(v3, 6, 0, "", "", "Monitoring Finished!!!");
                if(a1->Unk768)
                    a1->Unk768->WriteToOutput(v3);

                return;
            }
            break;
        }
    }

    if(i == 20)
    {
        for(i = 0; i <= 19; ++i)
        {
            if(!gserver.Unk41128[i])
            {
                gserver.Unk41128[i] = a1->Unk768;
                break;
            }
        }
    }

    if(i == 20)
    {
        CNetMsg v3;

        SayMsg(v3, 6, 0, "", "", "Cannot More Monitor!!!");
        if(a1->Unk768)
            a1->Unk768->WriteToOutput(v3);
    }

    if(a2)
    {
        if(*a2)
        {
            *g_buf = 0;
            v5 = AnyOneArg(a2, g_buf, 0);
            TrimString(g_buf);

            if(strlen(g_buf))
            {
                v2 = gserver.Unk24.Find(g_buf);
                if(v2)
                {
                    *g_buf = 0;
                    AnyOneArg(v5, g_buf, 1);
                    TrimString(g_buf);

                    v2->Unk475 = 1;
                    v2->Unk475 = (strcmp(g_buf, "off")) ? 1 : 0;

                    CNetMsg v3;

                    strcpy(g_buf, "SET CHAT MONITOR: ");
                    strcat(g_buf, v2->Unk8);
                    SayMsg(v3, 6, 0, "", "", g_buf);

                    if(a1->Unk768)
                        a1->Unk768->WriteToOutput(v3);
                }
                else
                {
                    CNetMsg v3;

                    SayMsg(v3, 6, 0, "", "", "Not Found the PC");
                    if(a1->Unk768)
                        a1->Unk768->WriteToOutput(v3);
                }
            }
        }
    }
}

void do_GMDoubleEvent(CPC *a1, char *a2)
{
    ;
}

void do_GMDoubleExpEvent(CPC *a1, char *a2)
{
    ;
}

void _do_GMLattoEvent(CPC *a1, char *a2)
{
    ;
}

void do_GMNewYearEvent(CPC *a1, char *a2)
{
    ;
}

void do_GMValentineEvent(CPC *a1, char *a2)
{
    ;
}
