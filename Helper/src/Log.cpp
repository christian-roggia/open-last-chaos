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

#include "Log.hpp"

CLogBuffer g_dblogbuffer;
CLogBuffer g_gamelogbuffer;

CLogBuffer &end(CLogBuffer &log_buffer)
{
    g_log.Write(log_buffer.Get());
    return log_buffer;
}
CLogBuffer &init(CLogBuffer &log_buffer)
{
    log_buffer.Init();
    return log_buffer;
}

void CLogBuffer::__ls(CLogHeader const &log_header)
{
    this->__ls(init);
    long lh_type = log_header.p_type;

    if(lh_type == 1 )
    {
        this->__ls(log_header.p_header1);
        this->__ls(" > ");
        this->__ls(log_header.p_header3);
        this->__ls(" : ");
    }
    else
    {
        if(lh_type > 1)
        {
            if(lh_type == 2)
            {
                this->__ls(log_header.p_header1);
                this->__ls(" > ");
                this->__ls(log_header.p_header2);
                this->__ls(" : ");
                this->__ls(log_header.p_header3);
                this->__ls(" : ");
            }
        }
        else
        {
            if(!lh_type)
            {
                this->__ls(log_header.p_header1);
                this->__ls(" > ");
            }
        }
    }
}

void CLogBuffer::appendLog(char const *log)
{
    if(strlen(log) + strlen(this->p_log) > 0x27FF)
    {
        if(strlen(this->p_log) + 3 <= 0x27FF)
            strcat(this->p_log, "N/A");
    }
    else
    {
        strcat(this->p_log, log);
    }
}

/* ------------------------------------------------------------------------------------------------- */

CLogFile g_log;
long force_to_data = -1; // unknown

CLogFile::CLogFile(void)
{
    this->p_log_file = 0;
    this->p_log_path = 0;
}

void CLogFile::Close(void)
{
    if (this->p_log_file)
    {
        if (this->p_log_file != stdout)
            fclose(this->p_log_file);
    }

    this->p_log_file = 0;
}

void CLogFile::InitLogFile(char const *init_log)
{
    struct tm *local_time;
    time_t timer;
    char secure_path[256];

    if(!this->p_log_path)
    {
        this->p_log_path = (char *)malloc(100);
        strcpy(this->p_log_path, init_log);
    }

    time(&timer);
    local_time = localtime(&timer);
    this->Close();
    sprintf((char *)secure_path, "LogFiles/Log %s %d_%d_%d.log", this->p_log_path, local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year +1900);

    /*strcpy(&dest, "../LogFiles/Log");
    IntCat0(&dest, local_time->tm_year % 10, 2, 0);
    strcat(&dest, this->p_log_path);
    IntCat0(&dest, local_time->tm_mon + 1, 2, 0);
    IntCat0(&dest, local_time->tm_mday, 2, 0);*/

    this->p_log_file = fopen(secure_path, "a+");

    if (!this->p_log_file)
        this->p_log_file = stdout;
}

void CLogFile::InitLogFile(int a2, int a3, int a4)
{
    char init_log[100];

    memset(init_log, 0, 100);
    sprintf(init_log, "%d%d%d", a2, a3, a4);
    /*IntCat0(init_log, a2, 2, 0);
    IntCat0(init_log, a3, 2, 0);
    IntCat0(init_log, a4, 2, 0);*/

    this->InitLogFile(init_log);
}

void CLogFile::Write(CLogBuffer &log_buffer)
{
    this->Write(log_buffer.Get());
    log_buffer.Init();
}

void CLogFile::Write(char const *log_to_write)
{
    char log[0x2800];
    //char date[0x2C];
    time_t timer;
    struct tm *l_time;
    //int v6 = 0; // static ???

    time(&timer);
    l_time = localtime(&timer);

    memset(log, 0, 0x2800);
    //memcpy(date, l_time, 0x2C);

    sprintf(log, "%d/%d/%d : %d:%d:%d :: %s\n", l_time->tm_mon + 1, l_time->tm_mday, l_time->tm_year + 1900, l_time->tm_hour, l_time->tm_min, l_time->tm_sec, log_to_write);


    /*IntCat0(&v4, v12 + 1900, 4, 0);
    strcat(&v4, L"/ :");
    IntCat0(&v4, v11 + 1, 2, 0);
    strcat(&v4, L"/ :");
    IntCat0(&v4, v10, 2, 0);
    strcat(&v4, " ");
    IntCat0(&v4, v9, 2, 0);
    strcat(&v4, ":");
    IntCat0(&v4, v8, 2, 0);
    strcat(&v4, ":");
    IntCat0(&v4, date, 2, 0);
    StrCat(&v4, "::");
    StrCat(&v4, log_to_write);*/

    if(force_to_data == -1)
        force_to_data = l_time->tm_year + 1900;

    if(force_to_data != l_time->tm_year + 1900)
        this->InitLogFile("UC");

    if(*log)
        fwrite(log, 1, strlen(log), this->p_log_file);
    //v6 += strlen(log) + 1; <--- no-sense

    fflush(this->p_log_file);
}

/* ------------------------------------------------------------------------------------------------- */

CLogHeader::CLogHeader(char const *h1, char const *h3)
{
    this->p_type = 1;
    this->p_header1 = h1;
    this->p_header2 = 0;
    this->p_header3 = h3;
}

CLogHeader::CLogHeader(char const *h1)
{
    this->p_type = 0;
    this->p_header1 = h1;
    this->p_header2 = 0;
    this->p_header3 = 0;
}

CLogHeader init(char const *h1, char const *h3)
{
    return CLogHeader(h1, h3);
}
CLogHeader init(char const *h1)
{
    return CLogHeader(h1);
}
