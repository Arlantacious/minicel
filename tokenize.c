#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "tokenize.h"

static void debug(Token* tokens)
{
    for (Token* token = tokens; token->type != END_OF_INPUT; ++token)
    {
        switch (token->type)
        {
            case CELL:
                printf("CEL = %c%d", token->value.cell_value.row, token->value.cell_value.col);
                break;
            case STRING:
                printf("STRING: %s ", token->value.string_value);
                break;
            case FLOAT:
                printf("FLOAT: %f ", token->value.float_value);
                break;
            case INTEGER:
                printf("INTEGER: %d ", token->value.integer_value);
                break;
            case ADD:
                printf("ADD ");
                break;
            case SUBTRACT:
                printf("SUBTRACT ");
                break;
            case MULTIPLY:
                printf("MULTIPLY ");
                break;
            case DIVIDE:
                printf("DIVIDE ");
                break;
            case MODULO:
                printf("MODULO ");
                break;
            case EQUAL:
                printf("EQUAL ");
                break;
            case LEFT_PARENTHESIS:
                printf("LEFT_PARENTHESIS ");
                break;
            case RIGHT_PARENTHESIS:
                printf("RIGHT_PARENTHESIS ");
                break; 
            case END_OF_INPUT:
                break;
            default:
                printf("[INVALID_TOKEN] ");
        } 
    }
}

static void try_token(char* input, Token* token, const TokenType token_type, const char* expr)
{
    static regex_t regex;
    regcomp(&regex, expr, 0);
    regmatch_t matches[1];
    int reti = regexec(&regex, expr, 1, matches, 0);
    if(!reti)
    {
        size_t szmatch = matches[0].rm_eo - matches[0].rm_so;
        char* match_s = malloc(szmatch + 1);
        match_s[szmatch] = 0;
        strncpy(match_s, input + matches[0].rm_so, szmatch);
        token->type = token_type;
        switch (token_type)
        {  
            case CELL:
                token->value.cell_value.col = match_s[0];
                token->value.cell_value.row = atoi(match_s + 1);
                break;
            case STRING:
                token->value.string_value = match_s;
                break;
            case FLOAT:
                token->value.float_value = atof(match_s);
                break;
            case INTEGER:
                token->value.integer_value = atoi(match_s);
                break;
            case ADD:
            case SUBTRACT:
            case MULTIPLY:
            case DIVIDE:
            case MODULO:
            case EXPONENT:
            case EQUAL:
            case LEFT_PARENTHESIS:
            case RIGHT_PARENTHESIS:
            case END_OF_INPUT:
                break;
        }
        *input += strlen(match_s);
        free(match_s);
    }
}

Token* tokenize(char* input)
{
    Token* tokens = (Token*)malloc(strlen(input) * sizeof(Token) + 1);
    for (size_t i = 0; i < strlen(input); ++i)
    {
        tokens[i].type = END_OF_INPUT;
    }
    Token* next_token = tokens;
    for (size_t input_start = 0; input_start < strlen(input); input_start++)
    { 
        strncpy(input, input + input_start, 0);
        try_token(input, next_token, CELL, "\\s*[A-Z]\\d+\\s*");
        try_token(input, next_token, STRING, "\\s*\\\".+\"\\s*");
        try_token(input, next_token, FLOAT, "\\s*\\+\\-]?\\d+\\.\\d*\\s*");
        try_token(input, next_token, INTEGER, "\\s*\\+\\-]?\\d+\\s*");
        try_token(input, next_token, ADD, "\\+");
        try_token(input, next_token, SUBTRACT, "\\-");
        try_token(input, next_token, MULTIPLY, "\\*");
        try_token(input, next_token, DIVIDE, "\\/");
        try_token(input, next_token, MODULO, "\\%");
        try_token(input, next_token, MODULO, "\\^");
        try_token(input, next_token, EQUAL, "\\=");
        try_token(input, next_token, LEFT_PARENTHESIS, "\\(");
        try_token(input, next_token, RIGHT_PARENTHESIS, "\\)"); 
        ++next_token; 
    } 
    debug(tokens);
    return tokens;
}
