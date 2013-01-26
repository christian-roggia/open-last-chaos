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

#include "CmdMsg.h"

#include "Character.h"
#include "Guild.h"
#include "Item.h"
#include "NPC.h"
#include "PC.h"
#include "Quest.h"
#include "Server.h"

void AppearMsg(CNetMsg &a1, CCharacter *a2, bool a3) // FULL CHECKED
{
    if(a2->Unk420)
    {
        a1.Init(7);

        if(a2)
        {
            if(a2->Unk78 <= 0)
                a2->Unk78 = 1;

            if(a2->Unk0 == 1)
            {
                if(((CNPC *)a2)->Unk468 > 0 && ((CNPC *)a2)->Unk488 <= 0)
                {
                    a1.__ls((char )(a3 ? 1 : 0));
                    a1.__ls((char )(a2->Unk0 == 1));
                    a1.__ls((int  )a2->Unk4);
                    a1.__ls((int  )((CNPC *)a2)->Unk468);
                    a1.__ls((float)a2->Unk120.Unk0);
                    a1.__ls((float)a2->Unk120.Unk4);
                    a1.__ls((float)((a2 && a2->Unk412) ? a2->Unk412->GetHeight(a2->Unk120.Unk16, a2->Unk120.Unk0, a2->Unk120.Unk4) : 0.0));
                    a1.__ls((float)a2->Unk120.Unk12);
                    a1.__ls((char )a2->Unk120.Unk16);
                    a1.__ls((short)a2->Unk76);
                    a1.__ls((short)a2->Unk78);

                    a2->Unk148.AppendAssistToNetMsg(a1);
                }
                else
                {
                    a1.Init();
                }
            }
            else
            {
                a1.__ls((char )(a3 ? 1 : 0));
                a1.__ls((char )(a2->Unk0 == 1));
                a1.__ls((int  )a2->Unk4);
                a1.__ls((char const *)a2->Unk8);
                a1.__ls((char )((CPC *)a2)->Unk477);
                a1.__ls((char )((CPC *)a2)->Unk478);
                a1.__ls((char )((CPC *)a2)->Unk479);
                a1.__ls((float)a2->Unk120.Unk0);
                a1.__ls((float)a2->Unk120.Unk4);
                a1.__ls((float)((a2 && a2->Unk412) ? a2->Unk412->GetHeight(a2->Unk120.Unk16, a2->Unk120.Unk0, a2->Unk120.Unk4) : 0.0));
                a1.__ls((float)a2->Unk120.Unk12);
                a1.__ls((char )a2->Unk120.Unk16);
                a1.__ls((short)a2->Unk76);
                a1.__ls((short)a2->Unk78);
                a1.__ls((char )((CPC *)a2)->GetPlayerState());
                a1.__ls((int  )((CPC *)a2)->Unk1852);
                a1.__ls((char )((CPC *)a2)->GetPKName());

                for(int i = 1; i <= 6; ++i)
                {
                    if(((CPC *)a2)->Unk1284[i])
                        a1.__ls((int)((CPC *)a2)->Unk1284[i]->Unk28);
                    else
                        a1.__ls((int)-1);
                }

                a2->Unk148.AppendAssistToNetMsg(a1);

                if(((CPC *)a2)->Unk1328)
                {
                    a1.__ls((char)((CPC *)a2)->Unk1328->GetType());
                    a1.__ls((char const *)((CPC *)a2)->Unk1328->GetName());
                }
                else
                {
                    a1.__ls((char)0);
                    a1.__ls((char const *)"");
                }

                if(((CPC *)a2)->Unk2368)
                {
                    a1.__ls((int)((CPC *)a2)->Unk2368->guild()->index());
                    a1.__ls((char const *)((CPC *)a2)->Unk2368->guild()->name());
                    a1.__ls((int)((CPC *)a2)->Unk2368->pos());
                }
                else
                {
                    a1.__ls((int)-1);
                    a1.__ls((char const *)"");
                    a1.__ls((int)-1);
                }

                a1.__ls((int)((CPC *)a2)->Unk2388);
            }
        }
    }
    else
    {
        a1.Init();
    }
}

void DisappearMsg(CNetMsg &a1, CCharacter *a2) // FULL CHECKED
{
    if(a2)
    {
        if(a2->Unk420)
        {
            a1.Init(8);
            a1.__ls((char)a2->Unk0 == 1);
            a1.__ls((int )a2->Unk4);
        }
        else
        {
            a1.Init();
        }
    }
}

void MoveMsg(CNetMsg &a1, __tagMsgMoveType a2, CCharacter *a3) // FULL CHECKED
{
    if(a3->Unk420)
    {
        a1.Init(12);
        a1.__ls((char)a3->Unk0 == 1);
        a1.__ls((char)a2);
        a1.__ls((int)a3->Unk4);

        if(a2)
        {
            if(a2 == 1)
                a1.__ls((float)a3->Unk108);
            else
                a1.__ls((float)0.0);
        }
        else
        {
            a1.__ls((float)a3->Unk104);
        }

        a1.__ls((float)a3->Unk120.Unk0);
        a1.__ls((float)a3->Unk120.Unk4);
        a1.__ls((float)((a3 && a3->Unk412) ? a3->Unk412->GetHeight(a3->Unk120.Unk16, a3->Unk120.Unk0, a3->Unk120.Unk4) : 0.0));
        a1.__ls((float)(a3->Unk120.Unk12));
        a1.__ls((char )(a3->Unk120.Unk16));
    }
    else
    {
        a1.Init();
    }
}

void StatusMsg(CNetMsg &a1, CPC *a2) // FULL CHECKED
{
    short v2; // ST17C_2@8
    short v3; // ST17A_2@8
    short v4; // ST178_2@8
    short v5; // ST17E_2@8
    short v6; // ST17C_2@8
    short v7; // ST17A_2@8
    short v8; // ST178_2@8
    unsigned short v9; // ST17E_2@8
    unsigned short v10; // ST17C_2@8
    unsigned short v11; // ST17A_2@8
    unsigned short v12; // ST178_2@8
    short v62; // [sp+26h] [bp-Ah]@1

    a1.Init(6);

    v62 = 0;

    if(!a2->Unk1284[2] || a2->Unk1284[2]->Unk20) // + 1292 = 1284 + 8
    {
        if(a2->Unk1284[2] && a2->Unk1284[2]->IsRangeWeapon())
            v62 = a2->Unk94 + a2->Unk86 / 2 + a2->Unk438;
        else
            v62 = a2->Unk92 + a2->Unk84 / 2 + a2->Unk436;
    }
    else
    {
        strcpy(g_buf3, "ERR:ITEM:PROTO:");
        strcat(g_buf3, a2->Unk8);
        strcat(g_buf3, ":");
        IntCat(g_buf3, a2->Unk1284[2]->Unk28, true);
        puts(g_buf3);
    }

    v2 = a2->Unk96 + a2->Unk88 / 2 + a2->Unk452;
    v3 = a2->Unk444 + a2->Unk98 + a2->Unk446;
    v4 = a2->Unk456 + a2->Unk100;

    v5 = ((int)((unsigned long long)(0x68DB8BAD * a2->Unk616[0] * (int)v62) >> 32) >> 12) - (a2->Unk616[0] * (int)v62 >> 31) + a2->Unk516[0] + v62;
    v6 = ((int)((unsigned long long)(0x68DB8BAD * a2->Unk616[2] * (int)v2 ) >> 32) >> 12) - (a2->Unk616[2] * (int)v2  >> 31) + a2->Unk516[2] + v2;
    v7 = ((int)((unsigned long long)(0x68DB8BAD * a2->Unk616[1] * (int)v3 ) >> 32) >> 12) - (a2->Unk616[1] * (int)v3  >> 31) + a2->Unk516[1] + v3;
    v8 = ((int)((unsigned long long)(0x68DB8BAD * a2->Unk616[3] * (int)v4 ) >> 32) >> 12) - (a2->Unk616[3] * (int)v4  >> 31) + a2->Unk516[3] + v4;

    v9  = ((signed int)((unsigned long long)(0x68DB8BAD * a2->Unk148.Unk140[0] * (signed int)v5) >> 32) >> 12) - (a2->Unk148.Unk140[0] * (signed int)v5 >> 31) + a2->Unk148.Unk40[0] + v5; // + 288 = 148 + 140 + 0 , 188 = 148 + 40 + 0
    v10 = ((signed int)((unsigned long long)(0x68DB8BAD * a2->Unk148.Unk140[2] * (signed int)v6) >> 32) >> 12) - (a2->Unk148.Unk140[2] * (signed int)v6 >> 31) + a2->Unk148.Unk40[2] + v6; // + 296 = 148 + 140 + 8 , 196 = 148 + 40 + 8
    v11 = ((signed int)((unsigned long long)(0x68DB8BAD * a2->Unk148.Unk140[1] * (signed int)v7) >> 32) >> 12) - (a2->Unk148.Unk140[1] * (signed int)v7 >> 31) + a2->Unk148.Unk40[1] + v7; // + 292 = 148 + 140 + 4 , 192 = 148 + 40 + 4
    v12 = ((signed int)((unsigned long long)(0x68DB8BAD * a2->Unk148.Unk140[3] * (signed int)v8) >> 32) >> 12) - (a2->Unk148.Unk140[3] * (signed int)v8 >> 31) + a2->Unk148.Unk40[3] + v8; // + 300 = 148 + 140 + 12, 200 = 148 + 40 + 12

    a1.__ls((short)a2->Unk60);
    a1.__ls((long long)a2->Unk64);
    a1.__ls((long long)GetLevelupExp(a2->Unk60));
    a1.__ls((short)a2->Unk76);
    a1.__ls((short)a2->Unk78);
    a1.__ls((short)a2->Unk80);
    a1.__ls((short)a2->Unk82);
    a1.__ls((short)(a2->Unk428 + a2->Unk742));
    a1.__ls((short)(a2->Unk430 + a2->Unk744));
    a1.__ls((short)(a2->Unk432 + a2->Unk746));
    a1.__ls((short)(a2->Unk434 + a2->Unk748));
    a1.__ls((short)a2->Unk428);
    a1.__ls((short)a2->Unk430);
    a1.__ls((short)a2->Unk432);
    a1.__ls((short)a2->Unk434);
    a1.__ls((short)v9);
    a1.__ls((short)v10);
    a1.__ls((short)v11);
    a1.__ls((short)v12);
    a1.__ls((int)a2->Unk72);
    a1.__ls((int)a2->Unk724);
    a1.__ls((int)a2->Unk728);
    a1.__ls((float)a2->Unk104);
    a1.__ls((float)a2->Unk108);
    a1.__ls((char)a2->Unk102);
    a1.__ls((char)a2->Unk103);
    a1.__ls((char)a2->GetPKName());
    a1.__ls((int)a2->Unk1852);
    a1.__ls((int)a2->Unk1856);
}

