#ifndef NUMTYPE_H
#define NUMTYPE_H

#define NUM_TYPE_Z24 24
#define NUM_TYPE_Z12 12
#define NUM_TYPE_Z6 6
#define NUM_TYPE_Z4 4

#include<stdlib.h>

class NumType {
    public:
        NumType(char *pNum, int len);
        ~NumType();
        int getCharLen();
        char getCharAt(int index);
        int getCharCountAt(int index);
        int getCharCount(char c);
        int getType();

    private:
        int type;   //组24，组12，组6，组4,24,12,6,4
        char *pChar;    //存放号码的字符
        int *pCharCount;    //存放号码的字符出现的次数，序号与pChar中保持一致
        int charLen;        //非重复的字符的数目

        void put(char c);   //压入一个字符到组中
};

#endif