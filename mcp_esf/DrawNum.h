#ifndef DRAWNUM_H
#define DRAWNUM_H

#include "IntArray.h"

#include <stdio.h>
#include<stdlib.h>
class DrawNum {
    public:
        DrawNum(char *pNum, int len);
        ~DrawNum();

        IntArray* getPNum();
    private:
        IntArray* prizeNum;
};
#endif