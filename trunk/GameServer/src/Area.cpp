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

#include "Area.h"
#include "Cell.h"
#include "Character.h"
#include "NPC.h"
#include "Party.h"
#include "PC.h"
#include "Room.h"
#include "Zone.h"

CArea::CArea(void)
{
    this->Unk4 = 0;
    this->Unk8 = -1;
    this->Unk16 = 0;
    this->Unk12 = 0;
    this->Unk20 = 0;
    this->Unk24 = 0;
    this->Unk28 = 0;
    this->Unk48 = 0;
    this->Unk52 = 0;
    this->Unk64 = 0;
    this->Unk68 = 0;
    this->Unk72 = 0;
    this->Unk76 = -1;
}

CArea::~CArea()
{
    CNPC *v7; // [sp+30h] [bp-8h]@30
    CNPC *v9; // [sp+34h] [bp-4h]@29

    if(this->Unk24)
    {
        for(int i = 0; i < this->Unk20; ++i)
        {
            for(int j = 0; j < this->Unk12; ++j)
            {
                if(this->Unk24[i][j])
                    delete [] this->Unk24[i][j]; // CHECK THIS!!!
            }

            if(this->Unk24[i])
                delete [] this->Unk24[i];
        }

        if(this->Unk24)
            delete this->Unk24;
    }

    if(this->Unk28)
    {
        for(int l = 0; l < this->Unk12; ++l)
        {
            if(this->Unk28[l])
                delete [] this->Unk28[l]; // CHECK THIS!!!
        }

        if(this->Unk28)
            delete [] this->Unk28;
    }

    if(this->Unk48)
    {
        v9 = this->Unk48;
        while(1)
        {
            v7 = v9;

            if(!v9)
                break;

            v9 = v9->Unk748;
            v7->DeleteNPC();
        }
    }

    this->Unk4 = 0;
    this->Unk16 = 0;
    this->Unk12 = 0;
    this->Unk20 = 0;
    this->Unk24 = 0;
    this->Unk28 = 0;
}

void CArea::Init(CZone *a2, int a3, int a4, int a5, int a6)
{
    this->Unk0 = 0;
    this->Unk4 = a2;
    this->Unk8 = a3;
    this->Unk12 = (signed int)((long double)a4 / 12.0);
    this->Unk16 = (signed int)((long double)a5 / 12.0);
    this->Unk20 = a6;
    this->Unk24 = (CEnv ***)malloc(sizeof(CEnv **)); // CHECK THIS!!!

    for(int i = 0; i < this->Unk20; i++)
    {
        this->Unk24[i] = (CEnv **)malloc(sizeof(CEnv *));
        for(int k = 0; k < this->Unk12; k++)
            this->Unk24[i][k] = new CEnv[this->Unk16];
    }

    if(a2->Unk0 != 2 && a2->Unk0 != 5 && a2->Unk0 != 6 && a2->Unk0 != 8)
    {
        this->Unk28 = (CCell **)malloc(sizeof(CCell *) * this->Unk12); // CHECK THIS!!!

        for(int j = 0; j < this->Unk12; j++)
            this->Unk28[j] = new CCell[this->Unk16];
    }
    else
    {
        this->Unk12 = 1;
        this->Unk16 = 1;
        this->Unk28 = (CCell **)malloc(sizeof(CCell *)); // CHECK THIS!!!
        this->Unk28[0] = new CCell[this->Unk16];
    }
}

void CArea::PointToCellNum(float a2, float a3, int *a4, int *a5)
{
    *a4 = (signed int)(a2 / 12.0);
    *a5 = (signed int)(a3 / 12.0);

    if(*a4 < 0)
        *a4 = 0;
    if(*a4 >= this->Unk12)
        *a4 = this->Unk12 - 1;

    if(*a5 < 0)
        *a5 = 0;
    if(*a5 >= this->Unk16)
        *a5 = this->Unk16 - 1;
}

void CArea::CharToCell(CCharacter *a2, char a3, int a4, int a5)
{
    if(a2->Unk140 < 0 && a3 >= 0)
    {
        if(a3 <= 2 * (this->Unk20 - 1))
        {
            this->Unk28[a4][a5].CharToCell(a2);
            a2->Unk408 = this->Unk4;
            a2->Unk412 = this;
            a2->Unk140 = a4;
            a2->Unk144 = a5;
            a2->Unk120.Unk16 = a3;
        }
    }
}

void CArea::CharFromCell(CCharacter *a2)
{
    if(a2->Unk140 >= 0)
    {
        this->Unk28[a2->Unk140][a2->Unk144].CharFromCell(a2);
        a2->Unk140 = -100;
        a2->Unk144 = -100;
    }
}

void CArea::ItemToCell(CItem *a2, char a3, int a4, int a5)
{
    if(a3 >= 0)
    {
        if(a3 <= 2 * (this->Unk20 - 1))
        {
            this->Unk28[a4][a5].ItemToCell(a2);
            a2->Unk196 = a4;
            a2->Unk200 = a5;
            a2->Unk176.Unk16 = a3;
        }
    }
}

void CArea::ItemFromCell(CItem *a2)
{
    if(a2->Unk196 >= 0)
    {
        this->Unk28[a2->Unk196][a2->Unk200].ItemFromCell(a2);
        a2->Unk196 = -100;
        a2->Unk200 = -100;
    }
}

