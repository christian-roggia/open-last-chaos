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

#ifndef PERSONALSHOP_H
#define PERSONALSHOP_H

#include <string.h>
#include <memory.h>

class CPersonalShop;

class CPersonalShop {
public:
    char Unk0; // Type
    char Unk1[103]; // Name
    int Unk104[10]; // NormalItemIndex
    long long Unk144[10]; // NormalItemCount
    long long Unk224[10]; // NormalItemPrice
    int Unk304[5]; // PackageItemIndex
    long long Unk324[5]; // PackageItemCount
    long long Unk364; // PackagePrice
public:
    CPersonalShop(char a2, char *src);

    bool AddItem(bool a2, int a3, long long a4, long long a5);
    int  FindItem(bool a2, int a3);
    void RemoveNormalItem(int a2, long long a3);
    void RemovePackage(void);
    char GetNormalCount(void);
    int  GetNextNormalItem(int a2);
    int  GetPackageCount(void);
    int  GetNextPackageItem(int a2);
    char GetType(void);
    char*GetName(void);
    int  GetNormalItemIndex(int a2);
    long long GetNormalItemCount(int a2);
    long long GetNormalItemPrice(int a2);
    long long GetPackagePrice(void);
    long long GetPackageItemIndex(int a2);
    long long GetPackageItemCount(int a2);
};

#endif // PERSONALSHOP_H
