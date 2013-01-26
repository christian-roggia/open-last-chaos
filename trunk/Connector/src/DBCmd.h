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

#ifndef DBCMD_H
#define DBCMD_H

#include "Utils.h"
#include <mysql/mysql.h>

/**********************************************************************
NOTE: bool CDBCmd::GetRec(int m_field, char *m_value, bool m_unk);
- Problems with _ctype_b

NOTE: DWORD at +4124
- Virtual table for run-time errors
**********************************************************************/

class CDBCmd {
public:
    MYSQL *MySQL;                       // +0
    my_ulonglong AffectedRows;          // +4
    MYSQL_RES *Resources;               // +8
    MYSQL_ROW Rows;                     // +12
    MYSQL_FIELD *Fields;                // +16
    unsigned long FieldsCount;          // +20
    char Query[4096];                   // +24
    int QuerySize;                      // +4120
public:
    CDBCmd(void);
    ~CDBCmd();

    void Init(st_mysql *);
    bool Open(void);
    void Close(void);
    bool MoveFirst(void);
    bool MoveNext(void);
    void SetQuery(char const *);
    bool Update(void);

    bool GetRec(char const *m_field, int &m_value)                  { return this->GetRec(this->FindField(m_field), m_value); }
    bool GetRec(char const *m_field, unsigned int &m_value)         { return this->GetRec(this->FindField(m_field), m_value); }
    bool GetRec(char const *m_field, short &m_value)                { return this->GetRec(this->FindField(m_field), m_value); }
    bool GetRec(char const *m_field, unsigned short &m_value)       { return this->GetRec(this->FindField(m_field), m_value); }
    bool GetRec(char const *m_field, char &m_value)                 { return this->GetRec(this->FindField(m_field), m_value); }
    bool GetRec(char const *m_field, unsigned char &m_value)        { return this->GetRec(this->FindField(m_field), m_value); }
    bool GetRec(char const *m_field, char *m_value, bool m_unk)     { return this->GetRec(this->FindField(m_field), m_value, m_unk); }
    bool GetRec(char const *m_field, float &m_value)                { return this->GetRec(this->FindField(m_field), m_value); }
    bool GetRec(char const *m_field, long long &m_value)            { return this->GetRec(this->FindField(m_field), m_value); }

    bool GetRec(int m_field, int &m_value);
    bool GetRec(int m_field, unsigned int &m_value);
    bool GetRec(int m_field, short &m_value);
    bool GetRec(int m_field, unsigned short &m_value);
    bool GetRec(int m_field, char &m_value);
    bool GetRec(int m_field, unsigned char &m_value);
    bool GetRec(int m_field, char *m_value, bool m_unk);
    bool GetRec(int m_field, float &m_value);
    bool GetRec(int m_field, long long &m_value);

    const char *GetRec(char const *m_field)  { return this->GetRec(this->FindField(m_field)); }
    const char *GetRec(int m_field)          { return this->Resources && m_field >= 0 && m_field < (signed long)this->FieldsCount ? this->Rows[m_field] : 0; }

    int FindField(char const *p_fields_to_find);

    int BeginTrans(void)            { return mysql_real_query(this->MySQL, "BEGIN", 5); }
    int Commit(void)                { return mysql_real_query(this->MySQL, "COMMIT", 6); }
    int Rollback(void)              { return mysql_real_query(this->MySQL, "ROLLBACK", 8); }
    const char *ErrorString(void)   { return mysql_error(this->MySQL); }
    int insertid(void)              { return mysql_insert_id(this->MySQL); }
};

#endif
