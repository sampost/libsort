TARGET=libsort.a
OBJS=sort.o bubblesort.o
CC=gcc
AR=ar
CFLAGS=-g -O2


all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) -cr $(TARGET) $(OBJS)


clean:
	-rm -f $(OBJS) $(TARGET) *~
