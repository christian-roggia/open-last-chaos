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

#ifndef ROOM_H
#define ROOM_H

#include "Area.h"
#include "Cell.h"
#include "Env.h"
#include "Global.h"

class CArea;
class CPC;

class CRoom {
public:
    CArea *Unk0;
    int Unk4, Unk8;
    char Unk12;
    int Unk16, Unk20, Unk24, Unk28;
    CEnv **Unk32;
    CCell **Unk36;
    CNPCRegenList Unk40;
    CNPC *Unk56;
    int Unk60;
    long Unk64;
    int Unk68;
    CRoom *Unk72, *Unk76;
public:
    CRoom(void);
    ~CRoom();

    void Init(CArea *a2, int a3, char a4, int a5, int a6, int a7, int a8, CNPCRegenList a10);
    void AddNPC(CNPC *a2);
    void PointToCellNum(float a2, float a3, int *a4, int *a5);
    void CharToCell(CCharacter *a2, int a3, int a4);
    bool SendToCell(CNetMsg &a2, CCharacter *a3, bool a4);
    bool SendToCell(CNetMsg &a2, int a3, int a4);
    bool MoveChar(CCharacter *a2, char a3, float a4, float a5, float a6, float a7, __tagMsgMoveType a8, CCharacter *a9);
    bool IsNotBlocked(CCharacter *a2, CCharacter *a3, bool a4);
    bool IsNotBlocked(CCharacter *a2, float a3, float a4, bool a5);
    void CharFromCell(CCharacter *a2);
    void SendCellInfo(CPC *a2);

    static int m_idxgen;
};

#endif // ROOM_H
