#include <node.h>
#include <stdlib.h>
#include "MathUtil.h"
#include "IntArray.h"

MathUtil::MathUtil()
{
}

MathUtil::~MathUtil()
{
}

int MathUtil::GetA(int m, int n)
{
    int value = 1;
    for (int i = 0; i < n; i++) {
        value = value * (m - i);
    }
    return value;
}


int MathUtil::GetC(int m, int n)
{
    if ((m < n) || (n < 0)) {
        return 0;
    }
    return MathUtil::GetA(m, n) / MathUtil::GetA(n, n);
}

/**
 * 简化版的字符串转换成整数的函数
 */
int MathUtil::StrToInt(char *pStr, int len)
{
    int rst = 0;
    int multiple = 1;
    for(int i = len - 1; i >= 0; i--)
    {
        rst += (pStr[i] - '0')*multiple;
        multiple *= 10;
    }
    return rst;
}

/**
 * 数字字符转换成整数
 */
int MathUtil::CharToInt(char c)
{
    return c - '0';
}


int MathUtil::abs(int value){
    return value > 0 ? value : -value;
}

int MathUtil::getHitCount(IntArray* lot, IntArray* prize)
{
    int len = lot->length();
    int plen = prize->length();
    int hitCount = 0; //中红球的个数
    for(int i = 0; i< len; i++){
        for (int j = 0; j < plen; j++){
            if (lot->get(i) == prize->get(j)){
                hitCount ++;
            }
        }
    }
    return hitCount;
}

int MathUtil::getHitCountByOrder(IntArray* lotArray, IntArray* prizeArray)
{
    IntArray *lot = lotArray;
    int len = lot->length();
    IntArray *prize = prizeArray;
    int plen = prize->length();
    if(len > plen){
        len = plen;
    }
    int hitCount = 0; //中红球的个数
    for(int i = 0; i< plen; i++){
        if (lot->get(i) == prize->get(i)){
            hitCount ++;
        }
    }
    return hitCount;
}

void MathUtil::SelectSort(IntArray* intArray)
{
    //SelectSort
   for(int i = 0; i < intArray->length()-1; i++){
      int index = i;
       //选择最小的值到最前面。
      for( int j = i +1; j< intArray->length() ; j++){
         if(intArray->get(j) < intArray->get(index))
         index = j;
      }
      if(i != index){
           int temp = intArray->get(i);
           intArray->modify(i, intArray->get(index));
           intArray->modify(index, temp);
      }
   }
}