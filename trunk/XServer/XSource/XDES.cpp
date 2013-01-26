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

#include "XDES.h"

static unsigned long KnL[32] = { 0L };

/*static unsigned short bytebit[8]	= {
    0200, 0100, 040, 020, 010, 04, 02, 01 };*/

static unsigned char bytebit[16] 	= {
    1, 0, 2, 0, 4, 0, 8, 0, 0x10, 0, 0x20, 0, 0x40, 0, 0x80 };

static unsigned long bigbyte[24] = {
	0x800000L,	0x400000L,	0x200000L,	0x100000L,
	0x80000L,	0x40000L,	0x20000L,	0x10000L,
	0x8000L,	0x4000L,	0x2000L,	0x1000L,
	0x800L, 	0x400L, 	0x200L, 	0x100L,
	0x80L,		0x40L,		0x20L,		0x10L,
	0x8L,		0x4L,		0x2L,		0x1L	};

/* Use the key schedule specified in the Standard (ANSI X3.92-1981). */

static unsigned char pc1[56] = {
	56, 48, 40, 32, 24, 16,  8,	 0, 57, 49, 41, 33, 25, 17,
	 9,  1, 58, 50, 42, 34, 26,	18, 10,  2, 59, 51, 43, 35,
	62, 54, 46, 38, 30, 22, 14,	 6, 61, 53, 45, 37, 29, 21,
	13,  5, 60, 52, 44, 36, 28,	20, 12,  4, 27, 19, 11,  3 };

static unsigned char totrot[16] = {
	1,2,4,6,8,10,12,14,15,17,19,21,23,25,27,28 };

static unsigned char pc2[48] = {
	13, 16, 10, 23,  0,  4,  2, 27, 14,  5, 20,  9,
	22, 18, 11,  3, 25,  7, 15,  6, 26, 19, 12,  1,
	40, 51, 30, 36, 46, 54, 29, 39, 50, 44, 32, 47,
	43, 48, 38, 55, 33, 52, 45, 41, 49, 35, 28, 31 };

void XDES::deskey(unsigned long *lkey,short edf)	/* Thanks to James Gillogly & Phil Karn! */
{
    register int i, j, l, m, n;
    unsigned char pc1m[56], pcr[56], key[8];
    unsigned long kn[32];

    unscrun(lkey, key);

    for ( j = 0; j < 56; j++ ) {
        l = pc1[j];
        m = l & 07;
        pc1m[j] = (key[l >> 3] & bytebit[2*m]) ? 1 : 0;
        }

    for( i = 0; i < 16; i++ ) {
        if( edf == XDES_DECRYPT ) m = (15 - i) << 1;
        else m = i << 1;
		n = m + 1;
        kn[m] = kn[n] = 0L;
        for( j = 0; j < 28; j++ ) {
			l = j + totrot[i];
			if( l < 28 ) pcr[j] = pc1m[l];
			else pcr[j] = pc1m[l - 28];
            }
        for( j = 28; j < 56; j++ ) {
		    l = j + totrot[i];
		    if( l < 56 ) pcr[j] = pc1m[l];
		    else pcr[j] = pc1m[l - 28];
            }
        for( j = 0; j < 24; j++ ) {
			if( pcr[pc2[j]] ) kn[m] |= bigbyte[j];
			if( pcr[pc2[j+24]] ) kn[n] |= bigbyte[j];
            }
        }

    cookey(kn);
	return;
	}

void XDES::cookey(unsigned long *raw1)
{
	register unsigned long *cook, *raw0;
	unsigned long dough[32];
	register int i;

	cook = dough;
	for( i = 0; i < 16; i++, raw1++ ) {
		raw0 = raw1++;
		*cook	 = (*raw0 & 0x00fc0000L) << 6;
		*cook	|= (*raw0 & 0x00000fc0L) << 10;
        *cook	|= (*raw1 & 0x00fc0000L) >> 10;
		*cook++ |= (*raw1 & 0x00000fc0L) >> 6;
		*cook	 = (*raw0 & 0x0003f000L) << 12;
		*cook	|= (*raw0 & 0x0000003fL) << 16;
		*cook	|= (*raw1 & 0x0003f000L) >> 4;
		*cook++ |= (*raw1 & 0x0000003fL);
		}
    usekey(dough);
	return;
}

void XDES::usekey(unsigned long *from)
{
	register unsigned long *to, *endp;

    to = KnL, endp = &KnL[32];
    while( to < endp ) *to++ = *from++;
	return;
}

