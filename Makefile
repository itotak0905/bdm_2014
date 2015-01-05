CC = gcc

SRCS = $(shell find . -name "*.c")
HEADS = $(shell find . -name "*.h")
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
OUT = a.out


a.out: $(OBJS)
	$(CC) -o $@ $(OBJS)
.c.o:	
	$(CC) -c $<
.PHONY: clean
clean:
	rm -f $(OBJS) $(DEPS) $(OUT)

