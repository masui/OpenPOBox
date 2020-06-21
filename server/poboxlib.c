//
//	$Date: 2002/07/06 09:16:59 $
//	$Revision: 1.25 $
//
//	POBox API$B$N(BUNIX$B>e$G$N<BAuNc(B
//

#include <stdio.h>
#if defined(POCKET_SIZE) || defined(PALM_SIZE)
#else
#include <strings.h>
#endif
#include "asearch.h"
#include "romakana.h"
#include "poboxlib.h"

/*
////////////////////////////////////////////////////////////////////////////////////////////
#include <sys/time.h>
struct timeval ts,te;
static void timebegin()
{
  gettimeofday(&ts,NULL);
}
static long timeend()
{
  long t;
  gettimeofday(&te,NULL);
  t = (te.tv_sec - ts.tv_sec) * 1000000 + (te.tv_usec - ts.tv_usec);
  return t;
}
////////////////////////////////////////////////////////////////////////////////////////////
*/

#define UCHAR unsigned char

#define MAXWORDLEN 200

#ifdef USELOOKUP
#include "lookup.h"
#endif

#ifdef USESARY
#include <sary.h>
#endif

#ifdef USEGC
//
//	$B4JC1$N$?$a(BBoehm GC$B$r;HMQ$7$F$$$k!#(B
//	Boehm GC$B%i%$%V%i%j$r;HMQ$9$k$H!"3d$jEv$F$?NN0h$O(B
//	$B<+F0E*$K(BFree$B$5$l$k$N$G!"(B
//	free()$B$NI,MW$,L5$$(Bmalloc()$B$d(Bstrdup()$B$r;H$&$3$H$,$G$-$k!#(B
//

#include "gc.h" 

#define malloc(n) GC_malloc(n)
#define calloc(m,n) GC_malloc((m)*(n))

#define strdup(x) strdup_gc(x)

static UCHAR *strdup_gc(const char *s)
{
	UCHAR *buf;
	if(s == NULL) return NULL;
	buf = (UCHAR*)GC_malloc(strlen(s)+1);
	strcpy((char*)buf,(char*)s);
	return buf;
}

#else

// WinCE$B$NI8=`%i%$%V%i%j$K(Bstrdup()$B$,4^$^$l$F$$$J$$$N$G$3$3$GDj5A(B

#define strdup(x) my_strdup(x)

UCHAR *my_strdup(const char *s)
{
	UCHAR *buf;
	if(s == NULL) return NULL;
	buf = (UCHAR*)malloc(strlen(s)+1);
	strcpy((char*)buf,(char*)s);
	return buf;
}

#endif

/////////////////////////////////////////////////////////////////
//
//		$B<-=qA`:n(BAPI
//
/////////////////////////////////////////////////////////////////

typedef struct { // $B<-=q%(%s%H%j(B
	char *pat;
	char *word;
	char *context;
} DicEntry;

typedef struct Dict Dict;
struct Dict {
	POBoxDict *poboxdict;
	//
	// $B3X=,<-=q$N$?$a$N%(%s%H%j(B
	// 
	DicEntry *entry;	// $B<-=q%G!<%?(B
	int nentries;		// $B<-=q$N%(%s%H%j?t(B
	int maxentries;		// $B<-=q%5%$%:!#B-$j$J$/$J$k$H(Bmalloc()	$B$GA}$d$9(B
#ifdef USESARY
	//
	// Sary$B$N$?$a$N%(%s%H%j(B
	//
	Saryer *saryer;
#endif
#ifdef USELOOKUP
	//
	// Trie$B8!:w$N$?$a$N%(%s%H%j(B
	//
	Lookup *lookup;
#endif
};

#define MAXDICTIONARIES 10
static Dict dictionaries[MAXDICTIONARIES];
static int ndictionaries = 0;	// $B<-=q?t(B

static Dict *findpbdict(POBoxDict *pbdict)
{
	int i;
	for(i=0;i<ndictionaries;i++){
		if(dictionaries[i].poboxdict == pbdict)
			return &(dictionaries[i]);
	}
	return NULL;
}

//
// $BEPO?C18l?t$N<hF@(B
//
POBOX_INT pobox_entries(POBoxDict *pbdict)
{
	Dict *dict;

	if(pbdict->type != POBOXDICT_STANDARD)
		return -1;
	dict = findpbdict(pbdict);
	return (POBOX_INT)(dict ? dict->nentries : -1);
}

