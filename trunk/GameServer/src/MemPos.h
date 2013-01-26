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

#ifndef MEMPOS_H
#define MEMPOS_H

#include "string.h"

class CMemPosData;
class CMemPos;

class CMemPosData {
public:
    int Unk0;
    float Unk4, Unk8;
    char Unk12, Unk13[152]; // CHECK!
public:
    CMemPosData(int a2, float a3, float a4, char a5, char const *src);
};

class CMemPos {
public:
    int Unk0;
    CMemPosData *Unk4[5];
public:
    CMemPos(void);
    ~CMemPos();

    bool Write(int a2, int a3, float a4, float a5, char a6, char const *src);
    bool Delete(int a2);
};

#endif // MEMPOS_H
