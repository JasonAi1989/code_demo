CC=g++
LD=g++
CPPFLAGS=-Wall -std=c++11 -ggdb
LDFLAGS=-pthread

SRCS := $(wildcard *.cc)
INCS := $(wildcard *.h)
OBJS := $(SRCS:%.cc=%.o)
BIN := otn_pm_report
BINS := $(SRCS:%.cc=%)

all:$(BIN)

$(BIN):$(SRCS) $(INCS)
	$(CC) $(CPPFLAGS) -o $@ $(SRCS)

#%.o:%.cc
#	$(CC) $(CPPFLAGS) -o $@ -c $<

.PHONY:
	clean

clean:
	rm $(BIN)
