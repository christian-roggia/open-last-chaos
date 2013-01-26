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

#ifndef INPUT_AUTH_H
#define INPUT_AUTH_H

#include "input.h"
#include "XDESC.h"
#include "XPack.h"
#include "XConstants.h"
#include "XPC.h"
#include "input_main.h"
#include "Utils.h"

#include <stdlib.h>
#include <time.h>

#define P_HEADER_LOGIN 3

class CInputAuth : public CInputProcessor {
public:
    CInputAuth() {}
    virtual ~CInputAuth() {}

    virtual int Analyze(XDESC *descriptor, unsigned char header, const char *data, int len);
    virtual unsigned char GetType(void) { return IP_TYPE_AUTH; }

    void RecvLoginMessage(XDESC *xDesc, const char *data, int len);
    void RecvMove(XDESC *xDesc, const char *data, int len);
    void RecvAliveMessage(XDESC *xDesc, const char *data, int len);

    void SendCharacterSelectionScreen(XDESC *xDesc);
    void SendServerListMessage(XDESC *xDesc);
    void SendCharacterInfo(XDESC *xDesc);
    void SendSelectMapIndex(XDESC *xDesc);
    void SendAtMessage(XDESC *xDesc);
    void SendStatusMessage(XDESC *xDesc);
    void SendStatPointsFree(XDESC *xDesc);
    void SendGameTime(XDESC *xDesc);

    void SendAppearMessage(XDESC *xDesc, int NetworkID, int MobIndex, float X, float Y, float Z, float R);
    void SendMobAppearMessage(XPack &xPacket, int NetworkID, int MobIndex, float X, float Y, float Z, float R);
};

#endif // INPUT_AUTH_H
