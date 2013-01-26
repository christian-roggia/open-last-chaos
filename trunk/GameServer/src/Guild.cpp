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

#include "Guild.h"

#include "PC.h"
#include "Server.h"

char byte_80D0030[4] = {0, 0, 0, 0};

CGuildMember::CGuildMember(void)
{
    this->Unk0 = -1;
    *this->Unk4 = 0;
    this->Unk56 = 2;
    this->Unk60 = 0;
    this->Unk64 = -1;
    this->Unk68 = 0;
    this->Unk72 = 0;
}

CGuildMember::~CGuildMember()
{
    if(this->Unk72)
        this->Unk72->Unk2368 = 0;

    this->Unk72 = 0;
}

CGuild::CGuild(int a2, char const *src, int a4)
{
    if(src && a4 > 0)
    {
        strncpy(this->Unk4, src, 20);
        this->Unk4[20] = 0;
        this->Unk24 = a4;
        this->Unk28 = 0;
        memset(this->Unk32, 0, 8);
        memset(this->Unk40, 0, 120);
        this->Unk160 = 0;
        this->Unk164 = 0;
        this->Unk168 = 0;
        this->Unk172 = 0;
        this->Unk176 = 0;
        this->Unk180 = 0;
        this->Unk0   = a2;
    }
    else
    {
        memset(this, 0, sizeof(this));
    }
}

CGuild::~CGuild()
{
    for(int i = 0; i <= 1; ++i)
    {
        if(this->Unk40[i])
        {
            if(this->Unk40[i])
                delete this->Unk40[i];
        }
    }

    memset(this->Unk32, 0, 8);
    memset(this->Unk40, 0, 120);

    this->Unk160 = 0;
    this->Unk164 = 0;
    this->Unk168 = 0;
}

int CGuild::maxmember(void)
{
        switch(this->Unk24)
        {
        case 1:
                return 10;
                break;
        case 2:
                return 15;
                break;
        case 3:
                return 20;
                break;
        case 4:
                return 25;
                break;
        case 5:
                return 30;
                break;
        default:
                return 0;
                break;
        }
}

int CGuild::addmember(int a2, char const *src)
{
    int i; // [sp+20h] [bp-Ch]@5
    CGuildMember *v7; // [sp+28h] [bp-4h]@1
    CGuildMember *v8; // [sp+28h] [bp-4h]@8

    v7 = this->findmember(a2, 0);
    if(v7)
        return v7->listindex();

    if(this->Unk160 < this->maxmember())
    {
        for(i = 0; ; ++i)
        {
            if(i > 29)
                return -1;

            if(!this->Unk40[i])
                break;
        }

        v8 = new CGuildMember();
        v8->charindex(a2);
        v8->name(src);
        v8->pos(2);
        v8->guild(this);
        v8->listindex(i);

        this->Unk40[i] = v8;
        ++this->Unk160;

        return i;
    }

    return -1;
}

CGuildMember *CGuild::changeboss(int a2)
{
    CGuildMember *v3; // [sp+14h] [bp-4h]@4

    if(a2 >= 0 && a2 <= 29)
    {
        v3 = 0;
        if(this->Unk40[a2])
        {
            if(this->Unk28)
            {
                v3 = this->Unk28;
                this->Unk28->pos(2);
                this->Unk28 = 0;
            }

            if(this->Unk40[a2]->pos() == 1)
                this->fire(a2);

            this->Unk28 = this->Unk40[a2];
            this->Unk28->pos(0);
        }

        return v3;
    }

    return 0;
}

CGuildMember *CGuild::findmember(int a2, bool a3)
{
    CGuildMember *v6; // [sp+10h] [bp-8h]@9

    for(int i = 0; i <= 29; ++i)
    {
        if(this->Unk40[i] && this->Unk40[i]->charindex() == a2)
            return this->Unk40[i];
    }

    if(!a3)
        return 0;

    if(this->leftchild() && ((v6 = this->leftchild()->findmember(a2, a3)) != 0))
        return v6;

    if(this->rightchild() && ((v6 = this->rightchild()->findmember(a2, a3)) != 0))
        return v6;

    return 0;
}

CGuildList::CGuildList(void)
{
    this->Unk0 = 0;
    this->Unk4 = 0;
}

