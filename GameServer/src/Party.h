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

#ifndef PARTY_H
#define PARTY_H

#include "NetMsg.h"
#include "Random.h"

class CPC;

class CParty;

class CParty {
public:
    char Unk0; // PartyType
    int  Unk4;
    CPC *Unk8[8];
    CPC *Unk40; // Request
public:
    CParty(char a2, CPC *a3, CPC *a4);
    ~CParty();

    int Add(CPC *a2);
    bool Del(CPC *a2);
    int Allow(void);
    int Request(CPC *a2);
    int Find(CPC *a2);
    int FindByIndex(int a2);
    bool Reject(void);
    void End(void);
    CPC *GetRandomParty(int *a2);
    void SendToInvisibleMember(CNetMsg &a2, CPC *a3);
    void SendAll(CNetMsg &a2, CPC *a3, bool a4);
    CPC *GetMember(int a2);
    char GetPartyType(void);
    CPC *GetRequest(void);
};

#endif // PARTY_H
