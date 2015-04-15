#include <node.h>
#include "Check.h"

using namespace v8;

Persistent<Function> Check::constructor;

Check::Check()
{
    this->gl = NULL;
    this->pDrawNum = NULL;
     //二维数组，
    this->bonusRule[0][0] = 2;
    this->bonusRule[0][1] = 6;
    this->bonusRule[1][0] = 3;
    this->bonusRule[1][1] = 5;
    this->bonusRule[2][0] = 4;
    this->bonusRule[2][1] = 4;
    this->bonusRule[3][0] = 5;
    this->bonusRule[3][1] = 3;
    this->bonusRule[4][0] = 6;
    this->bonusRule[4][1] = 2;
    this->bonusRule[5][0] = 7;
    this->bonusRule[5][1] = 1;
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
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0000"), FunctionTemplate::New(Count0000)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0001"), FunctionTemplate::New(Count0001)->GetFunction());


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
 * 七星彩 单式
 */
Handle<Value> Check::Count0000(const Arguments& args)
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
    int len = 0;
    char *temChar = pChar;
    for (int ch = 0 ; ch < length ; ch ++){
        char temp = pChar[ch];
        if(temp == ';' || ch == length -1){
             len ++;
             IntArray  *itemNumber =new IntArray(7, temChar, len, '|');
             int hitCount = self->getHitCountByOrder(self->pDrawNum->getPNum(), itemNumber);

             for(int i = 0; i < 6 ;i++ ){
                 int *temp = (int *)self->bonusRule[i];
                 if(hitCount == temp[0]){
                    self->gl->appendBonusObj(array, temp[1], 1);
                 }
             }

             delete itemNumber;
             len = 0;
             if(ch < length - 1)
             {
                 temChar = pChar + ch + 1;
             }
        }else{
               len ++;
        }
    }
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}


/**
 * 七星彩复式
 */
Handle<Value> Check::Count0001(const Arguments& args)
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
    int len = 0;
    char *numberChar = pChar;
    int pLen = 0;
    int hitCount = 0;
    int maxHitCount = 0;
    int nextHitIndex = 0;

    for(int ch = 0 ; ch < length ; ch ++){
        char temp = pChar[ch];
        if(temp == '|' || ch == length-1){
            if(ch == length-1 && temp != ';'){
                len ++;
            }
            IntArray *fuShiArray = new IntArray(10, numberChar, len, ',');
            int pNum = self->pDrawNum->getPNum()->get(pLen);
            for(int i = 0 ; i < fuShiArray->length(); i++){
                if (fuShiArray->get(i) == pNum && pLen == nextHitIndex){
                    nextHitIndex = pLen + 1;
                    hitCount ++;
                    break;
                }
                 //第一次不连续 并且 中奖
                if(fuShiArray->get(i) == pNum && (nextHitIndex - pLen) != 1){
                    nextHitIndex = pLen + 1;
                    hitCount = 1;
                }

            }
            if(hitCount > maxHitCount){
                maxHitCount = hitCount;
            }
           delete fuShiArray;
           pLen++;
           len = 0;
           if(ch < length -1){
               numberChar = pChar + ch + 1;
           }
        }else{
            len ++;
        }
    }
     for(int i = 0; i < 6 ;i++ ){
         int *temp = (int *)self->bonusRule[i];
         if(maxHitCount == temp[0]){
            self->gl->appendBonusObj(array, temp[1], 1);
         }
     }
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}


int Check::getHitCountByOrder(IntArray* lotArray, IntArray* prizeArray)
{
    IntArray *lot = lotArray;
    int len = lot->length();
    IntArray *prize = prizeArray;
    int plen = prize->length();
    if(len > plen){
        len = plen;
    }
    int maxHitCount = 0;
    int hitCount = 0; //中红球的个数
    int nextHitIndex = 0;
    for(int i = 0; i< plen; i++){
        if (lot->get(i) == prize->get(i) && i == nextHitIndex){
            nextHitIndex = i + 1;
            hitCount ++;
        }
         //第一次不连续 并且 中奖
        if(lot->get(i) == prize->get(i) && (nextHitIndex - i) != 1){
            nextHitIndex = i + 1;
            hitCount = 1;
        }
        if(hitCount > maxHitCount){
           maxHitCount = hitCount;
        }
    }
    return maxHitCount;
}

