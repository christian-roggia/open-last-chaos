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

#include "Utils.hpp"

/********************************************************************************
 * Integers to String functions
 ********************************************************************************/

/*char *__ltoa(int m_int, char *m_dest)
{
  char *result; // eax@4
  signed int v3; // [sp+40h] [bp-88h]@1
  int v4; // [sp+44h] [bp-84h]@1
  char v5[128]; // [sp+48h] [bp-80h]@8

  *dest = 0;
  v4 = 0;
  v3 = 0;
  if(a1 < 0)
  {
    strcpy(dest, L"-0.");
    a1 = -a1;
    v3 = 1;
  }
  if(a1)
  {
    while(a1)
    {
      if(a1 % 10 > 9 || a1 % 10 < 0)
        v5[v4++] = 48;
      else
        v5[v4++] = a1 % 10 + 48;
      a1 /= 10;
    }
    while(v4)
    {
      --v4;
      dest[v3++] = v5[v4];
    }
    dest[v3] = 0;
    result = dest;
  }
  else
  {
    strcpy(dest, L"");
    result = dest;
  }
  return result;
}

char *__ltoa(long long m_int64, char *m_dest)
{
  char *result; // eax@4
  signed __int64 v3; // [sp+34h] [bp-94h]@6
  signed int v4; // [sp+40h] [bp-88h]@1
  int v5; // [sp+44h] [bp-84h]@1
  char v6[128]; // [sp+48h] [bp-80h]@8

  *dest = 0;
  v5 = 0;
  v4 = 0;
  if(SHIDWORD(a1) < 0)
  {
    strcpy(dest, L"-0.");
    a1 = -a1;
    v4 = 1;
  }
  if(a1)
  {
    while(a1)
    {
      v3 = a1 % 10;
      if(_cmpdi2(v3, SHIDWORD(v3), 9u, 0) > 1 || _cmpdi2(v3, SHIDWORD(v3), 0, 0) < 1)
        v6[v5++] = 48;
      else
        v6[v5++] = (unsigned __int64)(a1 % 10) + 48;
      a1 /= 10LL;
    }
    while(v5)
    {
      --v5;
      dest[v4++] = v6[v5];
    }
    dest[v4] = 0;
    result = dest;
  }
  else
  {
    strcpy(dest, L"");
    result = dest;
  }
  return result;
}

char *__ftoa(float m_float, char *m_dest, int m_digits)
{
  char *result; // eax@5
  char src; // [sp+18h] [bp-80h]@2
  float v5; // [sp+A0h] [bp+8h]@8

  *dest = 0;
  if(a1 >= 0.0)
  {
    __ltoa((signed int)a1, dest);
  }
  else
  {
    a1 = -a1;
    __ltoa((signed int)a1, &src);
    strcpy(dest, L"-0.");
    strcat(dest, &src);
  }
  if(a3 > 0)
  {
    if(a3 > 8)
      a3 = 8;
    v5 = a1 - (long double)(signed int)a1;
    while(a3 > 0)
    {
      v5 = v5 * 10.0;
      --a3;
    }
    __ltoa((signed int)v5, &src);
    strcat(dest, L"0.");
    strcat(dest, &src);
    result = dest;
  }
  else
  {
    result = dest;
  }
  return result;
}*/

/********************************************************************************
 * Math functions
 ********************************************************************************/

uint32_t a_sin[360];
uint32_t a_cos[360];

void MakeMath(void)
{
    for (long i = 0; i <= 359; ++i)
    {
        a_sin[i] = sinf(i / 360.0 * 6.283185482025146);
        a_cos[i] = cosf(i / 360.0 * 6.283185482025146);
    }
}

long double get_sin(float RAD)
{
    long angle = RAD / 6.283185482025146 * 360.0;

    if(angle < 0)
        angle = angle % 360 + 360;

    if(angle > 359)
        angle %= 360;

    return a_sin[angle];
}

long double get_cos(float RAD)
{
    long angle = RAD / 6.283185482025146 * 360.0;

    if(angle < 0)
        angle = angle % 360 + 360;

    if(angle > 359)
        angle %= 360;

    return a_cos[angle];
}

