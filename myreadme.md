First of all we create a makefile 
its basically instructions for your compiler so it knows how to compile your code

then we are gonna create a src folder
an include folder inside it and inside it a main.h file

also we will have a main.c file in src folder
then we will define the name of our executable in our makefile



# exec = kscript.out
name of the final executable.
When the build is done, you’ll have a file called hello.out.

# sources = $(wildcard src/*.c)
grabs all .c files inside src/ directory.
wildcard is a Make function that matches all files by a pattern. So if you have src/main.c, src/utils.c, they’re both included.

# objects = $(sources:.c=.o)
transforms all .c files into .o files.
So src/main.c becomes src/main.o, etc.
These .o (object) files are intermediate files compiled from .c files.

# flags = -g
flags passed to gcc.
-g includes debug info in the compiled binary, so tools like gdb can be used to debug later.

# Build Rules
$(exec): $(objects)
	\gcc $(objects) $(flags) -o $(exec)
    the main rule.
    To build hello.out, compile and link all object files together."
    gcc takes all .o files, applies -g, and outputs hello.out.

%.o: %.c include/%.h 
	gcc -c $(flags) $< -o $@
     a pattern rule.
     To build x.o, you need both x.c and include/x.h.
     $< = the source file (x.c)
     $@ = the target file (x.o)
     gcc -c compiles the .c file to .o without linking.
     Key point: If you change x.c or x.h, Make knows to recompile x.o.

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o

Cleanup
phony target
Removes the hello.out executable
Removes any .o files in current and src/ directory
The - before rm tells Make to ignore errors, like if the file doesn’t exist.


so when you write your code for main.c file and then in terminal just inside the main folder you should be
type 
make 
it should compile the program
and you would get a kscript.out file
and when you type in terminal ./kscript.out
it should execute the Hello World!

now we add a install section in makefile
install:
	make
	cp ./kscript.out /usr/local/bin/kscript



    Runs the default make target — which means it builds your project (compiles all source files and links them into kscript.out).
    Copies the built executable (kscript.out) to /usr/local/bin/kscript.

This makes your program globally accessible via the terminal, so now you can just type hello to run it from anywhere.



and then in terminal run by using
sudo make install
you get

make
make[1]: `kscript.out' is up to date.
cp ./kscript.out /usr/local/bin/script



argc = argument count (how many command-line arguments were passed)
argv = argument vector (an array of strings)
argv[0] is the name of the program
argv[1], argv[2], etc. are the actual arguments


now the kscript binary is available on your system globally

now on just typing kscript in terminal you get the output as
"Hello World!"

******************************************************************************
# 2 lexer
set of functions that know how to turn your source code into tokens