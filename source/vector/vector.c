#include "vector.h"
#include <stdint.h>

Vector vectorAdd(Vector u, Vector v)
{
        Vector w = {};

        if (u.count != v.count) return w;

        for (int i = 0; i < u.count; i++)
        {
                vector_append(w, u.items[i] + v.items[i]);
        }

        return w;
}

double vectorDotProduct(Vector u, Vector v)
{
        Vector w = {};
        if (u.count != v.count) return INT32_MAX;

        double sum = 0;
        for (int i = 0; i < u.count; i++)
        {
                sum += u.items[i] * v.items[i];
        }

        return sum;
}

Vector vectorCrossProduct(Vector u, Vector v)
{
        Vector w = {};

        if (u.count != 3 || v.count != 3) return w;

        vector_append(w, u.items[1] * v.items[2] - u.items[2] * v.items[1]);
        vector_append(w, u.items[2] * v.items[0] - u.items[0] * v.items[2]);
        vector_append(w, u.items[0] * v.items[1] - u.items[1] * v.items[0]);

        return w;
}
