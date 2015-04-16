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
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0103"), FunctionTemplate::New(Count0103)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0104"), FunctionTemplate::New(Count0104)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0105"), FunctionTemplate::New(Count0105)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0106"), FunctionTemplate::New(Count0106)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0201"), FunctionTemplate::New(Count0201)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0202"), FunctionTemplate::New(Count0202)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0206"), FunctionTemplate::New(Count0206)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0301"), FunctionTemplate::New(Count0301)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0302"), FunctionTemplate::New(Count0302)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0306"), FunctionTemplate::New(Count0306)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0400"), FunctionTemplate::New(Count0400)->GetFunction());
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
    int len = 0;
    char *temChar = pChar;
    for (int ch = 0 ; ch < length ; ch ++){
        char temp = pChar[ch];
        if(temp == ';' || ch == length -1){
             if(ch == length -1 && temp != ';')
             len ++;
             IntArray  *itemNumber =new IntArray(3, temChar, len, '|');
             int hitCount = MathUtil::getHitCountByOrder(self->pDrawNum->getPNum(), itemNumber);
             if(hitCount == 3 ){
                self->gl->appendBonusObj(array, 1, 1);
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
    int len = 0;
    char *numberChar = pChar;
    int pLen = 0;
    int hitCount = 0;
    for(int ch = 0 ; ch < length ; ch ++){
        char temp = pChar[ch];
        if(temp == '|' || ch == length-1){
            if(ch == length-1 && temp != ';'){
                len ++;
            }
            IntArray *fuShiArray = new IntArray(10, numberChar, len, ',');
            int pNum = self->pDrawNum->getPNum()->get(pLen);
            for(int i = 0 ; i < fuShiArray->length(); i++){
                if (fuShiArray->get(i) == pNum){
                   hitCount ++;
                   break;
                }
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
    if(hitCount == 3){
        self->gl->appendBonusObj(array, 1, 1);
    }
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/***
和值计算
*/
Handle<Value> Check::Count0103(const Arguments& args)
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
        if(temp == ';' || ch == length - 1){
            if(ch == length -1 && temp != ';')
            len ++;
            IntArray *heNumber = new IntArray(27, temChar, len, ',');
            int sum = self->pDrawNum->getSum();
            int hitCount = 0;
            for(int i = 0 ; i < heNumber->length(); i++){
                if (heNumber->get(i) == sum){
                    hitCount ++;
                    break;
                }
            }
            if(hitCount == 1){
                self->gl->appendBonusObj(array, 1, 1);
            }
            delete heNumber;
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



/***
组合复式
*/
Handle<Value> Check::Count0104(const Arguments& args)
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
        if(temp == ';' || ch == length - 1){
            if(ch == length -1 && temp != ';')
             len ++;
            IntArray *heNumber = new IntArray(10, temChar, len, ',');
            IntArray *prizeNumber = self->pDrawNum->getPNum();
            int hitCount = MathUtil::getHitCount(heNumber, prizeNumber);
            if(hitCount == 3){
                self->gl->appendBonusObj(array, 1, 1);
            }

            delete heNumber;
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


/***
组合胆拖
*/
Handle<Value> Check::Count0105(const Arguments& args)
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
    //首先判断胆码是否中奖，如果中奖继续，否则不中奖
    IntArray *prizeNumber = self->pDrawNum->getPNum();
    bool flag = false;
    int tuoStart = 0;
    for(int at = 0; at < length; at++){
        if(pChar[at] == '$' ){
           temChar = pChar + at + 1;
           tuoStart = at + 1;

           IntArray *danNumber = new IntArray(2, temChar, at, ',');
           int hitCount = MathUtil::getHitCount(danNumber, prizeNumber);
           if(hitCount == 1){
                flag = true;
           }
           break;
        }
    }
    if(flag)
    for (int ch = tuoStart ; ch < length ; ch ++){
        char temp = pChar[ch];
        if(temp == ';' || ch == length - 1){
            if(ch == length -1 && temp != ';')
            len ++;
            IntArray *tuoNumber = new IntArray(10, temChar, len, ',');
            //判断拖码是否中奖， 如果拖码中奖则中奖
            int hitCount = MathUtil::getHitCount(tuoNumber, prizeNumber);
            if(hitCount == 2){
                self->gl->appendBonusObj(array, 1, 1);
            }
            delete tuoNumber;
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

/***
跨度复式
*/
Handle<Value> Check::Count0106(const Arguments& args)
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
        if(temp == ';' || ch == length - 1){
             if(ch == length -1 && temp != ';')
             len ++;
            IntArray *spanNumber = new IntArray(10, temChar, len, ',');
            int hitCount = 0;
            int span = self->pDrawNum->getSpan();
            for(int i = 0 ; i < spanNumber->length(); i++){
                if(span == spanNumber->get(i)){
                    hitCount ++;
                    break;
                }
            }

            if(hitCount == 1){
                self->gl->appendBonusObj(array, 1, 1);
            }

            delete spanNumber;
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
 * 组三复式
 */
Handle<Value> Check::Count0201(const Arguments& args)
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
             if(ch == length -1 && temp != ';')
             len ++;
             if(self->pDrawNum->type == NUM_TYPE_Z3 ){
                   IntArray *itemNumber =new IntArray(10, temChar, len, ',');
                   int hitCount = MathUtil::getHitCount(itemNumber, self->pDrawNum->getPNum());
                   if(hitCount >= 3 ){
                       self->gl->appendBonusObj(array, 2, 1);
                   }
                   delete itemNumber;
             }

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
 * 组三胆拖
 */
Handle<Value> Check::Count0202(const Arguments& args)
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

    if(self->pDrawNum->type == NUM_TYPE_Z3){
        int len = 0 ;
        char *lotNumChar = pChar;
        IntArray *danArray = 0;
        for(int ch = 0; ch < length ; ch++ ){
            char temp = pChar[ch];
            if(temp == '$' ){
                danArray =  new IntArray(2, lotNumChar, len, ',');
                if(ch < length - 1){
                   lotNumChar = pChar + ch + 1;
                }
                break;
            }
            len ++;
        }

        int hitCount = MathUtil::getHitCount(danArray, self->pDrawNum->getPNum());
        if(hitCount > 0){
            IntArray *tuoArray = new IntArray(10, lotNumChar, length - len -1, ',');
            int hitTuoCount = MathUtil::getHitCount(tuoArray, self->pDrawNum->getPNum());
            if(hitTuoCount > 0){
                    self->gl->appendBonusObj(array, 2, 1);
            }
            delete tuoArray;
        }
         delete danArray;
    }
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/* 组三跨度*/
Handle<Value> Check::Count0206(const Arguments& args)
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
        if(temp == ';' || ch == length - 1){
            if(ch == length -1 && temp != ';')
            len ++;
            IntArray *spanNumber = new IntArray(10, temChar, len, ',');
            int hitCount = 0;
            int span = self->pDrawNum->getSpan();
            if(self->pDrawNum->type == NUM_TYPE_Z3){
                for(int i = 0 ; i < spanNumber->length(); i++){
                    if(span == spanNumber->get(i)){
                        hitCount ++;
                        break;
                    }
                }
                if(hitCount == 1){
                    self->gl->appendBonusObj(array, 2, 1);
                }
            }
            delete spanNumber;
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
 * 组六复式
 */
Handle<Value> Check::Count0301(const Arguments& args)
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
              if(ch == length -1 && temp != ';')
              len ++;
             if(self->pDrawNum->type == NUM_TYPE_Z6 ){
                 IntArray *itemNumber =new IntArray(10, temChar, len, ',');
                 int hitCount = MathUtil::getHitCount(itemNumber, self->pDrawNum->getPNum());
                 if(hitCount >= 3 ){
                     self->gl->appendBonusObj(array, 3, 1);
                 }
                 delete itemNumber;
             }
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
 * 组六胆拖
 */
Handle<Value> Check::Count0302(const Arguments& args)
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

    if(self->pDrawNum->type == NUM_TYPE_Z6){
        int len = 0 ;
        char *lotNumChar = pChar;
        IntArray *danArray = 0;
        for(int ch = 0; ch < length ; ch++ ){
            char temp = pChar[ch];
            if(temp == '$' ){
                danArray =  new IntArray(2, lotNumChar, len, ',');
                if(ch < length - 1){
                   lotNumChar = pChar + ch + 1;
                }
                break;
            }
            len ++;
        }
        int hitCount = MathUtil::getHitCount(danArray, self->pDrawNum->getPNum());
        if(hitCount == danArray->length()){
            IntArray *tuoArray = new IntArray(10, lotNumChar, length - len -1, ',');
            int hitTuoCount = MathUtil::getHitCount(tuoArray, self->pDrawNum->getPNum());
            if(hitTuoCount == 3 - hitCount){
                 self->gl->appendBonusObj(array, 3, 1);
            }
            delete tuoArray;
        }
        delete danArray;
    }
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/* 组三跨度*/
Handle<Value> Check::Count0306(const Arguments& args)
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
        if(temp == ';' || ch == length - 1){
            if(ch == length -1 && temp != ';')
            len ++;
            IntArray *spanNumber = new IntArray(10, temChar, len, ',');
            int hitCount = 0;
            int span = self->pDrawNum->getSpan();
            if(self->pDrawNum->type == NUM_TYPE_Z6){
                for(int i = 0 ; i < spanNumber->length(); i++){
                    if(span == spanNumber->get(i)){
                        hitCount ++;
                        break;
                    }
                }
                if(hitCount >= 1){
                    self->gl->appendBonusObj(array, 3, 1);
                }
            }
            delete spanNumber;
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
 * 组选单式 排列三
 */
Handle<Value> Check::Count0400(const Arguments& args)
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
             if(ch == length -1 && temp != ';')
             len ++;
             IntArray  *itemNumber =new IntArray(3, temChar, len, ',');
             int hitCount = MathUtil::getHitCount(self->pDrawNum->getPNum(), itemNumber);
             if(hitCount == 3){
                if(self->pDrawNum->type == NUM_TYPE_Z3){
                    self->gl->appendBonusObj(array, 2, 1);
                }else if (self->pDrawNum->type == NUM_TYPE_Z6){
                    self->gl->appendBonusObj(array, 3, 1);
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

/***组选和值*/
Handle<Value> Check::Count0403(const Arguments& args)
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
        if(temp == ';' || ch == length - 1){
             if(ch == length -1 && temp != ';')
             len ++;
            IntArray *heNumber = new IntArray(27, temChar, len, ',');
            int sum = self->pDrawNum->getSum();
            for(int i = 0 ; i < heNumber->length(); i++){
                if (heNumber->get(i) == sum){
                    if(self->pDrawNum->type == NUM_TYPE_Z3){
                        self->gl->appendBonusObj(array, 2, 1);
                    }else if (self->pDrawNum->type == NUM_TYPE_Z6){
                        self->gl->appendBonusObj(array, 3, 1);
                    }
                }
            }
            delete heNumber;
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