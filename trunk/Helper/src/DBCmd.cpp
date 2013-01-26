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

#include "DBCmd.hpp"

st_mysql g_mysql;

CDBCmd::CDBCmd()
{
//  dword101C = force_to_data_0;
  Mysql = 0;
  Fields = 0;
  NumFields = 0;
  NumRows = 0;
  Result = 0;
  Query[0] = 0;
  QueryLen = 0;
}

CDBCmd::~CDBCmd()
{
//  dword101C = force_to_data_0;
  CDBCmd::Close();
  Mysql = 0;
  NumRows = 0;
  Result = 0;
  Fields = 0;
  NumFields = 0;
  QueryLen = 0;
//  if ( a2 & 1 )
//    __builtin_delete(this);
}

void CDBCmd::Init(st_mysql *a2)
{
  Mysql = a2;
}

char CDBCmd::Open()
{
  char result; // al@3
  CDBCmd::Close();
  if ( mysql_real_query(Mysql, Query, QueryLen)
    || (Result = mysql_store_result(Mysql)) == 0 )
  {
    result = 0;
  }
  else
  {
    NumRows = mysql_num_rows(Result);
    NumFields = mysql_num_fields(Result);
    Fields = mysql_fetch_fields(Result);
    result = 1;
  }
  return result;
}

void CDBCmd::Close()
{
  if ( Result )
  {
    mysql_free_result(Result);
    Result = 0;
  }
}

bool CDBCmd::MoveFirst()
{
  bool result; // al@2

  if ( Result )
  {
    mysql_data_seek(Result, 0);
    Row = mysql_fetch_row(Result);
    if ( Row )
      result = 1;
    else
      result = 0;
  }
  else
  {
    result = 0;
  }
  return result;
}

bool CDBCmd::MoveNext()
{
  bool result; // eax@2
  if ( Result )
  {
    Row = mysql_fetch_row(Result);
    if ( Row )
      result = 1;
    else
      result = 0;
  }
  else
  {
    result = 0;
  }
  return result;
}

void CDBCmd::SetQuery(const char *s)
{
  strcpy(Query, s);
  QueryLen = strlen(s);
}

unsigned __int8 CDBCmd::Update()
{
  unsigned __int8 result; // al@2
  CDBCmd::Close();
  if ( mysql_real_query(Mysql, Query, QueryLen) )
  {
    result = 0;
  }
  else
  {
    NumRows = mysql_affected_rows(Mysql);
    result = 1;
  }
  return result;
}

__int8 CDBCmd::GetRec(const char *s1, int *a3)
{
  int v3; // eax@1
  v3 = CDBCmd::FindField(s1);
  return CDBCmd::GetRec(v3, a3);
}

__int8 CDBCmd::GetRec(const char *s1, unsigned int *a3)
{
  int v3; // eax@1
  v3 = CDBCmd::FindField(s1);
  return CDBCmd::GetRec(v3, a3);
}

__int8 CDBCmd::GetRec(const char *s1, __int16 *a3)
{
  int v3; // eax@1
  v3 = CDBCmd::FindField(s1);
  return CDBCmd::GetRec(v3, a3);
}

__int8 CDBCmd::GetRec(const char *s1, unsigned __int16 *a3)
{
  int v3; // eax@1
  v3 = CDBCmd::FindField(s1);
  return CDBCmd::GetRec(v3, a3);
}

__int8 CDBCmd::GetRec(const char *s1, char *a3)
{
  int v3; // eax@1
  v3 = CDBCmd::FindField(s1);
  return CDBCmd::GetRec(v3, a3);
}

__int8 CDBCmd::GetRec(const char *s1, unsigned __int8 *a3)
{
  int v3; // eax@1
  v3 = CDBCmd::FindField(s1);
  return CDBCmd::GetRec(v3, a3);
}

__int8 CDBCmd::GetRec(const char *s1, char *s, bool a4)
{
  int v4; // eax@1
  v4 = CDBCmd::FindField(s1);
  return CDBCmd::GetRec(v4, s, a4);
}

__int8 CDBCmd::GetRec(const char *s1, float *a3)
{
  int v3; // eax@1
  v3 = CDBCmd::FindField(s1);
  return CDBCmd::GetRec(v3, a3);
}

__int8 CDBCmd::GetRec(const char *s1, __int64 *a3)
{
  int v3; // eax@1
  v3 = CDBCmd::FindField(s1);
  return CDBCmd::GetRec(v3, a3);
}

__int8 CDBCmd::GetRec(int a2, int *a3)
{
  __int8 result; // al@2
  const char *nptr; // [sp+1Ch] [bp-4h]@1
  nptr = CDBCmd::GetRec(a2);
  if ( nptr )
  {
    *a3 = atoi(nptr);
    result = 1;
  }
  else
  {
    result = 0;
  }
  return result;
}

