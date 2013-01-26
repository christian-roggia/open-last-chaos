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

#ifndef AREA_H
#define AREA_H

#include "Cell.h"
#include "DBCmd.h"
#include "Descriptor.h"
#include "Env.h"
#include "Global.h"
#include "Item.h"
#include "NetMsg.h"
#include "NPCRegenInfo.h"
#include "NPCProto.h"

class CCharacter;
class CPC;
class CNPC;

class CRoom;
class CZone;

class CArea;

class CArea {
public:
    char Unk0;      // isAreaEnabled
    CZone *Unk4;    // AreaZone
    int Unk8;
    int Unk12;
    int Unk16;
    int Unk20;
    CEnv ***Unk24;  // NotUsed
    CCell **Unk28;  // AreaCells
    CNPCRegenList Unk32;
    CNPC *Unk48;
    int Unk52; // Now
    int Unk56; // MobActivity?
    int Unk60; // MobRegen ?
    CRoom *Unk64;
    int Unk68;
    int Unk72;
    long Unk76;
public:
    CArea(void);
    ~CArea();

    void Init(CZone *a2, int a3, int a4, int a5, int a6);
    void PointToCellNum(float a2, float a3, int *a4, int *a5);
    void CharToCell(CCharacter *a2, char a3, int a4, int a5);
    void CharFromCell(CCharacter *a2);
    void ItemToCell(CItem *a2, char a3, int a4, int a5);
    void ItemFromCell(CItem *a2);
    bool MoveChar(CCharacter *a2, char a3, float a4, float a5, float a6, float a7, __tagMsgMoveType a8, CCharacter *a9);
    bool SendToCell(CNetMsg &a2, CCharacter *a3, bool a4, int a5);
    bool SendToCell(CNetMsg &a2, char a3, int a4, int a5, int a6);
    void SendCellInfo(CPC *a2);
    bool IsNotBlocked(CCharacter *a2, CCharacter *a3, bool a4);
    bool IsNotBlocked(CCharacter *a2, char a3, float a4, float a5, bool a6);
    char GetAttr(char a2, float a3, float a4);
    float GetHeight(char a2, float a3, float a4);
    void LoadNPC(void);
    int  GetPCCount(CCharacter *a2, int a3);
    int  GetPCCount(int a2, int a3, int a4);
    CCharacter *FindCharInCell(CCharacter *a2, int a3, __tagMsgCharType a4, bool a5);
    CCharacter *FindChar(int a2, __tagMsgCharType a3);
    void CreateRoom(int a2, char a3, int a4, int a5, int a6, int a7);
    CRoom *FindRoom(int a2, int a3);
    bool DeleteRoom(CRoom *a2);
    bool MoveToRoom(CCharacter *a2, float a3, float a4, float a5, int a6, int a7);
    void SetEnable(void);
    void SetDisable(void);
    CItem *DropItem(CItem *a2, CCharacter *a3);
    CItem *DropItem(int a2, CCharacter *a3, int a4, int a5, long long a6, bool a7);
    void GroundItemControl(void);
    void SendToAllClient(CNetMsg &a2);

    void MobActivity(void);
    CPC *FindNearestPC(CNPC *a2, float *a3);
    CNPC *MobTimeCheck(CNPC *a2);
    void AddNPC(CNPC *a2);
    void DelNPC(CNPC *a2);
    void MobRegen(void);
};

long double GetDistance(CCharacter *a1, CCharacter *a2);

#endif