void XDES::des(unsigned char *inblock, unsigned char *outblock)
{
    unsigned long work[2];

    scrunch(inblock, work);
	desfunc(work, KnL);
	unscrun(work, outblock);
	return;
}

void XDES::scrunch(unsigned char *outof, unsigned long *into)
{
	*into	 = (*outof++ & 0xffL) << 24;
	*into	|= (*outof++ & 0xffL) << 16;
	*into	|= (*outof++ & 0xffL) << 8;
	*into++ |= (*outof++ & 0xffL);
	*into	 = (*outof++ & 0xffL) << 24;
	*into	|= (*outof++ & 0xffL) << 16;
	*into	|= (*outof++ & 0xffL) << 8;
	*into	|= (*outof   & 0xffL);
	return;
}

void XDES::unscrun(unsigned long *outof, unsigned char *into)
{
	*into++ = (*outof >> 24) & 0xffL;
	*into++ = (*outof >> 16) & 0xffL;
	*into++ = (*outof >>  8) & 0xffL;
	*into++ =  *outof++	 & 0xffL;
	*into++ = (*outof >> 24) & 0xffL;
	*into++ = (*outof >> 16) & 0xffL;
	*into++ = (*outof >>  8) & 0xffL;
	*into	=  *outof	 & 0xffL;
	return;
}

static unsigned long SP1[64] = {
	0x01010400L, 0x00000000L, 0x00010000L, 0x01010404L,
	0x01010004L, 0x00010404L, 0x00000004L, 0x00010000L,
	0x00000400L, 0x01010400L, 0x01010404L, 0x00000400L,
	0x01000404L, 0x01010004L, 0x01000000L, 0x00000004L,
	0x00000404L, 0x01000400L, 0x01000400L, 0x00010400L,
	0x00010400L, 0x01010000L, 0x01010000L, 0x01000404L,
	0x00010004L, 0x01000004L, 0x01000004L, 0x00010004L,
	0x00000000L, 0x00000404L, 0x00010404L, 0x01000000L,
	0x00010000L, 0x01010404L, 0x00000004L, 0x01010000L,
	0x01010400L, 0x01000000L, 0x01000000L, 0x00000400L,
	0x01010004L, 0x00010000L, 0x00010400L, 0x01000004L,
	0x00000400L, 0x00000004L, 0x01000404L, 0x00010404L,
	0x01010404L, 0x00010004L, 0x01010000L, 0x01000404L,
	0x01000004L, 0x00000404L, 0x00010404L, 0x01010400L,
	0x00000404L, 0x01000400L, 0x01000400L, 0x00000000L,
	0x00010004L, 0x00010400L, 0x00000000L, 0x01010004L };

static unsigned long SP2[64] = {
	0x80108020L, 0x80008000L, 0x00008000L, 0x00108020L,
	0x00100000L, 0x00000020L, 0x80100020L, 0x80008020L,
	0x80000020L, 0x80108020L, 0x80108000L, 0x80000000L,
	0x80008000L, 0x00100000L, 0x00000020L, 0x80100020L,
	0x00108000L, 0x00100020L, 0x80008020L, 0x00000000L,
	0x80000000L, 0x00008000L, 0x00108020L, 0x80100000L,
	0x00100020L, 0x80000020L, 0x00000000L, 0x00108000L,
	0x00008020L, 0x80108000L, 0x80100000L, 0x00008020L,
	0x00000000L, 0x00108020L, 0x80100020L, 0x00100000L,
	0x80008020L, 0x80100000L, 0x80108000L, 0x00008000L,
	0x80100000L, 0x80008000L, 0x00000020L, 0x80108020L,
	0x00108020L, 0x00000020L, 0x00008000L, 0x80000000L,
	0x00008020L, 0x80108000L, 0x00100000L, 0x80000020L,
	0x00100020L, 0x80008020L, 0x80000020L, 0x00100020L,
	0x00108000L, 0x00000000L, 0x80008000L, 0x00008020L,
	0x80000000L, 0x80100020L, 0x80108020L, 0x00108000L };

