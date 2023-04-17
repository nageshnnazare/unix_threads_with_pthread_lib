CC = gcc

SRCS = $(wildcard *.c)

PROGS = $(patsubst %.c,%,$(SRCS))

CFLAGS = -lpthread

all: $(PROGS)

%: %.c
	$(CC) -o $@ $< $(CFLAGS)
test: $(PROGS)
	./$<
clean: 
	rm -f $(PROGS)