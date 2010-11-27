TARGETS=intsort
OBJS=intsort.o
LIBDIR=..
LIBS=$(LIBDIR)/libsort.a
CC=gcc
CFLAGS=-g -I$(LIBDIR)

all: $(TARGETS)

intsort: $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) -o intsort $(OBJS) $(LIBS) -I$(LIBDIR)

$(LIBDIR)/libsort.a:
	cd $(LIBDIR) && make clean && make

clean:
	-rm -f $(OBJS) $(TARGETS) $(LIBS) *~
