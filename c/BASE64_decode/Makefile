C = gcc
CFLAG = -g
INCLUDE = -I.
RM = rm -f
SRC = $(wildcard *.c)
LINK_FLAG := -lssl -lcrypto
PROGRAM = app_BASE64_decode

all:
	$(C) $(CFLAG) $(SRC) $(INCLUDE) -o $(PROGRAM) $(LINK_FLAG)


clean:
	$(RM) *.o *.d