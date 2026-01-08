#include "vector.h"
#include <stdint.h>

Vector vectorAdd(Vector u, Vector v)
{
        Vector w = {};

        if (u.count != v.count)
                return w;

        for (int i = 0; i < u.count; i++)
        {
                vector_append(w, u.items[i] + v.items[i]);
        }

        return w;
}

double vectorDotProduct(Vector u, Vector v)
{
        Vector w = {};
        if (u.count != v.count)
        {
                return INT32_MAX;
        }

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
        return w;
}
