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

#ifndef __X_MAP__
#define __X_MAP__

#include <vector>
#include <fstream>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "log.h"

class XCharacter;

using namespace std;

class XMap {
public:
	XMap();
	~XMap();
	
    bool LoadMap(const char *szDirectory);
	void CharacterEnterMap(XCharacter *xCharacter, float X, float Y);
	void CharacterMove(XCharacter *xCharacter, float X, float Y);
	void CharacterDisconnect(XCharacter *xCharacter, float X, float Y);
	
public:
	int iIndex, iHeight, iWidth;
    vector<XCharacter *> vCharacters;
    //XRegen xRegen;
	bool bIsEnable;
};

#endif
