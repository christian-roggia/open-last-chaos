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
#include "XSettings.h"

void at_exit_exec(void)
{
    return gserver.DisconnectDB();
}

int main(int argc, char *argv[])
{
    printf("\n========== [LAST CHAOS EMULATOR 2013] ==========\n");
    printf("==          Developed by Christian Roggia     ==\n");
    printf("==          Copyright (c) 2013-2014           ==\n");
    printf("================================================\n");

    if(!log_init())
    {
        printf("ABORT: Impossible to initialize the log files!\n");
        exit(0);
    }

    if(!config_init())
    {
        printf("ABORT: Impossible to initialize the settings file!\n");
        exit(0);
    }
    
    if(!gserver.InitGame())
    {
        printf("ABORT: Impossible to initialize the game!\n");
        exit(1);
    }

    printf("Server is running!\n");

    atexit(at_exit_exec);

    gserver.Run();
    gserver.Close();
    gserver.DisconnectDB();

    sys_log(0, "The login has been closed normally.");

    return 0;
}
