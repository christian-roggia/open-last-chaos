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

#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"

class CPC;

class CInventoryRow;
class CInventory;

class CInventoryRow {
public:
    CInventory *Unk0;
    CItem *Unk4[5];
public:
    CInventoryRow(CInventory *a2);
    ~CInventoryRow();

    bool FindEmpty(int *a2);
    bool FindItem(int *a2, int a3, int a4, int a5);
    bool FindItem(int *a2, int a3);
    bool IsEmpty(void);
    bool Remove(int a2, bool a3, bool a4);
    int  GetSpace(void);
};

class CInventory {
public:
    CPC *Unk0;
    int Unk4;
    CInventoryRow *Unk8[20];
public:
    CInventory(void);
    ~CInventory();

    bool AddItem(CItem *a2, CPC *a3, bool a4, bool a5, int a6, int a7);
    bool Decrease(CItem *a2, long long a3);
    bool FindEmpty(int *a2, int *a3);
    CItem *GetItem(int a2, int a3);
    bool FindItem(int *a2, int *a3, int a4, int a5, int a6);
    bool FindItem(int *a2, int *a3, int a4);
    bool Swap(int a2, int a3, int a4, int a5, int a6, int a7);
    void Arrange(void);
    bool Remove(int a2, int a3, bool a4, bool a5);
    bool Remove(CItem *a2, bool a3, bool a4);
    int  GetSpace(void);
    CItem *GetItemBySerial(char const *s2);
    CItem *GetItem(int a2);
    void Init(CPC *a2, int a3);
};


#endif // INVENTORY_H
