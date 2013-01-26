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

/**********************************************************************************
**  Last Chaos - Project Crackdown                                               **
**  File: Descriptor.cpp                                                         **
**  Developer(s): FadeToBlack                                                    **
**  Info: www.gamefilesopen.it - www.gamefilesopen.com                           **
**  Description: -                                                               **
**********************************************************************************/

#include "XDESC.h"

XDESC::XDESC(void)
    : Socket(-1), xCharacter(0), iServerMsgCount(0), iClientMsgCount(0), sPort(0)
{
    XDESManager::ResetDESKey(this->DESDecryptKey);
    XDESManager::ResetDESKey(this->DESEncryptKey);

    memset(this->szAddr, 0, 16);

    this->SetPhase(IP_TYPE_AUTH);
}

XDESC::~XDESC()
{
    sys_log(0, "Client %s:%d closed connection after %u packet sent", this->szAddr, this->sPort, this->iServerMsgCount);
	
    XDESManager::ResetDESKey(this->DESDecryptKey);
    XDESManager::ResetDESKey(this->DESEncryptKey);

    memset(this->szAddr, 0, 16);

    if(xCharacter) delete xCharacter;
}

void XDESC::CloseSocket(void)
{
    socket_close(this->Socket);
}

int XDESC::Packet(void const *vaInputData, size_t iInputLen)
{
    size_t iOutMsgLen;
	char *aOutMsgData;
    int iProcessStatus = 0;

    if(!XCommunicationProtocol::EncryptMessage(this->DESEncryptKey, iInputLen, (char *)vaInputData, iOutMsgLen, aOutMsgData)) return -1;
    if(!XCommunicationProtocol::SetMessageHeader(aOutMsgData, iOutMsgLen, this->iServerMsgCount))                             return -1;

    iProcessStatus = this->ProcessOutput(aOutMsgData, iOutMsgLen);
    if(aOutMsgData) free(aOutMsgData);

    return iProcessStatus;
}

int XDESC::ProcessOutput(void const *data, size_t len)
{
    if(socket_write_tcp(this->Socket, data, len) < 0)
    {
        this->SetPhase(IP_TYPE_CLOSE);
        return -1;
    }

    return 0;
}

int XDESC::ProcessInput(void)
{
    char aPool[4096], *paPool = aPool;
    ssize_t iReadBytes = socket_read(this->Socket, paPool, 4096);

    if(iReadBytes < 0)
	{
		this->SetPhase(IP_TYPE_CLOSE);
        return -1;
	}

    if(iReadBytes == 0) return 0;

    while(iReadBytes > 0)
    {
        size_t iMsgLen = iReadBytes;

        if(!XCommunicationProtocol::CheckMessageHeader(paPool, iMsgLen, this->iClientMsgCount)) return -1;

		char *paMsgData = paPool, *aOutMsgData = 0;
        size_t iOutMsgLen = 0;

        iReadBytes -= iMsgLen + sizeof(XProtocolMessageHeader);
        paPool     += iMsgLen;

        if(!XCommunicationProtocol::DecryptMessage(this->DESDecryptKey, iMsgLen, paMsgData, iOutMsgLen, aOutMsgData)) return -1;
		if(iOutMsgLen > 0 && aOutMsgData != NULL) this->Input->Process(this, aOutMsgData, iOutMsgLen);

        if(aOutMsgData) free(aOutMsgData);
    }

    return 1;
}

void XDESC::SetPhase(int phase)
{
    static CInputClose *s_inputClose = new CInputClose();
    static CInputAuth *s_inputAuth = new CInputAuth();
    static CInputMain *s_inputMain = new CInputMain();

    switch(phase)
    {
    case 0:
        this->Input = s_inputClose;
        break;
    case 1:
        this->Input = s_inputAuth;
        break;
    case 2:
        this->Input = s_inputMain;
        break;
    }
}
