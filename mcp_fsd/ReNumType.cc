#include "ReNumType.h"

ReNumType::ReNumType(char *pChar, int length)
{
    this->length = 0;
    this->iaSet = (long *)malloc(sizeof(IntArray *)*3);

    int jCount = 0;
    char *tmp = pChar;
    for(int j = 0; j < length; j++)
    {
        char jChar = pChar[j];
        if(jChar == '|' || j == length - 1) //号码结束
        {
            if(j == length - 1 && jChar != '|') //如果到了号码末尾，需要把最后一个字符加进来
            {
                jCount++;
            }

            this->iaSet[this->length] = (long)new IntArray(10, tmp, jCount, ',');
            this->length++;
            if(this->length >= 3)
            {
                break;
            }

            jCount = 0; //号码长度重新计算
            if(j < length - 1)
            {
                tmp = pChar + j + 1;
            }
        }
        else
        {
            jCount++;
        }
    }
}


ReNumType::~ReNumType()
{
    for(int i = 0; i < this->length; i++)
    {
        delete (IntArray *)this->iaSet[i];
    }
    free(this->iaSet);
}