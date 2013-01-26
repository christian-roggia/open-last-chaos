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

#ifndef POS_H
#define POS_H

class CPos;

class CPos {
public:
    float Unk0; // X
    float Unk4; // Y
    float Unk8; // YLayer
    float Unk12; // R
    char Unk16;
public:
    CPos(void);
    CPos(float a2, float a3, float a4, float a5, int a6);

    void __as(CPos const &a2);
};

#endif // POS_H
