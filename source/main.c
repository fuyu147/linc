#include "matrix/matrix.h"
#include "repl/repl.h"
#include "vector/vector.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void printHelp()
{
}

int main()
{
        if (0) matrixExample();
        if (0) vectorExample();

        const int lineSize       = 256;
        int       continuePrompt = 1;
        while (continuePrompt)
        {
                char line[lineSize];

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
                        handleLine(line, lineSize);
                }
        }

        return 0;
}
