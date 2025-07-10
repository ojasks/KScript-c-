exec = kscript.out  #name of our executable and define it as hello.out
sources = $(wildcard src/*.c) # where our source files are
objects = $(sources:.c=.o)  # we will create the objects, objects files are created by the compiler and links them together to create our executable
flags = -g


# now we tell it how to create the executable
$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

#how to create the o files
%.o: %.c include/%.h 
	gcc -c $(flags) $< -o $@   
# whenever it detects a change in object file its gonna re compile

install:
	make
	cp ./kscript.out /usr/local/bin/kscript
clean:
	-rm *.out
	-rm *.o
	-rm src/*.o
