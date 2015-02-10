#include <node.h>
#include <stdlib.h>
#include "StringUtil.h"

using namespace v8;

Persistent<Function> StringUtil::constructor;

StringUtil::StringUtil()
{
}

StringUtil::~StringUtil()
{
}

void StringUtil::Init()
{
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("StringUtil"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->PrototypeTemplate()->Set(String::NewSymbol("getIntArray"), FunctionTemplate::New(GetIntArray)->GetFunction());
    constructor = Persistent<Function>::New(tpl->GetFunction());
}

/**
 * 真正初始化的方法
 */
Handle<Value> StringUtil::New(const Arguments& args)
{
    HandleScope scope;
    if(args.IsConstructCall()){
        StringUtil * obj = new StringUtil();
        obj->Wrap(args.This());
        return args.This();
    }
    else{   //from GradeLevel()
        const int argc = 0;
        Local<Value> argv[argc] = {};
        return scope.Close(constructor->NewInstance(argc, argv));
    }
}

/**
 * Init方法中已经初始化过constructor变量，所以在这儿可以使用
 * constructor来新建一个对象。
 */
Handle<Value> StringUtil::NewInstance(const Arguments& args)
{
    HandleScope scope;
    const unsigned argc = 1;
    Handle<Value> argv[argc] = {args[0]};
    Local<Object> instance = constructor->NewInstance(argc, argv);
    return scope.Close(instance);
}

/**
 * 从字符串数组获得int数组
 */
Handle<Value> StringUtil::GetIntArray(const Arguments& args)
{
    HandleScope scope;
    //校验参数的类型
    if (!args[0]->IsString()) {
        ThrowException(Exception::TypeError(String::New("Wrong arguments")));
        return scope.Close(Undefined());
    }
    Handle<String> pStr = args[0]->ToString();
    int length = pStr->Utf8Length();
    char *pChar = new char[length];
    pStr->WriteUtf8(pChar);

    //已经拿到字符数组的指针
    Handle<Array> array = Array::New();
    int iCount = 0;
    array->Set(iCount, Number::New(atoi(pChar)));
    iCount++;
    char *pTmp = pChar;
    //记录分隔符位置
    for(int i = 0; i < length; i++)
    {
        char c = pTmp[0];
        pTmp++;
        if(c < '0' || c > '9')
        {
            array->Set(iCount, Number::New(atoi(pTmp)));
            iCount++;
        }
    }
    delete[] pChar;
    return scope.Close(array);
}

int* StringUtil::GetIntArray(char *pStr, char ne)
{
    /*char *pTmp = pStr;
    //记录分隔符位置
    for(int i = 0; i < length; i++)
    {
        char c = pTmp[0];
        pTmp++;
        if(c < '0' || c > '9')
        {
            array->Set(iCount, Number::New(atoi(pTmp)));
            iCount++;
        }
    }*/
    return NULL;
}