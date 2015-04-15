#include "DrawNum.h"

DrawNum::DrawNum(char *pNum, int len)
{
   if(pNum[len -1] ==';'){
        len = len - 1;
   }
   this->prizeNum = new IntArray(3, pNum, len, '|');
   if(this->prizeNum->length() < 3){
       this->prizeNum = new IntArray(3, pNum, len, ',');
   }

   int he = 0;
   for(int i = 0 ; i< this->prizeNum->length(); i++){
        he += this->prizeNum->get(i);
   }
   this->sum = he;
   int span = MathUtil::getSpan(this->prizeNum, this->prizeNum->length());
   this->span = span;
   this->getType();
}

DrawNum::getType(){

    if(this->prizeNum->get(0) == this->prizeNum->(1) && this->prizeNum->(1) == this->prizeNum->(2))
    {
        this->type = NUM_TYPE_Z0;
    }
    if(this->prizeNum->get(0) != this->prizeNum->get(1) && this->prizeNum->get(1) != this->prizeNum->get(2) && this->prizeNum->get(0) != this->prizeNum->get(2))
    {
        this->type = NUM_TYPE_Z6;
    }
    this->type = NUM_TYPE_Z3;
}
/*
*获得开奖号码的数组
*/
IntArray* DrawNum::getPNum(){
    return this->prizeNum;
}
/**
获得合值
*/
int DrawNum::getSum(){
    return this->sum;
}

/**
获得跨度
*/
int DrawNum::getSpan(){
    return this->span;
}

//析构函数
DrawNum::~DrawNum()
{
    delete this->prizeNum;
}