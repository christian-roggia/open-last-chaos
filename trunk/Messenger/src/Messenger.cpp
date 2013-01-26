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

#include "Messenger.hpp"

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
    g_log.InitLogFile("MS");
    if ( gserver.InitGame() )
    {
        puts("Messenger Server Running...");
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
bool CServer::DisConnectLogedIn(CDescriptor *desc)
{
  CDescriptor *desc1; // [sp+10h] [bp-8h]@1
  CDescriptor *desc2; // [sp+14h] [bp-4h]@2

  desc1 = this->NewDesc;
  do
  {
    desc2 = desc1;
    if ( !desc1 )
      return 0;
    desc1 = desc1->SubDesc;
  }
  while ( desc2 == desc || desc2->socket_ret == 23 );
  if ( desc2->socket_ret != 17 )
    desc2->socket_ret = 1;
  return 1;
}
