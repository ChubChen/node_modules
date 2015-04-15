#ifndef DRAWNUM_H
#define DRAWNUM_H

#include "IntArray.h"
#include "MathUtil.h"

#include <stdio.h>
#include <stdlib.h>
#define NUM_TYPE_Z6 6
#define NUM_TYPE_Z3 3
#define NUM_TYPE_Z0 1

class DrawNum {
    public:
        DrawNum(char *pNum, int len);
        ~DrawNum();

        IntArray* getPNum();
        int getSum();
        int getSpan();
    private:
        IntArray* prizeNum;
        int sum;
        int span;
        int type; \\组六 \\组三
};
#endif