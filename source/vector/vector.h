#pragma once

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define vector_append(XS, X)                                                   \
        do                                                                     \
        {                                                                      \
                if (XS.count >= XS.capacity)                                   \
                {                                                              \
                        if (XS.capacity == 0) XS.capacity = 256;               \
                        XS.capacity *= 2;                                      \
                        XS.items = realloc(XS.items,                           \
                                           XS.capacity * sizeof(*XS.items));   \
                }                                                              \
                XS.items[XS.count++] = X;                                      \
        } while (0)

#define vector_append_ptr(XS, X)                                               \
        do                                                                     \
        {                                                                      \
                if (XS->count >= XS->capacity)                                 \
                {                                                              \
                        if (XS->capacity == 0) XS->capacity = 256;             \
                        XS->capacity *= 2;                                     \
                        XS->items = realloc(                                   \
                            XS->items, XS->capacity * sizeof(*XS->items));     \
                }                                                              \
                XS->items[XS->count++] = X;                                    \
        } while (0)

#define vector_print(XS)                                                       \
        for (int i = 0; i < XS.count; ++i)                                     \
        {                                                                      \
                printf("%5g\n", XS.items[i]);                                  \
        }

#define def_vector_t(TYPE, NAME)                                               \
        typedef struct NAME                                                    \
        {                                                                      \
                TYPE  *items;                                                  \
                size_t count;                                                  \
                size_t capacity;                                               \
        } NAME;

def_vector_t(double, Vector);

Vector vectorAdd(Vector u, Vector v);
double vectorDotProduct(Vector u, Vector v);
Vector vectorCrossProduct(Vector u, Vector v);
Vector vectorElementWiseProduct(Vector u, Vector v);
