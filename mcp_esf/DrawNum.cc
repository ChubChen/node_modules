#include "DrawNum.h"

DrawNum::DrawNum(char *pNum, int len)
{
   if(pNum[len -1] ==';'){
        len = len - 1;
   }
   this->prizeNum = new IntArray(6, pNum, len, '|');
   if(this->prizeNum->length() < 5){
       this->prizeNum = new IntArray(6, pNum, len, ',');
   }
}

IntArray* DrawNum::getPNum(){
    return this->prizeNum;
}

DrawNum::~DrawNum()
{
    delete this->prizeNum;
}