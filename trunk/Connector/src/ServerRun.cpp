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

#include "ServerRun.h"

void CServer::Run(void)
{
  char v18; // [sp+8Fh] [bp-C85h]@56
  //fd_set exceptfds; // [sp+90h] [bp-C84h]@53
  //fd_set writefds; // [sp+490h] [bp-884h]@53
  //fd_set readfds; // [sp+890h] [bp-484h]@53
  //int v22; // [sp+C90h] [bp-84h]@9
  pthread_t newthread; // [sp+CA0h] [bp-74h]@1
  //fd_set *i; // [sp+CA4h] [bp-70h]@1
  //int v25; // [sp+CA8h] [bp-6Ch]@1
  //fd_set *v26; // [sp+CACh] [bp-68h]@1
  int v27; // [sp+CB0h] [bp-64h]@1
  int v28; // [sp+CB4h] [bp-60h]@1
  int v29; // [sp+CB8h] [bp-5Ch]@3
  int v30; // [sp+CBCh] [bp-58h]@5
  //int v31; // [sp+CC0h] [bp-54h]@25
  //int v32; // [sp+CC4h] [bp-50h]@26
  //char v33; // [sp+CC8h] [bp-4Ch]@1
  //struct timeval timeout; // [sp+CDCh] [bp-38h]@7
  //char v35; // [sp+CE4h] [bp-30h]@7
  //char v36; // [sp+CECh] [bp-28h]@3
  //char v37; // [sp+CF4h] [bp-20h]@7
  //int v38; // [sp+CFCh] [bp-18h]@3
  //int v39; // [sp+D00h] [bp-14h]@4
  //int v40; // [sp+D04h] [bp-10h]@1
  //int v41; // [sp+D08h] [bp-Ch]@1
  //struct timeval tv; // [sp+D0Ch] [bp-8h]@1

  fd_set exceptfds, writefds, readfds;
  CDescriptor *v31, *v32;
  CNetMsg v33;
  struct timeval timeout, v35, v36, v37, v38, v40, tv;
  int m_ret = 0;

  v28 = 0;
  v27 = 72000;
  v40.tv_usec = 50000;
  v40.tv_sec = 0;
  memset(this->p_unk_array4, 0, 0x400);
  GetTimeofDay(&tv, 0);

  while(!this->Shutdowned)
  {
    v29 = InitFDSET(this->ServerSocket, this->ClientDescriptors, &this->ReadFDS, &this->WriteFDS, &this->ExceptFDS);
    GetTimeofDay(&v36, 0);
    TimeDiff(&v38, &v36, &tv);

    if(v38.tv_sec || v38.tv_usec > 49999)
    {
      v30 = v38.tv_usec / 50000 + 20 * v38.tv_sec;
      v38.tv_sec = 0;
      v38.tv_usec %= 50000;
    }
    else
    {
      v30 = 0;
    }

    TimeDiff(&v37, &v40, &v38);
    TimeAdd(&tv, &v36, &v37);
    GetTimeofDay(&v35, 0);
    TimeDiff(&timeout, &tv, &v35);

    do
    {
      if(timeout.tv_sec >= 0)
      {
        if(!timeout.tv_sec && timeout.tv_usec < 0)
        {
          g_gamelogbuffer.__ls(init("SYS_ERR"));
          g_gamelogbuffer.__ls("Timeout value is negative");
          g_gamelogbuffer.__ls(end);

          timeout.tv_usec = 0;
        }
      }
      else
      {
        g_gamelogbuffer.__ls(init("SYS_ERR"));
        g_gamelogbuffer.__ls("Timeout value is negative");
        g_gamelogbuffer.__ls(end);

        timeout.tv_sec = 0;
      }

      this->ServerSleep(&timeout);
      GetTimeofDay(&v35, 0);
      TimeDiff(&timeout, &tv, &v35);
    }
    while(timeout.tv_usec || timeout.tv_sec);

    a_NullTime.tv_sec = 0;
    a_NullTime.tv_usec = 0;

    if(select(v29 + 1, &this->ReadFDS, &this->WriteFDS, &this->ExceptFDS, &a_NullTime) < 0)
    {
      g_gamelogbuffer.__ls(init("SYS_ERR"));
      g_gamelogbuffer.__ls("Select poll");
      g_gamelogbuffer.__ls(end);

      return;
    }

    a_NullTime.tv_sec = 0;
    a_NullTime.tv_usec = 0;

    if(FD_ISSET(this->ServerSocket, &this->ReadFDS))
        this->NewDescriptor(this->ServerSocket);


    if(v27 >= 0)
    {
      --v27;
    }
    else
    {
      v27 = 72000;

      g_gamelogbuffer.__ls(init("CONNECTIONS"));
      g_gamelogbuffer.__ls(v28);
      g_gamelogbuffer.__ls(end);
    }

    v28 = 0;
    ++v30;

    if(v30 <= 0)
      v30 = 1;

    v31 = this->ClientDescriptors;
RESTART:
    while(1)
    {
      v32 = v31;

      if(!v31)
        break;

      v31 = v32->Node;

      if(v32->Unk152 != 1 && v32->Unk152 != 17)
      {
        if(v32->Unk148 >= 0)
          v32->Unk148 += v30;

        if(FD_ISSET(v32->Socket, &this->ExceptFDS))
        {
          v32->WasErrors = true;
          this->CloseSocket(v32);

          continue;
        }

        if(FD_ISSET(v32->Socket, &this->ReadFDS) && v32->Unk152 != 17 && v32->ProcessInput() < 0)
        {
          v32->WasErrors = true;
          this->CloseSocket(v32);

          continue;
        }

        ++v28;
        if(v32->InputQueue2.Get(v33))
        {
          while(1)
          {
            if(v32->Unk152)
            {
              if(v32->Unk152 == 23)
              {
                if(!v32->GetLogin(v33))
                {
                  v32->WasErrors = true;
                  this->CloseSocket(v32);

                  goto RESTART;
                }

                g_gamelogbuffer.__ls(init("CONNECTED", v32->Hostname));
                g_gamelogbuffer.__ls(v32->IsTester);
                g_gamelogbuffer.__ls(delim);
                g_gamelogbuffer.__ls((int)v32->SubServerID);
                g_gamelogbuffer.__ls(end);
              }
            }
            else
            {
              this->CommandInterpreter(v32, v33);

              if(this->Shutdowned)
                goto RESTART;
            }

            if(!v32->InputQueue2.Get(v33))
              goto RESTART;
          }
        }

        if(v32->Unk152 == 23)
        {
          ++v32->Unk156;
          if(v32->Unk156 > 3600)
          {
            g_gamelogbuffer.__ls(init("BAD_CONNECTION", v32->Hostname));
            g_gamelogbuffer.__ls(end);
            v32->WasErrors = true;

            this->CloseSocket(v32);
          }
        }
      }
    }
	
    this->CheckPlayers();
	
    if(this->BillingClient.IsRunning())
    {
        FD_ZERO(&readfds);
        FD_ZERO(&writefds);
        FD_ZERO(&exceptfds);

        FD_SET(this->BillingClient.Socket, &readfds);
        FD_SET(this->BillingClient.Socket, &writefds);
        FD_SET(this->BillingClient.Socket, &exceptfds);

        a_NullTime.tv_sec = 0;
        a_NullTime.tv_usec = 0;

        m_ret = select(this->BillingClient.Socket + 1, &readfds, &writefds, &exceptfds, &a_NullTime);

        a_NullTime.tv_sec = 0;
        a_NullTime.tv_usec = 0;

        if(m_ret < 0 || FD_ISSET(this->BillingClient.Socket, &exceptfds))
        {
            this->BillingClient.Close();
        }
        else
        {
            v18 = 1;

            if(FD_ISSET(this->BillingClient.Socket, &readfds) && !this->BillingClient.ProcessInput())
            {
                v18 = 0;
                this->BillingClient.Close();
            }

            if(v18)
            {
                for(int i = 0; i <= 50 && this->BillingClient.ProcessInputQueue(); i++)
                    this->BillingClient.ProcessBilling();

                if(FD_ISSET(this->BillingClient.Socket, &writefds))
                    this->BillingClient.ProcessOutput();
            }
        }
    }
    else
    {
      if(!this->BillingClient.IsTrying())
        pthread_create(&newthread, 0, (void *(*)(void *))CBillingClient::BillingConnect, (char *)&this->BillingClient);
    }

    if(this->Shutdowned)
      break;

    v31 = this->ClientDescriptors;

    while(1)
    {
      v32 = v31;

      if(!v31)
        break;

      v31 = v32->Node;

      if(v32->WasErrors || v32->Unk152 == 1 || v32->Unk152 == 17)
      {
        this->CloseSocket(v32);
      }
      else
      {
        if(v32->OutputBuffer.GetNextPoint() && FD_ISSET(v32->Socket, &this->WriteFDS) && !v32->WasErrors && v32->ProcessOutput() < 0)
        {
          v32->WasErrors = true;
          this->CloseSocket(v32);
        }
      }
    }

    this->Unk1 += v30;

    this->HeartBeat();
    v30 = 0;
  }
}

