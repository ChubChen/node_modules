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
        int getHeZhi();
    private:
        IntArray* prizeNum;
        int hezhi;
};
#endif