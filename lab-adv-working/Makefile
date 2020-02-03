#define the macros
SDIR = ./src
ODIR = ./obj
IDIR = ./inc

_SRCS= hello.c hellof.c hellof2.c
_OBJS= hello.o hellof.o hellof2.o
_DEPS= hellof2.h hello.h

SRCS = $(patsubst %, $(SDIR)/%, $(_SRCS))
OBJS = $(patsubst %, $(ODIR)/%, $(_OBJS))
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))


CC= gcc

#$(OBJS): $(SRCS) $(DEPS)
#	$(CC) -c -o $@ $<

all: hello hello-d

#$(ODIR)/%.0 : %.c $(DEPS)
#	$(CC) -c -g -o $@ $< 

hello-d: $(SRCS)  $(DEPS)
	$(CC) -g -o $@ $^ 

hello: $(SRCS)  $(DEPS)
	$(CC) -o $@ $^

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