//
// n$BHVL\$N%(%s%H%j$KC18l$rEPO?(B
//
POBOX_INT pobox_regent(POBoxDict *pbdict, POBOX_INT nth,
	UCHAR *word, UCHAR *pat, UCHAR *context)
{
	DicEntry *d;
	Dict *dict;
	int newsize;
	int i;
//printf("pobox_regent(%d,%s,%s,%s)\n",nth,word,pat,context);

	if(pbdict->type != POBOXDICT_STANDARD)
		return -1;	

	dict = findpbdict(pbdict);
	if(dict == NULL) return -1;

	if(nth >= dict->maxentries){
		// $B<-=qNN0h$,B-$j$J$/$J$k$H%(%s%H%j$r3HD%$9$k(B
		newsize = ((nth / 100) + 1) * 100;

		// realloc() $B$GNI$$$O$:$@$,(B...?
		//
		d = (DicEntry*)malloc(sizeof(DicEntry) * newsize);
		if(d == NULL){
			fprintf(stderr,"Can't alloc dict data space!\n");
			return -1;
		}
		for(i=0;i<dict->nentries;i++){
			d[i] = dict->entry[i];
		}
		for(;i<newsize;i++){
			d[i].word =
			d[i].pat =
			d[i].context = (UCHAR*)NULL;
		}
#ifndef USEGC
		free(dict->entry);
#endif
		dict->entry = d;
		dict->maxentries = newsize;
	}

	// $B?7$7$$%(%s%H%j$rEPO?(B
	dict->entry[nth].word = strdup(word);
	dict->entry[nth].pat = strdup(pat);
	dict->entry[nth].context = (context ? strdup(context) : NULL);

	if(nth >= dict->nentries){
		dict->nentries = nth + 1;
	}

	return 0;
}

//
// n$BHVL\$N%(%s%H%jC18l$r<hF@(B
//
POBOX_INT pobox_getent(POBoxDict *pbdict, POBOX_INT nth,
	UCHAR *word, UCHAR *pat)
{
	Dict *dict;

	if(pbdict->type != POBOXDICT_STANDARD)
		return -1;
	dict = findpbdict(pbdict);
	if(dict == NULL) return -1;

	if(nth >= dict->nentries) return -1;

	if(dict->entry[nth].word) strcpy((char*)word,(char*)(dict->entry[nth].word));
	if(dict->entry[nth].pat) strcpy((char*)pat,(char*)(dict->entry[nth].pat));
	return 0;
}

//
// n$BHVL\$NEPO?C18l$N:o=|(B
//
POBOX_INT pobox_delent(POBoxDict *pbdict, POBOX_INT nth)
{
	Dict *dict;
	int i;

	if(pbdict->type != POBOXDICT_STANDARD)
		return -1;
	dict = findpbdict(pbdict);
	if(dict == NULL) return -1;

	if(nth >= dict->nentries) return -1;

#ifndef USEGC
	if(dict->entry[nth].word) free(dict->entry[nth].word);
	if(dict->entry[nth].pat) free(dict->entry[nth].pat);
	if(dict->entry[nth].context) free(dict->entry[nth].context);
#endif
	for(i=nth;i<dict->nentries-1;i++){
		dict->entry[i] = dict->entry[i+1];
	}
	dict->nentries--;

	return 0;
}

