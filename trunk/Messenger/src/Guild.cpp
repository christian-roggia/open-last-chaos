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

#include "Guild.hpp"

char defname[4];
CGuildList g_guildlist;

CGuildMember::CGuildMember()
{
    vCharIndex = -1;
    vName[0] = 0;
    vPosition = 2;
    vGuild = 0;
    vListIndex = -1;
    vOnline[0] = 0;
}

CGuildMember::~CGuildMember()
{
//  if ( a2 & 1 )
//    __builtin_delete(this);
}

int CGuildMember::charindex()
{
    return vCharIndex;
}

const char *CGuildMember::name()
{
    return vName;
}

int CGuildMember::pos()
{
    return vPosition;
}

CGuild *CGuildMember::guild() //CGuild
{
    return vGuild;
}

char CGuildMember::online()
{
    return vOnline[0];
}

void CGuildMember::charindex(int a2)
{
    vCharIndex = a2;
}

void CGuildMember::name(const char *src)
{
    if ( src )
        strcpy(vName, src);
    else
        strcpy(vName, defname);
}

void CGuildMember::pos(int a2)
{
    vPosition = a2;
}

void CGuildMember::guild(CGuild *guild) //CGuild
{
    vGuild = guild;
}

int CGuildMember::listindex()
{
    return vListIndex;
}

void CGuildMember::listindex(int a2)
{
    vListIndex = a2;
}

void CGuildMember::online(char a2)
{
    vOnline[0] = a2;
}


//***********************************CGUILD******************************************

CGuild::CGuild(int a2, const char *name, int level)
{
    if ( name && level > 0 )
    {
        strncpy(Name, name, 20u);
        LOBYTE(Level) = 0;
        Level = level;
        Boss = 0;
        memset(Officer, 0, 8u);
        memset(Member, 0, 120u);
        MemberCount = 0;
        NextGuild = 0;
        PrevGuild = 0;
        dwordAC = 0;
        LeftChild = 0;
        RightChild = 0;
        Index = a2;
    }
    else
    {
        memset(this, 0, 184u);
    }
}

CGuild::~CGuild()
{
    signed int i; // [sp+14h] [bp-4h]@1
    for ( i = 0; i <= 1; ++i )
    {
        if ( Member[i] )
        {
            if ( Member[i] )
                delete Member[i];
        }
    }
    memset(Officer, 0, 8u);
    memset(Member, 0, 0x78u);
    MemberCount = 0;
    NextGuild = 0;
    PrevGuild = 0;
//  if ( a2 & 1 )
//    __builtin_delete(this);
}

int CGuild::maxmember()
{
    int result; // eax@2
    switch ( Level )
    {
    case 1:
        result = 10;
        break;
    case 2:
        result = 15;
        break;
    case 3:
        result = 20;
        break;
    case 4:
        result = 25;
        break;
    case 5:
        result = 30;
        break;
    default:
        result = 0;
        break;
    }
    return result;
}

int CGuild::addmember(int retstr, const char *src)
{
    int result; // eax@2
//  CGuildMember *v4; // eax@8
//  CGuildMember *v5; // eax@8
    int i; // [sp+20h] [bp-Ch]@5
    CGuildMember *gmember; // [sp+28h] [bp-4h]@1
    gmember = CGuild::findmember(retstr, 0);
    if ( gmember )
        result = gmember->listindex();
    else
    {
        if ( MemberCount < CGuild::maxmember() )
        {
            for ( i = 0; ; ++i )
            {
                if ( i > 29 )
                    return -1;
                if ( !Member[i] )
                    break;
            }
//      GuildMember8 = (CGuildMember *)__builtin_new(0x48u);
            gmember = new CGuildMember;
//      CGuildMember::CGuildMember(v4);
//      v8 = v5;
            gmember->charindex(retstr);
            gmember->name(src);
            gmember->pos(2);
            gmember->guild(this);
            gmember->listindex(i);
            Member[i] = gmember;
            ++MemberCount;
            result = i;
        }
        else
        {
            result = -1;
        }
    }
    return result;
}

void CGuild::changeboss(int a2)
{
    if ( a2 >= 0 && a2 <= 29 && Member[a2] )
    {
        if ( Boss )
        {
            Boss->pos(2);
            Boss = 0;
        }
        if ( Member[a2]->pos() == 1 )
            CGuild::fire(a2);
        Boss = Member[a2];
        Boss->pos(0);
    }
}