static unsigned long SP3[64] = {
	0x00000208L, 0x08020200L, 0x00000000L, 0x08020008L,
	0x08000200L, 0x00000000L, 0x00020208L, 0x08000200L,
	0x00020008L, 0x08000008L, 0x08000008L, 0x00020000L,
	0x08020208L, 0x00020008L, 0x08020000L, 0x00000208L,
	0x08000000L, 0x00000008L, 0x08020200L, 0x00000200L,
	0x00020200L, 0x08020000L, 0x08020008L, 0x00020208L,
	0x08000208L, 0x00020200L, 0x00020000L, 0x08000208L,
	0x00000008L, 0x08020208L, 0x00000200L, 0x08000000L,
	0x08020200L, 0x08000000L, 0x00020008L, 0x00000208L,
	0x00020000L, 0x08020200L, 0x08000200L, 0x00000000L,
	0x00000200L, 0x00020008L, 0x08020208L, 0x08000200L,
	0x08000008L, 0x00000200L, 0x00000000L, 0x08020008L,
	0x08000208L, 0x00020000L, 0x08000000L, 0x08020208L,
	0x00000008L, 0x00020208L, 0x00020200L, 0x08000008L,
	0x08020000L, 0x08000208L, 0x00000208L, 0x08020000L,
	0x00020208L, 0x00000008L, 0x08020008L, 0x00020200L };

static unsigned long SP4[64] = {
	0x00802001L, 0x00002081L, 0x00002081L, 0x00000080L,
	0x00802080L, 0x00800081L, 0x00800001L, 0x00002001L,
	0x00000000L, 0x00802000L, 0x00802000L, 0x00802081L,
	0x00000081L, 0x00000000L, 0x00800080L, 0x00800001L,
	0x00000001L, 0x00002000L, 0x00800000L, 0x00802001L,
	0x00000080L, 0x00800000L, 0x00002001L, 0x00002080L,
	0x00800081L, 0x00000001L, 0x00002080L, 0x00800080L,
	0x00002000L, 0x00802080L, 0x00802081L, 0x00000081L,
	0x00800080L, 0x00800001L, 0x00802000L, 0x00802081L,
	0x00000081L, 0x00000000L, 0x00000000L, 0x00802000L,
	0x00002080L, 0x00800080L, 0x00800081L, 0x00000001L,
	0x00802001L, 0x00002081L, 0x00002081L, 0x00000080L,
	0x00802081L, 0x00000081L, 0x00000001L, 0x00002000L,
	0x00800001L, 0x00002001L, 0x00802080L, 0x00800081L,
	0x00002001L, 0x00002080L, 0x00800000L, 0x00802001L,
	0x00000080L, 0x00800000L, 0x00002000L, 0x00802080L };

static unsigned long SP5[64] = {
	0x00000100L, 0x02080100L, 0x02080000L, 0x42000100L,
	0x00080000L, 0x00000100L, 0x40000000L, 0x02080000L,
	0x40080100L, 0x00080000L, 0x02000100L, 0x40080100L,
	0x42000100L, 0x42080000L, 0x00080100L, 0x40000000L,
	0x02000000L, 0x40080000L, 0x40080000L, 0x00000000L,
	0x40000100L, 0x42080100L, 0x42080100L, 0x02000100L,
	0x42080000L, 0x40000100L, 0x00000000L, 0x42000000L,
	0x02080100L, 0x02000000L, 0x42000000L, 0x00080100L,
	0x00080000L, 0x42000100L, 0x00000100L, 0x02000000L,
	0x40000000L, 0x02080000L, 0x42000100L, 0x40080100L,
	0x02000100L, 0x40000000L, 0x42080000L, 0x02080100L,
	0x40080100L, 0x00000100L, 0x02000000L, 0x42080000L,
	0x42080100L, 0x00080100L, 0x42000000L, 0x42080100L,
	0x02080000L, 0x00000000L, 0x40080000L, 0x42000000L,
	0x00080100L, 0x02000100L, 0x40000100L, 0x00080000L,
	0x00000000L, 0x40080000L, 0x02080100L, 0x40000100L };

