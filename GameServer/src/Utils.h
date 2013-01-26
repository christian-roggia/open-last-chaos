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

#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <malloc.h>
#include <memory.h>
#include <alloca.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

extern float a_sin[360];
extern float a_cos[360];

void MakeMath(void);
long double get_sin(float RAD);
long double get_cos(float RAD);

/********************************************************************************
 * Time functions
 ********************************************************************************/

extern struct timeval a_NullTime; // a_NullTime

int GetTimeofDay(struct timeval *tv, struct timezone *tz);
void TimeDiff(timeval *m_time1, timeval *m_time2, timeval *m_time3);
void TimeAdd(timeval *m_time1, timeval *m_time2, timeval *m_time3);

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
char *IntCat(char *m_dest, int m_number, bool m_space);
char *IntCat(char *dest, long long a2, bool a3);
char *IntCat0(char *dest, int a2, int a3, bool a4);
char *IntCat0(char *dest, long long a2, int a3, bool a4);
char *FloatCat(char *m_string, float m_float, int m_digits, bool m_space);
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

//long long ntohll(long long a1)

#endif // UTILS_H
