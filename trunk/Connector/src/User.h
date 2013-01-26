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

#ifndef USER_H
#define USER_H

#include "Descriptor.h"
#include "Log.h"
#include "Utils.h"

class CDescriptor;

class CUser {
public:
        int PortalIndex;                        // +0
        char Username[30];                      // +4
        char Password[30];                      // +34
        int ServerNum, SubServerNum, ZoneNum;   // +64, +68, +72
        int Index;                              // +76
        int Unk80, Timestamp;                   // +80, +84
        CDescriptor *Descriptor;                // +88
        int Unk92;                              // +92
        char Unk96;                             // +96
        int Unk100, Unk104, Unk108, Unk112;     // +100, +104, +108, +112
public:
        CUser(int m_unk1, char const *m_username, int m_unk2, int m_unk3, char const *m_password);
};

class CUserList {
public:
        CUser **Users;          // +0
        long UsersOnline;       // +4
        long UserMaxRange;      // +8
        long *Count[20];        // +12
public:
	CUserList(void);
	~CUserList(void);

        CUser *Add(CUser *m_user);
	bool Remove(CUser *m_user, bool m_delete_istance);
        CUser *Find(char const *m_username);
        CUser *Find(int m_unk);
};

#endif
