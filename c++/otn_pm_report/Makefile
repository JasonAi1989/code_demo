BIN:otn_pm_report

CC=g++
CPPFLAGS=-Wall -std=c++11 -ggdb
LDFLAGS=-pthread
SRC=main.cc PmJobManager.cc

$(BIN):%.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o:%.cc
	$(CC) $(LDFLAGS) -o $@ $^

.PHONY:
	clean

clean:
	rm $(BIN)