//
// $B;HMQ$9$k<-=q$N;XDj(B
//
POBOX_INT pobox_usedict(POBoxDict *pbdict)
{
	FILE *f;
	char p[MAXWORDLEN],w[MAXWORDLEN],c[MAXWORDLEN];
	char buf[1000];
	int i,n;
	int nwords = 0;
	Dict *dict;

//printf("pobox_usedict(%x)\n",pbdict);

	if(pbdict == NULL){
		// save all dictionaries
		for(i=0;i<ndictionaries;i++){
			dict = &(dictionaries[i]);
			pobox_save(dict->poboxdict);
		}
		return 0;
	}
	for(i=0;i<ndictionaries;i++){
		if(dictionaries[i].poboxdict == pbdict){
			// $BM%@hEY$rJQ$($k$Y$-$+$b(B ***
			break;
		}
	}
	if(ndictionaries >= MAXDICTIONARIES-1)
		return -1;

	if(pbdict->type == POBOXDICT_STANDARD){
		if(i >= ndictionaries){
			dict = &(dictionaries[i]);
			dict->entry = NULL;
			dict->nentries = 0;
			dict->maxentries = 0;
			dict->poboxdict = pbdict;
			f = fopen(pbdict->name,"r");
			if(f == NULL) return -1;
			ndictionaries++;
			nwords = 0;
			while(fgets(buf,1000,f)){
				if(buf[0] == '#') continue;
				n = sscanf(buf,"%s\t%s\t%s",p,w,c);
				if(n == 3){
					pobox_regent(pbdict,nwords,w,p,c);
					nwords++;
					continue;
				}
				n = sscanf(buf,"%s\t%s",p,w);
				if(n == 2){
					pobox_regent(pbdict,nwords,w,p,NULL);
					nwords++;
					continue;
				}
			}
			fclose(f);
		}
	}
#ifdef USESARY
	else if(pbdict->type == POBOXDICT_SARY){
		if(i >= ndictionaries){
			dict = &(dictionaries[i]);
			dict->poboxdict = pbdict;
			dict->saryer = saryer_new(pbdict->name);
			if(dict->saryer == NULL) return -1;
			ndictionaries++;
		}
	}
#endif
#ifdef USELOOKUP
	else if(pbdict->type == POBOXDICT_LOOKUP){
		if(i >= ndictionaries){
			dict = &(dictionaries[i]);
			dict->poboxdict = pbdict;
printf("lookup dict init begin\n");
			dict->lookup = lookup_new(pbdict->name);
printf("lookup dict init end\n");
			if(dict->lookup == NULL) return -1;
			ndictionaries++;
		}
	}
#endif
	else {
		return -1;
	}
	return 0;
}

//
// $B<-=q%;!<%V(B
//
POBOX_INT pobox_save(POBoxDict *pbdict)
{
	FILE *f;
	int i;
	UCHAR *c,*w,*p;
	Dict *dict;

	for(i=0;i<ndictionaries;i++){
		dict = &(dictionaries[i]);
		if(dict->poboxdict == pbdict){
			if(pbdict->type == POBOXDICT_STANDARD){
				f = fopen(pbdict->name,"w");
				if(f == NULL) return -1;
				for(i=0;i< dict->nentries;i++){
					w = dict->entry[i].word;
					p = dict->entry[i].pat;
					c = dict->entry[i].context;
					if(w && *w && p && *p && c && *c){
						fprintf(f,"%s\t%s\t%s\n",p,w,c);
					}
					else if(w && *w && p && *p){
						fprintf(f,"%s\t%s\n",p,w);
					}
				}
				fclose(f);
			}

#ifdef USESARY
		 	else if(dict->poboxdict->type == POBOXDICT_SARY){
				saryer_destroy(dict->saryer);
			}
#endif
		}
	}
	return 0;
}

//
// $B;HMQ2DG=$J<-=q%j%9%H$N<hF@(B
//
POBOX_INT pobox_getdictlist(POBoxDict *dictlist[], int limit)
{
	int i;
	for(i=0;i<limit && i<MAXDICTIONARIES;i++){
		dictlist[i] = dictionaries[i].poboxdict;
	}
	return i;
}

//
// $B<-=q$NB0@-$r@_Dj(B
//
POBOX_INT pobox_setattr(POBoxDict *dict, POBoxDict *newdict)
{
}

