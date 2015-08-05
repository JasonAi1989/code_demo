objs = main.o joseph.o 
main: $(objs)
	$(CC) $^ -o $@

sources = main.c joseph.c

include $(sources:.c=.d)

%.d:%.c
	set -e;rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\o[ :]*,\1.o $@ :,g' < $@.$$$$ >$@; \
	rm -f $@.$$$$

clean:
	@echo "cleanning project"
	-rm main *.o *.d
	@echo "clean completed"

.PHONY: clean