/********************************************************************************
 * Time functions
 ********************************************************************************/

int GetTimeofDay(struct timeval *tv, struct timezone *tz)
{
    return gettimeofday(tv, tz);
}

void TimeDiff(timeval *m_time1, timeval *m_time2, timeval *m_time3)
{
    if(m_time2->tv_sec >= m_time3->tv_sec)
    {
        if(m_time2->tv_sec == m_time3->tv_sec)
        {
            if(m_time2->tv_usec >= m_time3->tv_usec)
            {
                m_time1->tv_sec = 0;
                m_time1->tv_usec = m_time2->tv_usec - m_time3->tv_usec;
            }
            else
            {
                m_time1->tv_sec = g_timeout.tv_sec;
                m_time1->tv_usec = g_timeout.tv_usec;
            }
        }
        else
        {
            m_time1->tv_sec = m_time2->tv_sec - m_time3->tv_sec;
            if(m_time2->tv_usec >= m_time3->tv_usec)
            {
                m_time1->tv_usec = m_time2->tv_usec - m_time3->tv_usec;
            }
            else
            {
                m_time1->tv_usec = m_time2->tv_usec - (m_time3->tv_usec - 1000000);
                --m_time1->tv_sec;
            }
        }
    }
    else
    {
        m_time1->tv_sec = g_timeout.tv_sec;
        m_time1->tv_usec = g_timeout.tv_usec;
    }
}

void TimeAdd(timeval *m_time1, timeval *m_time2, timeval *m_time3)
{
    m_time1->tv_sec = m_time3->tv_sec + m_time2->tv_sec;
    m_time1->tv_usec = m_time3->tv_usec + m_time2->tv_usec;

    while(1)
    {
        if(m_time1->tv_usec <= 999999)
            break;

        m_time1->tv_usec -= 1000000;
        ++m_time1->tv_sec;
    }
}

/********************************************************************************
 * ETC Functions
 ********************************************************************************/

long double GetDistance(float x1, float x2, float y1, float y2, float z1, float z2)
{
  long double m_x, m_y, m_z;
  float x, y, z;

  m_x = x1 - x2;
  if(x1 - x2 < 0.0)
    m_x = -m_x;

  m_y = y1 - y2;
  if(y1 - y2 < 0.0)
    m_y = -m_y;

  m_z = z1 - z2;
  if(z1 - z2 < 0.0)
    m_z = -m_z;

  x = m_x;
  y = m_y;
  z = m_z;

  return (float)sqrt(x * x + y * y + z * z);
}

/********************************************************************************
 * String functions
 ********************************************************************************/

char *SkipSpaces(char *m_string)
{
    while(m_string && *m_string && (*m_string == ' ' || *m_string > 8 && *m_string <= 13))
        ++m_string;

    return m_string;
}

char *RemoveTailSpaces(char *m_string)
{
    for(long i = strlen(m_string) - 1; i >= 0 && (m_string[i] == ' ' || m_string[i] > 8 && m_string[i] <= 13); ++i)
        m_string[i] = 0;

    return m_string;
}

char *TrimString(char *m_string)
{
    long i = 0, j = 0, k = strlen(m_string) - 1;;

    for(; m_string[i] == 32; ++i);

    if(i > 0)
    {
        for(; j <= strlen(m_string) - i; ++j)
            m_string[j] = m_string[i + j];

        m_string[j] = 0;
    }

    for(; (signed int)k > 0 && m_string[k] == 32; --k);

    m_string[k + 1] = 0;
    return m_string;
}

char *AnyOneArg(char *m_string, char *m_args, bool m_check)
{
    char *i;

    for(i = SkipSpaces(m_string); i && *i && *i != ' ' && (*i <= 8 || *i > 13); ++i)
    {
        if(m_check)
            *m_args++ = (*i <= 64 || *i > 90) ? *i : *i + 32;
        else
            *m_args++ = *i;
    }

    m_args[0] = 0;
    return i;
}

char *StrDup(char const *m_string)
{
    char *m_new_string = (char *)malloc(strlen(m_string) + 1);

    return strcpy(m_new_string, m_string);
}