static unsigned long SP6[64] = {
	0x20000010L, 0x20400000L, 0x00004000L, 0x20404010L,
	0x20400000L, 0x00000010L, 0x20404010L, 0x00400000L,
	0x20004000L, 0x00404010L, 0x00400000L, 0x20000010L,
	0x00400010L, 0x20004000L, 0x20000000L, 0x00004010L,
	0x00000000L, 0x00400010L, 0x20004010L, 0x00004000L,
	0x00404000L, 0x20004010L, 0x00000010L, 0x20400010L,
	0x20400010L, 0x00000000L, 0x00404010L, 0x20404000L,
	0x00004010L, 0x00404000L, 0x20404000L, 0x20000000L,
	0x20004000L, 0x00000010L, 0x20400010L, 0x00404000L,
	0x20404010L, 0x00400000L, 0x00004010L, 0x20000010L,
	0x00400000L, 0x20004000L, 0x20000000L, 0x00004010L,
	0x20000010L, 0x20404010L, 0x00404000L, 0x20400000L,
	0x00404010L, 0x20404000L, 0x00000000L, 0x20400010L,
	0x00000010L, 0x00004000L, 0x20400000L, 0x00404010L,
	0x00004000L, 0x00400010L, 0x20004010L, 0x00000000L,
	0x20404000L, 0x20000000L, 0x00400010L, 0x20004010L };

static unsigned long SP7[64] = {
	0x00200000L, 0x04200002L, 0x04000802L, 0x00000000L,
	0x00000800L, 0x04000802L, 0x00200802L, 0x04200800L,
	0x04200802L, 0x00200000L, 0x00000000L, 0x04000002L,
	0x00000002L, 0x04000000L, 0x04200002L, 0x00000802L,
	0x04000800L, 0x00200802L, 0x00200002L, 0x04000800L,
	0x04000002L, 0x04200000L, 0x04200800L, 0x00200002L,
	0x04200000L, 0x00000800L, 0x00000802L, 0x04200802L,
	0x00200800L, 0x00000002L, 0x04000000L, 0x00200800L,
	0x04000000L, 0x00200800L, 0x00200000L, 0x04000802L,
	0x04000802L, 0x04200002L, 0x04200002L, 0x00000002L,
	0x00200002L, 0x04000000L, 0x04000800L, 0x00200000L,
	0x04200800L, 0x00000802L, 0x00200802L, 0x04200800L,
	0x00000802L, 0x04000002L, 0x04200802L, 0x04200000L,
	0x00200800L, 0x00000000L, 0x00000002L, 0x04200802L,
	0x00000000L, 0x00200802L, 0x04200000L, 0x00000800L,
	0x04000002L, 0x04000800L, 0x00000800L, 0x00200002L };

static unsigned long SP8[64] = {
	0x10001040L, 0x00001000L, 0x00040000L, 0x10041040L,
	0x10000000L, 0x10001040L, 0x00000040L, 0x10000000L,
	0x00040040L, 0x10040000L, 0x10041040L, 0x00041000L,
	0x10041000L, 0x00041040L, 0x00001000L, 0x00000040L,
	0x10040000L, 0x10000040L, 0x10001000L, 0x00001040L,
	0x00041000L, 0x00040040L, 0x10040040L, 0x10041000L,
	0x00001040L, 0x00000000L, 0x00000000L, 0x10040040L,
	0x10000040L, 0x10001000L, 0x00041040L, 0x00040000L,
	0x00041040L, 0x00040000L, 0x10041000L, 0x00001000L,
	0x00000040L, 0x10040040L, 0x00001000L, 0x00041040L,
	0x10001000L, 0x00000040L, 0x10000040L, 0x10040000L,
	0x10040040L, 0x10000000L, 0x00040000L, 0x10001040L,
	0x00000000L, 0x10041040L, 0x00040040L, 0x10000040L,
	0x10040000L, 0x10001000L, 0x10001040L, 0x00000000L,
	0x10041040L, 0x00041000L, 0x00041000L, 0x00001040L,
	0x00001040L, 0x00040040L, 0x10000000L, 0x10041000L };