//
// $B<-=q$KC18l$rEPO?(B
//
POBOX_INT pobox_regword(POBoxDict *pbdict, UCHAR *word,
        UCHAR *pat, UCHAR *context)
{
	int i,j;
	DicEntry de;
	Dict *dict;

//printf("regword(%s,%s,%s)\n",word,pat,context);

	if(pbdict->type != POBOXDICT_STANDARD)
		return -1;
	dict = findpbdict(pbdict);
	if(dict == NULL) return -1;

	if(! (word && *word && pat && *pat)) return -1;

	// $BC18l3X=,(B
	for(i=0;i< dict->nentries;i++){
		if(strcmp(dict->entry[i].word,word)==0 && strcmp(dict->entry[i].pat,pat)==0 &&
		   (dict->entry[i].context == NULL || *(dict->entry[i].context) == '\0'))
			break;
	}
	if(i == dict->nentries){ // $B?7$?$KEPO?(B
		pobox_regent(pbdict,i,word,pat,NULL);
	}
//printf("i=%d\n",i);
	de = dict->entry[i];
	for(j=i-1;j>=0;j--) dict->entry[j+1] = dict->entry[j];
	dict->entry[0] = de;

	// $BNcJ83X=,(B
	if(context && *context){
		for(i=0;i< dict->nentries;i++){
			if(strcmp(dict->entry[i].word,word)==0 &&
			   strcmp(dict->entry[i].pat,pat)==0 &&
			   dict->entry[i].context &&
			   strcmp(dict->entry[i].context,context)==0)
				break;
		}
		if(i == dict->nentries){
			pobox_regent(pbdict,i,word,pat,context);
		}
		de = dict->entry[i];
		for(j=i-1;j>=0;j--) dict->entry[j+1] = dict->entry[j];
		dict->entry[0] = de;
	}
	return 0;
}

//
// $B<-=q$+$iC18l$r:o=|(B
//
POBOX_INT pobox_delword(POBoxDict *pbdict, UCHAR *word, UCHAR *pat)
{
	int i,j;
	Dict *dict;
	
	if(pbdict->type != POBOXDICT_STANDARD)
		return -1;
	dict = findpbdict(pbdict);
	if(dict == NULL) return -1;

	for(i=j=0;i< dict->nentries;i++){
		if(strcmp(dict->entry[i].word,word)){
			if(i != j){
				dict->entry[j] = dict->entry[i];
			}
			j++;
		}
#ifndef USEGC
		else {
			if(i != j){
				if(dict->entry[i].word) free(dict->entry[i].word);
				if(dict->entry[i].pat) free(dict->entry[i].pat);
				if(dict->entry[i].context) free(dict->entry[i].context);
			}
		}
#endif
	}
	dict->nentries = j;
	return 0;
}

/////////////////////////////////////////////////////////////////
//
//		$B8!:w(BAPI
//
/////////////////////////////////////////////////////////////////

#define MAXCANDS 40
static UCHAR *cands[MAXCANDS];
static UCHAR *candspat[MAXCANDS];
static int ncands = 0;

static int exact = 0;
static int approximate = 0;
static UCHAR context[MAXWORDLEN] = "";

static RomaKana *rktable;

void pobox_searchmode(POBOX_INT mode)
{
	exact = ((mode & POBOX_EXACT) ? 1 : 0);
	approximate = ((mode | POBOX_APPROXIMATE) ? 1 : 0);
}

static int
addcand(DicEntry *de)
{
	int i;
	for(i=0;i< ncands;i++){
		if(strcmp(cands[i],de->word)==0)
		return 0;
	}
	cands[ncands] = strdup(de->word);
	candspat[ncands] = strdup(de->pat);
	ncands++;
	return (ncands >= MAXCANDS ? -1 : 0);
}

static int
consonant(int c)
{
//	char *consonants = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";
	char *consonants = "bcdfghjklmpqrstvwxyz";
	char *s;
	for(s=consonants;*s;s++){
		if(*s == c) return 1;
	}
	return 0;
}

