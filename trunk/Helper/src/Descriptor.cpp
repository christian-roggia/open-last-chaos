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

#include "Descriptor.hpp"

CDescriptor::CDescriptor()
{
    //CInputQueue::CInputQueue(&this->IQ1);
    //CInputBuffer::CInputBuffer(&this->InBuf);
    //CInputQueue::CInputQueue(&this->IQ2);
    //COutputBuffer::COutputBuffer(&this->OutBuf);
    this->some_header = -1;
    this->unk_integer = -1;
    this->zone = 0;
    this->zone_count = 0;
    this->SocketDesc = 0;
    memset(this->NormalIP, 0, 31u);
    this->dwordA4 = -1;
    this->socket_ret = 0;
    this->dwordAC = 0;
    this->some_errno = 0;
    this->Lastfd = 0;
    this->Iserr = 0;
    this->byteB9 = 0;
    this->ServerDesc = 0;
    this->SubDesc = 0;
}

void CDescriptor::CloseSocket()
{
    close(this->SocketDesc);
    CDescriptor::FlushQueues();
}

int CDescriptor::FindZone(int p_zone)
{
    int i; // [sp+14h] [bp-4h]@1

    for ( i = 0; i < this->zone_count; ++i )
    {
        if ( this->zone[i] == p_zone )
            return i;
    }
    return -1;
}

void CDescriptor::FlushQueues()
{
    //CInputBuffer::Clear(&this->InBuf);
    //CInputQueue::Clear(&this->IQ2);
    //COutputBuffer::Clear(&this->OutBuf);
    this->InBuf.Clear();
    this->IQ2.Clear();
    this->OutBuf.Clear();
}

bool CDescriptor::GetLogin(CNetMsg &netmsg)
{
    int i; // [sp+30h] [bp-14h]@10
    int zonecount; // [sp+34h] [bp-10h]@3
    int unk_integer; // [sp+38h] [bp-Ch]@3
    int unk_header2; // [sp+3Ch] [bp-8h]@3
    int unk_header; // [sp+40h] [bp-4h]@3

    //CNetMsg::MoveFirst(netmsg);
    netmsg.MoveFirst();
    if ( netmsg.p_msg_type != 120 )
        return 0;
    netmsg.__rs(unk_header);
    netmsg.__rs(unk_header2);
    netmsg.__rs(unk_integer);
    netmsg.__rs(zonecount);
    //CNetMsg::__rs(netmsg, &unk_header);
    //CNetMsg::__rs(v3, &unk_header2);
    //CNetMsg::__rs(v4, &unk_integer);
    //CNetMsg::__rs(v5, &zonecount);
    if ( unk_header <= 599 || unk_header > 700 )
        return 0;
    this->some_header = unk_header2;
    this->unk_integer = unk_integer;
    if ( unk_header2 == 999 || unk_header2 == 888 )
    {
        this->zone_count = 0;
        this->zone = 0;
    }
    else
    {
        if ( zonecount <= 0 )
            return 0;
        this->zone_count = zonecount;
        this->zone = new int [zone_count*4];
        for ( i = 0; i < this->zone_count; ++i )
        {
            //CNetMsg::__rs(netmsg, &v19);
            netmsg.__rs(this->zone[i]);
            //this->zone[i] = v19;
        }
    }
    //v6 = this->zone_count;
    //v7 = this->unk_integer;
    //v8 = this->some_header;
    //v9 = unk_header;
    g_gamelogbuffer.__ls(init("CONNECTED"));
    //init((const char *)&v18, "CONNECTED");        // CONTROLLARE
    //CLogBuffer::__ls(&g_gamelogbuffer, &v18);
    g_gamelogbuffer.__ls(unk_header);
    //CLogBuffer::__ls(v10, v9);
    g_gamelogbuffer.__ls(" : ");
    g_gamelogbuffer.__ls(this->some_header);
    g_gamelogbuffer.__ls(" : ");
    g_gamelogbuffer.__ls(this->unk_integer);
    g_gamelogbuffer.__ls(" : ");
    g_gamelogbuffer.__ls(this->zone_count);
    g_gamelogbuffer.__ls(end);
    this->socket_ret = 0;
//#warning "Qualcosa da fare"
    //CGuildList::sendlist(&unk_806F008, this);
    g_guildlist.sendlist(this);
    return 1;
}

