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

#ifndef GUILD_H
#define GUILD_H

#include "NetMsg.h"

class CPC;

class CGuildMember;
class CGuild;
class CGuildList;

extern char byte_80D0030[4];

class CGuildMember {
public:
    int Unk0;
    char Unk4[52];
    int Unk56;
    CGuild *Unk60;
    int Unk64;
    char Unk68;
    CPC *Unk72;
public:
    CGuildMember(void);
    ~CGuildMember();

    void online(char a2);
    void charindex(int a2);
    void name(char const *src);
    void pos(int a2);
    void guild(CGuild *a2);
    int listindex(void);
    void SetPC(CPC *a2);
    CPC *GetPC(void);
    void listindex(int a2);
    int charindex(void);
    char *name(void);
    int pos(void);
    CGuild *guild(void);
    int online(void);
};

class CGuild {
public:
    int Unk0;
    char Unk4[20];
    int Unk24;
    CGuildMember *Unk28;
    CGuildMember *Unk32[2];
    CGuildMember *Unk40[30];
    int Unk160;
    CGuild *Unk164, *Unk168;
    CGuild *Unk172;
    CGuild *Unk176, *Unk180;
public:
    CGuild(int a2, char const *src, int a4);
    ~CGuild();

    int maxmember(void);
    int addmember(int a2, char const *src);
    CGuildMember *changeboss(int a2);
    CGuildMember *findmember(int a2, bool a3);
    void SendToAll(CNetMsg &a2);
    void DeleteAllChild(void);
    void removemember(CGuildMember *a2);
    void appoint(int a2);
    void fire(int a2);
    CGuildMember *boss(void);
    CGuildMember *officer(int a2);
    void level(int a2);
    CGuild *nextguild(void);
    void nextguild(CGuild *a2);
    CGuild *prevguild(void);
    void prevguild(CGuild *a2);
    CGuild *leftchild(void);
    CGuild *rightchild(void);
    int index(void);
    char *name(void);
    int level(void);
    CGuild *parentguild(void);
    int membercount(void);
    CGuildMember *member(int a2);
};

class CGuildList {
public:
    CGuild *Unk0;
    int Unk4;
public:
    CGuildList(void);
    ~CGuildList();

    static CGuild *create(int a1, char const *src, int a3, char const *a4);
    static CGuild *create(int a1, char const *src, int a3);
    void add(CGuild *a2);
    CGuild *findguild(int a2);
    CGuildMember *findmember(int a2);
    void Reset(void);
    void Remove(CGuild *a2);
};

#endif // GUILD_H
