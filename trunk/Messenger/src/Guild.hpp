/******************************************************************************************
  Copyright 2013 Andrea Ragusa

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

class CGuild;
class CGuildMember;
class CGuildList;

#ifndef __GUILD
#define __GUILD

#include "common.hpp"
#include "Descriptor.hpp"
#include "doFunc.hpp"





class CGuildMember
{
public:
    CGuildMember();
    ~CGuildMember();
    int charindex();
    const char *name();
    int pos();
    CGuild *guild(); //CGuild
    char online();
    void charindex(int a2);
    void name(const char *src);
    void pos(int a2);
    void guild(CGuild *guild); //CGuild
    int listindex();
    void listindex(int a2);
    void online(char a2);
private:
    int vCharIndex;
    char vName[52];
    int vPosition;
    CGuild *vGuild; //CGuild
    int vListIndex;
    char vOnline[4];
};


class CGuild
{
public:
    CGuild(int a2, const char *name, int level);
    ~CGuild();
    int maxmember();
    int addmember(int retstr, const char *src);
    void changeboss(int a2);
    CGuildMember *findmember(int retstr, bool a3);
    void DeleteAllChild();
    void removemember(CGuildMember *member);
    void appoint(int a2);
    void fire(int a2);
    int index();
    const char *name();
    int level();
    CGuildMember *boss();
    int membercount();
    CGuildMember *member(int a2);
    CGuild *nextguild();
    void nextguild(CGuild *a2);
    CGuild *prevguild();
    void prevguild(CGuild *a2);
    CGuild *leftchild();
    CGuild *rightchild();
    void LevelUp();
    int officer(int a2);

    int Index;
    char Name[20];
    int Level;
    CGuildMember *Boss;
    CGuildMember *Officer[2];
    CGuildMember *Member[30];
    int MemberCount;
    CGuild *NextGuild;
    CGuild *PrevGuild;
    int dwordAC;
    CGuild *LeftChild;
    CGuild *RightChild;
};
class CGuildList
{
public:
    CGuildList();
    ~CGuildList();
    CGuild *create(int a1, const char *src, int a3, const char *a4);
    CGuild *create(int a1, const char *src, int a3);
    void add(CGuild *newguild);
    CGuild *findguild(int guildindex);
    CGuildMember *findmember(int memb);
    void sendlist(CDescriptor *desc);
    void Reset();
    void Remove(CGuild *delguild);
private:
    CGuild *Guild;
    int GuildCount;
};

#endif

extern CGuildList g_guildlist;
