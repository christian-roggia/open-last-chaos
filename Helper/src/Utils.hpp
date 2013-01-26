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

#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <malloc.h>
#include <alloca.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

using namespace std;

/********************************************************************************
 * Integers to String functions
 ********************************************************************************/

char *__ltoa(int m_int, char *m_dest);
char *__ltoa(long long m_int64, char *m_dest);
char *__ftoa(float m_float, char *m_dest, int m_digits);

/********************************************************************************
 * Math functions
 ********************************************************************************/

extern uint32_t a_sin[360];
extern uint32_t a_cos[360];

void MakeMath(void);
long double get_sin(float RAD);
long double get_cos(float RAD);

/********************************************************************************
 * Time functions
 ********************************************************************************/

extern timeval g_timeout;

extern int GetTimeofDay(struct timeval *tv, struct timezone *tz);
extern void TimeDiff(timeval *m_time1, timeval *m_time2, timeval *m_time3);
extern void TimeAdd(timeval *m_time1, timeval *m_time2, timeval *m_time3);

/********************************************************************************
 * ETC Functions
 ********************************************************************************/

long double GetDistance(float x1, float x2, float y1, float y2, float z1, float z2);

/********************************************************************************
 * String Functions
 ********************************************************************************/

char *SkipSpaces(char *m_string);
char *RemoveTailSpaces(char *m_string);
char *TrimString(char *m_string);
char *AnyOneArg(char *m_string, char *m_args, bool m_check);
char *StrDup(char const *m_string);
char *StrCat(char *m_string1, char const *m_string2);
bool strinc(char *m_string, const char *m_to_find);

/********************************************************************************
 * IP banned
 ********************************************************************************/

extern long bannedIPList1[64][2];
extern long bannedIPList2[2][3];
extern long bannedIPList3[183][3];
extern long bannedIPList4[183];
extern long bannedIPList5[17][2];
extern long bannedIPList6[17];

/********************************************************************************
 * IP Functions
 ********************************************************************************/

char *DAnyOneArg(char *m_full, char *m_part);
void IPtoi(char *m_ip, int *m_addr1, int *m_addr2, int *m_addr3, int *m_addr4);
bool CheckIP(char *m_ip);

/********************************************************************************
 * Simple XOR Encryption
 ********************************************************************************/

extern char key[4];
char *DecryptMem(char *memory, long len);

/********************************************************************************
 * Inverse Bytes Functions
 ********************************************************************************/

class CMutex;
class CMutexObject;

class CMutexObject
{
protected:
    pthread_mutex_t mutex; // + 0
    bool unk;
public:
    CMutexObject(void)
    {
        this->unk = pthread_mutex_init(&this->mutex, 0) == 0;
    }
    ~CMutexObject()
    {
        if(!this->unk)
        {
            this->Unlock();
            pthread_mutex_destroy(&this->mutex);
        }
    }

    long Lock(void)
    {
        return pthread_mutex_lock(&this->mutex);
    }
    long Try(void)
    {
        return pthread_mutex_trylock(&this->mutex);
    }
    long Unlock(void)
    {
        return pthread_mutex_unlock(&this->mutex);
    }
};

class CMutex
{
private:
    CMutexObject *p_mutex_object;   // + 0
    long p_mutex_state;             // + 4
public:
    CMutex(CMutexObject *mutex_object, bool lock)
    {
        this->p_mutex_object = mutex_object;
        this->p_mutex_state = lock ? this->p_mutex_object->Lock() : this->p_mutex_object->Try();
    }

    ~CMutex()
    {
        if (!this->p_mutex_state)
            this->p_mutex_object->Unlock();
    }
};


#endif
