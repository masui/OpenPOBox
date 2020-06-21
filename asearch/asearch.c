//
//	$Date: 2001/02/12 18:10:50 $
//	$Revision: 1.2 $
//
#include "asearch.h"

#define INITPAT 0x4000
#define MAXCHAR 0x100

static int mismatch;
static unsigned int epsilon;
static unsigned int acceptpat;
static unsigned int shiftpat[MAXCHAR];

#define isupper(c) ((c) >= 'A' && (c) <= 'Z')
#define islower(c) ((c) >= 'a' && (c) <= 'z')
#define toupper(c) ((c) - 'a' + 'A')
#define tolower(c) ((c) - 'A' + 'a')

void asearch_makepat(unsigned char *pat, int m)
{
	int i;
	unsigned int mask = INITPAT;

	mismatch = m;
	epsilon = 0;

	for(i=0;i<MAXCHAR;i++) shiftpat[i] = 0;
	for(;*pat;pat++){
		if(*pat == ' '){ // ワイルドカード文字
			epsilon |= mask;
		}
		else if (*pat == '\003'){
			for(pat++;*pat != '\004';pat++){
				shiftpat[*pat] |= mask;
				if(isupper(*pat)) shiftpat[tolower(*pat)] |= mask;
				if(islower(*pat)) shiftpat[toupper(*pat)] |= mask;
			}
			mask >>= 1;
		}
		else {
			shiftpat[*pat] |= mask;
			if(isupper(*pat)) shiftpat[tolower(*pat)] |= mask;
			if(islower(*pat)) shiftpat[toupper(*pat)] |= mask;
			mask >>= 1;
		}
	}
	acceptpat = mask;
}

int asearch_match(register unsigned char *text)
{
	register unsigned int i0 = INITPAT;
#if MAXMISMATCH > 0
	register unsigned int i1=0;
#endif
#if MAXMISMATCH > 1
	register unsigned int i2=0;
#endif
#if MAXMISMATCH > 2
	register unsigned int i3=0;
#endif
	register unsigned int mask;
	register unsigned int e = epsilon;

	for(;*text;text++){
		mask = shiftpat[*text];
#if MAXMISMATCH > 2
		i3 = (i3 & e) | ((i3 & mask) >> 1) | (i2 >> 1) | i2;
#endif
#if MAXMISMATCH > 1
		i2 = (i2 & e) | ((i2 & mask) >> 1) | (i1 >> 1) | i1;
#endif
#if MAXMISMATCH > 0
		i1 = (i1 & e) | ((i1 & mask) >> 1) | (i0 >> 1) | i0;
#endif
		i0 = (i0 & e) | ((i0 & mask) >> 1);
#if MAXMISMATCH > 0
		i1 |= (i0 >> 1);
#endif
#if MAXMISMATCH > 1
		i2 |= (i1 >> 1);
#endif
#if MAXMISMATCH > 2
		i3 |= (i2 >> 1);
#endif
	}
	switch(mismatch){
		case 0: return (i0 & acceptpat);
		case 1: return (i1 & acceptpat);
		case 2: return (i2 & acceptpat);
		case 3: return (i3 & acceptpat);
		default: return 0;
	}
}

