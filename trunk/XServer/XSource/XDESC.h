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

#ifndef __X_DESC__
#define __X_DESC__


#include "XDES.h"
#include "XCommunicationProtocol.h"

#include "log.h"
#include "socket.h"
#include "input.h"
#include "input_auth.h"

#include <unistd.h>

class XPC;

class XDESC {
public:
    int Socket;
    XPC *xCharacter;
	unsigned int iServerMsgCount, iClientMsgCount;
    unsigned int DESDecryptKey[2], DESEncryptKey[2];
    CInputProcessor *Input;
    XDESC *PreviousNode, *NextNode;
    char szAddr[16];
	unsigned short sPort;

public:
    XDESC(void);
    ~XDESC();

    void CloseSocket(void);
    int Packet(void const *vaInputData, size_t iInputLen);
    int ProcessOutput(const void *data, size_t len);
    int ProcessInput(void);
    void SetPhase(int phase);
};

#endif
