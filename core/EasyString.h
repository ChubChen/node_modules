#ifndef EASYSTRING_H
#define EASYSTRING_H

#include <node.h>

class EasyString {

    public:
        EasyString();
        EasyString(v8::Handle<v8::String> str);
        ~EasyString();

        char *pointer();
        int length();

    private:
        char* content;  //数据的存储区域
        int len;        //字符串的长度
};

#endif