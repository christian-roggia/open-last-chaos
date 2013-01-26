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
    this->p_mysql = 0;
    this->p_fields = 0;
    this->p_mysql_num_fields = 0;
    this->p_affacted_rows = 0;
    this->p_mysql_res = 0;
    this->p_query_size = 0;
}

CDBCmd::~CDBCmd()
{
    this->p_mysql = 0;
    this->p_fields = 0;
    this->p_mysql_num_fields = 0;
    this->p_affacted_rows = 0;
    this->p_mysql_res = 0;
    this->p_query_size = 0;
    this->Close();
}

void CDBCmd::Init(st_mysql *a2)
{
    this->p_mysql = a2;
}

bool CDBCmd::Open(void)
{
    this->Close();
    if(mysql_real_query(this->p_mysql, this->p_query, this->p_query_size) || !(this->p_mysql_res = mysql_store_result(this->p_mysql)))
        return false;
    
    this->p_affacted_rows = mysql_num_rows(this->p_mysql_res);
    this->p_mysql_num_fields = mysql_num_fields(this->p_mysql_res);
    this->p_fields = mysql_fetch_fields(this->p_mysql_res);
    
    return true;
}

void CDBCmd::Close(void)
{
    if(this->p_mysql_res)
    {
        mysql_free_result(this->p_mysql_res);
        this->p_mysql_res = 0;
    }
}

bool CDBCmd::MoveFirst(void)
{
    if(!this->p_mysql_res)
        return false;
    
    mysql_data_seek(this->p_mysql_res, 0);
    this->p_mysql_row = mysql_fetch_row(this->p_mysql_res);
    
    return this->p_mysql_row != 0;
}

bool CDBCmd::MoveNext(void)
{
    if(!this->p_mysql_res)
        return false;
    
    this->p_mysql_row = mysql_fetch_row(this->p_mysql_res);
    
    return this->p_mysql_row != 0;
}

void CDBCmd::SetQuery(char const *query)
{
    strcpy(this->p_query, query);
    this->p_query_size = strlen(query);
}

bool CDBCmd::Update(void)
{
    this->Close();
    if(mysql_real_query(this->p_mysql, this->p_query, this->p_query_size))
        return false;
    
    this->p_affacted_rows = mysql_affected_rows(this->p_mysql);
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

    if(!this->p_fields)
        return -1;

    for(; strcmp(p_fields_to_find, this->p_fields[i].name); ++i)
    {
        if(i >= (signed int)this->p_mysql_num_fields)
            return -1;
    }

    return i;
}
