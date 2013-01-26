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

#include "DBCmd.h"

CDBCmd::CDBCmd(void)
{
    this->MySQL = 0;
    this->Fields = 0;
    this->FieldsCount = 0;
    this->AffectedRows = 0;
    this->Resources = 0;
    this->QuerySize = 0;
}

CDBCmd::~CDBCmd()
{
    this->MySQL = 0;
    this->Fields = 0;
    this->FieldsCount = 0;
    this->AffectedRows = 0;
    this->Resources = 0;
    this->QuerySize = 0;

    this->Close();
}

void CDBCmd::Init(st_mysql *a2)
{
    this->MySQL = a2;
}

bool CDBCmd::Open(void)
{
    this->Close();
    if(mysql_real_query(this->MySQL, this->Query, this->QuerySize) || !(this->Resources = mysql_store_result(this->MySQL)))
        return false;
    
    this->AffectedRows = mysql_num_rows(this->Resources);
    this->FieldsCount  = mysql_num_fields(this->Resources);
    this->Fields       = mysql_fetch_fields(this->Resources);
    
    return true;
}

void CDBCmd::Close(void)
{
    if(this->Resources)
    {
        mysql_free_result(this->Resources);
        this->Resources = 0;
    }
}

bool CDBCmd::MoveFirst(void)
{
    if(!this->Resources)
        return false;
    
        mysql_data_seek(this->Resources, 0);
    this->Rows = mysql_fetch_row(this->Resources);
    
    return this->Rows != 0;
}

bool CDBCmd::MoveNext(void)
{
    if(!this->Resources)
        return false;
    
    this->Rows = mysql_fetch_row(this->Resources);
    
    return this->Rows != 0;
}

void CDBCmd::SetQuery(char const *query)
{
    strcpy(this->Query, query);
    this->QuerySize = strlen(query);
}

bool CDBCmd::Update(void)
{
    this->Close();
    if(mysql_real_query(this->MySQL, this->Query, this->QuerySize))
        return false;
    
    this->AffectedRows = mysql_affected_rows(this->MySQL);
    return true;
}

bool CDBCmd::GetRec(int m_field, int &m_value)
{
    const char *v4;

    v4 = this->GetRec(m_field);
    if(v4)
    {
            m_value = atoi(v4);
            return true;
    }
    
    return false;
}

bool CDBCmd::GetRec(int m_field, unsigned int &m_value)
{
    unsigned int v4 = 0;

    if(this->GetRec(m_field, *(int*)&v4))
    {
                m_value = v4;
        return true;
    }
    
    return false;
}

bool CDBCmd::GetRec(int m_field, short &m_value)
{
    short v4;

    if(this->GetRec(m_field, *(int*)&v4))
    {
                m_value = v4;
        return true;
    }
    
    return false;
}

bool CDBCmd::GetRec(int m_field, unsigned short &m_value)
{
    unsigned short v4;

    if(this->GetRec(m_field, *(int*)&v4))
    {
                m_value = v4;
        return true;
    }
    
    return false;
}

bool CDBCmd::GetRec(int m_field, char &m_value)
{
    char v4;

    if(this->GetRec(m_field, *(int*)&v4))
    {
                m_value = v4;
        return true;
    }
    
    return false;
}

bool CDBCmd::GetRec(int m_field, unsigned char &m_value)
{
    unsigned char v4;

    if(this->GetRec(m_field, *(int*)&v4))
    {
                m_value = v4;
        return true;
    }
    
    return false;
}

bool CDBCmd::GetRec(int m_field, char *m_value, bool m_unk)
{
    const char *v5;
    //char *i;
    const char *v7;

    v7 = this->GetRec(m_field);
    if(v7)
    {
        v5 = v7;

        /* PROBLEMS WITH _ctype_b */
        /*if(m_unk)
        {
            while(*v5 && *(uint16_t *)(_ctype_b[2 * *v5]) & 0x2000)
            ++v5;
        }*/
        
        strcpy(m_value, v5);
        
        /*if(m_unk)
        {
            for(i = *(char **)(m_value + strlen(m_value) - 1); *i > *m_value && *i && *(uint16_t *)(_ctype_b[2 * *i]) & 0x2000; --i);
            i[1] = 0;
        }*/
        
        return true;
    }
    
    return false;
}

bool CDBCmd::GetRec(int m_field, float &m_value)
{
    const char *v4;

    v4 = this->GetRec(m_field);
    if(v4)
    {
        m_value = atof(v4);
        return true;
    }
    
    return false;
}

bool CDBCmd::GetRec(int m_field, long long &m_value)
{
    const char *v4;

    v4 = this->GetRec(m_field);
    if(v4)
    {
        m_value = atoll(v4);
        return true;
    }
    
    return false;
}

int CDBCmd::FindField(char const *p_fields_to_find)
{
    long i = 0;

    if(!this->Fields)
        return -1;

    for(; strcmp(p_fields_to_find, this->Fields[i].name); ++i)
    {
        if(i >= (signed int)this->FieldsCount)
            return -1;
    }

    return i;
}
