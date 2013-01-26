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

#include "XConfig.h"

bool config_init(void)
{
    char szLine[1024], *szSetting, *szValue;
    FILE *FSettings = fopen("CONFIG", "r");

    if(FSettings == NULL) return false;

    while(fgets(szLine, 1024, FSettings))
    {
        szSetting = strcln(strtok(szLine, " \t"));
        szValue   = strcln(strtok(NULL, " \t"));

        if(!szSetting || !szValue)
            continue;

        if(!strcasecmp(szSetting, "BIND_PORT"))
        {
            g_mother_port = atoi(szValue);
            continue;
        }

        if(!strcasecmp(szSetting, "BIND_IP"))
        {
            strncpy(g_mother_ip, atoip(szValue), 16);
            continue;
        }

        if(!strcasecmp(szSetting, "AUTH_SERVER"))
        {
            g_auth_server = strcmp(szValue, "1") == 0;
            continue;
        }
    }

    fclose(FSettings);

    return true;
}