void XDES::desfunc(unsigned long *block, unsigned long *keys)
{
    register unsigned long fval, work, right, leftt;
    register int round;

	leftt = block[0];
	right = block[1];
	work = ((leftt >> 4) ^ right) & 0x0f0f0f0fL;
	right ^= work;
	leftt ^= (work << 4);
	work = ((leftt >> 16) ^ right) & 0x0000ffffL;
	right ^= work;
	leftt ^= (work << 16);
	work = ((right >> 2) ^ leftt) & 0x33333333L;
	leftt ^= work;
	right ^= (work << 2);
	work = ((right >> 8) ^ leftt) & 0x00ff00ffL;
	leftt ^= work;
	right ^= (work << 8);
	right = ((right << 1) | ((right >> 31) & 1L)) & 0xffffffffL;
	work = (leftt ^ right) & 0xaaaaaaaaL;
	leftt ^= work;
	right ^= work;
	leftt = ((leftt << 1) | ((leftt >> 31) & 1L)) & 0xffffffffL;

	for( round = 0; round < 8; round++ ) {
		work  = (right << 28) | (right >> 4);
		work ^= *keys++;
		fval  = SP7[ work		 & 0x3fL];
		fval |= SP5[(work >>  8) & 0x3fL];
		fval |= SP3[(work >> 16) & 0x3fL];
		fval |= SP1[(work >> 24) & 0x3fL];
		work  = right ^ *keys++;
		fval |= SP8[ work		 & 0x3fL];
		fval |= SP6[(work >>  8) & 0x3fL];
		fval |= SP4[(work >> 16) & 0x3fL];
		fval |= SP2[(work >> 24) & 0x3fL];
		leftt ^= fval;
		work  = (leftt << 28) | (leftt >> 4);
		work ^= *keys++;
		fval  = SP7[ work		 & 0x3fL];
		fval |= SP5[(work >>  8) & 0x3fL];
		fval |= SP3[(work >> 16) & 0x3fL];
		fval |= SP1[(work >> 24) & 0x3fL];
		work  = leftt ^ *keys++;
		fval |= SP8[ work		 & 0x3fL];
		fval |= SP6[(work >>  8) & 0x3fL];
		fval |= SP4[(work >> 16) & 0x3fL];
		fval |= SP2[(work >> 24) & 0x3fL];
		right ^= fval;
		}

	right = (right << 31) | (right >> 1);
	work = (leftt ^ right) & 0xaaaaaaaaL;
	leftt ^= work;
	right ^= work;
	leftt = (leftt << 31) | (leftt >> 1);
	work = ((leftt >> 8) ^ right) & 0x00ff00ffL;
	right ^= work;
	leftt ^= (work << 8);
	work = ((leftt >> 2) ^ right) & 0x33333333L;
	right ^= work;
	leftt ^= (work << 2);
	work = ((right >> 16) ^ leftt) & 0x0000ffffL;
	leftt ^= work;
	right ^= (work << 16);
	work = ((right >> 4) ^ leftt) & 0x0f0f0f0fL;
	leftt ^= work;
	right ^= (work << 4);
    *block++ = right;
	*block = leftt;
	return;
}

void XDESManager::DESCryptography(unsigned int *laKey, short sMode, char *aInputData, size_t iInputLen, char *&aOutputData, size_t &iOutputLen)
{
    if(laKey == NULL || aInputData == NULL || iInputLen == 0) return;

    XDES::deskey((unsigned long *)laKey, sMode);

    unsigned char *paOutputData = (unsigned char *)aOutputData, *paInputData = (unsigned char *)aInputData;
    int iCycle = ((iInputLen - (iInputLen % 8)) + (sMode * 8)) / 8;

    if(iCycle <= 0) return;
    iOutputLen = iCycle * 8;
	
    do
    {
        XDES::des(paInputData, paOutputData);

        paInputData  += 8;
        paOutputData += 8;
    }
    while(iCycle--);
}

void XDESManager::NextDESKey(unsigned int *key)
{
    key[0] = (16807 * (key[1] % 0x1F31D)) + (2836 * (key[1] / 0x1F31D));
    key[1] = (16807 * (key[0] % 0x1F31D)) + (2836 * (key[0] / 0x1F31D));
}

void XDESManager::ResetDESKey(unsigned int *key)
{
    key[0] = 0x53653453;
    key[1] = 0x51476296;
}