//
// $BC18l8!:w(B
//
POBOX_INT pobox_search(UCHAR *pat)
{
	int i,j;
	int m;
	UCHAR *s,*p;
	int clen,plen;
	int kanjipat;		// $B8!:w$K4A;z$r;HMQ$9$k$+$I$&$+(B
	int dicno;

	UCHAR searchpat[1000];
	UCHAR kana[MAXWORDLEN];

	Dict *dict;
	DicEntry de;

	if(pat == NULL || strlen(pat) > 100)
		return 0;

#ifndef USEGC
	for(i=0;i<ncands;i++){
		if(cands[i]) free(cands[i]);
		if(candspat[i]) free(candspat[i]);
	}
#endif
	ncands = 0;

	kanjipat = (*pat & 0x80 ? 1 : 0);

	// $B40A4%^%C%A$r;XDj$5$l$?$H$-$O!"$R$i$,$J(B/$B%+%?%+%J(B/ASCII$B$r8uJd$K$9$k(B
	if(exact){
		Roma2Kana(pat,kana,rktable);
		de.pat = pat;
		de.word = kana;
		de.context = NULL;
		addcand(&de);
		for(s=kana;*s;s+=2){
			if(*s == 0xa4) *s = 0xa5;
		}
		addcand(&de);
		de.word = pat;
		addcand(&de);
	}

	// $B:G=i$O3F<-=q$K$D$$$F[#KfL5$7$G8!:w(B
	for(dicno=0;dicno<ndictionaries && ncands < MAXCANDS; dicno++){
		dict = &(dictionaries[dicno]);
		if(dict->poboxdict->type == POBOXDICT_STANDARD){
			// asearch$B$N$?$a$N8!:w%Q%?%s:n@.(B
			sprintf(searchpat,"%s%s",pat,exact ? "" : " ");
			// $BNcJ88!:w(B
			if(clen = strlen(context)){
				asearch_makepat(searchpat,0);
				for(i=0;i< dict->nentries && ncands < MAXCANDS;i++){
					if(dict->entry[i].context == NULL) continue;
					plen = strlen(dict->entry[i].context);
					if(plen > clen) continue;
					if(strcmp(context+clen-plen,dict->entry[i].context)==0 &&
						asearch_match(kanjipat ? dict->entry[i].word : dict->entry[i].pat)){
						addcand(&(dict->entry[i]));
					}
				}
			}
			// $BC18l8!:w(B
			if(ncands < MAXCANDS){
				asearch_makepat(searchpat,0);
				for(i=0;i< dict->nentries && ncands < MAXCANDS;i++){
					if(dict->entry[i].context) continue;
					if(asearch_match(kanjipat ? dict->entry[i].word : dict->entry[i].pat)){
						addcand(&(dict->entry[i]));
					}
				}
			}
		}
#ifdef USESARY
		else if(dict->poboxdict->type == POBOXDICT_SARY){
			sprintf(searchpat,"%s%s",pat,exact ? "\t" : "");
			if(saryer_search(dict->saryer,searchpat)) {
				gchar *line, *s;
				saryer_sort_occurrences(dict->saryer);
				for(;(line = saryer_get_next_line(dict->saryer)) && ncands < MAXCANDS;){
					de.pat = line;
					for(s = line;*s && *s != '\t';s++);
					*s++ = '\0';
					de.word = s;
					for(;*s && *s != '\n' && *s != '\r';s++);
					*s = '\0';
					de.context = NULL;
					addcand(&de);
					g_free(line);
				}
			}
		}
#endif
#ifdef USELOOKUP
		else if(dict->poboxdict->type == POBOXDICT_LOOKUP){
			sprintf(searchpat,"%s%s",pat,exact ? "\t" : "");
			if(lookup_search(dict->lookup,searchpat)){
				char *line, *s;
				for(;(line = lookup_get_next_line(dict->lookup)) && ncands < MAXCANDS;){
					de.pat = line;
					for(s = line;*s && *s != '\t';s++);
					*s++ = '\0';
					de.word = s;
					for(;*s && *s != '\t' && *s != '\n' && *s != '\r';s++);
					*s = '\0';
					de.context = NULL;
					addcand(&de);
					free(line);
				}
			}
		}
#endif
	}

	// $B[#Kf8!:w(B
	for(dicno=0;dicno<ndictionaries && ncands < MAXCANDS; dicno++){
//printf("dictno = %d\n",dicno);
		dict = &(dictionaries[dicno]);
		if(dict->poboxdict->type == POBOXDICT_STANDARD){
			for(m=1;ncands< MAXCANDS && m< 2;m++){
				asearch_makepat(searchpat,m);
				for(i=0;i< dict->nentries && ncands < MAXCANDS;i++){
					if(dict->entry[i].context) continue;
					if(asearch_match(kanjipat ? dict->entry[i].word : dict->entry[i].pat)){
						addcand(&(dict->entry[i]));
					}
				}
			}
			// $B8uJd$,$_$D$+$i$J$$>l9g$O%Q%?%s$rJQ$($F[#Kf8!:w$r9T$J$&(B
			if(ncands == 0 && !kanjipat){
				for(p=searchpat,s=pat;*s;s++){ // 'dsg' => 'd s g ', etc.
					*p++ = *s;
					*p++ = ' ';
				}
				*p = '\0';
				asearch_makepat(searchpat,0);
				for(i=0;i< dict->nentries && ncands < MAXCANDS;i++){
					if(asearch_match(dict->entry[i].pat)){
						addcand(&(dict->entry[i]));
					}
				}
			}
			// $B4J0WAw$j$,$J8!:w(B
//printf("okurigana == pat=[%s]\n",pat);
			if(ncands == 0 && !exact && Roma2Kana(pat,kana,rktable)){
				for(i=0;i< dict->nentries && ncands < MAXCANDS;i++){
					UCHAR *s;
					int len;
					s = dict->entry[i].pat;
					len = strlen(s);
//printf("s=[%s], kanjipat=%d, word=[%s]\n",s,kanjipat,dict->entry[i].word);
					if(strncmp(pat,s,len)==0 && 
					   consonant(s[len-1]) && 
					   (!kanjipat) &&
					   (dict->entry[i].word[0] & 0x80)){
						UCHAR wordbuf[100];
						strcpy(wordbuf,dict->entry[i].word);
						Roma2Kana(pat+len-1,kana,rktable);
						strcat(wordbuf,kana);
						de.word = wordbuf;
						de.pat = pat;
						de.context = NULL;
						addcand(&de);
					}
				}
			}
		}
	}

	if(ncands+3 < MAXCANDS){
		Roma2Kana(pat,kana,rktable);
		de.pat = pat;
		de.word = kana;
		de.context = NULL;
		addcand(&de);
		for(s=kana;*s;s+=2){
			if(*s == 0xa4) *s = 0xa5;
		}
		addcand(&de);
		de.word = pat;
		addcand(&de);
	}

	return ncands;
}

