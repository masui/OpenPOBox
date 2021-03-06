//
//	$Date: 2002/07/06 09:16:59 $
//	$Revision: 1.10 $
//
//	POBox API$B$r;H$C$?(BPOBox Server$B$r<BAu(B
//
//   $B!&(BUSEWNN$B$,Dj5A$5$l$F$$$k$H$-$OF0E*[#Kf8!:w$r4hD%$C$F9T$J$&$+$o$j$K(B
//     Jserver$B$KJQ49$r0MMj$9$k!#(B
//   $B!&(Bskkserv$B$O(BEUC$B$N4A;z$NFI$_$r<u$1$D$1$k$,!"$3$NHG$O%m!<%^;z$r(B
//     $B<u$1$D$1$k$h$&$K$J$C$F$$$k!#(B($BIaDL$N(BSKK$B$G$O;H$($J$$(B)
//
//	WinCE$B$K$O(Bread(),write(),close()$B$J$I$,$J$$$h$&$J$N$G(B
//	WinSock$B$N(Brecv(),send(),closesocket()$B$J$I$r;H$&(B

#include <stdio.h>
#if defined(POCKET_SIZE) || defined(PALM_SIZE)
#define isupper(c) ((c) >= 'A' && (c) <= 'Z')
#else
#include <strings.h>
#endif
#include "server.h"
#include "poboxlib.h"

#ifdef USE_PROFILER
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
#endif


#define POBOXSERVERPORT 1178

#define MAXCANDS 100
#define MAXWORDLEN 100
unsigned char *cands[MAXCANDS],*candspat[MAXCANDS];

int process(int);

unsigned char context[MAXCLIENT][MAXWORDLEN];

char *revision = "$Revision: 1.10 $";

int poboxdebug = 0;

// <a name="dictionaries">
POBoxDict learndic = {
#if defined(POCKET_SIZE) || defined(PALM_SIZE)
	"\\POBox\\learndic",
#else
	"./learndic",
#endif
	POBOXDICT_STANDARD,
	POBOXDICT_TEXT,
	0 // not read-only
};
#ifdef USESARY
POBoxDict sarydic = {
#if defined(POCKET_SIZE) || defined(PALM_SIZE)
	"\\POBox\\staticdic",
#else
	"./staticdic",
#endif
	POBOXDICT_STANDARD,
	POBOXDICT_SARY,
	1 // read-only
};
#endif
#ifdef USELOOKUP
POBoxDict lookupdic = {
#if defined(POCKET_SIZE) || defined(PALM_SIZE)
	"\\POBox\\staticdic",
#else
	"./staticdic",
#endif
	POBOXDICT_STANDARD,
	POBOXDICT_LOOKUP,
	1 // read-only
};
#endif

#if defined(POCKET_SIZE) || defined(PALM_SIZE)
WinMain()
{
#else
main(int argc, char **argv)
{
	if(argc > 1) poboxdebug = 1;
#endif
	if(pobox_init() < 0) exit(0);
	if(pobox_usedict(&learndic) < 0) exit(0);
#ifdef USESARY
	if(pobox_usedict(&sarydic) < 0) exit(0);
#endif
#ifdef USELOOKUP
	if(pobox_usedict(&lookupdic) < 0) exit(0);
#endif
	server(POBOXSERVERPORT,process);
	pobox_finish();
}

process(int sock)
{	
	unsigned char buf[1000],combuf[BUFSIZE];

	unsigned char w[100],p[100];
	int i,n;
	char *host;
	char *pat;
	int patlen;

	if((n = recv(sock, &combuf[0], BUFSIZE, 0)) <= 0)  return -1;
	combuf[n] = '\0';
	while(n > 0 && (combuf[n-1] == '\n' || combuf[n-1] == '\r')){
		combuf[n-1] = '\0';
		n--;
	}
	if(poboxdebug) printf("command: [%s]\n",combuf);
	switch(combuf[0]){
	case '0':
		pobox_usedict(NULL); // save all existing changes
		return -1; // this makes the server's main routine disconnect 
	case '1':
		for(pat=combuf+1;*pat;pat++){
			if(isupper(*pat)) *pat = tolower(*pat);
		}
		pat = combuf+1;
		patlen = strlen(pat);
		pobox_context(context[sock],strlen(context[sock]));
		if(pat[patlen-1] == ' '){
			pobox_searchmode(0);
			pat[patlen-1] = '\0';
		}
		else {
			pobox_searchmode(POBOX_EXACT);
		}
		n = pobox_search(pat);
		pobox_getcands(cands,candspat,0,n);
		if(n == 0){
			sprintf(buf,"4%s\n",pat);
		}
		else {
			strcpy(buf,"1\t");
			for(i=0;i< n;i++){
				strcat(buf,cands[i]);
				strcat(buf,"\t");
			}
			strcat(buf,"\n");
		}
		if(send(sock, buf, strlen(buf), 0) < 0) return -1;
		return 0;
	case '2':
		if(send(sock, revision+11, strlen(revision)-13, 0) < 0) return -1;
		return 0;
	case '3':
host = "dummyhost";
		if(send(sock,host,strlen(host),0) < 0) return(-1);
		return 0;
	case '4':
		strcpy(context[sock],combuf+1);
		if(send(sock,"1\n",2,0) < 0) return -1;
		return 0;
	case '5':
		n = sscanf(combuf+1,"%s %s",w,p);
		if(send(sock,"1\n",2,0)<0) return -1;
		if(n == 2){
			for(pat=p;*pat;pat++){
				if(isupper(*pat)) *pat = tolower(*pat);
			}
			pobox_regword(&learndic,w,p,NULL);
			strcpy(context[sock],w);
		}
		return 0;
	case '6':
		n = sscanf(combuf+1,"%s %s",w,p);
		if(send(sock,"1\n",2,0)<0) return -1;
		if(n == 2){
			pobox_delword(&learndic,w,p);
		}
		return 0;
	case '7':
		if(send(sock,"1\n",2,0) < 0) return -1;
		// pobox_usedict(NULL);
		// pobox_savedic(...)??
		pobox_save(&learndic);
		return 0;
	case '8':
		n = sscanf(combuf+1,"%d",&i);
		if(send(sock,"1\n",2,0) < 0) return -1;
		if(n == 1){
			pobox_select(i);
			strcpy(context[sock],cands[i]);
		}
		return 0;
	case 'Q':
		exit(0);
	default:
		return -1;
	}
}
