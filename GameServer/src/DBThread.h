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

#ifndef DBTHREAD_H
#define DBTHREAD_H

#include "Descriptor.h"
#include "Mutex.h"

class CCharDBQ;
class CDBThread;

class CCharDBQ {
public:
    CDescriptor *Unk0[100000];
    CMutexObject Unk400000;
    int Unk400028, Unk400032;
public:
    CCharDBQ(void);
    ~CCharDBQ();

    CDescriptor *GetFromQ(void);
    bool AddToQ(CDescriptor *a2);
    void EraseQ(CDescriptor *a2);
    bool IsFull(void);
    bool IsEmpty(void);
};

class CDBThread : public CCharDBQ {
public:
    char Unk400036;
    char Unk400037;
    char Unk400040[5120];
    char Unk405160[4096];
    char Unk409256[512];
public:
    CDBThread(void);
    ~CDBThread();

    bool CreateThread(void);
    static void RunThread(void *a1);

    void Run(void);
    int  PingDB(void);

    bool UpdateChar(CDescriptor *a2);

    bool OnUserDB(CDescriptor *a2);
    bool OnNewCharDB(CDescriptor *a2);
    bool OnDelCharDB(CDescriptor *a2);
    bool OnPlayCharDB(CDescriptor *a2);

    static void BackSlash(char *a1,char const *a2);
    static void GetDateStr(char *a1);
    static void TrimString(char *s);
    static void Wait300Millis(void);
};

#endif // DBTHREAD_H
