C = gcc
CFLAG = -g
INCLUDE = -I. 
RM = rm -f
SRC = $(wildcard *.c)
LINK_FLAG := 
PROGRAM = app_SHA1

all:
	$(C) $(CFLAG) $(SRC) $(INCLUDE) -o $(PROGRAM) $(LINK_FLAG)


clean:
	$(RM) *.o *.d
