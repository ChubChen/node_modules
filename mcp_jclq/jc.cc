#include <node.h>
#include <v8.h>
#include "Check.h"

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
 * 模块初始化
 */
void init(Handle<Object> exports) {
    Check::Init();
    exports->Set(String::NewSymbol("check"), FunctionTemplate::New(Check)->GetFunction());
}

NODE_MODULE(jc, init)
