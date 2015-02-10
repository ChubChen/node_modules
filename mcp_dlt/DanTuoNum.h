#ifndef DanTuoNum_H
#define DanTuoNum_H

#include "IntArray.h"

#include <stdio.h>
#include <stdlib.h>

class DanTuoNum {
    public:
        DanTuoNum(char *pNum, int len);
        ~DanTuoNum();
        IntArray* getPreDanArray();
        IntArray* getAfterDanArray();
        IntArray* getPreTuoArray();
        IntArray* getAfterTuoArray();

    private:
        IntArray *preDanArray;   //存放前区胆码的数组
        IntArray *afterDanArray; //存放后区胆码的数组
        IntArray *preTuoArray; //存放前区拖码的数组
        IntArray *afterTuoArray; //存放后区拖码的数组
        void initRedArray(char *pNum, int len); //初始化红球数组
        void initBlueArray(char *pNum, int len);    //初始化蓝球数组
};

#endif