//
// $B%$%s%G%/%9$r;XDj$7$F8!:w7k2L$NC18l$rF@$k(B
//
POBOX_INT pobox_getcands(UCHAR **candidates,
        UCHAR **patterns, POBOX_INT first, POBOX_INT n)
{
	int i;
	for(i=0;i< n && first+i < ncands;i++){
		candidates[i] = cands[first+i];
		patterns[i] = candspat[first+i];
	}
	return i;
}

//
// $B%3%s%F%/%9%H$N;XDj(B
//
void pobox_context(UCHAR *c, POBOX_INT contextlen)
{
	strncpy(context,c,contextlen);
	context[contextlen] = '\0';
}

//
// $B8uJd3X=,$r;XNa(B
//
void pobox_select(POBOX_INT selindex)
// $B$3$N(BAPI$B$G$O<-=q$r;XDj$7$F$$$J$$(B... $B:G=i$N<-=q$r3NDj$9$k(B?
{
	UCHAR *p,*w;
	int i;
	Dict *dict;

	if(selindex >= ncands) return;

	w = cands[selindex];
	p = candspat[selindex];
//printf("pobox_select(%d), %s, %p\n",selindex,w,p);

	for(i=0;i<ndictionaries;i++){
		dict = &(dictionaries[i]);
		if(dict->poboxdict->type == POBOXDICT_STANDARD){
//printf("Standard dic\n");
			pobox_regword(dict->poboxdict,w,p,NULL);
			pobox_regword(dict->poboxdict,w,p,context);
		}
		return;
	}
}

/////////////////////////////////////////////////////////////////
//
//		$B=i4|2=(B/$B=*N;(BAPI
//
/////////////////////////////////////////////////////////////////

//
// $B=i4|2=(B
//
POBOX_INT pobox_init(void)
{
	pobox_usedict((POBoxDict*)NULL);
	rktable = InitRomaTable();
	return 0;
}

//
// $B=*N;(B
//
void pobox_finish(void)
{
}

//////////////////////////////////////////////////////////////////
#ifdef TEST
main()
{
	UCHAR *cands[100];
	UCHAR *patterns[100];
	int i,n;

	for(i=0;i<100;i++){
		cands[i] = (UCHAR*)malloc(100);
		patterns[i] = (UCHAR*)malloc(100);
	}

	pobox_usedict(NULL);
	pobox_searchmode(0);

	n = pobox_search("\221\235");
	n = pobox_getcands(cands,patterns,0,n);
	for(i=0;i < n;i++){
		printf("cand[%d] = [%s]\n",i,cands[i]);
	}

	n = pobox_search("masu");
	n = pobox_getcands(cands,patterns,0,n);
	for(i=0;i < n;i++){
		printf("cand[%d] = [%s]\n",i,cands[i]);
	}
}
#endif

