EX=
CC=gcc
SRCDIR=src
INCLUDEDIR=include
CFLAGS= -I"$(SRCDIR)" -I"$(INCLUDEDIR)"

all: FileAttributes.o Borland.o

FileAttributes.o: $(SRCDIR)/FileAttributes.c
	$(CC) -c $^ $(CFLAGS)

Borland.o: $(SRCDIR)/Borland.c
	$(CC) -c $^ $(CFLAGS)

clean:
	rm *.o $(TESTEX) $(EX)