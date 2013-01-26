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

#ifndef STASH_H
#define STASH_H

#include "Item.h"

class CStash;

class CStash {
public:
    CItem *Unk0[50];
public:
    CStash(void);
    ~CStash();

    int add(CItem *a2);
    int add(int a2, int a3, int a4, long long a5);
    int remove(int a2, long long a3);
    CItem *remove(int a2);
    int find(int a2, int a3, int a4);
    int find(int a2);
    int space(void);
    CItem *item(int a2);
};

#endif // STASH_H
