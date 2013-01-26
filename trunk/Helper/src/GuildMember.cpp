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

#include "GuildMember.hpp"

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
    __builtin_delete(this);
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

CGuild *CGuildMember::guild()
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
    strcpy(vName, byte_805A0EC);
}

void CGuildMember::pos(int a2)
{
  vPosition = a2;
}

void CGuildMember::guild(CGuild *guild)
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
