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

#include "XMap.h"
#include "XCharacter.h"

XMap::XMap()
	: iIndex(-1), iHeight(-1), iWidth(-1), bIsEnable(false)
{

}

XMap::~XMap()
{
	vCharacters.clear();
}

bool XMap::LoadMap(const char *szDirectory)
{
	char szLine[1024], szPoolPath[256], *szSetting, *szValue;
    FILE *FSettings;
	
	strncpy(szPoolPath, szDirectory, 256);
    FSettings = fopen(strcat(szPoolPath, "SETTINGS"), "r");
	
	if(!FSettings)
	{
        sys_err(__FUNCTION__, __LINE__, "Impossible to load the map %s", szPoolPath);
		return false;
	}
	
	while(fgets(szLine, 1024, FSettings))
	{
		szSetting = strcln(strtok(szLine, " \t"));
        szValue   = strcln(strtok(NULL, " \t"));
		
		if(!strcasecmp(szSetting, "INDEX"))             this->iIndex = atoi(szValue);
		else if(!strcasecmp(szSetting, "ENABLED"))      this->bIsEnable = strcmp(szValue, "1") == 0;
		else if(!strcasecmp(szSetting, "HEIGHT"))       this->iHeight = atoi(szValue);
		else if(!strcasecmp(szSetting, "WIDTH"))        this->iWidth = atoi(szValue);
		
		//else if(!strcasecmp(szSetting, "HEIGHTMAP"))    this->LoadHeightMap(strcat(szPoolPath, szValue));
		//else if(!strcasecmp(szSetting, "ATTRIBUTEMAP")) this->LoadAttributeMap(strcat(szPoolPath, szValue));
		//else if(!strcasecmp(szSetting, "REGEN_NPC"))    this->LoadRegenMap(strcat(szPoolPath, szValue));
		//else if(!strcasecmp(szSetting, "REGEN_MOB"))    this->LoadRegenMap(strcat(szPoolPath, szValue));
		//else if(!strcasecmp(szSetting, "REGEN_BOSS"))   this->LoadRegenMap(strcat(szPoolPath, szValue));
	}

    fclose(FSettings);
}

void XMap::CharacterEnterMap(XCharacter *xCharacter, float X, float Y)
{
	for(int i = 0; i < vCharacters.size(); i++)
	{
		int X2 = vCharacters.at(i)->X, Y2 = vCharacters.at(i)->Y, RX = X2 - X, RY = Y2 - Y;
        if(sqrt(RX*RX + RY*RY) < 12.f && vCharacters.at(i) != xCharacter)
		{
			vCharacters.at(i)->SendAppearMessage(xCharacter);
			xCharacter       ->SendAppearMessage(vCharacters.at(i));
		}
	}
	
	vCharacters.push_back(xCharacter);
}

void XMap::CharacterMove(XCharacter *xCharacter, float X, float Y)
{
	for(int i = 0; i < vCharacters.size(); i++)
	{
		int X2 = vCharacters.at(i)->X, Y2 = vCharacters.at(i)->Y, RX = X2 - X, RY = Y2 - Y;
        if(sqrt(RX*RX + RY*RY) < 12.f && vCharacters.at(i) != xCharacter)
		{
			vCharacters.at(i)->SendAppearMessage(xCharacter);
			xCharacter       ->SendAppearMessage(vCharacters.at(i));
		}
	}
}

void XMap::CharacterDisconnect(XCharacter *xCharacter, float X, float Y)
{
    int x = -1;

	for(int i = 0; i < vCharacters.size(); i++)
	{
        //int X2 = vCharacters.at(i)->X, Y2 = vCharacters.at(i)->Y, RX = X2 - X, RY = Y2 - Y;

        //if(sqrt(RX*RX + RY*RY) < 12.f && vCharacters.at(i) != xCharacter) vCharacters.at(i)->SendDisppearMessage(xCharacter);
        if(vCharacters.at(i) == xCharacter) x = i;
	}

    if(x != -1) vCharacters.erase(vCharacters.begin() + x);
}
