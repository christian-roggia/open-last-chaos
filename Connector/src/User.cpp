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

#include "User.h"

CUser::CUser(int m_unk1, char const *m_username, int m_unk2, int m_unk3, char const *m_password)
{
  this->PortalIndex = m_unk1;
  strcpy(this->Username, m_username);
  this->ServerNum = m_unk2;
  this->SubServerNum = m_unk3;
  this->ZoneNum = 0;
  strcpy(this->Password, m_password);
  this->Unk80 = 0;
  this->Index = -1;
  this->Timestamp = 0;
  this->Unk92 = 0;
  this->Unk96 = 0;
  this->Unk100 = 0;
  this->Unk104 = 0;
  this->Unk108 = 0;
  this->Unk112 = 0;
}

CUserList::CUserList(void)
{
    this->UserMaxRange = 0;
    this->UsersOnline  = 0;
    this->Users        = (CUser **)malloc(sizeof(CUser *) * 50000);
    memset(this->Users, 0, sizeof(CUser *) * 50000);
    memset(this->Count, -1, 0x50);
}

CUserList::~CUserList(void)
{
    if(this->Users)
    {
        for(int i = 0; i <= this->UserMaxRange; ++i)
        {
          if(&this->Users[i])
              delete this->Users[i];
        }

        if(this->Users)
            delete this->Users;
    }
}

CUser *CUserList::Add(CUser *m_user)
{
    long i;

    if(this->UsersOnline <= 49999)
    {
        for(i = 0; i <= this->UserMaxRange && &this->Users[i]; ++i);

        this->Users[i] = m_user;
        m_user->Index = i;
        ++this->UsersOnline;

        if(this->UserMaxRange < i)
            this->UserMaxRange = i;

        g_gamelogbuffer.__ls(init("PLAYER_ADD", this->Users[i]->Username));
        g_gamelogbuffer.__ls((int)i);
        g_gamelogbuffer.__ls(end);

        return this->Users[i];
    }

    return 0;
}

bool CUserList::Remove(CUser *m_user, bool m_delete_istance)
{
    if(m_user->Index >= 0 && m_user->Index <= 49999 && this->Users[m_user->Index] == m_user)
    {
        g_gamelogbuffer.__ls(init("PLAYER_DEL", m_user->Username));
        g_gamelogbuffer.__ls((int)m_user->Index);
        g_gamelogbuffer.__ls(end);

        this->Users[m_user->Index] = 0;
        --this->UsersOnline;

        if(m_delete_istance)
            delete m_user;

        return true;
    }

    return false;
}

CUser *CUserList::Find(char const *m_username)
{
    for(int i = 0; i <= this->UserMaxRange; ++i)
    {
        if(this->Users[i] && !strcasecmp(this->Users[i]->Username, m_username))
            return this->Users[i];
    }

    return 0;
}

CUser *CUserList::Find(int m_portal_index)
{
    for(int i = 0; i <= this->UserMaxRange; ++i)
    {
        if(this->Users[i] && this->Users[i]->PortalIndex == m_portal_index)
            return this->Users[i];
    }

    return 0;
}
