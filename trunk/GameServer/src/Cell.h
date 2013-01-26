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

#ifndef CELL_H
#define CELL_H

#include "Global.h"
#include "NetMsg.h"

class CCharacter;
class CItem;
class CPC;

class CCell;

class CCell {
public:
    CCharacter *Unk0;
    CItem *Unk4;
    long Unk8, Unk12; // +0, +4, +8, +12
public:
    CCell(void);
    ~CCell() {}

    void CharToCell(CCharacter *a2);
    void CharFromCell(CCharacter *a2);
    bool Send(CNetMsg &a2, CPC *a3);
    void ItemToCell(CItem *a2);
    void ItemFromCell(CItem *a2);
};

#endif // CELL_H
