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

#include "Character.h"

#include "NPC.h"
#include "PC.h"

CCharacter::CCharacter(void)
{
    this->Unk0   = -1;
    this->Unk4   = -1;
    *this->Unk8   = 0;
    this->Unk60  = 0;
    this->Unk64  = 0;
    this->Unk72  = 0;
    this->Unk78  = 0;
    this->Unk76  = 0;
    this->Unk82  = 0;
    this->Unk80  = 0;
    this->Unk112 = 0;
    this->Unk114 = 0;
    this->Unk84  = 0;
    this->Unk86  = 0;
    this->Unk88  = 0;
    this->Unk90  = 0;
    this->Unk92  = 0;
    this->Unk94  = 0;
    this->Unk96  = 0;
    this->Unk98  = 0;
    this->Unk100 = 0;
    this->Unk102 = 0;
    this->Unk103 = 0;
    this->Unk104 = 0;
    this->Unk108 = 0;
    this->Unk116 = 0;
    this->Unk120.__as(CPos(0.0, 0.0, 0.0, 0.0, 0));
    this->Unk140 = -100;
    this->Unk144 = -100;
    this->Unk148.Init(this);
    this->Unk396 = 0;
    this->Unk400 = 0;
    this->Unk404 = 0;
    this->Unk408 = 0;
    this->Unk412 = 0;
    this->Unk416 = 0;
    this->Unk420 = 1;
    this->Unk424 = 0;
    this->Unk428 = 0;
    this->Unk430 = 0;
    this->Unk432 = 0;
    this->Unk434 = 0;
    this->Unk436 = 0;
    this->Unk438 = 0;
    this->Unk440 = 0;
    this->Unk442 = 0;
    this->Unk444 = 0;
    this->Unk446 = 0;
    this->Unk448 = 0;
    this->Unk450 = 0;
    this->Unk452 = 0;
    this->Unk454 = 0;
    this->Unk456 = 0;
    this->Unk458 = 0;
}

CCharacter::~CCharacter()
{
    this->Unk0 = -1;
    this->Unk4 = -1;
}

void CCharacter::SetVisible(void)
{
    CNetMsg v2;

    if(this->Unk420)
    {
        DelAttackList(this);
        DisappearMsg(v2, this);

        this->Unk420 = 0;

        if(!this->Unk0)
            ((CPC *)this)->Unk474 = 1;
    }
    else
    {
        this->Unk420 ^= 1;
        AppearMsg(v2, this, 1);
    }

    this->Unk412->SendToCell(v2, this, 0, 4);
}

void CCharacter::SendDisappearAllInCell(void)
{
    CItem *v2; // [sp+1Ch] [bp-38h]@19
    CItem *v3; // [sp+20h] [bp-34h]@20
    CCharacter *v4; // [sp+24h] [bp-30h]@13
    CCharacter *v5; // [sp+28h] [bp-2Ch]@14
    int v6; // [sp+2Ch] [bp-28h]@3
    int v7; // [sp+30h] [bp-24h]@3

    CNetMsg v10;

    DisappearMsg(v10, this);
    this->Unk412->SendToCell(v10, this, 0, 4);

    if(this->Unk0)
        return;

    v7 = this->Unk140;
    v6 = this->Unk144;

    for(int i = v7 - 4; i <= v7 + 4; ++i)
    {
        if(i >= 0 && i < this->Unk412->Unk12)
        {
            for(int j = v6 - 4; j <= v6 + 4; ++j)
            {
                if(j >= 0 && j < this->Unk412->Unk16)
                {
                    v4 = this->Unk412->Unk28[i][j].Unk0;

                    while(1)
                    {
                        v5 = v4;

                        if(!v4)
                            break;

                        v4 = v4->Unk404;

                        if(v5 != this)
                        {
                            DisappearMsg(v10, v5);

                            if(((CPC *)this)->Unk768)
                                ((CPC *)this)->Unk768->WriteToOutput(v10);
                        }
                    }

                    v2 = this->Unk412->Unk28[i][j].Unk4;

                    while(1)
                    {
                        v3 = v2;

                        if(!v2)
                            break;

                        v2 = v2->Unk208;
                        ItemDisappearMsg(v10, v3);

                        if(((CPC *)this)->Unk768)
                            ((CPC *)this)->Unk768->WriteToOutput(v10);
                    }
                }
            }
        }
    }
}

