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

#include "Room.h"
#include "NPC.h"
#include "NPCRegenInfo.h"
#include "Server.h"

/**************************
 CHECK WHAT IS WRONG THERE
 **************************/

int CRoom::m_idxgen = 0;

CRoom::CRoom(void)
{
    this->Unk0  = 0;
    this->Unk4  = this->m_idxgen++;
    this->Unk8  = -1;
    this->Unk12 = 0;
    this->Unk20 = 0;
    this->Unk16 = 0;
    this->Unk28 = 0;
    this->Unk24 = 0;
    this->Unk32 = 0;
    this->Unk36 = 0;
    this->Unk56 = 0;
    this->Unk60 = 0;
    this->Unk64 = 0;
    this->Unk68 = 0;
    this->Unk72 = 0;
    this->Unk76 = 0;
}

CRoom::~CRoom()
{
    CNPC *v7;

    if(this->Unk32)
    {
        for(int i = 0; i < this->Unk24; ++i)
        {
            if(this->Unk32[i])
                delete [] this->Unk32[i]; // CHECK !!!!!
        }

        if(this->Unk32)
            delete this->Unk32;

        this->Unk32 = 0;
    }

    if(this->Unk36)
    {
      for(int k = 0; k < this->Unk24; ++k)
      {
          if(this->Unk36[k])
              delete [] this->Unk36[k]; // CHECK !!!!!
      }

      if(this->Unk36)
          delete this->Unk36;

      this->Unk36 = 0;
    }

    while(this->Unk56)
    {
        v7 = this->Unk56->Unk748;

        if(this->Unk56)
            delete this->Unk56;

        this->Unk56 = v7;
    }
}

void CRoom::Init(CArea *a2, int a3, char a4, int a5, int a6, int a7, int a8, CNPCRegenList a10)
{
    CNPCRegenInfo *v13; // STAC_4@11
    CNPC *v14; // STA8_4@11

    this->Unk0    = a2;
    this->Unk8    = a3;
    this->Unk12 = a4;
    this->Unk16 = a5;
    this->Unk20 = a6;
    this->Unk24 = a7;
    this->Unk28 = a8;

    this->Unk32 = (CEnv  **)malloc(this->Unk24); // CHECK !!!!!
    this->Unk36 = (CCell **)malloc(this->Unk24); // CHECK !!!!!

    for(int i = 0; i < this->Unk28; i++)
    {
        this->Unk32[i] = new CEnv [this->Unk28];
        this->Unk36[i] = new CCell[this->Unk28];
    }

    this->Unk60 = 0;
    this->Unk64 = 0;

    if(a10.Unk8)
    {
        this->Unk40.Unk0 = this->Unk8;
        this->Unk40.SetCount(a10.Unk8);

        for(int l = 0; l < this->Unk40.Unk8; ++l)
        {
            this->Unk40.AddRegenInfo(&a10.Unk4[l]); // CHECK
            v13 = &this->Unk40.Unk4[l]; // CHECK
            v14 = gserver.Unk452200.Create(v13->Unk0);
            v14->Unk120.Unk0    = v13->Unk8;
            v14->Unk120.Unk16   = v13->Unk12;
            v14->Unk120.Unk4    = v13->Unk16;
            v14->Unk120.Unk12   = GetRandom(0, 62831) / 10000;
            v14->Unk476 = v14->Unk120.Unk0;
            v14->Unk484 = v14->Unk120.Unk4;
            v13->Unk32 = 1;
            ++v13->Unk40;
            this->AddNPC(v14);
            this->PointToCellNum(v14->Unk120.Unk0, v14->Unk120.Unk4, &a5, &a6);
            this->CharToCell(v14, a5, a6);
        }
    }

    this->Unk64 = this->Unk60;
    this->Unk68 = 0;
}

void CRoom::AddNPC(CNPC *a2)
{
    if(a2->Unk468 >= 0)
    {
        if(this->Unk56)
            this->Unk56->Unk744 = a2;
        a2->Unk748 = this->Unk56;
        a2->Unk744 = 0;
        this->Unk56 = a2;
        a2->Unk408 = this->Unk0->Unk4;
        a2->Unk412 = this->Unk0;
        a2->Unk416 = this;
        ++this->Unk60;
    }
}

void CRoom::PointToCellNum(float a2, float a3, int *a4, int *a5)
{
    *a4 = (signed int)(a2 / 12.0) - this->Unk16;
    *a5 = (signed int)(a3 / 12.0) - this->Unk20;

    if(*a4 < 0)
        *a4 = 0;
    if(*a4 >= this->Unk24)
        *a4 = this->Unk24 - 1;

    if(*a5 < 0)
        *a5 = 0;
    if(*a5 >= this->Unk28)
        *a5 = this->Unk28 - 1;
}

