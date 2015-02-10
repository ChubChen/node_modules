#include "DrawNum.h"

/**
 * 大乐透的红球与篮球之间用|分隔
 */
DrawNum::DrawNum(char *pNum, int len)
{
    int i = 0;
    int sepIndex = -1;
    while(i < len)
    {
        char c = *(pNum + i);
        if(c == '|')
        {
            sepIndex = i;
            break;
        }
        i++;
    }
    this->preArray = new IntArray(35, pNum, sepIndex, ',');
    //蓝球号码的长度
    int afterLen = len - (sepIndex + 1);
    if(*(pNum + len - 1) == ';')    //如果结束符是;,则长度还需要-1
    {
        afterLen--;
    }
    this->afterArray = new IntArray(12, pNum + sepIndex + 1, afterLen, ',');
}

IntArray* DrawNum::getPreArray(){
    return this->preArray;
}

IntArray* DrawNum::getAfterArray(){
    return this->afterArray;
}

DrawNum::~DrawNum()
{
    delete this->preArray;
    delete this->afterArray;
}