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

#include "ServerRun.hpp"

timeval g_timeout;
int g_usec;

void CServer::Run()
{
    int v11; // ST58_4@43
    int v12; // ST40_4@43
    int v13; // ST28_4@43
    int v14; // ST10_4@43
    signed int v23; // eax@52
    int val1; // [sp+70h] [bp-84h]@1
    int v26; // [sp+74h] [bp-80h]@1
    int val2; // [sp+78h] [bp-7Ch]@1
    int v28; // [sp+7Ch] [bp-78h]@1
    int v29; // [sp+80h] [bp-74h]@1
    CMsgListNodeServerNode *t_servernode; // [sp+84h] [bp-70h]@55
    CMsgListNodeServerNode *v31; // [sp+88h] [bp-6Ch]@56
    CMsgListNode *v32; // [sp+8Ch] [bp-68h]@49
    CMsgListNode *t_servernode2; // [sp+90h] [bp-64h]@50
    int v34; // [sp+94h] [bp-60h]@1
    int v35; // [sp+98h] [bp-5Ch]@2
    int v36; // [sp+9Ch] [bp-58h]@4
    CDescriptor *v37; // [sp+A0h] [bp-54h]@23
    CDescriptor *a2; // [sp+A4h] [bp-50h]@24
// [sp+A8h] [bp-4Ch]@1
    struct timeval timeout; // [sp+BCh] [bp-38h]@6
    timeval tv1; // [sp+C4h] [bp-30h]@6
    timeval tv2; // [sp+CCh] [bp-28h]@2
    timeval tv3; // [sp+D4h] [bp-20h]@6
    timeval tv4; // [sp+DCh] [bp-18h]@2
    timeval tv5; // [sp+E4h] [bp-10h]@1
    struct timeval tv; // [sp+ECh] [bp-8h]@1

    CNetMsg netmsg;
    v34 = 0;
    v29 = 0;
    tv5.tv_usec = 50000;
    tv5.tv_sec = 0;
    memset(&this->m_unkfds, 0, 1024u);
    v26 = 0;
    v28 = 0;
    //val1 = &this->MsgList;
    //val2 = &this->MsgList;
    GetTimeofDay(&tv, 0);
    while ( 1 )
    {
        v35 = InitFDSET(
                  this->fdesc,
                  this->NewDesc,
                  &this->m_readfds,
                  &this->m_writefds,
                  &this->m_exceptfds);
        GetTimeofDay(&tv2, 0);
        TimeDiff(&tv4, &tv2, &tv);
        if ( tv4.tv_sec || tv4.tv_usec > 49999 )
        {
            v36 = tv4.tv_usec / 50000 + 20 * tv4.tv_sec;
            tv4.tv_sec = 0;
            tv4.tv_usec %= 50000;
        }
        else
        {
            v36 = 0;
        }
        TimeDiff(&tv3, &tv5, &tv4);
        TimeAdd(&tv, &tv2, &tv3);
        GetTimeofDay(&tv1, 0);
        TimeDiff(&timeout, &tv, &tv1);
        do
        {
            if ( timeout.tv_sec >= 0 )
            {
                if ( !timeout.tv_sec && timeout.tv_usec < 0 )
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
            GetTimeofDay(&tv1, 0);
            TimeDiff(&timeout, &tv, &tv1);
        }
        while ( timeout.tv_usec || timeout.tv_sec );
        g_timeout.tv_sec = 0;
        g_usec = 0;
        if ( select(v35 + 1, &this->m_readfds, &this->m_writefds, &this->m_exceptfds, &g_timeout) < 0 )
        {
            g_gamelogbuffer.__ls(init("SYS_ERR"));
            g_gamelogbuffer.__ls("Select poll");
            g_gamelogbuffer.__ls(end);
            //CNetMsg::_CNetMsg(&netmsg, 2);
            return;
        }
//    if ( _bittest((signed __int32 *)&this->m_readfds + (this->fdesc >> 5), this->fdesc & 0x1F) )
        if ( FD_ISSET(this->fdesc, &this->m_readfds) )
            CServer::NewDescriptor(this->fdesc);
        v34 = 0;
        ++v36;
        if ( v36 <= 0 )
            v36 = 1;
        ++v29;
        if ( v29 > 300 )
        {
            mysql_ping(&this->stMysql);
            v29 = 0;
        }
        v37 = this->NewDesc;
        while ( 1 )
        {
            a2 = v37;
            if ( !v37 )
                break;
            v37 = a2->SubDesc;
            if ( a2->socket_ret != 1 && a2->socket_ret != 17 )
            {
                if ( a2->dwordA4 >= 0 )
                    a2->dwordA4 += v36;
                if ( FD_ISSET(a2->SocketDesc, &this->m_exceptfds) /*_bittest((signed __int32 *)&this->m_exceptfds + (a2->SocketDesc >> 5), a2->SocketDesc & 0x1F)*/ )
                {
                    if (FD_ISSET(a2->SocketDesc, &this->m_readfds))
                        FD_CLR(a2->SocketDesc, &this->m_readfds);

                    if (FD_ISSET(a2->SocketDesc, &this->m_writefds))
                        FD_CLR(a2->SocketDesc, &this->m_writefds);
                    //_bittestandreset((__int32 *)&this->m_readfds + (a2->SocketDesc >> 5), a2->SocketDesc & 0x1F);
                    //_bittestandreset((__int32 *)&this->m_writefds + (a2->SocketDesc >> 5), a2->SocketDesc & 0x1F);
                    a2->Iserr = 1;
                    CServer::CloseSocket(a2);
                    continue;
                }
                if ( FD_ISSET(a2->SocketDesc, &this->m_readfds) /*_bittest((signed __int32 *)&this->m_readfds + (a2->SocketDesc >> 5), a2->SocketDesc & 0x1F)*/
                        && a2->socket_ret != 17
                        && a2->ProcessInput() < 0 )
                {
                    a2->Iserr = 1;
                    a2->CloseSocket();
                    continue;
                }
                ++v34;
                if (a2->IQ2.Get(netmsg) )
                {
                    while ( 1 )
                    {
                        if ( a2->socket_ret == 23 )
                        {
                            if ( !a2->GetLogin(netmsg) )
                            {
                                netmsg.MoveFirst();
                                netmsg.__rs(val1);
                                netmsg.__rs(v26);
                                netmsg.__rs(val2);
                                netmsg.__rs(v28);
                                v11 = v28;
                                v12 = val2;
                                v13 = v26;
                                v14 = val1;
                                g_gamelogbuffer.__ls(init("BAD_VERSION"));
                                g_gamelogbuffer.__ls(v14);
                                g_gamelogbuffer.__ls(" : ");
                                g_gamelogbuffer.__ls(v13);
                                g_gamelogbuffer.__ls(" : ");
                                g_gamelogbuffer.__ls(v12);
                                g_gamelogbuffer.__ls(" : ");
                                g_gamelogbuffer.__ls(v11);
                                g_gamelogbuffer.__ls(end);
                                a2->Iserr = 1;
                                CServer::CloseSocket(a2);
                                continue;
                            }
                        }
                        else
                        {
                            CServer::CommandInterpreter(a2, netmsg);
                        }
                        if ( !a2->IQ2.Get(netmsg) )
                            continue;
                    }
                }
                if ( a2->socket_ret == 23 )
                {
                    ++a2->dwordAC;
                    if ( a2->dwordAC > 100 )
                    {
                        g_gamelogbuffer.__ls(init("BAD_CONNECTION"));
                        g_gamelogbuffer.__ls(end);
                        a2->Iserr = 1;
                        CServer::CloseSocket(a2);
                    }
                }
            }
        }
        if ( this->byte225C )
            break;
        v32 = this->MsgList.pMsgListNode;
        while ( 1 )
        {
            t_servernode2 = v32;
            if ( !v32 )
                break;
            v32 = t_servernode2->NewListNode;
            if ( t_servernode2->char2[0] )
            {
                v23 = t_servernode2->dword20++;
                if ( v23 > 100 )
                    CServer::ProcTimeout(t_servernode2);
            }
            else
            {
                t_servernode2->char2[0] = 1;
                t_servernode2->dword20 = 0;
                t_servernode = t_servernode2->ServerNode;
                while ( 1 )
                {
                    v31 = t_servernode;
                    if ( !t_servernode )
                        break;
                    t_servernode = v31->servernode2;
                    if ( v31->desc )
                        v31->desc->WriteToOutput(t_servernode2->NetMsg);
                }
                if ( !t_servernode2->char1[0] )
                {
                    if ( t_servernode2->ActualListNode )
                    {
                        t_servernode2->ActualListNode->NewListNode = t_servernode2->NewListNode;
                        if ( t_servernode2->NewListNode )
                            t_servernode2->NewListNode->ActualListNode = t_servernode2->ActualListNode;
                    }
                    else
                    {
                        this->MsgList.pMsgListNode = t_servernode2->NewListNode;
                        if ( t_servernode2->NewListNode )
                            t_servernode2->NewListNode->ActualListNode = 0;
                    }
                    t_servernode2->ActualListNode = 0;
                    t_servernode2->NewListNode = 0;
                    if ( t_servernode2 )
//                        CMsgListNode::_CMsgListNode(t_servernode2, 3);
                        delete t_servernode;
                }
            }
        }
        v37 = this->NewDesc;
        while ( 1 )
        {
            a2 = v37;
            if ( !v37 )
                break;
            v37 = a2->SubDesc;
            if ( a2->Iserr || a2->socket_ret == 1 || a2->socket_ret == 17 )
            {
                CServer::CloseSocket(a2);
            }
            else
            {
                if ( a2->OutBuf.GetNextPoint()
                        && FD_ISSET(a2->SocketDesc, &this->m_writefds)/*_bittest((__int32 *)&this->m_writefds + (a2->SocketDesc >> 5), a2->SocketDesc & 0x1F)*/
                        && !a2->Iserr
                        && a2->ProcessOutput() < 0 )
                {
                    a2->Iserr = 1;
                    CServer::CloseSocket(a2);
                }
            }
        }
        this->dword2260 += v36;
        this->dword8 = v34;
        v36 = 0;
    }
    //CNetMsg::_CNetMsg(&netmsg, 2);
}

int InitFDSET(int a1, CDescriptor *desc, fd_set *m_readfds, fd_set *m_writefds, fd_set *m_exceptfds)
{
    int v6 = a1;
    CDescriptor *v7;

    FD_ZERO(m_readfds);
    FD_ZERO(m_writefds);
    FD_ZERO(m_exceptfds);

    FD_SET(a1, m_readfds);

    while(1)
    {
        v7 = desc;

        if(!desc)
            break;

        desc = v7->SubDesc;

        if(v7->SocketDesc > v6)
            v6 = v7->SocketDesc;

        FD_SET(v7->SocketDesc, m_readfds);
        FD_SET(v7->SocketDesc, m_writefds);
        FD_SET(v7->SocketDesc, m_exceptfds);
    }

    return v6;
}