bool CArea::MoveChar(CCharacter *a2, char a3, float a4, float a5, float a6, float a7, __tagMsgMoveType a8, CCharacter *a9)
{
    char v27; // al@91
    char v28; // al@100

    float v29; // [sp+3Ch] [bp-ECh]@52
    float v30; // [sp+40h] [bp-E8h]@29
    CItem *v31; // [sp+44h] [bp-E4h]@135
    CItem *v32; // [sp+48h] [bp-E0h]@137
    CCharacter *v33; // [sp+4Ch] [bp-DCh]@111
    CCharacter *v34; // [sp+50h] [bp-D8h]@112
    char v35; // [sp+56h] [bp-D2h]@109
    char v36; // [sp+57h] [bp-D1h]@100
    int v37; // [sp+58h] [bp-D0h]@79
    int v38; // [sp+5Ch] [bp-CCh]@79
    int v39; // [sp+60h] [bp-C8h]@76
    int v40; // [sp+64h] [bp-C4h]@76
    int v41; // [sp+68h] [bp-C0h]@86
    int v42; // [sp+6Ch] [bp-BCh]@81
    //char v43; // [sp+70h] [bp-B8h]@75
    //char v44; // [sp+84h] [bp-A4h]@75
    //char v45; // [sp+98h] [bp-90h]@75
    //char v46; // [sp+ACh] [bp-7Ch]@75
    //char v47; // [sp+C0h] [bp-68h]@67
    float v48; // [sp+D4h] [bp-54h]@56
    unsigned int v49; // [sp+D8h] [bp-50h]@48
    long double v50; // [sp+DCh] [bp-4Ch]@47
    long double v51; // [sp+E0h] [bp-48h]@43
    float v52; // [sp+E4h] [bp-44h]@39
    float v53; // [sp+E8h] [bp-40h]@39
    float v54; // [sp+ECh] [bp-3Ch]@39
    //float v55; // [sp+FCh] [bp-2Ch]@39
    float v56; // [sp+100h] [bp-28h]@36
    float v57; // [sp+104h] [bp-24h]@22
    float v58; // [sp+108h] [bp-20h]@20
    CCharacter *v59; // [sp+10Ch] [bp-1Ch]@13
    CCharacter *v60; // [sp+110h] [bp-18h]@14
    CCharacter *v61; // [sp+114h] [bp-14h]@12
    CCharacter *v62; // [sp+118h] [bp-10h]@9
    int v63; // [sp+11Ch] [bp-Ch]@6
    int v64; // [sp+120h] [bp-8h]@6
    char v65; // [sp+126h] [bp-2h]@4
    char v66; // [sp+127h] [bp-1h]@1
    float v67; // [sp+13Ch] [bp+14h]@48
    float v68; // [sp+140h] [bp+18h]@48
    float v69; // [sp+144h] [bp+1Ch]@48

    v66 = a3;
    if(a2->Unk0 == 1 && !(((CNPC *)a2)->Unk472 & 8))
        return false;

    v65 = 0;
    if(!this->IsNotBlocked(a2, v66, a4, a5, 0))
        return false;

    this->PointToCellNum(a4, a5, &v64, &v63);

    v62 = a2->Unk0 ? 0 : a2;
    v61 = (a2->Unk0 == 1) ? a2 : 0;

    if(a2->Unk0 != 1)
        goto LABEL_65;

    v59 = this->Unk28[v64][v63].Unk0;
    while(1)
    {
        v60 = v59;

        if(!v59)
            break;

        v59 = v60->Unk404;

        if(v60->Unk120.Unk16 == v66 && v60 != a2 && a2->Unk76 > 0)
        {
            v58 = (v60->Unk120.Unk0 - a4 < 0.0) ? -(v60->Unk120.Unk0 - a4) : (v60->Unk120.Unk0 - a4);
            v57 = (v60->Unk120.Unk4 - a5 < 0.0) ? -(v60->Unk120.Unk4 - a5) : (v60->Unk120.Unk4 - a5);

            if(v60 && v60->Unk412)
            {
                if(v60->Unk412->GetHeight(v60->Unk120.Unk16, v60->Unk120.Unk0, v60->Unk120.Unk4) - a6 >= 0.0)
                    v30 = (v60 && v60->Unk412) ? (v60->Unk412->GetHeight(v60->Unk120.Unk16, v60->Unk120.Unk0, v60->Unk120.Unk4) - a6) : (0.0 - a6);
                else
                    v30 = (v60 && v60->Unk412) ? -(v60->Unk412->GetHeight(v60->Unk120.Unk16, v60->Unk120.Unk0, v60->Unk120.Unk4) - a6) : -(0.0 - a6);
            }
            else
            {
                if(0.0 - a6 >= 0.0)
                    v30 = (v60 && v60->Unk412) ? (v60->Unk412->GetHeight(v60->Unk120.Unk16, v60->Unk120.Unk0, v60->Unk120.Unk4) - a6) : (0.0 - a6);
                else
                    v30 = (v60 && v60->Unk412) ? -(v60->Unk412->GetHeight(v60->Unk120.Unk16, v60->Unk120.Unk0, v60->Unk120.Unk4) - a6) : -(0.0 - a6);
            }

            v56 = v30;
            if(v58 < 0.2 && v57 < 0.2 && v56 < 0.2)
            {
                v54 = v60->Unk120.Unk0 - cos(a7) * 0.5;
                v53 = v60->Unk120.Unk4 - sin(a7) * 0.5;
                v52 = this->GetHeight(v66, v54, v53);
                v51 = GetDistance(a4, a2->Unk120.Unk0, a5, a2->Unk120.Unk4, a6, ((a2 && a2->Unk412) ? a2->Unk412->GetHeight(a2->Unk120.Unk16, a2->Unk120.Unk0, a2->Unk120.Unk4) : 0.0));
                v50 = GetDistance(v54, a2->Unk120.Unk0, v53, a2->Unk120.Unk4, v52, ((a2 && a2->Unk412) ? a2->Unk412->GetHeight(a2->Unk120.Unk16, a2->Unk120.Unk0, a2->Unk120.Unk4) : 0.0));

                if(v51 > v50)
                {
                    v49 = GetRandom(-1570, 1570);
                    a7 = (long double)(signed int)v49 / 2000.0 + a7;
                    v67 = cos(a7) * 0.5 + a2->Unk120.Unk0;
                    v68 = sin(a7) * 0.5 + a2->Unk120.Unk4;
                    v69 = this->GetHeight(a2->Unk120.Unk16, v67, v68);
                    v29 = GetDistance(v67, a2->Unk120.Unk0, v68, a2->Unk120.Unk4, v69, (a2 && a2->Unk412) ? a2->Unk412->GetHeight(a2->Unk120.Unk16, a2->Unk120.Unk0, a2->Unk120.Unk4) : 0.0) + 0.1;
                    v48 = asin((a2 && a2->Unk412) ? ((v69 - a2->Unk412->GetHeight(a2->Unk120.Unk16, a2->Unk120.Unk0, a2->Unk120.Unk4)) / v29) : ((v69 - 0.0) / v29));
                    a4 = cos(v48) * (cos(a7) * 0.5) + a2->Unk120.Unk0;
                    a5 = sin(v48) * (sin(a7) * 0.5) + a2->Unk120.Unk4;
                    a6 = this->GetHeight(v66, a4, a5);
                    ((CNPC *)v61)->Unk492 = 0;
                    v65 = 1;
                }

                if(a9 == v60)
                    return 1;
            }
        }
    }

    if(v65 && !this->IsNotBlocked(v61, v66, a4, a5, 0))
        return false;

    if(((CNPC *)v61)->Unk488) // v61 + 488
    {
        v61->Move(a4, a5, a6, a7, v66);
        return true;
    }

LABEL_65:
    if(!a2->Unk0 && ((CPC *)v62)->IsParty())
    {
        CNetMsg v47;
        PartyInfoMsg(v47, ((CPC *)v62));
        ((CPC *)v62)->Unk1368->SendAll(v47, ((CPC *)v62), 0);
    }

    if(a2->Unk140 == v64 && a2->Unk144 == v63)
    {
        CNetMsg v47;

        a2->Move(a4, a5, a6, a7, v66);
        MoveMsg(v47, a8, a2);
        this->SendToCell(v47, a2, 0, 4);

        if(!a2->Unk0 && ((CPC *)v62)->IsSetPlayerState(8) && ((CPC *)v62)->IsInPeaceZone())
        {
            ((CPC *)v62)->ResetPlayerState(24);
            ActionMsg(v47, ((CPC *)v62), 0, 23);
            this->SendToCell(v47, a2, 1, 4);
        }

        return true;
    }

    int v59i = a2->Unk140;
    int v60i = a2->Unk144;
    this->CharFromCell(a2);
    a2->Move(a4, a5, a6, a7, v66);
    this->CharToCell(a2, v66, v64, v63);

    CNetMsg v47;
    CNetMsg v46;
    CNetMsg v45;
    CNetMsg v44;
    CNetMsg v43;

    MoveMsg(v47, a8, a2);
    AppearMsg(v46, a2, 0);
    DisappearMsg(v45, a2);

    if(v59i >= v64)
    {
        v39 = v59i;
        v40 = v64;
    }
    else
    {
        v40 = v59i;
        v39 = v64;
    }

    if(v60i >= v63)
    {
        v37 = v60i;
        v38 = v63;
    }
    else
    {
        v38 = v60i;
        v37 = v63;
    }
    v42 = v40 - 4;

    while(2)
    {
        if(v42 <= v39 + 4)
        {
            if(v42 < 0 || v42 >= this->Unk12)
            {
LABEL_150:
                ++v42;
                continue;
            }
            v41 = v38 - 4;
            while(2)
            {
                if(v41 > v37 + 4)
                    goto LABEL_150;
                if(v41 < 0 || v41 >= this->Unk16)
                {
LABEL_149:
                    ++v41;
                    continue;
                }
                break;
            }
            v27 = 0;
            if(v59i - v42 < 0)
            {
                if(v42 - v59i > 4)
                    goto LABEL_100;
            }
            else
            {
                if(v59i - v42 > 4)
                    goto LABEL_100;
            }
            if(v60i - v41 < 0)
            {
                if(v41 - v60i > 4)
                    goto LABEL_100;
            }
            else
            {
                if(v60i - v41 > 4)
                {
LABEL_100:
                    v36 = v27;
                    v28 = 0;
                    if(v64 - v42 < 0)
                    {
                        if(v42 - v64 <= 4)
                            goto LABEL_104;
                    }
                    else
                    {
                        if(v64 - v42 > 4)
                            goto LABEL_109;
LABEL_104:
                        if(v63 - v41 < 0)
                        {
                            if(v41 - v63 <= 4)
                                goto LABEL_108;
                        }
                        else
                        {
                            if(v63 - v41 > 4)
                                goto LABEL_109;
LABEL_108:
                            v28 = 1;
                        }
                    }
LABEL_109:
                    v35 = v28;
                    if(v36 || v28)
                    {
                        v33 = this->Unk28[v42][v41].Unk0;
                        while(1)
                        {
                            v34 = v33;
                            if(!v33)
                                break;
                            v33 = v33->Unk404;
                            if(v34 != a2)
                            {
                                if(v36)
                                {
                                    if(v35)
                                    {
                                        if(!((CPC *)v34)->Unk0 && ((CPC *)v34)->Unk768)
                                            ((CPC *)v34)->Unk768->WriteToOutput(v47);
                                    }
                                    else
                                    {
                                        if(!((CPC *)v34)->Unk0 && ((CPC *)v34)->Unk768)
                                            ((CPC *)v34)->Unk768->WriteToOutput(v45);

                                        DisappearMsg(v43, v34);

                                        if(((CPC *)v62) && ((CPC *)v62)->Unk768)
                                            ((CPC *)v62)->Unk768->WriteToOutput(v43);
                                    }
                                }
                                else
                                {
                                    if(v35)
                                    {
                                        if(!((CPC *)v34)->Unk0 && ((CPC *)v34)->Unk768)
                                            ((CPC *)v34)->Unk768->WriteToOutput(v46);

                                        AppearMsg(v44, v34, 0);

                                        if(((CPC *)v62) && ((CPC *)v62)->Unk768)
                                            ((CPC *)v62)->Unk768->WriteToOutput(v44);
                                    }
                                }
                            }
                        }
                        v31 = this->Unk28[v42][v41].Unk4;
                        while(!a2->Unk0)
                        {
                            v32 = v31;
                            if(!v31)
                                break;
                            v31 = v31->Unk208;
                            if(!v35 || v36)
                            {
                                if(!v35)
                                {
                                    if(v36)
                                    {
                                        ItemDisappearMsg(v43, v32);

                                        if(((CPC *)v62)->Unk768)
                                            ((CPC *)v62)->Unk768->WriteToOutput(v43);
                                    }
                                }
                            }
                            else
                            {
                                ItemAppearMsg(v44, v32);

                                if(((CPC *)v62)->Unk768)
                                    ((CPC *)v62)->Unk768->WriteToOutput(v44);
                            }
                        }
                    }
                    goto LABEL_149;
                }
            }
            v27 = 1;
            goto LABEL_100;
        }
        break;
    }

    if(!a2->Unk0 && ((CPC *)v62)->IsSetPlayerState(8) && ((CPC *)v62)->IsInPeaceZone())
    {
        ((CPC *)v62)->ResetPlayerState(24);
        ActionMsg(v47, ((CPC *)v62), 0, 23);
        this->SendToCell(v47, a2, 1, 4);
    }

    return 1;
}

