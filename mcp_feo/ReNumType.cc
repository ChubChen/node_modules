#include "ReNumType.h"

ReNumType::ReNumType(char *pNum, int len)
{
    this->pos = (long *)malloc(sizeof(char *)*4);
    this->posLen = (int *)malloc(sizeof(int)*4);
    for(int i = 0; i < 4; i++)
    {
        this->pos[i] = (long)malloc(sizeof(char)*16);
        this->posLen[i] = 0;
    }

    int posLen = 0;
    int posIndex = 0;
    //拆解每一位的号码，放入pos对应的位
    for(int i = 0; i < len ; i++)
    {
        char c = pNum[i];
        if(c == '|' || i == len - 1)
        {
            if(i == len - 1 && c != '|')    //把字符存到对应的队列
            {
                char *pos = (char *)this->pos[posIndex];
                pos[posLen] = c;
                posLen++;
            }

            //移动到下一个队列
            this->posLen[posIndex] = posLen;
            posLen = 0;
            posIndex++;
        }
        else    //把字符存到对应的队列
        {
            char *pos = (char *)this->pos[posIndex];
            pos[posLen] = c;
            posLen++;
        }
    }
}

bool ReNumType::hasChar(int index, char c)
{
    if(index < 0 || index > 3)
    {
        return false;
    }
    char *pos = (char *)this->pos[index];
    int len = this->posLen[index];
    bool hit = false;
    for(int i = 0; i < len ; i++)
    {
        if(pos[i] == c)
        {
            hit = true;
            break;
        }
    }
    return hit;
}

/**
 * 获得空白号码的位数
 */
int ReNumType::getEmptyCount()
{
    int count = 0;
    for(int i = 0; i < 4; i++)
    {
        if(this->posLen[i] == 1)
        {
            char *pos = (char *)this->pos[i];
            if(pos[0] == '_')
            {
                count++;
            }
        }
    }
    return count;
}

/**
 * 获得非空白号码的位数
 */
int ReNumType::getNotEmptyCount()
{
    return 4 - this->getEmptyCount();
}

ReNumType::~ReNumType()
{
    free(this->posLen);
    for(int i = 0; i < 4; i++)
    {
        free((char *)this->pos[i]);
    }
    free(this->pos);
}