char *StrCat(char *m_string1, char const *m_string2)
{
    strcat(m_string1, " ");
    strcat(m_string1, m_string2);

    return m_string1;
}

/*char *IntCat(char *,int,bool)
{
  char *v4; // eax@3
  char v5; // [sp+8h] [bp-80h]@3

  if(a3)
    strcat(dest, " ");
  v4 = __ltoa(a2, &v5);
  strcat(dest, v4);
  return dest;
}

char *IntCat(char *,long long,bool)
{
  char *v4; // eax@3
  char v5; // [sp+8h] [bp-80h]@3

  if(a3)
    strcat(dest, " ");
  v4 = __ltoa(a2, &v5);
  strcat(dest, v4);
  return dest;
}

char *IntCat0(char *,int,int,bool)
{
  char *v4; // eax@1
  int i; // [sp+Ch] [bp-8Ch]@4
  size_t v7; // [sp+10h] [bp-88h]@1
  size_t v8; // [sp+14h] [bp-84h]@1
  char src; // [sp+18h] [bp-80h]@1
  int v10; // [sp+A8h] [bp+10h]@4

  v4 = __ltoa(a2, &src);
  v8 = strlen(v4);
  v7 = strlen(dest);
  if(a4)
    strcat((char *)dest, " ");
  if(a3 > (signed int)v8)
  {
    v10 = a3 - v8;
    for(i = v7; i < (signed int)(v7 + v10); ++i)
    {
      dest[i] = 48;
      dest[i + 1] = 0;
    }
  }
  strcat((char *)dest, &src);
  return (char *)dest;
}

char *IntCat0(char *,long long,int,bool)
{
  char *v4; // eax@1
  int i; // [sp+Ch] [bp-8Ch]@4
  size_t v7; // [sp+10h] [bp-88h]@1
  size_t v8; // [sp+14h] [bp-84h]@1
  char src; // [sp+18h] [bp-80h]@1
  int v10; // [sp+ACh] [bp+14h]@4

  v4 = __ltoa(a2, &src);
  v8 = strlen(v4);
  v7 = strlen(dest);
  if(a4)
    strcat((char *)dest, " ");
  if(a3 > (signed int)v8)
  {
    v10 = a3 - v8;
    for(i = v7; i < (signed int)(v7 + v10); ++i)
    {
      dest[i] = 48;
      dest[i + 1] = 0;
    }
  }
  strcat((char *)dest, &src);
  return (char *)dest;
}

char *FloatCat(char *m_string, float m_float, int m_digits, bool m_space)
{
    char *v5;
    char v6; // [sp+8h] [bp-80h]@3

    if(m_space)
        strcat(m_string, " ");

    v5 = __ftoa(m_float, &v6, m_digits);
    strcat(m_string, v5);

    return m_string;
}*/

bool strinc(char *m_string, const char *m_to_find)
{
    size_t m_string_len = strlen(m_string);
    size_t m_to_find_len = strlen(m_to_find);

    if(m_string_len >= m_to_find_len)
    {
        for(long i = 0; strncmp(&m_string[i], m_to_find, m_to_find_len); ++i)
        {
            if(i > m_string_len - m_to_find_len)
                return false;
        }

        return true;
    }

    return false;
}

/********************************************************************************
 * IP banned
 ********************************************************************************
 ** Taiwan Cable Modem Service Provider
 ********************************************************************************/

long bannedIPList1[64][2] = {{222, 250}, {210, 85}, {218, 184}, {218, 35}, {218, 34}, {210, 58}, {61, 20}, {163, 29},
                             {210, 69}, {211, 23}, {210, 65}, {203, 69}, {61, 216}, {211, 20}, {203, 75}, {60, 248},
                             {61, 217}, {211, 22}, {211, 21}, {210, 61}, {203, 74}, {203, 66}, {220, 229}, {218, 32},
                             {61, 66}, {220, 228}, {219, 80}, {219, 81}, {61, 30}, {61, 31}, {221, 169}, {210, 68},
                             {203, 73}, {210, 64}, {203, 67}, {61, 59}, {210, 66}, {203, 70}, {219, 84}, {219, 85},
                             {61, 62}, {140, 135}, {140, 132}, {140, 129}, {140, 113}, {140, 110}, {210, 240}, {203, 71},
                             {140, 138}, {140, 133}, {140, 130}, {140, 115}, {140, 111}, {210, 60}, {203, 72}, {203, 68},
                             {140, 114}, {140, 134}, {140, 131}, {140, 128}, {140, 112}, {140, 109}, {210, 70}, {203, 64}};


