CC = gcc

SRCS = $(wildcard *.c)

PROGS = $(patsubst %.c,%,$(SRCS))

CFLAGS = -lpthread

all: $(PROGS)

%: %.c
	$(CC) -o $@ $< $(CFLAGS)
clean: 
	rm -f $(PROGS)