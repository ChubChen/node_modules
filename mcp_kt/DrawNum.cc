#include "DrawNum.h"

DrawNum::DrawNum(char *pNum, int len)
{
   if(pNum[len -1] ==';'){
        len = len - 1;
   }
   this->prizeNum = new IntArray(3, pNum, len, ',');
   if(this->prizeNum->length() < 3){
       this->prizeNum = new IntArray(3, pNum, len, '|');
   }
   //SelectSort
   for(int i = 0; i < this->prizeNum->length()-1; i++){
      int index = i;
       //选择最小的值到最前面。
      for( int j = i +1; j< this->prizeNum->length() ; j++){
         if(this->prizeNum->get(j) < this->prizeNum->get(index))
         index = j;
      }
      if(i != index){
           int temp = this->prizeNum->get(i);
           this->prizeNum->modify(i, this->prizeNum->get(index));
           this->prizeNum->modify(index, temp);
      }
   }

   int sum = 0;
   if(this->prizeNum != NULL){
       IntArray *prizeArray = this->prizeNum;
       for(int i = 0; i < prizeArray->length(); i++){
           sum += prizeArray->get(i);
       }
       this->hezhi = sum;
   }else{
       this->hezhi = sum;
   }
}

IntArray* DrawNum::getPNum(){
    return this->prizeNum;
}

int DrawNum::getHeZhi(){
    return this->hezhi;
}


DrawNum::~DrawNum()
{
    delete this->prizeNum;
}