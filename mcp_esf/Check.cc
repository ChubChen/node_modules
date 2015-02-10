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
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2100"), FunctionTemplate::New(Count2100)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2101"), FunctionTemplate::New(Count2101)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2200"), FunctionTemplate::New(Count2200)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2201"), FunctionTemplate::New(Count2201)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2202"), FunctionTemplate::New(Count2202)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2300"), FunctionTemplate::New(Count2300)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2301"), FunctionTemplate::New(Count2301)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2302"), FunctionTemplate::New(Count2302)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2400"), FunctionTemplate::New(Count2400)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2401"), FunctionTemplate::New(Count2401)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2402"), FunctionTemplate::New(Count2402)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2500"), FunctionTemplate::New(Count2500)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2501"), FunctionTemplate::New(Count2501)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2502"), FunctionTemplate::New(Count2502)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2600"), FunctionTemplate::New(Count2600)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2601"), FunctionTemplate::New(Count2601)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2602"), FunctionTemplate::New(Count2602)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2700"), FunctionTemplate::New(Count2700)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2701"), FunctionTemplate::New(Count2701)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2702"), FunctionTemplate::New(Count2702)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2800"), FunctionTemplate::New(Count2800)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2900"), FunctionTemplate::New(Count2900)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2901"), FunctionTemplate::New(Count2901)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2902"), FunctionTemplate::New(Count2902)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2903"), FunctionTemplate::New(Count2903)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count2906"), FunctionTemplate::New(Count2906)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count3000"), FunctionTemplate::New(Count3000)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count3001"), FunctionTemplate::New(Count3001)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count3007"), FunctionTemplate::New(Count3007)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count3003"), FunctionTemplate::New(Count3003)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count3006"), FunctionTemplate::New(Count3006)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count3200"), FunctionTemplate::New(Count3200)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count3201"), FunctionTemplate::New(Count3201)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count3207"), FunctionTemplate::New(Count3207)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count3203"), FunctionTemplate::New(Count3203)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count3206"), FunctionTemplate::New(Count3206)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count3100"), FunctionTemplate::New(Count3100)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count3101"), FunctionTemplate::New(Count3101)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count3102"), FunctionTemplate::New(Count3102)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count3103"), FunctionTemplate::New(Count3103)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count3106"), FunctionTemplate::New(Count3106)->GetFunction());


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
 * 11选5  任选一单式
 */
