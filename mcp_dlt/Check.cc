#include <node.h>

#include "Check.h"
#include "MathUtil.h"

using namespace v8;

Persistent<Function> Check::constructor;

Check::Check()
{
    this->gl = NULL;
    this->pDrawNum = NULL;
    //二维数组，第二维的三个数是中奖条件及对应的奖级
    this->bonusRule[0][0] = 5;
    this->bonusRule[0][1] = 2;
    this->bonusRule[0][2] = 1;
    this->bonusRule[1][0] = 5;
    this->bonusRule[1][1] = 1;
    this->bonusRule[1][2] = 2;
    this->bonusRule[2][0] = 5;
    this->bonusRule[2][1] = 0;
    this->bonusRule[2][2] = 3;
    this->bonusRule[3][0] = 4;
    this->bonusRule[3][1] = 2;
    this->bonusRule[3][2] = 3;
    this->bonusRule[4][0] = 4;
    this->bonusRule[4][1] = 1;
    this->bonusRule[4][2] = 4;
    this->bonusRule[5][0] = 4;
    this->bonusRule[5][1] = 0;
    this->bonusRule[5][2] = 5;
    this->bonusRule[6][0] = 3;
    this->bonusRule[6][1] = 2;
    this->bonusRule[6][2] = 4;
    this->bonusRule[7][0] = 3;
    this->bonusRule[7][1] = 1;
    this->bonusRule[7][2] = 5;
    this->bonusRule[8][0] = 3;
    this->bonusRule[8][1] = 0;
    this->bonusRule[8][2] = 6;
    this->bonusRule[9][0] = 2;
    this->bonusRule[9][1] = 2;
    this->bonusRule[9][2] = 5;
    this->bonusRule[10][0] = 1;
    this->bonusRule[10][1] = 2;
    this->bonusRule[10][2] = 6;
    this->bonusRule[11][0] = 0;
    this->bonusRule[11][1] = 2;
    this->bonusRule[11][2] = 6;
    this->bonusRule[12][0] = 2;
    this->bonusRule[12][1] = 1;
    this->bonusRule[12][2] = 6;
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
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0002"), FunctionTemplate::New(Count0002)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0500"), FunctionTemplate::New(Count0500)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0501"), FunctionTemplate::New(Count0501)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0502"), FunctionTemplate::New(Count0502)->GetFunction());
    constructor = Persistent<Function>::New(tpl->GetFunction());
}

/**
 * 真正初始化的方法
 */
