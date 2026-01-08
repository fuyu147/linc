
#include "vector.h"
#include <stdio.h>

int vectorExample()
{
        // Create two 3D vectors
        Vector u = {};
        Vector v = {};

        // Add components to vector u (1, 2, 3)
        vector_append(u, 1.0);
        vector_append(u, 2.0);
        vector_append(u, 3.0);

        // Add components to vector v (4, 5, 6)
        vector_append(v, 4.0);
        vector_append(v, 5.0);
        vector_append(v, 6.0);

        // Print vector u
        printf("Vector u: \n");
        vector_print(u);

        // Print vector v
        printf("Vector v: \n");
        vector_print(v);

        // Add vectors u and v
        Vector sum = vectorAdd(u, v);
        printf("u + v: \n");
        vector_print(sum);

        // Compute dot product
        double dot = vectorDotProduct(u, v);
        printf("u · v: %g\n", dot);

        // Compute cross product
        Vector cross = vectorCrossProduct(u, v);
        printf("u × v: \n");
        vector_print(cross);

        // Free memory (in real usage, you'd implement proper cleanup)
        free(u.items);
        free(v.items);
        free(sum.items);
        free(cross.items);

        return 0;
}
