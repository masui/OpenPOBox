#include <stdio.h>
// #include <string.h>
#include "poboxlib.h"

#define POBOXDIC "ICdic"

#ifndef ORIG

// implementation using Boehm GC 

#include "gc.h"

#define malloc(n) GC_malloc(n)
#define calloc(m,n) GC_malloc((m)*(n))

#define UCHAR unsigned char

static UCHAR *strdup(const char *s)
{
	UCHAR *buf;
	if(s == NULL) return NULL;
	buf = (UCHAR*)malloc(strlen(s)+1);
	strcpy((char*)buf,(char*)s);
	return buf;
}

static UCHAR **dicword;
static UCHAR **dicpat;
static UCHAR **diccontext;
static int dicentries = 0;
static int diclimit = 0;

POBOX_INT pobox_entries(POBoxDict *dict)
{
	return (POBOX_INT)dicentries;
}

#define ADD_ENTRY(buf,entry) \
	p = (UCHAR**)malloc(sizeof(UCHAR*) * newsize); \
	for(i=0;i<dicentries;i++){ \
		p[i] = buf[i]; \
	} \
	for(;i<newsize;i++){ \
		p[i] = (UCHAR*)NULL; \
	} \
	p[nth] = strdup(entry); \
	buf = p;

POBOX_INT pobox_regent(POBoxDict *dict, POBOX_INT nth,
	UCHAR *word, UCHAR *pat, UCHAR *context)
{
	static UCHAR **p;
	int newsize;
	int i;

	if(nth >= diclimit){
		newsize = ((nth / 100) + 1) * 100;
		ADD_ENTRY(dicword,word);
		ADD_ENTRY(dicpat,pat);
		ADD_ENTRY(diccontext,context);
		diclimit = newsize;
	}
	if(nth >= dicentries){
		dicentries = nth + 1;
	}
}

POBOX_INT pobox_getent(POBoxDict *dict, POBOX_INT nth,
	unsigned char *word, unsigned char *pat)
{
	if(nth >= dicentries) return -1;

	if(dicword[nth]) strcpy((char*)word,(char*)(dicword[nth]));
	if(dicpat[nth]) strcpy((char*)pat,(char*)(dicpat[nth]));
	return 0;
}

POBOX_INT pobox_delent(POBoxDict *dict, POBOX_INT nth);
{
	int i;

	if(nth >= dicentries) return -1;

	for(i=nth;i<dicentries-1;i++){
		dicword[i] = dicword[i+1]
		dicpat[i] = dicpat[i+1]
		diccontext[i] = diccontext[i+1]
	}
	dicentries--;

	return 0;
}

POBOX_INT pobox_usedict(POBoxDict *dict)
{
	static FILE *f = NULL;

	char buf[1000];
	char p[200],w[200],c[200];
	int n;
	int nwords = 0;

	if(f == NULL){ // 辞書ロード
		f = fopen(POBOXDIC,"r");
		if(f == NULL) return -1;
		nwords = 0;
		while(fgets(buf,1000,f)){
			if(buf[0] == '#') continue;
			n = sscanf(buf,"%s\t%s\t%s",p,w,c);
			if(n == 3){
				pobox_regent(NULL,nwords,w,p,c);
				nwords++;
				continue;
			}
			n = sscanf(buf,"%s\t%s",p,w);
			if(n == 2){
				pobox_regent(NULL,nwords,w,p,NULL);
				nwords++;
				continue;
			}
		}
		fclose(f);
	}

	printf("nwords = %d\n",nwords);
	printf("dicentries = %d\n",dicentries);
}
#endif

#ifdef ORIG

typedef struct {
	char *pat;
	char *word;
	char *context;
} DicEntry;

#define MAXWORDS 200000
static DicEntry word[MAXWORDS];
static int nwords = 0;

#define MAXPHRASES 40000
static DicEntry phrase[MAXWORDS];
static int nphrases = 0;

int pobox_usedict(POBoxDict *dict)
{
	static FILE *f = NULL;

	char buf[1000];
	char p[100],w[100],c[100];
	int n;

	if(f == NULL){ // 辞書ロード
		f = fopen(POBOXDIC,"r");
		if(f == NULL) return -1;
		nwords = 0;
		while(fgets(buf,1000,f)){
			if(buf[0] == '#') continue;
			n = sscanf(buf,"%s\t%s\t%s",p,w,c);
			if(n == 3){
				phrase[nphrases].pat = strdup(p);
				phrase[nphrases].word = strdup(w);
				phrase[nphrases].context = strdup(c);
				nphrases++;
				continue;
			}
			n = sscanf(buf,"%s\t%s",p,w);
			if(n == 2){
				word[nwords].pat = strdup(p);
				word[nwords].word = strdup(w);
				word[nwords].context = NULL;
				nwords++;
				continue;
			}
		}
		fclose(f);
//fprintf(stderr,"%s end -- nwords = %d, nphrases = %d\n",POBOXDIC,nwords,nphrases);
		return 0;
	}
	else { // 辞書セーブ
		unsigned char *c,*w,*p;
		int i;
		f = fopen(POBOXDIC,"w");
		if(f == NULL) return -1;
		for(i=0;i< nwords;i++){
			w = word[i].word;
			p = word[i].pat;
			if(w && *w && p && *p){
				fprintf(f,"%s\t%s\n",p,w);
			}
		}
		for(i=0;i< nphrases;i++){
			w = phrase[i].word;
			p = phrase[i].pat;
			c = phrase[i].context;
			if(w && *w && p && *p && c && *c){
				fprintf(f,"%s\t%s\t%s\n",p,w,c);
			}
		}
		fclose(f);
//fprintf(stderr,"Dictionary save end\n");
		return 0;
	}
}
#endif

main()
{
	pobox_usedict(NULL);
}


