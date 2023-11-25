#include <stdlib.h>
#include "tokenize.h"

static void cell_value_extraction(Token* tokens)
{

}

static void expression_segmentation(Token* tokens)
{
    static int lparen;
    static int rparem;
}

static void* parse(Token* tokens)
{
    float result;
    void* values[sizeof(*tokens) / sizeof(float)];
    for (Token* token = tokens; tokens->type != END_OF_INPUT; ++token)
    {
        switch (token->type)
        {
            case CELL:
                cell_value_extraction(tokens);
                break;
            case LEFT_PARENTHESIS:
            case RIGHT_PARENTHESIS:
                expression_segmentation(tokens);
            case FLOAT:
            case INTEGER:
                break;
            case EXPONENT:
                break;
            case MULTIPLY:
                break;
            case DIVIDE:
                break;
            case MODULO:
                break;
            case ADD:
                break;
            case SUBTRACT:
                break;
            case STRING:
            case EQUAL:
            case END_OF_INPUT:
                break;
        }
    }
    return 0;
}


