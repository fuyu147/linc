#pragma once

#include <stddef.h>

// syntax for vector : {1, 2, 3, ...}
// syntax for matrix : [[1, 2], [1, 2]]
//
// operators for vectors:
//      a - b -> substraction
//      a + b -> addition
//      a * b -> cross product
//      a . b -> dot product
//      a ~ b -> element-wise product
//
// operators for matrices:
//      A - B -> substraction
//      A + B -> addition
//      A * B -> multiplication by scalar
//      A . B -> multiplication with matrix
//
// functions for matrices:
//      DET(A)
//      GAUSS(A)
//      RREF(A)

enum
{
        // to call matrix functions
        TOKEN_matrixIdentifier = 'm',

        TOKEN_functionOpen     = '(', // X(A) where X is either D, G or R (like above) and A is a matrix
        TOKEN_functionClose    = ')',

        TOKEN_vectorOpen       = '{', // vector has syntax: {1, 2, 3, ..., n}
        TOKEN_vectorClose      = '}',

        TOKEN_matrixOpen       = '[', // matrix has syntax: [[1, 2, 3], [1, 2, 3], ...]
        TOKEN_matrixClose      = ']',

        TOKEN_operatorMinus    = '-', // available for matrix & vector
        TOKEN_operatorPlus     = '+', // available for matrix & vector
        TOKEN_operatorStar     = '*', // available for matrix & vector
        TOKEN_operatorDot      = '.', // available for matrix & vector
        TOKEN_operatorTilde    = '~', // available for vector
};

typedef struct
{
        const char **arg;
        size_t       count;
        size_t       capacity;
} Argument;

// returns 0 on success parsing line and giving output;
// returns 1 otherwise
int handleLine(const char *str, int strLen);
