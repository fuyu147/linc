#include "repl.h"

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parseMatrixPrefix(ReplArguments *replArguments, int *i, const char *line,
                      char currentChar, int strLen)
{
        // Check if it's an operator (m-, m+, m*, m.)
        if (*i + 1 < strLen)
        {
                char next_char = line[*i + 1];
                if (next_char == TOKEN_operatorMinus ||
                    next_char == TOKEN_operatorPlus ||
                    next_char == TOKEN_operatorStar ||
                    next_char == TOKEN_operatorDot)
                {
                        // "mX" + null terminator. Length 2 + 1 for null.
                        char *item_str = (char *)malloc(3);

                        if (!item_str)
                        {
                                printf("malloc failed\n");
                                return 1;
                        }

                        item_str[0]      = currentChar; // 'm'
                        item_str[1]      = next_char;
                        item_str[2]      = '\0';

                        ReplArgument arg = {.item = item_str,
                                            .kind = ARGUMENT_KIND_operator};
                        vector_append_ptr(replArguments, arg);

                        i++; // Consume the operator character as well
                        return 0;
                }
        }

        // If not an operator, assume it's a function (mDET, mGAUSS, mRREF)
        int op_start = *i + 1;
        int op_end   = op_start;
        while (op_end < strLen && line[op_end] != '(')
        {
                op_end++;
        }

        if (op_end >= strLen)
        {
                printf("Syntax error: missing '('\n");
                return 1;
        }

        int   len      = op_end - op_start;
        char *item_str = (char *)malloc(len + 1);
        if (!item_str)
        {
                printf("malloc failed\n");
                return 1;
        }
        memcpy(item_str, line + op_start, len);
        item_str[len]    = '\0';

        ReplArgument arg = {.item = item_str,
                            .kind = ARGUMENT_KIND_functionMatrix};
        vector_append_ptr(replArguments, arg);

        // Set i to char before '(', handleLine will increment to '('
        *i = op_end - 1;
        return 0;
}

int parseVectorPrefix(ReplArguments *replArguments, int *i, const char *line,
                      char currentChar, int strLen)
{

        // Check if it's an operator (v-, v+, v*, v., v~)
        if (*i + 1 < strLen)
        {
                char next_char = line[*i + 1];
                if (next_char == TOKEN_operatorMinus ||
                    next_char == TOKEN_operatorPlus ||
                    next_char == TOKEN_operatorStar ||
                    next_char == TOKEN_operatorDot ||
                    next_char == TOKEN_operatorTilde)
                {
                        // It's a vector operator
                        char *item_str = (char *)malloc(3); // "vX" + null
                                                            // terminator
                        if (!item_str)
                        {
                                printf("malloc failed\n");
                                return 1;
                        }

                        item_str[0]      = currentChar; // 'v'
                        item_str[1]      = next_char;
                        item_str[2]      = '\0';

                        ReplArgument arg = {.item = item_str,
                                            .kind = ARGUMENT_KIND_operator};

                        vector_append_ptr(replArguments, arg);

                        i++; // Consume the operator character as well
                        return 0;
                }
        }
        // If not an operator, assume it's an error for now
        printf("Error: unexpected character after 'v' prefix.\n");
        return 1;
}

int parseParen(ReplArguments *replArguments, int *i, const char *line,
               char currentChar, int strLen)
{
        int arg_start = *i + 1;
        int arg_end   = -1;

        for (int j = arg_start; j < strLen; j++)
        {
                if (line[j] == TOKEN_ParenClose)
                {
                        arg_end = j;
                        break;
                }
        }

        if (arg_end == -1)
        {
                printf("Syntax error: missing ')'\n");
                return 1;
        }

        // Trim whitespace
        int content_start = arg_start;
        while (content_start < arg_end && isspace(line[content_start]))
        {
                content_start++;
        }

        int content_end = arg_end;
        while (content_end > content_start && isspace(line[content_end - 1]))
        {
                content_end--;
        }

        int len = content_end - content_start;
        if (len <= 0)
        {
                printf("Syntax error: empty argument "
                       "in parenthesis\n");
                return 1;
        }

        char *item_str = (char *)malloc(len + 1);
        if (!item_str)
        {
                printf("malloc failed\n");
                return 1;
        }
        memcpy(item_str, line + content_start, len);

        item_str[len]     = '\0';
        ArgumentKind kind = ARGUMENT_KIND_matrix; // Default assumption

        if (item_str[0] == TOKEN_vectorOpen)
        {
                kind = ARGUMENT_KIND_vector;
        }
        else
        {
                printf("invalid argument passed : %s", item_str);
        }

        ReplArgument repl_arg = {.item = item_str, .kind = kind};
        vector_append_ptr(replArguments, repl_arg);

        *i = arg_end; // continue parsing after ')'
        return 0;
}

int parseVectorOpen(ReplArguments *replArguments, int *i, const char *line,
                    char currentChar, int strLen)
{
        return 1;
}
int parseMatrixOpen(ReplArguments *replArguments, int *i, const char *line,
                    char currentChar, int strLen)
{
        return 1;
}