/********************************************************************************
 ** 202.3.129.XXX = China Telecom
 ** 203.119.3.XXX = Taiwan Network Information Center
 ********************************************************************************/

long bannedIPList2[2][3] = {{202, 3, 129}, {203, 119, 3}};

/********************************************************************************
 ** Taiwan IPs
 ********************************************************************************/

long bannedIPList3[183][3] = {{202, 8, 14}, {202, 5, 4}, {202, 6, 104}, {202, 5, 12},
                              {202, 5, 8}, {210, 62, 248}, {210, 67, 248}, {210, 62, 240},
                              {211, 79, 192}, {61, 64, 32}, {61, 57, 240}, {61, 57, 192},
                              {61, 67, 112}, {61, 56, 48}, {61, 61, 192}, {61, 57, 208},
                              {61, 60, 240}, {61, 58, 48}, {61, 58, 16}, {211, 79, 96},
                              {211, 78, 80}, {61, 56, 64}, {61, 56, 80}, {210, 67, 96},
                              {211, 78, 240}, {202, 168, 192}, {61, 64, 48}, {210, 62, 176},
                              {211, 76, 224}, {211, 76, 96}, {61, 56, 16}, {61, 57, 144},
                              {61, 67, 48}, {61, 56, 0}, {211, 78, 64}, {61, 67, 0},
                              {211, 79, 32}, {211, 79, 208}, {61, 61, 240}, {211, 78, 0},
                              {211, 78, 16}, {61, 57, 160}, {61, 57, 176}, {61, 60, 208},
                              {61, 58, 0}, {210, 62, 160}, {211, 79, 48}, {61, 56, 96},
                              {211, 76, 160}, {211, 76, 240}, {211, 76, 112}, {61, 58, 112},
                              {61, 57, 224}, {211, 78, 208}, {61, 56, 112}, {61, 60, 192},
                              {211, 76, 144}, {61, 56, 128}, {61, 56, 144}, {211, 78, 192},
                              {211, 76, 128}, {210, 67, 128}, {202, 39, 96}, {210, 67, 0},
                              {210, 67, 112}, {210, 67, 16}, {210, 62, 224}, {211, 78, 224},
                              {61, 58, 80}, {61, 58, 64}, {61, 60, 224}, {210, 67, 192},
                              {210, 67, 208}, {210, 67, 144}, {61, 58, 32}, {61, 56, 32},
                              {61, 58, 96}, {211, 76, 176}, {61, 67, 96}, {210, 63, 224},
                              {210, 63, 192}, {211, 76, 192}, {211, 73, 32}, {61, 63, 128},
                              {61, 60, 128}, {61, 60, 160}, {210, 62, 96}, {210, 241, 160},
                              {211, 73, 128}, {210, 241, 192}, {203, 65, 160}, {210, 62, 0},
                              {210, 62, 32}, {210, 62, 192}, {210, 67, 160}, {61, 57, 32},
                              {211, 79, 128}, {61, 67, 64}, {211, 79, 160}, {61, 60, 0},
                              {203, 65, 128}, {210, 241, 224}, {211, 73, 96}, {61, 63, 0},
                              {211, 78, 32}, {210, 244, 192}, {211, 76, 0}, {210, 244, 224},
                              {211, 73, 64}, {61, 56, 224}, {211, 78, 160}, {61, 56, 192},
                              {211, 78, 128}, {211, 73, 192}, {203, 65, 192}, {211, 73, 224},
                              {210, 67, 64}, {210, 241, 128}, {61, 64, 0}, {211, 73, 0},
                              {211, 79, 64}, {210, 67, 32}, {210, 63, 0}, {210, 63, 32},
                              {210, 62, 64}, {61, 58, 160}, {61, 63, 96}, {61, 67, 16},
                              {61, 58, 128}, {211, 78, 96}, {202, 160, 64}, {210, 243, 96},
                              {210, 63, 160}, {211, 79, 0}, {210, 63, 128}, {61, 57, 0},
                              {210, 243, 64}, {61, 56, 160}, {211, 76, 32}, {61, 61, 208},
                              {203, 65, 224}, {211, 77, 64}, {211, 77, 0}, {210, 241, 0},
                              {210, 241, 64}, {61, 65, 192}, {220, 128, 0}, {61, 63, 32},
                              {210, 63, 64}, {61, 58, 192}, {61, 65, 128}, {61, 64, 64},
                              {210, 243, 0}, {61, 57, 64}, {61, 63, 160}, {61, 60, 32},
                              {221, 120, 0}, {202, 39, 0}, {202, 178, 128}, {222, 251, 0},
                              {211, 77, 128}, {203, 65, 0}, {211, 75, 128}, {210, 59, 128},
                              {211, 72, 128}, {211, 72, 0}, {210, 242, 0}, {210, 71, 128},
                              {202, 39, 128}, {211, 75, 0}, {210, 242, 128}, {61, 67, 128},
                              {61, 65, 0}, {211, 74, 0}, {211, 74, 128}, {210, 244, 0},
                              {210, 243, 128}, {61, 64, 128}, {210, 71, 0}, {210, 59, 0},
                              {210, 17, 0}, {220, 128, 64}, {61, 61, 0}};