int InitFDSET(int a1, CDescriptor *a2, fd_set *m_readfds, fd_set *m_writefds, fd_set *m_exceptfds)
{
    int v6 = a1;
    CDescriptor *v7;
    CDescriptor *v8 = a2;

    FD_ZERO(m_readfds);
    FD_ZERO(m_writefds);
    FD_ZERO(m_exceptfds);

    FD_SET(a1, m_readfds);

    while(1)
    {
        v7 = v8;

        if(!v8)
            break;

        v8 = v7->Node; // TO CHECK!

        if(v7->Socket > v6)
            v6 = v7->Socket;

        FD_SET(v7->Socket, m_readfds);
        FD_SET(v7->Socket, m_writefds);
        FD_SET(v7->Socket, m_exceptfds);
    }

    return v6;
}

void CServer::Close(void)
{
  CDescriptor *m_current_node = this->ClientDescriptors, *m_next_node;
  
  while(1)
  {
    m_next_node = m_current_node;
    
    if(!m_current_node)
      break;
    
    m_current_node = m_next_node->Node;
    this->CloseSocket(m_next_node);
  }
  
  g_gamelogbuffer.__ls(init("SYSTEM"));
  g_gamelogbuffer.__ls("Closing all sockets.");
  g_gamelogbuffer.__ls(end);
  
  close(this->ServerSocket);
  this->InitUserData();
  
  g_gamelogbuffer.__ls(init("SYSTEM"));
  g_gamelogbuffer.__ls("Normal termination of game.");
  g_gamelogbuffer.__ls(end);
  
  puts("Normal termination of game.");
  sleep(10);
}

void CServer::HeartBeat(void)
{
    this->SavePlayersCount();

    if(this->HeartBeats <= 300)
    {
        ++this->HeartBeats;
    }
    else
    {
        this->HeartBeats = 0;
        mysql_ping(&this->AuthSQL);
        mysql_ping(&this->UserSQL);
    }
}
