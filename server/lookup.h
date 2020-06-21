//
//	$Date: 2001/07/23 15:01:58 $
//	$Revision: 1.2 $
//

#ifndef _LOOKUP_H_
#define _LOOKUP_H_

#include <stdio.h>

// トライノード
typedef struct _TrieNode {
	char c;
	struct _TrieNode *child; // 子ノード
	struct _TrieNode *next;  // 兄弟ノード
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
