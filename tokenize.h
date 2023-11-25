typedef enum
{
    CELL,
    STRING,
    FLOAT,
    INTEGER,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    MODULO,
    EXPONENT,
    EQUAL,
    LEFT_PARENTHESIS,
    RIGHT_PARENTHESIS,
    END_OF_INPUT,
} TokenType;

typedef struct
{
    TokenType type;
    union
    {
        int integer_value;
        char *string_value;
        float float_value;
        struct
        {
            char row;
            int col;
        } cell_value;
    } value;
} Token;

Token* tokenize(char* input);