bool CArea::SendToCell(CNetMsg &a2, CCharacter *a3, bool a4, int a5)
{
    int v9; // [sp+28h] [bp-10h]@3
    int v10; // [sp+2Ch] [bp-Ch]@3
    int v11; // [sp+30h] [bp-8h]@3

    if(a3->Unk140 >= 0)
    {
        v11 = a5 + a3->Unk140;
        v10 = a3->Unk144 - a5;
        v9 = a5 + a3->Unk144;
        for(int i = a3->Unk140 - a5; i <= v11; ++i)
        {
            if(i >= 0 && i < this->Unk12)
            {
                for(int j = v10; j <= v9; ++j)
                {
                    if(j >= 0 && j < this->Unk16)
                    {
                        for(CCharacter *k = this->Unk28[i][j].Unk0; k; k = k->Unk404)
                        {
                            if(!k->Unk0 && (k != a3 || a4))
                            {
                              if(((CPC *)k)->Unk768)
                                  ((CPC *)k)->Unk768->WriteToOutput(a2);
                            }
                        }
                    }
                }
            }
        }

        return true;
    }

    return false;
}

bool CArea::SendToCell(CNetMsg &a2, char a3, int a4, int a5, int a6)
{
    for(int i = a4 - a6; i <= a6 + a4; ++i)
    {
        if(i >= 0 && i < this->Unk12)
        {
            for(int j = a5 - a6; j <= a6 + a5; ++j)
            {
                if(j >= 0 && j < this->Unk16)
                {
                    for(CCharacter *k = this->Unk28[i][j].Unk0; k; k = k->Unk404)
                    {
                        if(!((CPC *)k)->Unk0)
                        {
                          if(((CPC *)k)->Unk768)
                              ((CPC *)k)->Unk768->WriteToOutput(a2);
                        }
                    }
                }
            }
        }
    }

    return true;
}

