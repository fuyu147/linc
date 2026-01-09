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

const char  matrixIdentifier  = 'm';     // to call matrix functions:
const char *matrixDET         = "DET";   // -> mDET(A)
const char *matrixGAUSS       = "GAUSS"; // -> mGAUSS(A)
const char *matrixRREF        = "RREF";  // -> mRREF(A)
const char  functionCharOpen  = '(';     //
const char  functionCharClose = ')';     // X(A) where X is either D, G or R (like above) and A is a matrix

const char vectorCharOpen     = '{'; // vector has syntax: {1, 2, 3, ..., n}
const char vectorCharClose    = '}';
const char matrixCharOpen     = '['; // matrix has syntax: [[1, 2, 3], [1, 2, 3], ...]
const char matrixCharClose    = ']';

const char operatorMinus      = '-'; // matrix & vector
const char operatorPlus       = '+'; // matrix & vector
const char operatorStar       = '*'; // matrix & vector
const char operatorDot        = '.'; // matrix & vector
const char operatorTilde      = '~'; // vector

const int charOffset          = 48;

typedef struct
{
        const char **line;
        size_t       count;
        size_t       capacity;
} VectorArgs;

typedef struct
{
        const char **line;
        size_t       count;
        size_t       capacity;
} MatrixArgs;

// returns 0 on success parsing line and giving output;
// returns 1 otherwise
int handleLine(const char *str, int strLen);
