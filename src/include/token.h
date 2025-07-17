#ifndef TOKEN_H
#define TOKEN_H
// typedef struct TOKEN_STRUCT
//     {
//         enum{
//             TOKEN_ID,
//             TOKEN_EQUALS,
//             TOKEN_SEMI,
//             TOKEN_STRING,
//             TOKEN_LPAREN,
//             TOKEN_RPAREN,
//         }type;
//         char* value;
//     } token_T;

typedef enum {
    TOKEN_ID,
    TOKEN_EQUALS,
    TOKEN_SEMI,
    TOKEN_STRING,
    TOKEN_LPAREN,
    TOKEN_LBRACE,
    TOKEN_RPAREN,
    TOKEN_RBRACE,
    TOKEN_COMMA,
    TOKEN_EOF
} TokenType;

typedef struct TOKEN_STRUCT {
    TokenType type;
    char* value;
} token_T;

token_T* init_token(int type, char*value);
#endif