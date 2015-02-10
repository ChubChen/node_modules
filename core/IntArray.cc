#include <stdlib.h>
#include "IntArray.h"
#include "MathUtil.h"

IntArray::IntArray()
{
    this->pInt = NULL;
}

IntArray::IntArray(int volume)
{
    this->pInt = (int *)malloc(sizeof(int)*volume);
    this->volume = volume;
    this->curLen = 0;
}

IntArray::IntArray(int volume, char *p, int len, char sep)
{
    this->init(volume, p, len, sep);
}

IntArray::IntArray(int volume, EasyString *str, char sep)
{
    char *p = str->pointer();
    int len = str->length();
    this->init(volume, p, len, sep);
}

void IntArray::init(int volume, char *p, int len, char sep)
{
    this->pInt = (int *)malloc(sizeof(int)*volume);
    this->curLen = 0;

    int jCount = 0;
    char *tmp = p;
    //遍历字符串
    for(int j = 0; j < len; j++)
    {
        char jChar = p[j];
        if(jChar == sep || j == len - 1) //号码结束
        {
            if(j == len - 1) //如果到了号码末尾，需要把最后一个字符加进来
            {
                jCount++;
            }

            //转换成整数，存入数组
            int value = MathUtil::StrToInt(tmp, jCount);
            this->put(value);

            jCount = 0; //号码长度重新计算
            if(j < len - 1)
            {
                tmp = p + j + 1;
            }
        }
        else
        {
            jCount++;
        }
    }
}

IntArray::~IntArray()
{
    if(this->pInt != NULL)
    {
        free(this->pInt);
        this->pInt = NULL;
    }
}

/**
 * 添加一个元素进数组
 */
void IntArray::put(int value)
{
    this->pInt[this->curLen] = value;
    this->curLen++;
}

/**
 * 改变下标为index的值
 */
void IntArray::modify(int index, int value)
{
    if(index <= this->curLen -1){
        this->pInt[index] = value;
    }else{
         this->pInt[this->curLen] = value;
         this->curLen++;
    }
}

/**
 * 获得指定位置的元素
 */
int IntArray::get(int index)
{
    return this->pInt[index];
}

/**
 * 获得指定位置的元素
 */
void IntArray::traverse()
{
    for(int i = 0; i < this->curLen; i++)
    {
        printf("%d\n", this->pInt[i]);
    }
}

/**
 * 获得数组的长度
 */
int IntArray::length()
{
    return this->curLen;
}


bool IntArray::hasValue(int value)
{
    bool hit = false;
    for(int i = 0; i < this->curLen; i++)
    {
        if(this->pInt[i] == value)
        {
            hit = true;
            break;
        }
    }
    return hit;
}