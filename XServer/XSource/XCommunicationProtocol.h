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

#ifndef __X_COMMUNICATION_PROTOCOL__
#define __X_COMMUNICATION_PROTOCOL__

#include <stdlib.h>
#include "log.h"
#include "socket.h"
#include "XDES.h"

#define XCP_DIRECTION_MARK_CLIENT_SERVER 0x8101
#define XCP_DIRECTION_MARK_SERVER_CLIENT 0x0181

#define XCP_MAX_TOTAL_LEN     1021 // Max total length allow
#define XCP_MAX_XOR_LEN       1009 // Max length before xor or after xor operation
#define XCP_MAX_RAW_LEN       1004 // Max length of raw data

#define XCP_POOL_LEN          1008 // Length of the pool for DES Encryption, client length is 1012 but is not a multiple of 8

#define XCP_MAX_STRING_LENGTH 256 // Max input/output Length

#pragma pack(push)
#pragma pack(1)

typedef struct {
    unsigned short MessageDirectionMark;
	unsigned int MessageCount;
    unsigned short UknownSymbol;
    size_t MessageLength;
} XProtocolMessageHeader;

#pragma pack(pop)

class XCommunicationProtocol {
public:
    static bool CheckMessageHeader(char *&aMsg, size_t &iMsgLen, unsigned int &iClientMsgCount);
    static bool SetMessageHeader(char *&aMsg, size_t &iMsgLen, unsigned int &iServerMsgCount);
    static bool DecryptMessage(unsigned int *laKey, size_t iInputLen, char *aInputMsg, size_t &iOutputLen, char *&aOutputMsg);
    static bool EncryptMessage(unsigned int *laKey, size_t iInputLen, char *aInputMsg, size_t &iOutputLen, char *&aOutputMsg);
private:
    static void GetRealMessageLength(size_t iMsgLen, size_t &iRealMsgLen, char *&aMsg);
    static void SetRealMessageLength(size_t &iMsgLen, char *&aMsg);
};


#define XOR_SUCCESS_MARK 1

class XCommunicationEncryption {
public:
    static void XorDecrypt(size_t &iXorLength, char *&aXorArray);
    static void XorEncrypt(size_t &iXorLength, char *&aXorArray);
    static void CheckXorMark(size_t &iXorLength, char *&aXorArray);
    static void SetXorMark(size_t &iXorLength, char *&aXorArray);
};

#endif
