#ifndef CHECK_H
#define CHECK_H

#include <node.h>
#include "VsString.h"

class Check:public node::ObjectWrap {

    public:
        static void Init();
        static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);


    private:
        explicit Check();
        ~Check();

        //串关特征串
        struct VsJsonObject* bunchMap;

        //开奖号码
        struct VsJsonObject* drawMap;

        //场次取消特征值
        struct VsString* cancelFlag;

        static v8::Persistent<v8::Function> constructor;
        static v8::Handle<v8::Value> New(const v8::Arguments& args);
        static v8::Handle<v8::Value> SetDrawNumber(const v8::Arguments& args);
        static v8::Handle<v8::Value> Count(const v8::Arguments& args);

        //初始化串关特征串
        void initBunchMap();

        //获得号码串
        struct VsString* getNumber(const v8::Local<v8::Object> pObj);

        //获得玩法
        struct VsString* getBetType(const v8::Local<v8::Object> pObj);

        //获得场次及号码串、选项、赔率等信息
        struct VsJsonObject* getNumberObj(struct VsString* number, struct VsString* betType);
};

#endif