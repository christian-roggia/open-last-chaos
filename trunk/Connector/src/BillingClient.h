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

#ifndef BILLINGCLIENT_H
#define BILLINGCLIENT_H


#include "Log.h"
#include "Utils.h"

class CServer;

class CBillingClient {
public:
        bool isTrying;     // + 0
        bool isRunning;    // + 1
        bool Unk2;         // + 2
        long Unk4;         // + 4
        int Socket;        // + 8
public:
	CBillingClient(void);
	
    bool IsRunning(void) { return this->isRunning; }
    bool IsTrying(void)  { return this->isTrying; }
	bool Create(void);
	void Close(void);
	static void BillingConnect(void *m_ptr);
	void SendHeader(void) {}
	bool Login(char const *,char const *,char const *) { return true; }
	bool Logout(char const *) { return true; }
	void ProcessBilling(void) {}
	bool ProcessInput(void) { return true; }
	bool ProcessInputQueue(void) { return false; }
	bool ProcessOutput(void) { return true; }
};

#endif