static unsigned char byte_106292E0[] =
        "\x05\x09\x0C\x19\x15\x02\x12\x0F\x18\x16\x06\x13\x03\x1B\x17\x0B"
        "\x11\x07\x08\x10\x04\x0D\x14\x01\x00\x0E\x0A\x1A\x18\x07\x0A\x05"
        "\x1B\x10\x02\x17\x03\x19\x04\x11\x0D\x09\x14\x0C\x00\x16\x12\x0E"
        "\x08\x1A\x0F\x06\x13\x15\x01\x0B\x04\x17\x05\x0E\x13\x19\x0B\x01"
        "\x08\x18\x0A\x0C\x12\x00\x0D\x1A\x02\x0F\x1B\x11\x07\x10\x06\x15"
        "\x09\x03\x16\x14\x11\x02\x05\x17\x0F\x10\x16\x03\x0D\x00\x0C\x0B"
        "\x01\x06\x1A\x15\x13\x18\x1B\x0A\x19\x08\x14\x09\x07\x0E\x12\x04"
        "\x0C\x0A\x03\x09\x11\x10\x18\x16\x00\x0E\x06\x07\x17\x0B\x04\x12"
        "\x0F\x14\x02\x0D\x08\x19\x1A\x1B\x15\x05\x01\x13\x11\x05\x06\x0E"
        "\x0A\x02\x03\x17\x0F\x13\x0C\x10\x07\x01\x08\x16\x0D\x04\x14\x18"
        "\x19\x12\x15\x00\x1A\x09\x1B\x0B\x11\x0E\x00\x17\x1B\x19\x0F\x0A"
        "\x0C\x14\x07\x10\x04\x03\x08\x0B\x05\x18\x15\x13\x06\x02\x1A\x0D"
        "\x12\x09\x16\x01\x0F\x16\x0B\x13\x17\x00\x07\x0A\x15\x14\x19\x0E"
        "\x09\x0D\x12\x10\x0C\x1B\x01\x04\x05\x02\x1A\x03\x11\x18\x06\x08"
        "\x17\x11\x08\x1A\x06\x0E\x16\x0C\x04\x14\x07\x0D\x19\x0B\x09\x1B"
        "\x02\x10\x12\x01\x00\x03\x0A\x15\x18\x13\x05\x0F\x0B\x13\x0A\x09"
        "\x03\x1A\x04\x0F\x18\x14\x19\x07\x0E\x05\x17\x0C\x06\x02\x01\x1B"
        "\x00\x12\x08\x15\x10\x0D\x16\x11\x0B\x1B\x04\x03\x06\x0C\x0A\x19"
        "\x13\x02\x14\x1A\x09\x07\x15\x17\x18\x08\x16\x12\x10\x05\x0F\x0D"
        "\x0E\x11\x00\x01\x06\x14\x12\x0B\x16\x0C\x15\x0D\x01\x0F\x03\x05"
        "\x00\x0A\x0E\x11\x1A\x08\x1B\x17\x19\x10\x13\x09\x04\x02\x07\x18"
        "\x1B\x05\x1A\x03\x16\x14\x01\x0C\x17\x10\x06\x18\x02\x0F\x0E\x19"
        "\x11\x04\x15\x12\x09\x08\x0B\x07\x0A\x0D\x00\x13\x00\x09\x07\x17"
        "\x0F\x05\x0E\x1B\x15\x01\x19\x06\x13\x02\x11\x12\x10\x03\x1A\x16"
        "\x14\x0C\x04\x0D\x0A\x0B\x18\x08\x01\x0F\x12\x14\x03\x00\x1B\x1A"
        "\x06\x07\x13\x11\x0A\x17\x10\x16\x05\x0C\x04\x18\x15\x0D\x02\x08"
        "\x0B\x19\x09\x0E\x05\x1A\x16\x19\x0A\x0C\x10\x17\x08\x03\x0B\x06"
        "\x0D\x15\x0F\x09\x01\x14\x11\x04\x07\x1B\x12\x18\x0E\x00\x02\x13";

void XDESManager::ElaborateDESKey(unsigned int *key, unsigned int seed)
{
    unsigned int v2; // eax@1
    signed int v3; // esi@1
    int v4; // ebx@5
    unsigned int v5; // esi@5
    unsigned int v6; // eax@5

    v2 = 0;
    v3 = 0;

    do
    {
        if((seed >> *(&byte_106292E0[28 * (seed >> 28)] + v3)) & 1)
            v2 |= 1 << v3;
      ++v3;
    }
    while(v3 < 28);

    v4 = (v2 >> 24) & 0xF;

    v5 = (16807 * ((v2 & 0xFFFFFF) % 0x1F31D)) + (2836 * ((v2 & 0xFFFFFF) / 0x1F31D));
    v6 = (16807 * (v5 % 0x1F31D)) + (2836 * (v5 / 0x1F31D));

    if(v4 & 8)
        v5 ^= ~(v5 & 0xFFFF0000);
    if(v4 & 4)
        v5 ^= ~(v5 & 0x0000FFFF);

    if(v4 & 2)
        v6 ^= ~(v6 & 0xFFFF0000);
    if(v4 & 1)
        v6 ^= ~(v6 & 0x0000FFFF);

    key[0] = v5;
    key[1] = v6;
}
