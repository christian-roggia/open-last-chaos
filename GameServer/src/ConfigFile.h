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

#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include "Utils.h"

/*******************************
NOTE: int CConfigFile::NextToken(char *,char const *,int &,char const *);
- Function not required
*******************************/

class CConfigFileData;
class CConfigFile;

class CConfigFileData {
private:
    char CGroup[256], CName[256], CValue[256]; // +0, +256, +512
public:
    CConfigFileData(void)   {}
    ~CConfigFileData()      {}

    void Set(char const *m_group, char const *m_name, char const *m_value)
    {
        strcpy(this->CGroup, m_group);
        strcpy(this->CName, m_name);
        strcpy(this->CValue, m_value);
    }

    char *Value(void)   { return this->CValue; }
    char *Group(void)   { return this->CGroup; }
    char *Name(void)    { return this->CName; }
};

class CConfigFile {
private:
    CConfigFileData *Configs[1024]; // +0
    long Count;                     // +4096
public:
    CConfigFile(void);
    ~CConfigFile();
	
    bool Load(char const *f_name, bool isEncrypted);
    bool Load(char const *data, int size);
    bool Add(char const *config, char const *property, char const *value);
    void Sort(void);
    char *Find(char const *group, char const *name);
    static int Comp(const void *c_data1, const void *c_data2);
    //int CConfigFile::NextToken(char *,char const *,int &,char const *);
};

#endif
