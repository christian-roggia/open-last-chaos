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

#ifndef ITEM_H
#define ITEM_H

#include "DBCmd.h"
#include "Item.h"
#include "Option.h"
#include "Pos.h"

/***********************************
TODO: CItem::`vtbl'{00000000 080CC9F0 08074140 00000000}
TODO: CItemList::`vtbl'{00000000 080CCA30 08074300 00000000}
TODO: CItemProto::`vtbl'{00000000 080CC9B0 08074260 00000000}
************************************/

class CArea;
class CItem;
class CItemProto;
class CItemList;

class CItem {
public:
    long Unk0;
    int Unk4;
    long Unk8;
    long long Unk12;
    CItemProto *Unk20;
    int Unk24;
    int Unk28;
    char Unk32;
    int Unk36;
    int Unk40;
    char Unk44[20]; // Serial
    int Unk64; // FROM CDBThread
    COption Unk68[5];
    int Unk168;
    CArea *Unk172;
    CPos Unk176;
    int Unk196, Unk200;
    CItem *Unk204, *Unk208;
    long Unk212, Unk216;
    //long Unk220 -----> Virtual Table
public:
    CItem(void);
    ~CItem();

    int tab(void);
    int row(void);
    int col(void);
    long long Count(void);
    bool IsRangeWeapon(void);
    bool IsMagicWeapon(void);
    bool IsWeaponType(void);
    bool IsArmorType(void);
    bool IsAccessary(void);
};

class CItemProto {
public:
    int Unk0; // Index
    int Unk4; // TypeIndex
    int Unk8; // SubTypeIndex
    char Unk12[52]; // NameChannel
    int Unk64; // JobFlag
    int Unk68; // Flag
    int Unk72; // MaxUse
    int Unk76; // Num0
    int Unk80; // Num1
    int Unk84; // Num2
    int Unk88; // Num3
    int Unk92; // Num4
    long long Unk96; // Weight
    short Unk100; // Level
    int Unk104; // Price
    int Unk108; // Wearing
    int Unk112[10]; // NeedItem
    int Unk152[10]; // NeedItemCount
    int Unk192; // NeedSSkill
    int Unk196; // NeedSSkillLevel
    int Unk200; // NeedSSkill2
    int Unk204; // NeedSSkillLevel2
    //long Unk208 -----> Virtual Table
public:
    CItemProto(void);
    ~CItemProto();
};

class CItemList {
public:
    int Unk0; // Count
    long Unk4;
    CItemProto *Unk8;
    CItemProto *Unk12;
    CItemProto *Unk16;
    CItemProto *Unk20;
    CItemProto *Unk24;
    CItemProto *Unk28;
    CItemProto *Unk32;
    // long Unk36; -----> Virtual Table
public:
    CItemList(void);
    ~CItemList();

    void Load(void);
    CItemProto *FindIndex(int a2);
    CItem *CreateDBItem(int a2, char a3, int a4, int a5, int a6, char const *src, long long a8, short *a9);
    CItem *CreateItem(int a2, char a3, int a4, int a5, long long a6);
    static int CompIndex(void const *a1, void const *a2);
    int GetNextVirtualIndex(void);
};

/********************************************************************************
 * Serialization Function
 ********************************************************************************/

extern char code62[63];
void GetSerial(char *a1, int a2);

#endif // ITEM_H
