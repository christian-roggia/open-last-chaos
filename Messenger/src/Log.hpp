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

class CLogBuffer;
class CLogHeader;
class CLogFile;

#include "common.hpp"
#include "Utils.hpp"

#ifndef LOG_H
#define LOG_H

#include "time.h"

class CLogBuffer {
private:
    char p_log[0x5000];     // In the heap its len is 0x5000 but the appendLog uses only 0x2800 bytes
    char p_temp_buffer[32]; // Added as alternative for the itoa - i64toa - ftoa
public:
    CLogBuffer(void)                                        { this->Init(); }

    void __ls(char const *log)                              { this->appendLog(log); }
    //void __ls(int log)                                      { itoa(log, this->p_temp_buffer, 10); this->appendLog(this->p_temp_buffer); }
    //void __ls(long long log)                                { i64toa(log, this->p_temp_buffer, 10); this->appendLog(this->p_temp_buffer); }
    //void __ls(float log)                                    { ftoa(log, this->p_temp_buffer, 10); this->appendLog(this->p_temp_buffer); }
    void __ls(int log)                                      { sprintf(this->p_temp_buffer, "%d", log); this->appendLog(this->p_temp_buffer); }
    void __ls(long long log)                                { sprintf(this->p_temp_buffer, "%lld", log); this->appendLog(this->p_temp_buffer); }
    void __ls(float log)                                    { sprintf(this->p_temp_buffer, "%f", log); this->appendLog(this->p_temp_buffer); }
    void __ls(CLogBuffer &(*log_func)(CLogBuffer &))        { log_func(*this); }
    void __ls(CLogHeader const &log_header);

    char *Get(void)                                         { return this->p_log; }
    void Init(void)                                         { memset(this->p_log, 0, 0x5000); }
    void appendLog(char const *log);
};

extern CLogBuffer &end(CLogBuffer &log_buffer);
extern CLogBuffer &init(CLogBuffer &log_buffer);

extern CLogBuffer g_dblogbuffer;
extern CLogBuffer g_gamelogbuffer;

/*-----------------------------------------------------------*/

class CLogFile {
private:
    FILE *p_log_file;   // +0
    char *p_log_path;   // +4
public:
    CLogFile(void);
    ~CLogFile() { this->Close(); }

    void Close(void);
    void InitLogFile(char const *init_log);
    void InitLogFile(int a2, int a3, int a4);
    void Write(CLogBuffer &log_buffer);
    void Write(char const *log_to_write);
};

extern long force_to_data; // unknown / no-sense
extern CLogFile g_log;

/*-----------------------------------------------------------*/

class CLogHeader {
public:
    long p_type;           // + 0
    const char *p_header1; // + 4
    const char *p_header2; // + 8
    const char *p_header3; // + 12
public:
    CLogHeader(char const *h1, char const *h3);
    CLogHeader(char const *h1);
};

extern CLogHeader init(char const *h1, char const *h3);
extern CLogHeader init(char const *h1);

#endif // LOG_H
