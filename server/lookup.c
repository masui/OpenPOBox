//
//	$Date: 2001/07/23 15:01:54 $
//	$Revision: 1.9 $
//
//	トライを目次に使用する単純な辞書検索プログラム
//

#include <stdio.h>
#include "lookup.h"

static int trielevel = 3;

//
// トライ構築
//
static void
addnode(TrieNode **nodepp, char *s, int val)
{
	TrieNode *p;

//printf("addnode(%x,%s,%d)\n",nodepp,s,val);
	if(!nodepp || ! *s) return;

	p = (*nodepp);
	if(p == NULL){
		p = (TrieNode*)malloc(sizeof(TrieNode));
		p->c = *s;
		p->child = p->next = NULL;
		p->val = val;
		(*nodepp) = p;

		addnode(&(p->child),s+1,val);
	}
	else if(p->c ==*s){
		addnode(&(p->child),s+1,val);
	}
	else {
		addnode(&(p->next),s,val);
	}
}

static void
traverse(TrieNode *nodep, int level)
{
	int i;

	if(! nodep) return;

	for(i=0;i<level;i++) printf("\t");
	printf("[%c] %d\n",nodep->c,nodep->val);
	if(nodep->child) traverse(nodep->child,level+1);
	if(nodep->next) traverse(nodep->next,level);
}

static int
getval(TrieNode *nodep, char *s)
{
	char c;
	if(*s == nodep->c){
		c = *(s+1);
		if((c != '\0' && c != '\t' && c != '\n' && c != '\r') && nodep->child){
			return getval(nodep->child,s+1);
		}
		else {
			return nodep->val;
		}
	}
	else if(nodep->next){
		return getval(nodep->next,s);
	}
	else {
		return -1;
	}
}

void lookup_settrielevel(int level)
{
	trielevel = level;
}

Lookup *lookup_new(char *dictfile)
{
	FILE *f;
	Lookup *l;
	char buf[1000],prev[100];
	char *p;
	int pos = 0;
	int i;

	f = fopen(dictfile,"rb"); // Cygwin用に"b"が必要らしい
	if(f == NULL) return NULL;

	l = (Lookup*)malloc(sizeof(Lookup));
	if(l == NULL){
		fclose(f);
		return NULL;
	}
	l->dict = f;
	l->root = NULL;

	for(i=0;i<100;i++) prev[i] = '\0';

	while(fgets(buf,1000,f)){
		for(p=buf;*p && *p != '\t' && *p != '\n';p++);
		*p = '\0';
		buf[trielevel] = '\0';

		if(strncmp(buf,prev,trielevel)){
			addnode(&(l->root),buf,pos);
			strncpy(prev,buf,trielevel);
		}
		pos = ftell(f);
	}
	return l;
}

int
lookup_search(Lookup *l,char *pat)
{
	int pos;

	if(!l || !pat || !(*pat)) return 0;
	strcpy(l->pat,pat);
	pos = getval(l->root,pat);
//printf("lookup_search: pos=%d\n",pos);
	if(pos < 0) return 0;
	fseek(l->dict,pos,0);
	return pos;
}

char *
lookup_get_next_line(Lookup *l)
{
	char *buf;
	int cmp;

	buf = (char*)malloc(1000+1);
//printf("get_next_line: pat=[%s]\n",l->pat);
	while(fgets(buf,1000,l->dict)){
		cmp = strncmp(buf,l->pat,strlen(l->pat));
		if(cmp == 0) return buf;
		if(cmp < 0) continue;
		if(cmp > 0) return NULL;
	}
	return NULL;
}

int
lookup_destroy(Lookup *l)
{
	if(l){
		if(l->dict) fclose(l->dict);
		free(l);
	}
	return 1;
}
