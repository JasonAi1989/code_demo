INC = -I.
SRC = $(wildcard *.c)
OBJ = demo_app

all: $(SRC)
	gcc $(SRC) $(INC) -o $(OBJ)

.PHONY : clean

clean:
	rm $(OBJ)

