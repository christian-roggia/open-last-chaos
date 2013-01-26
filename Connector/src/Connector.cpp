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
#include "Log.h"

void at_exit_exec(void)
{
    mysql_close(&gserver.UserSQL);
    mysql_close(&gserver.AuthSQL);

    if(game_log)
        fclose(game_log);
}

int main()
{
    if(!gserver.LoadSettingFile())
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("Load Setting File");
        g_gamelogbuffer.__ls(end);
        exit(0);
    }

    sprintf(g_buf, "CS%02d", (int)gserver.Number);
    g_log.InitLogFile(g_buf);

    if(!gserver.ConnectDB())
    {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("Connect DB");
        g_gamelogbuffer.__ls(end);
        exit(0);
    }

    if(gserver.InitGame())
    {
        strcpy(g_buf, "Last Chaos Connector Running... (Language:");
        strcat(g_buf, "Korean)");
        puts(g_buf);
        atexit(at_exit_exec);
        gserver.Run();
        gserver.Close();

        if(gserver.WriteShutDown)
        {
            FILE *m_shut = fopen(".shutdown", "w");
            fclose(m_shut);
        }

        g_gamelogbuffer.__ls(init("SYSTEM"));
        g_gamelogbuffer.__ls("End!");
        g_gamelogbuffer.__ls(end);

        return 1004;
    }

    g_gamelogbuffer.__ls(init("SYS_ERR"));
    g_gamelogbuffer.__ls("Initialize Connector");
    g_gamelogbuffer.__ls(end);

    return 1;
}