void AtMsg(CNetMsg &a1, CPC *a2) // FULL CHECKED
{
    a1.Init(9);

    a1.__ls((int  )a2->Unk4);
    a1.__ls((char const *)a2->Unk8);
    a1.__ls((char )a2->Unk477);
    a1.__ls((char )a2->Unk478);
    a1.__ls((char )a2->Unk479);
    a1.__ls((int  )a2->Unk408->Unk0);
    a1.__ls((int  )a2->Unk412->Unk8);
    a1.__ls((float)a2->Unk120.Unk0);
    a1.__ls((float)a2->Unk120.Unk4);
    a1.__ls((float)((a2 && a2->Unk412) ? a2->Unk412->GetHeight(a2->Unk120.Unk16, a2->Unk120.Unk0, a2->Unk120.Unk4) : 0.0));
    a1.__ls((float)a2->Unk120.Unk12);
    a1.__ls((char )a2->Unk120.Unk16);
    a1.__ls((int  )a2->Unk768->Unk0);
    a1.__ls((int  )a2->Unk2376);
}

void SayMsg(CNetMsg &a1, __tagMsgChatType a2, int a3, char const *a4, char const *a5, char const *a6) // FULL CHECKED
{
    a1.Init(15);

    a1.__ls((unsigned char)a2);
    a1.__ls((int)a3);
    a1.__ls((char const *)a4);
    a1.__ls((char const *)a5);
    a1.__ls((char const *)a6);
}

void GotoMsg(CNetMsg &a1, CPC *a2) // FULL CHECKED
{
    a1.Init(19);

    a1.__ls((int  )((a2->Unk408) ? a2->Unk408->Unk0 : -1));
    a1.__ls((float)(a2->Unk120.Unk0));
    a1.__ls((float)(a2->Unk120.Unk4));
    a1.__ls((float)((a2 && a2->Unk412) ? a2->Unk412->GetHeight(a2->Unk120.Unk16, a2->Unk120.Unk0, a2->Unk120.Unk4) : 0.0));
    a1.__ls((float)(a2->Unk120.Unk12));
    a1.__ls((char )(a2->Unk120.Unk16));
}

void FailMsg(CNetMsg &a1, __tagMsgFailType a2) // FULL CHECKED
{
    a1.Init(1);
    a1.__ls((unsigned char)a2);
}

//void DamageMsg__FR7CNetMsgP10CCharacterT114_tagDamageTypeisc
void DamageMsg(CNetMsg &a1, CCharacter *a2, CCharacter *a3, _tagDamageType a4, int a5, short a6, char a7) // FULL CHECKED
{
    a1.Init(14);

    a1.__ls((char)(a2->Unk0 == 1));
    a1.__ls((int)a2->Unk4);
    a1.__ls((char)a4);
    a1.__ls((int)a5);
    a1.__ls((char)(a3->Unk0 == 1));
    a1.__ls((int)a3->Unk4);
    a1.__ls((short)a3->Unk76);
    a1.__ls((short)a3->Unk80);
    a1.__ls((short)a6);

    if(a4 > 2 || a4 < 0) // CHECK -> Always false
        a1.__ls((char)0);
    else
        a1.__ls((char)a2->Unk102);

    a1.__ls((char)a7);
}

bool InventoryMsg(CNetMsg &a1, CPC *a2, char a3, int a4, int a5)
{
    CInventory *v5; // eax@2

    CItem *v25; // [sp+14h] [bp-14h]@13
    CInventory *v28; // [sp+20h] [bp-8h]@8

    if(a4)
    {
        if(a4 == 1)
        {
            v5 = &a2->Unk880;
        }
        else
        {
            if(a4 == 2)
                v5 = &a2->Unk968;
            else
                v5 = 0;
        }
    }
    else
    {
        v5 = &a2->Unk792;
    }

    v28 = v5;

    if(v5 && v5->Unk8[a5])
    {
        a1.Init(10);

        a1.__ls(a3);
        a1.__ls(a4);
        a1.__ls(a5);

        for(int i = 0; i <= 4; ++i)
        {
            v25 = v28->GetItem(a5, i);
            if(v25)
            {
                a1.__ls((int)v25->Unk24);
                a1.__ls((int)v25->Unk28);
                a1.__ls((char)v25->Unk32);
                a1.__ls((int)v25->Unk36);
                a1.__ls((int)v25->Unk40);
                a1.__ls((int)v25->Unk64);
                a1.__ls((long long)v25->Count());
                a1.__ls((char)v25->Unk168);

                for(int j = 0; j < v25->Unk168; ++j)
                {
                    a1.__ls((char)v25->Unk68[j].Unk4); // 72 = 68 + 4
                    a1.__ls((char)v25->Unk68[j].Unk8); // 76 = 68 + 8
                }
            }
            else
            {
                a1.__ls((int)-1);
            }
        }
        return true;
    }

    a1.Init();

    return false;
}

void WearingMsg(CNetMsg &a1, CPC *a2, char a3, int a4)
{
    if(a2->Unk420)
    {
        a1.Init(11);
        a1.__ls((int )a2->Unk4);
        a1.__ls((char)a3);
        a1.__ls((int )a4);
    }
    else
    {
        a1.Init();
    }
}

void ItemUseMsg(CNetMsg &a1, CPC *a2, char a3, char a4, char a5, int a6, int a7)
{
    a1.Init(16);

    a1.__ls((int )0);
    a1.__ls((char)a3);
    a1.__ls((char)a4);
    a1.__ls((char)a5);
    a1.__ls((int )a6);
    a1.__ls((int )a7);
}

void ItemTakeMsg(CNetMsg &a1, CPC *a2, CItem *a3)
{
    a1.Init(16);

    a1.__ls((int)1);
    a1.__ls((int)a2->Unk4);
    a1.__ls((int)a3->Unk24);
}

void ItemDeleteMsg(CNetMsg &a1, CItem *a2)
{
    a1.Init(16);

    a1.__ls((int)4);
    a1.__ls((char)a2->tab());
    a1.__ls((char)a2->row());
    a1.__ls((char)a2->col());
}

void ItemWearMsg(CNetMsg &a1, char a2, CItem *a3, CItem *a4)
{
    a1.Init(16);

    a1.__ls((int)5);
    a1.__ls((char)a2);

    if(a3)
    {
        a1.__ls((char)a3->tab());
        a1.__ls((char)a3->row());
        a1.__ls((char)a3->col());
        a1.__ls((unsigned int)a3->Unk24);
    }
    else
    {
        a1.__ls((char)0);
        a1.__ls((char)0);
        a1.__ls((char)0);
        a1.__ls((unsigned int)-1);
    }

    if(a4)
    {
        a1.__ls((char)a4->tab());
        a1.__ls((char)a4->row());
        a1.__ls((char)a4->col());
        a1.__ls((unsigned int)a4->Unk24);
    }
    else
    {
        a1.__ls((char)0);
        a1.__ls((char)0);
        a1.__ls((char)0);
        a1.__ls((unsigned int)-1);
    }
}

void ItemSwapMsg(CNetMsg &a1, char a2, char a3, char a4, int a5, char a6, char a7, int a8)
{
    a1.Init(16);

    a1.__ls(6);
    a1.__ls((char)a2);
    a1.__ls((char)a3);
    a1.__ls((char)a4);
    a1.__ls((char)a6);
    a1.__ls((char)a7);
}

void ItemAddMsg(CNetMsg &a1, CItem *a2)
{
    a1.Init(16);

    a1.__ls(7);
    a1.__ls(a2->tab());
    a1.__ls(a2->row());
    a1.__ls(a2->col());
    a1.__ls(a2->Unk24);
    a1.__ls(a2->Unk28);
    a1.__ls(a2->Unk32);
    a1.__ls(a2->Unk36);
    a1.__ls(a2->Unk40);
    a1.__ls(a2->Unk64);
    a1.__ls(a2->Count());
    a1.__ls(a2->Unk168);

    for(int i = 0; i < a2->Unk168; ++i)
    {
        a1.__ls(a2->Unk68[i].Unk4);
        a1.__ls(a2->Unk68[i].Unk8);
    }
}

void ItemUpdateMsg(CNetMsg &a1, CItem *a2, long long a3)
{
    a1.Init(16);

    a1.__ls(8);
    a1.__ls(a2->tab());
    a1.__ls(a2->row());
    a1.__ls(a2->col());
    a1.__ls(a2->Unk24);
    a1.__ls(a2->Unk36);
    a1.__ls(a2->Unk40);
    a1.__ls(a2->Unk64);
    a1.__ls(a2->Count());
    a1.__ls(a3);
    a1.__ls(a2->Unk168);

    for(int i = 0; i < a2->Unk168; ++i)
    {
        a1.__ls(a2->Unk68[i].Unk4);
        a1.__ls(a2->Unk68[i].Unk8);
    }
}

void ItemDropMsg(CNetMsg &a1, CCharacter *a2, CItem *a3)
{
    a1.Init(16);

    a1.__ls(9);
    a1.__ls(a3->Unk24);
    a1.__ls(a3->Unk28);
    a1.__ls(a3->Count());
    a1.__ls(a3->Unk176.Unk0);
    a1.__ls(a3->Unk176.Unk4);

    if(a2->Unk408->Unk0 != 2 && a2->Unk408->Unk0 != 5 && a2->Unk408->Unk0 != 6 && a2->Unk408->Unk0 != 8)
    {
        a1.__ls(((a3 && a3->Unk172) ? (a3->Unk172->GetHeight(a3->Unk176.Unk16, a3->Unk176.Unk0, a3->Unk176.Unk4) + 1.0) : 1.0));
    }
    else
    {
        a1.__ls((a3->Unk176.Unk8 + 1.0));
    }

    a1.__ls(a3->Unk176.Unk12);
    a1.__ls(a3->Unk176.Unk16);
    a1.__ls((a2->Unk0 == 1));
    a1.__ls(a2->Unk4);
}

void ItemAppearMsg(CNetMsg &a1, CItem *a2)
{
    a1.Init(16);

    a1.__ls(10);
    a1.__ls(a2->Unk24);
    a1.__ls(a2->Unk28);
    a1.__ls(a2->Count());
    a1.__ls(a2->Unk176.Unk0);
    a1.__ls(a2->Unk176.Unk4);
    a1.__ls(((a2 && a2->Unk172) ? (a2->Unk172->GetHeight(a2->Unk176.Unk16, a2->Unk176.Unk0, a2->Unk176.Unk4) + 1.0) : 1.0));
    a1.__ls(a2->Unk176.Unk12);
    a1.__ls(a2->Unk176.Unk16);
}

void ItemDisappearMsg(CNetMsg &a1, CItem *a2)
{
    a1.Init(16);

    a1.__ls((int)11);
    a1.__ls((int)a2->Unk24);
}

void ItemUpgradeRepMsg(CNetMsg &a1, char a2)
{
    a1.Init(16);

    a1.__ls((int)15);
    a1.__ls((char)a2);
}

void ItemRefineRepMsg(CNetMsg &a1, char a2) // FULL CHECKED
{
    a1.Init(16);

    a1.__ls((unsigned char)17);
    a1.__ls((char)a2);
}

