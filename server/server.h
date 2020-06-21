#ifndef _SERVER_H_
#define _SERVER_H_


//#ifdef NO_GETDTABLESIZE
//#define MAXDTAB		_NFILE
//#else
//#define MAXDTAB		getdtablesize()	
//				/* max number of file descriptors */
//				/* it returns 64 on SunOS 4.x & NEWS OS 3.3 */
//				/* it returns 30 on SunOS 3.x & NEWS OS 2.2 */
//				/* 20 is guaranteed on all machines */
//#endif
// Cygwinでこの値が256になってしまったので、小さい値に固定する。
#define MAXDTAB 32

#define MAXCLIENT	64	/* max number of clients */
                                /* (must be larger than MAXDTAB-1) */
#define	BUFSIZE		512	/* max size of a request */
#define	MAXQUE		5

extern int portnum;
extern int server_debug;

typedef int ProcessFunc(int);
void server(int portnum, ProcessFunc *func);
#endif
