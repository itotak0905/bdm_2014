CC = gcc
CFLAGS = -Wall -lwiringPi

SRCS = $(shell find . -name "*.c")
HEADS = $(shell find . -name "*.h")
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
OUT = a.out


a.out: $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)
.c.o:	
	$(CC) -c $< $(CFLAGS)
.PHONY: clean
clean:
	rm -f $(OBJS) $(DEPS) $(OUT)

