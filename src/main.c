#include<stdio.h>
// now we write our main entry point 
#include "include/lexer.h"
#include "include/parser.h"
#include "include/visitor.h"

int main(int argc , char* argv[])  
{
    lexer_T* lexer = init_lexer(
        
        "var name = \" ojas ks\";\n"
        "var othername = \" gurman\";\n"
        "print(name,othername);\n"
    );

    parser_T* parser = init_parser(lexer);
    AST_T* root = parser_parse(parser);
    visitor_T* visitor = init_visitor();
    visitor_visit(visitor,root);

    return 0;
}





  // token_T* token = (void*)0;
    
    // while((token = lexer_get_next_token(lexer)) != (void*)0){
    //     printf("TOKEN(%d, %s)\n", token->type, token->value);
    // }


    
    // printf("%d\n",root->type);
    // printf("%d\n",root->compound_size);