void ItemOptionAddRepMsg(CNetMsg &a1, CItem *a2, _tagItemOptionAddResult a3) // FULL CHECKED
{
    a1.Init(16);

    a1.__ls((unsigned char)19);
    a1.__ls((char)a3);
}

void ItemOptionDelRepMsg(CNetMsg &a1, CItem *a2, _tagItemOptionDelResult a3) // FULL CHECKED
{
    a1.Init(16);

    a1.__ls((unsigned char)21);
    a1.__ls((char)a3);
}

void ItemProcessRepMsg(CNetMsg &a1, _tagProcessResult a2) // FULL CHECKED
{
    a1.Init(16);

    a1.__ls((unsigned char)23);
    a1.__ls((char)a2);
}

void ItemMakeRepMsg(CNetMsg &a1, _tagMakeResult a2) // FULL CHECKED
{
    a1.Init(16);

    a1.__ls((unsigned char)25);
    a1.__ls((char)a2);
}

void ItemMixRepMsg(CNetMsg &a1, _tagItemMixResult a2) // FULL CHECKED
{
    a1.Init(16);

    a1.__ls((unsigned char)27);
    a1.__ls((char)a2);
}

void ItemArcaneRepMsg(CNetMsg &a1, _tagItemArcaneResult a2) // FULL CHECKED
{
    a1.Init(16);

    a1.__ls((unsigned char)30);
    a1.__ls((char)a2);
}

void ItemGetMsg(CNetMsg &a1, CPC *a2, CItem *a3) // FULL CHECKED
{
    a1.Init(16);

    a1.__ls((unsigned char)28);
    a1.__ls((char const *)a2->Unk8);
    a1.__ls((int)a3->Unk20->Unk0);
    a1.__ls((long long)a3->Count());
}

void DBCharEndMsg(CNetMsg &a1) // FULL CHECKED
{
    a1.Init(2);

    a1.__ls((unsigned char)3);
}

void DBCharExistMsg(CNetMsg &a1, int a2, char const *a3, char a4, char a5, char a6, short a7, long long a8, int a9, short a10, short a11, short a12, short a13, int *a14) // FULL CHECKED
{
    a1.Init(2);

    a1.__ls((unsigned char)2);
    a1.__ls((int)a2);
    a1.__ls((char const *)a3);
    a1.__ls((char)a4);
    a1.__ls((char)a5);
    a1.__ls((char)a6);
    a1.__ls((short)a7);
    a1.__ls((long long)a8);
    a1.__ls((long long)GetLevelupExp(a7));
    a1.__ls((int)a9);
    a1.__ls((short)((a10 > a11) ? a11 : a10));
    a1.__ls((short)a11);
    a1.__ls((short)((a12 > a13) ? a13 : a12));
    a1.__ls((short)a13);

    for(int i = 1; i <= 6; ++i)
        a1.__ls((int)a14[i-1]);
}

void DBSuccessMsg(CNetMsg &a1) // FULL CHECKED
{
    a1.Init(2);

    a1.__ls((unsigned char)0);
}

void DBOtherServerMsg(CNetMsg &a1, int a2, char const *a3, int a4) // FULL CHECKED
{
    a1.Init(2);

    a1.__ls((unsigned char)4);
    a1.__ls((int)a2);
    a1.__ls((char const *)a3);
    a1.__ls((int)a4);
}

void DBOKMsg(CNetMsg &a1, int a2) // FULL CHECKED
{
    a1.Init(2);

    a1.__ls((unsigned char)1);
    a1.__ls((int)a2);
}

void MsgrRepWhisperNotFoundMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, int a6, char const *a7) // FULL CHECKED
{
    a1.Init(102);

    a1.__ls((int)a2);
    a1.__ls((int)a3);
    a1.__ls((int)a4);
    a1.__ls((int)a5);
    a1.__ls((unsigned char)3);
    a1.__ls((int)a6);
    a1.__ls((char const *)a7);
}

void ChatWhisperMsg(CNetMsg &a1, int a2, char const *a3, char const *a4, char const *a5) // FULL CHECKED
{
    a1.Init(15);

    a1.__ls((unsigned char)4);
    a1.__ls((int)a2);
    a1.__ls((char const *)a3);
    a1.__ls((char const *)a4);
    a1.__ls((char const *)a5);
}

void MsgrRepWhisperRepMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, int a6, char const *a7, char const *a8, char const *a9) // FULL CHECKED
{
    a1.Init(102);

    a1.__ls((int)a2);
    a1.__ls((int)a3);
    a1.__ls((int)a4);
    a1.__ls((int)a5);
    a1.__ls((unsigned char)1);
    a1.__ls((int)a6);
    a1.__ls((char const *)a7);
    a1.__ls((char const *)a8);
    a1.__ls((char const *)a9);
}

void SysWhisperNotFoundMsg(CNetMsg &a1) // FULL CHECKED
{
    a1.Init(17);
    a1.__ls((unsigned char)0);
}

void MsgrConnectMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, int *a6) // FULL CHECKED
{
    a1.Init(100);

    a1.__ls((int)a2);
    a1.__ls((int)a3);
    a1.__ls((int)a4);
    a1.__ls((int)a5);

    for(int i = 0; i < a5; ++i)
        a1.__ls((int)a6[i]);
}

void MsgrWhisperReqMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, char const *a6, char const *a7, char const *a8) // FULL CHECKED
{
    a1.Init(101);

    a1.__ls((int)a2);
    a1.__ls((int)a3);
    a1.__ls((int)a4);
    a1.__ls((int)-1);
    a1.__ls((unsigned char)0);
    a1.__ls((int)a5);
    a1.__ls((char const *)a6);
    a1.__ls((char const *)a7);
    a1.__ls((char const *)a8);
}

void MsgrGuildChatMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, char const *a6, int a7, char const *a8) // FULL CHECKED
{
    a1.Init(101);

    a1.__ls((int)a2);
    a1.__ls((int)a3);
    a1.__ls((int)a4);
    a1.__ls((int)-1);
    a1.__ls((unsigned char)4);
    a1.__ls((int)a5);
    a1.__ls((char const *)a6);
    a1.__ls((int)a7);
    a1.__ls((char const *)a8);
}

void SysFullInventoryMsg(CNetMsg &a1, char a2) // FULL CHECKED
{
    a1.Init(17);

    a1.__ls((unsigned char)3);
    a1.__ls((char)a2);
}

void SysMsg(CNetMsg &a1, _tagMsgSysType a2) // FULL CHECKED
{
    a1.Init(17);

    a1.__ls((unsigned char)a2);
}

void SysSkillInsuffMsg(CNetMsg &a1, char a2) // FULL CHECKED
{
    a1.Init(17);

    a1.__ls((unsigned char)13);
    a1.__ls((char)a2);
}

void SysSkillInvalState(CNetMsg &a1, char a2) // FULL CHECKED
{
    a1.Init(17);

    a1.__ls((unsigned char)27);
    a1.__ls((char)a2);
}

void SysBloodItemMsg(CNetMsg &a1, int a2) // FULL CHECKED
{
    a1.Init(17);

    a1.__ls((unsigned char)37);
    a1.__ls((char)a2);
}

void GoZoneMsg(CNetMsg &a1, int a2, int a3, char const *a4, int a5) // FULL CHECKED
{
    a1.Init(18);

    a1.__ls((int)a2);
    a1.__ls((int)a3);
    a1.__ls((char const *)a4);
    a1.__ls((int)a5);
}

void EnvWeatherMsg(CNetMsg &a1, int a2) // FULL CHECKED
{
    a1.Init(22);

    a1.__ls((unsigned char)1);
    a1.__ls((unsigned char)gserver.Unk452196[a2].Unk44);
}

void EnvTimeMsg(CNetMsg &a1) // FULL CHECKED
{
    a1.Init(22);

    a1.__ls((unsigned char)2);
    a1.__ls((int )(gserver.Unk41252 / 38880000));
    a1.__ls((char)(gserver.Unk41252 % 38880000 / 3240000));
    a1.__ls((char)(gserver.Unk41252 % 38880000 % 3240000 / 108000));
    a1.__ls((char)(gserver.Unk41252 % 38880000 % 3240000 % 108000 / 3600));
    a1.__ls((char)(gserver.Unk41252 % 38880000 % 3240000 % 108000 % 3600 / 60));
    a1.__ls((char)(gserver.Unk41252 % 38880000 % 3240000 % 108000 % 3600 % 60));
}

void EnvTaxChangeMsg(CNetMsg &a1, int a2) // FULL CHECKED
{
    a1.Init(22);

    a1.__ls((unsigned char)0);
    a1.__ls((int)a2);
    a1.__ls((int)gserver.Unk452196[a2].Unk64);
    a1.__ls((int)gserver.Unk452196[a2].Unk68);
}

void ExchangeReqMsg(CNetMsg &a1, _tagMsgExchangeReqType a2, CPC *a3, CPC *a4) // FULL CHECKED
{
    a1.Init(20);

    a1.__ls((unsigned char)0);
    a1.__ls((unsigned char)a2);

    if(!a2)
    {
        a1.__ls((int)a3->Unk4);
        a1.__ls((char const *)a3->Unk8);
        a1.__ls((int)a4->Unk4);
        a1.__ls((char const *)a4->Unk8);
    }
}

void ExchangeItemMsg(CNetMsg &a1, _tagMsgExchangeItemAction a2, CItem *a3, long long a4)
{
    a1.Init(20);

    a1.__ls((unsigned char)1);
    a1.__ls((unsigned char)a2);
    a1.__ls((int)a3->Unk24);

    if(a2 > 5 || a2 < 4)
    {
        a1.__ls((long long)a4);

        if(a2 <= 2 && a2 >= 0)
        {
            a1.__ls((int)a3->Unk28);
            a1.__ls((int)a3->Unk36);
            a1.__ls((int)a3->Unk40);
            a1.__ls((int)a3->Unk64);
            a1.__ls((char)a3->Unk168);

            for(int i = 0; i < a3->Unk168; ++i)
            {
                a1.__ls((char)a3->Unk68[i].Unk4); // 72 = 68 + 4
                a1.__ls((char)a3->Unk68[i].Unk8); // 76 = 68 + 8
            }
        }
    }
}

void MemPosListMsg(CNetMsg &a1, CPC *a2)
{
    a1.Init(21);

    a1.__ls((unsigned char)0);
    a1.__ls((char)a2->Unk1332.Unk0);

    for(int i = 0; i <= 4; ++i)
    {
        if(a2->Unk1332.Unk4[i]) // 1332 + 4
        {
            a1.__ls((int)i);
            a1.__ls((int)a2->Unk1332.Unk4[i]->Unk0);
            a1.__ls((float)a2->Unk1332.Unk4[i]->Unk4);
            a1.__ls((float)a2->Unk1332.Unk4[i]->Unk8);
            a1.__ls((char const *)a2->Unk1332.Unk4[i]->Unk13);
        }
    }
}