CGuildList::~CGuildList()
{
    CGuild *v3; // [sp+14h] [bp-4h]@2

    while(this->Unk0)
    {
        v3 = this->Unk0;
        this->Unk0 = this->Unk0->nextguild();

        if(v3)
            delete v3;
    }
}

CGuild *CGuildList::create(int a1, char const *src, int a3, char const *a4)
{
    CGuild *v6; // ST34_4@9

    if(src && a1 > 0 && a3 > 0 && a4)
    {
        if(strlen(src) && strlen(a4))
        {
            v6 = new CGuild(a1, src, 1);
            v6->changeboss(v6->addmember(a3, a4));

            return v6;
        }
    }

    return 0;
}

CGuild *CGuildList::create(int a1, char const *src, int a3)
{
    CGuild *v6; // [sp+14h] [bp-4h]@8

    if(src && a1 > 0 && a3 > 0 && a3 <= 5)
    {
        if(strlen(src))
        {
            v6 = new CGuild(a1, src, a3);
            return v6;
        }
    }

    return 0;
}

void CGuildList::add(CGuild *a2)
{
    if(a2)
    {
        if(this->Unk0)
            this->Unk0->prevguild(a2);

        a2->prevguild(0);
        a2->nextguild(this->Unk0);
        this->Unk0 = a2;
        ++this->Unk4;
    }
}

CGuild *CGuildList::findguild(int a2)
{
    for(CGuild *i = this->Unk0; i; i = i->nextguild())
    {
        if(i->index() == a2)
            return i;

        if(i->leftchild())
        {
            if(i->leftchild()->index() == a2)
                return i->leftchild();

            if(i->leftchild()->leftchild())
            {
                if(i->leftchild()->leftchild()->index() == a2)
                    return i->leftchild()->leftchild();
            }

            if(i->leftchild()->rightchild())
            {
                if(i->leftchild()->rightchild()->index() == a2)
                    return i->leftchild()->rightchild();
            }
        }

        if(i->rightchild())
        {
            if(i->rightchild()->index() == a2)
                return i->rightchild();

            if(i->rightchild()->leftchild())
            {
                if(i->rightchild()->leftchild()->index() == a2)
                    return i->rightchild()->leftchild();
            }

            if(i->rightchild()->rightchild())
            {
                if(i->rightchild()->rightchild()->index() == a2)
                    return i->rightchild()->rightchild();
            }
        }
    }

    return 0;
}

CGuildMember *CGuildList::findmember(int a2)
{
    CGuildMember *v4; // [sp+14h] [bp-4h]@1

    v4 = 0;
    for(CGuild *i = this->Unk0; i; i = i->nextguild())
    {
        v4 = i->findmember(a2, 1);

        if(v4)
            return v4;
    }

    return v4;
}

void CGuild::SendToAll(CNetMsg &a2)
{
    for(int i = 0; i <= 29; ++i)
    {
        if(this->Unk40[i] && this->Unk40[i]->GetPC())
        {
            if(this->Unk40[i]->GetPC()->Unk768)
                this->Unk40[i]->GetPC()->Unk768->WriteToOutput(a2);
        }
    }
}

void CGuildList::Reset(void)
{
    for(CGuild *i = this->Unk0; i; i = this->Unk0)
    {
        this->Unk0 = i->nextguild();
        i->DeleteAllChild();

        if(i)
            delete i;
    }

    this->Unk4 = 0;
}

void CGuild::DeleteAllChild(void)
{
    if(this->Unk176)
    {
        this->Unk176->DeleteAllChild();

        if(this->Unk176)
            delete this->Unk176;

        this->Unk176 = 0;
    }

    if(this->Unk180)
    {
        this->Unk180->DeleteAllChild();

        if(this->Unk180)
            delete this->Unk180;

        this->Unk180 = 0;
    }
}

void CGuildList::Remove(CGuild *a2)
{
    CGuild *i; // [sp+14h] [bp-4h]@1

    for(i = this->Unk0; i; i = this->Unk0)
    {
        if(i == a2)
            break;

        i->nextguild();
    }

    if(i)
    {
        if(i->prevguild())
            i->prevguild()->nextguild(i->nextguild());

        if(i->nextguild())
            i->nextguild()->prevguild(i->prevguild());

        if(i == this->Unk0)
            this->Unk0 = i->nextguild();

        i->prevguild(0);
        i->nextguild(0);

        --this->Unk4;
        if(i)
            delete i;
    }
}

