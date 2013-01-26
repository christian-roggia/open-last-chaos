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
#include "../Battle.h"

void do_Attack(CPC *a1, CNetMsg &a2)
{
    char v37; // [sp+17h] [bp-49h]@22
    float v38; // [sp+18h] [bp-48h]@22
    float v39; // [sp+1Ch] [bp-44h]@22
    float v40; // [sp+30h] [bp-30h]@22
    CPC *v42; // [sp+44h] [bp-1Ch]@8
    CCharacter *v43; // [sp+48h] [bp-18h]@4
    CCharacter *v44; // [sp+4Ch] [bp-14h]@4
    CArea *v45; // [sp+50h] [bp-10h]@3
    int dest; // [sp+54h] [bp-Ch]@1
    int v47; // [sp+58h] [bp-8h]@1
    char v48; // [sp+5Ch] [bp-4h]@1
    char v49; // [sp+5Dh] [bp-3h]@1
    char v50; // [sp+5Eh] [bp-2h]@1
    char v51; // [sp+5Fh] [bp-1h]@1

    v48 = 0;
    a2.__rs(v50); // (char &) CHECKED
    a2.__rs(dest); // (int &) CHECKED
    a2.__rs(v51); // (char &) CHECKED
    a2.__rs(v47); // (int &) CHECKED
    a2.__rs(v49); // (char &) CHECKED
    a2.__rs(v48); // (char &) CHECKED

    if(v48 > 5)
        v48 = 5;

    v45 = a1->Unk412;

    if(!v45)
        return;

    v44 = v45->FindCharInCell(a1, dest, v50, 0);
    v43 = v45->FindCharInCell(a1, v47, v51, 0);

    if(!v44 || !v43)
        return;

    if(v44->Unk0 == 0)
    {
        v42 = (CPC *)v44;

        //v8 = GetDistance(v44, v43);
        //v10 = ((CPC *)v44)->Unk736 + 1.5;
        //UNDEF(v9);
        //v11 = v10 < v8;
        //v12 = 0;
        //v13 = v10 == v8;
        //if((HIBYTE(v9) & 0x45) == 1 || gserver.Unk41248 - *(_DWORD *)(v42 + 788) + 3 < *(_BYTE *)(v42 + 102))

        if(GetDistance(v44, v43) > ((CPC *)v44)->Unk736 + 1.5 || gserver.Unk41248 - v42->Unk788 + 3 < v42->Unk102)
        {
            g_gamelogbuffer.__ls(init("HACK ATTACK", v42->Unk8, v42->Unk768->Unk4));
            g_gamelogbuffer.__ls(gserver.Unk41248 - v42->Unk788);
            g_gamelogbuffer.__ls(delim);
            g_gamelogbuffer.__ls(v42->Unk102);
            g_gamelogbuffer.__ls(end);

            v42->Unk768->IncreaseHackCount(1);
            return;
        }

        v42->Unk788 = gserver.Unk41248;
    }

    if(v50)
    {
        if(v50 == 1)
        {
            if(v51)
            {
                if(v51 == 1)
                {
                    while(v43)
                    {
                        AttackNPC((CNPC *)v44, (CNPC *)v43, 0, 0, 0);
                        if(v44->Unk412->Unk4->Unk0 != 2 && (v44->Unk412->Unk4->Unk0 < 2 || v44->Unk412->Unk4->Unk0 > 6 || v44->Unk412->Unk4->Unk0 < 5))
                        {
                            v43 = 0;
                        }
                        else
                        {
                            if(v48)
                            {
                                --v48;

                                int v42_2;
                                a2.__rs(v42_2); // CHECK
                                v43 = v45->FindCharInCell(a1, v42_2, v51, 0);
                            }
                            else
                            {
                                v43 = 0;
                            }
                        }
                    }
                }
            }
            else
            {
                while(v43)
                {
                    AttackChar((CNPC *)v44, (CPC *)v43, 0, 0, 0);
                    if(v44->Unk412->Unk4->Unk0  != 2 && (v44->Unk412->Unk4->Unk0  < 2 || v44->Unk412->Unk4->Unk0  > 6 || v44->Unk412->Unk4->Unk0  < 5))
                    {
                        v43 = 0;
                    }
                    else
                    {
                        if(v48)
                        {
                            --v48;

                            int v42_2;
                            a2.__rs(v42_2); // CHECK
                            v43 = v45->FindCharInCell(a1, v42_2, v51, 0);
                        }
                        else
                        {
                            v43 = 0;
                        }
                    }
                }
            }
        }
    }
    else
    {
        if(a1->Unk76 > 0)
        {
            if(!a1->Unk474)
            {
                if(a1->CanAttack())
                {
                    if(v51)
                    {
                        if(v51 == 1)
                        {
                            while(v43)
                            {
                                v40 = atan2(v43->Unk120.Unk4 - v44->Unk120.Unk4, v43->Unk120.Unk0 - v44->Unk120.Unk0);
                                v39 = v44->Unk120.Unk0;
                                v38 = v44->Unk120.Unk4;
                                v37 = 0;

                                while(1)
                                {
                                    //v23 = GetDistance(v39, v43->Unk120.Unk0, v38, v43->Unk120.Unk4, v44->Unk412->GetHeight(v44->Unk120.Unk16, v39, v38), ((v43 && v43->Unk412) ? v43->Unk412->GetHeight(v43->Unk120.Unk16, v43->Unk120.Unk0, v43->Unk120.Unk4) : 0.0));
                                    //UNDEF(v24);
                                    //v25 = 0.4 < v23;
                                    //v26 = 0;
                                    //v27 = 0.4 == v23;
                                    //if((HIBYTE(v24) & 0x45) != 1)

                                    if(GetDistance(v39, v43->Unk120.Unk0, v38, v43->Unk120.Unk4, v44->Unk412->GetHeight(v44->Unk120.Unk16, v39, v38), ((v43 && v43->Unk412) ? v43->Unk412->GetHeight(v43->Unk120.Unk16, v43->Unk120.Unk0, v43->Unk120.Unk4) : 0.0)) <= 0.4)
                                        break;

                                    v39 = cos(v40) * 0.5 + v39;
                                    v38 = sin(v40) * 0.5 + v38;

                                    if(v44->Unk412->GetAttr(v43->Unk120.Unk16, v39, v38) == -1)
                                    {
                                        v37 = 1;
                                        break;
                                    }
                                }

                                if(!v37)
                                    AttackMob((CPC *)v43, (CNPC *)v44, 0, 0, 0);

                                if(v44->Unk412->Unk4->Unk0 != 2 && (v44->Unk412->Unk4->Unk0 < 2 || v44->Unk412->Unk4->Unk0 > 6 || v44->Unk412->Unk4->Unk0 < 5))
                                {
                                    v43 = 0;
                                }
                                else
                                {
                                    if(v48)
                                    {
                                        --v48;

                                        int v42_2;
                                        a2.__rs(v42_2); // CHECK
                                        v43 = v45->FindCharInCell(a1, v42_2, v51, 0);

                                        if(v43)
                                        {
                                            //v30 = GetDistance(v44, v43);
                                            //v32 = a1->Unk736 + 1.5;
                                            //UNDEF(v31);
                                            //v33 = v32 < v30;
                                            //v34 = 0;
                                            //v35 = v32 == v30;
                                            //if((HIBYTE(v31) & 0x45) == 1)

                                            if(GetDistance(v44, v43) > a1->Unk736 + 1.5)
                                                v43 = 0;
                                        }
                                    }
                                    else
                                    {
                                        v43 = 0;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        AttackPvP((CPC *)v44, (CPC *)v43, 0, 0, 0);
                    }
                }
            }
        }
    }
}
