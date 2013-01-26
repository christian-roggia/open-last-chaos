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

#ifndef __DBCMD
#define __DBCMD

#include "common.hpp"
#include <mysql/mysql.h>

class CDBCmd
{
public:
    CDBCmd();
    ~CDBCmd();
    void Init(st_mysql *a2);
    char Open();
    void Close();
    bool MoveFirst();
    bool MoveNext();
    void SetQuery(const char *s);
    unsigned __int8 Update();
    __int8 GetRec(const char *s1, int *a3);
    __int8 GetRec(const char *s1, unsigned int *a3);
    __int8 GetRec(const char *s1, __int16 *a3);
    __int8 GetRec(const char *s1, unsigned __int16 *a3);
    __int8 GetRec(const char *s1, char *a3);
    __int8 GetRec(const char *s1, unsigned __int8 *a3);
    __int8 GetRec(const char *s1, char *s, bool a4);
    __int8 GetRec(const char *s1, float *a3);
    __int8 GetRec(const char *s1, __int64 *a3);
    __int8 GetRec(int a2, int *a3);
    __int8 GetRec(int a2, unsigned int *a3);
    __int8 GetRec(int a2, __int16 *a3);
    __int8 GetRec(int a2, unsigned __int16 *a3);
    __int8 GetRec(int a2, char *a3);
    __int8 GetRec(int a2, unsigned __int8 *a3);
    __int8 GetRec(int field, char *s, bool a4);
    __int8 GetRec(int a2, float *a3);
    __int8 GetRec(int a2, __int64 *a3);
    const char *GetRec(const char *s1);
    const char *GetRec(int field);
    int FindField(const char *s1);
    void BeginTrans();
    void Commit();
    void Rollback();
    void ErrorString();
    my_ulonglong insertid();
//private:

    MYSQL *Mysql;
    my_ulonglong NumRows;
    MYSQL_RES *Result;
    MYSQL_ROW Row;
    MYSQL_FIELD *Fields;
    int NumFields;
    char Query[4096];
    int QueryLen;
//  _DWORD dword101C;
};

#endif

extern st_mysql g_mysql;
