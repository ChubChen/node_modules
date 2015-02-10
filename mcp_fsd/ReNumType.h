#ifndef RENUMTYPE_H
#define RENUMTYPE_H

#include <stdlib.h>
#include <stdio.h>

#include "IntArray.h"

/**
 * 复式号码
 */
class ReNumType {

    public:
        ReNumType(char *pNum, int len);
        ~ReNumType();

    private:
        long* iaSet;    //每一位号码的集合
        int length;     //一共有多少位号码
};

#endif