CGuildMember *CGuild::findmember(int retstr, bool a3)
{
    CGuildMember *result; // eax@5
    CGuild *lchild; // eax@9
    CGuild *rchild; // eax@12
    signed int i; // [sp+14h] [bp-4h]@1
    for ( i = 0; i <= 29; ++i )
    {
        if ( Member[i] && Member[i]->charindex() == retstr )
            return Member[i];
    }
    if ( !a3 )
        return 0;
    if ( CGuild::leftchild() && (lchild = CGuild::leftchild(), (result = lchild->findmember(retstr, a3)) != 0 ) )
        return result;
    if ( CGuild::rightchild() && (rchild = CGuild::rightchild(), (result = rchild->findmember(retstr, a3)) != 0) )
        return result;
    else
        return 0;
}

void CGuild::DeleteAllChild()
{
    if ( LeftChild )
    {
        LeftChild->DeleteAllChild();
        if ( LeftChild )
            delete LeftChild;
        LeftChild = 0;
    }
    if ( RightChild )
    {
        RightChild->DeleteAllChild();
        if ( RightChild )
            delete RightChild;
        RightChild = 0;
    }
}

void CGuild::removemember(CGuildMember *member)
{
    signed int j; // [sp+10h] [bp-8h]@6
    signed int i; // [sp+14h] [bp-4h]@2
    if ( member )
    {
        for ( i = 0; i <= 29; ++i )
        {
            if ( Member[i] == member )
            {
                if ( member->pos() == 1 )
                {
                    for ( j = 0; j <= 1; ++j )
                    {
                        if ( Officer[j] == member )
                            Officer[j] = 0;
                    }
                }
                if ( member )
                    delete member;
                Member[i] = 0;
                --MemberCount;
                return;
            }
        }
    }
}

void CGuild::appoint(int a2)
{
    signed int i; // [sp+14h] [bp-4h]@5

    if ( a2 >= 0 && a2 <= 29 && Member[a2] )
    {
        for ( i = 0; i <= 1; ++i )
        {
            if ( !Officer[i] )
            {
                Officer[i] = Member[a2];
                Officer[i]->pos(1);
                return;
            }
        }
    }
}

void CGuild::fire(int a2)
{
    signed int i; // [sp+14h] [bp-4h]@5

    if ( a2 >= 0 && a2 <= 29 && Member[a2] )
    {
        for ( i = 0; i <= 1; ++i )
        {
            if ( Officer[i] == Member[a2] )
            {
                Officer[i]->pos(2);
                Officer[i] = 0;
                return;
            }
        }
    }
}

int CGuild::index()
{
    return Index;
}

const char *CGuild::name()
{
    return Name;
}

int CGuild::level()
{
    return Level;
}

CGuildMember *CGuild::boss()
{
    return Boss;
}

int CGuild::membercount()
{
    return MemberCount;
}

CGuildMember *CGuild::member(int a2)
{
    if ( a2 < 0 || a2 > 29 )
        return 0;
    else
        return Member[a2];
}

CGuild *CGuild::nextguild()
{
    return NextGuild;
}

void CGuild::nextguild(CGuild *a2)
{
    NextGuild = a2;
}

CGuild *CGuild::prevguild()
{
    return PrevGuild;
}

void CGuild::prevguild(CGuild *a2)
{
    PrevGuild = a2;
}

CGuild *CGuild::leftchild()
{
    return LeftChild;
}

CGuild *CGuild::rightchild()
{
    return RightChild;
}

void CGuild::LevelUp()
{
    if ( Level <= 4 )
        ++Level;
}

int CGuild::officer(int a2)
{
    int result; // eax@3
    if ( a2 < 0 || a2 > 1 )
        result = 0;
    else
        result = (int)Officer[a2];
    return result;
}

CGuildList::CGuildList()
{
    this->Guild = 0;
    this->GuildCount = 0;
}

CGuildList::~CGuildList()
{
    CGuild *v2; // [sp+14h] [bp-4h]@2

    while ( this->Guild )
    {
        v2 = this->Guild;
        this->Guild = Guild->nextguild();
        if ( v2 )
            //CGuild::_CGuild(v2, 3);
            delete this->Guild;
    }
//  if ( a2 & 1 )
//    __builtin_delete();
}

CGuild *CGuildList::create(int a1, const char *src, int a3, const char *a4)
{
    CGuild *result; // eax@5
    int v8; // ST30_4@9

    if ( src && a1 > 0 && a3 > 0 && a4 )
    {
        if ( strlen(src) && strlen(a4) )
        {
            CGuild *guild = new CGuild(a1,src,1);
            //v5 = (CGuild *)__builtin_new(184);
            //CGuild::CGuild(v5, a1, src, 1);
            //v7 = v6;
            v8 = guild->addmember(a3,a4);
            guild->changeboss(v8);
            //v8 = CGuild::addmember(v6, a3, a4);
            //CGuild::changeboss(v7, v8);
            //result = v7;
            result = guild;
        }
        else
        {
            result = 0;
        }
    }
    else
    {
        result = 0;
    }
    return result;
}