Handle<Value> Check::New(const Arguments& args)
{
    HandleScope scope;
    if(args.IsConstructCall()){ //from new Object()
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
 * 大了透单式算计
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
    char *pChar = new char[length + 1];
    pNum->WriteUtf8(pChar);
    *(pChar + length) = '\0';

    int len = 0 ; //每个单式的长度
    char *lotNumChar = pChar;
    for(int ch = 0; ch < length ; ch++ ){
        char temp = pChar[ch]; //copy 值
        if(temp == ';' || ch == length -1 ){ //单式结束或者真正结束了
            if(ch == length -1 && temp != ';')
            len ++;
            DrawNum *num = new DrawNum(lotNumChar, len );

            int hitRedCount = MathUtil::getHitCount(num->getPreArray(), self->pDrawNum->getPreArray());
            int hitBlueCount = MathUtil::getHitCount(num->getAfterArray(), self->pDrawNum->getAfterArray());

            for(int i = 0; i < 13 ;i++ ){
                int *temp = (int *)self->bonusRule[i];
                if(hitRedCount == temp[0] && hitBlueCount == temp[1]){
                   self->gl->appendBonusObj(array, temp[2], 1);
                }
            }
            delete num;
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
 * 大了透复式
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
    char *pChar = new char[length + 1];
    pNum->WriteUtf8(pChar);
    *(pChar + length) = '\0';

    //要算将的num
    DrawNum *num = new DrawNum(pChar, length);

    int hitRedCount = MathUtil::getHitCount(num->getPreArray(), self->pDrawNum->getPreArray());
    int hitBlueCount = MathUtil::getHitCount(num->getAfterArray(), self->pDrawNum->getAfterArray());
    int notHitRed = num->getPreArray()->length() - hitRedCount;
    int notHitBlue = num->getAfterArray()->length() - hitBlueCount;
    for(int i = 13 - 1; i >= 0; i--)
    {
        int *temp = (int *)self->bonusRule[i];
        int redCount = MathUtil::GetC(hitRedCount, temp[0])*MathUtil::GetC(notHitRed, 5 - temp[0]);
        int blueCount = MathUtil::GetC(hitBlueCount, temp[1])*MathUtil::GetC(notHitBlue, 2 - temp[1]);
        int hitCount = redCount * blueCount;
        if(hitCount > 0 )
        {
           self->gl->appendBonusObj(array, temp[2], hitCount);
        }
    }
    delete num;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}


/**
 * 大乐透胆拖 计算
 */
Handle<Value> Check::Count0002(const Arguments& args)
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

    DanTuoNum* danNum = new DanTuoNum(pChar, length);
    IntArray* redDanArray = danNum->getPreDanArray();
    IntArray* redTuoArray = danNum->getPreTuoArray();
    IntArray* blueDanArray = danNum->getAfterDanArray();
    IntArray* blueTuoArray = danNum->getAfterTuoArray();

    int redDanHit = MathUtil::getHitCount(self->pDrawNum->getPreArray(), redDanArray);
    int redTuoHit = MathUtil::getHitCount(self->pDrawNum->getPreArray(), redTuoArray);
    int blueDanHit = MathUtil::getHitCount(self->pDrawNum->getAfterArray(), blueDanArray);
    int blueTuoHit = MathUtil::getHitCount(self->pDrawNum->getAfterArray(), blueTuoArray);

    /*blueDanArray->traverse();
    blueTuoArray->traverse();
    printf("redDanHit:%d,redTuoHit:%d,blueDanHit:%d,blueTuoHit:%d\n", redDanHit, redTuoHit, blueDanHit, blueTuoHit);*/

    for(int i = 13 - 1; i >= 0; i--)
    {
        int *temp = (int *)self->bonusRule[i];
        int redCount = MathUtil::GetC(redTuoHit, temp[0] - redDanHit )*MathUtil::GetC(redTuoArray->length() - redTuoHit , 5 - (temp[0] - redDanHit) - redDanArray->length());
        int blueCount = MathUtil::GetC(blueTuoHit, temp[1] - blueDanHit)*MathUtil::GetC(blueTuoArray->length() - blueTuoHit, 2 - (temp[1] - blueDanHit) - blueDanArray->length());
        int hitCount = redCount*blueCount;
        if(hitCount > 0)
        {
           self->gl->appendBonusObj(array, temp[2], hitCount);
        }
    }
    delete danNum;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}


/**
 * 大了透单式算计
 */
Handle<Value> Check::Count0500(const Arguments& args)
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
            if( ch == length -1 &&  temp != ';')
            len ++;
            //要算将的num
            DrawNum *num = new DrawNum(lotNumChar, len );

            int hitRedCount = MathUtil::getHitCount(num->getPreArray(), self->pDrawNum->getPreArray());
            int hitBlueCount = MathUtil::getHitCount(num->getAfterArray(), self->pDrawNum->getAfterArray());

            for(int i = 0; i < 13 ;i++ ){
                int *temp = (int *)self->bonusRule[i];
                if(hitRedCount == temp[0] && hitBlueCount == temp[1]){
                   self->gl->appendBonusObj(array, temp[2], 1);
                   if(temp[2] != 6){
                    self->gl->appendBonusObj(array, temp[2] + 6 , 1);
                   }
                }
            }
            delete num;

            if(ch < length - 1){
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
 * 大了透复式算计
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

    //要算将的num
    DrawNum *num = new DrawNum(pChar, length);

    int hitRedCount = MathUtil::getHitCount(num->getPreArray(), self->pDrawNum->getPreArray());
    int hitBlueCount = MathUtil::getHitCount(num->getAfterArray(), self->pDrawNum->getAfterArray());
    int notHitRed = num->getPreArray()->length() - hitRedCount;
    int notHitBlue = num->getAfterArray()->length() - hitBlueCount;
    for(int i = 13-1; i >= 0 ;i-- ){
        int *temp = self->bonusRule[i];
        int redCount = MathUtil::GetC(hitRedCount, temp[0])*MathUtil::GetC(notHitRed, 5 - temp[0]);
        int blueCount = MathUtil::GetC(hitBlueCount, temp[1])*MathUtil::GetC(notHitBlue, 2 - temp[1]);
        int hitCount = redCount * blueCount;
        if(hitCount > 0 ){
           self->gl->appendBonusObj(array, temp[2], hitCount);
           if(temp[2] != 6){
              self->gl->appendBonusObj(array, temp[2] + 6 , hitCount);
           }
        }
    }
    delete num;
    delete[] pChar;

    return scope.Close(self->gl->getRst(array));
}


/**
 * 大乐透胆拖 计算
 */
Handle<Value> Check::Count0502(const Arguments& args)
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

    DanTuoNum* danNum = new DanTuoNum(pChar, length);
    IntArray* redDanArray = danNum->getPreDanArray();
    IntArray* redTuoArray = danNum->getPreTuoArray();
    IntArray* blueDanArray = danNum->getAfterDanArray();
    IntArray* blueTuoArray = danNum->getAfterTuoArray();

    int redDanHit = MathUtil::getHitCount(self->pDrawNum->getPreArray(), redDanArray);
    int redTuoHit = MathUtil::getHitCount(self->pDrawNum->getPreArray(), redTuoArray);
    int blueDanHit = MathUtil::getHitCount(self->pDrawNum->getAfterArray(), blueDanArray);
    int blueTuoHit = MathUtil::getHitCount(self->pDrawNum->getAfterArray(), blueTuoArray);

    /*blueDanArray->traverse();
    blueTuoArray->traverse();
    printf("redDanHit:%d,redTuoHit:%d,blueDanHit:%d,blueTuoHit:%d\n", redDanHit, redTuoHit, blueDanHit, blueTuoHit);*/

    for(int i = 13 - 1; i >= 0; i--)
    {
        int *temp = (int *)self->bonusRule[i];
        int redCount = MathUtil::GetC(redTuoHit, temp[0] - redDanHit )*MathUtil::GetC(redTuoArray->length() - redTuoHit , 5 - (temp[0] - redDanHit) - redDanArray->length());
        int blueCount = MathUtil::GetC(blueTuoHit, temp[1] - blueDanHit)*MathUtil::GetC(blueTuoArray->length() - blueTuoHit, 2 - (temp[1] - blueDanHit) - blueDanArray->length());
        int hitCount = redCount*blueCount;
        if(hitCount > 0)
        {
           self->gl->appendBonusObj(array, temp[2], hitCount);
           if(temp[2] != 6)
           {
               self->gl->appendBonusObj(array, temp[2] + 6 , hitCount);
           }
        }
    }
    delete danNum;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}
