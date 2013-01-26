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

#include "XPack.h"

XPack &XPack::operator<<(const char XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > XCP_MAX_RAW_LEN) return *this;
	
    *(char *)&this->XPackData[this->XPackPointer] = XPackValue;
	this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator<<(const short XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > XCP_MAX_RAW_LEN) return *this;
	
	*(short *)&this->XPackData[this->XPackPointer] = htons(XPackValue);
	this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator<<(const int XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > XCP_MAX_RAW_LEN) return *this;
	
	*(int *)&this->XPackData[this->XPackPointer] = htonl(XPackValue);
	this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator<<(const long XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > XCP_MAX_RAW_LEN) return *this;
	
	*(long *)&this->XPackData[this->XPackPointer] = htonl(XPackValue);
	this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator<<(const long long XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > XCP_MAX_RAW_LEN) return *this;
	
    *(long long *)&this->XPackData[this->XPackPointer] = htonll(XPackValue);
	this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator<<(const unsigned char XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > XCP_MAX_RAW_LEN) return *this;
	
    *(unsigned char *)&this->XPackData[this->XPackPointer] = XPackValue;
	this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator<<(const unsigned short XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > XCP_MAX_RAW_LEN) return *this;
	
	*(unsigned short *)&this->XPackData[this->XPackPointer] = htons(XPackValue);
	this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator<<(const unsigned int XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > XCP_MAX_RAW_LEN) return *this;
	
	*(unsigned int *)&this->XPackData[this->XPackPointer] = htonl(XPackValue);
	this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator<<(const unsigned long XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > XCP_MAX_RAW_LEN) return *this;
	
	*(unsigned long *)&this->XPackData[this->XPackPointer] = htonl(XPackValue);
	this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator<<(const unsigned long long XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > XCP_MAX_RAW_LEN) return *this;
	
    *(unsigned long long *)&this->XPackData[this->XPackPointer] = htonll(XPackValue);
	this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator<<(const float XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > XCP_MAX_RAW_LEN) return *this;
	
	*(float *)&this->XPackData[this->XPackPointer] = XPackValue;
	this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator<<(const double XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > XCP_MAX_RAW_LEN) return *this;
	
	*(double *)&this->XPackData[this->XPackPointer] = XPackValue;
	this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator<<(const char *XPackValue)
{
    if(this->XPackPointer + strlen(XPackValue) + sizeof(char) > XCP_MAX_RAW_LEN) return *this;
	
    strcpy(&this->XPackData[this->XPackPointer], XPackValue);
	this->XPackPointer += strlen(XPackValue);
	
    this->XPackData[this->XPackPointer] = 0;
    this->XPackPointer += sizeof(char);

    return *this;
}

XPack &XPack::operator>>(char &XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > this->XPackLimit) return *this;

    XPackValue = *(char *)&this->XPackData[this->XPackPointer];
    this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator>>(short &XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > this->XPackLimit) return *this;

    XPackValue = (short)htons(*(unsigned short *)&this->XPackData[this->XPackPointer]);
    this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator>>(int &XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > this->XPackLimit) return *this;

    XPackValue = (int)htonl(*(unsigned long *)&this->XPackData[this->XPackPointer]);
    this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator>>(long &XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > this->XPackLimit) return *this;

    XPackValue = (long)htonl(*(unsigned long *)&this->XPackData[this->XPackPointer]);
    this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator>>(long long &XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > this->XPackLimit) return *this;

    XPackValue = (long long)htonll(*(unsigned long long *)&this->XPackData[this->XPackPointer]);
    this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator>>(unsigned char &XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > this->XPackLimit) return *this;

    XPackValue = *(unsigned char *)&this->XPackData[this->XPackPointer];
    this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator>>(unsigned short &XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > this->XPackLimit) return *this;

    XPackValue = (unsigned short)htons(*(unsigned short *)&this->XPackData[this->XPackPointer]);
    this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator>>(unsigned int &XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > this->XPackLimit) return *this;

    XPackValue = (unsigned int)htonl(*(unsigned long *)&this->XPackData[this->XPackPointer]);
    this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator>>(unsigned long &XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > this->XPackLimit) return *this;

    XPackValue = (unsigned long)htonl(*(unsigned long *)&this->XPackData[this->XPackPointer]);
    this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator>>(unsigned long long &XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > this->XPackLimit) return *this;

    XPackValue = (unsigned long long)htonll(*(unsigned long long *)&this->XPackData[this->XPackPointer]);
    this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator>>(float &XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > this->XPackLimit) return *this;

    XPackValue = *(float *)&this->XPackData[this->XPackPointer];
    this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator>>(double &XPackValue)
{
    if(this->XPackPointer + sizeof(XPackValue) > this->XPackLimit) return *this;

    XPackValue = *(double *)&this->XPackData[this->XPackPointer];
    this->XPackPointer += sizeof(XPackValue);

    return *this;
}

XPack &XPack::operator>>(char *&XPackValue)
{
    if(this->XPackPointer + strlen(this->XPackData) > this->XPackLimit) return *this;

    strncpy(XPackValue, &this->XPackData[this->XPackPointer], XCP_MAX_STRING_LENGTH - sizeof(char));
    this->XPackPointer += strlen(&this->XPackData[this->XPackPointer]);

    XPackValue[strlen(XPackValue)] = 0;
    this->XPackPointer += sizeof(char);

    return *this;
}

XPack &XPack::operator>>(char (&XPackValue)[XCP_MAX_STRING_LENGTH])
{
    if(this->XPackPointer + strlen(this->XPackData) > this->XPackLimit) return *this;

    strncpy(XPackValue, &this->XPackData[this->XPackPointer], XCP_MAX_STRING_LENGTH - sizeof(char));
    this->XPackPointer += strlen(&this->XPackData[this->XPackPointer]);

    XPackValue[strlen(XPackValue)] = 0;
    this->XPackPointer += sizeof(char);

    return *this;
}
