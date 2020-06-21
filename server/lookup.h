//
//	$Date: 2001/07/23 15:01:58 $
//	$Revision: 1.2 $
//

#ifndef _LOOKUP_H_
#define _LOOKUP_H_

#include <stdio.h>

// $B%H%i%$%N!<%I(B
typedef struct _TrieNode {
	char c;
	struct _TrieNode *child; // $B;R%N!<%I(B
	struct _TrieNode *next;  // $B7;Do%N!<%I(B
	int val;
} TrieNode;

typedef struct {
	FILE *dict;
	TrieNode *root;
	char pat[100];
} Lookup;

Lookup *lookup_new(char *dictfile);
int lookup_search(Lookup *l,char *pat);
char *lookup_get_next_line(Lookup *l);
int lookup_destroy(Lookup *l);
void lookup_settrielevel(int level);

#endif
