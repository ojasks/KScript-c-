#include "include/AST.h"
#include <stdlib.h>

AST_T* init_ast(int type)
{
    AST_T* ast = calloc(1,sizeof(struct AST_STRUCT));
    ast->type = type;

    ast->scope = (void*)0;
     //  AST_VARIABLE_DEFINITON
    ast->variable_definition_variable_name = (void*)0;
    ast->variable_defintion_value = (void*)0;
     //  AST_FUNCTION_DEFINITON
    ast->function_definition_name = (void*)0;
    ast->function_definition_body = (void*)0;
        //  AST_STRING
    ast->variable_name = (void*)0;
        // AST_FUNCTION_CALL
    ast->function_call_name = (void*)0;
    ast->function_call_arguments = (void*)0;
    ast->function_call_arguments_size = 0;
        // AST_VARIABLE
    ast->string_value = (void*)0;
    //  AST_COMPOUND
    ast->compound_value = (void*)0;
    ast->compound_size = 0;

    return ast;
}