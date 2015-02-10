#ifndef MATHUTIL_H
#define MATHUTIL_H
#include "IntArray.h"

#include <node.h>

class MathUtil {
    public:
        MathUtil();
        ~MathUtil();
        static int GetA(int m, int n);
        static int GetC(int m, int n);
        //简化版的atoi
        static int StrToInt(char *pStr, int len);
        static int CharToInt(char c);
        static int abs(int value);
        static int getHitCountByOrder(IntArray* lotArray, IntArray* prizeArray);
        static int getHitCount(IntArray* lotArray, IntArray* prizeArray);
        static void SelectSort(IntArray* intArray);
    private:

};

#endif