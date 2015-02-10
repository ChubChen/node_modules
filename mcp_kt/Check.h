#ifndef CHECK_H
#define CHECK_H

#include <node.h>
#include "GradeLevel.h"
#include "DrawNum.h"
#include "MathUtil.h"
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
        static v8::Handle<v8::Value> SetGl(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0100(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0200(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0300(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0401(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0501(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0601(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0700(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0800(const v8::Arguments& args);

        GradeLevel* gl;
        DrawNum* pDrawNum;
        int hezhiRules[18];
};

#endif