void CArea::SendCellInfo(CPC *a2)
{
    CItem *v3; // [sp+1Ch] [bp-3Ch]@20
    CItem *v4; // [sp+20h] [bp-38h]@21
    CCharacter *v5; // [sp+24h] [bp-34h]@12
    CCharacter *v6; // [sp+28h] [bp-30h]@13
    int v10; // [sp+48h] [bp-10h]@2
    int v11; // [sp+4Ch] [bp-Ch]@2
    int v12; // [sp+50h] [bp-8h]@2
    int v13; // [sp+54h] [bp-4h]@2

    if(a2->Unk140 >= 0)
    {
        v13 = a2->Unk140 - 4;
        v12 = a2->Unk140 + 4;
        v11 = a2->Unk144 - 4;
        v10 = a2->Unk144 + 4;
        CNetMsg v7;

        for(int i = v13; i <= v12; ++i)
        {
            if(i >= 0 && i < this->Unk12)
            {
                for(int j = v11; j <= v10; ++j)
                {
                    if(j >= 0 && j < this->Unk16)
                    {
                        v5 = this->Unk28[i][j].Unk0;
                        while(1)
                        {
                            v6 = v5;

                            if(!v5)
                                break;

                            v5 = v5->Unk404;

                            if(v6 != a2 && (v6->Unk76 > 0 || !v6->Unk0))
                            {
                                AppearMsg(v7, v6, 0);

                                if(a2->Unk768)
                                    a2->Unk768->WriteToOutput(v7);
                            }
                        }

                        v3 = this->Unk28[i][j].Unk4;

                        while(1)
                        {
                            v4 = v3;

                            if(!v3)
                                break;

                            v3 = v3->Unk208;
                            ItemAppearMsg(v7, v4);

                            if(a2->Unk768)
                                a2->Unk768->WriteToOutput(v7);
                        }
                    }
                }
            }
        }
    }
}

bool CArea::IsNotBlocked(CCharacter *a2, CCharacter *a3, bool a4)
{
    return this->IsNotBlocked(a2, a3->Unk120.Unk16, a3->Unk120.Unk0, a3->Unk120.Unk4, a4);
}

