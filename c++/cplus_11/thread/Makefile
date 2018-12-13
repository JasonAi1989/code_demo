CC=g++
LD=g++
CPPFLAGS=-Wall -std=c++11 -ggdb
LDFLAGS=-pthread

SRCS := $(wildcard *.cc)
BINS := $(SRCS:%.cc=%)

all:$(BINS)

%.o: %.cc
	@echo + CC $<
	$(CC) $(CPPFLAGS) -o $@ -c $<

.PHONY:
	clean

clean:
	rm $(BINS)
