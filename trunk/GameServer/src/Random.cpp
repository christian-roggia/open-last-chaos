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

unsigned long seed = 0;

void ServerSrandom(unsigned long m_seed) { seed = m_seed; }
int ServerRandom(void) { return 0x41A7 * seed % 0x1F31D - 0xB14 * seed / 0x1F31D <= 0 ?
                              seed = (0x41A7 * seed % 0x1F31D - 0xB14 * seed / 0x1F31D <= 0) + 0x7FFFFFFF :
                              seed = 0x41A7 * seed % 0x1F31D - 0xB14 * seed / 0x1F31D; }

unsigned int GetRandom(int m_min, int m_max)
{
    int m_temp;

    if(m_min > m_max)
    {
        m_temp = m_min;
        m_min = m_max;
        m_max = m_temp;
    }
	
    return m_min + ServerRandom() % (unsigned int)(m_max - m_min + 1);
}
