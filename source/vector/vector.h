#pragma once

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define vector_append(xs, x)                                                                                           \
        do                                                                                                             \
        {                                                                                                              \
                if (xs.count >= xs.capacity)                                                                           \
                {                                                                                                      \
                        if (xs.capacity == 0) xs.capacity = 256;                                                       \
                        xs.capacity *= 2;                                                                              \
                        xs.items = realloc(xs.items, xs.capacity * sizeof(*xs.items));                                 \
                }                                                                                                      \
                xs.items[xs.count++] = x;                                                                              \
        } while (0)

#define vector_print(xs)                                                                                               \
        for (int i = 0; i < xs.count; ++i)                                                                             \
        {                                                                                                              \
                printf("%5g\n", xs.items[i]);                                                                          \
        }

#define vector_free(xs)                                                                                                \
        do                                                                                                             \
        {                                                                                                              \
                free(xs.items);                                                                                        \
                xs.items    = NULL;                                                                                    \
                xs.count    = 0;                                                                                       \
                xs.capacity = 0;                                                                                       \
        } while (0)

typedef struct
{
        double *items;
        size_t  count;
        size_t  capacity;
} Vector;

Vector vectorAdd(Vector u, Vector v);
double vectorDotProduct(Vector u, Vector v);
Vector vectorCrossProduct(Vector u, Vector v);
Vector vectorElementWiseProduct(Vector u, Vector v);

int vectorExample();
