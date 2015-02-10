
#include "DrawNum.h"

DrawNum::DrawNum(char *pNum, int len)
{
    this->charLen = 0;
    this->pChar = (char *)malloc(sizeof(char)*len);

    for(int i = 0; i < len; i++)
    {
        char c = pNum[i];
        if(c > '0' && c < '9')
        {
            this->pChar[this->charLen] = c;
            this->charLen++;
        }
    }
    printf("prize %s\n", pChar);
}

int DrawNum::getCharLen(){
    return this->charLen;
}
/**
 * 获得指定序号的位置的字符
 */
char DrawNum::getCharAt(int index)
{
    return this->pChar[index];
}

DrawNum::~DrawNum()
{
    delete[] this->pChar;
}