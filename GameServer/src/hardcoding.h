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

#ifndef HARDCODING_H
#define HARDCODING_H

#include <memory.h>

#include "Pos.h"

class CItem;
class CPC;

class CShop;
class CQuickSlot;
class CPCList;

class CShop {
public:
    int Unk0; // KeeperIDX
    float Unk4; // PosX
    float Unk8; // PosZ
    float Unk12; // PosR
    float Unk16; // PosH
    int Unk20; // YLayer
    int Unk24; // SellRate
    int Unk28; // BuyRate
    int *Unk32; // ItemList
    int Unk36; // ItemCount
public:
    CShop(void);
    ~CShop();

    bool ThersIsItem(int a2);
};

class CQuickSlot {
public:
    int Unk0[10];
    int Unk40[10]; // CHECK
    int Unk80[10]; // CHECK
    CItem *Unk120[10];
public:
    CQuickSlot(void);
};

#endif // HARDCODING_H
