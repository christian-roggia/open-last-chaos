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

#include "Helper.hpp"

int main(int argc, char *argv[])
{
    signed int result; // eax@11
    FILE *stream; // [sp+20h] [bp-8h]@13
    int v5; // [sp+24h] [bp-4h]@1

    v5 = 1004;
    signal(13, (__sighandler_t)1);
    if ( !gserver.LoadSettingFile() )
    {
        puts("Setting Error!!");
        exit(0);
    }
    g_log.InitLogFile("HS");
    if ( !gserver.ConnectDB() )
    {
        puts("Cannot Connect DB!!");
        exit(0);
    }
    if ( !gserver.LoadSettings() )
    {
        puts("Setting Error!!");
        exit(0);
    }
    if ( gserver.InitGame() )
    {
        puts("Helper Server Running...");
//    atexit();
        gserver.Run();
        gserver.Close();
        if ( g_Shutdown )
        {
            stream = fopen(".shutdown", "w");
            fclose(stream);
        }
        g_gamelogbuffer.__ls(init("SYSTEM"));
        g_gamelogbuffer.__ls("End!");
        g_gamelogbuffer.__ls(end);
        result = v5;
    }
    else
    {
        result = 1;
    }
    return result;
}
