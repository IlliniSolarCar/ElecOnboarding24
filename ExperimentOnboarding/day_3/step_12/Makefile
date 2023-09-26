# Define a pattern rule that compiles every .c file into a .o file
%.o : %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

# Define a pattern rule that has no pattern in the prerequisites.
# This just creates empty .c files when needed.
%.c:
	touch $@
	echo "int main() { return 0; }" > $@

test:

nothing:

empty.c:

clean:
	rm -f test nothing.* empty.*
