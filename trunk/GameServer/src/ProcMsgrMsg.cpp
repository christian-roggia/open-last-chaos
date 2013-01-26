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

void CServer::ProcessMessengerMessage(CNetMsg &a2)
{
    int v49; // eax@220
    float v50; // [sp+30h] [bp-A4h]@100
    float dest; // [sp+34h] [bp-A0h]@100
    int k; // [sp+38h] [bp-9Ch]@68
    int v53; // [sp+3Ch] [bp-98h]@67
    int v54; // [sp+40h] [bp-94h]@65
    int l; // [sp+44h] [bp-90h]@65
    int v56; // [sp+48h] [bp-8Ch]@65
    void *s; // [sp+4Ch] [bp-88h]@65
    int v58; // [sp+50h] [bp-84h]@65
    char v59; // [sp+57h] [bp-7Dh]@56
    char s2[52]; // [sp+58h] [bp-7Ch]@56
    int v61; // [sp+8Ch] [bp-48h]@39
    int v62; // [sp+A0h] [bp-34h]@30
    int j; // [sp+A4h] [bp-30h]@30
    //int v64; // [sp+A8h] [bp-2Ch]@15
    int i; // [sp+BCh] [bp-18h]@4
    unsigned char v66; // [sp+C3h] [bp-11h]@4
    int v67; // [sp+C4h] [bp-10h]@4
    int v68; // [sp+C8h] [bp-Ch]@4
    int v69; // [sp+CCh] [bp-8h]@4
    int src; // [sp+D0h] [bp-4h]@4

    a2.MoveFirst();

    if(a2.MsgType == 101)
    {
        a2.__rs(src);
        a2.__rs(v69);
        a2.__rs(v68);
        a2.__rs(v67);
        a2.__rs(v66);

        i = gserver.FindZone(v67);
        if(v69 == -1 || v69 == gserver.Unk41004 && (v68 == -1 || v68 == gserver.Unk41008))
        {
            if(v67 == -1 || i != -1 && gserver.Unk452196[i].Unk0 == v67)
            {
                switch(v66)
                {
                    case 0xD:
                        if(this->Unk41124)
                        {
                            a2.__rs(g_buf);

                            CNetMsg v64;

                            SayMsg(v64, 6, 0, "", "", g_buf);

                            if(this->Unk41124)
                                this->Unk41124->WriteToOutput(v64);
                        }
                        break;
                    case 0xC:
                        CNetMsg v64;

                        ConnRebootReqMsg(v64);

                        if(!gserver.Unk452128 && gserver.Unk16 && !gserver.Unk16->Unk361 && this->Unk16)
                            this->Unk16->WriteToOutput(v64);

                        HelperShutdownMsg(v64);

                        if(!gserver.Unk452130 && gserver.Unk20 && !gserver.Unk20->Unk361 && this->Unk20)
                            this->Unk20->WriteToOutput(v64);
                        break;
                    case 0:
                        *g_buf3 = 0;
                        *g_buf2 = 0;
                        *g_buf  = 0;

                        a2.__rs(j);
                        a2.__rs(g_buf);
                        a2.__rs(g_buf2);
                        a2.__rs(g_buf3);

                        CPC *v62 = gserver.Unk24.Find(g_buf2);
                        if(v62)
                        {
                            CNetMsg v64;

                            ChatWhisperMsg(v64, j, g_buf, v62->Unk8, g_buf3);

                            if(v62->Unk768)
                                v62->Unk768->WriteToOutput(v64);

                            CNetMsg v61;

                            MsgrRepWhisperRepMsg(v61, src, v69, v68, v67, j, g_buf, v62->Unk8, g_buf3);

                            if(!gserver.Unk452129 && gserver.Unk12 && !gserver.Unk12->Unk361 && gserver.Unk12)
                                gserver.Unk12->WriteToOutput(v61);
                        }
                        else
                        {
                            CNetMsg v64;

                            MsgrRepWhisperNotFoundMsg(v64, src, v69, v68, v67, j, g_buf);

                            if(!gserver.Unk452129 && gserver.Unk12 && !gserver.Unk12->Unk361 && gserver.Unk12)
                                gserver.Unk12->WriteToOutput(v64);
                        }
                        break;
                    case 5:
                        *g_buf = 0;

                        a2.__rs(g_buf);

                        CNetMsg v61;

                        SayMsg(v61, 6, 0, "", "", g_buf);

                        for(i = 0; i < gserver.Unk24.Unk32768; ++i)
                        {
                            if(gserver.Unk24.Unk0[i] && gserver.Unk24.Unk0[i]->Unk408 && (gserver.Unk24.Unk0[i]->Unk408->Unk0 == v67 || v67 == -1) && gserver.Unk24.Unk0[i]->Unk768)
                                gserver.Unk24.Unk0[i]->Unk768->WriteToOutput(v61);
                        }
                        break;
                    case 6:
                        CNetMsg v61;

                        a2.__rs(s2);
                        v59 = 1;
                        v62 = gserver.FindConnectIdName(s2, 0);

                        if(v62)
                        {
                            this->CloseSocket(v62);
                            break;
                        }

                        if(!gserver.Unk452129 && gserver.Unk12 && !gserver.Unk12->Unk361)
                        {
                            v59 = 0;
                            if(src != -1)
                            {
                                MsgrLogoutRepMsg(v61, src, v69, v68, v67, v59, &s2);

                                if(this->Unk12)
                                    this->Unk12->WriteToOutput(v61);
                            }
                        }
                        break;
                    case 7:
                        a2.__rs(v62);

                        v58 = 0;

                        int *s   = (int *)malloc(4 * this->Unk452192);
                        int *v56 = (int *)malloc(4 * this->Unk452192);
                        int *l   = (int *)malloc(4 * this->Unk452192);
                        int *v54 = (int *)malloc(4 * this->Unk452192);

                        memset(s,   0, 4 * this->Unk452192);
                        memset(v56, 0, 4 * this->Unk452192);
                        memset(l,   0, 4 * this->Unk452192);
                        memset(v54, 0, 4 * this->Unk452192);

                        for(j = 0; j < this->Unk32792; ++j)
                        {
                            CPC *v53 = this->Unk24.Unk0[j];
                            if(v53)
                            {
                                ++s[0x38E38E39 * (v53->Unk408 - this->Unk452196) >> 3]; // CHECK
                                v59 = 0;

                                for(CAttackChar *k = v53->Unk396; k; k = k->Unk20)
                                {
                                    if(((CNPC *)k->Unk16)->Unk464->Unk92 & 0x400 || ((CNPC *)k->Unk16)->Unk464->Unk92 & 0x400 || ((CNPC *)k->Unk16)->Unk464->Unk92 & 0x400) // NO-SENSE -> CHECK
                                    {
                                        v59 = 1;
                                        break;
                                    }
                                }

                                if(v59)
                                {
                                    ++v56[0x38E38E39 * (v53->Unk408 - this->Unk452196) >> 3]; // CHECK
                                }
                                else
                                {
                                    if(v53->Unk1328)
                                    {
                                        ++l[0x38E38E39 * (v53->Unk408 - this->Unk452196) >> 3];
                                    }
                                    else
                                    {
                                        ++v54[0x38E38E39 * (v53->Unk408 - this->Unk452196) >> 3]; // CHECK
                                    }
                                }
                            }
                        }

                        for(j = 0; j < this->Unk452192; ++j)
                        {
                            if(s[j])
                                ++v58;
                        }

                        CNetMsg v61;

                        MsgrPlayerCountRep(v61, src, v69, v68, v67, v62, v58, s, v56, l, v54);

                        if(!gserver.Unk452129 && gserver.Unk12 && !gserver.Unk12->Unk361 && this->Unk12)
                            this->Unk12->WriteToOutput(v61);

                        if(s)
                            delete s;
                        s = 0;

                        if(v56)
                            delete v56;
                        v56 = 0;

                        if(l)
                            delete l;
                        l = 0;

                        if(v54)
                            delete v54;
                        v54 = 0;
                        break;
                    case 10:
                        a2.__rs(k);
                        a2.__rs(v53);
                        a2.__rs(v54);
                        a2.__rs(l);
                        a2.__rs(dest);
                        a2.__rs(v50);

                        v56 = this->FindZone(v54);
                        if(v56 != -1)
                        {
                            CZone *s = &this->Unk452196[v56];
                            CNetMsg v61;

                            if(s->Unk40 <= 1) // NOT SO SURE, CHECK
                            {
                                MsgrGoZoneRepMsg(v61, src, s->Unk0, 1, k, v53, v54);
                            }
                            else
                            {
                                v62 = s->FindEmptyArea();
                                if(v62 == -1)
                                    MsgrGoZoneRepMsg(v61, src, s->Unk0, 0, k, v53, v54);
                                else
                                    MsgrGoZoneRepMsg(v61, src, s->Unk0, 1, k, v53, v54);
                            }

                            if(!gserver.Unk452129 && gserver.Unk12 && !gserver.Unk12->Unk361 && this->Unk12)
                                this->Unk12->WriteToOutput(v61);
                        }
                        break;
                    case 0xE:
                        a2.__rs(v59);

                        gserver.Unk452260 = v59 ? 1 : 0;
                        break;
                    case 0x10:
                        a2.__rs(v59);

                        gserver.Unk452261 = v59 ? 1 : 0;
                        break;
                    case 0xF:
                        a2.__rs(v59);
                        a2.__rs(k);
                        a2.__rs(v53);
                        a2.__rs(v54);

                        gserver.Unk452262 = v59 ? 1 : 0;
                        if(gserver.Unk41004 == k && gserver.Unk41008 == v53)
                        {
                            for(l = 0; l < gserver.Unk24.Unk32768; ++l)
                            {
                                if(gserver.Unk24.Unk0[l] && gserver.Unk24.Unk0[l]->Unk4 == v54)
                                {
                                    CNetMsg v61;

                                    if(this->Unk452262)
                                        SayMsg(v61, 6, 0, "", "", "Latto Event Start!!");
                                    else
                                        SayMsg(v61, 6, 0, "", "", "Latto Event Stop!!");

                                    if(gserver.Unk24.Unk0[l]->Unk768)
                                        gserver.Unk24.Unk0[l]->Unk768->WriteToOutput(v61);
                                }
                            }
                        }
                        break;
                    case 0x11:
                        a2.__rs(v59);
                        a2.__rs(k);
                        a2.__rs(v53);
                        a2.__rs(v54);

                        gserver.Unk452263 = v59 ? 1 : 0;
                        if(gserver.Unk41004 == k && gserver.Unk41008 == v53)
                        {
                            for(l = 0; l < gserver.Unk24.Unk32768; ++l)
                            {
                                if(gserver.Unk24.Unk0[l] && gserver.Unk24.Unk0[l]->Unk4 == v54)
                                {
                                    CNetMsg v61;

                                    if(this->Unk452263)
                                        SayMsg(v61, 6, 0, "", "", "NewYear Event Start!!");
                                    else
                                        SayMsg(v61, 6, 0, "", "", "NewYear Event Stop!!");

                                    if(gserver.Unk24.Unk0[l]->Unk768)
                                        gserver.Unk24.Unk0[l]->Unk768->WriteToOutput(v61);
                                }
                            }
                        }
                        break;
                    case 0x12:
                        a2.__rs(v59);
                        a2.__rs(k);
                        a2.__rs(v53);
                        a2.__rs(v54);

                        gserver.Unk452264 = v59 ? 1 : 0;
                        if(gserver.Unk41004 == k && gserver.Unk41008 == v53)
                        {
                            for(l = 0; l < gserver.Unk24.Unk32768; ++l)
                            {
                                if(gserver.Unk24.Unk0[l] && gserver.Unk24.Unk0[l]->Unk4 == v54)
                                {
                                    CNetMsg v61;

                                    if(this->Unk452264)
                                        SayMsg(v61, 6, 0, "", "", "Valentine Event Start!!");
                                    else
                                        SayMsg(v61, 6, 0, "", "", "Valentine Event Stop!!");

                                    if(gserver.Unk24.Unk0[l]->Unk768)
                                        gserver.Unk24.Unk0[l]->Unk768->WriteToOutput(v61);
                                }
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
    else
    {
        if(a2.MsgType == 102)
        {
            a2.__rs(k);
            a2.__rs(v53);
            a2.__rs(v54);
            a2.__rs(l);
            a2.__rs(v59);

            v56 = gserver.FindZone(l);
            if(v53 == -1 || v53 == gserver.Unk41004 && (v54 == -1 || v54 == gserver.Unk41008))
            {
                if(l == -1 || v56 != -1 && gserver.Unk452196[v56].Unk0 == l)
                {
                    switch(v59)
                    {
                        case 1:
                            g_buf3[0] = 0;
                            g_buf2[0] = 0;
                            g_buf[0] = 0;
							
                            a2.__rs(s);
                            a2.__rs(g_buf);
                            a2.__rs(v62);
                            a2.__rs(g_buf2);
                            a2.__rs(g_buf3);

                            j = gserver.Unk24.Find(s);
                            if(j)
                            {
                                CNetMsg v61;
								
                                ChatWhisperMsg(v61, (uint32_t)s, g_buf, g_buf2, g_buf3);
								
                                if(j->Unk768)
                                    j->Unk768->WriteToOutput(v61);
                            }
                            break;
                        case 3:
                            g_buf[0] = 0;
							
                            a2.__rs(s);
                            a2.__rs(g_buf);

                            v62 = gserver.Unk24.Find(s);
                            if(v62)
                            {
                                CNetMsg v61;
								
                                SysWhisperNotFoundMsg(v61);
								
                                if(v62->Unk768)
                                    v62->Unk768->WriteToOutput(v61);
                            }
                            break;
                        case 8:
                            a2.__rs(s);
                            a2.__rs(v62);

                            j = gserver.Unk24.Find(s);
                            if(j)
                            {
                                CNetMsg v61;
                                for(i = 0; i < v62; ++i)
                                {
                                    a2.__rs(v67);
                                    a2.__rs(v68);
                                    a2.__rs(v69);
                                    a2.__rs(src);
                                    a2.__rs(v58);
									
                                    strcpy(g_buf, "Server-SubNum-Zone-Player: ");
                                    if(v53 >= 0)
                                        IntCat(g_buf, v53, 0);
                                    else
                                        strcat(g_buf, "all");
									
                                    strcat(g_buf, "-");
                                    if(v54 >= 0)
                                        IntCat(g_buf, v54, 0);
                                    else
                                        strcat(g_buf, "all");
									
                                    strcat(g_buf, "-");
                                    IntCat(g_buf, v67, 0);
                                    strcat(g_buf, "-");
                                    IntCat(g_buf, v68, 0);
                                    strcat(g_buf, "-");
                                    IntCat(g_buf, v69, 0);
                                    strcat(g_buf, "-");
                                    IntCat(g_buf, src, 0);
                                    strcat(g_buf, "-");
                                    IntCat(g_buf, v58, 0);
									
                                    SayMsg(v61, 6, 0, "", "", g_buf);
									
                                    if(j->Unk768)
                                        j->Unk768->WriteToOutput(v61);
                                }
                            }
                            break;
                        case 9:
                            if(!gserver.Unk452128)
                            {
                                if(gserver.Unk16)
                                {
                                    if(!gserver.Unk16->Unk361)
                                    {
                                        a2.__rs(v66);
                                        a2.__rs(s2);
                                    }
                                }
                            }
                            break;
                        case 0xB:
                            a2.__rs(v66);
                            a2.__rs(s);
                            a2.__rs(v62);
                            a2.__rs(j);
                            a2.__rs(v67);
                            a2.__rs(v50);
                            a2.__rs(dest);

                            v68 = gserver.Unk24.Find(s);
                            if(v68)
                            {
                                if(v68->Unk408->Unk0 == v62)
                                {
                                    if(v66)
                                    {
                                        CNetMsg v61;
										
                                        src = this->FindZone(j);
                                        v69 = &gserver.Unk452196[src];
                                        if(src != -1)
                                        {
                                            v58 = v68->Unk412;
                                            v68->SendDisappearAllInCell();
                                            v58->CharFromCell(v68);
											
                                            if(v68->Unk408->Unk40 > 1)
                                                v68->Unk408->SetDisableArea(v6->Unk412->Unk8);
											
                                            if(v68->Unk408 != v69 && v68->Unk1368)
                                            {
                                                CNetMsg v64;
												
                                                v49 = v68->Unk1368->GetRequest();
                                                if(v49 == v68)
                                                    PartyMsg(v64, 2);
                                                else
                                                    PartyMsg(v64, 6);
												
                                                do_Party(v68, v64);
                                            }
											
                                            GoZoneMsg(v61, j, 0, v69->Unk5, v69->Unk26);
											
                                            if(v68->Unk768)
                                                v68->Unk768->WriteToOutput(v61);
											
                                            v68->Unk408 = v69;
                                            v68->Unk412 = 0;
                                            v68->Unk136 = v67;
                                            v68->Unk132 = 0;
                                            v68->Unk120 = v50;
                                            v68->Unk124 = dest;
                                            v68->Unk768->Unk363 = 1;
                                        }
                                    }
                                    else
                                    {
                                        CNetMsg v61;
										
                                        SysMsg(v61, 22);
										
                                        if(v68->Unk768)
                                            v68->Unk768->WriteToOutput(v61);
                                    }
                                }
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
