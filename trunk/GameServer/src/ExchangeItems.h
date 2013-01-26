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

#ifndef EXCHANGEITEMS_H
#define EXCHANGEITEMS_H

#include "Item.h"
#include "Log.h"
#include "PC.h"

class CExchangeItemsData;
class CExchangeItems; // size = 260

class CExchangeItemsData {
public:
    CPC *Unk0;              // +0  <--------- Exchanger
    int Unk4;               // +4  <--------- ItemCount
    int Unk8[10];           // +8  <--------- ItemsToExchange
    long long Unk48[10];    // +48 <--------- ItemsToExchangeCount
public:
    CExchangeItemsData(void);

    void SetCharacter(CPC *a2);
    int Add(int a2, long long a3, bool *a4);
    int Del(int a2, long long a3);
    int Find(int a2);
    int FindEmpty(void);
};

class CExchangeItems {
public:
    long Unk0;
    CExchangeItemsData Unk4, Unk132; // +4, +132
public:
    CExchangeItems(void);

    void SetCharacter(CPC *a2, CPC *a3);
    int Add(CPC *a2, int a3, long long a4, bool *a5);
    int Del(CPC *a2, int a3, long long a4);
    int Find(CPC *a2, int a3);
    int CanExchange(void);
    void DoExchange(void);
};

#endif
