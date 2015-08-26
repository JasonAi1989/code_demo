C = gcc
CFLAG = -g
INCLUDE = 
RM = rm -f
SRC = $(wildcard *.c)
LINK_FLAG := -lssl -lcrypto
PROGRAM = app_BASE63

all:
	$(C) $(CFLAG) $(SRC) $(INCLUDE) -o $(PROGRAM) $(LINK_FLAG)


clean:
	$(RM) *.o *.d