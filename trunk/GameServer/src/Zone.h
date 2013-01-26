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

#ifndef ZONE_H
#define ZONE_H

#include "Area.h"
#include "CmdMsg.h"
#include "DBCmd.h"
#include "hardcoding.h"
#include "Log.h"
#include "MapAttr.h"
#include "Random.h"

class CZone;

struct SUnkStruct {
    int Unk0; // INT?
    int Unk4;
    int Unk8;
    int Unk12;
    int Unk16;
};

class CZone {
public:
    int Unk0;
    char Unk4, Unk5[21];
    short Unk26;
    int Unk28;
    CMapAttr *Unk32;
    CArea *Unk36;
    int Unk40;
    char Unk44, Unk45;
    long Unk48;
    SUnkStruct **Unk52; // CHECK
    CShop *Unk56;
    int Unk60; // ShopCount
    int Unk64;
    int Unk68;
public:
    CZone(void);
    ~CZone();

    bool LoadZone(int a2);
    bool LoadNPC(void);  // ALWAYS TRUE O.o
    bool LoadShop(void); // ALWAYS TRUE O.o
    int  SetEnableArea(void);
    void SetDisableArea(int a2);
    CShop *FindShop(int a2);
    void ChangeWeather(void);
    void ChangeTaxRate(int a2, int a3);
    int  FindEmptyArea(void);
    static int CompIndex(void const *m_index1, void const *m_index2);
};

#endif