bool CArea::IsNotBlocked(CCharacter *a2, char a3, float a4, float a5, bool a6)
{
    char v35; // [sp+1Ah] [bp-2Eh]@27
    char v36; // [sp+1Bh] [bp-2Dh]@40
    char v37; // [sp+1Bh] [bp-2Dh]@70
    float v38; // [sp+1Ch] [bp-2Ch]@34
    float v39; // [sp+1Ch] [bp-2Ch]@64
    float v40; // [sp+20h] [bp-28h]@31
    float v41; // [sp+20h] [bp-28h]@61
    float v44; // [sp+28h] [bp-20h]@24
    float v45; // [sp+2Ch] [bp-1Ch]@22
    float v46; // [sp+30h] [bp-18h]@20
    float v47; // [sp+34h] [bp-14h]@20
    signed int v48; // [sp+38h] [bp-10h]@18
    char v49; // [sp+3Dh] [bp-Bh]@13
    char v50; // [sp+3Eh] [bp-Ah]@13
    char v51; // [sp+3Fh] [bp-9h]@13
    char v52; // [sp+47h] [bp-1h]@27

    if(a4 < 0.0 || a4 >= this->Unk4->Unk32[a3 / 2].Unk0 || a5 < 0.0 || a5 >= this->Unk4->Unk32[a3 / 2].Unk4)
        return false;

    if(a2->Unk0 != 1)
        return true;

    if(a2->Unk120.Unk16 - a3 < 0)
    {
        if(a3 - a2->Unk120.Unk16 <= 1)
            goto LABEL_13;

        return false;
    }

    if(a2->Unk120.Unk16 - a3 > 1)
        return false;

LABEL_13:
    v51 = this->GetAttr(a3, a4, a5);
    v50 = this->GetAttr(a2->Unk120.Unk16, a2->Unk120.Unk0, a2->Unk120.Unk4);
    v49 = 0;

    if(a2->Unk120.Unk16 & 1)
        v49 = 1;

    if(v51 != -1 || a6)
    {
        v48 = 0;

        if(a6)
            v48 = 1;

        v47 = a4 - a2->Unk120.Unk0;
        v46 = a5 - a2->Unk120.Unk4;

        v45 = (v47 < 0.0) ? -v47 : v47;
        v44 = (v46 < 0.0) ? -v46 : v46;

        if(v45 >= 0.0000099999997 || v44 >= 0.0000099999997)
        {
            v35 = 1;
            v52 = a2->Unk120.Unk16;

            if(v45 <= (long double)v44)
            {
                v41 = (v47 >= 0.0) ? (v45 / v44) : (v45 * -1.0 / v44);
                v39 = (v46 >= 0.0) ? 1.0 : -1.0;

                for(int i = v48; ; ++i)
                {
                    //UNDEF(v24);
                    //v25 = 0.0 < v46;
                    //v26 = 0;
                    //v27 = 0.0 == v46;

                    //if((HIBYTE(v24) & 0x45) != 1 || (v29 = (long double)i * v39 + a2->Unk120.Unk4, UNDEF(v28), v30 = v29 < a5, v31 = 0, v32 = v29 == a5,(HIBYTE(v28) & 0x45) != 1))
                    if(v46 <= 0.0 || i * v39 + a2->Unk120.Unk4 <= a5)
                    {
                        if(v46 >= 0.0 || i * v39 + a2->Unk120.Unk4 <= a5)
                            break;
                    }

                    v37 = this->GetAttr(v52, i * v41 + a2->Unk120.Unk0, i * v39 + a2->Unk120.Unk4);
                    if(v37 == -1)
                    {
                        if(!v49 || !v35)
                            return false;

                        i = v48 - 1;
                        ++v52;
                        v35 = 0;
                    }
                    else
                    {
                        if(!a6)
                        {
                            if(v49 && !v37)
                            {
                                if(v50 == 40)
                                {
                                    ++v52;
                                    a2->Unk120.Unk16 = v52;
                                }
                                else
                                {
                                    if(v50 == 50)
                                    {
                                        --v52;
                                        a2->Unk120.Unk16 = v52;
                                    }
                                }
                            }
                            if(!v49)
                            {
                                if(v37 == 40)
                                {
                                    ++v52;
                                    a2->Unk120.Unk16 = v52;
                                }
                                else
                                {
                                    if(v37 == 50)
                                    {
                                        --v52;
                                        a2->Unk120.Unk16 = v52;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                v40 = (v47 >= 0.0) ? 1.0 : -1.0;
                v38 = (v46 >= 0.0) ? (v44 / v45) : (v44 * -1.0 / v45);

                for(int j = v48; ; ++j)
                {
                    //UNDEF(v11);
                    //v12 = 0.0 < v47;
                    //v13 = 0;
                    //v14 = 0.0 == v47;

                    //if((HIBYTE(v11) & 0x45) != 1 || (v16 = (long double)j * v40 + a2->Unk120.Unk0, UNDEF(v15), v17 = v16 < a4, v18 = 0, v19 = v16 == a4, (HIBYTE(v15) & 0x45) != 1))
                    if(v47 <= 0.0 || j * v40 + a2->Unk120.Unk0 <= a4)
                    {
                        if(v47 >= 0.0 || j * v40 + a2->Unk120.Unk0 <= a4)
                            break;
                    }

                    v36 = this->GetAttr(v52, j * v40 + a2->Unk120.Unk0, j * v38 + a2->Unk120.Unk4);
                    if(v36 == -1)
                    {
                        if(!v49 || !v35)
                            return false;

                        j = v48 - 1;
                        ++v52;
                        v35 = 0;
                    }
                    else
                    {
                        if(!a6)
                        {
                            if(v49 && !v36)
                            {
                                if(v50 == 40)
                                {
                                    ++v52;
                                    a2->Unk120.Unk16 = v52;
                                }
                                else
                                {
                                    if(v50 == 50)
                                    {
                                        --v52;
                                        a2->Unk120.Unk16 = v52;
                                    }
                                }
                            }
                            if(!v49)
                            {
                                if(v36 == 40)
                                {
                                    ++v52;
                                    a2->Unk120.Unk16 = v52;
                                }
                                else
                                {
                                    if(v36 == 50)
                                    {
                                        --v52;
                                        a2->Unk120.Unk16 = v52;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        return true;
    }

    return false;
}

char CArea::GetAttr(char a2, float a3, float a4)
{
    signed int v5; // [sp+14h] [bp-14h]@1
    signed int v6; // [sp+20h] [bp-8h]@1
    char v7; // [sp+27h] [bp-1h]@1

    v6 = (signed int)a3;
    v5 = (signed int)a4;
    v7 = a2 / 2;

    if((char)(a2 / 2) >= 0 && (signed int)v7 < this->Unk4->Unk28)
    {
        if(v6 >= 0 && v6 < this->Unk4->Unk32[v7].Unk0 && v5 >= 0 && v5 < this->Unk4->Unk32[v7].Unk4)
            return this->Unk4->Unk32[v7].Unk8[v6][v5]; // TO CHECK
    }

    return 255;
}

float CArea::GetHeight(char a2, float a3, float a4)
{
    signed int v5; // [sp+14h] [bp-14h]@1
    signed int v6; // [sp+20h] [bp-8h]@1
    char v7; // [sp+27h] [bp-1h]@1

    v6 = (signed int)a3;
    v5 = (signed int)a4;
    v7 = a2 / 2;

    if((char)(a2 / 2) >= 0 && (signed int)v7 < this->Unk4->Unk28)
    {
        if(v6 >= 0 && v6 < this->Unk4->Unk32[v7].Unk0 && v5 >= 0 && v5 < this->Unk4->Unk32[v7].Unk4)
            return this->Unk4->Unk32[v7].Unk12[v6][v5];
    }

    return 0.0;
}

void CArea::LoadNPC(void)
{
    float v2; // [sp+18h] [bp-103Ch]@3
    float v3; // [sp+1Ch] [bp-1038h]@3
    float v4; // [sp+20h] [bp-1034h]@3
    int v5; // [sp+24h] [bp-1030h]@3
    int v6; // [sp+28h] [bp-102Ch]@3
    int v7; // [sp+2Ch] [bp-1028h]@3
    int v8; // [sp+30h] [bp-1024h]@3

    CDBCmd v9;

    v9.Init(&gserver.Unk41816);
    strcpy(g_buf, "SELECT * FROM t_npc_regen WHERE a_zone_num=");
    IntCat(g_buf, this->Unk4->Unk0, false);
    StrCat(g_buf, "ORDER BY a_index");
    v9.SetQuery(g_buf);
    v9.Open();

    this->Unk52 = v9.AffectedRows;
    this->Unk32.SetCount(this->Unk52);

    while(v9.MoveNext())
    {
        v9.GetRec("a_npc_idx", v8);
        v9.GetRec("a_pos_x", v4);
        v9.GetRec("a_y_layer", v7);
        v9.GetRec("a_pos_z", v3);
        v9.GetRec("a_pos_r", v2);
        v9.GetRec("a_regen_sec", v6);
        v9.GetRec("a_total_num", v5);

        this->Unk32.Unk0 = 0;
        this->Unk32.AddRegenInfo(v8, v6, v4, v7, v3, v2, v5, this->Unk4->Unk0);
    }
}

int CArea::GetPCCount(CCharacter *a2, int a3)
{
    return this->GetPCCount(a2->Unk140, a2->Unk144, a3);
}

int CArea::GetPCCount(int a2, int a3, int a4)
{
    int v5; // [sp+1Ch] [bp-Ch]@1

    v5 = 0;
    for(int i = a2 - a4; i <= a4 + a2; ++i)
    {
        if(i >= 0 && i < this->Unk12)
        {
            for(int j = a3 - a4; j <= a4 + a3; ++j)
            {
                if(j >= 0)
                {
                    if(j < this->Unk16)
                        v5 += this->Unk28[i][j].Unk12;
                }
            }
        }
    }

    return v5;
}

CCharacter *CArea::FindCharInCell(CCharacter *a2, int a3, __tagMsgCharType a4, bool a5)
{
    if(a2->Unk140 >= 0)
    {
        for(int i = a2->Unk140 - 4; i <= a2->Unk140 + 4; ++i)
        {
            if(i >= 0 && i < this->Unk12)
            {
                for(int j = a2->Unk144 - 4; j <= a2->Unk144 + 4; ++j)
                {
                    if(j >= 0 && j < this->Unk16)
                    {
                        for(CCharacter *k = this->Unk28[i][j].Unk0; k; k = k->Unk404)
                        {
                            if(k->Unk0 == a4 && k->Unk4 == a3 && (k->Unk76 > 0 || a5))
                                return k;
                        }
                    }
                }
            }
        }
    }

    return 0;
}

CCharacter *CArea::FindChar(int a2, __tagMsgCharType a3)
{
    for(int i = 0; i < this->Unk12; ++i)
    {
        for(int j = 0; j < this->Unk16; ++j)
        {
            for(CCharacter *k = this->Unk28[i][j].Unk0; k; k = k->Unk404)
            {
                if(k->Unk0 == a3 && k->Unk4 == a2 && k->Unk76 > 0)
                    return k;
            }
        }
    }

    return 0;
}

void CArea::CreateRoom(int a2, char a3, int a4, int a5, int a6, int a7)
{
    CRoom *v19; // [sp+4Ch] [bp-8h]@1
    char v20; // [sp+53h] [bp-1h]@1

    v20 = a3;
    v19 = new CRoom();
    CNPCRegenList v11, v15;

    if(this->Unk32.Unk0 == a2)
    {
        v15.Unk0  = this->Unk32.Unk0;
        v15.Unk4  = this->Unk32.Unk4;
        v15.Unk8  = this->Unk32.Unk8;
        v15.Unk12 = this->Unk32.Unk12;
    }

    v11.Unk0  = v15.Unk0;
    v11.Unk4  = v15.Unk4;
    v11.Unk8  = v15.Unk8;
    v11.Unk12 = v15.Unk12;

    v19->Init(this, a2, v20, a4, a5, a6, a7, v15); // CHECK PARAMETERS

    if(this->Unk64)
        this->Unk64->Unk72 = v19;

    v19->Unk76  = this->Unk64;
    v19->Unk72  = 0;
    this->Unk64 = v19;
}

CRoom *CArea::FindRoom(int a2, int a3)
{
    for(CRoom *i = this->Unk64; i; i = i->Unk76)
    {
        if(i->Unk4 == a2 && (a3 == -1 || i->Unk8 == a3))
            return i;
    }

    return 0;
}

bool CArea::DeleteRoom(CRoom *a2)
{
    if(a2 && a2->Unk0 == this)
    {
        if(a2->Unk68)
        {
            for(int i = 0; i < a2->Unk24; ++i)
            {
                for(int j = 0; j < a2->Unk28; ++j)
                {
                    if(a2->Unk36[i][j].Unk12)
                    {
                        for(CCharacter *k = a2->Unk36[i][j].Unk0; k; k = k->Unk404);
                    }
                }
            }
        }

        if(a2->Unk72)
        {
            a2->Unk72->Unk76 = a2->Unk76;

            if(a2->Unk76)
                a2->Unk76->Unk72 = a2->Unk72;
        }
        else
        {
            this->Unk64 = a2->Unk76;

            if(a2->Unk76)
                a2->Unk76->Unk72 = 0;
        }

        a2->Unk72 = 0;
        a2->Unk76 = 0;

        if(a2)
            delete a2;

        return true;
    }

    return false;
}

bool CArea::MoveToRoom(CCharacter *a2, float a3, float a4, float a5, int a6, int a7)
{
    int v18; // [sp+20h] [bp-34h]@11
    int v19; // [sp+24h] [bp-30h]@9
    char v20; // [sp+2Bh] [bp-29h]@8
    int v21; // [sp+2Ch] [bp-28h]@8
    int v22; // [sp+30h] [bp-24h]@8
    int v24; // [sp+38h] [bp-1Ch]@1
    CRoom *v25; // [sp+3Ch] [bp-18h]@1

    CNetMsg v26;

    v25 = this->FindRoom(a6, a7);
    v24 = 12;

    if(v25)
    {
        //v23 = v24 * *(_DWORD *)(v25 + 16);
        //v8 = (long double)v23;
        //UNDEF(v9);
        //v10 = a3 < v8;
        //v11 = 0;
        //v12 = a3 == v8;

        //if((HIBYTE(v9) & 0x45) != 1 && (v23 = v24 * (*(_DWORD *)(v25 + 24) + *(_DWORD *)(v25 + 16)), a3 <= (long double)v23) && (v23 = v24 * *(_DWORD *)(v25 + 20), v13 = (long double)v23, UNDEF(v14), v15 = a4 < v13, v16 = 0, v17 = a4 == v13, (HIBYTE(v14) & 0x45) != 1) && (v23 = v24 * (*(_DWORD *)(v25 + 28) + *(_DWORD *)(v25 + 20)), a4 <= (long double)v23))
        if(v24 * v25->Unk16 <= a3 && v24 * v25->Unk20 <= a4 && a4 <= v24 * (v25->Unk28 + v25->Unk20))
        {
            v22 = a2->Unk140;
            v21 = a2->Unk144;
            v20 = a2->Unk120.Unk16;

            DisappearMsg(v26, a2);

            if(a2->Unk416)
            {
                a2->Unk416->CharFromCell(a2);
                a2->Unk416->SendToCell(v26, v22, v21);
            }
            else
            {
                this->CharFromCell(a2);
                this->SendToCell(v26, v20, v22, v21, 4);
            }

            a2->Unk120.Unk0 = a3;
            a2->Unk120.Unk4 = a4;
            a2->Unk120.Unk12 = a5;

            v25->PointToCellNum(a2->Unk120.Unk0, a2->Unk120.Unk4, &v19, &v18);
            v25->CharToCell(a2, v19, v18);

            if(!a2->Unk0)
            {
                GotoMsg(v26, ((CPC *)a2));

                if(((CPC *)a2)->Unk768)
                    ((CPC *)a2)->Unk768->WriteToOutput(v26);

                v25->SendCellInfo(((CPC *)a2));
            }

            AppearMsg(v26, a2, 1);
            v25->SendToCell(v26, a2, 0);

            return true;
        }
    }

    return false;
}

void CArea::SetEnable(void)
{
    CNPCRegenInfo *v5; // [sp+3Ch] [bp-28h]@8
    CNPC *v6; // [sp+40h] [bp-24h]@8
    CNPC *v7; // [sp+40h] [bp-24h]@16
    int v8; // [sp+44h] [bp-20h]@12
    int v9; // [sp+48h] [bp-1Ch]@12

    CNetMsg v11;

    if(this->Unk0)
    {
        return;
    }
    else
    {
        this->Unk0 = 1;
        this->Unk56 = gserver.Unk41248;
        this->Unk60 = gserver.Unk41248;
        this->Unk52 = 0;
        this->Unk72 = 0;

        if(this->Unk4->Unk0 != 2 && this->Unk4->Unk0 != 5 && this->Unk4->Unk0 != 6)
        {
            for(int i = 0; i < this->Unk32.Unk8; ++i)
            {
                v5 = &this->Unk32.Unk4[i];
                v6 = gserver.Unk452200.Create(v5->Unk0);

                if(v6)
                {
                    v6->Unk120.Unk0     = v5->Unk8;
                    v6->Unk120.Unk16    = v5->Unk12;
                    v6->Unk120.Unk4     = v5->Unk16;
                    v6->Unk120.Unk12    = (v6->Unk464->Unk92 & 4) ? (GetRandom(0, 62831) / 10000) : v5->Unk20;
                    v6->Unk476          = v6->Unk120.Unk0;
                    v6->Unk480          = v6->Unk120.Unk16;
                    v6->Unk484          = v6->Unk120.Unk4;
                    v6->Unk752          = v5;

                    v5->Unk32 = 1;
                    ++v5->Unk40;
                    v5->Unk36 = 0;

                    this->AddNPC(v6);
                    this->PointToCellNum(v6->Unk120.Unk0, v6->Unk120.Unk4, &v9, &v8);
                    this->CharToCell(v6, v6->Unk120.Unk16, v9, v8);
                    AppearMsg(v11, v6, 1);
                    this->SendToCell(v11, v6->Unk120.Unk16, v9, v8, 4);
                }
            }
        }

        for(int i = 0; i < this->Unk4->Unk60; ++i)
        {
            v7 = gserver.Unk452200.Create(this->Unk4->Unk56[i].Unk0);

            if(v7)
            {
                v7->Unk120.Unk12    = this->Unk4->Unk56[i].Unk12;
                v7->Unk120.Unk0     = this->Unk4->Unk56[i].Unk4;
                v7->Unk476          = this->Unk4->Unk56[i].Unk4;
                v7->Unk120.Unk4     = this->Unk4->Unk56[i].Unk8;
                v7->Unk484          = this->Unk4->Unk56[i].Unk8;
                v7->Unk120.Unk16    = (char)this->Unk4->Unk56[i].Unk20;
                v7->Unk480          = (char)this->Unk4->Unk56[i].Unk20; // *(_DWORD *)(v7->Unk480)

                this->AddNPC(v7);
                this->PointToCellNum(v7->Unk120.Unk0, v7->Unk120.Unk4, &v9, &v8);
                this->CharToCell(v7, v7->Unk120.Unk16, v9, v8);
                AppearMsg(v11, v7, 1);
                this->SendToCell(v11, v7->Unk120.Unk16, v9, v8, 4);
            }
        }
    }
}

void CArea::SetDisable(void)
{
    CNPC  *v1; // ST28_4@16
    CItem *v3; // [sp+18h] [bp-10h]@8
    CItem *v4; // [sp+1Ch] [bp-Ch]@9
    CRoom *v5; // [sp+1Ch] [bp-Ch]@22

    if(this->Unk0)
    {
        this->Unk0 = 0;
        for(int i = 0; i < this->Unk12; ++i)
        {
            for(int j = 0; j < this->Unk16; ++j)
            {
                while(this->Unk28[i][j].Unk0)
                    this->CharFromCell(this->Unk28[i][j].Unk0);

                v3 = this->Unk28[i][j].Unk4;

                while(1)
                {
                    v4 = v3;

                    if(!v3)
                        break;

                    v3 = v3->Unk208;
                    this->ItemFromCell(v4);
                    v4->Unk172 = 0;

                    if(v4)
                        delete v4;
                }
            }
        }

        while(this->Unk48)
        {
            v1 = this->Unk48->Unk748;
            this->Unk48->DeleteNPC();
            this->Unk48 = 0;
            this->Unk48 = v1;
        }

        for(int k = 0; k < this->Unk32.Unk8; ++k)
        {
            this->Unk32.Unk4[k].Unk32 = 0;
            this->Unk32.Unk4[k].Unk36 = 0;
            this->Unk32.Unk4[k].Unk40 = 0;
        }

        this->Unk72 = 0;
        while(this->Unk64)
        {
            v5 = this->Unk64->Unk76;

            if(this->Unk64)
                delete this->Unk64;

            this->Unk64 = v5;
        }
    }
}

CItem *CArea::DropItem(CItem *a2, CCharacter *a3)
{
    float v10; // [sp-18h] [bp-90h]@15
    float v11; // [sp-14h] [bp-8Ch]@12
    float v12; // [sp-10h] [bp-88h]@8
    float v13; // [sp-10h] [bp-88h]@28
    char v14; // [sp-Ch] [bp-84h]@8
    char v15; // [sp-Ch] [bp-84h]@28
    double v16; // [sp+18h] [bp-60h]@15
    double v17; // [sp+28h] [bp-50h]@15
    double v18; // [sp+30h] [bp-48h]@12
    double v19; // [sp+40h] [bp-38h]@12
    int v20; // [sp+4Ch] [bp-2Ch]@33
    int v21; // [sp+50h] [bp-28h]@33
    float v23; // [sp+60h] [bp-18h]@15

    if(a2)
    {
        if(this->Unk4->Unk0 != 2 && this->Unk4->Unk0 != 5 && this->Unk4->Unk0 != 6 && this->Unk4->Unk0 != 8)
        {
            v14 = a3->Unk120.Unk16;
            v12 = a3->Unk120.Unk12;
            v11 = (a3 && a3->Unk412) ? a3->Unk412->GetHeight(a3->Unk120.Unk16, a3->Unk120.Unk0, a3->Unk120.Unk4) : 0.0;

            ((CPC *)a3)->GetSize(); //(*(void (__cdecl **)(int))(*(_DWORD *)(a3 + 460) + 36))(a3);
            v19 = GetRandom(0, 100) * 0.01 + v11;
            v18 = a3->Unk120.Unk4;
            v23 = GetRandom(0, 1) ? (v18 + v19) : (-1.0 * v19 + v18);
            v10 = v23;

            ((CPC *)a3)->GetSize(); //(*(void (__cdecl **)(int))(*(_DWORD *)(a3 + 460) + 36))(a3);
            v17 = GetRandom(0, 100) * 0.01 + v23;
            v16 = a3->Unk120.Unk0;
            v23 = GetRandom(0, 1) ? (v16 + v17) : (-1.0 * v17 + v16);

            a2->Unk176.__as(CPos(v23, v10, v11, v12, v14));
        }
        else
        {
            a2->Unk176.__as(CPos(a3->Unk120.Unk0, a3->Unk120.Unk4, a3->Unk120.Unk8, a3->Unk120.Unk12, a3->Unk120.Unk16));
        }

        if(a2->Unk176.Unk0 < 0.0)
            a2->Unk176.Unk0 = 0;

        if(a2->Unk176.Unk4 < 0.0)
            a2->Unk176.Unk4 = 0;

        if(a2->Unk176.Unk0 >= this->Unk4->Unk32->Unk0)
            a2->Unk176.Unk0 = this->Unk4->Unk32->Unk0;

        if(a2->Unk176.Unk4 >= this->Unk4->Unk32->Unk4)
            a2->Unk176.Unk4 = this->Unk4->Unk32->Unk4;

        if(this->GetAttr(a2->Unk176.Unk16, a2->Unk176.Unk0, a2->Unk176.Unk4) == -1)
        {
            v15 = a3->Unk120.Unk16;
            v13 = a3->Unk120.Unk12;

            a2->Unk176.__as(CPos(a3->Unk120.Unk0, a3->Unk120.Unk4, ((a3 && a3->Unk412) ? a3->Unk412->GetHeight(a3->Unk120.Unk16, a3->Unk120.Unk0, a3->Unk120.Unk4) : 0.0), v13, v15));
        }

        a2->Unk172 = this;
        a2->Unk212 = gserver.Unk41248;

        this->PointToCellNum(a2->Unk176.Unk0, a2->Unk176.Unk4, &v21, &v20);
        this->ItemToCell(a2, a2->Unk176.Unk16, v21, v20);

        return a2;
    }

    return 0;
}

CItem *CArea::DropItem(int a2, CCharacter *a3, int a4, int a5, long long a6, bool a7)
{
    int v12; // ecx@23
    char v13; // cl@39
    __int64 v14; // qax@39
    float v19; // ST1C_4@69

    float v21; // [sp-10h] [bp-ECh]@12
    float v22; // [sp-Ch] [bp-E8h]@8
    float v23; // [sp-Ch] [bp-E8h]@65
    char v24; // [sp-8h] [bp-E4h]@8
    char v25; // [sp-8h] [bp-E4h]@65
    double v26; // [sp+5Ch] [bp-80h]@15
    double v27; // [sp+6Ch] [bp-70h]@15
    double v28; // [sp+74h] [bp-68h]@12
    double v29; // [sp+84h] [bp-58h]@12
    COptionProto *v30; // [sp+8Ch] [bp-50h]@46
    int v31; // [sp+90h] [bp-4Ch]@35
    long long v32; // [sp+94h] [bp-48h]@35
    int *v33; // [sp+9Ch] [bp-40h]@35
    int v34; // [sp+A0h] [bp-3Ch]@26
    int v35; // [sp+A4h] [bp-38h]@26
    int j; // [sp+A8h] [bp-34h]@37
    int i; // [sp+ACh] [bp-30h]@21
    float v39; // [sp+C0h] [bp-1Ch]@15
    int v40[4]; // [sp+C4h] [bp-18h]@7
    CItem *v44; // [sp+D8h] [bp-4h]@1

    v44 = gserver.Unk41208.CreateItem(a2, -1, a4, a5, a6);
    if(v44)
    {
        if(this->Unk4->Unk0 != 2 && this->Unk4->Unk0 != 5 && this->Unk4->Unk0 != 6 && this->Unk4->Unk0 != 8)
        {
            v24 = a3->Unk120.Unk16;
            v22 = a3->Unk120.Unk12;
            v21 = (a3 && a3->Unk412) ? a3->Unk412->GetHeight(a3->Unk120.Unk16, a3->Unk120.Unk0, a3->Unk120.Unk4) : 0.0;

            a3->GetSize(); //(*(void (__cdecl **)(int))(*(_DWORD *)(a3 + 460) + 36))(a3);
            v29 = GetRandom(0, 100) * 0.01 + v21;
            v28 = a3->Unk120.Unk4;

            v39 = GetRandom(0, 1) ? (v28 + v29) : (-1.0 * v29 + v28);

            a3->GetSize();  //(*(void (__cdecl **)(int))(*(_DWORD *)(a3 + 460) + 36))(a3);
            v27 = GetRandom(0, 100) * 0.01 + v39;
            v26 = a3->Unk120.Unk0;

            v39 = GetRandom(0, 1) ? (v26 + v27) : (-1.0 * v27 + v26);

            v44->Unk176.__as(CPos(v39, v39, v21, v22, v24));
        }
        else
        {
            CPos::__as(CPos(a3->Unk120.Unk0, a3->Unk120.Unk4, a3->Unk120.Unk8, a3->Unk120.Unk12, a3->Unk120.Unk16));
        }

        if(a7 && v44->IsAccessary())
        {
            for(int i = 0; i <= 3; ++i)
            {
                v12 = factor_666[i] * a3->Unk60;
                v40[i] = v12;

                if(v12 > *limit_667) v40[i] = limit_667[i];
            }

            v35 = GetRandom(1, 10000);
            v34 = 2;

            v34 = (v35 > v40[0]) ? ((v35 > v40[1]) ? ((v35 > v40[2]) ? ((v35 > v40[3]) ? 2 : 1) : 3) : 4) : 5;

            v33 = (int *)malloc(sizeof(int) * v34);
            v32 = 0LL;
            v31 = 24;
            i = 0;

            while(i < v34)
            {
                v33[i] = GetRandom(0, 23);

                for(int j = 0; ; ++j)
                {
                    if(j <= 23)
                    {
                        v13 = j + ((char)v33[i]) - 24 * (((signed int)((unsigned long long)(715827883LL * (j + v33[i])) >> 32) >> 2) - ((j + v33[i]) >> 31));
                        v14 = v32 >> (v13 & 0x1F);

                        if(v13 & 0x20) LOBYTE(v14) = (unsigned long long)(v32 >> (v13 & 0x1F)) >> 32;
                        if(v14 & 1) continue;
                    }
                    break;
                }

                if(j == 24)
                {
                    v34 = i;
                }
                else
                {
                    v33[i] = (j + v33[i]) / 24;
                    v33[i] = (j + v33[i]) - 24 * v33[i];
                }

                v32 |= 1LL << ((char)v33[i]);
                v30 = gserver.Unk452236.FindProto(v33[i]);

                if(v30 && !(((unsigned char)(v30->Unk72 >> v44->Unk20->Unk8) ^ 1) & 1))
                    ++i;
            }

            for(int i = 0; i < v34; ++i)
            {
                v30 = gserver.Unk452236.FindProto(v33[i]);
                if(v30)
                {
                    ++v44->Unk168;
                    v44->Unk20[i].MakeOptionValue(v30, a3->Unk60, v34);
                }
            }

            if(v33) delete(v33);
        }

        if(v44->Unk176.Unk0 < 0.0)
            v44->Unk176.Unk0 = 0;

        if(v44->Unk176.Unk4 < 0.0)
            v44->Unk176.Unk4 = 0;

        if(v44->Unk176.Unk0 >= this->Unk4->Unk32->Unk0)
            v44->Unk176.Unk0 = this->Unk4->Unk32->Unk0;

        if(v44->Unk176.Unk4 >= this->Unk4->Unk32->Unk4)
            v44->Unk176.Unk4 = this->Unk4->Unk32->Unk4;

        if(this->GetAttr(v44->Unk176.Unk16, v44->Unk176.Unk0, v44->Unk176.Unk4) == -1)
        {
            v25 = a3->Unk120.Unk16;
            v23 = a3->Unk120.Unk12;
            v19 = (a3 && a3->Unk412) ? a3->Unk412->GetHeight(a3->Unk120.Unk16, a3->Unk120.Unk0, a3->Unk120.Unk4) : 0.0;

            v44->Unk176.__as(CPos(a3->Unk120.Unk0, a3->Unk120.Unk4, v19, v23, v25));
        }

        v44->Unk172 = this;
        v44->Unk212 = gserver.Unk41248;

        this->PointToCellNum(v44->Unk176.Unk0, *v44->Unk176.Unk4, &v30, &v31);
        this->ItemToCell(v44, v44->Unk176.Unk16, v30, v31);

        return v44;
    }

    return 0;
}

void CArea::GroundItemControl(void)
{
    CItem *v13; // [sp+44h] [bp-10h]@5
    CItem *v14; // [sp+48h] [bp-Ch]@6

    CNetMsg v12;

    for(int i = 0; i < this->Unk12; ++i)
    {
        for(int j = 0; j < this->Unk16; ++j)
        {
            v13 = this->Unk28[i][j].Unk4;
            while(1)
            {
                v14 = v13;

                if(!v13)
                    break;

                v13 = v13->Unk208;
                if(gserver.Unk41248 - v14->Unk212 <= 2999)
                {
                    if(gserver.Unk41248 - v14->Unk212 > 99)
                        v14->Unk216 = -1;
                }
                else
                {
                    ItemDisappearMsg(v12, v14);
                    this->SendToCell(v12, v14->Unk176.Unk16, i, j, 4);

                    g_gamelogbuffer.__ls(init("ITEM_JUNK"));
                    g_gamelogbuffer.__ls((int)v14->Unk172->Unk8);
                    g_gamelogbuffer.__ls(delim);
                    g_gamelogbuffer.__ls((char *)v14->Unk20->Unk12);
                    g_gamelogbuffer.__ls(delim);
                    g_gamelogbuffer.__ls((char *)v14->Unk44);
                    g_gamelogbuffer.__ls(end);

                    this->ItemFromCell(v14);

                    v14->Unk172 = 0;

                    if(v14) delete v14;

                    v14 = 0;
                    ++this->Unk68;
                }
            }
        }
    }
}

void CArea::SendToAllClient(CNetMsg &a2)
{
    for(int i = 0; i < this->Unk12; ++i)
    {
        for(int j = 0; j < this->Unk16; ++j)
        {
            for(CCharacter *k = this->Unk28[i][j].Unk0; k; k = k->Unk404)
            {
                if(!k->Unk0)
                {
                    if(((CPC *)k)->Unk768)
                        ((CPC *)k)->Unk768->WriteToOutput(a2);
                }
            }
        }
    }
}


long double GetDistance(CCharacter *a1, CCharacter *a2)
{
    float v4; // ST10_4@9
    long double v5; // fst7@9
    float v6; // ST34_4@9
    float v7; // ST30_4@9
    float v9; // [sp-4h] [bp-24h]@5

    v9 = (a2 && a2->Unk412) ? a2->Unk412->GetHeight(a2->Unk120.Unk16, a2->Unk120.Unk0, a2->Unk120.Unk4) : 0.0;
    v4 = (a1 && a1->Unk412) ? a1->Unk412->GetHeight(a1->Unk120.Unk16, a1->Unk120.Unk0, a1->Unk120.Unk4) : 0.0;

    v5 = GetDistance(a1->Unk120.Unk0, a2->Unk120.Unk0, a1->Unk120.Unk4, a2->Unk120.Unk4, v4, v9);
    v6 = v5;
    ((CPC *)a1)->GetSize(); //(*(void (__cdecl **)(int))(*(_DWORD *)(a1->Unk460) + 36))(a1);
    v7 = v5;
    ((CPC *)a2)->GetSize(); //(*(void (__cdecl **)(int))(*(_DWORD *)(a2->Unk460) + 36))(a2);
    return v6 - v7 - v5;
}