Handle<Value> Check::Count2100(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];

        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(2, lotNumChar , len, ',');
            for(int i = 0; i < numArray->length(); i++){
                if(numArray->get(i) == self->pDrawNum->getPNum()->get(0)){
                    self->gl->appendBonusObj(array, 1, 1);
                    break;
                }
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
 * 11选5  任选一复式
 */
Handle<Value> Check::Count2101(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(11, lotNumChar , len, ',');
            for(int i = 0; i < numArray->length(); i++){
                if(numArray->get(i) == self->pDrawNum->getPNum()->get(0)){
                    self->gl->appendBonusObj(array, 1, 1);
                    break;
                }
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
 * 任选二单式
 */
Handle<Value> Check::Count2200(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(11, lotNumChar , len, ',');
            int hitCount = self->getHitCount(numArray, self->pDrawNum->getPNum());
            if (hitCount == 2){
                self->gl->appendBonusObj(array, 2, 1);
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
 * 任选二复式
 */
Handle<Value> Check::Count2201(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(11, lotNumChar , len, ',');
            int hitCount = self->getHitCount(numArray, self->pDrawNum->getPNum());
            int count = MathUtil::GetC(hitCount, 2);
            if (count > 0){
                self->gl->appendBonusObj(array, 2, count);
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
 * 任选二胆拖
 */
Handle<Value> Check::Count2202(const Arguments& args)
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

    int len = 0 ;
    char *lotNumChar = pChar;
    IntArray *danArray = 0;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
        
        if(temp == '$' ){
            danArray =  new IntArray(1 ,lotNumChar, len, ',');
            if(ch < length - 1){
               lotNumChar = pChar + ch + 1;
            }
            break;
        }
        len ++;
    }
    IntArray *tuoArray = new IntArray(10, lotNumChar, length - len -1, ',');
    int hitCount = self->getHitCount(danArray, self->pDrawNum->getPNum());
    if(hitCount == danArray->length()){
        int hitTuoCount = self->getHitCount(tuoArray, self->pDrawNum->getPNum());
        int count = MathUtil::GetC(hitTuoCount, 2 - danArray->length());
        if(count > 0){
            self->gl->appendBonusObj(array, 2, count);
        }
    }
    delete danArray;
    delete tuoArray;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}


/**
 * 任选三单式
 */
Handle<Value> Check::Count2300(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(11, lotNumChar , len, ',');
            int hitCount = self->getHitCount(numArray, self->pDrawNum->getPNum());
            if (hitCount == 3){
                self->gl->appendBonusObj(array, 3, 1);
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
 * 任选三复式
 */
Handle<Value> Check::Count2301(const Arguments& args)
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

    int len = 0 ;
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
        
        if(temp == ';' || ch == length -1 ){
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(11, lotNumChar , len, ',');
            int hitCount = self->getHitCount(numArray, self->pDrawNum->getPNum());
            int count = MathUtil::GetC(hitCount, 3);
            if (count > 0){
                self->gl->appendBonusObj(array, 3, count);
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
 * 任选三胆拖
 */
Handle<Value> Check::Count2302(const Arguments& args)
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

    int len = 0 ;
    char *lotNumChar = pChar;
    IntArray *danArray = 0;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
        
        if(temp == '$' ){
            danArray =  new IntArray(3 ,lotNumChar, len, ',');
            if(ch < length - 1){
               lotNumChar = pChar + ch + 1;
            }
            break;
        }
        len ++;
    }
    IntArray *tuoArray = new IntArray(10, lotNumChar, length - len -1, ',');
    int hitCount = self->getHitCount(danArray, self->pDrawNum->getPNum());
    if(hitCount == danArray->length()){
        int hitTuoCount = self->getHitCount(tuoArray, self->pDrawNum->getPNum());
        int count = MathUtil::GetC(hitTuoCount, 3 - danArray->length());
        if(count > 0){
            self->gl->appendBonusObj(array, 3, count);
        }
    }
    delete danArray;
    delete tuoArray;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/**
 * 任选四单式
 */
Handle<Value> Check::Count2400(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(11, lotNumChar , len, ',');
            int hitCount = self->getHitCount(numArray, self->pDrawNum->getPNum());
            if (hitCount == 4){
                self->gl->appendBonusObj(array, 4, 1);
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
 * 任选四复式
 */
Handle<Value> Check::Count2401(const Arguments& args)
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

    int len = 0 ;
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
        
        if(temp == ';' || ch == length -1 ){
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(11, lotNumChar , len, ',');
            int hitCount = self->getHitCount(numArray, self->pDrawNum->getPNum());
            int count = MathUtil::GetC(hitCount, 4);
            if (count > 0){
                self->gl->appendBonusObj(array, 4, count);
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
 * 任选四胆拖
 */
Handle<Value> Check::Count2402(const Arguments& args)
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

    int len = 0 ;
    char *lotNumChar = pChar;
    IntArray *danArray = 0;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
        
        if(temp == '$' ){
            danArray =  new IntArray(4 ,lotNumChar, len, ',');
            if(ch < length - 1){
               lotNumChar = pChar + ch + 1;
            }
            break;
        }
        len ++;
    }
    IntArray *tuoArray = new IntArray(10, lotNumChar, length - len -1, ',');
    int hitCount = self->getHitCount(danArray, self->pDrawNum->getPNum());
    if(hitCount == danArray->length()){
        int hitTuoCount = self->getHitCount(tuoArray, self->pDrawNum->getPNum());
        int count = MathUtil::GetC(hitTuoCount, 4 - danArray->length());
        if(count > 0){
            self->gl->appendBonusObj(array, 4, count);
        }
    }
    delete danArray;
    delete tuoArray;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}



/**
 * 任选五单式
 */
Handle<Value> Check::Count2500(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(11, lotNumChar , len, ',');
            int hitCount = self->getHitCount(numArray, self->pDrawNum->getPNum());
            if (hitCount == 5){
                self->gl->appendBonusObj(array, 5, 1);
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
 * 任选五复式
 */
Handle<Value> Check::Count2501(const Arguments& args)
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

    int len = 0 ;
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
        
        if(temp == ';' || ch == length -1 ){
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(11, lotNumChar , len, ',');
            int hitCount = self->getHitCount(numArray, self->pDrawNum->getPNum());
            int count = MathUtil::GetC(hitCount, 5);
            if (count > 0){
                self->gl->appendBonusObj(array, 5, count);
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
 * 任选五胆拖
 */
Handle<Value> Check::Count2502(const Arguments& args)
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

    int len = 0 ;
    char *lotNumChar = pChar;
    IntArray *danArray = 0;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
        
        if(temp == '$' ){
            danArray =  new IntArray(5 ,lotNumChar, len, ',');
            if(ch < length - 1){
               lotNumChar = pChar + ch + 1;
            }
            break;
        }
        len ++;
    }
    IntArray *tuoArray = new IntArray(10, lotNumChar, length - len -1, ',');
    int hitCount = self->getHitCount(danArray, self->pDrawNum->getPNum());
    if(hitCount == danArray->length()){
        int hitTuoCount = self->getHitCount(tuoArray, self->pDrawNum->getPNum());
        int count = MathUtil::GetC(hitTuoCount, 5 - danArray->length());
        if(count > 0){
            self->gl->appendBonusObj(array, 5, count);
        }
    }
    delete danArray;
    delete tuoArray;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}


/**
 * 任选六单式
 */
Handle<Value> Check::Count2600(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(11, lotNumChar , len, ',');
            int hitCount = self->getHitCount(numArray, self->pDrawNum->getPNum());
            if (hitCount == 5){
                self->gl->appendBonusObj(array, 6, 1);
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
 * 任选六复式
 */
Handle<Value> Check::Count2601(const Arguments& args)
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

    int len = 0 ;
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
        
        if(temp == ';' || ch == length -1 ){
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(11, lotNumChar , len, ',');
            int hitCount = self->getHitCount(numArray, self->pDrawNum->getPNum());
            if(hitCount == 5){
                int count = MathUtil::GetC(numArray->length() - 5, 1);
                if (count > 0){
                    self->gl->appendBonusObj(array, 6, count);
                }
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
 * 任选四胆拖
 */
Handle<Value> Check::Count2602(const Arguments& args)
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

    int len = 0 ;
    char *lotNumChar = pChar;
    IntArray *danArray = 0;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
        
        if(temp == '$' ){
            danArray =  new IntArray(6 ,lotNumChar, len, ',');
            if(ch < length - 1){
               lotNumChar = pChar + ch + 1;
            }
            break;
        }
        len ++;
    }
    IntArray *tuoArray = new IntArray(10, lotNumChar, length - len -1, ',');
    int hitCount = self->getHitCount(danArray, self->pDrawNum->getPNum());
    int hitTuoCount = self->getHitCount(tuoArray, self->pDrawNum->getPNum());
    if(hitCount + hitTuoCount == 5 && hitTuoCount <= 6 - danArray->length()){
        int count = MathUtil::GetC(tuoArray->length() - hitTuoCount , 6 - danArray->length() - hitTuoCount);
        if(count > 0){
            self->gl->appendBonusObj(array, 6, count);
        }
    }
    delete danArray;
    delete tuoArray;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/**
 * 任选七单式
 */
Handle<Value> Check::Count2700(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(11, lotNumChar , len, ',');
            int hitCount = self->getHitCount(numArray, self->pDrawNum->getPNum());
            if (hitCount == 5){
                self->gl->appendBonusObj(array, 7, 1);
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
 * 任选七复式
 */
Handle<Value> Check::Count2701(const Arguments& args)
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

    int len = 0 ;
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
        
        if(temp == ';' || ch == length -1 ){
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(11, lotNumChar , len, ',');
            int hitCount = self->getHitCount(numArray, self->pDrawNum->getPNum());
            if(hitCount == 5){
                int count = MathUtil::GetC(numArray->length() - 5, 2);
                if (count > 0){
                    self->gl->appendBonusObj(array, 7, count);
                }
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
 * 任选七胆拖
 */
Handle<Value> Check::Count2702(const Arguments& args)
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

    int len = 0 ;
    char *lotNumChar = pChar;
    IntArray *danArray = 0;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
        
        if(temp == '$' ){
            danArray =  new IntArray(7 ,lotNumChar, len, ',');
            if(ch < length - 1){
               lotNumChar = pChar + ch + 1;
            }
            break;
        }
        len ++;
    }
    IntArray *tuoArray = new IntArray(10, lotNumChar, length - len -1, ',');
    int hitCount = self->getHitCount(danArray, self->pDrawNum->getPNum());
        int hitTuoCount = self->getHitCount(tuoArray, self->pDrawNum->getPNum());
        if(hitCount + hitTuoCount == 5 && hitTuoCount <= 7 - danArray->length()){
            int count = MathUtil::GetC(tuoArray->length() - hitTuoCount , 7 - danArray->length() - hitTuoCount);
            if(count > 0){
                self->gl->appendBonusObj(array, 7, count);
            }
        }
    delete danArray;
    delete tuoArray;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/**
 * 任选八单式
 */
Handle<Value> Check::Count2800(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(11, lotNumChar , len, ',');
            int hitCount = self->getHitCount(numArray, self->pDrawNum->getPNum());
            if (hitCount == 5){
                self->gl->appendBonusObj(array, 8, 1);
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
 * 前二组选 单式
 */
Handle<Value> Check::Count2900(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(2, lotNumChar , len, ',');
            IntArray* prizeArray = self->getCopyLengthIntArray(self->pDrawNum->getPNum(), 0, 2);
            int hitCount = self->getHitCount(numArray, prizeArray);
            if( hitCount == 2){
                self->gl->appendBonusObj(array, 9, 1);
            }

            delete numArray;
            delete prizeArray;
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
 * 前二组选 复式
 */
Handle<Value> Check::Count2901(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(11, lotNumChar , len, ',');
            IntArray* prizeArray = self->getCopyLengthIntArray(self->pDrawNum->getPNum(), 0, 2);
            int hitCount = self->getHitCount(numArray, prizeArray);
            if(hitCount == 2){
                self->gl->appendBonusObj(array, 9, 1);
            }
            delete prizeArray;
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
 * 前二组选 胆拖
 */
Handle<Value> Check::Count2902(const Arguments& args)
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

    int len = 0 ;
    char *lotNumChar = pChar;
    IntArray *danArray = 0;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
        
        if(temp == '$' ){
            danArray =  new IntArray(1 ,lotNumChar, len, ',');
            if(ch < length - 1){
               lotNumChar = pChar + ch + 1;
            }
            break;
        }
        len ++;
    }
    IntArray *tuoArray = new IntArray(10, lotNumChar, length - len -1, ',');
    IntArray *prizeArray = self->getCopyLengthIntArray(self->pDrawNum->getPNum(), 0, 2);;

    int danHitCount = self->getHitCount(danArray, prizeArray);
    int tuoHitCount = self->getHitCount(tuoArray, prizeArray);

    if(danHitCount == 1 && tuoHitCount == 2 - danHitCount){
        self->gl->appendBonusObj(array, 9, 1);
    }

    delete danArray;
    delete prizeArray;
    delete tuoArray;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}


/**
 * 前二组选 合值
 */
Handle<Value> Check::Count2903(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(21, lotNumChar , len, ',');
            int hezhi = self->pDrawNum->getPNum()->get(0) + self->pDrawNum->getPNum()->get(1);
            for(int i = 0; i < numArray->length(); i++){
                if(numArray->get(i) == hezhi){
                    self->gl->appendBonusObj(array, 9, 1);
                }
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
 * 前二组选 跨度
 */
Handle<Value> Check::Count2906(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(21, lotNumChar , len, ',');
            int kuadu = self->getKuadu(self->pDrawNum->getPNum(), 2);
            for(int i = 0; i < numArray->length(); i++){
                if(numArray->get(i) == kuadu){
                    self->gl->appendBonusObj(array, 9, 1);
                }
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
 * 前三组选 单式
 */
Handle<Value> Check::Count3100(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(3, lotNumChar , len, ',');
            IntArray* prizeArray = self->getCopyLengthIntArray(self->pDrawNum->getPNum(), 0, 3);
            int hitCount = self->getHitCount(numArray, prizeArray);
            if(hitCount == 3){
                self->gl->appendBonusObj(array, 11, 1);
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
 * 前三组选 复式
 */
Handle<Value> Check::Count3101(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(11, lotNumChar , len, ',');
            IntArray* prizeArray = self->getCopyLengthIntArray(self->pDrawNum->getPNum(), 0, 3);
            int hitCount = self->getHitCount(numArray, prizeArray);
            if(hitCount == 3){
                self->gl->appendBonusObj(array, 11, 1);
            }
            delete prizeArray;
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
 * 前三组选 胆拖
 */
Handle<Value> Check::Count3102(const Arguments& args)
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

    int len = 0 ;
    char *lotNumChar = pChar;
    IntArray *danArray = 0;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
        
        if(temp == '$' ){
            danArray =  new IntArray(2 ,lotNumChar, len, ',');
            if(ch < length - 1){
               lotNumChar = pChar + ch + 1;
            }
            break;
        }
        len ++;
    }
    IntArray *tuoArray = new IntArray(10, lotNumChar, length - len -1, ',');
    IntArray *prizeArray = self->getCopyLengthIntArray(self->pDrawNum->getPNum(), 0, 3);
    int danHitCount = self->getHitCount(danArray, prizeArray);
    int tuoHitCount = self->getHitCount(tuoArray, prizeArray);

    if(danHitCount + tuoHitCount == 3 && danHitCount == danArray->length()){
        self->gl->appendBonusObj(array, 11, 1);
    }

    delete danArray;
    delete prizeArray;
    delete tuoArray;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}


/**
 * 前三组选 合值
 */
Handle<Value> Check::Count3103(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(21, lotNumChar , len, ',');
            int hezhi = self->pDrawNum->getPNum()->get(0) + self->pDrawNum->getPNum()->get(1) + self->pDrawNum->getPNum()->get(2);
            for(int i = 0; i < numArray->length(); i++){
                if(numArray->get(i) == hezhi){
                    self->gl->appendBonusObj(array, 11, 1);
                }
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
 * 前三组选 跨度
 */
Handle<Value> Check::Count3106(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(21, lotNumChar , len, ',');
            int kuadu = self->getKuadu(self->pDrawNum->getPNum(), 3);
            for(int i = 0; i < numArray->length(); i++){
                if(numArray->get(i) == kuadu){
                    self->gl->appendBonusObj(array, 11, 1);
                }
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



int Check::getHitCount(IntArray *lotArray, IntArray *prizeArray){
    IntArray *lot = lotArray;
    int len = lot->length();
    IntArray *prize = prizeArray;
    int plen = prize->length();
    int hitCount = 0; //中红球的个数
     for(int i = 0; i< len; i++){
            for (int j = 0; j < plen; j++){
                if (lot->get(i) == prize->get(j)){
                    hitCount ++;
                }
            }
        }
    return hitCount;
}

/**
 * 前二直选 单式
 */
Handle<Value> Check::Count3000(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(2, lotNumChar , len, '|');
            if(numArray->get(0) == self->pDrawNum->getPNum()->get(0) && numArray->get(1) == self->pDrawNum->getPNum()->get(1)){
                self->gl->appendBonusObj(array, 10, 1);
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
 * 前二直选 复式
 */
Handle<Value> Check::Count3001(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(11, lotNumChar , len, ',');
            IntArray* prizeArray = self->getCopyLengthIntArray(self->pDrawNum->getPNum(), 0, 2);
            int hitCount = self->getHitCount(numArray, prizeArray);
            if(hitCount == 2){
                self->gl->appendBonusObj(array, 10, 1);
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
 * 前二直选 合值
 */
Handle<Value> Check::Count3003(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(21, lotNumChar , len, ',');
            int hezhi = self->pDrawNum->getPNum()->get(0) + self->pDrawNum->getPNum()->get(1);
            for(int i = 0; i < numArray->length(); i++){
                if(numArray->get(i) == hezhi){
                    self->gl->appendBonusObj(array, 10, 1);
                }
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
 * 前二直选 跨度
 */
Handle<Value> Check::Count3006(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(21, lotNumChar , len, ',');
            int kuadu = self->getKuadu(self->pDrawNum->getPNum(), 2);
            for(int i = 0; i < numArray->length(); i++){
                if(numArray->get(i) == kuadu){
                    self->gl->appendBonusObj(array, 10, 1);
                }
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
 * 前二直选 定位
 */
Handle<Value> Check::Count3007(const Arguments& args)
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

    int len = 0 ;
    char *lotNumChar = pChar;
    IntArray *firstArray = 0;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
        
        if(temp == '|' ){
            firstArray =  new IntArray(10 ,lotNumChar, len, ',');
            if(ch < length - 1){
               lotNumChar = pChar + ch + 1;
            }
            break;
        }
        len ++;
    }
    IntArray* secondArray = new IntArray(10, lotNumChar, length - len -1, ',');
    IntArray* prizeOne = new IntArray(1);
    prizeOne->put(self->pDrawNum->getPNum()->get(0));
    IntArray* prizeTwo = new IntArray(1);
    prizeTwo->put(self->pDrawNum->getPNum()->get(1));

    int firstHitCount = self->getHitCount(firstArray, prizeOne);
    int secondHitCount = self->getHitCount(secondArray, prizeTwo);
    if(firstHitCount == 1 && secondHitCount == 1){
        self->gl->appendBonusObj(array, 10, 1);
    }


    delete firstArray;
    delete secondArray;
    delete prizeOne;
    delete prizeTwo;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/**
 * 前三直选 单式
 */
Handle<Value> Check::Count3200(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(3, lotNumChar , len, '|');
            if(numArray->get(0) == self->pDrawNum->getPNum()->get(0) && numArray->get(1) == self->pDrawNum->getPNum()->get(1) && numArray->get(2) == self->pDrawNum->getPNum()->get(2)){
                self->gl->appendBonusObj(array, 12, 1);
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
 * 前三直选 复式
 */
Handle<Value> Check::Count3201(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(11, lotNumChar , len, ',');
            IntArray* prizeArray = self->getCopyLengthIntArray(self->pDrawNum->getPNum(), 0, 3);
            int hitCount = self->getHitCount(numArray, prizeArray);
            if(hitCount == 3){
                self->gl->appendBonusObj(array, 12, 1);
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
 * 前三直选 合值
 */
Handle<Value> Check::Count3203(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
         
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(21, lotNumChar , len, ',');
            int hezhi = self->pDrawNum->getPNum()->get(0) + self->pDrawNum->getPNum()->get(1) + self->pDrawNum->getPNum()->get(2);
            for(int i = 0; i < numArray->length(); i++){
                if(numArray->get(i) == hezhi){
                    self->gl->appendBonusObj(array, 12, 1);
                }
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
 * 前三直选 跨度
 */
Handle<Value> Check::Count3206(const Arguments& args)
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

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
        
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;

            IntArray* numArray = new IntArray(21, lotNumChar , len, ',');
            int kuadu = self->getKuadu(self->pDrawNum->getPNum(), 3);
            for(int i = 0; i < numArray->length(); i++){
                if(numArray->get(i) == kuadu){
                    self->gl->appendBonusObj(array, 12, 1);
                }
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
 * 前三直选 定位
 */
Handle<Value> Check::Count3207(const Arguments& args)
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

    int len = 0 ;
    char *lotNumChar = pChar;
    IntArray *firstArray = 0;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch];
        if(temp == '|' ){
            firstArray =  new IntArray(10 ,lotNumChar, len, ',');
            if(ch < length - 1){
               lotNumChar = pChar + ch + 1;
            }
            break;
        }
        len ++;
    }
    IntArray* secondArray = 0;
    int secondLen = 0;
    for(int ch = 0 ; ch < length - len - 1; ch++ ){
        char temp = pChar[ch];
        if(temp == '|' ){
            secondArray =  new IntArray(10 ,lotNumChar, secondLen, ',');
            if(ch < length - 1){
               lotNumChar = pChar + ch + 1;
            }
            break;
        }
        secondLen ++;
    }

    IntArray* threeArray = new IntArray(10, lotNumChar, length - len - secondLen - 2, ',');
    IntArray* prizeOne = new IntArray(1);
    prizeOne->put(self->pDrawNum->getPNum()->get(0));
    IntArray* prizeTwo = new IntArray(1);
    prizeTwo->put(self->pDrawNum->getPNum()->get(1));
    IntArray* prizeThree = new IntArray(1);
    prizeThree->put(self->pDrawNum->getPNum()->get(2));


    int firstHitCount = self->getHitCount(firstArray, prizeOne);
    int secondHitCount = self->getHitCount(secondArray, prizeTwo);
    int threeHitCount = self->getHitCount(threeArray, prizeThree);
    if(firstHitCount == 1 && secondHitCount == 1 && threeHitCount == 1){
        self->gl->appendBonusObj(array, 12, 1);
    }


    delete firstArray;
    delete secondArray;
    delete threeArray;
    delete prizeOne;
    delete prizeTwo;
    delete prizeThree;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

IntArray* Check::getCopyLengthIntArray(IntArray* numArray, int form, int len){
    IntArray* newIntArray = new IntArray(len);
    for(int i= 0; i< len ; i++){
        if(i >= form && i <= numArray->length() - 1 ){
            newIntArray->put(numArray->get(i));
        }
    }
    return newIntArray;
}

int Check::getKuadu(IntArray* numArray, int len){
    if(len == 2){
        return MathUtil::abs(numArray->get(1) - numArray->get(0));
    }else{
        int kuadu = 0 ;
        int temp = MathUtil::abs(numArray->get(1) - numArray->get(0));
        if(temp > kuadu){
            kuadu = temp;
        }
        temp = MathUtil::abs(numArray->get(2) - numArray->get(1));
        if(temp > kuadu){
            kuadu = temp;
        }
        temp = MathUtil::abs(numArray->get(2) - numArray->get(0));
        if(temp > kuadu){
            kuadu = temp;
        }
        return kuadu;
    }
}
