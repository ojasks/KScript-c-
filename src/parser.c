#include "include/parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/AST.h"


parser_T* init_parser(lexer_T* lexer)
{
    parser_T* parser = calloc(1,sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->current_token = lexer_get_next_token(lexer);
    parser->prev_token = parser->current_token;

    return parser;
}

void parser_eat(parser_T* parser, int token_type)
{
    if(parser->current_token->type == token_type)
    {
        parser->prev_token = parser->current_token;
        parser->current_token = lexer_get_next_token(parser->lexer);
    }
    else
    {
        printf(
            "Unexpexted Token '%s' with type '%d'",
            parser->current_token->value,
            parser->current_token->type
        );
        exit(1);
    }
}

AST_T* parser_parse(parser_T* parser)
{
    return parser_parse_statements(parser);
}

AST_T* parser_parse_statement(parser_T* parser)
{
    switch (parser->current_token->type)
    {
        case TOKEN_ID: return parser_parse_id(parser);
        case TOKEN_EOF: return NULL; // safe exit
         default:
            printf("❌ Unexpected token in parser_parse_statement: type = %d, value = %s\n",
                parser->current_token->type,
                parser->current_token->value);
        
    }
    return init_ast(AST_NOOP);
}

AST_T* parser_parse_statements(parser_T* parser)
{
    AST_T* compound = init_ast((AST_COMPOUND));
    compound->compound_value = calloc(1,sizeof(struct AST_STRUCT*));
    AST_T* ast_statement = parser_parse_statement(parser);

    if (ast_statement)
    compound->compound_value[0] = ast_statement;
    else
    compound->compound_size = 0;

      compound->compound_size +=1;

    while(parser->current_token->type == TOKEN_SEMI)
    {
        if (parser->current_token->type == TOKEN_RBRACE)
            break;
    parser_eat(parser, TOKEN_SEMI);

    AST_T* next_statement = parser_parse_statement(parser);

    if (!next_statement) break;

    if(ast_statement){
    compound->compound_size++;
    compound->compound_value = realloc(
    compound->compound_value,
    compound->compound_size * sizeof(struct AST_STRUCT*)
    );
    compound->compound_value[compound->compound_size - 1] = next_statement;
    
    }
}
    return compound;
}

AST_T* parser_parse_expr(parser_T* parser)
{
    switch(parser->current_token->type)
    {
         case TOKEN_ID: return parser_parse_id(parser);
        case TOKEN_STRING: return parser_parse_string(parser);
         default: printf("Unexpected token in parser_parse_expr: %d\n", parser->current_token->type);
        
    }
    return init_ast(AST_NOOP);
}

// AST_T* parser_parse_factor(parser_T* parser)
// {

// }

// AST_T* parser_parse_term(parser_T* parser)
// {

// }

AST_T* parser_parse_function_call(parser_T* parser)
{
    AST_T* function_call = init_ast(AST_FUNCTION_CALL);
    
    function_call->function_call_name = parser->prev_token->value;
    parser_eat(parser, TOKEN_LPAREN);


    function_call->function_call_arguments = calloc(1,sizeof(struct AST_STRUCT*));

    AST_T* ast_expr = parser_parse_expr(parser);
    function_call->function_call_arguments[0] = ast_expr;
    function_call->function_call_arguments_size +=1;
    

    while(parser->current_token->type == TOKEN_COMMA)
    {
        parser_eat(parser,TOKEN_COMMA);

        AST_T* ast_expr = parser_parse_expr(parser);
        function_call->function_call_arguments_size +=1;
        function_call->function_call_arguments = realloc(
            function_call->function_call_arguments,
            function_call->function_call_arguments_size * sizeof(struct AST_STRUCT*)
        );
        function_call->function_call_arguments[function_call->function_call_arguments_size-1]  = ast_expr;
    }
    parser_eat(parser,TOKEN_RPAREN);

    return function_call;
}

AST_T* parser_parse_variable_definition(parser_T* parser)
{
    parser_eat(parser, TOKEN_ID);
    char* variable_defintion_variable_name = parser->current_token->value;
    parser_eat(parser, TOKEN_ID);
    parser_eat(parser, TOKEN_EQUALS);
    AST_T* variable_defintion_value = parser_parse_expr(parser);

    AST_T* variable_defintion = init_ast(AST_VARIABLE_DEFINITION);
    variable_defintion->variable_definition_variable_name = variable_defintion_variable_name;
    variable_defintion->variable_defintion_value = variable_defintion_value;

    return variable_defintion;

}

AST_T* parser_parse_function_definition(parser_T* parser)
{
     AST_T* ast = init_ast(AST_FUNCTION_DEFINITION);
    parser_eat(parser, TOKEN_ID); //function
    char* function_name = parser->current_token->value;
    parser_eat(parser, TOKEN_ID); //function
    parser_eat(parser, TOKEN_LPAREN); //function
    parser_eat(parser, TOKEN_RPAREN); //function
    parser_eat(parser, TOKEN_LBRACE); //function
    ast->function_definition_body = parser_parse_statements(parser);
    parser_eat(parser, TOKEN_RBRACE); //function

    return ast;

}

AST_T* parser_parse_variable(parser_T* parser)
{
    char* token_value = parser->current_token->value;
    parser_eat(parser, TOKEN_ID);

    if(parser->current_token->type == TOKEN_LPAREN)
    return parser_parse_function_call(parser);

    AST_T* ast_variable = init_ast(AST_VARIABLE);
    ast_variable->variable_name = token_value;

    return ast_variable;
}

AST_T* parser_parse_string(parser_T* parser)
{
    AST_T* ast_string = init_ast(AST_STRING);
    ast_string->string_value = parser->current_token->value;

    parser_eat(parser, TOKEN_STRING);
    return ast_string;
}

AST_T* parser_parse_id(parser_T* parser)
{
    if(strcmp(parser->current_token->value, "var") == 0)
    {
        return parser_parse_variable_definition(parser);
    }
    else if(strcmp(parser->current_token->value, "function") == 0)
    {
        return parser_parse_function_definition(parser);
    }
    else{
        return parser_parse_variable(parser);
    }
}