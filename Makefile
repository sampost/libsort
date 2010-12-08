TARGET=libsort.a
OBJS=sort.o bubblesort.o mergesort.o quicksort.o quicksort.o
CC=gcc
AR=ar
CFLAGS=-g


all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) -cr $(TARGET) $(OBJS)


clean:
	-rm -f $(OBJS) $(TARGET) *~
