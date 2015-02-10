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

    if(this->gl != NULL)
    {
        delete this->gl;
    }
    if(this->pDrawNum != NULL)
    {
        delete this->pDrawNum;
    }
}

void Check::Init()
{
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("Check"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->PrototypeTemplate()->Set(String::NewSymbol("setDrawNum"), FunctionTemplate::New(SetDrawNum)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("setGl"), FunctionTemplate::New(SetGl)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0100"), FunctionTemplate::New(Count0100)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0101"), FunctionTemplate::New(Count0101)->GetFunction());
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
 * 设置红球开奖号码
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

    Handle<String> pStr = args[0]->ToString();
    int length = pStr->Utf8Length();
    char *pChar = new char[length];
    pStr->WriteUtf8(pChar);
    //设置开奖号码的类型信息
    obj->pDrawNum = new DrawNum(pChar, length);
    delete[] pChar;
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
 * 直选单式 排列三
 */
Handle<Value> Check::Count0100(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();

    //获得号码的字符串
    Local<Object> pObj = Local<Object>::Cast(args[0]);
    Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
    int length = pNum->Utf8Length();
    char *pChar = new char[length];
    pNum->WriteUtf8(pChar);
    int itemslenth = 0;
    char *temChar = pChar;
    for (int ch = 0 ; ch < length ; ch ++){
        char temp = pChar[ch];
        if(temp == ';' || ch == length -1){
             itemslenth ++;
             DrawNum *num = new DrawNum(temChar, itemslenth);
             int len = num->getCharLen();
             int pLen = self->pDrawNum->getCharLen();
             if (len == pLen){
                 int hitCount = 0;
                 for(int i = 0 ; i < len ; i++){
                    if (num->getCharAt(i) == self->pDrawNum->getCharAt(i)){
                        hitCount ++;
                    }
                 }
                 if(hitCount >= 3){
                    self->gl->appendBonusObj(array, 1, 1);
                 }
             }
             delete num;
             itemslenth = 0;
             if(ch < length - 1)
             {
                 temChar = pChar + ch + 1;
             }
        }else{
               itemslenth ++;
        }
    }
    delete[] pChar;
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

    //获得号码的字符串
    Local<Object> pObj = Local<Object>::Cast(args[0]);
    Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
    int length = pNum->Utf8Length();
    char *pChar = new char[length];
    pNum->WriteUtf8(pChar);
    int itemslenth = 0;
    int hitCount = 0;
    char *numChar = pChar;
    int pLen = 0;
    for(int ch = 0 ; ch < length ; ch ++){
        char temp = pChar[ch];
        if(temp == '|' || ch == length-1){
            if(ch == length-1 && temp != ';'){
                itemslenth ++;
            }
            IntArray *fushiArray = new IntArray(16, numChar, itemslenth, ',');
            int pnum = MathUtil::CharToInt(self->pDrawNum->getCharAt(pLen));
            for(int i = 0 ; i < fushiArray->length(); i++){
                if (fushiArray->get(i) == pnum){
                   hitCount ++;
                }
            }
           delete fushiArray;

           pLen++;
           itemslenth = 0;
           if(ch < length -1){
               numChar = pChar + ch + 1;
           }
        }else{
            itemslenth ++;
        }
    }
    if(hitCount >= 3){
        self->gl->appendBonusObj(array, 1, 1);
    }
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}