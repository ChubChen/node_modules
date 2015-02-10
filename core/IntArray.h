#ifndef INTARRAY_H
#define INTARRAY_H

#include "EasyString.h"

class IntArray {

    public:
        IntArray();
        IntArray(int volume);
        IntArray(int volume, char *p, int len, char sep);
        IntArray(int volume, EasyString *str, char sep);
        ~IntArray();

        void put(int value);
        void modify(int index, int value);
        int get(int index);
        int length();
        bool hasValue(int value);
        void traverse();

    private:
        int* pInt;  //数据存储区
        int curLen; //当前长度
        int volume; //当前最大容量

        void init(int volume, char *p, int len, char sep);
};

#endif