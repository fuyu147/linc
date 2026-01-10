#include "repl.h"

#include <stddef.h>
#include <stdio.h>

const int charOffset    = 48;

const char *matrixDET   = "DET";   // -> mDET(A)
const char *matrixGAUSS = "GAUSS"; // -> mGAUSS(A)
const char *matrixRREF  = "RREF";  // -> mRREF(A)

typedef vector_t(char) Digits;
typedef vector_t(double) Numbers;

double parseNumber(Digits digits)
{
        double d;
        // sscanf(digits, "%lf", &d);
        return d;
}

int handleLine(const char *line, int strLen)
{
        printf("line gotten: %s\n", line);
        for (int i = 0; i < strLen; i++)
        {
                // parse characters and stuff
                char currentChar = line[i];
                if (currentChar == ' ') continue;
                switch (currentChar)
                {
                        case TOKEN_matrixIdentifier:
                                break;
                        case TOKEN_functionOpen:
                                break;
                        case TOKEN_vectorOpen:
                                Digits digits  = {}; // first push each digit to this vector
                                Vector numbers = {}; // than parse it into a number to this vector
                                i++;
                                for (; i < strLen; i++)
                                {
                                        char currentChar = line[i];
                                        if (currentChar == TOKEN_vectorClose)
                                        {
                                                if (digits.count > 0)
                                                {
                                                        digits.items[digits.count] = '\0';
                                                        vector_append(numbers, parseNumber(digits.items));
                                                }
                                                vector_free(digits);
                                                vector_print(numbers);
                                                break;
                                        }
                                        else if (currentChar == ',' || currentChar == ' ')
                                        {
                                                if (digits.count > 0)
                                                {
                                                        digits.items[digits.count] = '\0';
                                                        vector_append(numbers, parseNumber(digits.items));
                                                        digits.count = 0;
                                                }
                                        }
                                        else if ('0' <= currentChar && currentChar <= '9')
                                        {
                                                int number = currentChar - charOffset;
                                                vector_append(digits, currentChar);
                                        }
                                        else if (currentChar == '.')
                                        {
                                                vector_append(digits, currentChar);
                                        }
                                        else
                                        {
                                                return 1;
                                        }
                                }
                                break;
                        case TOKEN_matrixOpen:
                                // syntax [[1, 2], [3, 4]]
                                i++;
                                for (; i < strLen; i++)
                                {
                                        // [ /* we are here*/ [1, 2], [3, 4]]
                                        int isInside = 0;
                                        if (isInside)
                                        {
                                                // [[/* we are here*/ 1, 2], [3, 4]]
                                                // parse the inner
                                        }
                                        else
                                        {
                                                // [ /* we are here*/ [1, 2], [3, 4]]
                                                // parse the inner
                                        }
                                }
                                break;
                        case TOKEN_operatorMinus:
                                break;
                        case TOKEN_operatorPlus:
                                break;
                        case TOKEN_operatorStar:
                                break;
                        case TOKEN_operatorDot:
                                break;
                        case TOKEN_operatorTilde:
                                break;
                        default:
                                printf("nothing to parse\n");
                                return 1;
                }
        }

        return 0;
}
