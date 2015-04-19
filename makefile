# xfil v2.02 - simple makefile
#
# Made by Sasa on 26.6.1993.
#
# if you are using something else than gcc compiler put it here
CC= gcc
# this is a flag for speed and code optimization .You don't need it but 
# your program will not be so fast
CFLG= -O2
# this is the path for standard include files
ILIB= -I/usr/local/X11R5/include
# this is the path for standard files that use ld (loader-linker)
LLIB= -lX11 -L/usr/local/X11R5/lib
#
#
OBJ= fil.o testfil.o xfil.o
xfil: $(OBJ)
	$(CC) $(CFLG) $(OBJ) $(LLIB) -o xfil
fil.o: fil.c fil.h
	$(CC) $(CFLG) $(ILIB) -c fil.c
testfil.o: testfil.c fil.h
	$(CC) $(CFLG) $(ILIB) -c testfil.c
xfil.o: xfil.c fil.h
	$(CC) $(CFLG) $(ILIB) -c xfil.c
