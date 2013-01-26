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
    int v30, v31;
    XDESC *v33, *v32;
    struct timeval v37, tv, v39, v38, v41, v36, timeout;

    v41.tv_sec = 0;
    v41.tv_usec = 50000;
    GetTimeofDay(&tv, 0);

    while(!this->ServerShutdowned)
    {
        v30 = InitFDSET(this->MainSocket, this->MainDesc, &this->ReadFDS, &this->WriteFDS, &this->ExceptFDS);

        GetTimeofDay(&v37, 0);
        TimeDiff(&v39, &v37, &tv);

        if(v39.tv_sec || v39.tv_usec > 49999)
        {
            v31 = v39.tv_usec / 50000 + 20 * v39.tv_sec;
            v39.tv_sec = 0;
            v39.tv_usec %= 50000;
        }
        else
        {
            v31 = 0;
        }

        TimeDiff(&v38, &v41, &v39);
        TimeAdd(&tv, &v37, &v38);
        GetTimeofDay(&v36, 0);
        TimeDiff(&timeout, &tv, &v36);

        do
        {
            if(timeout.tv_sec >= 0)
            {
                if(!timeout.tv_sec && timeout.tv_usec < 0)
                {
                    sys_err(__FUNCTION__, __LINE__, "Timeout value is negative");

                    timeout.tv_usec = 0;
                }
            }
            else
            {
                sys_err(__FUNCTION__, __LINE__, "Timeout value is negative");

                timeout.tv_sec = 0;
            }

            CServer::ServerSleep(&timeout);

            GetTimeofDay(&v36, 0);
            TimeDiff(&timeout, &tv, &v36);
        }
        while(timeout.tv_usec || timeout.tv_sec);

        a_NullTime.tv_sec = 0;
        a_NullTime.tv_usec = 0;

        if(select(v30 + 1, &this->ReadFDS, &this->WriteFDS, &this->ExceptFDS, &a_NullTime) < 0)
        {
            sys_err(__FUNCTION__, __LINE__, "Select poll");
            return;
        }

        if(FD_ISSET(this->MainSocket, &this->ReadFDS)) this->NewDescriptor(this->MainSocket);

        ++v31;
        if(v31 <= 0)
            v31 = 1;

        v32 = this->MainDesc;

        while(1)
        {
            v33 = v32;
            if(!v32)
                break;

            v32 = this->MainDesc->PreviousNode;

            if(FD_ISSET(v33->Socket, &this->ExceptFDS))
            {
                FD_SET(v33->Socket, &this->ReadFDS);
                FD_SET(v33->Socket, &this->WriteFDS);
                v33->SetPhase(IP_TYPE_CLOSE);
                this->CloseSocket(v33);
            }
            else
            {
                if(v33->ProcessInput() < 0 && FD_ISSET(v33->Socket, &this->ReadFDS))
                {
                    v33->SetPhase(IP_TYPE_CLOSE);
                    this->CloseSocket(v33);
                }
            }
        }

        if(this->ServerShutdowned)
            break;

        v32 = this->MainDesc;

        while(1)
        {
            v33 = v32;
            if(!v32)
                break;
            v32 = v33->PreviousNode;

            if(v33->Input->GetType() == IP_TYPE_CLOSE) this->CloseSocket(v33);
        }

        /*if(this->MySQLNextPing <= 300)
        {
            ++this->MySQLNextPing;
        }
        else
        {
            mysql_ping(&this->MySQLAuthDB);
            mysql_ping(&this->MySQLDataDB);
            this->MySQLNextPing = 0;
        }*/

        v31 = 0;
    }
}

int InitFDSET(int a1, XDESC *a2, fd_set *m_readfds, fd_set *m_writefds, fd_set *m_exceptfds)
{
    int v6 = a1;
    XDESC *v7, *v8 = a2;

    FD_ZERO(m_readfds);
    FD_ZERO(m_writefds);
    FD_ZERO(m_exceptfds);

    FD_SET(a1, m_readfds);

    while(1)
    {
        v7 = v8;

        if(!v8)
            break;

        v8 = v7->PreviousNode;

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
    XDESC *m_next_node, *m_current_node;

    m_next_node = this->MainDesc;

    while(m_next_node)
    {
        m_current_node = m_next_node;
        m_next_node = m_current_node->PreviousNode;
        this->CloseSocket(m_current_node);
    }

    sys_log(0, "Closing all sockets.");

    socket_close(this->MainSocket);

    sys_log(0, "Normal termination of game.");
    printf("Normal termination of game.");

    sleep(10);
}
