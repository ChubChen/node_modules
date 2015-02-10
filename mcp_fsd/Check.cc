#include <node.h>
#include "Check.h"

using namespace v8;

Persistent<Function> Check::constructor;

Check::Check()
{
    this->gl = NULL;
    this->pDrawNum = NULL;
}

Check::~Check()
{
    delete this->gl;
    this->gl = NULL;
    delete this->pDrawNum;
    this->pDrawNum = NULL;
}

void Check::Init()
{
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("Check"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->PrototypeTemplate()->Set(String::NewSymbol("setDrawNum"), FunctionTemplate::New(SetDrawNum)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("setGl"), FunctionTemplate::New(SetGl)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count"), FunctionTemplate::New(Count)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0100"), FunctionTemplate::New(Count0100)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0101"), FunctionTemplate::New(Count0101)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0103"), FunctionTemplate::New(Count0103)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0201"), FunctionTemplate::New(Count0201)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0301"), FunctionTemplate::New(Count0301)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0403"), FunctionTemplate::New(Count0403)->GetFunction());
    constructor = Persistent<Function>::New(tpl->GetFunction());
}

/**
 * 真正初始化的方法
 */
Handle<Value> Check::New(const Arguments& args)
{
    HandleScope scope;
    if(args.IsConstructCall()){ //from new GradeLevel()
        Check * obj = new Check();
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
 * 设置开奖号码
 */
Handle<Value> Check::SetDrawNum(const Arguments& args)
{
    HandleScope scope;
    //校验参数的类型
    if (!args[0]->IsString()) {
        ThrowException(Exception::TypeError(String::New("Wrong arguments")));
        return scope.Close(Undefined());
    }
    Check *obj = ObjectWrap::Unwrap<Check>(args.This());
    EasyString* es = new EasyString(args[0]->ToString());
    obj->pDrawNum = new IntArray(3, es, '|');
    delete es;
    return scope.Close(Undefined());
}

/**
 * 设置奖级信息
 */
Handle<Value> Check::SetGl(const Arguments& args)
{
    HandleScope scope;
    Check *obj = ObjectWrap::Unwrap<Check>(args.This());
    GradeLevel *gl = ObjectWrap::Unwrap<GradeLevel>(args[0]->ToObject());
    int lCount = gl->getLevelCount();
    GradeLevel *newGl = new GradeLevel(lCount);
    for(int i = 0; i < lCount; i++)
    {
        newGl->setBonus(i, gl->getBonus(i));
    }
    obj->gl = newGl;
    return scope.Close(Undefined());
}

/**
 * 算奖
 */
Handle<Value> Check::Count(const Arguments& args)
{
    HandleScope scope;
    Handle<Array> array = Array::New();
    Handle<Object> obj = Object::New();
    obj->Set(String::NewSymbol("bonus"), Number::New(4000));
    obj->Set(String::NewSymbol("bonusBeforeTax"), Number::New(4000));
    obj->Set(String::NewSymbol("level"), Number::New(1));
    obj->Set(String::NewSymbol("count"), Number::New(1));
    array->Set(0, obj);
    return scope.Close(array);
}

/**
 * Init方法中已经初始化过constructor变量，所以在这儿可以使用
 * constructor来新建一个对象。
 */
Handle<Value> Check::NewInstance(const Arguments& args)
{
    HandleScope scope;
    const unsigned argc = 0;
    Handle<Value> argv[argc] = {};
    Local<Object> instance = constructor->NewInstance(argc, argv);
    return scope.Close(instance);
}


/**
 * 直选单式
 */
Handle<Value> Check::Count0100(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();

    Local<Object> pObj = Local<Object>::Cast(args[0]);
    Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
    EasyString* es = new EasyString(pNum);
    char* pChar = es->pointer(); int length = es->length();

    int jCount = 0;
    char *tmp = pChar;
    for(int j = 0; j < length; j++)
    {
        char jChar = pChar[j];
        if(jChar == ';' || j == length - 1) //号码结束
        {
            if(j == length - 1 && jChar != ';') //如果到了号码末尾，需要把最后一个字符加进来
            {
                jCount++;
            }

            IntArray* ia = new IntArray(3, tmp, jCount, '|');
            bool hit = true;
            int len = ia->length();
            for(int i = 0; i < len; i++)
            {
                if(self->pDrawNum->get(i) != ia->get(i))
                {
                    hit = false;
                    break;
                }
            }
            if(hit)
            {
                self->gl->appendBonusObj(array, 1, 1);
            }
            delete ia;

            jCount = 0; //号码长度重新计算
            if(j < length - 1)
            {
                tmp = pChar + j + 1;
            }
        }
        else
        {
            jCount++;
        }
    }
    delete es;
    return scope.Close(self->gl->getRst(array));
}

/**
 * 直选复式
 */
Handle<Value> Check::Count0101(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();

    Local<Object> pObj = Local<Object>::Cast(args[0]);
    Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
    EasyString* es = new EasyString(pNum);
    char* pChar = es->pointer(); int length = es->length();

    ReNumType *pReNumType = new ReNumType(pChar, length);
    delete pReNumType;

    delete es;
    return scope.Close(self->gl->getRst(array));
}

/**
 * 直选和值
 */
Handle<Value> Check::Count0103(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    return scope.Close(self->gl->getRst(array));
}

/**
 * 组三复式
 */
Handle<Value> Check::Count0201(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    return scope.Close(self->gl->getRst(array));
}

/**
 * 组六复式
 */
Handle<Value> Check::Count0301(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    return scope.Close(self->gl->getRst(array));
}

/**
 * 组选和值
 */
Handle<Value> Check::Count0403(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    return scope.Close(self->gl->getRst(array));
}