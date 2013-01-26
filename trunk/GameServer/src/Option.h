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

#ifndef OPTION_H
#define OPTION_H

#include "DBCmd.h"
#include "Random.h"

class CPC;

class COptionProto;
class COptionProtoList;
class COption;

extern int limit_548[4];
extern char optionLevel_537[255];
extern char optionProb_538[255];

class COptionProto {
public:
    int Unk0; // Index
    int Unk4; // Type
    int Unk8[7]; // Level
    int Unk36[7]; // Prop
    int Unk64; // WeaponType
    int Unk68; // WearType
    int Unk72; // AccessoryType
public:
    COptionProto(void);
};

class COptionProtoList {
public:
    COptionProto *Unk0;
    int Unk4; // OptionCount
public:
    COptionProtoList(void);
    ~COptionProtoList();

    bool Load(void);
    COptionProto *FindProto(int a2);
    static int CompIndex(void const *a1, void const *a2);
};

class COption {
public:
    COptionProto *Unk0;
    int Unk4; // NOT SURE
    int Unk8;
    int Unk12;
    short Unk16;
public:
    COption(void);

    void MakeOptionValue(COptionProto *a2, int a3, int a4);
    void ApplyOptionValue(CPC *a2);
    void GetDBValue(short a2);
    void SetDBValue(void);
};

#endif // OPTION_H