long bannedIPList4[183] = {15, 5, 105, 15, 11, 255, 255, 247, 207, 47, 255, 207, 127, 63, 207, 223,
                           255, 63, 31, 111, 95, 79, 95, 111, 255, 207, 63, 191, 239, 111, 31, 159,
                           63, 15, 79, 15, 47, 223, 255, 15, 31, 175, 191, 223, 15, 175, 63, 111,
                           175, 255, 127, 127, 239, 223, 127, 207, 159, 143, 159, 207, 143, 143, 111, 15,
                           127, 31, 239, 239, 95, 79, 239, 207, 223, 159, 47, 47, 111, 191, 111, 255,
                           223, 223, 63, 159, 159, 191, 127, 191, 159, 223, 191, 31, 63, 223, 191, 63,
                           159, 95, 191, 31, 159, 255, 127, 31, 63, 223, 31, 255, 95, 255, 191, 223,
                           159, 223, 223, 255, 95, 159, 31, 31, 95, 63, 31, 63, 95, 191, 127, 47,
                           159, 127, 95, 127, 191, 31, 159, 31, 95, 191, 63, 239, 255, 127, 63, 63,
                           127, 255, 63, 95, 127, 255, 191, 127, 63, 127, 255, 127, 95, 95, 255, 127,
                           255, 127, 255, 255, 255, 127, 127, 255, 255, 127, 255, 255, 127, 127, 255, 127,
                           255, 255, 127, 127, 127, 255, 191};

/********************************************************************************
 ** Other Taiwan IPs
 ********************************************************************************/

long bannedIPList5[17][2] = {{218, 166}, {61, 218}, {218, 164}, {59, 104}, {140, 136}, {163, 30}, {61, 220}, {59, 120},
                             {61, 224}, {218, 160}, {61, 228}, {140, 116}, {59, 112}, {218, 168}, {140, 120}, {220, 129},
                             {163, 13}};

long bannedIPList6[17] = {167, 219, 165, 105, 137, 32, 223, 123, 227, 163, 231, 119, 119, 175, 127, 143, 28};

/********************************************************************************
 * IP Functions
 ********************************************************************************/

char *DAnyOneArg(char *m_full, char *m_part)
{
    while(*m_full && *m_full != '.')
        *m_part++ = *m_full++;

    m_part[0] = 0;
    return m_full + 1;
}

