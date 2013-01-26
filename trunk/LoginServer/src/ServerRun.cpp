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
    char v22[52], v23[55], dest[33];
    int v30, v31;
    CNetMsg v34;
    CDescriptor *v33, *v32;
    struct timeval v37, tv, v39, v38, v41, v36, timeout;
    fd_set m_readfds, m_writefds, m_exceptfds;

    v41.tv_sec = 0;
    v41.tv_usec = 50000;
    memset(this->p_unk_array4, 0, 1024);
    GetTimeofDay(&tv, 0);

    while(!this->p_unk_char1)
    {
        v30 = InitFDSET(this->p_socket, this->p_unk_desc1, &this->p_readfds, &this->p_writefds, &this->p_exceptfds);

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

            CServer::ServerSleep(&timeout);

            GetTimeofDay(&v36, 0);
            TimeDiff(&timeout, &tv, &v36);
        }
        while(timeout.tv_usec || timeout.tv_sec);

        a_NullTime.tv_sec = 0;
        a_NullTime.tv_usec = 0;

        if(select(v30 + 1, &this->p_readfds, &this->p_writefds, &this->p_exceptfds, &a_NullTime) < 0)
        {
            g_gamelogbuffer.__ls(init("SYS_ERR"));
            g_gamelogbuffer.__ls("Select poll");
            g_gamelogbuffer.__ls(end);

            return;
        }

        if(FD_ISSET(this->p_socket, &this->p_readfds))
            this->NewDescriptor(this->p_socket);

        ++v31;
        if(v31 <= 0)
            v31 = 1;

        v32 = this->p_unk_desc1;

        while(1)
        {
            v33 = v32;
            if(!v32)
                break;

            v32 = this->p_unk_desc1->PreviousNode;

            if(v33->SocketPhase != 1 && v33->SocketPhase != 17)
            {
                if(v33->Unk252 >= 0)
                    v33->Unk252 += v31;

                if(FD_ISSET(v33->Socket, &this->p_exceptfds))
                {
                    FD_SET(v33->Socket, &this->p_readfds);
                    FD_SET(v33->Socket, &this->p_writefds);
                    v33->WasErrors = true;
                    this->CloseSocket(v33);
                }
                else
                {
                    if(v33->ProcessInput() < 0 && FD_ISSET(v33->Socket, &this->p_readfds) && v33->SocketPhase != 17)
                    {
                        v33->WasErrors = true;
                        this->CloseSocket(v33);
                    }
                    else
                    {
                        if(v33->InputQueue.Get(v34))
                        {
                            do
                            {
                                if(v33->SocketPhase == 23 && !v33->GetLogin(v34))
                                {
                                    char v100; // arg
                                    v34.MoveFirst();
                                    v34.__rs(v100);
                                    v34.__rs(dest);
                                    v34.__rs(v23);
                                    v34.__rs(v22);

                                    g_gamelogbuffer.__ls(init("BAD_CONNECTION"));
                                    g_gamelogbuffer.__ls(v33->Hostname);
                                    g_gamelogbuffer.__ls(end);

                                    v33->WasErrors = true;
                                    this->CloseSocket(v33);
                                }
                            }
                            while(v33->InputQueue.Get(v34));
                        }
                        else
                        {
                            if(v33->SocketPhase == 23)
                            {
                                if(++v33->FailedAttempts > 100)
                                {
                                    g_gamelogbuffer.__ls(init("BAD_CONNECTION"));
                                    g_gamelogbuffer.__ls(v33->Hostname);
                                    g_gamelogbuffer.__ls(end);

                                    v33->WasErrors = true;
                                    this->CloseSocket(v33);
                                }
                            }
                        }
                    }
                }
            }
        }

        if(this->p_connecting_messenger || !this->p_messenger_desc)
        {
            if(!this->p_connecting_messenger)
            {
                pthread_t m_thread;
                this->p_connecting_messenger = pthread_create(&m_thread, 0, (void *(*)(void *))&CServer::MessengerConnect, 0) == 0;
            }
        }
        else
        {
            if(this->p_messenger_desc->WasErrors)
            {
                this->p_messenger_desc->CloseSocket();

                if(this->p_messenger_desc)
                    delete this->p_messenger_desc;

                this->p_messenger_desc = 0;
            }
            else
            {
                FD_ZERO(&m_readfds);
                FD_ZERO(&m_writefds);
                FD_ZERO(&m_exceptfds);

                FD_SET(this->p_messenger_desc->Socket, &m_readfds);
                FD_SET(this->p_messenger_desc->Socket, &m_writefds);
                FD_SET(this->p_messenger_desc->Socket, &m_exceptfds);

                a_NullTime.tv_sec = 0;
                a_NullTime.tv_usec = 0;

                long m_select = select(this->p_messenger_desc->Socket + 1, &m_readfds, &m_writefds, &m_exceptfds, &a_NullTime);

                a_NullTime.tv_sec = 0;
                a_NullTime.tv_usec = 0;

                if((m_select & 0x80000000) != 0 || FD_ISSET(this->p_messenger_desc->Socket, &m_exceptfds))
                {
                    this->p_messenger_desc->WasErrors = true;
                }
                else
                {
                    if(this->p_messenger_desc->ProcessInput() < 0 && FD_ISSET(this->p_messenger_desc->Socket, &m_readfds))
                        this->p_messenger_desc->WasErrors = true;

                    if(!this->p_messenger_desc->WasErrors)
                    {
                        CNetMsg v22;

                        for(int i = 0; i <= 50 && this->p_messenger_desc->InputQueue.Get(v22); i++)
                            this->ProcMessenger(v22);

                        if(FD_ISSET(this->p_messenger_desc->Socket, &m_writefds))
                            this->p_messenger_desc->ProcessOutput();
                    }
                }
            }
        }

        for(long j = 0; j < this->p_connector_count; ++j)
        {
            if(this->p_connecting_connector[j] || !this->p_connector_descs[j])
            {
                if(!this->p_connecting_connector[j])
                {
                    pthread_t m_thread;
                    this->p_connecting_connector[j] = pthread_create(&m_thread, 0, (void *(*)(void *))&CServer::ConnectorConnect, (char *)j) == 0;
                }
            }
            else
            {
                if(this->p_connector_descs[j]->WasErrors)
                {
                    this->p_connector_descs[j]->CloseSocket();

                    if(this->p_connector_descs[j])
                        delete this->p_connector_descs[j];

                    this->p_connector_descs[j] = 0;
                }
                else
                {
                    FD_ZERO(&m_readfds);
                    FD_ZERO(&m_writefds);
                    FD_ZERO(&m_exceptfds);

                    FD_SET(this->p_connector_descs[j]->Socket, &m_readfds);
                    FD_SET(this->p_connector_descs[j]->Socket, &m_writefds);
                    FD_SET(this->p_connector_descs[j]->Socket, &m_exceptfds);

                    a_NullTime.tv_sec = 0;
                    a_NullTime.tv_usec = 0;

                    long m_select = select(this->p_connector_descs[j]->Socket + 1, &m_readfds, &m_writefds, &m_exceptfds, &a_NullTime);

                    a_NullTime.tv_sec = 0;
                    a_NullTime.tv_usec = 0;

                    if(m_select < 0 || FD_ISSET(this->p_connector_descs[j]->Socket, &m_exceptfds))
                    {
                        this->p_connector_descs[j]->WasErrors = true;
                    }
                    else
                    {
                        if(this->p_connector_descs[j]->ProcessInput() < 0 && FD_ISSET(this->p_connector_descs[j]->Socket, &m_readfds))
                            this->p_connector_descs[j]->WasErrors = true;

                        if(!this->p_connector_descs[j]->WasErrors)
                        {
                            CNetMsg v22;

                            for(int i = 0; i <= 50 && this->p_connector_descs[j]->InputQueue.Get(v22); i++)
                                this->ProcConnector(v22);

                            if(FD_ISSET(this->p_connector_descs[j]->Socket, &m_writefds))
                                this->p_connector_descs[j]->ProcessOutput();
                        }
                    }
                }
            }
        }

        if(this->p_unk_char1)
            break;

        v32 = this->p_unk_desc1;

        while(1)
        {
            v33 = v32;
            if(!v32)
                break;
            v32 = v33->PreviousNode;

            if(v33->WasErrors || v33->SocketPhase == 1 || v33->SocketPhase == 17)
            {
                this->CloseSocket(v33);
            }
            else
            {
                if(v33->OutputBuffer.GetNextPoint() && FD_ISSET(v33->Socket, &this->p_writefds) && !v33->WasErrors && v33->ProcessOutput() < 0)
                {
                    v33->WasErrors = true;
                    this->CloseSocket(v33);
                }
            }
        }

        this->p_unk_dword1 += v31;
        this->SendConnectorReqPlayer();

        if(this->p_unk_dword5 <= 300)
        {
            ++this->p_unk_dword5;
        }
        else
        {
            mysql_ping(&this->mysql_auth_db);
            mysql_ping(&this->mysql_user_db);
            this->p_unk_dword5 = 0;
        }

        v31 = 0;
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
    CDescriptor *m_next_node, *m_current_node;

    m_next_node = this->p_unk_desc1;

    while(m_next_node)
    {
        m_current_node = m_next_node;
        m_next_node = m_current_node->PreviousNode;
        this->CloseSocket(m_current_node);
    }

    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Closing all sockets.");
    g_gamelogbuffer.__ls(end);
    close(this->p_socket);

    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Normal termination of game.");
    g_gamelogbuffer.__ls(end);

    printf("Normal termination of game.");
    sleep(10);
}

void CServer::SendConnectorReqPlayer(void)
{
    if(!this->p_unk_dword3 || this->p_unk_dword1 - this->p_unk_dword3 > 199)
    {
        this->p_unk_dword3 = this->p_unk_dword1;

        CNetMsg m_msg;
        PlayerReqMsg(m_msg);

        for(long i = 0; i < this->p_connector_count; ++i)
        {
            if(this->p_connector_descs[i] && !this->p_connector_descs[i]->WasErrors && !this->p_connecting_connector[i])
            {
                if(&this->p_connector_descs[i])
                    this->p_connector_descs[i]->WriteToOutput(m_msg);

                this->p_array_connectors[i] = this->p_unk_dword1;
            }
        }
    }

    for(long i = 0; i < this->p_connector_count; ++i)
    {
        if(this->p_connector_descs[i] && !this->p_connecting_connector[i] && this->p_array_connectors[i] && this->p_unk_dword1 - this->p_array_connectors[i] > 399)
        {
            if(this->p_unk_dword1 - this->p_array_connectors[i] > 399)
            {
                for(long j = 0; j < this->p_connector_descs[i]->MaxSubNumber; ++j)
                    this->p_connector_descs[i]->ConnectorsUnk[j] = -1;
            }
        }
    }
}
