# Generated automatically from Makefile.in by configure.
#
#	$Date: 2002/02/17 14:04:38 $
#	$Revision: 1.6 $
#

WTANGLE = perl ../wtangle/wtangle

# for SGI
# CC=cc
# CFLAGS = -DUNIX  -DUSELOOKUP -Xcpluscomm \
#	-I../asearch -I../romakana -I../include -g

CC = gcc
CFLAGS = -DUNIX  -DUSELOOKUP \
	-I/usr/local/include -I/usr/local/lib/glib/include \
	-I/usr/local/include \
	-I../asearch -I../romakana -I../include -g

pbserver: pbserver.o server.o poboxlib.o romakana_he.o lookup.o
	$(CC) -o pbserver pbserver.o server.o poboxlib.o romakana_he.o \
		../asearch/libasearch.a  lookup.o

../asearch/libasearch.a:
	cd ../asearch; make
../asearch/asearch.h:
	cd ../asearch; make
../include/poboxlib.h: ../doc/api.html
	cd ../include; make

romakana_he.c: ../romakana/rklist
	cd ../romakana; perl rklist2rkc -h ../romakana/rklist > ../server/romakana_he.c

pbserver.o: pbserver.c ../include/poboxlib.h server.h
	$(CC) $(CFLAGS) -c pbserver.c

pbserver.c: pbserver.html
	$(WTANGLE) pbserver.html
server.c: server.html
	$(WTANGLE) server.html
server.h: server.html
	$(WTANGLE) server.html
poboxlib.o: poboxlib.c ../asearch/asearch.h
poboxlib.c: poboxlib.html 
	$(WTANGLE) poboxlib.html

winpbserver: pbserver.o server.o poboxlib.o romakana_he.o lookup.o resource.o
	$(CC) -o winpbserver pbserver.o server.o poboxlib.o romakana_he.o \
		../asearch/libasearch.a resource.o  lookup.o -mwindows
resource.o: pbserver.rc pbserver.ico
	windres -i pbserver.rc -o resource.o

clean:
	-\rm -f pbserver \
		server.c server.h pbserver.c poboxlib.c \
		*~ #* *.o

