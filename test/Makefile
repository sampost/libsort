TARGETS=intsort
OBJS=intsort.o
LIBDIR=..
LIBS=$(LIBDIR)/libsort.a
CC=gcc
CFLAGS=-g -I$(LIBDIR)

all: $(TARGETS)

intsort: $(OBJS)
	$(CC) $(CFLAGS) -o intsort $(OBJS) $(LIBS) -I$(LIBDIR)


clean:
	-rm -f $(OBJS) $(TARGETS) *~
