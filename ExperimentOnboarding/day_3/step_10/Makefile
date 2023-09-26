objects = foo.o bar.o all.o
all: $(objects)

# These files compile via implicit rules
foo.o: foo.c
bar.o: bar.c
all.o: all.c

%.c:
	touch $@

clean:
	rm -f *.c *.o all
	