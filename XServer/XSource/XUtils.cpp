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

#include "XUtils.h"

char *XUtils::atoip(char *in)
{
    int i = 0, k = 0;
    static char szIP[16];
	
	if(in == NULL) return 0;

    while(1)
    {
        if(in[i] == '\0' || k == 16) break;
        if((in[i] >= '0' && in[i] <= '9') || in[i] == '.') szIP[k++] = in[i];

        i++;
    }

    szIP[k] = '\0';

    return szIP;
}

char *XUtils::strcln(char *in)
{
	int i = 0, k = 0;
    static char szString[1024];
	
	if(in == NULL) return 0;

    while(1)
    {
        if(in[i] == '\0' || k == 1024) break;
        if(in[i] != '\r' && in[i] != '\n' && in[i] != '\t' && in[i] != ' ') szString[k++] = in[i];

        i++;
    }

    szString[k] = '\0';

    return szString;
}

long long XUtils::ntohll(long long __hostlong)
{
    char iTmpByte[8];

    iTmpByte[0] = ((__hostlong >> 56) & 0xFF);
    iTmpByte[1] = ((__hostlong >> 48) & 0xFF);
    iTmpByte[2] = ((__hostlong >> 40) & 0xFF);
    iTmpByte[3] = ((__hostlong >> 32) & 0xFF);
    iTmpByte[4] = ((__hostlong >> 24) & 0xFF);
    iTmpByte[5] = ((__hostlong >> 16) & 0xFF);
    iTmpByte[6] = ((__hostlong >> 8 ) & 0xFF);
    iTmpByte[7] = ((__hostlong >> 0 ) & 0xFF);

    return *(long long *)iTmpByte;
}

long long XUtils::htonll(long long __hostlong)
{
    char iTmpByte[8];

    iTmpByte[0] = ((__hostlong >> 56) & 0xFF);
    iTmpByte[1] = ((__hostlong >> 48) & 0xFF);
    iTmpByte[2] = ((__hostlong >> 40) & 0xFF);
    iTmpByte[3] = ((__hostlong >> 32) & 0xFF);
    iTmpByte[4] = ((__hostlong >> 24) & 0xFF);
    iTmpByte[5] = ((__hostlong >> 16) & 0xFF);
    iTmpByte[6] = ((__hostlong >> 8 ) & 0xFF);
    iTmpByte[7] = ((__hostlong >> 0 ) & 0xFF);

    return *(long long *)iTmpByte;
}

bool XUtils::is_number(char *szString)
{
	if(strlen(szString) <= 0 || szString == NULL) return false;
	
	for(int i = 0; i < strlen(szString); i++)
	{
		if(!isdigit(szString[i]) && szString[i] != '.') return false;
	}
	
	return true;
}