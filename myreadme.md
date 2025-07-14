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

In C (and C++), .h files are header files — they declare functions, types, and structs so they can be used in other files. Think of them like contracts.

.c files are source files — they implement the logic you declared in the header.

You can reuse a header across multiple .c files, which is great for modular code. It also keeps your implementation clean and separated.

token.h — The token definitions
defines what a token is — a token is a basic unit the lexer emits (like ID, STRING, EQUALS, etc.)

Creates a token_T object in heap memory with zero-initialized bytes.
Sets the token’s type, like TOKEN_ID, TOKEN_STRING, etc.
Sets the actual text value, like "name", "=", etc.



TokenType enum defines different types of tokens.
token_T struct stores the type and actual string value (e.g., "name" or "=").
init_token(...) is declared in token.h (implemented in token.c).

token.c — Token constructor implementation
Implements the init_token function to create new tokens using calloc.

lexer.h — The lexer definitions
lexer.c — Lexer logic implementation
Key Functions:
1. init_lexer(contents)
Creates a new lexer object with the input source code.

2. lexer_advance
Moves the character pointer one step forward.

3. lexer_get_next_token
The main loop: decides what the next token should be.

4. lexer_collect_string
If we find ", it collects a whole string "like this".

5. lexer_collect_id
If we find letters or digits (like var, name), it collects the identifier.

6. lexer_advance_with_token
Returns a token and advances the lexer.

7. lexer_get_current_char_as_string
Returns the current character as a dynamically allocated string (for token values).

main.c — Entry point / testing
your test harness — it feeds a simple script to the lexer and prints out the tokens.



main.c  ─────┐
             │
             ▼
         lexer.c  ───── uses ─────▶ token.c
             ▲                        ▲
             │                        │
         lexer.h                  token.h
Your lexer produces tokens. Each token is created using init_token() from token.c.
Header files ensure each .c file knows how to talk to the others.


A lexer (short for lexical analyzer) is the first part of a compiler or interpreter.

Its job:
It takes raw source code like this:

js
Copy
Edit
var name = "ojas ks";
print(name);
…and splits it into meaningful pieces called tokens, such as:

var → identifier

name → identifier

= → equals sign

"ojas ks" → string literal

; → semicolon

etc.
This makes it easier for the parser to understand the structure of the code.



What does calloc do?
Allocates memory for 1 object of size sizeof(struct TOKEN_STRUCT)
Initializes all bytes to zero
This is safer than malloc() when you want to avoid uninitialized memory bugs.


in this context?
A token is just a struct with:
type: What kind of thing it is (identifier, string, equals sign...)
value: The actual characters found in the code (like "name")
Tokens are the building blocks the parser will later use to make sense of the program.

Understanding main.c
The lexer reads one token at a time until there are no more.
Prints the type and value of each token.






If you wanted to write this in C++, what would change?
C++ lets you do all this in a much cleaner and more OOP-friendly way.

You’d use classes instead of manually managing structs and functions.

You wouldn't need typedef struct, just class or struct.

You could avoid raw malloc/calloc/free and use constructors.

You might combine .h and .c into .hpp and .cpp.


Token.cpp
Implements the constructor for Token.
This uses an initializer list to assign type and value directly when creating a new Token.

The constructor takes in a source code string.
getNextToken() returns one token at a time.
The private helpers:
advance() moves to the next character.
skipWhitespace() ignores spaces/newlines.
collectString() gathers a full string like "ojas ks".
collectId() collects identifiers like print, name.
currentCharAsString() returns current character as a string.

main.cpp
Purpose:
This is the entry point. It sets up the lexer and prints each token one by one.
Initializes a lexer with a small snippet of code.
Fetches tokens one by one and prints them.
delete token; frees memory after each use.


main.cpp
  └── uses Lexer.hpp
          └── uses Token.hpp
Lexer.cpp
  └── implements Lexer logic using Token
Token.cpp
  └── implements the Token constructor

Everything revolves around Token objects.
Lexer breaks code into Tokens.
Main shows how this all works together.

Main: Feeds code to the lexer and prints all the tokens
Lexer: Splits code into tokens using character-by-character logic
Token: A small unit like =, "ojas ks", or name

******************************************************************************
# 3 Parser
first thing we gonna do is define the ast .h
then ast.c

in ast.c

AST_T* init_ast(int type)
{
    AST_T* ast = calloc(1,sizeof(struct AST_STRUCT));

Creates a new AST node.
calloc allocates memory and zeroes it out.
type is the kind of AST node (e.g., assignment, string, function call).

Initializes all fields to NULL (or zero for the size).
This avoids undefined behavior if you try to use them later without setting them.

What this code is for
You call this when you're constructing nodes for your abstract syntax tree (AST).


compound is a list of multiple statements
