#ifndef CHECK_H
#define CHECK_H

#include <node.h>
#include "GradeLevel.h"
#include "IntArray.h"

class Check:public node::ObjectWrap {
    public:
        static void Init();
        static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);

    private:
        explicit Check();
        ~Check();

        static v8::Persistent<v8::Function> constructor;
        static v8::Handle<v8::Value> New(const v8::Arguments& args);
        static v8::Handle<v8::Value> SetDrawNum(const v8::Arguments& args);
        static v8::Handle<v8::Value> GetDrawNum(const v8::Arguments& args);
        static v8::Handle<v8::Value> SetGl(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0000(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0001(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0002(const v8::Arguments& args);
        GradeLevel* gl;
        IntArray* redIntArray;   //红球开奖号码
        int blue;   //蓝球开奖号码
        int hitAndLevel[7][2];    //选中数目与奖级对应关系表
};

#endif