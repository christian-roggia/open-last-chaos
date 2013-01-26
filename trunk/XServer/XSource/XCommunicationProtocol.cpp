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

#include "XCommunicationProtocol.h"

bool XCommunicationProtocol::CheckMessageHeader(char *&aMsg, size_t &iMsgLen, unsigned int &iClientMsgCount)
{
    if(iMsgLen < sizeof(XProtocolMessageHeader) || iMsgLen > XCP_MAX_TOTAL_LEN || aMsg == NULL) return false;
	
    XProtocolMessageHeader *xHeader = (XProtocolMessageHeader *)aMsg;
	
    if(htons(xHeader->MessageDirectionMark) != XCP_DIRECTION_MARK_CLIENT_SERVER)
	{
		sys_err(__FUNCTION__, __LINE__, "Message direction is not Client -> Server (0x%02X)!", htons(xHeader->MessageDirectionMark));
		return false;
	}
	
    iClientMsgCount = htonl(xHeader->MessageCount);
    iMsgLen         = htonl(xHeader->MessageLength);
	
    aMsg += sizeof(XProtocolMessageHeader);
	return true;
}

bool XCommunicationProtocol::SetMessageHeader(char *&aMsg, size_t &iMsgLen, unsigned int &iServerMsgCount)
{
    if(iMsgLen == 0 || iMsgLen > XCP_MAX_XOR_LEN || aMsg == NULL) return false;
	
	XProtocolMessageHeader xHeader;
	
    xHeader.MessageDirectionMark = htons(XCP_DIRECTION_MARK_SERVER_CLIENT);
    xHeader.MessageCount = htonl(iServerMsgCount++);
    xHeader.UknownSymbol = 0;
    xHeader.MessageLength = htonl(iMsgLen);
	
    char *aTmpMsg = (char *)malloc(iMsgLen + sizeof(XProtocolMessageHeader));
	
	memcpy(aTmpMsg, &xHeader, sizeof(XProtocolMessageHeader));
    memcpy(aTmpMsg + sizeof(XProtocolMessageHeader), aMsg, iMsgLen);
	
    if(aMsg) free(aMsg);

    iMsgLen += sizeof(XProtocolMessageHeader);
    aMsg = aTmpMsg;

    return true;
}

bool XCommunicationProtocol::DecryptMessage(unsigned int *laKey, size_t iInputLen, char *aInputMsg, size_t &iOutputLen, char *&aOutputMsg)
{
    if(laKey == NULL || iInputLen == 0 || iInputLen > XCP_MAX_XOR_LEN || aInputMsg == NULL) return false;
	
    size_t iCryptoOutLen = 0;
    char aPool[XCP_POOL_LEN], *paPool = aPool;

    XCommunicationEncryption::XorDecrypt(iInputLen, aInputMsg);
    XDESManager::DESCryptography(laKey, XDES_DECRYPT, aInputMsg, iInputLen, paPool, iCryptoOutLen);
    if(iCryptoOutLen == 0)
    {
        sys_err(__FUNCTION__, __LINE__, "DES DEcryption failed: The packet is too small to be decrypted!");
        return false;
    }

    XCommunicationProtocol::GetRealMessageLength(iCryptoOutLen, iOutputLen, paPool);
    if(iOutputLen == 0) return false;

    aOutputMsg = (char *)malloc(iOutputLen);
    memcpy(aOutputMsg, paPool, iOutputLen);
	
    XDESManager::NextDESKey(laKey);
    return true;
}

bool XCommunicationProtocol::EncryptMessage(unsigned int *laKey, size_t iInputLen, char *aInputMsg, size_t &iOutputLen, char *&aOutputMsg)
{
    if(laKey == NULL || iInputLen == 0 || iInputLen > XCP_MAX_RAW_LEN || aInputMsg == NULL) return false;
	
    size_t iCryptoOutLen = 0;
    char aPool[XCP_POOL_LEN], *paPool = aPool;

    XCommunicationProtocol::SetRealMessageLength(iInputLen, aInputMsg);
    XDESManager::DESCryptography(laKey, XDES_ENCRYPT, aInputMsg, iInputLen, paPool, iCryptoOutLen);
    XCommunicationEncryption::XorEncrypt(iCryptoOutLen, paPool);
	
    iOutputLen = iCryptoOutLen;
    aOutputMsg = (char *)malloc(iOutputLen);
    memcpy(aOutputMsg, paPool, iOutputLen);

    if(aInputMsg) free(aInputMsg);
    if(paPool)    free(paPool);

    XDESManager::NextDESKey(laKey);
    return true;
}


void XCommunicationProtocol::GetRealMessageLength(size_t iMsgLen, size_t &iRealMsgLen, char *&aMsg)
{
    if(iMsgLen == 0 || aMsg == NULL) return;

    iRealMsgLen = htonl(*(int *)aMsg);
	
    aMsg    += sizeof(int);
	iMsgLen -= sizeof(int);

    if(iRealMsgLen > iMsgLen)
    {
        sys_err(__FUNCTION__, __LINE__, "POST-DES Real message length overflow (%d > %d)!", iRealMsgLen, iMsgLen);
        iRealMsgLen = 0;
		return;
    }
	
    if(iRealMsgLen == 0)
    {
        sys_err(__FUNCTION__, __LINE__, "POST-DES Real message length is zero!");
        iRealMsgLen = 0;
		return;
    }
}

void XCommunicationProtocol::SetRealMessageLength(size_t &iMsgLen, char *&aMsg)
{
    char *aTmpMsg = (char *)malloc(iMsgLen + sizeof(int));
    int iTmpMsgLen = ntohl(iMsgLen);
	
	memcpy(aTmpMsg, &iTmpMsgLen, sizeof(int));
    memcpy(aTmpMsg + sizeof(int), aMsg, iMsgLen);
	
    iMsgLen += sizeof(int);
    aMsg = aTmpMsg;
}

static char szXorTable[] = "wlqdprkrhtlvek";

void XCommunicationEncryption::XorDecrypt(size_t &iXorLength, char *&aXorArray)
{
	char iDeltaXor = -128;

    for(size_t i = 0; i < iXorLength; i++)
    {
        aXorArray[i] = (aXorArray[i] ^ szXorTable[i % 14]) - iDeltaXor;
        iDeltaXor += aXorArray[i];
    }
	
    XCommunicationEncryption::CheckXorMark(iXorLength, aXorArray);
}

void XCommunicationEncryption::XorEncrypt(size_t &iXorLength, char *&aXorArray)
{
    XCommunicationEncryption::SetXorMark(iXorLength, aXorArray);
	
	char iDeltaXor = -128;
	
    for(size_t i = 0; i < iXorLength; i++)
    {
        aXorArray[i] = iDeltaXor = aXorArray[i] + iDeltaXor;
        aXorArray[i] = aXorArray[i] ^ szXorTable[i % 14];
    }
}

void XCommunicationEncryption::CheckXorMark(size_t &iXorLength, char *&aXorArray)
{
    if(*aXorArray != XOR_SUCCESS_MARK) aXorArray = 0;
	
    aXorArray++;
    iXorLength--;
}

void XCommunicationEncryption::SetXorMark(size_t &iXorLength, char *&aXorArray)
{
    char *aTmpXorArray = (char *)malloc(iXorLength + sizeof(char));
    int iTmpXorLength = iXorLength + sizeof(char);
	
	*aTmpXorArray = XOR_SUCCESS_MARK;
    memcpy(aTmpXorArray + sizeof(char), aXorArray, iTmpXorLength);
	
    iXorLength = iTmpXorLength;
    aXorArray  = aTmpXorArray;
}
