#define the macros
SRCS= hello.c hellof.c hellof2.c
OBJS= hello.o hellof.o hellof2.o
DEPS= hello.h hellof2.h
CC= gcc

#$(OBJS): $(SRCS) $(DEPS)
#	$(CC) -c -o $@ $<

all: hello hello-d

hello-d: $(SRCS) $(DEPS)
	$(CC) -g -o $@ $^ 

hello: $(SRCS) $(DEPS)
	$(CC) -o $@ $^

.PHONY: clean

clean:
	rm edit $(OBJS)
