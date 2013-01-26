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

void at_exit_exec(void) { return gserver.DisconnectDB(); }

int main()
{
    if(!gserver.LoadSettingFile())
    {
        printf("Load Setting File Error!!\n");
        exit(0);
    }
    
    sprintf(g_buf, "LS%02d", gserver.p_server_no);
    g_log.InitLogFile(g_buf);
    
    if(!gserver.ConnectDB())
    {
        printf("Cannot connect to the Database!\n");
        exit(0);
    }
    
    if(!gserver.InitGame())
        return 1;
    
    mysql_close(&gserver.mysql_data_db);
    printf("Last Chaos - Login Running...\n");
    
    /* CLOSE THE DATABASE CONNECTION AT EXIT */
    atexit(at_exit_exec);
    gserver.Run();
    gserver.Close();
    gserver.DisconnectDB();
    
    if(gserver.p_unk_char3)
    {
        FILE *stream;
        stream = fopen(".shutdown", "w");
        fclose(stream);
    }
    
    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("End!");
    g_gamelogbuffer.__ls(end);
    return 0;
}
