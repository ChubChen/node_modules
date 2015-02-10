#include <node.h>
#include "Check.h"

using namespace v8;

Persistent<Function> Check::constructor;

Check::Check()
{
    this->gl = NULL;
    this->pDrawNum = NULL;
    this->hezhiRules[0]= -1;
    this->hezhiRules[1]= -1;
    this->hezhiRules[2]= -1;
    this->hezhiRules[3]= -1;
    this->hezhiRules[4]=  1;
    this->hezhiRules[5]=  2;
    this->hezhiRules[6]=  3;
    this->hezhiRules[7]=  4;
    this->hezhiRules[8]=  5;
    this->hezhiRules[9]=  6;
    this->hezhiRules[10]=  7;
    this->hezhiRules[11]=  8;
    this->hezhiRules[12]=  9;
    this->hezhiRules[13]= 10;
    this->hezhiRules[14]= 11;
    this->hezhiRules[15]= 12;
    this->hezhiRules[16]= 13;
    this->hezhiRules[17]= 14;

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
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0200"), FunctionTemplate::New(Count0200)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0300"), FunctionTemplate::New(Count0300)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0401"), FunctionTemplate::New(Count0401)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0501"), FunctionTemplate::New(Count0501)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0601"), FunctionTemplate::New(Count0601)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0700"), FunctionTemplate::New(Count0700)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0800"), FunctionTemplate::New(Count0800)->GetFunction());


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
    char *pChar = new char[length + 1];
    pStr->WriteUtf8(pChar);
    *(pChar + length) = '\0';
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
*快三 三不同单选
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
    char *pChar = new char[length + 1];
    pNum->WriteUtf8(pChar);
    *(pChar + length) = '\0';

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];

        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(3, lotNumChar , len, ',');
            MathUtil::SelectSort(numArray);
            int hitCount = MathUtil::getHitCountByOrder(numArray, self->pDrawNum->getPNum());
            if(hitCount >= 3){
                self->gl->appendBonusObj(array, 19, 1);
            }
            delete numArray;
            if(ch < length -1){
                lotNumChar = pChar + ch + 1;
            }
            len = 0;
            continue;
        }
        len ++;
    }
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}


/**
*快三 二同单选
*/
Handle<Value> Check::Count0200(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    //获得号码的字符串
    Local<Object> pObj = Local<Object>::Cast(args[0]);
    Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
    int length = pNum->Utf8Length();
    char *pChar = new char[length + 1];
    pNum->WriteUtf8(pChar);
    *(pChar + length) = '\0';

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];

        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(3, lotNumChar , len, ',');
            MathUtil::SelectSort(numArray);
            int hitCount = MathUtil::getHitCountByOrder(numArray, self->pDrawNum->getPNum());
            if(hitCount >= 3){
                self->gl->appendBonusObj(array, 18, 1);
            }
            delete numArray;
            if(ch < length -1){
                lotNumChar = pChar + ch + 1;
            }
            len = 0;
            continue;
        }
        len ++;
    }
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/**
*快三 三同单选
*/
Handle<Value> Check::Count0300(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    //获得号码的字符串
    Local<Object> pObj = Local<Object>::Cast(args[0]);
    Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
    int length = pNum->Utf8Length();
    char *pChar = new char[length + 1];
    pNum->WriteUtf8(pChar);
    *(pChar + length) = '\0';

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];

        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(3, lotNumChar , len, ',');
            int prizeValue = self->pDrawNum->getPNum()->get(0)*100 + self->pDrawNum->getPNum()->get(1)*10 +self->pDrawNum->getPNum()->get(2);
            int lotValue = numArray->get(0)*100 + numArray->get(1)*10 + numArray->get(2);
            if(prizeValue == lotValue){
                self->gl->appendBonusObj(array, 16, 1);
            }
            delete numArray;
            if(ch < length -1){
                lotNumChar = pChar + ch + 1;
            }
            len = 0;
            continue;
        }
        len ++;
    }
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/**
*快三 合值普通
*/
Handle<Value> Check::Count0401(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    //获得号码的字符串
    Local<Object> pObj = Local<Object>::Cast(args[0]);
    Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
    int length = pNum->Utf8Length();
    char *pChar = new char[length + 1];
    pNum->WriteUtf8(pChar);
    *(pChar + length) = '\0';

    char *lotNumChar = pChar;
    //如果末尾包含了分号
    if(lotNumChar[length-1] == ';'){
        length = length-1;
    }
    IntArray *numArray = new IntArray(17, pChar, length, ',');
    int hezhi = self->pDrawNum->getHeZhi();
    for(int i = 0; i < numArray->length(); i++){
        if( numArray->get(i) == hezhi){
            self->gl->appendBonusObj(array, self->hezhiRules[hezhi], 1);
        }
    }
    delete numArray;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}


