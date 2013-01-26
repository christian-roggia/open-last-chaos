/******************************************************************************************
  Copyright 2013 Andrea Ragusa

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

#include "common.hpp"

class CGuild;

class CGuildMember{
public:
    CGuildMember();
    ~CGuildMember();
    int charindex();
    const char *name();
    int pos();
    CGuild *guild();
    char online();
    void charindex(int a2);
    void name(const char *src);
    void pos(int a2);
    void guild(CGuild *guild);
    int listindex();
    void listindex(int a2);
    void online(char a2);
private:
    int vCharIndex;
    char vName[52];
    int vPosition;
    CGuild *vGuild;
    int vListIndex;
    char vOnline[4];
};
