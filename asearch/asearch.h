//
//	$Date: 2001/02/12 18:10:50 $
//	$Revision: 1.2 $
//
#ifndef _ASEARCH_H_
#define _ASEARCH_H_

#define MAXMISMATCH 3

void asearch_makepat(unsigned char *pattern, int ambig);
int asearch_match(unsigned char *text);
#endif
