#include "NumType.h"

NumType::NumType(char *pNum, int len)
{
    this->charLen = 0;
    this->pChar = (char *)malloc(sizeof(char)*len);
    this->pCharCount = (int *)malloc(sizeof(int)*len);

    for(int i = 0; i < len; i++)
    {
        char c = pNum[i];
        if(c != ',' && c > '0' && c < '9')
        {
            this->put(c);
        }
    }

    if(this->charLen == 4)
    {
        this->type = NUM_TYPE_Z24;
    }
    else if(this->charLen == 3)
    {
        this->type = NUM_TYPE_Z12;
    }
    else if(this->charLen == 2 && this->pCharCount[0] == 2)
    {
        this->type = NUM_TYPE_Z6;
    }
    else if(this->charLen == 2)
    {
        this->type = NUM_TYPE_Z4;
    }
    else
    {
        this->type = -1;
    }
}

int NumType::getCharLen()
{
    return this->charLen;
}

/**
 * 获得指定序号的位置的字符
 */
char NumType::getCharAt(int index)
{
    return this->pChar[index];
}

/**
 * 获得字符c出现的次数
 */
int NumType::getCharCount(char c)
{
    for(int i = 0; i < this->charLen; i++)
    {
        if(c == this->pChar[i])
        {
            return this->pCharCount[i];
        }
    }
    return 0;
}

/**
 * 获得指定位置字符出现的次数
 */
int NumType::getCharCountAt(int index)
{
    return this->pCharCount[index];
}

int NumType::getType()
{
    return this->type;
}

void NumType::put(char c)
{
    if(this->charLen == 0)
    {
        this->pCharCount[0] = 1;
        this->pChar[0] = c;
        this->charLen++;
    }
    else
    {
        int hitIndex = -1;
        for(int i = 0; i < this->charLen; i++)
        {
            char tmpChar = this->pChar[i];
            if(tmpChar == c)
            {
                hitIndex = i;
                break;
            }
        }
        if(hitIndex > -1)
        {
            this->pCharCount[hitIndex] += 1;
        }
        else
        {
            this->pCharCount[this->charLen] = 1;
            this->pChar[this->charLen] = c;
            this->charLen++;
        }
    }
}

NumType::~NumType()
{
    free(this->pChar);
    free(this->pCharCount);
}