/**
*快三 二不同单选
*/
Handle<Value> Check::Count0501(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    //获得号码的字符串
    Local<Object> pObj = Local<Object>::Cast(args[0]);
    Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
    int length = pNum->Utf8Length();
    char *pChar = new char[length + 1];
    pNum->WriteUtf8(pChar);
    *(pChar + length) = '\0';

    char *lotNumChar = pChar;
    //如果末尾包含了分号
    if(lotNumChar[length-1] == ';'){
        length = length-1;
    }

    IntArray *firstArray = new IntArray(1);
    IntArray *secondArray = new IntArray(1);
    IntArray *numArray = new IntArray(15, pChar, length, ';');
    IntArray *prizeArray = self->pDrawNum->getPNum();
    for(int i = 0; i < numArray->length() ; i ++){
        int first = numArray->get(i) / 10;
        int second = numArray->get(i) % 10;
        firstArray->modify(0, first);
        secondArray->modify(0, second);
        if(MathUtil::getHitCount(firstArray, prizeArray) >0 && MathUtil::getHitCount(secondArray, prizeArray) > 0){
            self->gl->appendBonusObj(array, 20, 1);
        }
    }
    delete firstArray;
    delete secondArray;
    delete numArray;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}


/**
*快三 二同复选
*/
Handle<Value> Check::Count0601(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    //获得号码的字符串
    Local<Object> pObj = Local<Object>::Cast(args[0]);
    Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
    int length = pNum->Utf8Length();
    char *pChar = new char[length + 1];
    pNum->WriteUtf8(pChar);
    *(pChar + length) = '\0';

    char *lotNumChar = pChar;
    //如果末尾包含了分号
    if(lotNumChar[length-1] == ';'){
        length = length-1;
    }

    IntArray *lotArray = new IntArray(1);
    IntArray *numArray = new IntArray(15, pChar, length, ';');
    IntArray *prizeArray = self->pDrawNum->getPNum();
    for(int i = 0; i < numArray->length() ; i ++){
        int value = numArray->get(i) % 10;
        lotArray->modify(0, value) ;
        if(MathUtil::getHitCount(lotArray, prizeArray) >= 2){
            self->gl->appendBonusObj(array, 17, 1);
        }
    }
    delete lotArray;
    delete numArray;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}


/**
*快三 三同通选
*/
Handle<Value> Check::Count0700(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    //获得号码的字符串
    Local<Object> pObj = Local<Object>::Cast(args[0]);
    Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
    int length = pNum->Utf8Length();
    char *pChar = new char[length + 1];
    pNum->WriteUtf8(pChar);
    *(pChar + length) = '\0';

    char *lotNumChar = pChar;
    //如果末尾包含了分号
    if(lotNumChar[length-1] == ';'){
        length = length-1;
    }
    IntArray *numArray = new IntArray(6, pChar, length, ',');
    int prizeValue = self->pDrawNum->getPNum()->get(0)*100 + self->pDrawNum->getPNum()->get(1)*10 +self->pDrawNum->getPNum()->get(2);
    for(int i=0 ; i < numArray->length(); i++){
        if(numArray->get(i) == prizeValue){
            self->gl->appendBonusObj(array, 15, 1);
        }
    }
    delete numArray;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/**
*快三 三连号通选
*/
Handle<Value> Check::Count0800(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    //获得号码的字符串
    Local<Object> pObj = Local<Object>::Cast(args[0]);
    Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
    int length = pNum->Utf8Length();
    char *pChar = new char[length + 1];
    pNum->WriteUtf8(pChar);
    *(pChar + length) = '\0';

    char *lotNumChar = pChar;
    //如果末尾包含了分号
    if(lotNumChar[length-1] == ';'){
        length = length-1;
    }
    IntArray *numArray = new IntArray(6, pChar, length, ',');
    IntArray *prizeArray = self->pDrawNum->getPNum();
    int prizeValue = prizeArray->get(0)*100 + prizeArray->get(1)*10 + prizeArray->get(2);
    for(int i=0 ; i < numArray->length(); i++){
        if(numArray->get(i) == prizeValue){
            self->gl->appendBonusObj(array, 21, 1);
        }
    }
    delete numArray;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