void IPtoi(char *m_ip, int *m_addr1, int *m_addr2, int *m_addr3, int *m_addr4)
{
  char m_arg[12];
  char *m_temp_ip = m_ip;

  m_temp_ip = DAnyOneArg(m_ip, m_arg);
  *m_addr1 = atoi(m_arg);
  m_temp_ip = DAnyOneArg(m_temp_ip, m_arg);
  *m_addr2 = atoi(m_arg);
  m_temp_ip = DAnyOneArg(m_temp_ip, m_arg);
  *m_addr3 = atoi(m_arg);
  *m_addr4 = atoi(m_temp_ip);
}

bool CheckIP(char *m_ip)
{
    int ip1, ip2, ip3, ip4;
    char m_ip_copy[20];
    long b1[64][2], b2[2][3], b3[183][3], b4[183], b5[17][2], b6[17];

    memcpy(b1, bannedIPList1, 512);
    memcpy(b2, bannedIPList2, 24);
    memcpy(b3, bannedIPList3, 2196);
    memcpy(b4, bannedIPList4, 732);
    memcpy(b5, bannedIPList5, 136);
    memcpy(b6, bannedIPList6, 68);
    strcpy(m_ip_copy, m_ip);

    IPtoi(m_ip_copy, &ip1, &ip2, &ip3, &ip4);

    if(ip1 == 211 && ip2 == 181 && ip3 == 248)
        return true;

    if(ip1 == 220 && ip2 == 130 && ip3 == 35)
        return true;

    for(long i = 0; i <= 16; ++i)
    {
        if(b5[i][0] == ip1 && b5[i][1] <= ip2 && ip2 <= b6[i])
            return false;
    }

    for(long j = 0; j <= 182; ++j)
    {
        if(b3[j][0] == ip1 && b3[j][1] == ip2 && b3[j][2] <= ip3 && ip3 <= b4[j])
            return false;
    }

    for(long k = 0; k <= 1; ++k)
    {
        if(b2[k][0] == ip1 && b2[k][1] == ip2 && b2[k][2] == ip3)
            return false;
    }

    for(long l = 0; l <= 63; ++l)
    {
        if(b1[l][0] == ip1 && b1[l][1] == ip2)
            return false;
    }

    return true;
}

/********************************************************************************
 * Simple XOR Encryption
 ********************************************************************************
 ** key = nako ---> 6E 61 6B 6F
 ** It is the name of the company that had developed Last Chaos (Nako Interactive)
 ** More Info: http://www.nako.co.kr
 ********************************************************************************/

char key[4] = {0x6E, 0x61, 0x6B, 0x6F};

char *DecryptMem(char *memory, long len)
{
    char delta = -128;

    for (long i = 0; i < len; i++)
    {
        memory[i] ^= key[i % 4];
        memory[i] -= delta;
        delta += memory[i];
    }

    return memory;
}

/********************************************************************************
 * Inverse Bytes Functions
 ********************************************************************************/

/*
__int64 ntohll(long long)
{
  char v1; // ST13_1@1
  char v2; // ST13_1@1
  char v3; // ST13_1@1
  char v4; // ST13_1@1

  v1 = a1;
  LOBYTE(a1) = BYTE7(a1);
  BYTE7(a1) = v1;
  v2 = BYTE1(a1);
  BYTE1(a1) = BYTE6(a1);
  BYTE6(a1) = v2;
  v3 = BYTE2(a1);
  BYTE2(a1) = BYTE5(a1);
  BYTE5(a1) = v3;
  v4 = BYTE3(a1);
  BYTE3(a1) = BYTE4(a1);
  BYTE4(a1) = v4;
  return a1;
}

__int64 htonll(long long)
{
  char v1; // ST13_1@1
  char v2; // ST13_1@1
  char v3; // ST13_1@1
  char v4; // ST13_1@1

  v1 = a1;
  LOBYTE(a1) = BYTE7(a1);
  BYTE7(a1) = v1;
  v2 = BYTE1(a1);
  BYTE1(a1) = BYTE6(a1);
  BYTE6(a1) = v2;
  v3 = BYTE2(a1);
  BYTE2(a1) = BYTE5(a1);
  BYTE5(a1) = v3;
  v4 = BYTE3(a1);
  BYTE3(a1) = BYTE4(a1);
  BYTE4(a1) = v4;
  return a1;
}
*/
