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

#include "XRegen.h"

/*bool XRegen::LoadRegenMap(const char szPath)
{
	FILE *FSettings = fopen(szPath, "r");
	char szLine[1024], *szToken;
	
	if(!FSettings)
	{
		syserr(__FUNCTION__, __LINE__, "Impossible to load the map %s", strcat(szDirectory, "SETTINGS"));
		return false;
	}
	
	while(fgets(szLine, 1024, FSettings))
	{
        XNPC *xNPC = new XNPC();
		
		if((szToken = strtok(szLine, " \t")) == NULL || !is_number(szToken)) continue; else SRegen.NetworkID = atoi(szToken);
		if((szToken = strtok(NULL  , " \t")) == NULL || !is_number(szToken)) continue; else SRegen.MobID = atoi(szToken);
        if((szToken = strtok(NULL  , " \t")) == NULL || !is_number(szToken)) continue; else SRegen.X = atof(szToken);
		if((szToken = strtok(NULL  , " \t")) == NULL || !is_number(szToken)) continue; else SRegen.Y = atof(szToken);
		if((szToken = strtok(NULL  , " \t")) == NULL || !is_number(szToken)) continue; else SRegen.Z = atof(szToken);
		if((szToken = strtok(NULL  , " \t")) == NULL || !is_number(szToken)) continue; else SRegen.R = atof(szToken);
		
		vRegenNPC.push_back(SRegen);
	}
}
*/
