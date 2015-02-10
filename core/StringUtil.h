#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <node.h>

class StringUtil:public node::ObjectWrap {
    public:
        static void Init();
        static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);
        int* GetIntArray(char *pStr, char ne);

    private:
        explicit StringUtil();
        ~StringUtil();

        static v8::Handle<v8::Value> GetIntArray(const v8::Arguments& args);
        static v8::Handle<v8::Value> New(const v8::Arguments& args);
        static v8::Persistent<v8::Function> constructor;
};

#endif