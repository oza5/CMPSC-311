CC := gcc
CFLAGS := -Wall
PROGS := main mainlink

.PHONY:all

all: $(PROGS)

mainlink: main.o doublylinkedlist.o mymalloc.o
	$(CC) $(CFLAGS) -Wl,--wrap,malloc -Wl,--wrap,free -o $@ main.o doublylinkedlist.o mymalloc.o

mymalloc.o:
	$(CC) $(CFLAGS) -DLINKTIME -c mymalloc.c

main: main.o doublylinkedlist.o
	$(CC) $(CFLAGS) -o $@ main.o doublylinkedlist.o

main.o: doublylinkedlist.h
doublylinkedlist.o: doublylinkedlist.h

.PHONY:clean

clean:
	rm -f $(PROGS) *.o