__int8 CDBCmd::GetRec(int a2, unsigned int *a3)
{
  __int8 result; // al@2
  int v4; // [sp+18h] [bp-4h]@1
  if ( CDBCmd::GetRec(a2, &v4) )
  {
    *a3 = v4;
    result = 1;
  }
  else
  {
    result = 0;
  }
  return result;
}

__int8 CDBCmd::GetRec(int a2, __int16 *a3)
{
  __int8 result; // al@2
  int v4; // [sp+18h] [bp-4h]@1
  if ( CDBCmd::GetRec(a2, &v4) )
  {
    *a3 = v4;
    result = 1;
  }
  else
  {
    result = 0;
  }
  return result;
}

__int8 CDBCmd::GetRec(int a2, unsigned __int16 *a3)
{
  __int8 result; // al@2
  int v4; // [sp+18h] [bp-4h]@1
  if ( CDBCmd::GetRec(a2, &v4) )
  {
    *a3 = v4;
    result = 1;
  }
  else
  {
    result = 0;
  }
  return result;
}

__int8 CDBCmd::GetRec(int a2, char *a3)
{
  __int8 result; // al@2
  int v4; // [sp+18h] [bp-4h]@1
  if ( CDBCmd::GetRec(a2, &v4) )
  {
    *a3 = v4;
    result = 1;
  }
  else
  {
    result = 0;
  }
  return result;
}

__int8 CDBCmd::GetRec(int a2, unsigned __int8 *a3)
{
  __int8 result; // al@2
  int v4; // [sp+18h] [bp-4h]@1
  if ( CDBCmd::GetRec(a2, &v4) )
  {
    *a3 = v4;
    result = 1;
  }
  else
  {
    result = 0;
  }
  return result;
}

__int8 CDBCmd::GetRec(int field, char *s, bool a4)
{
  __int8 result; // al@2
  const char *src; // [sp+18h] [bp-8h]@3
  char *srca; // [sp+18h] [bp-8h]@9
  const char *v7; // [sp+1Ch] [bp-4h]@1
  v7 = CDBCmd::GetRec(field);
  if ( v7 )
  {
    src = v7;
    if ( a4 )
    {
      while ( *src /*&& *(_WORD *)(_ctype_b + 2 * *src) & 0x2000 */)
        ++src;
    }
    strcpy(s, src);
    if ( a4 )
    {
      for ( srca = &s[strlen(s) - 1]; srca > s /*&& *srca && *(_WORD *)(_ctype_b + 2 * *srca) & 0x2000*/; --srca )
        ;
      srca[1] = 0;
    }
    result = 1;
  }
  else
  {
    result = 0;
  }
  return result;
}

__int8 CDBCmd::GetRec(int a2, float *a3)
{
  __int8 result; // al@2
  const char *nptr; // [sp+1Ch] [bp-4h]@1
  nptr = CDBCmd::GetRec(a2);
  if ( nptr )
  {
    *a3 = atof(nptr);
    result = 1;
  }
  else
  {
    result = 0;
  }
  return result;
}

__int8 CDBCmd::GetRec(int a2, __int64 *a3)
{
  __int8 result; // al@2
  const char *nptr; // [sp+1Ch] [bp-4h]@1
  nptr = CDBCmd::GetRec(a2);
  if ( nptr )
  {
    *a3 = atoll(nptr);
    result = 1;
  }
  else
  {
    result = 0;
  }
  return result;
}

const char *CDBCmd::GetRec(const char *s1)
{
  int v2; // eax@1
  v2 = CDBCmd::FindField(s1);
  return CDBCmd::GetRec(v2);
}

const char *CDBCmd::GetRec(int field)
{
  const char *result; // eax@4
  if ( Result && field >= 0 && field < NumFields )
    result = Row[field];
  else
    result = 0;
  return result;
}

int CDBCmd::FindField(const char *s1)
{
  int result; // eax@2
  int i; // [sp+14h] [bp-4h]@3
  if ( Fields )
  {
    for ( i = 0; i < NumFields; ++i )
    {
      if ( !strcmp(s1, *((const char **)&Fields->name + 10 * i)) )
        return i;
    }
    result = -1;
  }
  else
  {
    result = -1;
  }
  return result;
}

void CDBCmd::BeginTrans()
{
  mysql_real_query(Mysql, "BEGIN", 5u);
}

void CDBCmd::Commit()
{
  mysql_real_query(Mysql, "COMMIT", 6u);
}

void CDBCmd::Rollback()
{
  mysql_real_query(Mysql, "ROLLBACK", 8u);
}

void CDBCmd::ErrorString()
{
  mysql_error(Mysql);
}

my_ulonglong CDBCmd::insertid()
{
  return mysql_insert_id(Mysql);
}