void MemPosWriteMsg(CNetMsg &a1, CPC *a2, int a3)
{
    a1.Init(21);

    a1.__ls((unsigned char)1);
    a1.__ls((int)a3);
    a1.__ls((char const *)a2->Unk1332.Unk4[a3]->Unk13);
    a1.__ls((int)a2->Unk1332.Unk4[a3]->Unk0);
    a1.__ls((float)a2->Unk1332.Unk4[a3]->Unk4);
    a1.__ls((float)a2->Unk1332.Unk4[a3]->Unk8);
}

void GMWhoAmIMsg(CNetMsg &a1, CPC *a2) // FULL CHECKED
{
    a1.Init(23);

    a1.__ls((unsigned char)0);
    a1.__ls((unsigned char)a2->Unk732);
}

void GMCommandMsg(CNetMsg &a1, char const *a2)
{
    a1.Init(23);

    a1.__ls((unsigned char)1);
    a1.__ls((char const *)a2);
}

void MsgrNoticeMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, char const *a6)
{
    a1.Init(101);

    a1.__ls((int)a2);
    a1.__ls((int)a3);
    a1.__ls((int)a4);
    a1.__ls((int)a5);
    a1.__ls((unsigned char)5);
    a1.__ls((char const *)a6);
}

void MsgrLogoutReqMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, char const *a6)
{
    a1.Init(101);

    a1.__ls((int)a2);
    a1.__ls((int)a3);
    a1.__ls((int)a4);
    a1.__ls((int)a5);
    a1.__ls((unsigned char)6);
    a1.__ls((char const *)a6);
}

void MsgrLogoutRepMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, char a6, char const *a7)
{
    a1.Init(102);

    a1.__ls((int)a2);
    a1.__ls((int)a3);
    a1.__ls((int)a4);
    a1.__ls((int)a5);
    a1.__ls((unsigned char)9);
    a1.__ls((char)a6);
    a1.__ls((char const *)a7);
}

void MsgrGoZoneReqMsg(CNetMsg &a1, int a2, int a3, int a4, int a5)
{
    a1.Init(101);

    a1.__ls((int)a2);
    a1.__ls((int)gserver.Unk41004);
    a1.__ls((int)gserver.Unk41008);
    a1.__ls((int)a5);
    a1.__ls((unsigned char)10);
    a1.__ls((int)a3);
    a1.__ls((int)a4);
    a1.__ls((int)a5);
}

void MsgrGoZoneRepMsg(CNetMsg &a1, int a2, int a3, char a4, int a5, int a6, int a7)
{
    a1.Init(102);

    a1.__ls((int)a2);
    a1.__ls((int)gserver.Unk41004);
    a1.__ls((int)gserver.Unk41008);
    a1.__ls((int)a3);
    a1.__ls((unsigned char)11);
    a1.__ls((int)a4);
    a1.__ls((int)a5);
    a1.__ls((int)a6);
    a1.__ls((int)a7);
}

void MsgrEndGameReqMsg(CNetMsg &a1)
{
    a1.Init(101);

    a1.__ls((int)-1);
    a1.__ls((int)-1);
    a1.__ls((int)-1);
    a1.__ls((int)-1);
    a1.__ls((unsigned char)12);
}

void MsgrObserverMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, char const *a6)
{
    a1.Init(101);

    a1.__ls((int)a2);
    a1.__ls((int)a3);
    a1.__ls((int)a4);
    a1.__ls((int)a5);
    a1.__ls((unsigned char)13);
    a1.__ls((char const *)a6);
}

void MsgrDoubleEventReqMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, bool a6)
{
    a1.Init(101);

    a1.__ls((int)a2);
    a1.__ls((int)a3);
    a1.__ls((int)a4);
    a1.__ls((int)a5);
    a1.__ls((unsigned char)14);
    a1.__ls((bool)a6);
}

void MsgrDoubleExpEventReqMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, bool a6)
{
    a1.Init(101);

    a1.__ls((int)a2);
    a1.__ls((int)a3);
    a1.__ls((int)a4);
    a1.__ls((int)a5);
    a1.__ls((unsigned char)16);
    a1.__ls((bool)a6);
}

void MsgrLattoEventReqMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, bool a6, int a7, int a8, int a9)
{
    a1.Init(101);

    a1.__ls((int)a2);
    a1.__ls((int)a3);
    a1.__ls((int)a4);
    a1.__ls((int)a5);
    a1.__ls((unsigned char)15);
    a1.__ls((bool)a6);
    a1.__ls((int)a7);
    a1.__ls((int)a8);
    a1.__ls((int)a9);
}

void MsgrNewYearEventReqMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, bool a6, int a7, int a8, int a9)
{
    a1.Init(101);

    a1.__ls((int)a2);
    a1.__ls((int)a3);
    a1.__ls((int)a4);
    a1.__ls((int)a5);
    a1.__ls((unsigned char)17);
    a1.__ls((bool)a6);
    a1.__ls((int)a7);
    a1.__ls((int)a8);
    a1.__ls((int)a9);
}

void MsgrValentineEventReqMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, bool a6, int a7, int a8, int a9)
{
    a1.Init(101);

    a1.__ls((int)a2);
    a1.__ls((int)a3);
    a1.__ls((int)a4);
    a1.__ls((int)a5);
    a1.__ls((unsigned char)18);
    a1.__ls((bool)a6);
    a1.__ls((int)a7);
    a1.__ls((int)a8);
    a1.__ls((int)a9);
}

void QuickSlotAddMsg(CNetMsg &a1, CPC *a2, char a3, char a4)
{
    a1.Init(25);

    a1.__ls((unsigned char)1);
    a1.__ls((char)a3);
    a1.__ls((char)a4);

    if(a2->Unk1372[a3].Unk0[a4] == 0)
    {
        a1.__ls((char)a2->Unk1372[a3].Unk0[a4]);
        a1.__ls((char)a2->Unk1372[a3].Unk40[a4]);
    }

    if(a2->Unk1372[a3].Unk0[a4] <= 0)
    {
        a1.__ls((char)a2->Unk1372[a3].Unk0[a4]);
        return;
    }

    if(a2->Unk1372[a3].Unk0[a4] == 1)
    {
        a1.__ls((char)a2->Unk1372[a3].Unk0[a4]);
        a1.__ls((char)a2->Unk1372[a3].Unk80[a4]);
    }

    if(a2->Unk1372[a3].Unk0[a4] == 2)
    {
        if(a2->Unk1372[a3].Unk120[a4])
        {
            a1.__ls((char)a2->Unk1372[a3].Unk0[a4]);
            a1.__ls((char)a2->Unk1372[a3].Unk120[a4]->col());
            a1.__ls((char)a2->Unk1372[a3].Unk120[a4]->row());
            return;
        }

        a1.__ls((char)-1);
        return;
    }

    a1.__ls((char)a2->Unk1372[a3].Unk0[a4]);
}

void QuickSlotListMsg(CNetMsg &a1, CPC *a2, char a3)
{
    a1.Init(25);

    a1.__ls((unsigned char)0);
    a1.__ls((char)a3);

    for(int i = 0; i <= 9; ++i)
    {
        if(!a2->Unk1372[a3].Unk0[i] == 0) // 160 * a3 + 4 * i + a2->Unk1372
        {
            a1.__ls((char)a2->Unk1372[a3].Unk0[i]);
            a1.__ls((char)a2->Unk1372[a3].Unk40[i]); // 160 * a3 + 4 * i + a2->Unk1412
            continue;
        }

        if(a2->Unk1372[a3].Unk0[i] <= 0)
        {
            a1.__ls((char)a2->Unk1372[a3].Unk0[i]);
            continue;
        }

        if(a2->Unk1372[a3].Unk0[i] == 1)
        {
            a1.__ls((char)a2->Unk1372[a3].Unk0[i]);
            a1.__ls((char)a2->Unk1372[a3].Unk80[i]); // 160 * a3 + 4 * i + a2->Unk1452
            continue;
        }

        if(a2->Unk1372[a3].Unk0[i] == 2)
        {
            if(a2->Unk1372[a3].Unk120[i])
            {
                a1.__ls((char)a2->Unk1372[a3].Unk0[i]);
                a1.__ls((char)a2->Unk1372[a3].Unk120[i]->row()); // 160 * a3 + 4 * i + a2->Unk1492
                a1.__ls((char)a2->Unk1372[a3].Unk120[i]->col());
                continue;
            }

            a1.__ls((char)-1);
            continue;
        }

        a1.__ls((char)a2->Unk1372[a3].Unk0[i]);
    }
}

void PartyInviteMsg(CNetMsg &a1, CPC *a2)
{
    a1.Init(24);

    a1.__ls((unsigned char)0);
    a1.__ls((int)a2->Unk1368->GetPartyType());
    a1.__ls((int)a2->Unk4);
    a1.__ls((char const *)a2->Unk8);
}

void PartyMsg(CNetMsg &a1, _tagMsgPartyType a2)
{
    a1.Init(24);

    a1.__ls((unsigned char)a2);
}

void PartyAddMsg(CNetMsg &a1, CPC *a2, char a3)
{
    a1.Init(24);

    a1.__ls((unsigned char)5);
    a1.__ls((char)a3);
    a1.__ls((int)a2->Unk4);
    a1.__ls((char const *)a2->Unk8);
    a1.__ls((char)a2->Unk477);
    a1.__ls((short)a2->Unk60);
    a1.__ls((short)a2->Unk76);
    a1.__ls((short)a2->Unk78);
    a1.__ls((short)a2->Unk80);
    a1.__ls((short)a2->Unk82);
    a1.__ls((float)a2->Unk120.Unk0);
    a1.__ls((float)a2->Unk120.Unk4);
    a1.__ls((char)a2->Unk120.Unk16);
}

void PartyDelMsg(CNetMsg &a1, bool a2, CPC *a3)
{
    a1.Init(24);

    if(a2)
        a1.__ls((unsigned char)7);
    else
        a1.__ls((unsigned char)6);

    a1.__ls((int)a3->Unk4);
}

void PartyInfoMsg(CNetMsg &a1, CPC *a2)
{
    a1.Init(24);

    a1.__ls((unsigned char)9);
    a1.__ls((int)a2->Unk4);
    a1.__ls((short)a2->Unk60);
    a1.__ls((short)a2->Unk76);
    a1.__ls((short)a2->Unk78);
    a1.__ls((short)a2->Unk80);
    a1.__ls((short)a2->Unk82);
    a1.__ls((float)a2->Unk120.Unk0);
    a1.__ls((float)a2->Unk120.Unk4);
    a1.__ls((char)a2->Unk120.Unk16);
}

void PartyErrorMsg(CNetMsg &a1, _tagMsgPartyErrorType a2)
{
    a1.Init(24);

    a1.__ls((unsigned char)10);
    a1.__ls((unsigned char)a2);
}

void PartyAssistInfoMsg(CNetMsg &a1, CPC *a2)
{
    a1.Init(24);

    a1.__ls((unsigned char)11);

    a2->Unk148.AppendAssistToNetMsg(a1);
}

void ConnConnectMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, int *a6)
{
    a1.Init(110);

    a1.__ls((int)a2);
    a1.__ls((int)a3);
    a1.__ls((int)a4);
    a1.__ls((char const *)gserver.Unk41012); // unk_81044B4
    a1.__ls((int)gserver.Unk41044); // dword_81044D4
    a1.__ls((int)a5);

    for(int i = 0; i < a5; ++i)
        a1.__ls((int)a6[i]);
}

void ConnLoginMsg(CNetMsg &a1, CDescriptor *a2)
{
    a1.Init(111);

    a1.__ls((unsigned char)0);
    a1.__ls((char const *)a2->Unk4);
    a1.__ls((char const *)a2->Unk35);
    a1.__ls((int)gserver.Unk41004);
    a1.__ls((int)gserver.Unk41008);
    a1.__ls((char)a2->Unk356);
    a1.__ls((char const *)a2->Unk196);
}

void ConnLogoutMsg(CNetMsg &a1, char const *a2)
{
    a1.Init(111);

    a1.__ls((unsigned char)2);
    a1.__ls((char const *)a2);
}

void ConnPlayingMsg(CNetMsg &a1, CDescriptor *a2, __tagMsgLoginType a3)
{
    a1.Init(111);

    a1.__ls((unsigned char)5);
    a1.__ls((char const *)a2->Unk4);
    a1.__ls((unsigned char)a3);
    a1.__ls((int)a2->Unk372->Unk408->Unk0);
}

void NPCRegenMsg(CNetMsg &a1, CNPC *a2, int a3)
{
    a1.Init(26);

    a1.__ls((int)a2->Unk4);
    a1.__ls((int)a2->Unk468);
    a1.__ls((float)a2->Unk120.Unk0);
    a1.__ls((float)a2->Unk120.Unk4);
    a1.__ls((float)a2->Unk120.Unk8);
    a1.__ls((float)a2->Unk120.Unk12);
    a1.__ls((char)a2->Unk120.Unk16);
    a1.__ls((int)a3);
}

void SkillListMsg(CNetMsg &a1, CPC *a2)
{
    CSkill *v10; // [sp+Ch] [bp-Ch]@3
    CSkillListNode *v12; // [sp+10h] [bp-8h]@1
    char v13; // [sp+17h] [bp-1h]@1

    v13 = a2->Unk480.count();
    v13 += a2->Unk492.count();
    v13 += a2->Unk504.count();

    a1.Init(27);

    a1.__ls((unsigned char)0);
    a1.__ls((char)v13);

    v12 = a2->Unk480.GetHeadPosition();
    while(v12)
    {
        v10 = a2->Unk480.GetNext((void *&)v12);
        if(v10)
        {
            a1.__ls((int)v10->Unk0->Unk0);
            a1.__ls((char)v10->Unk4);
        }
    }

    v12 = a2->Unk492.GetHeadPosition();
    while(v12)
    {
        v10 = a2->Unk492.GetNext((void *&)v12);
        if(v10)
        {
            a1.__ls((int)v10->Unk0->Unk0);
            a1.__ls((char)v10->Unk4);
        }
    }

    v12 = a2->Unk504.GetHeadPosition();
    while(v12)
    {
        v10 = a2->Unk504.GetNext((void *&)v12);
        if(v10)
        {
            a1.__ls((int)v10->Unk0->Unk0);
            a1.__ls((char)v10->Unk4);
        }
    }
}

void SkillLearnErrorMsg(CNetMsg &a1, _tagSkillLearnErrorType a2)
{
    a1.Init(27);

    a1.__ls((unsigned char)5);
    a1.__ls((unsigned char)a2);
}

void SkillLearnMsg(CNetMsg &a1, CSkill *a2)
{
    a1.Init(27);

    a1.__ls((unsigned char)1);
    a1.__ls((int)a2->Unk0->Unk0);
    a1.__ls((bool)(a2->Unk4 == 1));
    a1.__ls((char)a2->Unk4);
}

void SkillReadyMsg(CNetMsg &a1, CCharacter *a2, CSkill *a3, CCharacter *a4)
{
    if(a3->Unk0->Unk28 >= 0 && (a3->Unk0->Unk28 <= 2 || a3->Unk0->Unk28 == 7))
        a4 = a2;

    a1.Init(27);

    a1.__ls((unsigned char)2);
    a1.__ls((char)a2->Unk0);
    a1.__ls((int)a2->Unk4);
    a1.__ls((int)a3->Unk0->Unk0);

    if(a4)
    {
        a1.__ls((char)a4->Unk0);
        a1.__ls((int)a4->Unk4);
    }
    else
    {
        a1.__ls((char)-1);
        a1.__ls((int)-1);
    }
}

void SkillCancelMsg(CNetMsg &a1, CCharacter *a2)
{
    a1.Init(27);

    a1.__ls((unsigned char)4);
    a1.__ls((char)a2->Unk0);
    a1.__ls((int)a2->Unk4);
}

void SkillFireMsg(CNetMsg &a1, CCharacter *a2, CSkill *a3, CCharacter *a4, char a5, char *a6, int *a7)
{
    if(a3->Unk0->Unk28 >= 0 && (a3->Unk0->Unk28 <= 2 || a3->Unk0->Unk28 == 7))
        a4 = a2;

    a1.Init(27);

    a1.__ls((unsigned char)3);
    a1.__ls((char)a2->Unk0);
    a1.__ls((int)a2->Unk4);
    a1.__ls((int)a3->Unk0->Unk0);

    if(a4)
    {
        a1.__ls((char)a4->Unk0);
        a1.__ls((int)a4->Unk4);
    }
    else
    {
        a1.__ls((char)-1);
        a1.__ls((int)-1);
    }

    a1.__ls((char)a5);

    for(int i = 0; i < a5; ++i)
    {
        a1.__ls((char)a6[i]);
        a1.__ls((int)a7[i]);
    }
}

void MsgrPlayerCountReq(CNetMsg &a1, int a2, int a3, int a4)
{
    a1.Init(101);

    a1.__ls((unsigned char)0);
    a1.__ls((int)a2);
    a1.__ls((int)a3);
    a1.__ls((int)-1);
    a1.__ls((unsigned char)7);
    a1.__ls((int)a4);
}

void MsgrPlayerCountRep(CNetMsg &a1, int a2, int a3, int a4, int a5, int a6, int a7, int *a8, int *a9, int *a10, int *a11)
{
    a1.Init(102);

    a1.__ls((int)a2);
    a1.__ls((int)a3);
    a1.__ls((int)a4);
    a1.__ls((int)a5);
    a1.__ls((unsigned char)8);
    a1.__ls((int)a6);
    a1.__ls((int)a7);

    for(int i = 0; i < gserver.Unk452192; ++i)
    {
        if(a8[i])
        {
            a1.__ls((int)gserver.Unk452196[i].Unk0);
            a1.__ls((int)a8[i]);
            a1.__ls((int)a9[i]);
            a1.__ls((int)a10[i]);
            a1.__ls((int)a11[i]);
        }
    }
}

void AssistAddMsg(CNetMsg &a1, CCharacter *a2, int a3, int a4, char a5, int a6)
{
    a1.Init(28);

    a1.__ls((unsigned char)0);
    a1.__ls((bool)(a2->Unk0 == 1));
    a1.__ls((int)a2->Unk4);
    a1.__ls((int)a3);
    a1.__ls((int)a4);
    a1.__ls((char)a5);
    a1.__ls((int)a6);
}

void AssistDelMsg(CNetMsg &a1, CCharacter *a2, int a3, int a4)
{
    a1.Init(28);

    a1.__ls((unsigned char)1);
    a1.__ls((bool)(a2->Unk0 == 1));
    a1.__ls((int)a2->Unk4);
    a1.__ls((int)a3);
    a1.__ls((int)a4);
}

void AssistListMsg(CNetMsg &a1, CPC *a2)
{
    a1.Init(28);

    a1.__ls((unsigned char)2);
    a2->Unk148.AppendAssistToNetMsg(a1);
}

void CharStatusMsg(CNetMsg &a1, CCharacter *a2, int a3)
{
    a1.Init(29);

    a1.__ls((bool)(a2->Unk0 == 1));
    a1.__ls((int)a2->Unk4);
    a1.__ls((short)a2->Unk76);
    a1.__ls((short)a2->Unk78);
    a1.__ls((short)a2->Unk80);
    a1.__ls((short)a2->Unk82);

    if(a2->Unk0)
    {
        a1.__ls((int)0);
        a1.__ls((char)0);
    }
    else
    {
        a1.__ls((int)((CPC *)a2)->Unk1852);
        a1.__ls((char)(((CPC *)a2)->GetPKName()));
    }

    a1.__ls((int)a2->Unk148.Unk240); // 148 + 240 = 388
    a1.__ls((int)a3);
}

void RebirthMsg(CNetMsg &a1, CCharacter *a2)
{
    a1.Init(30);

    a1.__ls((bool)(a2->Unk0 == 1));
    a1.__ls((int)a2->Unk4);
    a1.__ls((short)a2->Unk76);
    a1.__ls((short)a2->Unk78);
    a1.__ls((short)a2->Unk80);
    a1.__ls((short)a2->Unk82);
}

void EffectEtcMsg(CNetMsg &a1, CCharacter *a2, _tagMsgEffectEtcType a3)
{
    a1.Init(31);

    a1.__ls((unsigned char)1);
    a1.__ls((bool)(a2->Unk0 == 1));
    a1.__ls((int)a2->Unk4);
    a1.__ls((unsigned char)a3);
}

void EffectSkillMsg(CNetMsg &a1, CCharacter *a2, CSkillProto const *a3)
{
    a1.Init(31);

    a1.__ls((unsigned char)0);
    a1.__ls((int)a3->Unk0);
    a1.__ls((bool)(a2->Unk0 == 1));
    a1.__ls((int)a2->Unk4);
}

//EffectProduceMsg__FR7CNetMsgP10CCharacterT115_tagProduceKind
void EffectProduceMsg(CNetMsg &a1, CCharacter *a2, CCharacter *a3, _tagProduceKind a4)
{
    a1.Init(31);

    a1.__ls((unsigned char)2);
    a1.__ls((unsigned char)a4);
    a1.__ls((char)(a2->Unk0 == 1));
    a1.__ls((int)a2->Unk4);
    a1.__ls((char)(a3->Unk0 == 1));
    a1.__ls((int)a3->Unk4);
    a1.__ls((short)a3->Unk76);
}

void EffectItemMsg(CNetMsg &a1, CCharacter *a2, CItem *a3)
{
    a1.Init(31);

    a1.__ls((unsigned char)3);
    a1.__ls((bool)(a2->Unk0 == 1));
    a1.__ls((int)a2->Unk4);
    a1.__ls((int)a3->Unk20->Unk0);
}

void ConnRebootReqMsg(CNetMsg &a1)
{
    a1.Init(111);

    a1.__ls((unsigned char)8);
}

void ConnPreopenGiftMsg(CNetMsg &a1, int a2, int a3, bool a4)
{
    a1.Init(111);

    a1.__ls((unsigned char)9);
    a1.__ls((int)a2);
    a1.__ls((int)a3);

    if(a4)
        a1.__ls((unsigned char)1);
    else
        a1.__ls((unsigned char)0);
}

