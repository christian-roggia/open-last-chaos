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

#include "Battle.h"

bool AttackMob(CPC *a1, CNPC *a2, _tagDamageType a2_1, CSkill *a3, int a4)
{
    signed long long v7; // [sp+2Ch] [bp-48h]@66
    unsigned int v8; // [sp+34h] [bp-40h]@46
    CItem *v9; // [sp+34h] [bp-40h]@58
    int v10; // [sp+34h] [bp-40h]@63
    CItem *v11; // [sp+38h] [bp-3Ch]@46
    CItem *v12; // [sp+38h] [bp-3Ch]@65
    CCharacter *v14; // [sp+40h] [bp-34h]@41
    int i; // [sp+58h] [bp-1Ch]@26
    int v17; // [sp+5Ch] [bp-18h]@22
    char v18; // [sp+63h] [bp-11h]@22
    CMagicLevelProto *v19; // [sp+64h] [bp-10h]@17
    CMagicProto *v20; // [sp+68h] [bp-Ch]@17
    CSkillLevelProto *v21; // [sp+6Ch] [bp-8h]@17
    signed int v23; // [sp+84h] [bp+10h]@20

    if(a1->IsInPeaceZone() || a2->IsInPeaceZone())
        return false;

    a2->Unk148.CancelSleep();

    if(a2->Unk464->Unk92 & 1 || a2->Unk464->Unk92 & 0x20 || a2->Unk464->Unk92 & 0x80 || a2->Unk464->Unk92 & 0x100 || a2->Unk464->Unk92 & 0x200 || a2->Unk464->Unk92 & 0x400 || a2->Unk464->Unk92 & 0x800 || a2->Unk464->Unk92 & 0x1000 || a2->Unk464->Unk92 & 0x4000 || a2->Unk464->Unk92 & 0x8000)
        return false;

    if(a1->Unk474)
    {
        DelAttackList(a1);
        return false;
    }

    v21 = 0;
    v20 = 0;
    v19 = 0;

    if(a3 && !GetSkillPrototypes(a3->Unk0, a3->Unk4, a4, (const CSkillLevelProto **)&v21, (const CMagicProto **)&v20, (const CMagicLevelProto **)&v19))
        return false;

    v23 = a1->GetAttackType(a3->Unk0);
    if(v23 == -1)
        return false;

    v18 = SelectHitType(a1, a2, v23, GetHitType(a1, a2, v23), v20, v19);
    v17 = GetDamage(a1, a2, v23, v18, v20, v19);
    ApplyHate(a1, a2, v18, v17);
    ApplyDamage(a1, a2, v23, (CSkillProto *)a3->Unk0, v17, v18);

    if(v18 != 1)
    {
        if(a1->Unk60 - a2->Unk60 <= 4)
        {
            ((CPC *)a1)->Unk752 -= 15;
            if(((CPC *)a1)->Unk752 <= 0)
            {
                ((CPC *)a1)->Unk752 = 5000;
                ((CPC *)a1)->SettingItemOption();
            }
        }

        for(i = 7; i <= 7; ++i)
        {
            if(a1->Unk1284[i] && a1->Unk1284[i]->Unk20->Unk72 == -1)
            {
                a1->Unk1284[i]->Unk64 -= 10;
                if(a1->Unk1284[i]->Unk64 <= 0)
                {
                    a1->Unk1284[i]->Unk64 = 0;
                    ((CPC *)a1)->CalcStatus(true);
                }
            }
        }

        if(a1->Unk412->GetAttr(a1->Unk120.Unk16, a1->Unk120.Unk0, a1->Unk120.Unk4))
        {
            a2->Unk526 = 1;
            AddAttackList(a1, a2, 0);
        }
    }

    if(a2->Unk76 > 0)
        return false;

    if(a1->Unk1852 < -9)
    {
        if(a2->Unk60 >= a1->Unk60 - 5)
        {
            ++a1->Unk1876;
            if(a1->Unk1876 > 24)
            {
                a1->Unk1876 = 0;
                ++a1->Unk1852;

                CNetMsg v15;

                CharStatusMsg(v15, a1, 0);
                a1->Unk412->SendToCell(v15, a1, 0, 4);
                a1->Unk473 = 1;
            }
        }
    }

    i = -1;
    v14 = FindPreferencePC(a2, &i);
    DivisionExpSP(a2);

    for(int j = 0; j <= 3; ++j)
    {
        if(a2->Unk464->Unk264 > 0 && i != -1 && i - a2->Unk60 <= 5)
        {
            v11 = 0;
            v8 = GetRandom(0, 19);

            if(a2->Unk464->Unk104[v8] != -1 && (int)GetRandom(1, 10000) <= a2->Unk464->Unk184[v8])
                v11 = a2->Unk412->DropItem(a2->Unk464->Unk104[v8], a2, 0, 0, 1, true);

            if(v11)
            {
                CNetMsg v15;

                ItemDropMsg(v15, a2, v11);
                a2->Unk412->SendToCell(v15, v11->Unk176.Unk16, v11->Unk196, v11->Unk200, 4);
                v11->Unk216 = v14 ? v14->Unk4 : -1;
            }
        }
    }

    if(a2->Unk60 > 12)
    {
        if(a2->Unk60 <= 27)
        {
            if(GetRandom(1, 10000) <= 50)
            {
                v9 = a2->Unk412->DropItem(gserver.Unk41208.Unk32->Unk0, a2, 0, 0, 1, false); // *unk_8104598
                if(v9)
                {
                    CNetMsg v15;

                    ItemDropMsg(v15, a2, v9);
                    a2->Unk412->SendToCell(v15, v9->Unk176.Unk16, v9->Unk196, v9->Unk200, 4);
                    v9->Unk216 = v14 ? v14->Unk4 : -1;
                }
            }
        }
    }

    v10 = 8000;
    if(i != -1)
        v10 = a2->Unk60 - i + 8000;
    v12 = 0;

    if(GetRandom(1, 10000) <= v10)
    {
        v7 = (a2->Unk464->Unk64 * GetRandom(50, 150)) / 100;

        if(gserver.Unk452260)
            v7 *= 2;

        v12 = a2->Unk412->DropItem(gserver.Unk41208.Unk12->Unk0, a2, 0, 0, v7, false); // *unk_8104584
    }

    if(v12)
    {
        CNetMsg v15;

        ItemDropMsg(v15, a2, v12);
        a2->Unk412->SendToCell(v15, v12->Unk176.Unk16, v12->Unk196, v12->Unk200, 4);
        v12->Unk216 = v14 ? v14->Unk4 : -1;
    }

    for(int k = 0; k <= 9; ++k)
    {
        if(a1->Unk1900.Unk0[k] && a1->Unk1900.Unk40[k] && (!a1->Unk1900.Unk0[k]->Unk0->Unk4 || a1->Unk1900.Unk0[k]->Unk0->Unk4 == 1 || a1->Unk1900.Unk0[k]->Unk0->Unk4 == 3 || a1->Unk1900.Unk0[k]->Unk0->Unk4 == 4))
            a1->Unk1900.Unk0[k]->QuestUpdateData(a1, a2);
    }

    DelAttackList(a2);
    a1->Unk412->CharFromCell(a2);
    a1->Unk412->DelNPC(a2);

    return true;
}

bool AttackChar(CNPC *a1, CPC *a2, _tagDamageType a3, CSkill *a4, int a5)
{
    char v7; // ST47_1@12
    CMagicLevelProto*v10; // [sp+18h] [bp-10h]@7
    CMagicProto*v11; // [sp+1Ch] [bp-Ch]@7
    CSkillLevelProto*v12; // [sp+20h] [bp-8h]@7
    signed int v14; // [sp+38h] [bp+10h]@10

    if(a2->Unk76 <= 0 || a2->Unk474)
        return false;

    if(a1->IsInPeaceZone() || a2->IsInPeaceZone())
        return false;

    a2->Unk148.CancelSleep();

    v12 = 0;
    v11 = 0;
    v10 = 0;

    if(a4 && !GetSkillPrototypes(a4->Unk0, a4->Unk4, a5, (const CSkillLevelProto**)&v12, (const CMagicProto**)&v11, (const CMagicLevelProto**)&v10))
        return false;

    v14 = a1->GetAttackType(a4->Unk0);
    if(v14 == -1)
        return false;

    v7 = SelectHitType(a1, a2, v14, GetHitType(a1, a2, v14), v11, v10);
    ApplyDamage(a1, a2, v14, (CSkillProto *)a4->Unk0, GetDamage(a1, a2, v14, v7, v11, v10), v7);

    if(v7 != 1)
    {
        if(a2->Unk60 - a1->Unk60 <= 4)
        {
            a2->Unk752 -= 3;
            if(a2->Unk752 <= 0)
            {
                a2->Unk752 = 5000;
                a2->SettingItemOption();
            }
        }

        for(int i = 7; i <= 7; ++i)
        {
            if(a2->Unk1284[i] && a2->Unk1284[i]->Unk20->Unk72 == -1)
            {
                a2->Unk1284[i]->Unk64 -= 10;
                if(a2->Unk1284[i]->Unk64 <= 0)
                {
                    a2->Unk1284[i]->Unk64 = 0;
                    a2->CalcStatus(true);
                }
            }
        }
    }

    if(a2->Unk76 > 0)
        return false;

    ProcDeathPC(a2, 1);
    return true;
}

//AttackPvP__FP3CPCT014_tagDamageTypeP6CSkilli
bool AttackPvP(CPC *a1, CPC *a2, _tagDamageType a3, CSkill *a4, int a5)
{
    char v8; // [sp+1Bh] [bp-2Dh]@34
    int v10; // [sp+30h] [bp-18h]@31
    char v11; // [sp+37h] [bp-11h]@31
    CMagicLevelProto *v12; // [sp+38h] [bp-10h]@26
    CMagicProto *v13; // [sp+3Ch] [bp-Ch]@26
    CSkillLevelProto *v14; // [sp+40h] [bp-8h]@26
    signed int v16; // [sp+58h] [bp+10h]@29

    if(a1->Unk76 <= 0 || a2->Unk76 <= 0 || a1->Unk474 || a2->Unk474 || (!a1->IsSetPlayerState(8) || !a1->IsSetPlayerState(32)))
        return false;

    if(a1->IsInPeaceZone() || a2->IsInPeaceZone())
        return false;

    if(a2->Unk60 <= 15)
        return false;

    if(a1->IsSetPlayerState(32) && !IsRaList(a1, a2))
        return false;

    if(IsRaList(a1, a2))
    {
        for(CRaChar *i = a2->Unk1880; i; i = i->Unk12)
        {
            if(i->Unk0 == a1 && i->Unk8)
            {
                i->Unk4 = 200;
                break;
            }
        }
    }
    else
    {
        if(!a2->IsSetPlayerState(8))
            AddRaList(a1, a2);
    }

    a2->Unk148.CancelSleep();

    v14 = 0;
    v13 = 0;
    v12 = 0;

    if(a4 && !GetSkillPrototypes(a4->Unk0, a4->Unk4, a5, (const CSkillLevelProto **)&v14, (const CMagicProto **)&v13, (const CMagicLevelProto **)&v12))
        return false;

    v16 = a1->GetAttackType(a4->Unk0);
    if(v16 == -1)
        return false;

    v11 = SelectHitType(a1, a2, v16, GetHitType(a1, a2, v16), v13, v12);
    v10 = GetDamage(a1, a2, v16, v11, v13, v12);
    ApplyDamage(a1, a2, v16, (CSkillProto *)a4->Unk0, v10, v11);
    if(a2->Unk76 > 0)
        return false;

    if(a2->IsSetPlayerState(64))
    {
        a2->Unk2388 = -1;
        a2->Unk2384 = 0;
        a2->ResetPlayerState(64);

        CNetMsg v9;
        ChangeStopMsg(v9, a2);
        a2->Unk412->SendToCell(v9, a2, 1, 4);
    }

    v8 = 0;

    if(a2->IsSetPlayerState(8) || a2->Unk1852 < -9)
        v8 = 1;

    for(CRaChar *j = a1->Unk1880; j; j = j->Unk12)
    {
        if(j->Unk0 == a2)
        {
            if(!j->Unk8)
                CalcPKPoint(a1, a2);

            break;
        }
    }

    DelRaList(a2, 0);
    ProcDeathPC(a2, v8);

    return true;
}

