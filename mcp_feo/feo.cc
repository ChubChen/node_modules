#include <node.h>
#include <v8.h>
#include "GradeLevel.h"
#include "Check.h"
#include "StringUtil.h"
#include "NumType.h"

using namespace v8;

/**
 * StringUtil
 */
Handle<Value> StringUtil(const Arguments& args)
{
    HandleScope scope;
    return scope.Close(StringUtil::NewInstance(args));
}

/**
 * 对象工厂
 *
 */
Handle<Value> Gl(const Arguments& args)
{
    HandleScope scope;
    return scope.Close(GradeLevel::NewInstance(args));
}

/**
 * Check的实例
 */
Handle<Value> Check(const Arguments& args)
{
    HandleScope scope;
    return scope.Close(Check::NewInstance(args));
}


/**
 * Check的实例
 */
Handle<Value> GetCharLen(const Arguments& args)
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

    NumType *pNumType = new NumType(pChar, length);
    int len = pNumType->getCharLen();
    delete pNumType;

    delete[] pChar;
    return scope.Close(Number::New(len));
}

/**
 * Check的实例
 */
Handle<Value> GetNumType(const Arguments& args)
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

    NumType *pNumType = new NumType(pChar, length);
    int type = pNumType->getType();
    delete pNumType;

    delete[] pChar;
    return scope.Close(Number::New(type));
}

void init(Handle<Object> exports) {
    StringUtil::Init();
    GradeLevel::Init();
    Check::Init();
    exports->Set(String::NewSymbol("gl"), FunctionTemplate::New(Gl)->GetFunction());
    exports->Set(String::NewSymbol("check"), FunctionTemplate::New(Check)->GetFunction());
    exports->Set(String::NewSymbol("stringUtil"), FunctionTemplate::New(StringUtil)->GetFunction());
    exports->Set(String::NewSymbol("getCharLen"), FunctionTemplate::New(GetCharLen)->GetFunction());
    exports->Set(String::NewSymbol("getNumType"), FunctionTemplate::New(GetNumType)->GetFunction());
}

NODE_MODULE(feo, init)
