#include "DrawNum.h"

DrawNum::DrawNum(char *pNum, int len)
{
   if(pNum[len -1] ==';'){
        len = len - 1;
   }
   this->prizeNum = new IntArray(5, pNum, len, '|');
   if(this->prizeNum->length() < 5){
       this->prizeNum = new IntArray(5, pNum, len, ',');
   }
}
/*
*获得开奖号码的数组
*/
IntArray* DrawNum::getPNum(){
    return this->prizeNum;
}


//析构函数
DrawNum::~DrawNum()
{
    delete this->prizeNum;
}