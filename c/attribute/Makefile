all:
	gcc -Wall -o format format.c
	gcc structor.c -o structor
	gcc packed.c -o packed
	gcc aligned.c -o aligned
	gcc -c section.c
clean:
	rm -rf a.out format structor packed aligned section.o
