#include "repl.h"

#include "../matrix/matrix.h"
#include "../vector/vector.h"
#include <stdio.h>

int handleLine(const char *line, int strLen)
{
        VectorArgs vargs = {};
        MatrixArgs margs = {};

        for (int i = 0; i < strLen; i++)
        {
                // parse characters and stuff
                char currentChar = line[i];
                switch (currentChar)
                {
                        case matrixIdentifier:
                                break;
                        case functionCharOpen:
                                break;
                        case functionCharClose:
                                break;
                        case vectorCharOpen:
                                i++;
                                if (charOffset <= currentChar && currentChar <= charOffset + 9)
                                {
                                        printf("char: %c, number: %d\n", currentChar, currentChar - charOffset);
                                }
                                break;
                        case vectorCharClose:
                                break;
                        case matrixCharOpen:
                                break;
                        case matrixCharClose:
                                break;
                        case operatorMinus:
                                break;
                        case operatorPlus:
                                break;
                        case operatorStar:
                                break;
                        case operatorDot:
                                break;
                        case operatorTilde:
                                break;
                        default: // a space should get us here
                                break;
                }
        }

        return 0;
}