void CGuild::removemember(CGuildMember *a2) //void _CGuild::removemember(CGuildMember *)
{
    if(a2)
    {
        for(int i = 0; i <= 29; ++i)
        {
            if(this->Unk40[i] == a2)
            {
                if(a2->GetPC())
                    a2->GetPC()->Unk2368 = 0;

                a2->SetPC(0);

                if(a2->pos() == 1)
                {
                    for(int j = 0; j <= 1; ++j)
                    {
                        if(this->Unk32[j] == a2)
                            this->Unk32[j] = 0;
                    }
                }

                if(a2)
                    delete a2;

                this->Unk40[i] = 0;
                --this->Unk160;
            }
        }
    }
}

void CGuild::appoint(int a2)
{
    if(a2 >= 0)
    {
        if(a2 <= 29)
        {
            if(this->Unk40[a2])
            {
                for(int i = 0; i <= 1; ++i)
                {
                    if(!this->Unk32[i])
                    {
                        this->Unk32[i] = this->Unk40[a2];
                        this->Unk32[i]->pos(1);
                    }
                }
            }
        }
    }
}

void CGuild::fire(int a2)
{
    if(a2 >= 0)
    {
        if(a2 <= 29)
        {
            if(this->Unk40[a2])
            {
                for(int i = 0; i <= 1; ++i)
                {
                    if(this->Unk32[i] == this->Unk40[a2])
                    {
                        this->Unk32[i]->pos(2);
                        this->Unk32[i] = 0;
                    }
                }
            }
        }
    }
}

CGuildMember *CGuild::boss(void)
{
    return this->Unk28;
}

CGuildMember *CGuild::officer(int a2)
{
    return (a2 < 0 || a2 > 1) ? 0 : this->Unk32[a2];
}

void CGuildMember::online(char a2)
{
    this->Unk68 = a2;
}

void CGuild::level(int a2)
{
    this->Unk24 = a2;
}

void CGuildMember::charindex(int a2)
{
    this->Unk0 = a2;
}

void CGuildMember::name(char const *src)
{
    if(src)
        strcpy(this->Unk4, src);
    else
        strcpy(this->Unk4, byte_80D0030);
}

void CGuildMember::pos(int a2)
{
    this->Unk56 = a2;
}

void CGuildMember::guild(CGuild *a2)
{
    this->Unk60 = a2;
}

int CGuildMember::listindex(void)
{
    return this->Unk64;
}

void CGuildMember::SetPC(CPC *a2)
{
    this->Unk72 = a2;
    if(a2)
        a2->Unk2368 = this;
}

CPC *CGuildMember::GetPC(void)
{
    return this->Unk72;
}

void CGuildMember::listindex(int a2)
{
    this->Unk64 = a2;
}

CGuild *CGuild::nextguild(void)
{
    return this->Unk164;
}

void CGuild::nextguild(CGuild *a2)
{
    this->Unk164 = a2;
}

CGuild *CGuild::prevguild(void)
{
    return this->Unk168;
}

void CGuild::prevguild(CGuild *a2)
{
    this->Unk168 = a2;
}

CGuild *CGuild::leftchild(void)
{
    return this->Unk176;
}

CGuild *CGuild::rightchild(void)
{
    return this->Unk180;
}

int CGuildMember::charindex(void)
{
    return this->Unk0;
}

char *CGuildMember::name(void)
{
    return this->Unk4;
}

int CGuildMember::pos(void)
{
    return this->Unk56;
}

CGuild *CGuildMember::guild(void)
{
    return this->Unk60;
}

int CGuildMember::online(void)
{
    return this->Unk68;
}

int CGuild::index(void)
{
    return this->Unk0;
}

char *CGuild::name(void)
{
    return this->Unk4;
}

int CGuild::level(void)
{
    return this->Unk24;
}

CGuild *CGuild::parentguild(void)
{
    return this->Unk172;
}

int CGuild::membercount(void)
{
    return this->Unk160;
}

CGuildMember *CGuild::member(int a2)
{
    return (a2 < 0 || a2 > 29) ? 0 : this->Unk40[a2];
}
