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

long long gLevelupExp[80];

void InitExp(void)
{
    long long v6 = 0;

    gLevelupExp[0] = 36;
    gLevelupExp[1] = 130;
    gLevelupExp[2] = 415;
    gLevelupExp[3] = 1161;
    gLevelupExp[4] = 2787;
    gLevelupExp[5] = 5853;
    gLevelupExp[6] = 10535;
    gLevelupExp[7] = 16855;
    gLevelupExp[8] = 23597;

    for(long long i = 9; i <= 58 && i <= 79; ++i)
    {
        gLevelupExp[i] = ((((i + 1) * (i + 1) * (i + 1) * (i + 1)) / 8 + 1999) * ((i + 1) * (i + 1))) / 10; // TO CHECK... 90% IS WRONG
        v6 += gLevelupExp[i];
    }

    for(long long j = 59; j <= 79; ++j)
    {
        gLevelupExp[j] = v6;
        v6 *= 2; // TO CHECK...
    }
}

long long GetLevelupExp(int m_level)
{
    int m_deltaLevel = m_level - 1;

    if(m_deltaLevel >= 0)
    {
        if(m_deltaLevel > 79)
            m_deltaLevel = 79;

        return gLevelupExp[m_deltaLevel];
    }

    return 0;
}
