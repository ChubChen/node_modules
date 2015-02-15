#ifndef DRAWNUM_H
#define DRAWNUM_H

#include "IntArray.h"
#include "MathUtil.h"

#include <stdio.h>
#include <stdlib.h>
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
};
#endif