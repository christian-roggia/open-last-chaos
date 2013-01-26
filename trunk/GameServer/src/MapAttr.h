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

#ifndef MAPATTR_H
#define MAPATTR_H

#include <fstream>
#include <netinet/in.h>
#include "Log.h"

class CMapAttr;

class CMapAttr {
public:
    int Unk0, Unk4; // +0, +4
    char **Unk8;    // +8
    float **Unk12;  // +12
public:
    CMapAttr(void);
    ~CMapAttr();

    bool Load(int a2, int a3, int a4, int a5, char const *filename, char const *a7);
};

#endif // MAPATTR_H
