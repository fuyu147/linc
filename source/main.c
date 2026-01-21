#include <stddef.h>

#include "vector/vector.h"

int main()
{
        Vector vec = {};
        vector_append(vec, 1);
        vector_append(vec, 2);
        vector_append(vec, 3);

        vector_print(vec);

        return 0;
}