signed int CDescriptor::PerformSocketRead(int fd, void *buf, size_t nbytes)
{
    signed int result; // eax@2
    ssize_t v4; // [sp+14h] [bp-4h]@1

    v4 = read(fd, buf, nbytes);
    if ( v4 <= 0 )
    {
        if ( v4 )
        {
            if ( errno == 4 )
            {
                result = 0;
            }
            else
            {
                if ( errno == 11 )
                {
                    result = 0;
                }
                else
                {
                    if ( errno == 11 )
                    {
                        result = 0;
                    }
                    else
                    {
                        if ( errno == 35 )
                            result = 0;
                        else
                            result = -1;
                    }
                }
            }
        }
        else
        {
            result = -1;
        }
    }
    else
    {
        result = v4;
    }
    return result;
}

signed int CDescriptor::ProcessInput()
{
    int nbytes; // ST10_4@4
    void *buf; // eax@4
    signed int v6; // eax@10
    char v7; // [sp+26h] [bp-2Eh]@8
    char v8; // [sp+27h] [bp-2Dh]@8
    CNetMsg NetMsg; // [sp+28h] [bp-2Ch]@8
    int a2; // [sp+4Ch] [bp-8h]@4
    char v12; // [sp+53h] [bp-1h]@1

    v12 = 0;
    do
    {
        if ( this->InBuf.GetRemain() <= 0 )
        {
            //init((const char *)&v10);                 // //CONTROLLARE
            g_gamelogbuffer.__ls(init("SYS_WARN"));
            g_gamelogbuffer.__ls("m_input overflow");
            g_gamelogbuffer.__ls(end);
            return -1;
        }
        nbytes = this->InBuf.GetRemain();
        buf = this->InBuf.GetPoint();
        a2 = CDescriptor::PerformSocketRead(this->SocketDesc, buf, nbytes);
        if ( a2 < 0 )
            return -1;
        if ( !a2 )
            return 0;
        this->InBuf.SetPoint(a2);
        //CNetMsg::CNetMsg(&NetMsg);
        v8 = 0;
        v7 = 0;
        while ( !v8 )
        {
            v6 = this->InBuf.GetMessage(NetMsg);
            if ( v6 )
            {
                if ( v6 > 0 )
                {
                    if ( v6 == 1 )
                        v8 = 1;
                }
                else
                {
                    if ( v6 == -1 )
                    {
                        v7 = 1;
                        v8 = 1;
                    }
                }
            }
            else
            {
                this->IQ2.Add(NetMsg);
                v12 = 1;
            }
        }
        if ( v7 )
        {
            delete [] &NetMsg;
            return -1;
        }
        delete [] &NetMsg;
    }
    while ( !v12 );
    return 1;
}

int CDescriptor::ProcessOutput()
{
    int v1; // eax@2
    unsigned char *buf; // [sp+1Ch] [bp-8h]@1
    int v4; // [sp+20h] [bp-4h]@2

    while ( 1 )
    {
        buf = this->OutBuf.GetNextPoint();
        if ( !buf )
            break;
        v1 = this->OutBuf.GetRemain();
        v4 = CDescriptor::WriteToDescriptor(this->SocketDesc, buf, v1);
        if ( v4 < 0 )
        {
            this->Iserr = 1;
            return -1;
        }
        if ( !v4 || this->OutBuf.Update(v4) )
            return 0;
    }
    return 0;
}

signed int CDescriptor::WriteToDescriptor(int fd, const void *buf, size_t n)
{
    signed int result; // eax@2
    int v4; // ST1C_4@11
    int v9; // [sp+24h] [bp-4h]@3

    if ( n )
    {
        v9 = write(fd, buf, n);
        if ( v9 > 0 )
        {
            result = v9;
        }
        else
        {
            if ( v9 )
            {
                if ( errno == 11 )
                {
                    result = 0;
                }
                else
                {
                    if ( errno == 11 )
                    {
                        result = 0;
                    }
                    else
                    {
                        if ( errno != 104 )
                        {
                            v4 = errno;
                            g_gamelogbuffer.__ls(init("SYS_ERR"));
                            g_gamelogbuffer.__ls("WriteToDescriptor : no =");
                            g_gamelogbuffer.__ls(errno);
                            g_gamelogbuffer.__ls(end);
                        }
                        result = -1;
                    }
                }
            }
            else
            {
                result = -1;
            }
        }
    }
    else
    {
        result = 0;
    }
    return result;
}

void CDescriptor::WriteToOutput(CNetMsg &a2)
{
    if ( a2.p_msg_type )
    {
        if ( this->OutBuf.Add(a2) )
        {
            CDescriptor::ProcessOutput();
        }
        else
        {
            g_gamelogbuffer.__ls(init("OUTPUT OVERFLOW"));
            g_gamelogbuffer.__ls(end);
            this->Iserr = 1;
        }
    }
}

CDescriptor::~CDescriptor()
{
    if ( this->zone && this->zone )
        delete [] this->zone;
    //delete this->OutBuf;
    //delete this->IQ2;
    //delete this->InBuf;
    //delete this->IQ1;
}