CGuild *CGuildList::create(int a1, const char *src, int a3)
{
    CGuild *result; // eax@5

    if ( src && a1 > 0 && a3 > 0 && a3 <= 5 )
    {
        if ( strlen(src) )
        {
            CGuild *guild = new CGuild(a1,src,1);
            //v4 = (CGuild *)__builtin_new(184);
            //CGuild::CGuild(v4, a1, src, a3);
            //v6 = v5;
            //result = v6;
            result = guild;
        }
        else
        {
            result = 0;
        }
    }
    else
    {
        result = 0;
    }
    return result;
}

void CGuildList::add(CGuild *newguild)
{
    if ( newguild )
    {
        if ( this->Guild )
            Guild->prevguild(newguild);
        newguild->prevguild(0);
        newguild->nextguild(this->Guild);
        this->Guild = newguild;
        ++this->GuildCount;
    }
}

CGuild *CGuildList::findguild(int guildindex)
{
    CGuild *t_guild;
    CGuild *p_guild; // [sp+14h] [bp-4h]@1

    for ( p_guild = this->Guild; p_guild; p_guild = p_guild->nextguild() )
    {
        if ( p_guild->index() == guildindex )
            return p_guild;
        if ( p_guild->leftchild() )
        {
            t_guild = p_guild->leftchild();
            if ( t_guild->index() == guildindex )
                return p_guild->leftchild();
            t_guild = p_guild->leftchild();
            if ( t_guild->leftchild() )
            {
                t_guild = p_guild->leftchild();
                t_guild = t_guild->leftchild();
                if ( t_guild->index() == guildindex )
                {
                    t_guild = p_guild->leftchild();
                    return t_guild->leftchild();
                }
            }
            t_guild = p_guild->leftchild();
            if ( t_guild->rightchild() )
            {
                t_guild = p_guild->leftchild();
                t_guild = t_guild->rightchild();
                if ( t_guild->index() == guildindex )
                {
                    t_guild = p_guild->leftchild();
                    return t_guild->rightchild();
                }
            }
        }
        if ( p_guild->rightchild() )
        {
            t_guild = p_guild->rightchild();
            if ( t_guild->index() == guildindex )
                return p_guild->rightchild();
            t_guild = p_guild->rightchild();
            if ( t_guild->leftchild() )
            {
                t_guild = p_guild->rightchild();
                t_guild = t_guild->leftchild();
                if ( t_guild->index() == guildindex )
                {
                    t_guild = p_guild->rightchild();
                    return t_guild->leftchild();
                }
            }
            t_guild = p_guild->rightchild();
            if ( t_guild->rightchild() )
            {
                t_guild = p_guild->rightchild();
                t_guild = p_guild->rightchild();
                if ( t_guild->index() == guildindex )
                {
                    t_guild = p_guild->rightchild();
                    return t_guild->rightchild();
                }
            }
        }
    }
    return 0;
}

CGuildMember *CGuildList::findmember(int memb)
{
    CGuild *i; // [sp+10h] [bp-8h]@1
    CGuildMember *gmember; // [sp+14h] [bp-4h]@1

    gmember = 0;
    for ( i = this->Guild; i; i = i->nextguild() )
    {
        gmember = i->findmember(memb, 1);
        if ( gmember )
            return gmember;
    }
    return gmember;
}

void CGuildList::Reset()
{
    CGuild *i; // [sp+14h] [bp-4h]@1

    for ( i = this->Guild; i; i = this->Guild )
    {
        this->Guild = i->nextguild();
        i->DeleteAllChild();
        if ( i )
            //CGuild::_CGuild(i, 3);
            delete i;
    }
    this->GuildCount = 0;
}

void CGuildList::Remove(CGuild *delguild)
{
    CGuild *v2; // ST10_4@7
    CGuild *v3; // eax@7
    CGuild *t_guild; // [sp+14h] [bp-4h]@1

    for ( t_guild = this->Guild; t_guild && t_guild != delguild; t_guild = t_guild->nextguild() )
        ;
    if ( t_guild )
    {
        if ( t_guild->prevguild() )
        {
            v2 = t_guild->nextguild();
            v3 = t_guild->prevguild();
            v3->nextguild(v2);
        }
        if ( t_guild->nextguild() )
        {
            v2 = t_guild->prevguild();
            v3 = t_guild->nextguild();
            v3->prevguild(v2);

        }
        if ( t_guild == this->Guild )
            this->Guild = t_guild->nextguild();
        t_guild->prevguild(0);
        t_guild->nextguild(0);
        --this->GuildCount;
        if ( t_guild )
            //CGuild::_CGuild(t_guild, 3);
            delete t_guild;
    }
}