void ConnLevelupPointMsg(CNetMsg &a1, int a2, int a3)
{
    a1.Init(111);

    a1.__ls((unsigned char)10);
    a1.__ls((int)a2);
    a1.__ls((int)a3);
}

void ConnStashState(CNetMsg &a1, int a2, int a3)
{
    a1.Init(111);

    a1.__ls((unsigned char)11);
    a1.__ls((int)a2);
    a1.__ls((int)a3);
}

void ConnStashCheckPassword(CNetMsg &a1, int a2, int a3, char const *a4)
{
    a1.Init(111);

    a1.__ls((unsigned char)12);
    a1.__ls((int)a2);
    a1.__ls((int)a3);
    a1.__ls((char const *)a4);
}

void ConnStashChangePassword(CNetMsg &a1, int a2, int a3, char const *a4, char const *a5)
{
    a1.Init(111);

    a1.__ls((unsigned char)13);
    a1.__ls((int)a2);
    a1.__ls((int)a3);
    a1.__ls((char const *)a4);
    a1.__ls((char const *)a5);
}

void ConnStashSeal(CNetMsg &a1, int a2, int a3)
{
    a1.Init(111);

    a1.__ls((unsigned char)14);
    a1.__ls((int)a2);
    a1.__ls((int)a3);
}

void ExpSPMsg(CNetMsg &a1, long long a2, int a3)
{
    a1.Init(32);

    a1.__ls((long long)a2);
    a1.__ls((int)a3);
}

void QuestPCListMsg(CNetMsg &a1, CPC *a2)
{
    a1.Init(35);

    a1.__ls((unsigned char)0);
    a1.__ls((int)a2->Unk1900.Unk60);

    for(int i = 0; i <= 9; ++i)
    {
        if(a2->Unk1900.Unk0[i])
        {
            if(a2->Unk1900.Unk40[i])
            {
                a1.__ls((int)a2->Unk1900.Unk0[i]->Unk0->Unk0);

                for(int j = 0; j <= 2; ++j)
                    a1.__ls((int)a2->Unk1900.Unk0[i]->Unk4[j]); // TO CHENGE THE TYPE
            }
        }
    }
}

void QuestNPCListMsg(CNetMsg &a1, int a2, int *a3, int *a4)
{
    a1.Init(35);

    a1.__ls((unsigned char)2);
    a1.__ls((int)a2);

    for(int i = 0; i < a2; ++i)
    {
        a1.__ls((int)a4[i]);
        a1.__ls((char)a3[i]);
    }
}

void QuestCreateListMsg(CNetMsg &a1, int a2, int *a3)
{
    a1.Init(35);

    a1.__ls((unsigned char)3);
    a1.__ls((int)a2);

    for(int i = 0; i < a2; ++i)
        a1.__ls((int)a3[i]);
}

void QuestStartMsg(CNetMsg &a1, CQuest *a2)
{
    a1.Init(35);

    a1.__ls((unsigned char)4);
    a1.__ls((int)a2->Unk0->Unk0);
}

void QuestCompleteMsg(CNetMsg &a1, CQuest *a2)
{
    a1.Init(35);

    a1.__ls((unsigned char)5);
    a1.__ls((int)a2->Unk0->Unk0);
}

void QuestStatusMsg(CNetMsg &a1, CQuest *a2)
{
    a1.Init(35);

    a1.__ls((unsigned char)6);
    a1.__ls((int)a2->Unk0->Unk0);

    for(int i = 0; i <= 2; ++i)
        a1.__ls((int)a2->Unk4[i]); // CHECK LONG TYPE
}

void QuestPrizeMsg(CNetMsg &a1, CQuest *a2)
{
    a1.Init(35);

    a1.__ls((unsigned char)7);
    a1.__ls((int)a2->Unk0->Unk0);
}

void QuestGiveUpMsg(CNetMsg &a1, CQuest *a2)
{
    a1.Init(35);

    a1.__ls((unsigned char)8);
    a1.__ls((int)a2->Unk0->Unk0);
}

void QuestFailMsg(CNetMsg &a1, CQuest *a2)
{
    a1.Init(35);

    a1.__ls((unsigned char)9);
    a1.__ls((int)a2->Unk0->Unk0);
}

void QuestErrorMsg(CNetMsg &a1, _tagMsgQuestErrorType a2)
{
    a1.Init(35);

    a1.__ls((unsigned char)10);
    a1.__ls((unsigned char)a2);
}

void StatPointRemainMsg(CNetMsg &a1, CPC *a2)
{
    a1.Init(36);

    a1.__ls((unsigned char)0);
    a1.__ls((short)a2->Unk740);
}

void StatPointUseMsg(CNetMsg &a1, CPC *a2, _tagStatPointUseType a3, short a4)
{
    a1.Init(36);

    a1.__ls((unsigned char)1);
    a1.__ls((unsigned char)a3);
    a1.__ls((short)a4);
    a1.__ls((short)a2->Unk740);
}

void StatPointErrorMsg(CNetMsg &a1, char a2)
{
    a1.Init(36);

    a1.__ls((unsigned char)2);
    a1.__ls((char)a2);
}

void ActionMsg(CNetMsg &a1, CPC *a2, char a3, char a4)
{
    a1.Init(33);

    a1.__ls((int)a2->Unk4);
    a1.__ls((char)a3);
    a1.__ls((char)a4);
    a1.__ls((char)a2->GetPlayerState()); // TO CHECK RETURNED VALUE
}

void WarpStartMsg(CNetMsg &a1, CPC *a2)
{
    a1.Init(37);

    a1.__ls((unsigned char)0);
    a1.__ls((int)a2->Unk4);
}

void WarpCancelMsg(CNetMsg &a1, CPC *a2)
{
    a1.Init(37);

    a1.__ls((unsigned char)1);
    a1.__ls((int)a2->Unk4);
}

void WarpEndMsg(CNetMsg &a1, CPC *a2)
{
    a1.Init(37);

    a1.__ls((unsigned char)2);
    a1.__ls((int)a2->Unk4);
}

void SSkillListMsg(CNetMsg &a1, CPC *a2)
{
    a1.Init(40);

    a1.__ls((unsigned char)0);
    a1.__ls((char)a2->Unk716.Unk4);

    for(CSSkillNode *i = a2->Unk716.Unk0; i; i = i->Unk4)
    {
        a1.__ls((int)i->Unk0->Unk0->Unk0);
        a1.__ls((char)i->Unk0->Unk4);
    }
}

void SSkillLearnErrorMsg(CNetMsg &a1, _tagSSkillLearnErrorType a2)
{
    a1.Init(40);

    a1.__ls((unsigned char)3);
    a1.__ls((unsigned char)a2);
}

void SSkillLearnMsg(CNetMsg &a1, CSSkill *a2)
{
    a1.Init(40);

    a1.__ls((unsigned char)1);
    a1.__ls((int)a2->Unk0->Unk0);
    a1.__ls((bool)(a2->Unk4 == 1));
    a1.__ls((char)a2->Unk4);
}

void SSkillRemoveMsg(CNetMsg &a1, CSSkill *a2)
{
    a1.Init(40);

    a1.__ls((unsigned char)2);
    a1.__ls((int)a2->Unk0->Unk0);
}

void PKItemSealMsg(CNetMsg &a1, CItem *a2)
{
    a1.Init(41);

    a1.__ls((unsigned char)1);
    a1.__ls((char)a2->tab());
    a1.__ls((char)a2->row());
    a1.__ls((char)a2->col());
    a1.__ls((int)a2->Unk24);
    a1.__ls((int)a2->Unk40);
}

void PKRecoverItemSealMsg(CNetMsg &a1, CItem *a2)
{
    a1.Init(41);

    a1.__ls((unsigned char)3);
    a1.__ls((char)a2->tab());
    a1.__ls((char)a2->row());
    a1.__ls((char)a2->col());
    a1.__ls((int)a2->Unk24);
    a1.__ls((int)a2->Unk40);
}

void PKErrorMsg(CNetMsg &a1, char a2)
{
    a1.Init(41);

    a1.__ls((unsigned char)4);
    a1.__ls((char)a2);
}

void EventErrorMsg(CNetMsg &a1, _tagEventErrorType a2)
{
    a1.Init(43);

    a1.__ls((unsigned char)0);
    a1.__ls((unsigned char)a2);
}

void EventPreopenGiftMsg(CNetMsg &a1, int a2)
{
    a1.Init(43);

    a1.__ls((unsigned char)1);
    a1.__ls((int)a2);
}

void EventLattoMsg(CNetMsg &a1, _tagEventLattoType a2, int a3, int a4)
{
    a1.Init(43);

    a1.__ls((unsigned char)2);
    a1.__ls((unsigned char)a2);

    if(a2 == 3)
    {
        a1.__ls((int)a3);
        a1.__ls((int)a4);
    }

    if(a2 == 6)
        a1.__ls((int)a3);
}

void PersonalShopErrorMsg(CNetMsg &a1, _tagPersonalShopErrorType a2)
{
    a1.Init(44);

    a1.__ls((unsigned char)0);
    a1.__ls((unsigned char)a2);
}

void PersonalShopSellStartMsg(CNetMsg &a1, CPC *a2)
{
    a1.Init(44);

    a1.__ls((unsigned char)2);
    a1.__ls((int)a2->Unk4);
    a1.__ls((char)a2->Unk1328->GetType());
    a1.__ls((char const *)a2->Unk1328->GetName());
}

