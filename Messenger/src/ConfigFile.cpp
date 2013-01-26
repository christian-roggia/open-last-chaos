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
#include "Utils.hpp"
#include "ConfigFile.hpp"


CConfigFile::CConfigFile(void)
{
    for(long i = 0; i <= 1023; ++i)
        this->p_conf_data[i] = 0;

    this->p_conf_data_counter = 0;
}

CConfigFile::~CConfigFile()
{
    for(long i = 0; i <= 1023; ++i)
        delete this->p_conf_data[i];
    this->p_conf_data_counter = 0;
}

bool CConfigFile::Load(char const *f_name)
{
    uint32_t size;
    char *data;
    FILE *s_file;
    s_file = fopen(f_name, "rb");

    if(!s_file)
        return false;

    fseek(s_file, 0, SEEK_END);
    size = ftell(s_file);
    fseek(s_file, 0, SEEK_SET);
    data = (char *)malloc(size);
    fread(data, 1, size, s_file);
    fclose(s_file);

    //if(isEncryptedMem)
    //DecryptMem(data, size);

    this->Load(data, size);

    if(data)
        free(data);

    return true;
}

bool CConfigFile::Load(char const *data, uint32_t size)
{
    char group[1024], name[1024], value[1024];
    uint32_t counter = 0, c_group = 0, c_name = 0, c_value = 0;

RESTART:
    while (counter < size)
    {
        if (!strchr("\t\r\n ", data[counter]))
        {
            if (data[counter] == 0x5b)
            {
                ++counter;
                c_group = 0;
                memset(group, 0, 1024);
                while(counter < size && c_group < 1024)
                {
                    if(data[counter] == 0x5d)
                    {
                        ++counter;
                        group[c_group++] = 0;
                        goto RESTART;
                    }

                    group[c_group++] = data[counter++];
                }
            }
            else
            {
                if (data[counter] == 0x3b)
                {
                    while (counter < size)
                    {
                        if (strchr("\r\n", data[counter]))
                        {
                            ++counter;
                            goto RESTART;
                        }

                        ++counter;
                    }
                }
                else
                {
                    c_name = 0;
                    memset(name, 0, 0x400);
                    while (counter < size && c_name < 1024)
                    {
                        if (data[counter] == 0x3d)
                        {
                            ++counter;
                            name[c_name++] = 0;
                            c_value = 0;
                            memset(value, 0, 0x400);
                            while (counter < size && c_value < 1024)
                            {
                                if (strchr("\r\n", data[counter]))
                                {
                                    ++counter;
                                    break;
                                }

                                value[c_value++] = data[counter++];
                            }

                            value[c_value++] = 0;
                            if (name)
                            {
                                if (value)
                                    this->Add(group, name, value);
                            }

                            goto RESTART;
                        }

                        name[c_name++] = data[counter++];
                    }
                }
            }

            return 1;
        }

        ++counter;
    }
    return 1;
}

bool CConfigFile::Add(char const *group, char const *name, char const *value)
{
    char *src_value = this->Find(group, name);

    if(src_value)
    {
        //strcpy((char *)src_value, value);
        return true;
    }

    if(this->p_conf_data_counter == 1024)
        return false;
    this->p_conf_data[this->p_conf_data_counter] = new CConfigFileData();
    this->p_conf_data[this->p_conf_data_counter++]->Set(group, name, value);
    this->Sort();

    return true;
}

void CConfigFile::Sort(void)
{
    if(this->p_conf_data_counter > 1)
        qsort(this->p_conf_data, this->p_conf_data_counter, 4, CConfigFile::Comp);
}

char *CConfigFile::Find(char const *group, char const *name)
{
    CConfigFileData *c_data = new CConfigFileData();
    void *src_data_ptr;

    c_data->Set(group, name, "");
    src_data_ptr = bsearch(&c_data, this->p_conf_data, this->p_conf_data_counter, 4, CConfigFile::Comp);

    delete c_data;

    return src_data_ptr ? (*(CConfigFileData **)src_data_ptr)->Value() : 0;
}

int CConfigFile::Comp(const void *c_data1, const void *c_data2)
{
    uint32_t cmp_group = 0, cmp_name = 0;

    if(&c_data1 == &c_data2)
        return 0;

    if(!c_data1 || !c_data2)
        return -1;

    cmp_group = strcmp((*(CConfigFileData **)c_data1)->Group(), (*(CConfigFileData **)c_data2)->Group());
    if(cmp_group)
        return cmp_group;

    cmp_name = strcmp((*(CConfigFileData **)c_data1)->Name(), (*(CConfigFileData **)c_data2)->Name());
    if(cmp_name)
        return cmp_name;

    return 0;
}

/*int CConfigFile::NextToken(char *,char const *,int &,char const *)
{
    int result; // eax@24
    char i; // [sp+12h] [bp-6h]@11
    char v6; // [sp+13h] [bp-5h]@11
    int v7; // [sp+14h] [bp-4h]@1
    int *v8; // [sp+24h] [bp+Ch]@1

    v7 = a1;
    v8 = (int *)(*(_DWORD *)a3 + a2);
    while ( *(_BYTE *)v8 )
    {
        if ( s )
        {
            if ( !strchr(s, *(_BYTE *)v8) )
                break;
        }
        else
        {
            if ( !strchr("\r\n\t ", *(_BYTE *)v8) )
                break;
        }
        v8 = (int *)((char *)v8 + 1);
        ++*(_DWORD *)a3;
    }
    v6 = 0;
    for ( i = 0; *(_BYTE *)v8; i = 1 )
    {
        if ( s )
        {
            if ( strchr(s, *(_BYTE *)v8) )
                v6 = 1;
        }
        else
        {
            if ( strchr("\r\n\t ", *(_BYTE *)v8) )
                v6 = 1;
        }
        if ( v6 )
            break;
        *(_BYTE *)a1 = *(_BYTE *)v8;
        v8 = (int *)((char *)v8 + 1);
        ++a1;
        ++*(_DWORD *)a3;
    }
    *(_BYTE *)a1 = 0;
    if ( i )
        result = v7;
    else
        result = 0;
    return result;
}*/
