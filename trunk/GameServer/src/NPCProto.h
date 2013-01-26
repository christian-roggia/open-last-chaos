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

#ifndef NPCPROTO_H
#define NPCPROTO_H

#include "DBCmd.h"
#include "Log.h"

class CNPC;

class CNPCProto;
class CNPCProtoList;

class CNPCProto {
public:
    int Unk0; // Index
    char Unk4[52]; // NameCHN
    int Unk56; // Level
    int Unk60; // Exp
    int Unk64; // Prize
    int Unk68; // Sight
    int Unk72; // SkillPoint
    float Unk76; // WalkSpeed
    float Unk80; // RunSpeed
    float Unk84; // Size
    short Unk88; // HP
    short Unk90; // MP
    short Unk92; // Flag
    int Unk96; // Family
    short Unk100; // RecoverHP
    short Unk102; // RecoverMP
    int Unk104[20]; // ItemK
    int Unk184[20]; // ItemPercentK
    int Unk264; // ItemKCounter
    int Unk268[5]; // ProductK
    short Unk288; // STR
    short Unk290; // DEX
    short Unk292; // INT
    short Unk294; // CON
    short Unk296; // Attack
    short Unk298; // Magic
    short Unk300; // Defense
    short Unk302; // Resist
    short Unk304; // AttackLevel
    short Unk306; // DefenseLevel
    char Unk308; // AttackType
    char Unk309; // AttackSpeed
    float Unk312; // AttackArea -> Check float type
    long Unk316;
    int Unk320[2]; // SkillK1
    int Unk328[2]; // SkillK2
    int Unk336[2]; // SkillK3
    char Unk344; // MoveArea
public:
    CNPCProto(void);
    ~CNPCProto();
};

class CNPCProtoList {
public:
    CNPCProto *Unk0;
    long Unk4;
    int Unk8;
public:
    CNPCProtoList(void);
    ~CNPCProtoList();

    bool Load(void);
    CNPC *Create(int a2);
    CNPCProto *FindProto(int a2);
    static int CompIndex(void const *a1, void const *a2);
};

#endif // NPCPROTO_H
