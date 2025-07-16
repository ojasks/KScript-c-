#include<stdio.h>
// now we write our main entry point 
#include "include/lexer.h"
#include "include/parser.h"
#include "include/visitor.h"
#include "include/io.h"
#include <stdlib.h>


void print_help()
{
  printf("Usage : \nkscript.out <filename>\n");
  exit(1);
}
int main(int argc , char* argv[])  
{

  if(argc < 2 ) 
  print_help();

    lexer_T* lexer = init_lexer(
        get_file_contents(argv[1])
    );

    parser_T* parser = init_parser(lexer);
    AST_T* root = parser_parse(parser);
    visitor_T* visitor = init_visitor();
    visitor_visit(visitor,root);

    return 0;
}








// #include <stdio.h>
// #include <stdlib.h>

// #include "include/lexer.h"
// #include "include/parser.h"
// #include "include/visitor.h"
// #include "include/io.h"

// void print_help()
// {
//     printf("Usage:\n  kscript.out <filename>\n");
// }

// int main(int argc, char* argv[])  
// {
//     const char* filepath;

//     if (argc >= 2) {
//         filepath = argv[1];
//     } else {
//         // Fallback file if no argument is passed
//         filepath = "examples/default.kscript";
//         printf("No file provided. Falling back to: %s\n", filepath);
//     }

//     char* file_content = get_file_contents(filepath);
//     if (!file_content) {
//         fprintf(stderr, "Failed to read file: %s\n", filepath);
//         print_help();
//         return 1;
//     }

//     lexer_T* lexer = init_lexer(file_content);
//     parser_T* parser = init_parser(lexer);
//     AST_T* root = parser_parse(parser);
//     visitor_T* visitor = init_visitor();
//     visitor_visit(visitor, root);

//     return 0;
// }




















  // token_T* token = (void*)0;
    
    // while((token = lexer_get_next_token(lexer)) != (void*)0){
    //     printf("TOKEN(%d, %s)\n", token->type, token->value);
    // }


    
    // printf("%d\n",root->type);
    // printf("%d\n",root->compound_size);