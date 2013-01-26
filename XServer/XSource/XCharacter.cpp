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

#include "XCharacter.h"
#include "Server.h"

XCharacter::XCharacter(void)
{
}

XCharacter::~XCharacter(void)
{
}

void XCharacter::SetPosition(float X, float Y, float Z, float R)
{
	this->X = X;
	this->Y = Y;
	this->Z = Z;
	this->R = R;
	
	gserver.xMaps.at(0)->CharacterMove(this, X, Y);
}

void XCharacter::SendAppearMessage(XCharacter *xCharacter)
{
    if(this->GetType() == 1) ((CInputAuth *)((XPC *)this)->xDesc->Input)->SendAppearMessage(((XPC *)this)->xDesc, 1, 1, xCharacter->X, xCharacter->Y, xCharacter->Z, xCharacter->R);
}
