#ifndef RENUMTYPE_H
#define RENUMTYPE_H

#include <stdlib.h>
#include <stdio.h>


/**
 * 任1到任4的号码
 */
class ReNumType {
    public:
        ReNumType(char *pNum, int len);
        ~ReNumType();
        //对应的位置是否包含字符c,index从0开始
        bool hasChar(int index, char c);
        //获得空位的数目
        int getEmptyCount();
        //获得非空位的数目
        int getNotEmptyCount();

    private:
        long *pos;  //指针数组，存放任选号码的4位，序号从0开始
        int *posLen;    //存放号码4个位的长度
};

#endif