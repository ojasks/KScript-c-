#include "AST.h"

#ifndef SCOPE_H
#define SCOPE_H

typedef struct SCOPE_STRUCT
{
    AST_T** function_definitions;
    size_t function_definitions_size;
} scope_T;

scope_T* init_scope();
AST_T* scope_add_function_definition(scope_T* scope, AST_T* fedef);
AST_T* scope_get_function_definition(scope_T* scope, const char* fname);
#endif