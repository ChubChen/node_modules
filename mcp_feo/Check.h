#ifndef CHECK_H
#define CHECK_H

#include <node.h>
#include "GradeLevel.h"
#include "NumType.h"
#include "ReNumType.h"
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

        //根据任选的数目获得对应的奖级
        int getGlByReCount(int reCount);

        static v8::Persistent<v8::Function> constructor;
        static v8::Handle<v8::Value> New(const v8::Arguments& args);
        static v8::Handle<v8::Value> SetDrawNum(const v8::Arguments& args);
        static v8::Handle<v8::Value> GetDrawNum(const v8::Arguments& args);
        static v8::Handle<v8::Value> SetGl(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0000(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0100(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0101(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0102(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0200(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0201(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0202(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0208(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0300(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0301(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0302(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0400(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0401(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0402(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0408(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0500(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0501(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0600(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0601(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0603(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0606(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0609(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0700(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0701(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0709(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0800(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0801(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0900(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0901(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count0902(const v8::Arguments& args);
        GradeLevel* gl;
        NumType* pDrawNumType;
        DrawNum* pDrawNum;
};

#endif