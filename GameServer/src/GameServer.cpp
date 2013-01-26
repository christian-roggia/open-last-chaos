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

#include "Server.h"

void at_exit_exec(void)
{
    gserver.DisconnectDB(true);
    g_gamelogbuffer.__ls(flush);
}

int main(void)
{
    char src[20]; // [sp+Ch] [bp-1Ch]@6
    int i; // [sp+20h] [bp-8h]@4
    int v13 = 1004;

    if(!gserver.LoadSettingFile())
    {
        puts("Setting Error!!");
        exit(0);
    }

    for(i = 0; ; ++i)
    {
        if(i < atoi(gserver.Unk36904.Find("Zones", "Count")))
        {
            *src = 0;
            memset(src + 1, 0, 19);
            sprintf(src, "Zone_%d", i);

            if(strcmp(gserver.Unk36904.Find(src, "Remote"), "FALSE"))
                continue;
        }

        break;
    }

    if(i == atoi(gserver.Unk36904.Find("Zones", "Count")))
    {
        i = -1;
    }
    else
    {
        *src = 0;
        memset(src + 1, 0, 19);
        sprintf(src, "Zone_%d", i);

        i = atoi(gserver.Unk36904.Find(src, "No"));
    }

    g_log.InitLogFile(gserver.Unk41004, gserver.Unk41008, i);

    if(!gserver.ConnectDB())
    {
        puts("Cannot Connect DB!!");
        exit(0);
    }

    if(!gserver.LoadSettings())
    {
        puts("Setting Error!!");
        exit(0);
    }

    if(!gserver.CreateDBThread())
        return 1;

    if(!gserver.InitGame())
        return 1;

    gserver.DisconnectDB(false);

    puts("SETTINGS");
    if(gserver.Unk41100) puts(" : Only Local IP");

    puts(" : Old Network Format");
    puts(" : Little Endian");
    puts("Force start zone 0");
    strcpy(g_buf, "LastChaos Running...");
    puts(g_buf);

    atexit(at_exit_exec);
    gserver.Run();
    gserver.Close();

    if(gserver.Unk41054) fclose(fopen(".shutdown", "w"));

    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("End!");
    g_gamelogbuffer.__ls(end);

    return v13;
}