//AttackNPC__FP4CNPCT014_tagDamageTypeP6CSkilli
bool AttackNPC(CNPC *a1, CNPC *a2, _tagDamageType a3, CSkill *a4, int a5)
{
    int v36; // [sp+50h] [bp-38h]@39
    int v37; // [sp+54h] [bp-34h]@39
    CCharacter *v42; // [sp+68h] [bp-20h]@13
    int v44; // [sp+70h] [bp-18h]@11
    char v45; // [sp+77h] [bp-11h]@11
    const CMagicLevelProto *v46; // [sp+78h] [bp-10h]@6
    const CMagicProto *v47; // [sp+7Ch] [bp-Ch]@6
    const CSkillLevelProto *v48; // [sp+80h] [bp-8h]@6
    const CSkillProto *v49; // [sp+84h] [bp-4h]@6
    _tagDamageType v50; // [sp+98h] [bp+10h]@9

    if(a2->Unk76 <= 0)
        return true;

    if(a1->IsInPeaceZone() || a2->IsInPeaceZone())
        return false;

    a2->Unk148.CancelSleep();

    v49 = 0;
    v48 = 0;
    v47 = 0;
    v46 = 0;

    if(a4)
    {
        v49 = a4->Unk0;
        if(!GetSkillPrototypes(v49, a4->Unk4, a5, &v48, &v47, &v46))
            return false;
    }

    v50 = a1->GetAttackType(v49); //v50 = (*(int (**)(int, int))(*(_DWORD *)(a1->Unk460) + 32))(a1, v49);
    if(v50 == -1)
        return false;

    v45 = SelectHitType(a1, a2, v50, GetHitType(a1, a2, v50), (CMagicProto *)v47, (CMagicLevelProto *)v46);
    v44 = GetDamage(a1, a2, v50, v45, (CMagicProto *)v47, (CMagicLevelProto *)v46);
    ApplyDamage(a1, a2, v50, (CSkillProto *)v49, v44, v45);

    if(a2->Unk76 > 0)
        return false;

    if(a2->Unk408->Unk0 == 5)
    {
        CCharacter *k = 0;
        v42 = 0;

        for(int i = 0; i < a2->Unk412->Unk12; ++i)
        {
            for(int j = 0; j < a2->Unk412->Unk16; ++j)
            {
                for(k = a2->Unk412->Unk28[i][j].Unk0; k; k = k->Unk404)
                {
                    if(!k->Unk0 && k->Unk76 > 0)
                    {
                        v42 = k;
                        break;
                    }
                }
            }
        }

        if(!v42)
            return false;

        for(int i = 0; i <= 9; ++i)
        {
            // if(((CPC *)v42)->Unk1900.Unk0[i] && v42 != -1940 && ((CPC *)v42)->Unk1900.Unk0[i]->Unk0->Unk4 == 4) -> v42 != -1940 WHAT IS THIS?
            if(((CPC *)v42)->Unk1900.Unk0[i] && ((CPC *)v42)->Unk1900.Unk0[i]->Unk0->Unk4 == 4)
            {
                for(int l = 0; l <= 2; ++l)
                {
                    if(!((CPC *)v42)->Unk1900.Unk0[i]->Unk0->Unk76[l] && ((CPC *)v42)->Unk1900.Unk0[i]->Unk0->Unk88[l] == a2->Unk464->Unk0)
                    {
                        for(int m = 0; m <= 2; ++m)
                        {
                            if(((CPC *)v42)->Unk1900.Unk0[i]->Unk0->Unk76[m] == 1)
                            {
                                if(((CPC *)v42)->Unk880.FindItem(&v37, &v36, ((CPC *)v42)->Unk1900.Unk0[i]->Unk0->Unk88[m], 0, 0))
                                {
                                    CItem *v33 = ((CPC *)v42)->Unk880.GetItem(v37, v36);
                                    if(v33)
                                    {
                                        if(((CPC *)v42)->Unk1900.Unk0[i]->Unk0->Unk100[m] <= v33->Count())
                                        {
                                            CNetMsg v34;

                                            ((CPC *)v42)->Unk880.Decrease(v33, ((CPC *)v42)->Unk1900.Unk0[i]->Unk0->Unk100[m]); // CHECK MINUS

                                            if(v33->Count() <= 0) // SOME SHIT FOR LONG LONG THERE
                                            {
                                                ItemDeleteMsg(v34, v33);
                                                if(((CPC *)v42)->Unk768)
                                                    ((CPC *)v42)->Unk768->WriteToOutput(v34);
                                                ((CPC *)v42)->RemoveItemFromQuickSlot(v33);
                                                ((CPC *)v42)->Unk880.Remove(v33, 1, 1);
                                            }
                                            else
                                            {
                                                ItemUpdateMsg(v34, v33, -((CPC *)v42)->Unk1900.Unk0[i]->Unk0->Unk100[m]);
                                                if(((CPC *)v42)->Unk768)
                                                    ((CPC *)v42)->Unk768->WriteToOutput(v34);
                                            }
                                        }
                                    }
                                }

                                g_gamelogbuffer.__ls(init("QUEST FAIL"));
                                g_gamelogbuffer.__ls(v42->Unk8);
                                g_gamelogbuffer.__ls(delim);
                                g_gamelogbuffer.__ls(((CPC *)v42)->Unk1900.Unk0[i]->Unk0->Unk0);
                                g_gamelogbuffer.__ls(end);

                                CNetMsg v32;
                                QuestFailMsg(v32, ((CPC *)v42)->Unk1900.Unk0[i]);
                                ((CPC *)v42)->Unk1900.DelQuest((CPC *)v42, ((CPC *)v42)->Unk1900.Unk0[i]);

                                if(((CPC *)v42)->Unk768)
                                    ((CPC *)v42)->Unk768->WriteToOutput(v32);

                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    a1->Unk412->CharFromCell(a2);
    a1->Unk412->DelNPC(a2);

    return true;
}

void ProcDeathPC(CPC *a1, bool a2)
{
    char s[40]; // [sp+ACh] [bp-4Ch]@27
    char v12; // [sp+EBh] [bp-Dh]@16
    int v13; // [sp+ECh] [bp-Ch]@2
    long long v14; // [sp+F0h] [bp-8h]@2

    if(a1->Unk76 <= 0)
    {
        v14 = 0LL;
        v13 = 0;

        if(a1->Unk408->Unk0 == 2 || a1->Unk408->Unk0 >= 2 && a1->Unk408->Unk0 <= 6 && a1->Unk408->Unk0 >= 5)
            a2 = 0;

        if(a2)
        {
            if(a1->Unk60 > 10)
            {
                if(a1->Unk60 > 20)
                {
                    if(a1->Unk60 > 35)
                    {
                        v14 = GetLevelupExp(a1->Unk60) / 50;
                        v13 = a1->Unk72 / 50;
                    }
                    else
                    {
                        v14 = 300 * GetLevelupExp(a1->Unk60) / 10000;
                        v13 = 300LL * a1->Unk72 / 10000;
                    }
                }
                else
                {
                    v14 = GetLevelupExp(a1->Unk60) / 20;
                    v13 = a1->Unk72 / 20;
                }
            }
            else
            {
                GetLevelupExp(a1->Unk60);
                v14 = 0LL;
                v13 = 0;
            }

            if(a1->Unk1852 >= -9)
            {
                if(v14 > a1->Unk64)
                    v14 = a1->Unk64;
            }
            else
            {
                v12 = 0;
                CNetMsg v11;
                if(a1->Unk1852 > -130)
                {
                    if(a1->Unk1852 > -100)
                    {
                        if(a1->Unk1852 > -70)
                        {
                            if(a1->Unk1852 > -40)
                            {
                                if(a1->Unk1852 <= -10)
                                {
                                    v14 = 125 * v14 / 100;
                                    v12 = GetRandom(1, 100) <= 5;
                                }
                            }
                            else
                            {
                                v14 = 150 * v14 / 100;
                                v12 = GetRandom(1, 100) <= 7;
                            }
                        }
                        else
                        {
                            v14 = 175 * v14 / 100;
                            v12 = GetRandom(1, 100) <= 9;
                        }
                    }
                    else
                    {
                        v14 *= 2LL;
                        v12 = GetRandom(1, 100) <= 11;
                    }
                }
                else
                {
                    v14 = 225 * v14 / 100;
                    v12 = GetRandom(1, 100) <= 13;
                }

                if(v12)
                {
                    memset(s, 0, 40);
                    for(int i = 0; i <= 9; ++i);
                }

                if(v14 < 0)
                    v14 = 0LL;

                a1->Unk1852 += 5;
                if(a1->Unk1852 > 0)
                    a1->Unk1852 = 0;

                CharStatusMsg(v11, a1, 0);

                a1->Unk412->SendToCell(v11, a1, 0, 4);
                a1->Unk473 = 1;
                a1->CalcStatus(true);
            }
        }

        if(a2)
        {
            if(v14 < 0)
                v14 = 0LL;

            if(v13 < 0)
                v13 = 0;

            a1->Unk64 -= v14;
            a1->Unk72 -= v13;

            if(a1->Unk72 < 0)
                a1->Unk72 = 0;

            a1->Unk473 = 1;
        }

        for(int j = 7; j <= 7; ++j)
        {
            if(a1->Unk1284[j] && a1->Unk1284[j]->Unk20->Unk72 == -1)
            {
                a1->Unk1284[j]->Unk64 -= 200;
                if(a1->Unk1284[j]->Unk64 <= 0)
                {
                    a1->Unk1284[j]->Unk64 = 0;
                    a1->CalcStatus(1);
                }
            }
        }

        for(CAttackChar *k = a1->Unk396; k; k = k->Unk20)
        {
            for(CAttackChar *l = k->Unk16->Unk396; l; l = l->Unk20)
            {
                if(l->Unk16 == a1)
                {
                    l->Unk4 = 0;
                    break;
                }
            }
        }

        a1->Unk148.Clear();
        if(a1->IsSetPlayerState(4))
        {
            a1->Unk1356 = 0;
            a1->Unk1360 = -1;
            a1->Unk1364 = -1;
        }

        a1->ResetPlayerState(15);

        g_gamelogbuffer.__ls(init("CHAR_DEATH", a1->Unk8, a1->Unk768->Unk4));
        g_gamelogbuffer.__ls(end);
    }
}

bool CheckInNearCellExt(CCharacter *a1, CCharacter *a2)
{
    if(a1->Unk408->Unk0 != a2->Unk408->Unk0)
        return false;

    if(a1->Unk412->Unk8 != a2->Unk412->Unk8)
        return false;

    if(a1->Unk140 - a2->Unk140 < 0)
    {
        if(a2->Unk140 - a1->Unk140 > 4)
            return false;
    }
    else
    {
        if(a1->Unk140 - a2->Unk140 > 4)
            return false;
    }

    if(a1->Unk144 - a2->Unk144 >= 0)
    {
        if(a1->Unk144 - a2->Unk144 > 4)
            return false;

        return true;
    }

    if(a2->Unk144 - a1->Unk144 <= 4)
        return true;

    return false;
}

//GetHitType__FP10CCharacterT014_tagDamageType
char GetHitType(CCharacter *a1, CCharacter *a2, _tagDamageType a3)
{
    int v5; // [sp+28h] [bp-10h]@1
    int v6; // [sp+2Ch] [bp-Ch]@1
    int v7; // [sp+2Ch] [bp-Ch]@31
    int v8; // [sp+2Ch] [bp-Ch]@39
    int v9; // [sp+30h] [bp-8h]@0
    int v10; // [sp+30h] [bp-8h]@29
    int v11; // [sp+30h] [bp-8h]@35
    int v12; // [sp+30h] [bp-8h]@37

    v6 = 0;
    v5 = 0;
    if(a3 >= 0)
    {
        if(a3 <= 1)
        {
            if(a1->Unk0 == 1)
            {
                v9 = 130 * a1->Unk86 * (a1->Unk60 + 10) / (a2->Unk60 + 10) / (a2->Unk86 + a1->Unk86);
            }
            else
            {
                if(a1->Unk0)
                {
                    v9 = 0;
                }
                else
                {
                    if(a2->Unk0)
                    {
                        if(a2->Unk0 == 1)
                        {
                            if(((CPC *)a1)->Unk477 == 1)
                            {
                                v9 = 200 * a1->Unk86 * (a1->Unk60 + 10) / (a2->Unk60 + 10) / (75 * a2->Unk86 / 100 + a1->Unk86);
                            }
                            else
                            {
                                if(((CPC *)a1)->Unk477 > 1)
                                {
                                    if(((CPC *)a1)->Unk477 == 2)
                                    {
                                        v9 = 200 * a1->Unk86 * (a1->Unk60 + 10) / (a2->Unk60 + 10) / (a2->Unk86 + a1->Unk86);
                                    }
                                    else
                                    {
                                        if(((CPC *)a1)->Unk477 == 3)
                                            v9 = 200 * a1->Unk86 * (a1->Unk60 + 10) / (a2->Unk60 + 10) / (a2->Unk86 + a1->Unk86);
                                    }
                                }
                                else
                                {
                                    if(((CPC *)a1)->Unk477 == 0)
                                        v9 = 200 * a1->Unk86 * (a1->Unk60 + 10) / (a2->Unk60 + 10) / (45 * a2->Unk86 / 100 + a1->Unk86);
                                }
                            }
                        }
                        else
                        {
                            v9 = 0;
                        }
                    }
                    else
                    {
                        if(((CPC *)a1)->Unk477)
                            v9 = 200 * a1->Unk86 * (a1->Unk60 + 10) / (a2->Unk60 + 10) / (a2->Unk86 + a1->Unk86);
                        else
                            v9 = 200 * a1->Unk86 * (a1->Unk60 + 10) / (a2->Unk60 + 10) / (a2->Unk86 / 2 + a1->Unk86);
                    }
                }
            }

            v10 = 100 * v9;

            if(a1->Unk0 == 0)
                v6 = ((CPC *)a1)->Unk616[4] * v10 / 10000 + ((CPC *)a1)->Unk516[4]; // 616 + 16 = 632, 516 + 16 = 532

            v7 = a1->Unk148.Unk40[4] + a1->Unk148.Unk140[4] * v10 / 10000 + v6; // 148 + 40 + 16 = 204, 148 + 140 + 16 = 304

            if(a2->Unk0 == 0)
                v5 = ((CPC *)a2)->Unk616[5] * v10 / 10000 + ((CPC *)a2)->Unk516[5]; // 616 + 20 = 636, 516 + 20 = 536

            v9 = v7 - (a2->Unk148.Unk40[5] + a2->Unk148.Unk140[5] * v10 / 10000 + v5) + v10; // 148 + 40 + 20 = 204, 148 + 140 + 20 = 304
        }
        else
        {
            if(a3 == 2)
            {
                if(a1->Unk0 == 1)
                    v11 = 130 * a1->Unk88 * (a1->Unk60 + 10) / (a2->Unk60 + 10) / (a2->Unk88 + a1->Unk88);
                else
                    v11 = 200 * a1->Unk88 * (a1->Unk60 + 10) / (a2->Unk60 + 10) / (a2->Unk88 + a1->Unk88);
                v12 = 100 * v11;

                if(a1->Unk0 == 0)
                    v6 = ((CPC *)a1)->Unk616[21] * v12 / 10000 + ((CPC *)a1)->Unk516[21]; // 616 + 84 = 700, 516 + 84 = 600

                v8 = a1->Unk148.Unk40[21] + a1->Unk148.Unk140[21] * v12 / 10000 + v6; // 148 + 40 + 84 = 272, 148 + 140 + 84 = 372

                if(a2->Unk0 == 0)
                    v5 = ((CPC *)a2)->Unk616[22] * v12 / 10000 + ((CPC *)a2)->Unk516[22]; // 616 + 88 = 704, 516 + 88 = 604

                v9 = v8 - (a2->Unk148.Unk40[22] + a2->Unk148.Unk140[22] * v12 / 10000 + v5) + v12; // 148 + 40 + 88 = 276, 148 + 140 + 88 = 376
            }
        }
    }

    return (GetRandom(1, 10000) <= v9) ? 126 : 1;
}

int dword_80CE73C[5] = {0x000001F4, 0x000004E2, 0x000003E8, 0x00000384, 0x00000258};
int dword_80CE750[5] = {0x00000002, 0x00000008, 0x00000010, 0x00000020, 0x00000040};

//SelectHitType__FP10CCharacterT014_tagDamageTypecPC11CMagicProtoPC16CMagicLevelProto
int SelectHitType(CCharacter *a1, CCharacter *a2, _tagDamageType a3, char a4, CMagicProto *a5, CMagicLevelProto *a6)
{
    int v7[5]; // [sp+20h] [bp-38h]@18
    int v8[5]; // [sp+34h] [bp-24h]@18
    int v14; // [sp+4Ch] [bp-Ch]@5
    int v15; // [sp+50h] [bp-8h]@4
    char v16; // [sp+57h] [bp-1h]@1

    v16 = a4;
    if(a5 && a6 && !a5->Unk8)
    {
        v15 = a6->Unk4;
        if(a5->Unk5 == 3)
        {
            v14 = ((CPC *)a1)->GetAttackLevel() - a1->Unk60;
            if(v14 <= 20)
            {
                if(v14 <= 15)
                {
                    if(v14 <= 10)
                    {
                        if(v14 > 5)
                            v15 = 85 * v15 / 100;
                    }
                    else
                    {
                        v15 = 70 * v15 / 100;
                    }
                }
                else
                {
                    v15 = 55 * v15 / 100;
                }
            }
            else
            {
                v15 /= 5;
            }
        }

        return (GetRandom(1, 10000) > v15) ? 1 : 4;
    }

    v14 = 0;
    v15 = 10000;

    if(v16 & 1)
        return 1;

    memcpy(v8, dword_80CE73C, 20);
    memcpy(v7, dword_80CE750, 20);

    if(a1->Unk0 == 0)
    {
        v8[3] += ((CPC *)a1)->Unk516[6]  + ((CPC *)a1)->Unk616[6]  * v8[3] / 10000; // 540 = 516 + 24, 640 = 540 + 100
        v8[4] += ((CPC *)a1)->Unk516[14] + ((CPC *)a1)->Unk616[14] * v8[4] / 10000; // 572 = 516 + 56, 672 = 572 + 100
    }

    v8[3] += a1->Unk148.Unk40[6]  + a1->Unk148.Unk140[6]  * v8[3] / 10000; // 212 = 148 + 40 + 24, 312 = 212 + 100
    v8[4] += a1->Unk148.Unk40[14] + a1->Unk148.Unk140[14] * v8[4] / 10000; // 244 = 148 + 40 + 56, 344 = 244 + 100

    if(v8[3] > 2000)
        v8[3] = 2000;

    if(v8[4] > 1000)
        v8[4] = 1000;

    if(a1->Unk0 == 1)
    {
        v8[0] = 2000;
        v8[1] = 2000;
        v8[2] = 0;
        v8[3] = 0;
        v8[4] = 0;
    }

    for(int i = 1; i <= 4; ++i)
        v8[i] += v8[i-1];

    if(v8[4] > v15)
        v15 = v8[4];

    v14 = GetRandom(1, v15);

    for(int i = 0; i <= 4; ++i)
    {
        if(v14 <= v8[i])
            return v7[i];
    }

    return 4;
}

//GetDamage__FP10CCharacterT014_tagDamageTypecPC11CMagicProtoPC16CMagicLevelProto
int GetDamage(CCharacter *a1, CCharacter *a2, _tagDamageType a3, char a4, CMagicProto *a5, CMagicLevelProto *a6)
{
    int v8; // [sp+18h] [bp-30h]@114
    int v9; // [sp+18h] [bp-30h]@116
    int v10; // [sp+1Ch] [bp-2Ch]@30
    int v11; // [sp+1Ch] [bp-2Ch]@32
    int v12; // [sp+20h] [bp-28h]@30
    int v13; // [sp+20h] [bp-28h]@32
    int v14; // [sp+20h] [bp-28h]@66
    signed int v15; // [sp+20h] [bp-28h]@68
    int v16; // [sp+20h] [bp-28h]@108
    signed int v17; // [sp+20h] [bp-28h]@110
    int v18; // [sp+24h] [bp-24h]@24
    signed int v19; // [sp+24h] [bp-24h]@26
    int v20; // [sp+24h] [bp-24h]@72
    int v21; // [sp+24h] [bp-24h]@74
    int v22; // [sp+24h] [bp-24h]@108
    int v23; // [sp+28h] [bp-20h]@72
    int v24; // [sp+28h] [bp-20h]@74
    int v25; // [sp+28h] [bp-20h]@114
    int v26; // [sp+28h] [bp-20h]@116
    int v27; // [sp+2Ch] [bp-1Ch]@18
    int v28; // [sp+30h] [bp-18h]@18
    signed int v29; // [sp+38h] [bp-10h]@1
    signed int v30; // [sp+3Ch] [bp-Ch]@1
    int v31; // [sp+40h] [bp-8h]@1
    signed int v32; // [sp+40h] [bp-8h]@151

    v31 = 0;
    v30 = 0;
    v29 = 0;

    if(a4 == 1)
        return 0;

    if(a5)
    {
        if(!a6)
            return 0;

        if(a5->Unk7 == 1)
        {
            v30 = a6->Unk0;
        }
        else
        {
            if(a5->Unk7 > 1)
            {
                if(a5->Unk7 == 2)
                    v29 = a6->Unk0;
            }
            else
            {
                if(!a5->Unk7)
                    return (a6->Unk0 < 1) ? 1 : a6->Unk0;
            }
        }
    }

    v28 = ((CPC *)a1)->GetAttackLevel() - a1->Unk60; // CHECK TYPE CPC *
    v27 = ((CPC *)a1)->GetDefenseLevel() - a2->Unk60; // CHECK TYPE CPC *

    if(a3 == 1)
    {
        v14 = a1->Unk438 + a1->Unk94;
        if(a1->Unk0 == 0)
            v14 += ((CPC *)a1)->Unk516[0] + ((CPC *)a1)->Unk616[0] * v14 / 10000;

        v15 = a1->Unk148.Unk40[0] + a1->Unk148.Unk140[0] * v14 / 10000 + v14; // 188 = 148 + 40, 288 = 148 + 140

        if(v30)
            v15 += v30;

        if(v29)
            v15 += v29 * v15 / 10000;

        v20 = a2->Unk98;
        v23 = a2->Unk446;

        if(a2->Unk0 == 0)
        {
            v20 += ((CPC *)a2)->Unk616[1] * v20 / 10000;
            v23 += ((CPC *)a2)->Unk516[1] + ((CPC *)a2)->Unk616[1] * v23 / 10000;
        }

        v21 = a2->Unk148.Unk140[1] * v20 / 10000 + v20; // 292 = 148 + 140 + 4
        v24 = a2->Unk148.Unk40[1] + a2->Unk148.Unk140[1] * v23 / 10000 + v23; // 192 = 148 + 40 + 4, 292 = 148 + 140 + 4

        if(v28 <= 4 || v28 > 8)
        {
            if(v28 <= 8 || v28 > 12)
            {
                if(v28 > 12)
                    v15 /= 10;
            }
            else
            {
                v15 = 3 * v15 / 10;
            }
        }
        else
        {
            v15 = (signed int)(((unsigned int)((unsigned long long)v15 >> 32) >> 31) + v15) >> 1;
        }

        if(v27 <= 5 || v27 > 10)
        {
            if(v27 <= 10 || v27 > 15)
            {
                if(v27 > 15)
                {
                    v21 /= 10;
                    v24 /= 10;
                }
            }
            else
            {
                v21 = 3 * v21 / 10;
                v24 = 3 * v24 / 10;
            }
        }
        else
        {
            v21 = (signed int)(((unsigned int)((unsigned long long)v21 >> 32) >> 31) + v21) >> 1;
            v24 = (signed int)(((unsigned int)((unsigned long long)v24 >> 32) >> 31) + v24) >> 1;
        }

        if(a4 == 8)
        {
            v31 = 13 * v15 / 10 + ((signed int)(((unsigned int)((unsigned long long)a1->Unk86 >> 32) >> 31) + a1->Unk86) >> 1) - (v24 + v21) / 5;
        }
        else
        {
            if(a4 > 8)
            {
                if(a4 == 32)
                {
                    v31 = 16 * v15 / 10
                            + ((signed int)(((unsigned int)((unsigned long long)a1->Unk86 >> 32) >> 31) + a1->Unk86) >> 1)
                            - v24 / 5;
                }
                else
                {
                    if(a4 > 32)
                    {
                        if(a4 == 64)
                            v31 = 2 * v15 + ((signed int)(((unsigned int)((unsigned long long)a1->Unk86 >> 32) >> 31) + a1->Unk86) >> 1) - v24 / 5;
                    }
                    else
                    {
                        if(a4 == 16)
                            v31 = 16 * v15 / 10 + ((signed int)(((unsigned int)((unsigned long long)a1->Unk86 >> 32) >> 31) + a1->Unk86) >> 1) - (v24 + v21) / 5;
                    }
                }
            }
            else
            {
                if(a4 == 2)
                {
                    v31 = v15 / 2 + ((signed int)(((unsigned int)((unsigned long long)a1->Unk86 >> 32) >> 31) + a1->Unk86) >> 1) - (v24 + v21) / 5;
                }
                else
                {
                    if(a4 == 4)
                        v31 = ((signed int)(((unsigned int)((unsigned long long)a1->Unk86 >> 32) >> 31) + a1->Unk86) >> 1) + v15 - (v24 + v21) / 5;
                }
            }
        }
    }
    else
    {
        if(a3 > 1)
        {
            if(a3 != 2)
                return 0;

            v16 = a1->Unk452 + a1->Unk96;
            v22 = a1->Unk454;

            if(a1->Unk0 == 0)
                v16 += ((CPC *)a1)->Unk516[2] + ((CPC *)a1)->Unk616[2] * v16 / 10000;

            v17 = a1->Unk148.Unk40[3] + a1->Unk148.Unk140[3] * v16 / 10000 + v16; // 196 = 148 + 40 + 12, 288 = 148 + 140 + 12

            if(v30)
                v17 += v30;

            if(v29)
                v17 += v29 * v17 / 10000;

            v25 = a2->Unk100;
            v8 = a2->Unk456;

            if(a2->Unk0 == 0)
            {
                v25 += ((CPC *)a2)->Unk616[3] * v25 / 10000;
                v8  += ((CPC *)a2)->Unk516[3] + ((CPC *)a2)->Unk616[3] * v8 / 10000;
            }

            v26 = a2->Unk148.Unk140[4] * v25 / 10000 + v25; // 300 = 148 + 140 + 16
            v9 = a2->Unk148.Unk40[4] + a2->Unk148.Unk140[4] * v8 / 10000 + v8; // 196 = 148 + 40 + 16, 300 = 148 + 140 + 16

            if(v28 <= 4 || v28 > 8)
            {
                if(v28 <= 8 || v28 > 12)
                {
                    if(v28 > 12)
                        v17 /= 10;
                }
                else
                {
                    v17 = 3 * v17 / 10;
                }
            }
            else
            {
                v17 = (signed int)(((unsigned int)((unsigned long long)v17 >> 32) >> 31) + v17) >> 1;
            }
            if(v27 <= 5 || v27 > 10)
            {
                if(v27 <= 10 || v27 > 15)
                {
                    if(v27 > 15)
                    {
                        v26 /= 10;
                        v9 /= 10;
                    }
                }
                else
                {
                    v26 = 3 * v26 / 10;
                    v9 = 3 * v9 / 10;
                }
            }
            else
            {
                v26 = (signed int)(((unsigned int)((unsigned long long)v26 >> 32) >> 31) + v26) >> 1;
                v9 = (signed int)(((unsigned int)((unsigned long long)v9 >> 32) >> 31) + v9) >> 1;
            }
            if(a4 == 8)
            {
                v31 = (v22 - (v9 + v26 - 10000)) * 13 * v17 / 10 / 10000 + ((signed int)(((unsigned int)((unsigned long long)a1->Unk88 >> 32) >> 31) + a1->Unk88) >> 1);
            }
            else
            {
                if(a4 > 8)
                {
                    if(a4 == 32)
                    {
                        v31 = (v22 - (v9 - 10000)) * 16 * v17 / 10 / 10000 + ((signed int)(((unsigned int)((unsigned long long)a1->Unk88 >> 32) >> 31) + a1->Unk88) >> 1);
                    }
                    else
                    {
                        if(a4 > 32)
                        {
                            if(a4 == 64)
                                v31 = v17 * 2 * (v22 - (v9 - 10000)) / 10000 + ((signed int)(((unsigned int)((unsigned long long)a1->Unk88 >> 32) >> 31) + a1->Unk88) >> 1);
                        }
                        else
                        {
                            if(a4 == 16)
                                v31 = (v22 - (v9 + v26 - 10000)) * 16 * v17 / 10 / 10000 + ((signed int)(((unsigned int)((unsigned long long)a1->Unk88 >> 32) >> 31) + a1->Unk88) >> 1);
                        }
                    }
                }
                else
                {
                    if(a4 == 2)
                    {
                        v31 = (v22 - (v9 + v26 - 10000)) * v17 / 2 / 10000 + ((signed int)(((unsigned int)((unsigned long long)a1->Unk88 >> 32) >> 31) + a1->Unk88) >> 1);
                    }
                    else
                    {
                        if(a4 == 4)
                            v31 = v17 * (v22 - (v9 + v26 - 10000)) / 10000 + ((signed int)(((unsigned int)((unsigned long long)a1->Unk88 >> 32) >> 31) + a1->Unk88) >> 1);
                    }
                }
            }
        }
        else
        {
            if(a3)
                return 0;

            v18 = a1->Unk436 + a1->Unk92;

            if(a1->Unk0 == 0)
                v18 += ((CPC *)a1)->Unk516[0] + ((CPC *)a1)->Unk616[0] * v18 / 10000;

            v19 = a1->Unk148.Unk40[0] + a1->Unk148.Unk140[0] * v18 / 10000 + v18; // 188 = 148 + 40, 288 = 148 + 140

            if(v30)
                v19 += v30;

            if(v29)
                v19 += v29 * v19 / 10000;

            v12 = a2->Unk98;
            v10 = a2->Unk444;

            if(a2->Unk0 == 0)
            {
                v12 += ((CPC *)a2)->Unk616[1] * v12 / 10000;
                v10 += ((CPC *)a2)->Unk516[1] + ((CPC *)a2)->Unk616[1] * v10 / 10000;
            }

            v13 = a2->Unk148.Unk140[1] * v12 / 10000 + v12; // 292 = 148 + 140 + 4
            v11 = a2->Unk148.Unk40[1]  + a2->Unk148.Unk140[1]  * v10 / 10000 + v10; // 192 = 148 + 40 + 4, 292 = 148 + 140 + 4

            if(v28 <= 4 || v28 > 8)
            {
                if(v28 <= 8 || v28 > 12)
                {
                    if(v28 > 12)
                        v19 /= 10;
                }
                else
                {
                    v19 = 3 * v19 / 10;
                }
            }
            else
            {
                v19 = (signed int)(((unsigned int)((unsigned long long)v19 >> 32) >> 31) + v19) >> 1;
            }
            if(v27 <= 5 || v27 > 10)
            {
                if(v27 <= 10 || v27 > 15)
                {
                    if(v27 > 15)
                    {
                        v13 /= 10;
                        v11 /= 10;
                    }
                }
                else
                {
                    v13 = 3 * v13 / 10;
                    v11 = 3 * v11 / 10;
                }
            }
            else
            {
                v13 = (signed int)(((unsigned int)((unsigned long long)v13 >> 32) >> 31) + v13) >> 1;
                v11 = (signed int)(((unsigned int)((unsigned long long)v11 >> 32) >> 31) + v11) >> 1;
            }
            if(a4 == 8)
            {
                v31 = 13 * v19 / 10 + ((signed int)(((unsigned int)((unsigned long long)a1->Unk84 >> 32) >> 31) + a1->Unk84) >> 1) - (v11 + v13) / 5;
            }
            else
            {
                if(a4 > 8)
                {
                    if(a4 == 32)
                    {
                        v31 = 16 * v19 / 10 + ((signed int)(((unsigned int)((unsigned long long)a1->Unk84 >> 32) >> 31) + a1->Unk84) >> 1) - v11 / 5;
                    }
                    else
                    {
                        if(a4 > 32)
                        {
                            if(a4 == 64)
                                v31 = 2 * v19 + ((signed int)(((unsigned int)((unsigned long long)a1->Unk84 >> 32) >> 31) + a1->Unk84) >> 1) - v11 / 5;
                        }
                        else
                        {
                            if(a4 == 16)
                                v31 = 16 * v19 / 10 + ((signed int)(((unsigned int)((unsigned long long)a1->Unk84 >> 32) >> 31) + a1->Unk84) >> 1) - (v11 + v13) / 5;
                        }
                    }
                }
                else
                {
                    if(a4 == 2)
                    {
                        v31 = v19 / 2 + ((signed int)(((unsigned int)((unsigned long long)a1->Unk84 >> 32) >> 31) + a1->Unk84) >> 1) - (v11 + v13) / 5;
                    }
                    else
                    {
                        if(a4 == 4)
                            v31 = ((signed int)(((unsigned int)((unsigned long long)a1->Unk84 >> 32) >> 31) + a1->Unk84) >> 1) + v19 - (v11 + v13) / 5;
                    }
                }
            }
        }
    }

    v32 = GetRandom(-7, 7) + v31;

    if(v32 <= 0)
        v32 = 1;

    if(a1->Unk0 == 0)
    {
        if(((CPC *)a1)->Unk1852 > -150)
        {
            if(((CPC *)a1)->Unk1852 > -140)
            {
                if(((CPC *)a1)->Unk1852 > -130)
                {
                    if(((CPC *)a1)->Unk1852 > -120)
                    {
                        if(((CPC *)a1)->Unk1852 > -110)
                        {
                            if(((CPC *)a1)->Unk1852 > -100)
                            {
                                if(((CPC *)a1)->Unk1852 > -90)
                                {
                                    if(((CPC *)a1)->Unk1852 > -80)
                                    {
                                        if(((CPC *)a1)->Unk1852 > -70)
                                        {
                                            if(((CPC *)a1)->Unk1852 > -60)
                                            {
                                                if(((CPC *)a1)->Unk1852 > -50)
                                                {
                                                    if(((CPC *)a1)->Unk1852 > -40)
                                                    {
                                                        if(((CPC *)a1)->Unk1852 > -30)
                                                        {
                                                            if(((CPC *)a1)->Unk1852 > -20)
                                                            {
                                                                if(((CPC *)a1)->Unk1852 <= -10)
                                                                    v32 -= v32 / 25;
                                                            }
                                                            else
                                                            {
                                                                v32 -= 8 * v32 / 100;
                                                            }
                                                        }
                                                        else
                                                        {
                                                            v32 -= 12 * v32 / 100;
                                                        }
                                                    }
                                                    else
                                                    {
                                                        v32 -= 16 * v32 / 100;
                                                    }
                                                }
                                                else
                                                {
                                                    v32 -= v32 / 5;
                                                }
                                            }
                                            else
                                            {
                                                v32 -= 24 * v32 / 100;
                                            }
                                        }
                                        else
                                        {
                                            v32 -= 28 * v32 / 100;
                                        }
                                    }
                                    else
                                    {
                                        v32 -= 32 * v32 / 100;
                                    }
                                }
                                else
                                {
                                    v32 -= 36 * v32 / 100;
                                }
                            }
                            else
                            {
                                v32 -= 40 * v32 / 100;
                            }
                        }
                        else
                        {
                            v32 -= 44 * v32 / 100;
                        }
                    }
                    else
                    {
                        v32 -= 48 * v32 / 100;
                    }
                }
                else
                {
                    v32 -= 52 * v32 / 100;
                }
            }
            else
            {
                v32 -= 56 * v32 / 100;
            }
        }
        else
        {
            v32 -= 60 * v32 / 100;
        }
    }

    if(v32 <= 0)
        v32 = 1;

    if(a2->Unk0 == 0)
    {
        if(((CPC *)a2)->Unk1852 > -150)
        {
            if(((CPC *)a2)->Unk1852 > -140)
            {
                if(((CPC *)a2)->Unk1852 > -130)
                {
                    if(((CPC *)a2)->Unk1852 > -120)
                    {
                        if(((CPC *)a2)->Unk1852 > -110)
                        {
                            if(((CPC *)a2)->Unk1852 > -100)
                            {
                                if(((CPC *)a2)->Unk1852 > -90)
                                {
                                    if(((CPC *)a2)->Unk1852 > -80)
                                    {
                                        if(((CPC *)a2)->Unk1852 <= -70)
                                            v32 += v32 / 20;
                                    }
                                    else
                                    {
                                        v32 += v32 / 10;
                                    }
                                }
                                else
                                {
                                    v32 += 15 * v32 / 100;
                                }
                            }
                            else
                            {
                                v32 += v32 / 5;
                            }
                        }
                        else
                        {
                            v32 += v32 / 4;
                        }
                    }
                    else
                    {
                        v32 += 30 * v32 / 100;
                    }
                }
                else
                {
                    v32 += 35 * v32 / 100;
                }
            }
            else
            {
                v32 += 40 * v32 / 100;
            }
        }
        else
        {
            v32 += 45 * v32 / 100;
        }
    }

    if(v32 <= 0)
        v32 = 1;

    return v32;
}

CAttackChar *FindMaxDamage(CNPC *a1)
{
    int v2; // [sp+Ch] [bp-Ch]@1
    CAttackChar *v3; // [sp+10h] [bp-8h]@1
    CAttackChar *v4; // [sp+14h] [bp-4h]@1

    v4 = 0;
    v3 = a1->Unk396;
    v2 = 0;

    while(v3)
    {
        if(v3->Unk16)
        {
            if(a1->Unk408->Unk0 != v3->Unk16->Unk408->Unk0 || a1->Unk412->Unk8 != v3->Unk16->Unk412->Unk8 || !CheckInNearCellExt(a1, v3->Unk16))
                return v4;

            if(v2 <= v3->Unk0)
            {
                v2 = v3->Unk0;
                v4 = v3;
            }
        }

        v3 = v3->Unk20;
    }

    return v4;
}

CCharacter *FindPreferencePC(CNPC *a1, int *a2)
{
    signed int v3; // [sp+20h] [bp-18h]@1
    signed int v4; // [sp+24h] [bp-14h]@1
    int v5; // [sp+28h] [bp-10h]@1
    signed int v6; // [sp+2Ch] [bp-Ch]@8
    CAttackChar *v7; // [sp+30h] [bp-8h]@1
    CCharacter *v8; // [sp+34h] [bp-4h]@1

    v8 = 0;
    v7 = a1->Unk396;
    v5 = a1->Unk78 / 5 + a1->Unk740;
    v4 = 0;
    v3 = 0;

    while(v7)
    {
        if(v7->Unk16)
        {
            if(a1->Unk408->Unk0 != v7->Unk16->Unk408->Unk0 || a1->Unk412->Unk8 != v7->Unk16->Unk412->Unk8 || !CheckInNearCellExt(a1, v7->Unk16))
                break;

            v6 = v7->Unk0;

            if(!v7->Unk20)
                v6 += a1->Unk78 / 5;

            if(v6 > (signed int)(((unsigned int)((unsigned long long)v5 >> 32) >> 31) + v5) >> 1)
                v8 = v7->Unk16;

            v4 += v7->Unk16->Unk60;
            ++v3;
        }

        v7 = v7->Unk20;
    }

    *a2 = v3 ? v4 / v3 : -1;

    return v8;
}

void DivisionExpSPParty(CParty *a1, CNPC *a2)
{
    /* TODO */
}

/*void DivisionExpSPParty(CParty *a1, CNPC *a2)
{
    int v2; // eax@15
    int v3; // eax@19
    float v4; // ST70_4@29
    float v5; // ST6C_4@29
    float v6; // ST70_4@29
    float v7; // ST6C_4@29
    long double v8; // fst7@31
    __int16 v9; // fps@31
    char v10; // c0@31
    char v11; // c2@31
    char v12; // c3@31
    float v13; // ST68_4@56
    float v14; // ST64_4@56
    float v15; // ST68_4@56
    float v16; // ST64_4@56
    long double v17; // fst7@57
    __int16 v18; // fps@57
    char v19; // c0@57
    char v20; // c2@57
    char v21; // c3@57
    int v22; // [sp+10h] [bp-58h]@27
    int v23; // [sp+20h] [bp-48h]@57
    float v24; // [sp+24h] [bp-44h]@51
    char v25; // [sp+2Ah] [bp-3Eh]@31
    char v26; // [sp+2Ah] [bp-3Eh]@57
    char v27; // [sp+2Bh] [bp-3Dh]@31
    char v28; // [sp+2Bh] [bp-3Dh]@57
    signed int v29; // [sp+2Ch] [bp-3Ch]@19
    int v30; // [sp+2Ch] [bp-3Ch]@31
    int v31; // [sp+2Ch] [bp-3Ch]@49
    int v32; // [sp+34h] [bp-34h]@4
    signed int v33; // [sp+38h] [bp-30h]@4
    int v34; // [sp+40h] [bp-28h]@4
    int j; // [sp+40h] [bp-28h]@51
    float v36; // [sp+44h] [bp-24h]@50
    float v37; // [sp+48h] [bp-20h]@50
    float v38; // [sp+4Ch] [bp-1Ch]@29
    float v39; // [sp+50h] [bp-18h]@29
    float v40; // [sp+54h] [bp-14h]@4
    char s[8]; // [sp+58h] [bp-10h]@4
    int v42; // [sp+60h] [bp-8h]@4
    int i; // [sp+64h] [bp-4h]@4

    if(a1 && a2)
    {
        v42 = 0;
        v40 = 0.0;
        memset(s, 0, 8u);
        v34 = *(_DWORD *)(a2->Unk396);
        v33 = 0;
        v32 = 0;
        i = 0;
        while(v34)
        {
            if(CPC::IsParty(*(_DWORD *)(v34 + 16))
                && a1 == *(_DWORD *)(*(_DWORD *)(v34 + 16) + 1368)
                && CheckInNearCellExt(*(_DWORD *)(v34 + 16), a2))
            {
                if(*(_WORD *)(*(_DWORD *)(v34 + 16) + 76) > 0)
                {
                    v40 = (long double)*(signed int *)v34 + v40;
                    *(_BYTE *)(v34 + 12) = 1;
                }
            }
            v34 = *(_DWORD *)(v34 + 20);
        }
        for(i = 0; i <= 7; ++i)
        {
            if(CParty::GetMember(a1, i))
            {
                v2 = CParty::GetMember(a1, i);
                if(CheckInNearCellExt(v2, a2))
                {
                    if(*(_WORD *)(CParty::GetMember(a1, i) + 76) > 0)
                    {
                        ++v42;
                        v33 += *(_DWORD *)(CParty::GetMember(a1, i) + 60);
                        if(v32 < *(_DWORD *)(CParty::GetMember(a1, i) + 60))
                            v32 = *(_DWORD *)(CParty::GetMember(a1, i) + 60);
                        v3 = CParty::GetMember(a1, i);
                        v29 = CParty::Find(a1, v3);
                        if(v29 >= 0)
                            s[v29] = 1;
                    }
                }
            }
        }
        if(v40 >= 1.0 && v42 > 0 && v33 > 0)
        {
            if(v32 - v33 / v42 <= 5)
                v22 = v33 / v42;
            else
                v22 = v32 - 5;
            v4 = (long double)*(signed int *)(*(_DWORD *)(a2->Unk464) + 60) * v40 / (long double)*(signed int *)(a2->Unk740);
            v5 = (long double)*(signed int *)(*(_DWORD *)(a2->Unk464) + 72) * v40 / (long double)*(signed int *)(a2->Unk740);
            v6 = ((long double)(v42 - 1) * 5.0 / 100.0 + 0.1) * v4 + v4;
            v7 = ((long double)(v42 - 1) * 5.0 / 100.0 + 0.1) * v5 + v5;
            v39 = (long double)(signed int)GetRandom(900, 1100) / 1000.0 * v6;
            v38 = (long double)(signed int)GetRandom(900, 1100) / 1000.0 * v7;
            if(!(unsigned __int8)CParty::GetPartyType(a1))
            {
                if(v22 <= *(_DWORD *)(a2->Unk60))
                {
                    if(v22 < *(_DWORD *)(a2->Unk60))
                        v38 = ((long double)(*(_DWORD *)(a2->Unk60) - v22) * 5.0 / 100.0 + 1.0) * v38;
                }
                else
                {
                    v30 = v22 - *(_DWORD *)(a2->Unk60);
                    v27 = 0;
                    v25 = 0;
                    v8 = (long double)v30;
                    UNDEF(v9);
                    v10 = 7.0100002 < v8;
                    v11 = 0;
                    v12 = 7.0100002 == v8;
                    if((HIBYTE(v9) & 0x45) == 1)
                        v27 = 1;
                    if(v30 > 10)
                        v25 = 1;
                    if(v27)
                        v39 = v39 * 0.29899997;
                    else
                        v39 = (1.0 - (long double)v30 * 10.0 / 100.0) * v39;
                    if(v25)
                        v38 = 1.0;
                    else
                        v38 = (1.0 - (long double)v30 * 10.0 / 100.0) * v38;
                }
            }
            for(i = 0; i <= 7; ++i)
            {
                if(CParty::GetMember(a1, i) && s[i])
                {
                    v31 = CParty::GetMember(a1, i);
                    if((unsigned __int8)CParty::GetPartyType(a1))
                    {
                        v24 = 0.0;
                        for(j = *(_DWORD *)(a2->Unk396); j; j = *(_DWORD *)(j + 20))
                        {
                            if(*(_DWORD *)(j + 16) == v31)
                            {
                                v24 = (long double)*(signed int *)j;
                                break;
                            }
                        }
                        v13 = v39 * 20.0 / ((long double)v42 * 100.0);
                        v14 = v38 * 20.0 / ((long double)v42 * 100.0);
                        v15 = v39 * 60.0 * v24 / (v40 * 100.0) + v13;
                        v37 = v39 * 20.0 * (long double)*(signed int *)(v31 + 60) / ((long double)v33 * 100.0) + v15;
                        v16 = v38 * 60.0 * v24 / (v40 * 100.0) + v14;
                        v36 = v38 * 20.0 * (long double)*(signed int *)(v31 + 60) / ((long double)v33 * 100.0) + v16;
                        if(*(_DWORD *)(v31 + 60) <= *(_DWORD *)(a2->Unk60))
                        {
                            if(*(_DWORD *)(v31 + 60) < *(_DWORD *)(a2->Unk60))
                                v36 = ((long double)(*(_DWORD *)(a2->Unk60) - *(_DWORD *)(v31 + 60)) * 5.0 / 100.0 + 1.0) * v36;
                        }
                        else
                        {
                            v23 = *(_DWORD *)(v31 + 60) - *(_DWORD *)(a2->Unk60);
                            v26 = 0;
                            v28 = 0;
                            v17 = (long double)v23;
                            UNDEF(v18);
                            v19 = 7.0100002 < v17;
                            v20 = 0;
                            v21 = 7.0100002 == v17;
                            if((HIBYTE(v18) & 0x45) == 1)
                                v26 = 1;
                            if(v23 > 10)
                                v28 = 1;
                            if(v26)
                                v37 = v37 * 0.29899997;
                            else
                                v37 = (1.0 - (long double)v23 * 10.0 / 100.0) * v37;
                            if(v28)
                                v36 = 1.0;
                            else
                                v36 = (1.0 - (long double)v23 * 10.0 / 100.0) * v36;
                        }
                    }
                    else
                    {
                        v37 = v39 / (long double)v42;
                        v36 = v38 / (long double)v42;
                    }
                    if(v37 < 1.0)
                        v37 = 1.0;
                    if(v36 < 1.0)
                        v36 = 1.0;
                    CPC::AddExpSP(v31, (signed __int64)v37, (signed int)v36);
                }
            }
        }
    }
}*/

void DivisionExpSP(CNPC *a1)
{
    bool v9; // [sp+16h] [bp-22h]@14
    bool v10; // [sp+17h] [bp-21h]@14
    int v11; // [sp+18h] [bp-20h]@14
    CAttackChar *v12; // [sp+1Ch] [bp-1Ch]@1
    CAttackChar *v13; // [sp+20h] [bp-18h]@2
    float v14; // [sp+24h] [bp-14h]@1
    float v15; // [sp+2Ch] [bp-Ch]@1
    float v16; // [sp+30h] [bp-8h]@27
    float v17; // [sp+34h] [bp-4h]@27

    v15 = a1->Unk464->Unk60;
    v14 = a1->Unk464->Unk72;
    v12 = a1->Unk396;

    while(1)
    {
        v13 = v12;
        if(!v12)
            break;

        v12 = v12->Unk20;
        if(v13->Unk16 && a1->Unk408->Unk0 == v13->Unk16->Unk408->Unk0 && a1->Unk412->Unk8 == v13->Unk16->Unk412->Unk8 && CheckInNearCellExt(a1, v13->Unk16) && !v13->Unk12)
        {
            if(v13->Unk0 > 0) // O.o -> Unk0 should be 0
            {
                if(((CPC *)v13->Unk16)->IsParty())
                {
                    DivisionExpSPParty(((CPC *)v13->Unk16)->Unk1368, a1);
                }
                else
                {
                    v13->Unk12 = 1;
                    if(v13->Unk16->Unk60 <= a1->Unk60)
                    {
                        if(v13->Unk16->Unk60 < a1->Unk60)
                            v14 = ((long double)(a1->Unk60 - v13->Unk16->Unk60) * 5.0 / 100.0 + 1.0) * v14;
                    }
                    else
                    {
                        v11 = v13->Unk16->Unk60 - a1->Unk60;
                        v10 = 0;
                        v9 = 0;
                        //v2 = (long double)v11;
                        //UNDEF(v3);
                        //v4 = 7.0100002 < v2;
                        //v5 = 0;
                        //v6 = 7.0100002 == v2;

                        //if((HIBYTE(v3) & 0x45) == 1)
                        if((long double)v11 > 7.0100002)
                            v10 = true;

                        if(v11 > 10)
                            v9 = true;

                        v15 = v10 ? (v15 * 0.29899997) : ((1.0 - v11 * 10.0 / 100.0) * v15);
                        v14 = v9  ? 1.0 : ((1.0 - v11 * 10.0 / 100.0) * v14);
                    }

                    v17 = GetRandom(900, 1100) / 1000.0 * (v13->Unk0 * v15 / a1->Unk740);
                    v16 = GetRandom(900, 1100) / 1000.0 * (v13->Unk0 * v14 / a1->Unk740);

                    if(v17 < 1.0)
                        v17 = 1.0;

                    if(v16 < 1.0)
                        v16 = 1.0;

                    if(!v13->Unk16->Unk0)
                    {
                        ((CPC *)v13->Unk16)->AddExpSP(v17, v16);
                        v13->Unk12 = 1;
                        ((CPC *)v13->Unk16)->Unk473 = 1;
                    }
                }
            }
            else
            {
                v13->Unk12 = 1;
            }
        }
    }
}

void DivisionPartyMoney(CPC *a1, CItem *a2)
{
    /* TODO */
}

/*void DivisionPartyMoney(CPC *a1, CItem *a2)
{
    int result; // eax@3
    int v3; // eax@9
    __int64 v4; // qax@16
    int v5; // eax@23
    int v6; // esi@30
    int v7; // eax@44
    __int64 v8; // qax@48
    int v9; // eax@52
    __int64 v10; // ST70_8@53
    signed int v11; // ST58_4@53
    signed int v12; // ST40_4@53
    const char *v13; // ST28_4@53
    const char *v14; // ST10_4@53
    const char *v15; // eax@53
    int v16; // eax@53
    int v17; // eax@53
    int v18; // eax@53
    int v19; // eax@53
    int v20; // eax@53
    int v21; // eax@53
    int v22; // eax@53
    int v23; // eax@53
    int v24; // eax@53
    int v25; // eax@53
    int v26; // eax@53
    int v27; // eax@54
    int v28; // eax@57
    char v29; // [sp+18h] [bp-80h]@67
    char v30; // [sp+2Ch] [bp-6Ch]@56
    int v31; // [sp+40h] [bp-58h]@53
    int v32; // [sp+50h] [bp-48h]@47
    int v33; // [sp+54h] [bp-44h]@46
    int v34; // [sp+58h] [bp-40h]@46
    char v35; // [sp+5Fh] [bp-39h]@44
    int v36; // [sp+60h] [bp-38h]@43
    int v37; // [sp+64h] [bp-34h]@42
    __int64 v38; // [sp+68h] [bp-30h]@16
    char v39; // [sp+73h] [bp-25h]@16
    int v40; // [sp+74h] [bp-24h]@14
    int v41; // [sp+88h] [bp-10h]@4
    char v42; // [sp+8Fh] [bp-9h]@4
    int v43; // [sp+90h] [bp-8h]@4
    int i; // [sp+94h] [bp-4h]@4

    if(a1 || a2 || (result = v1C, v1C == *unk_8104584))
    {
        v43 = *(_DWORD *)(a1->Unk1368);
        v42 = 0;
        v41 = 0;
        for(i = 0; i <= 7; ++i)
        {
            if(CParty::GetMember(v43, i))
            {
                if(*(_DWORD *)(a2->Unk216) == *(_DWORD *)(CParty::GetMember(v43, i) + 4))
                    v42 = 1;
                v3 = CParty::GetMember(v43, i);
                if(CheckInNearCellExt(a1, v3))
                    ++v41;
            }
        }
        result = a2;
        if(*(_DWORD *)(a2->Unk216) == -1 || v42)
        {
            CNetMsg::CNetMsg((int)&v40);
            if(v41 > 0)
            {
                v39 = 0;
                v4 = CItem::Count(a2);
                v38 = v4 / v41;
                if(SHIDWORD(v38) > 0 || !HIDWORD(v38) && (_DWORD)v38)
                {
                    for(i = 7; i >= 0; --i)
                    {
                        if(CParty::GetMember(v43, i))
                        {
                            v5 = CParty::GetMember(v43, i);
                            if(CheckInNearCellExt(a1, v5))
                            {
                                if(*(_DWORD *)(*(_DWORD *)(a2->Unk20) + 4) != 4
                                    || *(_DWORD *)(*(_DWORD *)(a2->Unk20) + 8) && *(_DWORD *)(*(_DWORD *)(a2->Unk20) + 8) != 1)
                                {
                                    v6 = CParty::GetMember(v43, i) + 792;
                                }
                                else
                                {
                                    if(*(_DWORD *)(*(_DWORD *)(a2->Unk20) + 4) != 4 || *(_DWORD *)(*(_DWORD *)(a2->Unk20) + 8))
                                        v6 = *(_DWORD *)(*(_DWORD *)(a2->Unk20) + 4) == 4
                                            && *(_DWORD *)(*(_DWORD *)(a2->Unk20) + 8)
                                            && *(_DWORD *)(*(_DWORD *)(a2->Unk20) + 8) == 1 ? CParty::GetMember(v43, i) + 968 : 0;
                                    else
                                        v6 = CParty::GetMember(v43, i) + 880;
                                }
                                v37 = v6;
                                if(v6)
                                {
                                    v36 = CItemList::CreateItem(gserver.Unk41208, *unk_8104584, -1, 0, 0, v38);
                                    if(v36)
                                    {
                                        v35 = 0;
                                        v7 = CParty::GetMember(v43, i);
                                        if(CInventory::AddItem(v37, v36, v7, 1, 1, -1, -1))
                                        {
                                            v39 = 1;
                                            if(CItem::tab(v36) == -1)
                                            {
                                                v35 = 1;
                                                if(CInventory::FindItem(
                                                             v37,
                                                             (int)&v34,
                                                             (int)&v33,
                                                             *(_DWORD *)(v36 + 28),
                                                             *(_DWORD *)(v36 + 36),
                                                             *(_DWORD *)(v36 + 40)))
                                                {
                                                    v32 = CInventory::GetItem(v37, v34, v33);
                                                    if(v32)
                                                    {
                                                        v8 = CItem::Count(v36);
                                                        ItemUpdateMsg((int)&v40, v32, v8);
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                ItemAddMsg((int)&v40, v36);
                                                if(*(_DWORD *)(v36 + 28) == *unk_8104584 && !*(_DWORD *)(CParty::GetMember(v43, i) + 1280))
                                                {
                                                    v9 = CParty::GetMember(v43, i);
                                                    *(_DWORD *)(v9 + 1280) = v36;
                                                }
                                            }
                                            v10 = CItem::Count(v36);
                                            v11 = *(_DWORD *)(v36 + 40);
                                            v12 = *(_DWORD *)(v36 + 36);
                                            v13 = (const char *)(v36 + 44);
                                            v14 = (const char *)(*(_DWORD *)(v36 + 20) + 12);
                                            init((int)&v31, (int)"ITEM_PICK", a1->Unk8, *(_DWORD *)(a1->Unk768) + 4);
                                            v15 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v31);
                                            v16 = (int)CLogBuffer::__ls(v15, v14);
                                            v17 = CLogBuffer::__ls(v16, (int (*)(_DWORD))delim);
                                            v18 = (int)CLogBuffer::__ls((const char *)v17, v13);
                                            v19 = CLogBuffer::__ls(v18, (int (*)(_DWORD))delim);
                                            v20 = (int)CLogBuffer::__ls((char *)v19, v12);
                                            v21 = CLogBuffer::__ls(v20, (int (*)(_DWORD))delim);
                                            v22 = (int)CLogBuffer::__ls((char *)v21, v11);
                                            v23 = CLogBuffer::__ls(v22, (int (*)(_DWORD))delim);
                                            v24 = (int)CLogBuffer::__ls((char *)v23, v10);
                                            v25 = CLogBuffer::__ls(v24, (int (*)(_DWORD))delim);
                                            v26 = (int)CLogBuffer::__ls((char *)v25, 0);
                                            CLogBuffer::__ls(v26, end);
                                            if(*(_DWORD *)(CParty::GetMember(v43, i) + 768))
                                            {
                                                v27 = CParty::GetMember(v43, i);
                                                CDescriptor::WriteToOutput(*(_DWORD *)(v27 + 768), (int)&v40);
                                            }
                                            if(v35)
                                            {
                                                if(v36)
                                                    (*(void (**)(int, signed int))(*(_DWORD *)(v36 + 220) + 8))(v36, 3);
                                                v36 = 0;
                                            }
                                        }
                                        else
                                        {
                                            CNetMsg::CNetMsg((int)&v30);
                                            SysFullInventoryMsg((int)&v30, *(_BYTE *)(v37 + 4));
                                            if(*(_DWORD *)(CParty::GetMember(v43, i) + 768))
                                            {
                                                v28 = CParty::GetMember(v43, i);
                                                CDescriptor::WriteToOutput(*(_DWORD *)(v28 + 768), (int)&v30);
                                            }
                                            if(v36)
                                                (*(void (**)(int, signed int))(*(_DWORD *)(v36 + 220) + 8))(v36, 3);
                                            v36 = 0;
                                            CNetMsg::_CNetMsg((int)&v30, 2);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if(v39)
                    {
                        CNetMsg::CNetMsg((int)&v30);
                        CNetMsg::CNetMsg((int)&v29);
                        v32 = *(_DWORD *)(a2->Unk196);
                        v33 = *(_DWORD *)(a2->Unk200);
                        ItemTakeMsg((int)&v29, a1, a2);
                        ItemDisappearMsg((int)&v30, a2);
                        *(_DWORD *)(a2->Unk216) = -1;
                        CArea::ItemFromCell(*(_DWORD *)(a1->Unk412), a2);
                        if(a2)
                            (*(void (**)(int, signed int))(*(_DWORD *)(a2->Unk220) + 8))(a2, 3);
                        CArea::SendToCell(*(_DWORD *)(a1->Unk412), (int)&v29, a1, 1, 4);
                        CArea::SendToCell(*(_DWORD *)(a1->Unk412), (int)&v30, *(_BYTE *)(a1->Unk136), v32, v33, 4);
                        CNetMsg::_CNetMsg((int)&v29, 2);
                        CNetMsg::_CNetMsg((int)&v30, 2);
                    }
                    result = CNetMsg::_CNetMsg((int)&v40, 2);
                }
                else
                {
                    result = CNetMsg::_CNetMsg((int)&v40, 2);
                }
            }
            else
            {
                result = CNetMsg::_CNetMsg((int)&v40, 2);
            }
        }
    }
    return result;
}*/

void GetItemRandomParty(CPC *a1, CItem *a2)
{
    /* TODO */
}

/*void GetItemRandomParty(CPC *a1, CItem *a2)
{
    int result; // eax@3
    int v3; // eax@9
    int v4; // eax@36
    int v5; // eax@56
    __int64 v6; // qax@60
    signed int v7; // ST8C_4@63
    __int64 v8; // ST74_8@63
    signed int v9; // ST5C_4@63
    signed int v10; // ST44_4@63
    const char *v11; // ST14_4@63
    int v12; // ST10_4@63
    int v13; // eax@63
    const char *v14; // eax@63
    int v15; // eax@63
    int v16; // eax@63
    int v17; // eax@63
    int v18; // eax@63
    int v19; // eax@63
    int v20; // eax@63
    int v21; // eax@63
    int v22; // eax@63
    int v23; // eax@63
    int v24; // eax@63
    signed int v25; // ST8C_4@66
    signed int v26; // ST74_4@66
    int v27; // eax@66
    int v28; // eax@66
    int v29; // eax@66
    int v30; // eax@69
    int v31; // eax@72
    int v32; // eax@70
    int v33; // eax@70
    int v34; // eax@77
    int v35; // [sp+1Ch] [bp-9Ch]@43
    char v36; // [sp+24h] [bp-94h]@70
    char v37; // [sp+38h] [bp-80h]@70
    char v38; // [sp+4Ch] [bp-6Ch]@70
    int v39; // [sp+60h] [bp-58h]@63
    int v40; // [sp+70h] [bp-48h]@59
    int v41; // [sp+74h] [bp-44h]@58
    int v42; // [sp+78h] [bp-40h]@58
    char v43; // [sp+7Fh] [bp-39h]@56
    int v44; // [sp+80h] [bp-38h]@55
    char v45; // [sp+87h] [bp-31h]@18
    int v46; // [sp+88h] [bp-30h]@18
    int v47; // [sp+8Ch] [bp-2Ch]@20
    char v48; // [sp+93h] [bp-25h]@18
    int v49; // [sp+94h] [bp-24h]@14
    int v50; // [sp+A8h] [bp-10h]@4
    char v51; // [sp+AFh] [bp-9h]@4
    int v52; // [sp+B0h] [bp-8h]@4
    int i; // [sp+B4h] [bp-4h]@4

    if(a1 || a2 || (result = 0, v558))
    {
        v52 = *(_DWORD *)(a1->Unk1368);
        v51 = 0;
        v50 = 0;
        for(i = 0; i <= 7; ++i)
        {
            if(CParty::GetMember(v52, i))
            {
                if(*(_DWORD *)(a2->Unk216) == *(_DWORD *)(CParty::GetMember(v52, i) + 4))
                    v51 = 1;
                v3 = CParty::GetMember(v52, i);
                if(CheckInNearCellExt(a1, v3))
                    ++v50;
            }
        }
        result = a2;
        if(*(_DWORD *)(a2->Unk216) == -1 || v51)
        {
            if(v50 > 0)
            {
                CNetMsg::CNetMsg((int)&v49);
                v48 = 0;
                v46 = 0;
                v45 = 0;
                while(!v48)
                {
                    v47 = GetRandom(0, 7);
                    for(i = 0; i <= 7 && (v46 >> (i + v47) % 8) & 1; ++i)
                        ;
                    if(i == 8)
                    {
                        if(v45)
                            return CNetMsg::_CNetMsg((int)&v49, 2);
                        v45 = 1;
                        v46 = 0;
                        for(i = 0; i <= 7; ++i)
                        {
                            if(CParty::GetMember(*(_DWORD *)(a1->Unk1368), i))
                                *(_BYTE *)(CParty::GetMember(*(_DWORD *)(a1->Unk1368), i) + 2380) = 0;
                            else
                                v46 |= 1 << i;
                        }
                    }
                    else
                    {
                        v47 = (i + v47) % 8;
                        v46 |= 1 << v47;
                        if(CParty::GetMember(v52, v47) && !*(_BYTE *)(CParty::GetMember(v52, v47) + 2380))
                        {
                            v4 = CParty::GetMember(v52, v47);
                            if(CheckInNearCellExt(a1, v4))
                            {
                                if(*(_DWORD *)(*(_DWORD *)(a2->Unk20) + 4) != 4
                                    || *(_DWORD *)(*(_DWORD *)(a2->Unk20) + 8) && *(_DWORD *)(*(_DWORD *)(a2->Unk20) + 8) != 1)
                                {
                                    v35 = CParty::GetMember(v52, v47) + 792;
                                }
                                else
                                {
                                    if(*(_DWORD *)(*(_DWORD *)(a2->Unk20) + 4) != 4 || *(_DWORD *)(*(_DWORD *)(a2->Unk20) + 8))
                                    {
                                        if(*(_DWORD *)(*(_DWORD *)(a2->Unk20) + 4) == 4
                                            && *(_DWORD *)(*(_DWORD *)(a2->Unk20) + 8)
                                            && *(_DWORD *)(*(_DWORD *)(a2->Unk20) + 8) == 1)
                                            v35 = CParty::GetMember(v52, v47) + 968;
                                        else
                                            v35 = 0;
                                    }
                                    else
                                    {
                                        v35 = CParty::GetMember(v52, v47) + 880;
                                    }
                                }
                                v44 = v35;
                                if(v35)
                                {
                                    v43 = 0;
                                    v5 = CParty::GetMember(v52, v47);
                                    if(CInventory::AddItem(v44, a2, v5, 1, 1, -1, -1))
                                    {
                                        v48 = 1;
                                        if(CItem::tab(a2) == -1)
                                        {
                                            v43 = 1;
                                            if(CInventory::FindItem(
                                                         v44,
                                                         (int)&v42,
                                                         (int)&v41,
                                                         *(_DWORD *)(a2->Unk28),
                                                         *(_DWORD *)(a2->Unk36),
                                                         *(_DWORD *)(a2->Unk40)))
                                            {
                                                v40 = CInventory::GetItem(v44, v42, v41);
                                                if(v40)
                                                {
                                                    v6 = CItem::Count(a2);
                                                    ItemUpdateMsg((int)&v49, v40, v6);
                                                }
                                            }
                                        }
                                        else
                                        {
                                            ItemAddMsg((int)&v49, a2);
                                        }
                                        v7 = *(_DWORD *)(a2->Unk168);
                                        v8 = CItem::Count(a2);
                                        v9 = *(_DWORD *)(a2->Unk40);
                                        v10 = *(_DWORD *)(a2->Unk36);
                                        v11 = (const char *)(*(_DWORD *)(a2->Unk20) + 12);
                                        v12 = *(_DWORD *)(CParty::GetMember(v52, v47) + 768) + 4;
                                        v13 = CParty::GetMember(v52, v47);
                                        init((int)&v39, (int)"ITEM_PICK", v13 + 8, v12);
                                        v14 = CLogBuffer::__ls(g_gamelogbuffer, (int)&v39);
                                        v15 = (int)CLogBuffer::__ls(v14, v11);
                                        v16 = CLogBuffer::__ls(v15, (int (*)(_DWORD))delim);
                                        v17 = (int)CLogBuffer::__ls((const char *)v16, (const char *)(a2->Unk44));
                                        v18 = CLogBuffer::__ls(v17, (int (*)(_DWORD))delim);
                                        v19 = (int)CLogBuffer::__ls((char *)v18, v10);
                                        v20 = CLogBuffer::__ls(v19, (int (*)(_DWORD))delim);
                                        v21 = (int)CLogBuffer::__ls((char *)v20, v9);
                                        v22 = CLogBuffer::__ls(v21, (int (*)(_DWORD))delim);
                                        v23 = (int)CLogBuffer::__ls((char *)v22, v8);
                                        v24 = CLogBuffer::__ls(v23, (int (*)(_DWORD))delim);
                                        CLogBuffer::__ls((char *)v24, v7);
                                        for(i = 0; i < *(_DWORD *)(a2->Unk168); ++i)
                                        {
                                            if(*(_DWORD *)(20 * i + a2->Unk68))
                                            {
                                                v25 = *(_DWORD *)(20 * i + a2->Unk76);
                                                v26 = *(_DWORD *)(20 * i + a2->Unk72);
                                                v27 = CLogBuffer::__ls((int)g_gamelogbuffer, (int (*)(_DWORD))delim);
                                                v28 = (int)CLogBuffer::__ls((char *)v27, v26);
                                                v29 = CLogBuffer::__ls(v28, (int (*)(_DWORD))delim);
                                                CLogBuffer::__ls((char *)v29, v25);
                                            }
                                        }
                                        CLogBuffer::__ls((int)g_gamelogbuffer, end);
                                        if(*(_DWORD *)(CParty::GetMember(v52, v47) + 768))
                                        {
                                            v30 = CParty::GetMember(v52, v47);
                                            CDescriptor::WriteToOutput(*(_DWORD *)(v30 + 768), (int)&v49);
                                        }
                                        CNetMsg::CNetMsg((int)&v38);
                                        CNetMsg::CNetMsg((int)&v37);
                                        CNetMsg::CNetMsg((int)&v36);
                                        v40 = *(_DWORD *)(a2->Unk196);
                                        v41 = *(_DWORD *)(a2->Unk200);
                                        ItemTakeMsg((int)&v37, a1, a2);
                                        ItemDisappearMsg((int)&v38, a2);
                                        v32 = CParty::GetMember(v52, v47);
                                        ItemGetMsg((int)&v36, v32, a2);
                                        *(_DWORD *)(a2->Unk216) = -1;
                                        v33 = CParty::GetMember(v52, v47);
                                        CArea::ItemFromCell(*(_DWORD *)(v33 + 412), a2);
                                        *(_BYTE *)(CParty::GetMember(v52, v47) + 2380) = 1;
                                        CArea::SendToCell(*(_DWORD *)(a1->Unk412), (int)&v37, a1, 1, 4);
                                        CArea::SendToCell(*(_DWORD *)(a1->Unk412), (int)&v38, *(_BYTE *)(a1->Unk136), v40, v41, 4);
                                        for(i = 0; i <= 7; ++i)
                                        {
                                            if(CParty::GetMember(v52, i) && *(_DWORD *)(CParty::GetMember(v52, i) + 768))
                                            {
                                                v34 = CParty::GetMember(v52, i);
                                                CDescriptor::WriteToOutput(*(_DWORD *)(v34 + 768), (int)&v36);
                                            }
                                        }
                                        if(v43)
                                        {
                                            if(a2)
                                                (*(void (**)(int, signed int))(*(_DWORD *)(a2->Unk220) + 8))(a2, 3);
                                            a2 = 0;
                                        }
                                        CNetMsg::_CNetMsg((int)&v36, 2);
                                        CNetMsg::_CNetMsg((int)&v37, 2);
                                        CNetMsg::_CNetMsg((int)&v38, 2);
                                    }
                                    else
                                    {
                                        CNetMsg::CNetMsg((int)&v38);
                                        SysFullInventoryMsg((int)&v38, *(_BYTE *)(v44 + 4));
                                        if(*(_DWORD *)(CParty::GetMember(v52, v47) + 768))
                                        {
                                            v31 = CParty::GetMember(v52, v47);
                                            CDescriptor::WriteToOutput(*(_DWORD *)(v31 + 768), (int)&v38);
                                        }
                                        CNetMsg::_CNetMsg((int)&v38, 2);
                                    }
                                }
                            }
                            else
                            {
                                *(_BYTE *)(CParty::GetMember(v52, v47) + 2380) = 1;
                            }
                        }
                    }
                }
                result = CNetMsg::_CNetMsg((int)&v49, 2);
            }
        }
        else
        {
            CNetMsg::CNetMsg((int)&v49);
            SysMsg((int)&v49, 15);
            if(*(_DWORD *)(a1->Unk768))
                CDescriptor::WriteToOutput(*(_DWORD *)(a1->Unk768), (int)&v49);
            result = CNetMsg::_CNetMsg((int)&v49, 2);
        }
    }
    return result;
}*/

CAttackChar *GetMaxHateTarget(CNPC *a1)
{
    int v2; // [sp+Ch] [bp-Ch]@1
    CAttackChar *v3; // [sp+10h] [bp-8h]@1
    CAttackChar *v4; // [sp+14h] [bp-4h]@1

    v4 = 0;
    v3 = a1->Unk396;
    v2 = 0;

    while(v3)
    {
        if(v2 <= v3->Unk4)
        {
            if(v3->Unk4)
            {
                v2 = v3->Unk4;
                v4 = v3;
            }
        }

        v3 = v3->Unk20;
    }
    return v4;
}

CCharacter *CheckAttackPulse(CNPC *a1)
{
    CAttackChar *v2; // [sp+Ch] [bp-1Ch]@16
    CAttackChar *v3; // [sp+10h] [bp-18h]@17
    int v4; // [sp+14h] [bp-14h]@6
    CCharacter *v5; // [sp+18h] [bp-10h]@1
    int v6; // [sp+1Ch] [bp-Ch]@1
    CAttackChar *v7; // [sp+20h] [bp-8h]@1
    CAttackChar *v8; // [sp+24h] [bp-4h]@2

    v7 = a1->Unk396;
    v6 = 0;
    v5 = 0;
    while(1)
    {
        v8 = v7;
        if(!v7)
            break;

        v7 = v7->Unk20;
        if(a1->Unk464->Unk92 & 0x400 || a1->Unk464->Unk92 & 0x800 || a1->Unk464->Unk92 & 0x1000)
            v4 = 40;
        else
            v4 = 1800;

        if(v8->Unk0 <= 0 || gserver.Unk41248 - v8->Unk8 <= v4)
        {
            if(v8)
            {
                if(v6 <= v8->Unk4)
                {
                    if(v8->Unk4)
                    {
                        v6 = v8->Unk4;
                        v5 = v8->Unk16;
                        if(!CheckInNearCellExt(a1, v5))
                            v5 = 0;
                    }
                }
            }
        }
        else
        {
            if(v8->Unk24)
            {
                v8->Unk24->Unk20 = v8->Unk20;
                if(v8->Unk20)
                    v8->Unk20->Unk24 = v8->Unk24;
            }
            else
            {
                a1->Unk396 = v8->Unk20;
                if(v8->Unk20)
                    v8->Unk20->Unk24 = 0;
            }

            v8->Unk24 = 0;
            v8->Unk20 = 0;

            v2 = v8->Unk16->Unk396;
            while(1)
            {
                v3 = v2;
                if(!v2)
                    break;

                v2 = v2->Unk20;
                if(v3->Unk16 == a1)
                {
                    if(v3->Unk24)
                    {
                        v3->Unk24->Unk20 = v3->Unk20;
                        if(v3->Unk20)
                            v3->Unk20->Unk24 = v3->Unk24;
                    }
                    else
                    {
                        v8->Unk16->Unk396 = v3->Unk20;
                        if(v3->Unk20)
                            v3->Unk20->Unk24 = 0;
                    }

                    v3->Unk24 = 0;
                    v3->Unk20 = 0;

                    if(v3)
                        delete v3;
                }
            }

            a1->Unk740 -= v8->Unk0;

            if(v8)
                delete v8;
        }
    }
    return v5;
}

void AddAttackList(CCharacter *a1, CCharacter *a2, int a3)
{
    CAttackChar *v8; // [sp+14h] [bp-14h]@18
    CAttackChar *v9; // [sp+18h] [bp-10h]@18
    CAttackChar *v10; // [sp+1Ch] [bp-Ch]@1
    CAttackChar *v11; // [sp+20h] [bp-8h]@1
    char v12; // [sp+26h] [bp-2h]@1
    char v13; // [sp+27h] [bp-1h]@1

    v13 = 1;
    v12 = 1;
    v11 = a1->Unk396;
    v10 = a2->Unk396;

    while(1)
    {
        if(!v11)
            goto LABEL_10;
        if(v11->Unk16 == a2)
            break;
        v11 = v11->Unk20;
    }

    if(a3 == 2)
    {
        if(!v11->Unk4)
        {
            if(a2->Unk76 > 0)
            {
                v11->Unk4 = 30;
            }
        }
    }

    v13 = 0;
LABEL_10:
    while(v10)
    {
        if(v10->Unk16 == a1)
        {
            if(!a3)
            {
                if(!v10->Unk4)
                {
                    if(a1->Unk76 > 0)
                    {
                        v10->Unk4 = 30;
                    }
                }
            }
            v12 = 0;
            break;
        }
        v10 = v10->Unk20;
    }

    v9 = 0;
    v8 = 0;

    if(v13)
    {
        v9 = new CAttackChar();
        v9->Unk16 = a2;

        if(a1->Unk396)
            a1->Unk396->Unk24 = v9;

        v9->Unk20 = a1->Unk396;
        v9->Unk24 = 0;
        a1->Unk396 = v9;
    }

    if(v12)
    {
        v8 = new CAttackChar();
        v8->Unk16 = a1;

        if(a2->Unk396)
            a2->Unk396->Unk24 = v8;

        v8->Unk20 = a2->Unk396;
        v8->Unk24 = 0;
        a2->Unk396 = v8;
    }

    if(v13)
    {
        if(v12)
        {
            if(a3 != 1)
            {
                if(a3 > 1)
                {
                    if(a3 == 2)
                    {
                        v9->Unk4 = 30;
                    }
                }
                else
                {
                    if(!a3)
                    {
                        v8->Unk4 = 30;
                        v8->Unk8 = gserver.Unk41248;
                    }
                }
            }
        }
    }
}

void DelAttackList(CCharacter *a1)
{
    CAttackChar *v2; // [sp+8h] [bp-10h]@3
    CAttackChar *v3; // [sp+Ch] [bp-Ch]@4
    CAttackChar *v4; // [sp+10h] [bp-8h]@1
    CAttackChar *v5; // [sp+14h] [bp-4h]@2

    v4 = a1->Unk396;
    while(1)
    {
        v5 = v4;
        if(!v4)
            break;

        v4 = v4->Unk20;
        v2 = v5->Unk16->Unk396;

        while(1)
        {
            v3 = v2;
            if(!v2)
                break;

            v2 = v2->Unk20;
            if(v3->Unk16 == a1)
            {
                if(v3->Unk24)
                {
                    v3->Unk24->Unk20 = v3->Unk20;
                    if(v3->Unk20)
                        v3->Unk20->Unk24 = v3->Unk24;
                }
                else
                {
                    v5->Unk16->Unk396 = v3->Unk20;
                    if(v3->Unk20)
                        v3->Unk20->Unk24 = 0;
                }

                v3->Unk24 = 0;
                v3->Unk20 = 0;

                if(v3)
                    delete v3;
                break;
            }
        }

        if(v5->Unk24)
        {
            v5->Unk24->Unk20 = v5->Unk20;
            if(v5->Unk20)
                v5->Unk20->Unk24 = v5->Unk24;
        }
        else
        {
            a1->Unk396 = v5->Unk20;
            if(v5->Unk20)
                v5->Unk20->Unk24 = 0;
        }

        v5->Unk24 = 0;
        v5->Unk20 = 0;

        if(v5)
            delete v5;
    }
}

void AddRaList(CPC *a1, CPC *a2)
{
    CRaChar *v8; // [sp+3Ch] [bp-8h]@5
    CRaChar *v9; // [sp+40h] [bp-4h]@1

    v9 = new CRaChar();

    v9->Unk0 = a1;
    v9->Unk4 = 200;
    v9->Unk8 = 1;

    if(a2->Unk1880)
        a2->Unk1880->Unk16 = v9;

    v9->Unk12 = a2->Unk1880;
    v9->Unk16 = 0;
    a2->Unk1880 = v9;

    a2->SetPlayerState(32);

    v8 = new CRaChar();

    v8->Unk0 = a2;
    v8->Unk8 = 0;
    if(a1->Unk1880)
        a1->Unk1880->Unk16 = v8;

    v8->Unk12 = a1->Unk1880;
    v8->Unk16 = 0;
    a1->Unk1880 = v8;

    CNetMsg v7;

    RightAttackMsg(v7, a1, 0);

    if(a1->Unk768)
        a1->Unk768->WriteToOutput(v7);

    if(a2->Unk768)
        a2->Unk768->WriteToOutput(v7);
}

void DelRaList(CPC *a1, bool a2)
{
    CRaChar *v4; // [sp+28h] [bp-10h]@3
    CRaChar *v5; // [sp+2Ch] [bp-Ch]@4
    CRaChar *v6; // [sp+30h] [bp-8h]@1
    CRaChar *v7; // [sp+34h] [bp-4h]@2

    v6 = a1->Unk1880;

    CNetMsg v3;

    RightAttackMsg(v3, a1, 2);

    while(1)
    {
        v7 = v6;

        if(!v6)
            return;

        v6 = v7->Unk12;
        v4 = v7->Unk0->Unk1880;

        while(1)
        {
            v5 = v4;

            if(!v4)
                break;

            v4 = v5->Unk12;

            if(v5->Unk0 == a1)
            {
                if(!v5->Unk8 && !a2)
                    return;

                if(v5->Unk0->Unk768)
                    v5->Unk0->Unk768->WriteToOutput(v3);

                if(v5->Unk16)
                {
                    v5->Unk16->Unk12 = v5->Unk12;
                    if(v5->Unk12)
                        v5->Unk12->Unk16 = v5->Unk16;
                }
                else
                {
                    v7->Unk0->Unk1880 = v5->Unk12;
                    if(v5->Unk12)
                        v5->Unk12->Unk16 = 0;
                }

                v5->Unk16 = 0;
                v5->Unk12 = 0;

                if(v5)
                    delete v5;

                v5 = 0;
                break;
            }
        }

        if(v7->Unk0->Unk768)
            v7->Unk0->Unk768->WriteToOutput(v3);

        if(v7->Unk16)
        {
            v7->Unk16->Unk12 = v7->Unk12;
            if(v7->Unk12)
                v7->Unk12->Unk16 = v7->Unk16;
        }
        else
        {
            a1->Unk1880 = v7->Unk12;
            if(v7->Unk12)
                v7->Unk12->Unk16 = 0;
        }

        v7->Unk16 = 0;
        v7->Unk12 = 0;

        if(v7)
            delete v7;

        v7 = 0;
    }
}

bool IsRaList(CPC *a1, CPC *a2)
{
    for(CRaChar *i = a1->Unk1880; i; i = i->Unk12)
    {
        if(i->Unk0 == a2)
            return true;
    }

    return false;
}

void FindFamilyInNear(CPC *a1, CNPC *a2)
{
    int j; // [sp+20h] [bp-18h]@6
    int v8; // [sp+28h] [bp-10h]@1
    int v9; // [sp+2Ch] [bp-Ch]@1
    int v10; // [sp+30h] [bp-8h]@1

    v10 = a2->Unk140 + 2;
    v9 = a2->Unk144 - 2;
    v8 = a2->Unk144 + 2;
    for(int i = a2->Unk140 - 2; ; ++i)
    {
        if(i > v10)
            break;

        if(i >= 0 && i < a2->Unk412->Unk12)
        {
            for(j = v9; j <= v8; ++j)
            {
                if(j >= 0 && j < a2->Unk412->Unk16)
                {
                    for(CCharacter *k = a2->Unk412->Unk28[i][j].Unk0; k; k = k->Unk404)
                    {
                        if(k->Unk0 == 1)
                        {
                            if(k != a2)
                            {
                                if(a2->Unk464->Unk96 != -1)
                                {
                                    if(((CNPC *)k)->Unk464->Unk96 == a2->Unk464->Unk96)
                                    {
                                        if(a2->Unk464->Unk68 + a2->Unk464->Unk68 > GetDistance(a2, k))
                                        {
                                            if(!a2->Unk488)
                                                AddAttackList(a1, k, 0);
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
}

bool GetSkillPrototypes(CSkillProto const *a1, int a2, int a3, CSkillLevelProto const **a4, CMagicProto const **a5, CMagicLevelProto const **a6)
{
    *a4 = 0;
    *a5 = 0;
    *a6 = 0;

    if(!a1)
        return false;

    if(a3 < 0 || a3 > 2)
        return false;

    *a4 = ((CSkillProto *)a1)->Level(a2);
    if(!*a4)
        return false;

    *a5 = (*a4)->Unk88[a3];
    if(!*a5)
        return false;

    *a6 = (CMagicLevelProto const *)((CSkillProto *)(*a5))->Level((*a4)->Unk100[a3]);
    if(!*a6)
        return false;

    return true;
}

void ApplyHate(CPC *a1, CNPC *a2, char a3, int a4)
{
    int v5; // ST38_4@9
    CAttackChar *v7; // [sp+20h] [bp-8h]@2

    if(a3 == 1)
        return;

    AddAttackList(a1, a2, 0);
    FindFamilyInNear(a1, a2);
    v7 = GetMaxHateTarget(a2);

    for(CAttackChar *i = a2->Unk396; i; i = i->Unk20)
    {
        if(i->Unk16 == a1)
        {
            i->Unk0 += a4;
            ++i->Unk4;
            i->Unk8 = gserver.Unk41248; // gserver.Unk41248

            if(v7 && i != v7)
            {
                if(i->Unk0 > 120 * v7->Unk0 / 100)
                {
                    v5 = i->Unk4;
                    i->Unk4 = v7->Unk4;
                    v7->Unk4 = v5;
                }
            }

            break;
        }
    }

    a2->Unk740 += a4;
}

//ApplyDamage__FP10CCharacterT014_tagDamageTypePC11CSkillProtoic
void ApplyDamage(CCharacter *a1, CCharacter *a2, _tagDamageType a3, CSkillProto *a4, int a5, char a6)
{
    char v8; // [sp+27h] [bp-1h]@1

    v8 = a6;
    if(a5)
    {
        a2->Unk76 -= a5;

        if(a2->Unk76 <= 0)
            a2->Unk76 = 0;
    }

    CNetMsg v7;

    if(a4)
        DamageMsg(v7, a1, a2, a3, a4->Unk0, a5, v8); // *a4
    else
        DamageMsg(v7, a1, a2, a3, (int)-1, a5, v8);

    a2->Unk412->SendToCell(v7, a2, 1, 4);
}

void CalcPKPoint(CPC *a1, CPC *a2)
{
    char v4; // [sp+27h] [bp-1h]@1

    v4 = a1->Unk1852 < -9;
    if(a2->Unk1852 < -9)
    {
        if(a2->Unk60 >= a1->Unk60)
        {
            a1->Unk1852 += 5;
            ++a1->Unk1856;

            if(a1->Unk1852 > 155)
                a1->Unk1852 = 155;

            if(a1->Unk1856 > 110)
                a1->Unk1856 = 110;
        }
    }
    else
    {
        a1->Unk1852 -= 10;
        --a1->Unk1856;

        if(!a2->IsSetPlayerState(8))
            a1->Unk1852 -= 10;

        if(a1->Unk1852 < -155)
            a1->Unk1852 = -155;

        if(a1->Unk1856 < -110)
            a1->Unk1856 = -110;
    }

    if(a1->Unk1852 < -9 && (!v4 || a1->Unk1860 <= 0))
        a1->Unk1860 = 36000;

    a1->Unk473 = 1;

    CNetMsg v3;

    CharStatusMsg(v3, a1, 0);
    a1->Unk412->SendToCell(v3, a1, 0, 4);
    a1->Unk473 = 1;
}
