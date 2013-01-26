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

#include "Random.hpp"

uint32_t seed;

void ServerSrandom(uint32_t s)
{
  seed = s;
}

int ServerRandom()
{
  unsigned int tmp; // [sp+1Ch] [bp-Ch]@1

  tmp = 16807 * seed % 0x1F31Du - 2836 * seed / 0x1F31Du;
  if ( (signed int)tmp <= 0 )
    seed = tmp + 2147483647;
  else
    seed = 16807 * seed % 0x1F31Du - 2836 * seed / 0x1F31Du;
  return seed;
}

unsigned int GetRandom(int v1, int v2)
{
  int tmp;

  if ( v1 > v2 )
  {
    tmp = v1;
    v1 = v2;
    v2 = tmp;
  }
  return v1 + ServerRandom() % (unsigned int)(v2 - v1 + 1);
}
