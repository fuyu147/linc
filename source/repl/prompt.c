#include "repl.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

void printHelp()
{
        return;
}
int startPrompt()
{
        int continuePrompt = 1;
        while (continuePrompt)
        {
                char line[256];

                printf("> ");
                fflush(stdout);

                if (!fgets(line, sizeof line, stdin)) break;

                if (strchr(line, '\n') == NULL)
                {
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF)
                        {
                        }
                        continue;
                }

                line[strcspn(line, "\n")] = '\0';

                int actualLen             = strlen(line);

                if (line[0] == ':')
                {
                        switch (line[1])
                        {
                                case 'q':
                                        continuePrompt = 0;
                                        break;
                                case 'h':
                                        printHelp();
                                        break;
                                default:
                                        break;
                        }
                }
                else
                {
                        int err = handleLine(line, actualLen);

                        if (err)
                        {
                                printf("error gotten in repl\n");
                                return 1;
                        }
                }
        }

        return 0;
}

const int charOffset    = 48;

const char *matrixDET   = "DET";   // -> mDET(A)
const char *matrixGAUSS = "GAUSS"; // -> mGAUSS(A)
const char *matrixRREF  = "RREF";  // -> mRREF(A)

int handleLine(const char *line, int strLen)
{
        ReplArguments replArguments = {};

        printf("line gotten: %s\n", line);
        for (int i = 0; i < strLen; i++)
        {
                char currentChar = line[i];
                if (currentChar == ' ') continue;
                switch (currentChar)
                {
                        case TOKEN_matrixPrefix:
                                int errMatrix =
                                    parseMatrixPrefix(&replArguments, &i, line,
                                                      currentChar, strLen);
                                if (errMatrix) return 1;
                                break;
                        case TOKEN_vectorPrefix:
                                int errVector =
                                    parseVectorPrefix(&replArguments, &i, line,
                                                      currentChar, strLen);
                                if (errVector) return 1;
                                break;
                        case TOKEN_ParenOpen:
                                int errParen =
                                    parseVectorPrefix(&replArguments, &i, line,
                                                      currentChar, strLen);
                                if (errParen) return 1;
                                break;
                        case TOKEN_vectorOpen:
                                int errVectorOpen =
                                    parseVectorOpen(&replArguments, &i, line,
                                                    currentChar, strLen);
                                if (errVectorOpen) return 1;
                                break;
                        case TOKEN_matrixOpen:
                                int errMatrixOpen =
                                    parseMatrixOpen(&replArguments, &i, line,
                                                    currentChar, strLen);
                                if (errMatrixOpen) return 1;
                                break;
                        default:
                                printf("nothing to parse\n");
                                return 1;
                }
        }

        return 0;
}
