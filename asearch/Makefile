#
#	$Date: 2001/07/23 07:18:15 $
#	$Revision: 1.2 $
#
CC = gcc
CFLAGS = -Xcpluscomm
WTANGLE = perl ../wtangle/wtangle

libasearch.a: asearch.o
	ar cr libasearch.a asearch.o
asearchtest: asearchtest.o libasearch.a
	$(CC) $(CFLAGS) asearchtest.o libasearch.a -o asearchtest

asearch.o: asearch.h asearch.c

asearch.h: asearch.html
	$(WTANGLE) asearch.html
asearch.c: asearch.html
	$(WTANGLE) asearch.html
asearchtest.c: asearch.html
	$(WTANGLE) asearch.html

clean:
	-\rm -f \#* *~ *.o *.a asearch.h asearch.c asearchtest.c \
		asearchtest a.out
