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

void CServer::Run(void)
{
    fd_set exceptfds; // [sp+124h] [bp-CA0h]@195
    fd_set writefds; // [sp+524h] [bp-8A0h]@195
    fd_set readfds; // [sp+924h] [bp-4A0h]@195
    char dest; // [sp+D27h] [bp-9Dh]@91
    pthread_t newthread; // [sp+D54h] [bp-70h]@1
    int v68; // [sp+D64h] [bp-60h]@1
    int v69; // [sp+D68h] [bp-5Ch]@3
    int v70; // [sp+D6Ch] [bp-58h]@5
    CDescriptor *v71; // [sp+D70h] [bp-54h]@22
    CDescriptor *v72; // [sp+D74h] [bp-50h]@23
    struct timeval timeout; // [sp+D8Ch] [bp-38h]@7
    struct timeval v75; // [sp+D94h] [bp-30h]@7
    struct timeval v76; // [sp+D9Ch] [bp-28h]@3
    struct timeval v77; // [sp+DA4h] [bp-20h]@7
    struct timeval v78; // [sp+DACh] [bp-18h]@3
    struct timeval v80; // [sp+DB4h] [bp-10h]@1
    struct timeval tv; // [sp+DBCh] [bp-8h]@1

    CNetMsg v73;

    v68 = 0;

    v80.tv_usec = 100000;
    v80.tv_sec = 0;

    FD_ZERO(&this->Unk35876);

    //i = 0;
    //v67 = 0;
    //newthread = this->Unk36900;
    //v66 = this->Unk36900;

    GetTimeofDay(&tv, 0);

    while(!this->Unk41052)
    {
        v69 = InitFDSET(this->Unk0, this->Unk4, &this->Unk32804, &this->Unk33828, &this->Unk34852);

        GetTimeofDay(&v76, 0);
        TimeDiff(&v78, &v76, &tv);

        if(v78.tv_sec || v78.tv_usec > 99999)
        {
            v70 = v78.tv_usec / 100000 + 10 * v78.tv_sec;
            v78.tv_sec = 0;
            v78.tv_usec %= 100000;
        }
        else
        {
            v70 = 0;
        }

        TimeDiff(&v77, &v80, &v78);
        TimeAdd(&tv, &v76, &v77);
        GetTimeofDay(&v75, 0);
        TimeDiff(&timeout, &tv, &v75);

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

            GetTimeofDay(&v75, 0);
            TimeDiff(&timeout, &tv, &v75);
        }
        while(timeout.tv_usec || timeout.tv_sec);

        a_NullTime.tv_sec = 0;
        a_NullTime.tv_usec = 0;

        if(select(v69 + 1, &this->Unk32804, &this->Unk33828, &this->Unk34852, &a_NullTime) < 0)
        {
            g_gamelogbuffer.__ls(init("SYS_ERR"));
            g_gamelogbuffer.__ls("Select poll");
            g_gamelogbuffer.__ls(end);

            return;
        }

        a_NullTime.tv_sec = 0;
        a_NullTime.tv_usec = 0;

        if(FD_ISSET(this->Unk0, &this->Unk32804)) // _bittest
            this->NewDescriptor(this->Unk0);

        v68 = 0;
        ++v70;

        if(v70 <= 0)
            v70 = 1;

        v71 = this->Unk4;

        while(1)
        {
            v72 = v71;

            if(!v71)
                break;

            v71 = v72->Unk380;
            if(v72->Unk340 != 1 && v72->Unk340 != 17)
            {
                if(v72->Unk332 >= 0)
                    v72->Unk332 += v70;

                if(FD_ISSET(v72->Unk192, &this->Unk34852) || ++v72->Unk320 > 1800) // _bittest
                {
                    FD_SET(v72->Unk192, &this->Unk32804); // _bittestandreset
                    FD_SET(v72->Unk192, &this->Unk33828); // _bittestandreset

                    v72->Unk320 = 0;
                    v72->Unk361 = 1;

                    this->CloseSocket(v72);
                }
                else
                {
                    if(!v72->Unk117)
                    {
                        if(v72->Unk364)
                        {
                            if(++v72->Unk368 > 600)
                            {
                                g_gamelogbuffer.__ls(init("HELPER ERROR", v72->Unk4));
                                g_gamelogbuffer.__ls("TIMEOUT");
                                g_gamelogbuffer.__ls(end);

                                this->CloseSocket(v72);
                            }
                        }
                        else
                        {
                            CMutex v62(&v72->Unk164, false);

                            if(v62.IsLock())
                            {
                                if(FD_ISSET(v72->Unk192, &this->Unk32804) && v72->Unk340 != 17 && v72->ProcessInput() < 0) // _bittest
                                {
                                    v72->Unk361 = 1;
                                    this->CloseSocket(v72);
                                }
                                else
                                {
                                    ++v68;
                                    switch(v72->Unk340)
                                    {
                                        case 0x1E:
                                            if(++v72->Unk344 > 600)
                                            {
                                                g_gamelogbuffer.__ls(init("CONN_ERR", v72->Unk4));
                                                g_gamelogbuffer.__ls("Timeout");
                                                g_gamelogbuffer.__ls(end);

                                                CNetMsg v61;

                                                FailMsg(v61, 5);

                                                if(v72)
                                                    v72->WriteToOutput(v61);

                                                this->SendOutput(v72);
                                                v72->Unk361 = 1;

                                                this->CloseSocket(v72);
                                            }
                                            break;
                                        case 0x1F:
                                            v72->Unk124.Clear();
                                            if(!this->DisConnectLogedIn(v72))
                                            {
                                                v72->Unk117 = 1;
                                                v72->Unk340 = 19;

                                                this->Unk42360.AddToQ(v72);
                                            }
                                            break;
                                        case 0x13:
                                            if(v72->Unk124.Get(v73))
                                            {
                                                do
                                                {
                                                    if(v72)
                                                        v72->WriteToOutput(v73);

                                                    this->SendOutput(v72);
                                                }
                                                while(v72->Unk124.Get(v73));

                                                v72->Unk340 = 10;
                                                v72->Unk320 = 0;
                                            }
                                            else
                                            {
                                                CNetMsg v61;

                                                FailMsg(v61, 7);

                                                if(v72)
                                                    v72->WriteToOutput(v61);

                                                this->SendOutput(v72);
                                                v72->Unk340 = 1;
                                            }
                                            break;
                                        default:
                                            if(v72->Unk340 != 20 && v72->Unk340 != 21)
                                            {
                                                if(v72->Unk340 == 22)
                                                {
                                                    if(v72->Unk124.Get(v73))
                                                    {
                                                        do
                                                        {
                                                            if(v72)
                                                                v72->WriteToOutput(v73);

                                                            this->SendOutput(v72);
                                                        }
                                                        while(v72->Unk124.Get(v73));

                                                        if(v73.MsgType == 2)
                                                        {
                                                            v73.MoveFirst();

                                                            v73.__rs(dest);

                                                            if(dest == 4)
                                                            {
                                                                v72->Unk363 = 1;
                                                                v72->Unk340 = 2;
                                                            }
                                                            else
                                                            {
                                                                if(!this->Unk452252.findmember(v72->Unk372->Unk4))
                                                                {
                                                                    CNetMsg v61;

                                                                    HelperGuildLoadReq(v61, v72->Unk4, v72->Unk372->Unk4);

                                                                    if(!gserver.Unk452130 && gserver.Unk20 && !gserver.Unk20->Unk361 && this->Unk20)
                                                                        this->Unk20->WriteToOutput(v61);

                                                                    v72->WaitHelperReply(true);
                                                                }

                                                                v72->Unk340 = 25;
                                                                v72->Unk320 = 0;
                                                            }
                                                        }
                                                    }
                                                    else
                                                    {
                                                        CNetMsg v61;

                                                        FailMsg(v61, 9);

                                                        if(v72)
                                                            v72->WriteToOutput(v61);

                                                        this->SendOutput(v72);
                                                        v72->Unk340 = 1;
                                                    }
                                                }
                                                else
                                                {
                                                    if(!v72->Unk340 && this->Unk24.Playing(v72->Unk372))
                                                    {
                                                        this->DecreaseTimeForPC(v72->Unk372);
                                                        if(v72->Unk372->Unk772 <= 0)
                                                        {
                                                            v72->Unk372->Unk772 = 6000;
                                                            v72->Unk316 = 0;
                                                            v72->Unk120 = 1;
                                                            this->Unk42360.AddToQ(v72);

                                                            g_gamelogbuffer.__ls(init("CHAR_UPDATE", v72->Unk372->Unk8, v72->Unk4));
                                                            if(v72->Unk372->Unk1280)
                                                            {
                                                                g_gamelogbuffer.__ls(v72->Unk372->Unk1280->Count());
                                                            }
                                                            else
                                                            {
                                                                g_gamelogbuffer.__ls(0);
                                                            }
                                                            g_gamelogbuffer.__ls(end);
                                                        }

                                                        if(v72->IsHackResponseTimeout())
                                                        {
                                                            g_gamelogbuffer.__ls(init("HACK PULSE", v72->Unk372->Unk8, v72->Unk4));
                                                            g_gamelogbuffer.__ls("NOT RESPONSE");
                                                            g_gamelogbuffer.__ls(end);

                                                            v72->SetHackCheckPulse();
                                                            v72->Unk361 = 1;
                                                        }
                                                    }

                                                    if(v72->Unk240.Get(v73))
                                                    {
                                                        v72->Unk320 = 0;
                                                        if(v72->Unk340)
                                                        {
                                                            if(v72->Unk340 == 23)
                                                            {
                                                                if(v72->GetLogin(v73))
                                                                {
                                                                    v72->Unk320 = 0;
                                                                    v72->Unk117 = 0;

                                                                    if(gserver.Unk452128 || !gserver.Unk16 || gserver.Unk16->Unk361)
                                                                    {
                                                                        CNetMsg v61;

                                                                        FailMsg(v61, 5);

                                                                        if(v72)
                                                                            v72->WriteToOutput(v61);

                                                                        this->SendOutput(v72);
                                                                        v72->Unk340 = 1;
                                                                    }
                                                                    else
                                                                    {
                                                                        CNetMsg v61;

                                                                        ConnLoginMsg(v61, v72);

                                                                        if(this->Unk16)
                                                                            this->Unk16->WriteToOutput(v61);

                                                                        v72->Unk340 = 30;
                                                                        v72->Unk344 = 0;
                                                                    }
                                                                    goto LABEL_157;
                                                                }
                                                            }
                                                            else
                                                            {
                                                                if(v72->Unk340 != 10 || v73.MsgType != 4)
                                                                {
                                                                    if(v72->Unk340 == 25 && v73.MsgType == 5)
                                                                    {
                                                                        g_gamelogbuffer.__ls(init("CHAR_LOAD", v72->Unk4));
                                                                        g_gamelogbuffer.__ls("NAME");
                                                                        g_gamelogbuffer.__ls(delim);
                                                                        g_gamelogbuffer.__ls(v72->Unk372->Unk8);
                                                                        g_gamelogbuffer.__ls(delim);
                                                                        g_gamelogbuffer.__ls("JOB");
                                                                        g_gamelogbuffer.__ls(delim);
                                                                        g_gamelogbuffer.__ls(v72->Unk372->Unk477);
                                                                        g_gamelogbuffer.__ls(delim);
                                                                        g_gamelogbuffer.__ls("LEVEL");
                                                                        g_gamelogbuffer.__ls(delim);
                                                                        g_gamelogbuffer.__ls(v72->Unk372->Unk60);
                                                                        g_gamelogbuffer.__ls(delim);
                                                                        g_gamelogbuffer.__ls("EXP");
                                                                        g_gamelogbuffer.__ls(delim);
                                                                        g_gamelogbuffer.__ls(v72->Unk372->Unk64);
                                                                        g_gamelogbuffer.__ls(delim);
                                                                        g_gamelogbuffer.__ls("MONEY");
                                                                        g_gamelogbuffer.__ls(delim);
                                                                        if(v72->Unk372->Unk1280)
                                                                        {
                                                                            g_gamelogbuffer.__ls(v72->Unk372->Unk1280->Count());
                                                                        }
                                                                        else
                                                                        {
                                                                            g_gamelogbuffer.__ls(0);
                                                                        }
                                                                        g_gamelogbuffer.__ls(end);

                                                                        this->CharPrePlay(v72);
                                                                        if(!gserver.Unk452128)
                                                                        {
                                                                            if(gserver.Unk16 && !gserver.Unk16->Unk361)
                                                                            {
                                                                                CNetMsg v61;

                                                                                ConnPlayingMsg(v61, v72, 0);

                                                                                if(this->Unk16)
                                                                                    this->Unk16->WriteToOutput(v61);
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                                else
                                                                {
                                                                    if(v72->StartGame(v73))
                                                                    {
                                                                        this->Unk42360.AddToQ(v72);
                                                                    }
                                                                    else
                                                                    {
                                                                        if(v72->CharNew(v73))
                                                                        {
                                                                            this->Unk42360.AddToQ(v72);
                                                                        }
                                                                        else
                                                                        {
                                                                            if(v72->CharDel(v73))
                                                                                this->Unk42360.AddToQ(v72);
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                        else
                                                        {
                                                            if(!this->Unk24.Playing(v72->Unk372))
                                                            {
                                                                g_gamelogbuffer.__ls(init("SYS_ERR", v72->Unk4));
                                                                g_gamelogbuffer.__ls("The state is playing, but character can't find player list!");
                                                                g_gamelogbuffer.__ls(end);

                                                                v72->Unk340 = 1;
                                                                v72->Unk361 = 1;
                                                                goto LABEL_157;
                                                            }

                                                            this->CommandInterpreter(v72, v73);
                                                            if(this->Unk41052)
                                                            {
                                                                goto LABEL_157;
                                                            }
                                                        }
                                                    }
                                                    else
                                                    {
                                                        if(v72->Unk340 == 23)
                                                        {
                                                            if(++v72->Unk344 > 100)
                                                            {
                                                                g_gamelogbuffer.__ls(init("BAD_CONNECTION"));
                                                                g_gamelogbuffer.__ls(v72->Unk196);
                                                                g_gamelogbuffer.__ls(end);

                                                                v72->Unk361 = 1;
                                                                this->CloseSocket(v72);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                            else
                                            {
                                                if(v72->Unk124.Get(v73))
                                                {
                                                    if(v72)
                                                        v72->WriteToOutput(v73);

                                                    this->SendOutput(v72);
                                                    v72->Unk124.Clear();

                                                    v72->Unk320 = 0;
                                                    v72->Unk117 = 1;

                                                    if(v72->Unk340 == 20)
                                                    {
                                                        g_gamelogbuffer.__ls(init("CHAR_CREATE", v72->Unk372->Unk8, v72->Unk4));
                                                        g_gamelogbuffer.__ls(end);
                                                    }

                                                    if(v72->Unk340 == 21)
                                                    {
                                                        g_gamelogbuffer.__ls(init("CHAR_DELETE", v72->Unk4));
                                                        g_gamelogbuffer.__ls("Char Index");
                                                        g_gamelogbuffer.__ls(delim);
                                                        g_gamelogbuffer.__ls(v72->Unk372->Unk4);
                                                        g_gamelogbuffer.__ls(delim);
                                                        g_gamelogbuffer.__ls("IP");
                                                        g_gamelogbuffer.__ls(delim);
                                                        g_gamelogbuffer.__ls(v72->Unk196);
                                                        g_gamelogbuffer.__ls(end);

                                                        if(!gserver.Unk452130)
                                                        {
                                                            if(gserver.Unk20 && !gserver.Unk20->Unk361)
                                                            {
                                                                CNetMsg v61;

                                                                HelperCharDelMsg(v61, v72->Unk372->Unk4);

                                                                if(this->Unk20)
                                                                    this->Unk20->WriteToOutput(v61);
                                                            }
                                                        }
                                                    }

                                                    v72->Unk340 = 19;
                                                    this->Unk42360.AddToQ(v72);
                                                }
                                                else
                                                {
                                                    CNetMsg v61;

                                                    FailMsg(v61, 8);

                                                    if(v72)
                                                        v72->WriteToOutput(v61);

                                                    this->SendOutput(v72);
                                                    v72->Unk340 = 1;
                                                }
                                            }
                                            break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
LABEL_157:
        v71 = this->Unk4;

        while(1)
        {
            v72 = v71;

            if(!v71)
                break;

            v71 = v72->Unk380;

            if(!v72->Unk361 && !v72->Unk340 && this->Unk24.Playing(v72->Unk372) && v72->Unk372->Unk473)
                v72->Unk372->SendStatus();
        }

        if(this->Unk41084 != -1)
        {
            if(--this->Unk41084 <= 0)
            {
                this->Unk41052 = 1;
                this->Unk41054 = 0;
            }
        }

        if(this->Unk41080 != -1)
        {
            if(--this->Unk41080 <= 0)
            {
                CNetMsg v61;

                ConnRebootReqMsg(v61);

                if(!gserver.Unk452128 && gserver.Unk16 && !gserver.Unk16->Unk361 && this->Unk16)
                    this->Unk16->WriteToOutput(v61);

                HelperShutdownMsg(v61);

                if(!gserver.Unk452130 && gserver.Unk20 && !gserver.Unk20->Unk361 && this->Unk20)
                    this->Unk20->WriteToOutput(v61);

                this->Unk41080 = -1;
            }
        }

        if(this->Unk41088 != -1)
        {
            if(--this->Unk41088 <= 0)
            {
                CNetMsg v61;

                MsgrEndGameReqMsg(v61);

                if(!gserver.Unk452129 && gserver.Unk12 && !gserver.Unk12->Unk361 && this->Unk12)
                    this->Unk12->WriteToOutput(v61);

                this->Unk41088 = -1;
            }
        }

        if(this->Unk452129 || !this->Unk12)
        {
            if(!this->Unk452129)
                this->Unk452129 = pthread_create(&newthread, 0, (void *(*)(void *))CServer::MessengerConnect, 0) == 0;
        }
        else
        {
            if(this->Unk12->Unk361)
            {
                this->Unk12->CloseSocket();

                if(this->Unk12)
                    delete this->Unk12;

                this->Unk12 = 0;
            }
            else
            {
                FD_ZERO(&readfds);
                FD_ZERO(&writefds);
                FD_ZERO(&exceptfds);

                //v66 = 0;
                int newthread_1 = 0;
                //v67 = &writefds;
                //i = &writefds;

                FD_SET(this->Unk12->Unk192, &readfds); // _bittestandset
                FD_SET(this->Unk12->Unk192, &writefds); // _bittestandset
                FD_SET(this->Unk12->Unk192, &exceptfds); // _bittestandset

                a_NullTime.tv_sec = 0;
                a_NullTime.tv_usec = 0;

                newthread_1 = select(this->Unk12->Unk192 + 1, &readfds, &writefds, &exceptfds, &a_NullTime);

                a_NullTime.tv_sec = 0;
                a_NullTime.tv_usec = 0;

                if((newthread_1 & 0x80000000) == 0)
                {
                    if(FD_ISSET(this->Unk12->Unk192, &exceptfds)) // _bittest
                    {
                        this->Unk12->Unk361 = 1;
                    }
                    else
                    {
                        if(FD_ISSET(this->Unk12->Unk192, &readfds) && this->Unk12->ProcessInput() < 0) // _bittest
                            this->Unk12->Unk361 = 1;

                        if(!this->Unk12->Unk361)
                        {
                            CNetMsg v61;

                            for(int i = 0; i <= 50 && this->Unk12->Unk240.Get(v61); i++)
                                this->ProcessMessengerMessage(v61);

                            if(FD_ISSET(this->Unk12->Unk192, &writefds)) // _bittest
                                this->Unk12->ProcessOutput();
                        }
                    }
                }
                else
                {
                    this->Unk12->Unk361 = 1;
                }
            }
        }

        if(this->Unk452130 || !this->Unk20)
        {
            if(!this->Unk452130)
                this->Unk452130 = pthread_create(&newthread, 0, (void *(*)(void *))CServer::HelperConnect, 0) == 0;
        }
        else
        {
            if(this->Unk20->Unk361)
            {
                this->Unk452252.Reset();
                this->Unk20->CloseSocket();

                if(this->Unk20)
                    delete this->Unk20;

                this->Unk20 = 0;
            }
            else
            {
                FD_SET(this->Unk12->Unk192, &exceptfds); // _bittestandset
                FD_SET(this->Unk12->Unk192, &writefds); // _bittestandset
                FD_SET(this->Unk12->Unk192, &readfds); // _bittestandset

                //v66 = 0;
                int newthread_1 = 0;
                //v67 = (fd_set *)&v59;
                //i = (fd_set *)&v59;

                FD_SET(this->Unk20->Unk192, &exceptfds); // _bittestandset
                FD_SET(this->Unk20->Unk192, &writefds); // _bittestandset
                FD_SET(this->Unk20->Unk192, &readfds); // _bittestandset

                a_NullTime.tv_sec = 0;
                a_NullTime.tv_usec = 0;

                newthread_1 = select(this->Unk20->Unk192 + 1, &exceptfds, &writefds, &readfds, &a_NullTime);

                a_NullTime.tv_sec = 0;
                a_NullTime.tv_usec = 0;

                if((newthread_1 & 0x80000000) == 0)
                {
                    if(FD_ISSET(this->Unk20->Unk192, &readfds)) // _bittest
                    {
                        this->Unk20->Unk361 = 1;
                    }
                    else
                    {
                        if(FD_ISSET(this->Unk20->Unk192, &exceptfds) && this->Unk20->ProcessInput() < 0) // _bittest
                            this->Unk20->Unk361 = 1;

                        if(!this->Unk20->Unk361)
                        {
                            CNetMsg v61;

                            for(int i = 0; i <= 50 && this->Unk20->Unk240.Get(v61); i++)
                                this->ProcessHelperMessage(v61);

                            if(FD_ISSET(this->Unk20->Unk192, &writefds)) // _bittest
                                this->Unk20->ProcessOutput();
                        }
                    }
                }
                else
                {
                    this->Unk20->Unk361 = 1;
                }
            }
        }

        if(this->Unk452128 || !this->Unk16)
        {
            if(!this->Unk452128)
                this->Unk452128 = pthread_create(&newthread, 0, (void *(*)(void *))CServer::BillingConnect, (void *)this) == 0;
        }
        else
        {
            if(this->Unk16->Unk361)
            {
                this->Unk16->CloseSocket();

                if(this->Unk16)
                    delete this->Unk16;

                this->Unk16 = 0;
            }
            else
            {
                FD_ZERO(&exceptfds);
                FD_ZERO(&writefds);
                FD_ZERO(&readfds);

                //v66 = 0;
                int newthread_1 = 0;
                //v67 = (fd_set *)&v59;
                //i = (fd_set *)&v59;

                FD_SET(this->Unk16->Unk192, &exceptfds);
                FD_SET(this->Unk16->Unk192, &writefds);
                FD_SET(this->Unk16->Unk192, &readfds);

                a_NullTime.tv_sec = 0;
                a_NullTime.tv_usec = 0;

                newthread_1 = select(this->Unk16->Unk192 + 1, &exceptfds, &writefds, &readfds, &a_NullTime);

                a_NullTime.tv_sec = 0;
                a_NullTime.tv_usec = 0;

                if((newthread_1 & 0x80000000) == 0)
                {
                    if(FD_ISSET(this->Unk16->Unk192, &readfds)) // _bittest
                    {
                        this->Unk16->Unk361 = 1;
                    }
                    else
                    {
                        if(FD_ISSET(this->Unk16->Unk192, &exceptfds) && this->Unk16->ProcessInput() < 0) // _bittest
                        {
                            this->Unk16->Unk361 = 1;
                            this->Unk41052 = 1;
                            this->Unk41054 = 1;
                        }

                        if(!this->Unk16->Unk361)
                        {
                            CNetMsg v61;

                            for(int i = 0; i <= 50 && this->Unk16->Unk240.Get(v61); i++)
                                this->ProcessBilling(v61);

                            if(FD_ISSET(this->Unk16->Unk192, &writefds)) // _bittest
                                this->Unk16->ProcessOutput();
                        }
                    }
                }
                else
                {
                    this->Unk16->Unk361 = 1;
                }
            }
        }

        if(this->Unk41052)
            break;

        v71 = this->Unk4;
        while(1)
        {
            v72 = v71;

            if(!v71)
                break;

            v71 = v72->Unk380;
            if(v72->Unk361 || v72->Unk340 == 1 || v72->Unk340 == 17)
            {
                if(v72->Unk280.GetNextPoint() && FD_ISSET(v72->Unk192, &this->Unk33828) && !v72->Unk361) // _bittest
                    v72->ProcessOutput();

                this->CloseSocket(v72);
            }
            else
            {
                if(v72->Unk280.GetNextPoint())
                {
                    if(FD_ISSET(v72->Unk192, &this->Unk33828) && (v72->Unk340 || !v72->Unk372 || v72->Unk372->Unk472) && !v72->Unk361 && v72->ProcessOutput() < 0) // _bittest
                    {
                        v72->Unk361 = 1;
                        this->CloseSocket(v72);
                    }
                }
                else
                {
                    if(v72->Unk363)
                    {
                        v72->Unk361 = 1;
                        this->CloseSocket(v72);
                    }
                }
            }
        }

        this->Unk41248 += v70;
        this->Unk41252 += 6;
        this->Unk8 = v68;

        this->HeartBeat();
        v70 = 0;
    }
}

int InitFDSET(int a1, CDescriptor *a2, fd_set *a3, fd_set *a4, fd_set *a5)
{
    int v6; // [sp+D8h] [bp-10h]@1
    CDescriptor *v7; // [sp+DCh] [bp-Ch]@1
    CDescriptor *v8; // [sp+E0h] [bp-8h]@1

    FD_ZERO(a3);
    FD_ZERO(a4);
    FD_ZERO(a5);

    FD_SET(a1, a3);

    v6 = a1;
    v8 = a2;

    while(1)
    {
        v7 = v8;

        if(!v8)
            break;

        v8 = v7->Unk380;

        if(v7->Unk192 > v6)
            v6 = v7->Unk192;

        FD_SET(v7->Unk192, a3);
        FD_SET(v7->Unk192, a4);
        FD_SET(v7->Unk192, a5);
    }

    return v6;
}

void CServer::Close(void)
{
    CDescriptor *v11; // [sp+28h] [bp-8h]@1
    CDescriptor *v12; // [sp+2Ch] [bp-4h]@2

    v11 = this->Unk4;

    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Saving All User Data....");
    g_gamelogbuffer.__ls(end);

    while(1)
    {
        v12 = v11;

        if(!v11)
            break;

        v11 = v12->Unk380;
        this->CloseSocket(v12);
    }

    this->Unk42360.Unk400037 = 1; // 442397

    while(!this->Unk42360.Unk400036) // 442396
    {
        g_gamelogbuffer.__ls(init("SYSTEM"));
        g_gamelogbuffer.__ls("Waiting for Quit DB ...");
        g_gamelogbuffer.__ls(end);

        sleep(1);
    }

    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Closing all sockets.");
    g_gamelogbuffer.__ls(end);

    close(this->Unk0);

    if(this->Unk12)
    {
        if(this->Unk12->Unk192)
            close(this->Unk12->Unk192);

        if(this->Unk12)
            delete this->Unk12;

        this->Unk12 = 0;
    }

    if(this->Unk20)
    {
        if(this->Unk20->Unk192)
            close(this->Unk20->Unk192);

        if(this->Unk20)
            delete this->Unk20;

        this->Unk20 = 0;
    }

    if(this->Unk16)
    {
        if(this->Unk16)
            delete this->Unk16;

        this->Unk16 = 0;
    }

    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Normal termination of game.");
    g_gamelogbuffer.__ls(end);

    puts("Normal termination of game.");
    sleep(10);
}

void CServer::HeartBeat(void)
{
    struct timeval v11; // [sp+1Ch] [bp-2Ch]@44
    struct timeval tv; // [sp+24h] [bp-24h]@44

    if(this->Unk41248 - this->Unk41260 > 599)
    {
        this->Unk41252 = this->GetServerTime();
        this->Unk41260 = this->Unk41248;

        CNetMsg v13;

        EnvTimeMsg(v13);

        for(int i = 0; i < this->Unk24.Unk32768; ++i)
        {
            if(this->Unk24.Unk0[i])
            {
                if(this->Unk24.Unk0[i]->Unk768)
                    this->Unk24.Unk0[i]->Unk768->WriteToOutput(v13);
            }
        }
    }

    for(int i = 0; i < this->Unk452192; ++i)
    {
        if(!this->Unk452196[i].Unk4)
        {
            for(int j = 0; j < this->Unk452196[i].Unk40; ++j)
            {
                if(this->Unk452196[i].Unk36[j].Unk0)
                {
                    if(this->Unk452196[i].Unk0 != 2 && this->Unk452196[i].Unk0 != 5 && this->Unk452196[i].Unk0 != 6)
                    {
                        if(this->Unk41248 - this->Unk452196[i].Unk36[j].Unk56 > 1)
                        {
                            this->Unk452196[i].Unk36[j].Unk56 = this->Unk41248;
                            this->Unk452196[i].Unk36[j].MobActivity();
                        }

                        if(this->Unk41248 - this->Unk452196[i].Unk36[j].Unk60 > 149)
                        {
                            this->Unk452196[i].Unk36[j].Unk60 = this->Unk41248;
                            this->Unk452196[i].Unk36[j].MobRegen();
                        }
                    }

                    this->Unk452196[i].Unk36[j].GroundItemControl();
                }
            }
        }
    }

    if(this->Unk41248 - this->Unk41268 > 599)
    {
        for(int i = 0; i < this->Unk452192; ++i)
        {
            for(int j = 0; j < this->Unk452196[i].Unk40; ++j)
            {
                if(this->Unk452196[i].Unk36[j].Unk0 && this->Unk452196[i].Unk36[j].Unk68)
                {
                    g_gamelogbuffer.__ls(init("ITEM_ADJUST"));
                    g_gamelogbuffer.__ls(this->Unk452196[i].Unk0);
                    g_gamelogbuffer.__ls(delim);
                    g_gamelogbuffer.__ls(this->Unk452196[i].Unk36[j].Unk8);
                    g_gamelogbuffer.__ls(delim);
                    g_gamelogbuffer.__ls(this->Unk452196[i].Unk36[j].Unk68);
                    g_gamelogbuffer.__ls(end);

                    this->Unk452196[i].Unk36[j].Unk68 = 0;
                }
            }
        }

        this->Unk41268 = this->Unk41248;
    }

    if(this->Unk41248 - this->Unk41264 > 17999)
    {
        for(int i = 0; i < this->Unk452192; ++i)
        {
            if(!this->Unk452196[i].Unk4)
                this->Unk452196[i].ChangeWeather();
        }

        this->Unk41264 = this->Unk41248;
    }

    if(this->Unk41116)
    {
        GetTimeofDay(&tv, 0);
        TimeDiff(&v11, &tv, &this->Unk41104);

        if(v11.tv_sec <= 9)
        {
            ++this->Unk41112;
        }
        else
        {
            if(this->Unk41120)
            {
                strcpy(g_buf, "Loop Count (10 sec): ");
                IntCat(g_buf, this->Unk41112, 0);

                CNetMsg v13;

                SayMsg(v13, 6, 0, "", "", g_buf); // FUCKING CHECK unk_80D168C -> ""

                if(this->Unk41120)
                    this->Unk41120->WriteToOutput(v13);
            }

            this->Unk41116 = 0;
            this->Unk41120 = 0;
        }
    }
}

void CServer::MessengerConnect(void *a1)
{
    gserver.Unk452129 = 1;

    while(!gserver.MakeMessengerClient())
    {
        if(gserver.Unk12)
            gserver.Unk12->Unk361 = 1;

        sleep(2);
    }

    gserver.SendMessengerHeader();
    gserver.Unk452129 = 0;

    pthread_exit(0);
}

void CServer::HelperConnect(void *a1)
{
    gserver.Unk452130 = 1;

    while(!gserver.MakeHelperClient())
    {
        if(gserver.Unk20)
            gserver.Unk20->Unk361 = 1;

        sleep(2);
    }

    gserver.SendHelperHeader();
    gserver.Unk452130 = 0;

    pthread_exit(0);
}
