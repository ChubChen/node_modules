#include <node.h>
#include "GradeLevel.h"

using namespace v8;

Persistent<Function> GradeLevel::constructor;

GradeLevel::GradeLevel(int levelCount)
{
    this->levelCount = levelCount;
    this->bonusArray = new long[levelCount];
}

GradeLevel::~GradeLevel()
{
    delete[] this->bonusArray;
}

void GradeLevel::setBonus(int level, long bonus)
{
    this->bonusArray[level] = bonus;
}

int GradeLevel::getLevelCount()
{
    return this->levelCount;
}

void GradeLevel::Init()
{
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("GradeLevel"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->PrototypeTemplate()->Set(String::NewSymbol("setBonus"), FunctionTemplate::New(SetBonus)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("getBonus"), FunctionTemplate::New(GetBonus)->GetFunction());
    constructor = Persistent<Function>::New(tpl->GetFunction());
}

/**
 * 真正初始化的方法
 */
Handle<Value> GradeLevel::New(const Arguments& args)
{
    HandleScope scope;
    if(args.IsConstructCall()){ //from new GradeLevel()
        int levelCount = args[0]->ToInt32()->Value();
        GradeLevel * obj = new GradeLevel(levelCount);
        obj->Wrap(args.This());
        return args.This();
    }
    else{   //from GradeLevel()
        const int argc = 1;
        Local<Value> argv[argc] = {args[0]};
        return scope.Close(constructor->NewInstance(argc, argv));
    }
}

/**
 * 设置奖级的金额
 */
Handle<Value> GradeLevel::SetBonus(const Arguments& args)
{
    HandleScope scope;
    //校验参数的类型
    if (!args[0]->IsArray()) {
        ThrowException(Exception::TypeError(String::New("Wrong arguments")));
        return scope.Close(Undefined());
    }
    GradeLevel *obj = ObjectWrap::Unwrap<GradeLevel>(args.This());
    Local<Array> pArray = Local<Array>::Cast(args[0]);
    int length = pArray->Length();
    if(length != obj->levelCount)
    {
        ThrowException(Exception::Error(String::New("arguments length illegle")));
        return scope.Close(Undefined());
    }
    int index = 0;
    for(; index < obj->levelCount; index++)
    {
        obj->bonusArray[index] = pArray->Get(index)->IntegerValue();
    }
    return scope.Close(Undefined());
}

/**
 * 获得奖级的金额
 */
Handle<Value> GradeLevel::GetBonus(const Arguments& args)
{
    HandleScope scope;
    //校验参数的长度
    if (args.Length() < 1) {
        ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
        return scope.Close(Undefined());
    }
    //校验参数的类型
    if (!args[0]->IsNumber()) {
        ThrowException(Exception::TypeError(String::New("Wrong arguments")));
        return scope.Close(Undefined());
    }
    int index = args[0]->ToInt32()->Value();
    GradeLevel *obj = ObjectWrap::Unwrap<GradeLevel>(args.This());
    Local<Number> num = Number::New(obj->bonusArray[index]);
    return scope.Close(num);
}

/**
 * 根据奖级获得金额
 */
long GradeLevel::getBonus(int level)
{
    return this->bonusArray[level];
}

/**
 * Init方法中已经初始化过constructor变量，所以在这儿可以使用
 * constructor来新建一个对象。
 */
Handle<Value> GradeLevel::NewInstance(const Arguments& args)
{
    HandleScope scope;
    const unsigned argc = 1;
    Handle<Value> argv[argc] = {args[0]};
    Local<Object> instance = constructor->NewInstance(argc, argv);
    return scope.Close(instance);
}

/**
 * 获得奖级的明细
 */
void GradeLevel::setBonusObj(Handle<Object> obj, int level, int count)
{
    long bonus = this->getBonus(level - 1);
    long curBonusBeforeTax = bonus*count;   //level-1，奖级从1开始，bonus的序号从0开始
    if(bonus > 1000000){
        bonus = bonus * 4 / 5;
    }
    long curBonus = bonus *count;
    Local<String> bonusKey = String::NewSymbol("bonus");
    Local<String> bonusBeforeTaxKey = String::NewSymbol("bonusBeforeTax");
    Local<String> levelKey = String::NewSymbol("level");
    Local<String> countKey = String::NewSymbol("count");
    if(!obj->Get(levelKey)->IsNull())
    {
        curBonus += obj->Get(bonusKey)->IntegerValue();
        curBonusBeforeTax += obj->Get(bonusBeforeTaxKey)->IntegerValue();
        count += obj->Get(countKey)->Int32Value();
    }
    obj->Set(bonusKey, Number::New(curBonus));
    obj->Set(bonusBeforeTaxKey, Number::New(curBonusBeforeTax));
    obj->Set(levelKey, Number::New(level));
    obj->Set(countKey, Number::New(count));
    return;
}

/**
 * 添加指定奖级的指定注数到奖级明细
 */
void GradeLevel::appendBonusObj(v8::Handle<v8::Array> array, int level, int count)
{
    //校验奖级和注数，都必须大于0
    if(level <= 0 || count <= 0)
    {
        return;
    }
    int len = array->Length();
    if(len == 0)
    {
        Handle<Object> obj = Object::New();
        this->setBonusObj(obj, level, count);
        array->Set(len, obj);
    }
    else
    {
        bool exist = false;
        for(int i = 0; i < len; i++)
        {
            Handle<Object> obj = array->Get(i)->ToObject();
            int tLevel = obj->Get(String::NewSymbol("level"))->Int32Value();
            if(tLevel == level)
            {
                exist = true;
                this->setBonusObj(obj, level, count);
                break;
            }
        }
        if(!exist)
        {
            Handle<Object> obj = Object::New();
            this->setBonusObj(obj, level, count);
            array->Set(len, obj);
        }
    }
    return;
}

/**
 * 获得算奖的结果
 */
Handle<Object> GradeLevel::getRst(v8::Handle<v8::Array> array)
{
    long bonus = 0;
    long bonusBeforeTax = 0;
    int len = array->Length();
    Local<String> bonusKey = String::NewSymbol("bonus");
    Local<String> bonusBeforeTaxKey = String::NewSymbol("bonusBeforeTax");
    for(int i = 0; i < len; i++)
    {
        Handle<Object> obj = array->Get(i)->ToObject();
        bonus += obj->Get(String::NewSymbol("bonus"))->IntegerValue();
        bonusBeforeTax += obj->Get(String::NewSymbol("bonusBeforeTax"))->IntegerValue();
    }
    Handle<Object> rst = Object::New();
    rst->Set(bonusKey, Number::New(bonus));
    rst->Set(bonusBeforeTaxKey, Number::New(bonusBeforeTax));
    rst->Set(String::NewSymbol("bonusDetail"), array);
    return rst;
}