bool CCharacter::CanApplySkill(CSkillProto const *a2, CSkillLevelProto const *a3)
{
    if(a2->Unk52 & 1 && this->Unk76 > 0)
        return false;

    if((a2->Unk52 ^ 1) & 1 && this->Unk76 <= 0)
        return false;

    if(this->Unk0)
        goto LABEL_36;

    if(a2->Unk52 & 2 && !((CPC *)this)->Unk1284[2]) // 1292 = 1284 + 8
        return false;

    if((!(a2->Unk52 & 0x20) || !(a2->Unk52 & 4)) && (a2->Unk52 & 4 || a2->Unk52 & 0x20))
    {
        if(a2->Unk52 & 4 && !((CPC *)this)->IsSetPlayerState(1))
            return false;

        if(a2->Unk52 & 0x20 && ((CPC *)this)->IsSetPlayerState(1))
            return false;
    }

    if(!(a2->Unk52 & 0x10) || ((CPC *)this)->Unk1284[4]) // 1300 = 1284 + 16
    {
LABEL_36:
        if(a2->Unk52 & 8 && this->IsInPeaceZone())
        {
            return false;
        }
        else
        {
            for(int i = 0; i <= 2; ++i)
               {
                if(a3->Unk72[i] >= 0 && !this->Unk148.Find(a3->Unk72[i], a3->Unk84[i]))
                    return false;
            }

            return true;
        }
    }

    return false;
}

bool CCharacter::CanMove(void)
{
    if(this->Unk148.Unk240 & 2)
        return false;

    if(this->Unk148.Unk240 & 0x80)
        return false;

    if(this->Unk148.Unk240 & 0x100)
        return false;

    return true;
}

bool CCharacter::CanAttack(void)
{
    if(this->Unk148.Unk240 & 8)
        return false;

    if(this->Unk148.Unk240 & 0x80)
        return false;

    if(this->Unk148.Unk240 & 0x100)
        return false;

    return true;
}

bool CCharacter::CanSpell(void)
{
    if(this->Unk148.Unk240 & 0x10)
        return false;

    if(this->Unk148.Unk240 & 0x80)
        return false;

    if(this->Unk148.Unk240 & 0x100)
        return false;

    return true;
}

void CCharacter::ApplyAssistData(_tagAssistValue *a2, _tagAssistValue *a3)
{
    this->Unk102 -= a2[7];
    this->Unk102 -= ((signed int)((unsigned long long)(0x68DB8BAD * (a2[7] * this->Unk102)) >> 32) >> 12) - ((a2[7] * this->Unk102) >> 31);
    this->Unk103 += a2[8];
    this->Unk103 += ((signed int)((unsigned long long)(0x68DB8BAD * (a2[8] * this->Unk103)) >> 32) >> 12) - ((a2[8] * this->Unk103) >> 31);
    this->Unk108 = (long double)*(signed int *)(a2 + 36) / 10.0 + this->Unk108;
    this->Unk108 = (long double)*(signed int *)(a3 + 36) * this->Unk108 / 10000.0 + this->Unk108;
    this->Unk78 += a2[12];
    this->Unk78 += ((signed int)((unsigned long long)(0x68DB8BAD * (a2[12] * this->Unk78)) >> 32) >> 12) - ((a2[12] * this->Unk78) >> 31);
    this->Unk82 += a2[13];
    this->Unk82 += ((signed int)((unsigned long long)(0x68DB8BAD * (a2[13] * this->Unk82)) >> 32) >> 12) - ((a2[13] * this->Unk82) >> 31);

    if(this->Unk92)
        this->Unk108 = 8.0;

    if(this->Unk148.Unk240 & 0x4000)
    {
        this->Unk108 = (long double)this->Unk148.Unk40[24] + this->Unk108; // 284 = 148 + 40 + 96
        this->Unk108 = (long double)this->Unk148.Unk140[24] * this->Unk108 / 10000.0 + this->Unk108; // 384 = 148 + 140 + 96
    }
}

bool CCharacter::IsInPeaceZone(void)
{
    int v2; // eax@3

    if(!this->Unk412)
        return true;

    v2 = this->Unk412->GetAttr(this->Unk120.Unk16, this->Unk120.Unk0, this->Unk120.Unk4);

    if(v2 == 20)
        return true;

    if(v2 <= 20)
    {
        if(v2 != 10)
            return false;

        return true;
    }

    if(v2 == 30)
        return true;

    return false;
}

void CCharacter::Move(float a2, float a3, float a4, float a5, int a6)
{
    this->Unk120.__as(CPos(a2, a3, a4, a5, a6));
}

void CCharacter::InitPointsToMax(void)
{
    this->Unk76 = this->Unk78;
    this->Unk80 = this->Unk82;
}
