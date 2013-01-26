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

#include "doFunc.hpp"

void MsgrWhisperNotfoundMsg(CNetMsg &netmsg, int a2, int a3, int a4, int a5, int a6, const char *a7)
{
    netmsg.Init(102);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
    netmsg.__ls(a4);
    netmsg.__ls(5);
    netmsg.__ls(3);
    netmsg.__ls(a6);
    netmsg.__ls(a7);
}

void MsgrGoZoneRepMsg(CNetMsg &netmsg, int a2, int a3, int a4, int a5, char a6, int a7, int a8, int a9, int a10, float a11, float a12)
{

    netmsg.Init(102);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
    netmsg.__ls(a4);
    netmsg.__ls(a5);
    netmsg.__ls(11);
    netmsg.__ls(a6);
    netmsg.__ls(a7);
    netmsg.__ls(a8);
    netmsg.__ls(a9);
}

void MsgrWhisperRep(CNetMsg &netmsg, int a2, int a3, int a4, int a5, int a6, const char *a7, const char *a8, const char *a9)
{
    netmsg.Init(102);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
    netmsg.__ls(a4);
    netmsg.__ls(a5);
    netmsg.__ls(1);
    netmsg.__ls(a6);
    netmsg.__ls(a7);
    netmsg.__ls(a8);
    netmsg.__ls(a9);
}

void MsgrLogoutRepMsg(CNetMsg &netmsg, int a2, int a3, int a4, int a5, char a6, const char *a7)
{
    netmsg.Init(102);
    netmsg.__ls(a2);
    netmsg.__ls(a3);
    netmsg.__ls(a4);
    netmsg.__ls(a5);
    netmsg.__ls(9);
    netmsg.__ls(a6);
    netmsg.__ls(a7);
}
