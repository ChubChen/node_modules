#ifndef DRAWNUM_H
#define DRAWNUM_H

#include "IntArray.h"

#include <stdio.h>
#include<stdlib.h>

class DrawNum {
    public:
        DrawNum(char *pNum, int len);
        ~DrawNum();
        IntArray* getPreArray();
        IntArray* getAfterArray();

    private:
        IntArray *preArray;   //存放前区号码的数组
        IntArray *afterArray; //存放后区的数组
};

#endif