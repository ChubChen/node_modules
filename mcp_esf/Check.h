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
        static v8::Handle<v8::Value> GetDrawNum(const v8::Arguments& args);
        static v8::Handle<v8::Value> SetGl(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2100(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2101(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2200(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2201(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2202(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2300(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2301(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2302(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2400(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2401(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2402(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2500(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2501(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2502(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2600(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2601(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2602(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2700(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2701(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2702(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2800(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2900(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2901(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2902(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2903(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count2906(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count3100(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count3101(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count3102(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count3103(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count3106(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count3000(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count3001(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count3007(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count3003(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count3006(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count3200(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count3201(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count3207(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count3203(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count3206(const v8::Arguments& args);



        int getHitCount(IntArray* lotArray, IntArray* prizeArray);
        IntArray* getCopyLengthIntArray(IntArray* numArray, int from, int len);
        int getKuadu(IntArray* numArray, int len);

        GradeLevel* gl;
        DrawNum* pDrawNum;
};

#endif