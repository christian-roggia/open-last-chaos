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

#ifndef __X_CHARACTER__
#define __X_CHARACTER__

class XDESC;

class XCharacter {
public:
	int iIndex;
	char szName[32], eClass, eJob, eHair, eFace;
	int iLevel;
	long long iCurrentExp;
	int iSkillPoint;
    int iCurrentHP, iCurrentMP, iBoostedMaxHP, iBoostedMaxMP;
	int iStrength, iDexterity, iIntelligence, iConstitution;
	float RunSpeed, WalkSpeed;

	float X, Y, Z, R;
	int iMapIndex;
	
public:
	XCharacter(void);
	~XCharacter(void);
	
	void SetPosition(float X, float Y, float Z, float R);
    void SendAppearMessage(XCharacter *xCharacter);
    virtual unsigned char GetType(void) { return 0; }
};

#endif
