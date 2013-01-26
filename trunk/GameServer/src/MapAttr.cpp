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

#include "MapAttr.h"
#include "Server.h"

CMapAttr::CMapAttr(void)
{
    this->Unk4 = 0;
    this->Unk0 = 0;
    this->Unk8 = 0;
    this->Unk12 = 0;
}

CMapAttr::~CMapAttr()
{
    if(this->Unk8)
    {
        for(int i = 0; i < this->Unk0; ++i)
        {
            if(this->Unk8[i])
                delete [] this->Unk8[i];
        }

        delete [] this->Unk8;
        this->Unk8 = 0;
    }

    if(this->Unk12)
    {
        for(int j = 0; j < this->Unk0; ++j)
        {
            if(this->Unk12[j])
                delete [] this->Unk12[j];
        }

        delete [] this->Unk12;
        this->Unk12 = 0;
    }
}

bool CMapAttr::Load(int a2, int a3, int a4, int a5, char const *filename, char const *a7)
{
    short netshort; // [sp+54h] [bp-42Ch]@17
    char ptr; // [sp+57h] [bp-429h]@16
    char s[1024]; // [sp+68h] [bp-418h]@1
    FILE *v20; // [sp+468h] [bp-18h]@3
    FILE *stream; // [sp+46Ch] [bp-14h]@1

    g_gamelogbuffer.__ls(init("SYSTEM"));
    g_gamelogbuffer.__ls("Attribute File Reading ");
    g_gamelogbuffer.__ls((int)a3);
    g_gamelogbuffer.__ls(end);

    sprintf(s, "%s%s", gserver.Unk36900, filename);
    stream = fopen(filename, "rb");

    if(!stream)
        return false;

    sprintf(s, "%s%s", gserver.Unk36900, a7);
    v20 = fopen(a7, "rb");
    if(!v20)
    {
      fclose(stream);
      return false;
    }

    char  **v16 = new char *[a4]; // CHECK!!!!
    float **v15 = new float*[a4]; // CHECK!!!!

    for(int i = 0; i < a4; i++)
    {
        v16[i] = new char [a5];
        v15[i] = new float[a5];
    }

    bool v12 = false;
    for(int j = 0; !v12 && j < a5; ++j)
    {
        for(int i = 0; !v12 && i < a4; ++i)
        {
          if(!fread(&ptr, 1, 1, stream) || !fread(&netshort, 2, 1, v20))
          {
              v12 = true;
              break;
          }

          switch(ptr)
          {
          case 0:
              v16[i][j] = 0;
              break;
          case 10:
              v16[i][j] = 10;
              break;
          case 20:
              v16[i][j] = 20;
              break;
          case 30:
              v16[i][j] = 30;
              break;
          case 40:
              v16[i][j] = 40;
              break;
          case 50:
              v16[i][j] = 50;
              break;
          default:
              v16[i][j] = -1;
              break;
          }

          v15[i][j] = (long double)ntohs(netshort) / 100.0;
        }
    }

    fclose(stream);
    fclose(v20);

    if(v12)
    {
        for(int i = 0; i < a4; ++i)
        {
            if(v16[i] && v16[i]) delete [] v16[i];
            if(v15[i] && v15[i]) delete [] v15[i];
        }

        if(v16) delete [] v16;
        if(v15) delete [] v15;

        return false;
    }

    this->Unk0  = a4;
    this->Unk4  = a5;
    this->Unk8  = v16;
    this->Unk12 = v15;

    return true;
}
