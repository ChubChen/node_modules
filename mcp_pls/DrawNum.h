#ifndef DRAWNUM_H
#define DRAWNUM_H



#include <stdio.h>
#include<stdlib.h>
class DrawNum {
    public:
        DrawNum(char *pNum, int len);
        ~DrawNum();

        char getCharAt(int index);
        int getCharLen();
    private:
        char *pChar;    //存放号码的字符
        int charLen;        //非重复的字符的数目
};

#endif