void CRoom::CharToCell(CCharacter *a2, int a3, int a4)
{
    if(a2->Unk140 < 0)
    {
        this->Unk36[a3][a4].CharToCell(a2);
        a2->Unk408 = this->Unk0->Unk4;
        a2->Unk412 = this->Unk0;
        a2->Unk416 = this;
        a2->Unk140 = a3;
        a2->Unk144 = a4;

        if(!a2->Unk0)
            ++this->Unk68;
    }
}

bool CRoom::SendToCell(CNetMsg &a2, CCharacter *a3, bool a4)
{
    int v8; // [sp+28h] [bp-10h]@3
    int v9; // [sp+2Ch] [bp-Ch]@3
    int v10; // [sp+30h] [bp-8h]@3

    if(a3->Unk140 >= 0)
    {
        v10 = a3->Unk140 + 4;
        v9 = a3->Unk144 - 4;
        v8 = a3->Unk144 + 4;
        for(int i = a3->Unk140 - 4; i <= v10; ++i)
        {
            if(i >= 0 && i < this->Unk24)
            {
                for(int j = v9; j <= v8; ++j)
                {
                    if(j >= 0 && j < this->Unk28)
                    {
                        for(CCharacter *k = this->Unk36[i][j].Unk0; k; k = k->Unk404)
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

bool CRoom::SendToCell(CNetMsg &a2, int a3, int a4)
{
    for(int i = a3 - 4; i <= a3 + 4; ++i)
    {
        if(i >= 0 && i < this->Unk24)
        {
            for(int j = a4 - 4; j <= a4 + 4; ++j)
            {
                if(j >= 0 && j < this->Unk28)
                {
                    for(CCharacter *k = this->Unk36[i][j].Unk0; k; k = k->Unk404)
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
    }

    return true;
}

bool CRoom::MoveChar(CCharacter *a2, char a3, float a4, float a5, float a6, float a7, __tagMsgMoveType a8, CCharacter *a9)
{
    signed int v12; // eax@18
    signed int v15; // eax@21
    char v19; // al@51
    char v20; // al@60

    CCharacter *v21; // [sp+18h] [bp-C0h]@71
    CCharacter *v22; // [sp+1Ch] [bp-BCh]@72
    char v23; // [sp+22h] [bp-B6h]@69
    char v24; // [sp+23h] [bp-B5h]@60
    unsigned long long v25; // [sp+24h] [bp-B4h]@39
    int v26; // [sp+2Ch] [bp-ACh]@36
    int v27; // [sp+30h] [bp-A8h]@36
    //char v28; // [sp+34h] [bp-A4h]@35
    //char v29; // [sp+48h] [bp-90h]@35
    //char v30; // [sp+5Ch] [bp-7Ch]@35
    //char v31; // [sp+70h] [bp-68h]@35
    //char v32; // [sp+84h] [bp-54h]@34
    float v33; // [sp+A4h] [bp-34h]@29
    float v34; // [sp+A8h] [bp-30h]@29
    int v35; // [sp+ACh] [bp-2Ch]@18
    short v36; // [sp+B0h] [bp-28h]@18
    short v37; // [sp+B2h] [bp-26h]@18
    short v38; // [sp+B4h] [bp-24h]@20
    int i; // [sp+BCh] [bp-1Ch]@13
    int j; // [sp+C0h] [bp-18h]@14
    CCharacter *v41; // [sp+C4h] [bp-14h]@12
    int v42; // [sp+C8h] [bp-10h]@9
    int v43; // [sp+CCh] [bp-Ch]@9
    int v44; // [sp+D0h] [bp-8h]@6
    char v45; // [sp+D7h] [bp-1h]@1

    v45 = a3;

    if(a2->Unk0 == 1 && !((CNPC *)a2)->Unk472 & 8)
        return false;

    if(!this->IsNotBlocked(a2, a4, a5, 0))
        return false;

    v44 = 0;
    if(a8 >= 0 && a8 <= 2)
        v44 = a8;

    this->PointToCellNum(a4, a5, &v43, &v42);
    v41 = (a2->Unk0) ? 0 : a2;

    if(a2->Unk0 != 1)
    {
LABEL_32:
        if(a2->Unk140 == v43 && a2->Unk144 == v42)
        {
            CNetMsg v32;
            a2->Move(a4, a5, a6, a7, v45);
            MoveMsg(v32, a8, a2);
            return this->SendToCell(v32, a2, 0);
        }

        v38 = a2->Unk140;
        this->CharFromCell(a2);
        a2->Move(a4, a5, a6, a7, v45);
        this->CharToCell(a2, v43, v42);

        CNetMsg v32;
        CNetMsg v31;
        CNetMsg v30;
        CNetMsg v29;
        CNetMsg v28;

        MoveMsg(v32, a8, a2);
        AppearMsg(v31, a2, 0);
        DisappearMsg(v30, a2);

        if((signed int)v38 >= v43)
        {
            v26 = v38;
            v27 = v43;
        }
        else
        {
            v27 = v38;
            v26 = v43;
        }

        //v25 = (SHIDWORD(v38) >= v42) ? __PAIR__(v42, HIDWORD(v38)) : __PAIR__(HIDWORD(v38), v42); // CHEEECK <------------ WTF?

        for(i = v27 - 4; i < 0 || i >= this->Unk24; ++i) // CHEEECK
        {
            if(i > v26 + 4)
                return true;
LABEL_96:
            ;
        }

        //for(j = HIDWORD(v25) - 4; j < 0 || j >= this->Unk28; ++j) // CHEEECK <------------ WTF?
        {
            if(j > (signed int)v25 + 4)
                goto LABEL_96;
LABEL_95:
            ;
        }

        v19 = 0;
        if((signed int)v38 - i < 0)
        {
            if(i - (signed int)v38 > 4)
                goto LABEL_60;
        }
        else
        {
            if((signed int)v38 - i > 4)
                goto LABEL_60;
        }

        //if(HIDWORD(v38) - j < 0) // CHEEECK <------------ WTF?
        {
            //if(j - HIDWORD(v38) > 4) // CHEEECK <------------ WTF?
                goto LABEL_60;
        }
        //else
        {
            //if(HIDWORD(v38) - j > 4) // CHEEECK <------------ WTF?
            {
LABEL_60:
                v24 = v19;
                v20 = 0;
                if(v43 - i < 0)
                {
                    if(i - v43 > 4)
                        goto LABEL_69;
                }
                else
                {
                    if(v43 - i > 4)
                        goto LABEL_69;
                }
                if(v42 - j >= 0)
                {
                    if(v42 - j > 4)
                        goto LABEL_69;
                    goto LABEL_68;
                }
                if(j - v42 <= 4)
LABEL_68:
                    v20 = 1;
LABEL_69:
                v23 = v20;
                if(v24 || v20)
                {
                    v21 = this->Unk36[i][j].Unk0;
                    while(1)
                    {
                        v22 = v21;

                        if(!v21)
                            break;

                        v21 = v21->Unk404;

                        if(v22 != a2)
                        {
                            if(v24)
                            {
                                if(v23)
                                {
                                    if(!v22->Unk0 && ((CPC *)v22)->Unk768)
                                        ((CPC *)v22)->Unk768->WriteToOutput(v32);
                                }
                                else
                                {
                                    if(!v22->Unk0 && ((CPC *)v22)->Unk768)
                                        ((CPC *)v22)->Unk768->WriteToOutput(v30);

                                    DisappearMsg(v28, v22);
                                    if(v41 && ((CPC *)v41)->Unk768)
                                        ((CPC *)v41)->Unk768->WriteToOutput(v28);
                                }
                            }
                            else
                            {
                                if(v23)
                                {
                                    if(!v22->Unk0 && ((CPC *)v22)->Unk768)
                                        ((CPC *)v22)->Unk768->WriteToOutput(v31);

                                    AppearMsg(v29, v22, 0);
                                    if(v41 && ((CPC *)v41)->Unk768)
                                        ((CPC *)v41)->Unk768->WriteToOutput(v29);
                                }
                            }
                        }
                    }
                }
                goto LABEL_95;
            }
        }
        v19 = 1;
        goto LABEL_60;
    }

    CCharacter *c_i, *c_j; // i, j

    c_i = this->Unk36[v43][v42].Unk0;
    do
    {
        while(1)
        {
            c_j = c_i;

            if(!c_i)
                goto LABEL_32;

            c_i = c_j->Unk404;

            if(c_j != a2 && a2->Unk76 > 0)
            {
                if(c_j->Unk120.Unk0 - a4 >= 0.0)
                {
                    v36 = v37 | 0xC00;
                    v35 = c_j->Unk120.Unk0 - a4;
                    v12 = c_j->Unk120.Unk0 - a4;
                }
                else
                {
                    v36 = v37 | 0xC00;
                    v35 = -(c_j->Unk120.Unk0 - a4);
                    v12 = -(c_j->Unk120.Unk0 - a4);
                }

                //HIDWORD(v38) = v12; // CHEEECK <------------ WTF?

                if(c_j->Unk120.Unk4 - a5 >= 0.0)
                {
                    v36 = v37 | 0xC00;
                    v35 = c_j->Unk120.Unk4 - a5;
                    v15 = c_j->Unk120.Unk4 - a5;
                }
                else
                {
                    v36 = v37 | 0xC00;
                    v35 = -(c_j->Unk120.Unk4 - a5);
                    v15 = -(c_j->Unk120.Unk4 - a5);
                }

                //LODWORD(v38) = v15; // CHEEECK <------------ WTF?

                //if(v38 <= 0)
                    break; // BREAK IMMEDIATLY TO AVOID AN INFINITE LOOP
            }
        }

        if(a9 == c_j)
            return true;

        v34 = GetRandom(0, 1) ? 1.5707964 : -1.5707964;
        v33 = cos(a2->Unk120.Unk12 + v34);
        a4 = v33 + a2->Unk120.Unk0;
        v33 = sin(a2->Unk120.Unk12 + v34);
        a5 = v33 + a2->Unk120.Unk4;
    }
    while(this->IsNotBlocked(a2, a4, a5, 0));

    return false;
}

bool CRoom::IsNotBlocked(CCharacter *a2, CCharacter *a3, bool a4)
{
    return this->IsNotBlocked(a2, a3->Unk120.Unk0, a3->Unk120.Unk4, a4);
}

bool CRoom::IsNotBlocked(CCharacter *a2, float a3, float a4, bool a5)
{
    /*long double v5; // fst7@1
    __int16 v6; // fps@1
    char v7; // c0@1
    char v8; // c2@1
    char v9; // c3@1
    long double v10; // fst7@3
    __int16 v11; // fps@3
    char v12; // c0@3
    char v13; // c2@3
    char v14; // c3@3
    char result; // al@5
    __int16 v16; // fps@10
    char v17; // c0@10
    char v18; // c2@10
    char v19; // c3@10        char v5; // [sp+1Ch] [bp-2Ch]@2
    int j; // [sp+30h] [bp-18h]@7
    int i; // [sp+34h] [bp-14h]@2
    __int16 v20; // fps@13
    char v21; // c0@13
    char v22; // c2@13
    char v23; // c3@13
    float v24; // ST2C_4@23
    __int16 v25; // fps@22
    long double v26; // fst7@22
    char v27; // c0@22
    char v28; // c2@22
    char v29; // c3@22
    float v30; // ST0C_4@23
    float v31; // ST08_4@23
    float v32; // ST30_4@30
    __int16 v33; // fps@29
    long double v34; // fst7@29
    char v35; // c0@29
    char v36; // c2@29
    char v37; // c3@29
    float v38; // ST0C_4@30
    float v39; // ST08_4@30
    char v40; // [sp+1Bh] [bp-2Dh]@23
    char v41; // [sp+1Bh] [bp-2Dh]@30
    signed int j; // [sp+24h] [bp-24h]@21
    signed int i; // [sp+24h] [bp-24h]@28
    float v44; // [sp+28h] [bp-20h]@16
    float v45; // [sp+2Ch] [bp-1Ch]@16
    float v46; // [sp+34h] [bp-14h]@14
    float v47; // [sp+38h] [bp-10h]@11
    float v48; // [sp+3Ch] [bp-Ch]@11
    signed int v49; // [sp+40h] [bp-8h]@8

    //v5 = (long double)*(signed int *)(a1 + 16) * 12.0;
    //UNDEF(v6);
    //v7 = a3 < v5;
    //v8 = 0;
    //v9 = a3 == v5;
    //if((HIBYTE(v6) & 0x45) != 1 && a3 < (long double)(*(_DWORD *)(a1 + 24) + *(_DWORD *)(a1 + 16)) * 12.0 && (v10 = (long double)*(signed int *)(a1 + 20) * 12.0, UNDEF(v11), v12 = a4 < v10, v13 = 0, v14 = a4 == v10, (HIBYTE(v11) & 0x45) != 1) && a4 < (long double)(*(_DWORD *)(a1 + 28) + *(_DWORD *)(a1 + 20)) * 12.0)
    {
        if(a2->Unk0)
        {
            v49 = 0;
            if(a5)
                v49 = 1;
            UNDEF(v16);
            v17 = a3 < (long double)*(float *)(a2 + 120);
            v18 = 0;
            v19 = a3 == *(float *)(a2 + 120);
            if((HIBYTE(v16) & 0x45) == 1)
            {
                v48 = a3;
                v47 = *(float *)(a2 + 120);
            }
            else
            {
                v48 = *(float *)(a2 + 120);
                v47 = a3;
            }
            UNDEF(v20);
            v21 = a4 < (long double)*(float *)(a2 + 124);
            v22 = 0;
            v23 = a4 == *(float *)(a2 + 124);
            if((HIBYTE(v20) & 0x45) == 1)
                v46 = a4;
            else
                v46 = *(float *)(a2 + 124);
            v45 = *(float *)(a2 + 120) - a3;
            v44 = *(float *)(a2 + 124) - a4;
            if(v45 >= 0.0000099999997 || v44 >= 0.0000099999997)
            {
                if(*(_DWORD *)a2 == 1)
                {
                    if(v45 <= (long double)v44)
                    {
                        for(i = v49; ; ++i)
                        {
                            v34 = (long double)i * 1.0 + v46;
                            UNDEF(v33);
                            v35 = v34 < v47;
                            v36 = 0;
                            v37 = v34 == v47;
                            if((HIBYTE(v33) & 0x45) != 1)
                                break;
                            v38 = (long double)i * 1.0 + v46;
                            v32 = v45 / v44;
                            v39 = (long double)i * v32 + v48;
                            v41 = CArea::GetAttr(*(_DWORD *)a1, *(_BYTE *)(a1 + 12), v39, v38);
                            if(v41 != 2 && v41 != 3)
                                return 0;
                        }
                    }
                    else
                    {
                        for(j = v49; ; ++j)
                        {
                            v26 = (long double)j * 1.0 + v48;
                            UNDEF(v25);
                            v27 = v26 < v47;
                            v28 = 0;
                            v29 = v26 == v47;
                            if((HIBYTE(v25) & 0x45) != 1)
                                break;
                            v24 = v44 / v45;
                            v30 = (long double)j * v24 + v46;
                            v31 = (long double)j * 1.0 + v48;
                            v40 = CArea::GetAttr(*(_DWORD *)a1, *(_BYTE *)(a1 + 12), v31, v30);
                            if(v40 != 2 && v40 != 3)
                                return 0;
                        }
                    }
                }
                result = 1;
            }
            else
            {
                result = 1;
            }
        }
        else
        {
            result = 1;
        }
    }
    else
    {
        result = 0;
    }
    return result;*/

    return true; // SOMETHING STRANGE IN THIS FUNCTION
}

void CRoom::CharFromCell(CCharacter *a2)
{
    if(a2->Unk140 >= 0)
    {
        this->Unk36[a2->Unk140][a2->Unk144].CharFromCell(a2);
        a2->Unk416 = 0;
        a2->Unk140 = -100;
        a2->Unk144 = -100;

        if(!a2->Unk0)
            --this->Unk68;
    }
}

void CRoom::SendCellInfo(CPC *a2)
{
    CCharacter *v3; // [sp+14h] [bp-34h]@12
    CCharacter *v4; // [sp+18h] [bp-30h]@13
    int v8; // [sp+38h] [bp-10h]@2
    int v9; // [sp+3Ch] [bp-Ch]@2
    int v10; // [sp+40h] [bp-8h]@2
    int v11; // [sp+44h] [bp-4h]@2

    if(a2->Unk140 >= 0)
    {
        v11 = a2->Unk140 - 4;
        v10 = a2->Unk140 + 4;
        v9 = a2->Unk144 - 4;
        v8 = a2->Unk144 + 4;

        CNetMsg v5;

        for(int i = v11; i <= v10; ++i)
        {
            if(i >= 0 && i <= this->Unk24)
            {
                for(int j = v9; j <= v8; ++j)
                {
                    if(j >= 0 && j <= this->Unk28)
                    {
                        v3 = this->Unk36[i][j].Unk0;

                        while(1)
                        {
                            v4 = v3;

                            if(!v3)
                                break;

                            v3 = v3->Unk404;

                            if(v4 != a2 && (v4->Unk76 > 0 || !v4->Unk0))
                            {
                                AppearMsg(v5, v4, 0);

                                if(a2->Unk768)
                                    a2->Unk768->WriteToOutput(v5);
                            }
                        }
                    }
                }
            }
        }
    }
}
