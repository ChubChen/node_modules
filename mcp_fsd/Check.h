#ifndef CHECK_H
#define CHECK_H

#include <node.h>
#include "GradeLevel.h"
#include "EasyString.h"
#include "MathUtil.h"
#include "IntArray.h"
#include "ReNumType.h"

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
        static v8::Handle<v8::Value> Count(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0100(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0101(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0103(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0201(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0301(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0403(const v8::Arguments& args);
        GradeLevel* gl;
        IntArray* pDrawNum;
};

#endif