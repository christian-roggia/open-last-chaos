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

#ifndef __X_PACK__
#define __X_PACK__

#include "XCommunicationProtocol.h"
#include "Utils.h" // Only for ntohll()

class XPack {
public:
    XPack(void) : XPackPointer(0), XPackLimit(0) { }
    ~XPack(void) { }

    XPack(unsigned char XPackType) : XPackPointer(1), XPackLimit(0)
	{
		XPackData[0] = XPackType;
    }
	
    XPack(unsigned char XPackType, unsigned char XPackSubType) : XPackPointer(2), XPackLimit(0)
	{
		XPackData[0] = XPackType;
		XPackData[1] = XPackSubType;
	}
	
    XPack(unsigned char XPackType, unsigned char XPackSubType, unsigned char XPackSubSubType) : XPackPointer(3), XPackLimit(0)
	{
		XPackData[0] = XPackType;
		XPackData[1] = XPackSubType;
		XPackData[2] = XPackSubSubType;
	}

    XPack(const char *XPackMessage, int XPackLength) : XPackPointer(0), XPackLimit(XPackLength)
    {
        memcpy(this->XPackData, XPackMessage, XPackLength);
        this->XPackData[XPackLength] = 0;
    }
	
	XPack &operator<<(const char XPackValue);
	XPack &operator<<(const short XPackValue);
	XPack &operator<<(const int XPackValue);
	XPack &operator<<(const long XPackValue);
	XPack &operator<<(const long long XPackValue);
	
	XPack &operator<<(const unsigned char XPackValue);
	XPack &operator<<(const unsigned short XPackValue);
	XPack &operator<<(const unsigned int XPackValue);
	XPack &operator<<(const unsigned long XPackValue);
	XPack &operator<<(const unsigned long long XPackValue);
	
	XPack &operator<<(const float XPackValue);
	XPack &operator<<(const double XPackValue);
	
    XPack &operator<<(const char *XPackValue);


    XPack &operator>>(char &XPackValue);
    XPack &operator>>(short &XPackValue);
    XPack &operator>>(int &XPackValue);
    XPack &operator>>(long &XPackValue);
    XPack &operator>>(long long &XPackValue);

    XPack &operator>>(unsigned char &XPackValue);
    XPack &operator>>(unsigned short &XPackValue);
    XPack &operator>>(unsigned int &XPackValue);
    XPack &operator>>(unsigned long &XPackValue);
    XPack &operator>>(unsigned long long &XPackValue);

    XPack &operator>>(float &XPackValue);
    XPack &operator>>(double &XPackValue);

    XPack &operator>>(char *&XPackValue);
    XPack &operator>>(char (&XPackValue)[XCP_MAX_STRING_LENGTH]);
	
    char *GetPackData(void)    { return this->XPackData; }
    int   GetPackPointer(void) { return this->XPackPointer; }
    int   GetPackLength(void)  { return this->XPackLimit ? this->XPackLimit : this->XPackPointer; }
    int   GetPackRemain(void)  { return this->XPackLimit ? (this->XPackLimit - this->XPackPointer) : (XCP_MAX_RAW_LEN - this->XPackPointer); }
    void  ResetPointer(void)   { this->XPackPointer = 0; }
    void  ResetBuffer(void)    { this->XPackPointer = 0; memset(XPackData, 0, XCP_MAX_RAW_LEN); }
    void  Clear(void)          { this->XPackPointer = 0; memset(XPackData, 0, XCP_MAX_RAW_LEN); this->XPackLimit = 0; }
private:
    char XPackData[XCP_MAX_RAW_LEN];
    int XPackPointer;
    int XPackLimit;
};

#endif
