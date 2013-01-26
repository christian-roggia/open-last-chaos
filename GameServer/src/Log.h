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

#ifndef LOG_H
#define LOG_H

#include "time.h"
#include "Utils.h"

class CLogHeader;
class CLogBuffer;
class CLogFile;

class CLogHeader {
public:
    int p_type;            // + 0
    const char *p_header1; // + 4
    const char *p_header2; // + 8
    const char *p_header3; // + 12
public:
    CLogHeader(char const *h1, char const *h2, char const *h3); // ADDED IN GameServer
    CLogHeader(char const *h1, char const *h3);
    CLogHeader(char const *h1);
};

CLogHeader init(char const *h1, char const *h2, char const *h3); // ADDED IN GameServer
CLogHeader init(char const *h1, char const *h3);
CLogHeader init(char const *h1);

class CLogBuffer {
private:
    char p_log[0x2800];
    char p_log_int[0x2800];
public:
    CLogBuffer(void)                                        { this->Init(); }

    void __ls(char const *log)                              { this->appendLog(log); }
    void __ls(int log)                                      { __ltoa(log, this->p_log_int); this->appendLog(this->p_log_int); }
    void __ls(long long log)                                { __ltoa(log, this->p_log_int); this->appendLog(this->p_log_int); }
    void __ls(float log)                                    { __ftoa(log, this->p_log_int, 4); this->appendLog(this->p_log_int); }
    void __ls(CLogBuffer &(*log_func)(CLogBuffer &))        { log_func(*this); }
    void __ls(CLogHeader const &log_header);

    char *Get(void)                                         { return this->p_log; }
    void Init(void)                                         { *this->p_log = 0; }
    void appendLog(char const *log);
};

CLogBuffer &end(CLogBuffer &log_buffer);
CLogBuffer &init(CLogBuffer &log_buffer);
CLogBuffer &delim(CLogBuffer &log_buffer); // ADDED IN GameServer - Connector - ...
CLogBuffer &flush(CLogBuffer &log_buffer); // ADDED IN GameServer - Connector - ...

extern CLogBuffer g_dblogbuffer; // ADDED IN GameServer
extern CLogBuffer g_gamelogbuffer; // ADDED IN GameServer

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
    void Flush(void); // ADDED IN GameServer
};

extern int force_to_data; // unknown / no-sense
extern CLogFile g_log;
extern FILE *game_log;

#endif // LOG_H
