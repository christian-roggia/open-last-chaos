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

class CDescriptor;

#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include "InputBuffer.hpp"
//#include "NetMsg.hpp"
#include "OutputBuffer.hpp"
#include "Log.hpp"
#include "Guild.hpp"

#include <sys/errno.h>

class CDescriptor
{
public:
    CDescriptor();
    void CloseSocket();
    int FindZone(int p_zone);
    void FlushQueues();
    bool GetLogin(CNetMsg &);
    signed int PerformSocketRead(int fd, void *buf, size_t nbytes);
    signed int ProcessInput();
    int ProcessOutput();
    signed int WriteToDescriptor(int fd, const void *buf, size_t n);
    void WriteToOutput(CNetMsg &);
    ~CDescriptor();
//private:
    int32_t some_header;
    int32_t unk_integer;
    int32_t *zone;
    int32_t zone_count;
    int32_t SocketDesc;
    char NormalIP[32];
    //#define NormalIP f15
    CInputQueue IQ1;
    CInputBuffer InBuf;
    CInputQueue IQ2;
    COutputBuffer OutBuf;
    int32_t dwordA4;
    int32_t socket_ret;
    //#define socket_ret dwordA8
    int32_t dwordAC;
    int32_t some_errno;
    //#define some_errno dwordB0
    int32_t Lastfd;
    //#define Lastfd dwordB4
    char Iserr;
    char byteB9;
    char fBA[2];
  CDescriptor *ServerDesc;
  CDescriptor *SubDesc;
};

#endif
