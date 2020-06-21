#include <stdio.h>
#if defined(POCKET_SIZE) || defined(PALM_SIZE)
#include <windows.h>
#include <winsock.h>
#define close(x) closesocket(x)
#else
#include <ctype.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif

#include "server.h"

int server_debug = 0;

static int initsock;		// 要求待ちsocket
static int clientfd[MAXCLIENT];	// 各クライアント用socket
static int nclients = 0;

#if defined(POCKET_SIZE) || defined(PALM_SIZE)
static void bzero(char *p, int size)
{
	while(size-- > 0) *p++ = 0;
}

static void perror(char *s)
{
}
#endif

static void error(char *s)
{
	perror(s);
	exit(-1);
}

void server(int portnum, ProcessFunc *func)
{
	int i;
	int len;
	char value;
	struct sockaddr_in sin;
	struct sockaddr_in from;
	struct servent *sp;

	fd_set readfds, writefds, exceptfds;
	fd_set getrfds();

	bzero((char*)&sin, sizeof(sin));

	sin.sin_family = AF_INET;
	//sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(portnum); 

	if((initsock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		error("socket error; socket cannot be created");
#if defined(POCKET_SIZE) || defined(PALM_SIZE)
// テリオス用にMips/WinCE2.11でコンパイルすると
// ここでエラーになって異常終了してしまうので
// CE版のサーバでは使わないことにする。
#else
	value = 1;
        if (setsockopt(initsock, SOL_SOCKET, SO_REUSEADDR,
               (char *)(&value), sizeof(int)) < 0)
                error("setsockopt");
#endif
	if(bind(initsock, (struct sockaddr *)&sin, sizeof(sin))< 0) 
		error("bind error; the socket is already used");
	if(listen(initsock, MAXQUE) < 0) 
		error("listen error; something wrong happened with the socket");
	if(server_debug) printf("file descriptor for initsock is %d\n", initsock);

	FD_ZERO(&writefds);
	FD_ZERO(&exceptfds);
	for(;;){
		FD_ZERO(&readfds);
		FD_SET(initsock, &readfds);
		for (i = 0; i < nclients; i ++)
			FD_SET(clientfd[i], &readfds);
		if (select(MAXDTAB, &readfds, &writefds, &exceptfds, NULL) < 0)
			error("select error; something wrong happened with the socket");
		if(server_debug) printf("select: read file descriptor is %08x\n", readfds);
		if (FD_ISSET(initsock, &readfds)) {
			len = sizeof(from);
			if((clientfd[nclients++] = accept(initsock, &from, &len)) < 0) {
				error("accept error; something wrong happened with the socket");
			}
			if(nclients >= MAXDTAB-3) {
				send(clientfd[--nclients], "F", 1, 0);
				close(clientfd[nclients]);
			}
		}
		for (i = 0; i < nclients; i ++){
			if (FD_ISSET(clientfd[i], &readfds)) {
				if ((*func)(clientfd[i]) < 0) { 
			  		/* -1 means client closed the connection */
					close(clientfd[i]);
					clientfd[i] = clientfd[nclients-1];
					nclients--;
				}
			}
		}
	}
}
