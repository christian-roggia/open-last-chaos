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

#ifndef __X_DES__
#define __X_DES__

#include <stdio.h>
#include <memory.h>

#define XDES_ENCRYPT 1
#define XDES_DECRYPT 0

class XDES {
public:
	static void deskey(unsigned long *lkey, short edf);
	static void des(unsigned char *inblock, unsigned char *outblock);
private:
	static void cookey(unsigned long *raw1);
	static void usekey(unsigned long *from);
	static void scrunch(unsigned char *outof, unsigned long *into);
	static void unscrun(unsigned long *outof, unsigned char *into);
	static void desfunc(unsigned long *block, unsigned long *keys);
};

class XDESManager {
public:
    static void DESCryptography(unsigned int *laKey, short sMode, char *aInputData, size_t iInputLen, char *&aOutputData, size_t &iOutputLen);
	static void NextDESKey(unsigned int *key);
	static void ResetDESKey(unsigned int *key);
	static void ElaborateDESKey(unsigned int *key, unsigned int seed);
};

#endif