/*void PersonalShopSellListMsg(CNetMsg &a1, CPC *a2)
{
    char v2; // ST24_1@3
    uint32_t v3; // ST18_4@3
    int v4; // eax@3
    int v5; // eax@3
    char v6; // ST44_1@12
    uint32_t v7; // ST38_4@12
    uint32_t v8; // ST2C_4@12
    uint32_t v9; // ST20_4@12
    int v10; // eax@12
    int v11; // eax@12
    int v12; // eax@12
    int v13; // eax@12
    char v14; // ST44_1@14
    int v15; // eax@14
    int v16; // eax@15
    __int64 v17; // qax@17
    int v18; // eax@17
    char v19; // ST34_1@25
    uint32_t v20; // ST28_4@25
    uint32_t v21; // ST1C_4@25
    uint32_t v22; // ST10_4@25
    int v23; // eax@25
    int v24; // eax@25
    int v25; // eax@25
    int v26; // eax@25
    char v27; // ST44_1@27
    int v28; // eax@27
    char v29; // [sp+Fh] [bp-39h]@17
    int j; // [sp+10h] [bp-38h]@12
    signed int k; // [sp+10h] [bp-38h]@17
    __int64 v32; // [sp+14h] [bp-34h]@12
    __int64 v33; // [sp+14h] [bp-34h]@25
    __int64 src; // [sp+1Ch] [bp-2Ch]@12
    int v35; // [sp+24h] [bp-24h]@10
    int v36; // [sp+24h] [bp-24h]@17
    int v37; // [sp+28h] [bp-20h]@8
    int v38; // [sp+2Ch] [bp-1Ch]@8
    int v39; // [sp+30h] [bp-18h]@8
    int v40; // [sp+34h] [bp-14h]@4
    int i; // [sp+38h] [bp-10h]@4
    char v42; // [sp+3Fh] [bp-9h]@3
    int v43; // [sp+40h] [bp-8h]@1
    int v44; // [sp+44h] [bp-4h]@1

    v44 = *(_DWORD *)(a2->Unk1328);
    v43 = a2->Unk792;
    if(v44)
    {
        a1.Init(44);
        v2 = CPersonalShop::GetType(v44);
        v3 = *(_DWORD *)(a2->Unk4);
        v4 = CNetMsg::__ls(a1, 3);
        v5 = CNetMsg::__ls(v4, v3);
        CNetMsg::__ls(v5, v2);
        v42 = CPersonalShop::GetNormalCount(v44);
        CNetMsg::__ls(a1, v42);
        if(v42)
        {
            v40 = -1;
            for(i = 0; i < v42; ++i)
            {
                v40 = CPersonalShop::GetNextNormalItem(v44, v40);
                if(v40 == -1)
                {
                    CNetMsg::Init(a1);
                    return;
                }
                v39 = CPersonalShop::GetNormalItemIndex(v44, v40);
                if(!CInventory::FindItem(v43, (int)&v38, (int)&v37, v39))
                {
                    CNetMsg::Init(a1);
                    return;
                }
                v35 = CInventory::GetItem(v43, v38, v37);
                if(!v35)
                {
                    CNetMsg::Init(a1);
                    return;
                }
                src = CPersonalShop::GetNormalItemCount(v44, v40);
                v32 = CPersonalShop::GetNormalItemPrice(v44, v40);
                v6 = *(_BYTE *)(v35 + 168);
                v7 = *(_DWORD *)(v35 + 40);
                v8 = *(_DWORD *)(v35 + 36);
                v9 = *(_DWORD *)(v35 + 28);
                v10 = CNetMsg::__ls(a1, v39);
                v11 = CNetMsg::__ls(v10, v9);
                v12 = CNetMsg::__ls(v11, v8);
                v13 = CNetMsg::__ls(v12, v7);
                CNetMsg::__ls(v13, v6);
                for(j = 0; j < *(_DWORD *)(v35 + 168); ++j)
                {
                    v14 = *(_BYTE *)(20 * j + v35 + 76);
                    v15 = CNetMsg::__ls(a1, *(_BYTE *)(20 * j + v35 + 72));
                    CNetMsg::__ls(v15, v14);
                }
                v16 = CNetMsg::__ls(a1, src);
                CNetMsg::__ls(v16, v32);
            }
        }
        if(CPersonalShop::GetType(v44) & 8)
        {
            v29 = CPersonalShop::GetPackageCount(v44);
            v17 = CPersonalShop::GetPackagePrice(v44);
            v18 = CNetMsg::__ls(a1, v17);
            CNetMsg::__ls(v18, v29);
            v36 = -1;
            for(k = 0; k < v29; ++k)
            {
                v36 = CPersonalShop::GetNextPackageItem(v44, v36);
                if(v36 == -1)
                {
                    CNetMsg::Init(a1);
                    return;
                }
                v37 = CPersonalShop::GetPackageItemIndex(v44, v36);
                if(!CInventory::FindItem(v43, (int)&v38, (int)&v39, v37))
                {
                    CNetMsg::Init(a1);
                    return;
                }
                v40 = CInventory::GetItem(v43, v38, v39);
                if(!v40)
                {
                    CNetMsg::Init(a1);
                    return;
                }
                v33 = CPersonalShop::GetPackageItemCount(v44, v36);
                v19 = *(_BYTE *)(v40 + 168);
                v20 = *(_DWORD *)(v40 + 40);
                v21 = *(_DWORD *)(v40 + 36);
                v22 = *(_DWORD *)(v40 + 28);
                v23 = CNetMsg::__ls(a1, v37);
                v24 = CNetMsg::__ls(v23, v22);
                v25 = CNetMsg::__ls(v24, v21);
                v26 = CNetMsg::__ls(v25, v20);
                CNetMsg::__ls(v26, v19);
                for(i = 0; i < *(_DWORD *)(v40 + 168); ++i)
                {
                    v27 = *(_BYTE *)(20 * i + v40 + 76);
                    v28 = CNetMsg::__ls(a1, *(_BYTE *)(20 * i + v40 + 72));
                    CNetMsg::__ls(v28, v27);
                }
                CNetMsg::__ls(a1, v33);
            }
        }
    }
    else
    {
        CNetMsg::Init(a1);
    }
}*/

void PersonalShopChangeMsg(CNetMsg &a1, CPC *a2)
{
    a1.Init(44);

    a1.__ls((unsigned char)1);
    a1.__ls((int)a2->Unk4);

    if(a2->Unk1328)
        a1.__ls((char)a2->Unk1328->GetType());
    else
        a1.__ls((char)0);
}

void PersonalShopBuyMsg(CNetMsg &a1, CNetMsg &a2, CPC *a3)
{
    a1.Init(a2);
    a1.MoveFirst();

    a1.__ls((unsigned char)4);
    a1.__ls((int)a3->Unk4);
}

void RightAttackMsg(CNetMsg &a1, CPC *a2, _tagRightAttackType a3)
{
    a1.Init(45);

    a1.__ls((unsigned char)a3);
    a1.__ls((bool)(a2->Unk0 == 1));
    a1.__ls((int)a2->Unk4);
}

void StashIsSetPassword(CNetMsg &a1, bool a2)
{
    a1.Init(46);

    a1.__ls((unsigned char)1);
    if(a2)
        a1.__ls((unsigned char)1);
    else
        a1.__ls((unsigned char)0);
}

void StashErrorMsg(CNetMsg &a1, _tagStashErrorType a2)
{
    a1.Init(46);

    a1.__ls((unsigned char)0);
    a1.__ls((unsigned char)a2);
}

void StashListRepMsg(CNetMsg &a1, CItem const *a2, bool a3, bool a4, bool a5)
{
    unsigned char v21; // [sp+17h] [bp-1h]@1

    v21 = 0;

    if(a3)
        v21 = 1;

    if(a4)
        v21 |= 2;

    if(a5)
        v21 |= 4;

    a1.Init(46);

    a1.__ls((unsigned char)3);
    a1.__ls((unsigned char)v21);

    if(!a5)
    {
        a1.__ls((int)a2->Unk24);
        a1.__ls((int)a2->Unk28);
        a1.__ls((int)a2->Unk36);
        a1.__ls((int)a2->Unk40);
        a1.__ls((int)a2->Unk64);
        a1.__ls((char)a2->Unk168);

        for(int i = 0; i < a2->Unk168; ++i)
        {
            a1.__ls((char)a2->Unk68[i].Unk4); // 20 * i + a2 + 72 = 20 * i + a2 + 68 + 4
            a1.__ls((char)a2->Unk68[i].Unk8); // 20 * i + a2 + 76 = 20 * i + a2 + 68 + 8
        }

        a1.__ls((long long)((CItem *)a2)->Count());
    }
}

void StashKeepRepMsg(CNetMsg &a1, int a2, int *a3, long long *a4)
{
    a1.Init(46);

    a1.__ls((unsigned char)5);
    a1.__ls((int)a2);

    for(int i = 0; i < a2; ++i)
    {
        a1.__ls((int)a3[i]);
        a1.__ls((long long)a4[i]);
    }
}

void StashTakeRepMsg(CNetMsg &a1, int a2, int *a3, long long *a4)
{
    a1.Init(46);

    a1.__ls((unsigned char)7);
    a1.__ls((int)a2);

    for(int i = 0; i < a2; ++i)
    {
        a1.__ls((int)a3[i]);
        a1.__ls((long long)a4[i]);
    }
}

void StashChangePasswordRepMsg(CNetMsg &a1, bool a2)
{
    a1.Init(46);

    a1.__ls((unsigned char)9);
    if(a2)
        a1.__ls((unsigned char)1);
    else
        a1.__ls((unsigned char)0);
}

void StashSealMsg(CNetMsg &a1)
{
    a1.Init(46);

    a1.__ls((unsigned char)10);
}

void GuildErrorMsg(CNetMsg &a1, _tagGuildErrorType a2)
{
    a1.Init(42);

    a1.__ls((unsigned char)0);
    a1.__ls((unsigned char)a2);
}

void GuildInfoMsg(CNetMsg &a1, CPC *a2)
{
    a1.Init(42);

    a1.__ls((unsigned char)2);
    if(a2->Unk2368)
    {
        a1.__ls((int)a2->Unk2368->guild()->index());
        a1.__ls((char const *)a2->Unk2368->guild()->name());
        a1.__ls((int)a2->Unk2368->guild()->level());
        a1.__ls((int)a2->Unk2368->pos());
        return;
    }
    a1.__ls((int)-1);
}

void GuildListMsg(CNetMsg &a1, CPC *a2, bool a3)
{
    CGuildMember *v13; // [sp+Ch] [bp-Ch]@9
    CGuild *v15; // [sp+14h] [bp-4h]@3

    if(!a2->Unk2368)
    {
        a1.Init();
        return;
    }

    v15 = a2->Unk2368->guild();

    a1.Init(42);

    a1.__ls((unsigned char)3);
    if(a3)
    {
        if(!v15->parentguild())
        {
            a1.Init();
            return;
        }

        v15 = v15->parentguild();
    }

    a1.__ls((int)v15->index());
    a1.__ls((int)v15->membercount());

    for(int i = 0; i <= 29; ++i)
    {
        v13 = v15->member(i);
        if(v13)
        {
            a1.__ls((int)v13->charindex());
            a1.__ls((char const *)v13->name());
            a1.__ls((int)v13->pos());
            a1.__ls((int)v13->online());
        }
    }
}

void HelperShutdownMsg(CNetMsg &a1)
{
    a1.Init(123);

    a1.__ls((unsigned char)0);
}

/*void HelperRepWhisperNotFoundMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, int a6, char const *a7)
{
    int v7; // eax@1
    int v8; // eax@1
    int v9; // eax@1
    int v10; // eax@1
    int v11; // eax@1
    int v12; // eax@1

    a1.Init(122);
    v7 = CNetMsg::__ls(a1, src);
    v8 = CNetMsg::__ls(v7, a3);
    v9 = CNetMsg::__ls(v8, a4);
    v10 = CNetMsg::__ls(v9, a5);
    v11 = CNetMsg::__ls(v10, 3);
    v12 = CNetMsg::__ls(v11, a6);
    return CNetMsg::__ls(v12, a7);
}

void HelperRepWhisperRepMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, int a6, char const *a7, char const *a8, char const *a9)
{
    int v9; // eax@1
    int v10; // eax@1
    int v11; // eax@1
    int v12; // eax@1
    int v13; // eax@1
    int v14; // eax@1
    int v15; // eax@1
    int v16; // eax@1

    a1.Init(122);
    v9 = CNetMsg::__ls(a1, src);
    v10 = CNetMsg::__ls(v9, a3);
    v11 = CNetMsg::__ls(v10, a4);
    v12 = CNetMsg::__ls(v11, a5);
    v13 = CNetMsg::__ls(v12, 1);
    v14 = CNetMsg::__ls(v13, a6);
    v15 = CNetMsg::__ls(v14, a7);
    v16 = CNetMsg::__ls(v15, a8);
    return CNetMsg::__ls(v16, a9);
}

void HelperGoZoneRepMsg(CNetMsg &a1, int a2, int a3, char a4, int a5, int a6, int a7)
{
    uint32_t v7; // ST1C_4@1
    uint32_t v8; // ST10_4@1
    int v9; // eax@1
    int v10; // eax@1
    int v11; // eax@1
    int v12; // eax@1
    int v13; // eax@1
    int v14; // eax@1
    int v15; // eax@1
    int v16; // eax@1

    a1.Init(122);
    v7 = gserver.Unk41008;
    v8 = gserver.Unk41004;
    v9 = CNetMsg::__ls(a1, src);
    v10 = CNetMsg::__ls(v9, v8);
    v11 = CNetMsg::__ls(v10, v7);
    v12 = CNetMsg::__ls(v11, a3);
    v13 = CNetMsg::__ls(v12, 6);
    v14 = CNetMsg::__ls(v13, a4);
    v15 = CNetMsg::__ls(v14, a5);
    v16 = CNetMsg::__ls(v15, a6);
    return CNetMsg::__ls(v16, a7);
}

void HelperGuildCreateReqMsg(CNetMsg &a1, CPC *a2, char const *a3)
{
    uint32_t v3; // ST10_4@1
    int v4; // eax@1
    int v5; // eax@1
    int v6; // eax@1

    a1.Init(123);
    v3 = *(_DWORD *)(a2->Unk4);
    v4 = CNetMsg::__ls(a1, 1u);
    v5 = CNetMsg::__ls(v4, v3);
    v6 = CNetMsg::__ls(v5, (char *)(a2->Unk8));
    return CNetMsg::__ls(v6, a3);
}

void GuildOnlineMsg(CNetMsg &a1, CGuildMember *a2)
{
    char v2; // ST3C_1@1
    int v3; // ST30_4@1
    int v4; // ST24_4@1
    int v5; // eax@1
    int v6; // ST18_4@1
    int v7; // eax@1
    int v8; // eax@1
    int v9; // eax@1
    int v10; // eax@1

    a1.Init(42);
    v2 = CGuildMember::online(a2);
    v3 = CGuildMember::name(a2);
    v4 = CGuildMember::charindex(a2);
    v5 = CGuildMember::guild(a2);
    v6 = CGuild::index(v5);
    v7 = CNetMsg::__ls(a1, 4);
    v8 = CNetMsg::__ls(v7, v6);
    v9 = CNetMsg::__ls(v8, v4);
    v10 = CNetMsg::__ls(v9, (char *)v3);
    return CNetMsg::__ls(v10, v2);
}*/

void HelperConnectMsg(CNetMsg &a1, int a2, int a3, int a4, int a5, int *a6)
{
    a1.Init(120);

    a1.__ls(a2);
    a1.__ls(a3);
    a1.__ls(a4);
    a1.__ls(a5);

    for(int i = 0; i < a5; ++i)
        a1.__ls(a6[i]);
}

void HelperGuildOnline(CNetMsg &a1, CGuildMember *a2)
{
    a1.Init(123);

    a1.__ls(6);
    a1.__ls(a2->guild()->index());
    a1.__ls(a2->charindex());
    a1.__ls(a2->online());
}

void HelperGuildLoadReq(CNetMsg &a1, char const *a2, int a3)
{
    a1.Init(123);

    a1.__ls(7);
    a1.__ls(a2);
    a1.__ls(a3);
}

/*void HelperGuildLevelUpReqMsg(CNetMsg &,int,int)
{
    int v3; // eax@1
    int v4; // eax@1

    a1.Init(123);
    v3 = CNetMsg::__ls(a1, 9u);
    v4 = CNetMsg::__ls(v3, src);
    return CNetMsg::__ls(v4, a3);
}

void GuildLevelInfoMsg(CNetMsg &a1, int a2, int a3)
{
    int v3; // eax@1
    int v4; // eax@1

    a1.Init(42);
    v3 = CNetMsg::__ls(a1, 6);
    v4 = CNetMsg::__ls(v3, src);
    return CNetMsg::__ls(v4, a3);
}

void HelperGuildBreakUpReqMsg(CNetMsg &a1, CPC *a2)
{
    int v2; // eax@1
    int v3; // ST1C_4@1
    uint32_t v4; // ST10_4@1
    int v5; // eax@1
    int v6; // eax@1

    a1.Init(123);
    v2 = CGuildMember::guild(*(_DWORD *)(a2->Unk2368));
    v3 = CGuild::index(v2);
    v4 = *(_DWORD *)(a2->Unk4);
    v5 = CNetMsg::__ls(a1, 0xCu);
    v6 = CNetMsg::__ls(v5, v4);
    return CNetMsg::__ls(v6, v3);
}

void GuildBreakUpNotifyMsg(CNetMsg &a1, int a2, char const *a3)
{
    int v3; // eax@1
    int v4; // eax@1

    a1.Init(42);
    v3 = CNetMsg::__ls(a1, 8);
    v4 = CNetMsg::__ls(v3, src);
    return CNetMsg::__ls(v4, a3);
}*/

void GuildRegistCancelMsg(CNetMsg &a1, bool a2)
{
    a1.Init(42);

    a1.__ls(11);
    a1.__ls((a2 ? 1 : 0));
}

void HelperGuildMemberAddReqMsg(CNetMsg &a1, int a2, int a3, int a4, char const *a5)
{
    a1.Init(123);
	
    a1.__ls(0xF);
    a1.__ls(a2);
    a1.__ls(a3);
    a1.__ls(a4);
    a1.__ls(a5);
}

void GuildMemberAddMsg(CNetMsg &a1, int a2, int a3, char const *a4)
{
    a1.Init(42);

    a1.__ls(17);
    a1.__ls(a2);
    a1.__ls(a3);
    a1.__ls(a4);
}

void HelperGuildOutReqMsg(CNetMsg &a1, int a2, int a3)
{
    a1.Init(123);

    a1.__ls(0x12);
    a1.__ls(a2);
    a1.__ls(a3);
}

void GuildMemberOutMsg(CNetMsg &a1, int a2, int a3, char const *a4)
{
    a1.Init(42);

    a1.__ls(18);
    a1.__ls(a2);
    a1.__ls(a3);
    a1.__ls(a4);
}

void HelperGuildKickReqMsg(CNetMsg &a1, int a2, int a3, int a4)
{
    a1.Init(123);

    a1.__ls(0x15);
    a1.__ls(a2);
    a1.__ls(a3);
    a1.__ls(a4);
}

/*void GuildMemberKickMsg(CNetMsg &a1, int a2, int a3, int a4, char const *a5)
{
    int v5; // eax@1
    int v6; // eax@1
    int v7; // eax@1
    int v8; // eax@1

    a1.Init(42);
    v5 = CNetMsg::__ls(a1, 19);
    v6 = CNetMsg::__ls(v5, src);
    v7 = CNetMsg::__ls(v6, a3);
    v8 = CNetMsg::__ls(v7, a4);
    return CNetMsg::__ls(v8, a5);
}

void GuildInfoChangeMsg(CNetMsg &a1, int a2, int a3, char const *a4, _tagGuildPositionType a5)
{
    int v5; // eax@1
    int v6; // eax@1
    int v7; // eax@1
    int v8; // eax@1

    a1.Init(42);
    v5 = CNetMsg::__ls(a1, 20);
    v6 = CNetMsg::__ls(v5, src);
    v7 = CNetMsg::__ls(v6, a3);
    v8 = CNetMsg::__ls(v7, a4);
    return CNetMsg::__ls(v8, a5);
}

void HelperGuildChangeBossReqMsg(CNetMsg &a1, int a2, int a3, int a4)
{
    int v4; // eax@1
    int v5; // eax@1
    int v6; // eax@1

    a1.Init(123);
    v4 = CNetMsg::__ls(a1, 0x18u);
    v5 = CNetMsg::__ls(v4, src);
    v6 = CNetMsg::__ls(v5, a3);
    return CNetMsg::__ls(v6, a4);
}

void GuildChangeBossMsg(CNetMsg &a1, int a2, int a3, int a4)
{
    int v4; // eax@1
    int v5; // eax@1
    int v6; // eax@1

    a1.Init(42);
    v4 = CNetMsg::__ls(a1, 13);
    v5 = CNetMsg::__ls(v4, src);
    v6 = CNetMsg::__ls(v5, a3);
    return CNetMsg::__ls(v6, a4);
}

void HelperGuildAppointOfficerReqMsg(CNetMsg &a1, int a2, int a3, int a4)
{
    int v4; // eax@1
    int v5; // eax@1
    int v6; // eax@1

    a1.Init(123);
    v4 = CNetMsg::__ls(a1, 0x1Bu);
    v5 = CNetMsg::__ls(v4, src);
    v6 = CNetMsg::__ls(v5, a3);
    return CNetMsg::__ls(v6, a4);
}*/

void GuildAppointOfficerMsg(CNetMsg &a1, int a2, int a3)
{
    a1.Init(42);

	a1.__ls(14);
    a1.__ls(a2);
    a1.__ls(a3);
}

void HelperGuildChat(CNetMsg &a1, int a2, int a3, char const *a4, char const *a5)
{
    a1.Init(123);

    a1.__ls(0x1E);
    a1.__ls(a2);
    a1.__ls(a3);
    a1.__ls(a4);
    a1.__ls(a5);
}

void HelperGuildFireOfficerReqMsg(CNetMsg &a1, int a2, int a3, int a4)
{
    a1.Init(123);
	
    a1.__ls(0x1F);
    a1.__ls(a2);
    a1.__ls(a3);
    a1.__ls(a4);
}

void GuildFireOfficerMsg(CNetMsg &a1, int a2, int a3)
{
    a1.Init(42);
	
    a1.__ls(15);
    a1.__ls(a2);
    a1.__ls(a3);
}

void HelperCharDelMsg(CNetMsg &a1, int a2)
{
    a1.Init(123);

    a1.__ls(0x22);
    a1.__ls(a2);
}

void ChangeErrMsg(CNetMsg &a1, _tagMsgChangeErrType a2)
{
    a1.Init(47);

    a1.__ls(3);
    a1.__ls(a2);
}

void ChangeStartMsg(CNetMsg &a1, CPC *a2)
{
    a1.Init(47);

    a1.__ls(0);
    a1.__ls(a2->Unk4);
    a1.__ls(a2->Unk2388);
}

void ChangeStopMsg(CNetMsg &a1, CPC *a2)
{
    a1.Init(47);

    a1.__ls(1);
    a1.__ls(a2->Unk4);
}
