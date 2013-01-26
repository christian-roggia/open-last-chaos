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

#ifndef INPUT_MAIN_H
#define INPUT_MAIN_H

#include "XDESC.h"
#include "input.h"

class CInputMain : public CInputProcessor {
public:
    CInputMain();

    virtual int Analyze(XDESC *descriptor, unsigned char header, const char *data, int len);
    virtual unsigned char GetType(void) { return IP_TYPE_MAIN; }
};

#endif // INPUT_MAIN_H
