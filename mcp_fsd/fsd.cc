#include <node.h>
#include <v8.h>
#include "GradeLevel.h"
#include "Check.h"
#include "StringUtil.h"

using namespace v8;


/**
 * Check的实例
 */
Handle<Value> Check(const Arguments& args)
{
    HandleScope scope;
    return scope.Close(Check::NewInstance(args));
}

/**
 * 奖级
 */
Handle<Value> Gl(const Arguments& args)
{
    HandleScope scope;
    return scope.Close(GradeLevel::NewInstance(args));
}


void init(Handle<Object> exports) {
    StringUtil::Init();
    GradeLevel::Init();
    Check::Init();

    exports->Set(String::NewSymbol("gl"), FunctionTemplate::New(Gl)->GetFunction());
    exports->Set(String::NewSymbol("check"), FunctionTemplate::New(Check)->GetFunction());
}

NODE_MODULE(fsd, init)
