#include <node.h>
#include "Check.h"

using namespace v8;

Persistent<Function> Check::constructor;

Check::Check()
{
    this->gl = NULL;
    this->pDrawNumType = NULL;
    this->pDrawNum = NULL;
}

Check::~Check()
{
    if(this->pDrawNumType != NULL)
    {
        delete this->pDrawNumType;
    }
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
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count"), FunctionTemplate::New(Count)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0000"), FunctionTemplate::New(Count0000)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0100"), FunctionTemplate::New(Count0100)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0101"), FunctionTemplate::New(Count0101)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0102"), FunctionTemplate::New(Count0102)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0200"), FunctionTemplate::New(Count0200)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0201"), FunctionTemplate::New(Count0201)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0202"), FunctionTemplate::New(Count0202)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0208"), FunctionTemplate::New(Count0208)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0300"), FunctionTemplate::New(Count0300)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0301"), FunctionTemplate::New(Count0301)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0302"), FunctionTemplate::New(Count0302)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0400"), FunctionTemplate::New(Count0400)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0401"), FunctionTemplate::New(Count0401)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0402"), FunctionTemplate::New(Count0402)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0408"), FunctionTemplate::New(Count0408)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0500"), FunctionTemplate::New(Count0500)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0501"), FunctionTemplate::New(Count0501)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0600"), FunctionTemplate::New(Count0600)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0601"), FunctionTemplate::New(Count0601)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0603"), FunctionTemplate::New(Count0603)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0606"), FunctionTemplate::New(Count0606)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0609"), FunctionTemplate::New(Count0609)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0700"), FunctionTemplate::New(Count0700)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0701"), FunctionTemplate::New(Count0701)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0709"), FunctionTemplate::New(Count0709)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0800"), FunctionTemplate::New(Count0800)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0801"), FunctionTemplate::New(Count0801)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0900"), FunctionTemplate::New(Count0900)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0901"), FunctionTemplate::New(Count0901)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count0902"), FunctionTemplate::New(Count0902)->GetFunction());
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
    obj->pDrawNumType = new NumType(pChar, length);
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
 * 根据任选的数目获得对应的奖级
 */
int Check::getGlByReCount(int reCount)
{
    int level = -1;
    if(reCount == 1)
    {
        level = 5;
    }
    else if(reCount == 2)
    {
        level = 6;
    }
    else if(reCount == 3)
    {
        level = 7;
    }
    else if(reCount == 4)
    {
        level = 8;
    }
    return level;
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
 * 组选，单式
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

            NumType *pNumType = new NumType(tmp, jCount);
            if(self->pDrawNumType->getType() == pNumType->getType())    //和开奖号码组选类型相同
            {
                bool hit = true;
                int drawLen = self->pDrawNumType->getCharLen();
                for(int i = 0; i < drawLen; i++)
                {
                    char c = self->pDrawNumType->getCharAt(i);
                    int iCount = self->pDrawNumType->getCharCountAt(i);
                    if(pNumType->getCharCount(c) != iCount)
                    {
                        hit = false;
                        break;
                    }
                }
                if(hit)
                {
                    int level = -1;
                    if(self->pDrawNumType->getType() == NUM_TYPE_Z24)
                    {
                        level = 1;
                    }
                    else if(self->pDrawNumType->getType() == NUM_TYPE_Z12)
                    {
                        level = 2;
                    }
                    else if(self->pDrawNumType->getType() == NUM_TYPE_Z6)
                    {
                        level = 3;
                    }
                    else if(self->pDrawNumType->getType() == NUM_TYPE_Z4)
                    {
                        level = 4;
                    }
                    self->gl->appendBonusObj(array, level, 1);
                }
            }

            jCount = 0; //号码长度重新计算
            delete pNumType;
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
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/**
 * 组24，单式算计
 */
Handle<Value> Check::Count0100(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    //号码类型是否相同
    if(self->pDrawNumType->getType() == NUM_TYPE_Z24)
    {
        //获得号码的字符串
        Local<Object> pObj = Local<Object>::Cast(args[0]);
        Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
        int length = pNum->Utf8Length();
        char *pChar = new char[length + 1];
        pNum->WriteUtf8(pChar);
        *(pChar + length) = '\0';

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
                NumType *pNumType = new NumType(tmp, jCount);
                bool hit = true;
                int drawLen = self->pDrawNumType->getCharLen();
                for(int i = 0; i < drawLen; i++)
                {
                    char c = self->pDrawNumType->getCharAt(i);
                    int iCount = self->pDrawNumType->getCharCountAt(i);
                    if(pNumType->getCharCount(c) != iCount)
                    {
                        hit = false;
                        break;
                    }
                }
                if(hit)
                {
                    self->gl->appendBonusObj(array, 1, 1);
                }
                jCount = 0; //号码长度重新计算
                delete pNumType;
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
        delete[] pChar;
    }
    return scope.Close(self->gl->getRst(array));
}

/**
 * 组24，复式算奖
 */
Handle<Value> Check::Count0101(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    //号码类型是否相同
    if(self->pDrawNumType->getType() == NUM_TYPE_Z24)
    {
        //获得号码的字符串
        Local<Object> pObj = Local<Object>::Cast(args[0]);
        Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
        int length = pNum->Utf8Length();
        char *pChar = new char[length + 1];
        pNum->WriteUtf8(pChar);
        *(pChar + length) = '\0';

        NumType *pNumType = new NumType(pChar, length);

        bool hit = true;    //是否中奖
        int drawLen = self->pDrawNumType->getCharLen();
        for(int i = 0; i < drawLen; i++)
        {
            char c = self->pDrawNumType->getCharAt(i);
            int iCount = self->pDrawNumType->getCharCountAt(i);
            if(pNumType->getCharCount(c) != iCount)
            {
                hit = false;
                break;
            }
        }
        if(hit)
        {
            self->gl->appendBonusObj(array, 1, 1);
        }
        delete pNumType;
        delete[] pChar;
    }
    return scope.Close(self->gl->getRst(array));
}

/**
 * 组24，胆拖算奖
 */
Handle<Value> Check::Count0102(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    //号码类型是否相同
    if(self->pDrawNumType->getType() == NUM_TYPE_Z24)
    {
        //获得号码的字符串
        Local<Object> pObj = Local<Object>::Cast(args[0]);
        Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
        int length = pNum->Utf8Length();
        char *pChar = new char[length + 1];
        pNum->WriteUtf8(pChar);
        *(pChar + length) = '\0';

        NumType *pDan, *pTuo;
        int pos = 0;
        for(int i = 0; i < length; i++)
        {
            char c = pChar[i];
            if(c == '$')
            {
                pos = i;
                break;
            }
        }
        char *pCharTuo = pChar + pos + 1;
        pDan = new NumType(pChar, pos);     //胆码
        pTuo = new NumType(pCharTuo, length - pos - 1); //拖码

        bool hit = true;    //是否中奖
        int danLen = pDan->getCharLen();
        for(int i = 0; i < danLen; i++)
        {
            char c = pDan->getCharAt(i);
            int iCount = self->pDrawNumType->getCharCount(c);
            if(iCount < 1)
            {
                hit = false;
                break;
            }
        }

        if(hit)
        {
            int tuoHitCount = 0;
            int tuoLen = pTuo->getCharLen();
            for(int i = 0; i < tuoLen; i++)
            {
                char c = pTuo->getCharAt(i);
                int iCount = self->pDrawNumType->getCharCount(c);
                if(iCount >= 1)
                {
                    tuoHitCount++;
                }
            }
            if(tuoHitCount + danLen < 4)    //总hit数必须大于等于4
            {
                hit = false;
            }
        }

        if(hit)
        {
            self->gl->appendBonusObj(array, 1, 1);
        }

        delete pDan;
        delete pTuo;
        delete[] pChar;
    }
    return scope.Close(self->gl->getRst(array));
}

/**
 * 组12，单式算奖
 */
Handle<Value> Check::Count0200(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    //号码类型是否相同
    if(self->pDrawNumType->getType() == NUM_TYPE_Z12)
    {
        //获得号码的字符串
        Local<Object> pObj = Local<Object>::Cast(args[0]);
        Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
        int length = pNum->Utf8Length();
        char *pChar = new char[length + 1];
        pNum->WriteUtf8(pChar);
        *(pChar + length) = '\0';

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
                NumType *pNumType = new NumType(tmp, jCount);
                bool hit = true;
                int drawLen = self->pDrawNumType->getCharLen();
                for(int i = 0; i < drawLen; i++)
                {
                    char c = self->pDrawNumType->getCharAt(i);
                    int iCount = self->pDrawNumType->getCharCountAt(i);
                    if(pNumType->getCharCount(c) != iCount)
                    {
                        hit = false;
                        break;
                    }
                }
                if(hit)
                {
                    self->gl->appendBonusObj(array, 2, 1);
                }
                jCount = 0; //号码长度重新计算
                delete pNumType;
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
        delete[] pChar;
    }
    return scope.Close(self->gl->getRst(array));
}

/**
 * 组12，复式算奖
 */
Handle<Value> Check::Count0201(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    //号码类型是否相同
    if(self->pDrawNumType->getType() == NUM_TYPE_Z12)
    {
        //获得号码的字符串
        Local<Object> pObj = Local<Object>::Cast(args[0]);
        Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
        int length = pNum->Utf8Length();
        char *pChar = new char[length + 1];
        pNum->WriteUtf8(pChar);
        *(pChar + length) = '\0';

        NumType *pNumType = new NumType(pChar, length);

        bool hit = true;    //是否中奖
        int drawLen = self->pDrawNumType->getCharLen();
        for(int i = 0; i < drawLen; i++)
        {
            char c = self->pDrawNumType->getCharAt(i);
            //int iCount = self->pDrawNumType->getCharCountAt(i);
            if(pNumType->getCharCount(c) < 1)
            {
                hit = false;
                break;
            }
        }
        //printf("hitCount:%d\n", hit);
        if(hit)
        {
            self->gl->appendBonusObj(array, 2, 1);
        }
        delete pNumType;
        delete[] pChar;
    }
    return scope.Close(self->gl->getRst(array));
}

/**
 * 组12，胆拖算奖
 */
Handle<Value> Check::Count0202(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    //号码类型是否相同
    if(self->pDrawNumType->getType() == NUM_TYPE_Z12)
    {
        //获得号码的字符串
        Local<Object> pObj = Local<Object>::Cast(args[0]);
        Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
        int length = pNum->Utf8Length();
        char *pChar = new char[length + 1];
        pNum->WriteUtf8(pChar);
        *(pChar + length) = '\0';

        NumType *pDan, *pTuo;
        int pos = 0;
        for(int i = 0; i < length; i++)
        {
            char c = pChar[i];
            if(c == '$')
            {
                pos = i;
                break;
            }
        }
        char *pCharTuo = pChar + pos + 1;
        pDan = new NumType(pChar, pos);     //胆码
        pTuo = new NumType(pCharTuo, length - pos - 1); //拖码

        bool hit = true;    //是否中奖
        int danLen = pDan->getCharLen();
        for(int i = 0; i < danLen; i++)
        {
            char c = pDan->getCharAt(i);
            int iCount = self->pDrawNumType->getCharCount(c);
            if(iCount < 1)
            {
                hit = false;
                break;
            }
        }

        if(hit)
        {
            int tuoHitCount = 0;
            int tuoLen = pTuo->getCharLen();
            for(int i = 0; i < tuoLen; i++)
            {
                char c = pTuo->getCharAt(i);
                int iCount = self->pDrawNumType->getCharCount(c);
                if(iCount >= 1)
                {
                    tuoHitCount++;
                }
            }
            if(tuoHitCount + danLen < 3)    //总hit数必须大于等于3
            {
                hit = false;
            }
        }

        if(hit)
        {
            self->gl->appendBonusObj(array, 2, 1);
        }

        delete pDan;
        delete pTuo;
        delete[] pChar;
    }
    return scope.Close(self->gl->getRst(array));
}

/**
 * 组12，重胆拖算奖
 */
Handle<Value> Check::Count0208(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    //号码类型是否相同
    if(self->pDrawNumType->getType() == NUM_TYPE_Z12)
    {
        //获得号码的字符串
        Local<Object> pObj = Local<Object>::Cast(args[0]);
        Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
        int length = pNum->Utf8Length();
        char *pChar = new char[length + 1];
        pNum->WriteUtf8(pChar);
        *(pChar + length) = '\0';

        NumType *pDan, *pTuo;
        int pos = 0;
        for(int i = 0; i < length; i++)
        {
            char c = pChar[i];
            if(c == '$')
            {
                pos = i;
                break;
            }
        }
        char *pCharTuo = pChar + pos + 1;
        pDan = new NumType(pChar, pos);     //胆码
        pTuo = new NumType(pCharTuo, length - pos - 1); //拖码

        bool hit = true;    //是否中奖
        int danLen = pDan->getCharLen();
        for(int i = 0; i < danLen; i++)
        {
            char c = pDan->getCharAt(i);
            int iCount = self->pDrawNumType->getCharCount(c);
            if(iCount < 2)  //重胆拖的胆码必须是对子号
            {
                hit = false;
                break;
            }
        }

        if(hit)
        {
            int tuoHitCount = 0;
            int tuoLen = pTuo->getCharLen();
            for(int i = 0; i < tuoLen; i++)
            {
                char c = pTuo->getCharAt(i);
                int iCount = self->pDrawNumType->getCharCount(c);
                if(iCount >= 1)
                {
                    tuoHitCount++;
                }
            }
            if(tuoHitCount + danLen < 3)    //总hit数必须大于等于3
            {
                hit = false;
            }
        }

        if(hit)
        {
            self->gl->appendBonusObj(array, 2, 1);
        }

        delete pDan;
        delete pTuo;
        delete[] pChar;
    }
    return scope.Close(self->gl->getRst(array));
}

/**
 * 组6，单式算奖
 */
Handle<Value> Check::Count0300(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    //号码类型是否相同
    if(self->pDrawNumType->getType() == NUM_TYPE_Z6)
    {
        //获得号码的字符串
        Local<Object> pObj = Local<Object>::Cast(args[0]);
        Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
        int length = pNum->Utf8Length();
        char *pChar = new char[length + 1];
        pNum->WriteUtf8(pChar);
        *(pChar + length) = '\0';

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
                NumType *pNumType = new NumType(tmp, jCount);
                bool hit = true;
                int drawLen = self->pDrawNumType->getCharLen();
                for(int i = 0; i < drawLen; i++)
                {
                    char c = self->pDrawNumType->getCharAt(i);
                    int iCount = self->pDrawNumType->getCharCountAt(i);
                    if(pNumType->getCharCount(c) != iCount)
                    {
                        hit = false;
                        break;
                    }
                }
                if(hit)
                {
                    self->gl->appendBonusObj(array, 3, 1);
                }
                jCount = 0; //号码长度重新计算
                delete pNumType;
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
        delete[] pChar;
    }
    return scope.Close(self->gl->getRst(array));
}

/**
 * 组6，复式算奖
 */
Handle<Value> Check::Count0301(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    //号码类型是否相同
    if(self->pDrawNumType->getType() == NUM_TYPE_Z6)
    {
        //获得号码的字符串
        Local<Object> pObj = Local<Object>::Cast(args[0]);
        Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
        int length = pNum->Utf8Length();
        char *pChar = new char[length + 1];
        pNum->WriteUtf8(pChar);
        *(pChar + length) = '\0';

        NumType *pNumType = new NumType(pChar, length);

        bool hit = true;    //是否中奖
        int drawLen = self->pDrawNumType->getCharLen();
        for(int i = 0; i < drawLen; i++)
        {
            char c = self->pDrawNumType->getCharAt(i);
            //int iCount = self->pDrawNumType->getCharCountAt(i);
            if(pNumType->getCharCount(c) < 1)
            {
                hit = false;
                break;
            }
        }
        //printf("hitCount:%d\n", hit);
        if(hit)
        {
            self->gl->appendBonusObj(array, 3, 1);
        }
        delete pNumType;
        delete[] pChar;
    }
    return scope.Close(self->gl->getRst(array));
}

/**
 * 组6，胆拖算奖
 */
Handle<Value> Check::Count0302(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    //号码类型是否相同
    if(self->pDrawNumType->getType() == NUM_TYPE_Z6)
    {
        //获得号码的字符串
        Local<Object> pObj = Local<Object>::Cast(args[0]);
        Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
        int length = pNum->Utf8Length();
        char *pChar = new char[length + 1];
        pNum->WriteUtf8(pChar);
        *(pChar + length) = '\0';

        NumType *pDan, *pTuo;
        int pos = 0;
        for(int i = 0; i < length; i++)
        {
            char c = pChar[i];
            if(c == '$')
            {
                pos = i;
                break;
            }
        }
        char *pCharTuo = pChar + pos + 1;
        pDan = new NumType(pChar, pos);     //胆码
        pTuo = new NumType(pCharTuo, length - pos - 1); //拖码

        bool hit = true;    //是否中奖
        int danLen = pDan->getCharLen();
        for(int i = 0; i < danLen; i++)
        {
            char c = pDan->getCharAt(i);
            int iCount = self->pDrawNumType->getCharCount(c);
            if(iCount < 1)
            {
                hit = false;
                break;
            }
        }

        if(hit)
        {
            int tuoHitCount = 0;
            int tuoLen = pTuo->getCharLen();
            for(int i = 0; i < tuoLen; i++)
            {
                char c = pTuo->getCharAt(i);
                int iCount = self->pDrawNumType->getCharCount(c);
                if(iCount >= 1)
                {
                    tuoHitCount++;
                }
            }
            if(tuoHitCount + danLen < 2)    //总hit数必须大于等于3
            {
                hit = false;
            }
        }

        if(hit)
        {
            self->gl->appendBonusObj(array, 3, 1);
        }

        delete pDan;
        delete pTuo;
        delete[] pChar;
    }
    return scope.Close(self->gl->getRst(array));
}

/**
 * 组4，单式算奖
 */
Handle<Value> Check::Count0400(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    //号码类型是否相同
    if(self->pDrawNumType->getType() == NUM_TYPE_Z4)
    {
        //获得号码的字符串
        Local<Object> pObj = Local<Object>::Cast(args[0]);
        Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
        int length = pNum->Utf8Length();
        char *pChar = new char[length + 1];
        pNum->WriteUtf8(pChar);
        *(pChar + length) = '\0';

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
                NumType *pNumType = new NumType(tmp, jCount);
                bool hit = true;
                int drawLen = self->pDrawNumType->getCharLen();
                for(int i = 0; i < drawLen; i++)
                {
                    char c = self->pDrawNumType->getCharAt(i);
                    int iCount = self->pDrawNumType->getCharCountAt(i);
                    if(pNumType->getCharCount(c) != iCount)
                    {
                        hit = false;
                        break;
                    }
                }
                if(hit)
                {
                    self->gl->appendBonusObj(array, 4, 1);
                }
                jCount = 0; //号码长度重新计算
                delete pNumType;
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
        delete[] pChar;
    }
    return scope.Close(self->gl->getRst(array));
}

/**
 * 组4，复式算奖
 */
Handle<Value> Check::Count0401(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    //号码类型是否相同
    if(self->pDrawNumType->getType() == NUM_TYPE_Z4)
    {
        //获得号码的字符串
        Local<Object> pObj = Local<Object>::Cast(args[0]);
        Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
        int length = pNum->Utf8Length();
        char *pChar = new char[length + 1];
        pNum->WriteUtf8(pChar);
        *(pChar + length) = '\0';

        NumType *pNumType = new NumType(pChar, length);

        bool hit = true;    //是否中奖
        int drawLen = self->pDrawNumType->getCharLen();
        for(int i = 0; i < drawLen; i++)
        {
            char c = self->pDrawNumType->getCharAt(i);
            //int iCount = self->pDrawNumType->getCharCountAt(i);
            if(pNumType->getCharCount(c) < 1)
            {
                hit = false;
                break;
            }
        }
        //printf("hitCount:%d\n", hit);
        if(hit)
        {
            self->gl->appendBonusObj(array, 4, 1);
        }
        delete pNumType;
        delete[] pChar;
    }
    return scope.Close(self->gl->getRst(array));
}

/**
 * 组4，胆拖算奖
 */
Handle<Value> Check::Count0402(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    //号码类型是否相同
    if(self->pDrawNumType->getType() == NUM_TYPE_Z4)
    {
        //获得号码的字符串
        Local<Object> pObj = Local<Object>::Cast(args[0]);
        Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
        int length = pNum->Utf8Length();
        char *pChar = new char[length + 1];
        pNum->WriteUtf8(pChar);
        *(pChar + length) = '\0';

        NumType *pDan, *pTuo;
        int pos = 0;
        for(int i = 0; i < length; i++)
        {
            char c = pChar[i];
            if(c == '$')
            {
                pos = i;
                break;
            }
        }
        char *pCharTuo = pChar + pos + 1;
        pDan = new NumType(pChar, pos);     //胆码
        pTuo = new NumType(pCharTuo, length - pos - 1); //拖码

        bool hit = true;    //是否中奖
        int danLen = pDan->getCharLen();
        for(int i = 0; i < danLen; i++)
        {
            char c = pDan->getCharAt(i);
            int iCount = self->pDrawNumType->getCharCount(c);
            if(iCount < 1)
            {
                hit = false;
                break;
            }
        }

        if(hit)
        {
            int tuoHitCount = 0;
            int tuoLen = pTuo->getCharLen();
            for(int i = 0; i < tuoLen; i++)
            {
                char c = pTuo->getCharAt(i);
                int iCount = self->pDrawNumType->getCharCount(c);
                if(iCount >= 1)
                {
                    tuoHitCount++;
                }
            }
            if(tuoHitCount + danLen < 2)    //总hit数必须大于等于2
            {
                hit = false;
            }
        }

        if(hit)
        {
            self->gl->appendBonusObj(array, 4, 1);
        }

        delete pDan;
        delete pTuo;
        delete[] pChar;
    }
    return scope.Close(self->gl->getRst(array));
}

/**
 * 组4，重胆拖算奖
 */
Handle<Value> Check::Count0408(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Handle<Array> array = Array::New();
    //号码类型是否相同
    if(self->pDrawNumType->getType() == NUM_TYPE_Z4)
    {
        //获得号码的字符串
        Local<Object> pObj = Local<Object>::Cast(args[0]);
        Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
        int length = pNum->Utf8Length();
        char *pChar = new char[length + 1];
        pNum->WriteUtf8(pChar);
        *(pChar + length) = '\0';

        NumType *pDan, *pTuo;
        int pos = 0;
        for(int i = 0; i < length; i++)
        {
            char c = pChar[i];
            if(c == '$')
            {
                pos = i;
                break;
            }
        }
        char *pCharTuo = pChar + pos + 1;
        pDan = new NumType(pChar, pos);     //胆码
        pTuo = new NumType(pCharTuo, length - pos - 1); //拖码

        bool hit = true;    //是否中奖
        int danLen = pDan->getCharLen();
        for(int i = 0; i < danLen; i++)
        {
            char c = pDan->getCharAt(i);
            int iCount = self->pDrawNumType->getCharCount(c);
            if(iCount < 3)  //重胆拖，胆码必须出现3次
            {
                hit = false;
                break;
            }
        }

        if(hit)
        {
            int tuoHitCount = 0;
            int tuoLen = pTuo->getCharLen();
            for(int i = 0; i < tuoLen; i++)
            {
                char c = pTuo->getCharAt(i);
                int iCount = self->pDrawNumType->getCharCount(c);
                if(iCount >= 1)
                {
                    tuoHitCount++;
                }
            }
            if(tuoHitCount + danLen < 2)    //总hit数必须大于等于2
            {
                hit = false;
            }
        }

        if(hit)
        {
            self->gl->appendBonusObj(array, 4, 1);
        }

        delete pDan;
        delete pTuo;
        delete[] pChar;
    }
    return scope.Close(self->gl->getRst(array));
}

/**
 * 任一，单式算奖
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

            int hitCount = 0;
            ReNumType *pReNumType = new ReNumType(tmp, jCount);
            for(int i = 0; i < 4; i++)
            {
                if(pReNumType->hasChar(i, self->pDrawNum->getCharAt(i)))
                {
                    hitCount++;
                }
            }
            if(hitCount > 0)
            {
                self->gl->appendBonusObj(array, 5, hitCount);
            }

            jCount = 0; //号码长度重新计算
            delete pReNumType;
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
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/**
 * 任1，复式算奖
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

    int hitCount = 0;
    ReNumType *pReNumType = new ReNumType(pChar, length);
    for(int i = 0; i < 4; i++)
    {
        if(pReNumType->hasChar(i, self->pDrawNum->getCharAt(i)))
        {
            hitCount++;
        }
    }
    if(hitCount > 0)
    {
        self->gl->appendBonusObj(array, 5, hitCount);
    }
    delete pReNumType;
    delete[] pChar;

    return scope.Close(self->gl->getRst(array));
}

/**
 * 任2，单式算奖
 */
Handle<Value> Check::Count0600(const Arguments& args)
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

            int hitCount = 0;
            ReNumType *pReNumType = new ReNumType(tmp, jCount);
            for(int i = 0; i < 4; i++)
            {
                if(pReNumType->hasChar(i, self->pDrawNum->getCharAt(i)))
                {
                    hitCount++;
                }
            }
            if(hitCount >= 2)
            {
                self->gl->appendBonusObj(array, 6, 1);
            }

            jCount = 0; //号码长度重新计算
            delete pReNumType;
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
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/**
 * 任2，复式算奖
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

    int hitCount = 0;
    ReNumType *pReNumType = new ReNumType(pChar, length);
    for(int i = 0; i < 4; i++)
    {
        if(pReNumType->hasChar(i, self->pDrawNum->getCharAt(i)))
        {
            hitCount++;
        }
    }
    if(hitCount > 0)
    {
        int count = MathUtil::GetC(hitCount, 2);
        self->gl->appendBonusObj(array, 6, count);
    }
    delete pReNumType;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/**
 * 任2，和值算奖
 */
Handle<Value> Check::Count0603(const Arguments& args)
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

    bool hit = false;
    int first = MathUtil::CharToInt(self->pDrawNum->getCharAt(MathUtil::StrToInt(pChar, 1) - 1));
    int second = MathUtil::CharToInt(self->pDrawNum->getCharAt(MathUtil::StrToInt(pChar + 2, 1) - 1));
    int heZhi = first + second;
    IntArray* ia = new IntArray(16, pChar + 4, length - 4, ',');
    int aiLen = ia->length();
    for(int i = 0; i < aiLen; i++)
    {
        if(heZhi == ia->get(i))
        {
            hit = true;
            break;
        }
    }
    if(hit)
    {
        self->gl->appendBonusObj(array, 6, 1);
    }
    delete ia;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/**
 * 任2，跨度算奖
 */
Handle<Value> Check::Count0606(const Arguments& args)
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

    bool hit = false;
    int first = MathUtil::CharToInt(self->pDrawNum->getCharAt(MathUtil::StrToInt(pChar, 1) - 1));
    int second = MathUtil::CharToInt(self->pDrawNum->getCharAt(MathUtil::StrToInt(pChar + 2, 1) - 1));
    int kuaDu = first - second;
    if(kuaDu < 0)
    {
        kuaDu = kuaDu*(-1);
    }
    IntArray* ia = new IntArray(16, pChar + 4, length - 4, ',');
    int aiLen = ia->length();
    for(int i = 0; i < aiLen; i++)
    {
        if(kuaDu == ia->get(i))
        {
            hit = true;
            break;
        }
    }
    if(hit)
    {
        self->gl->appendBonusObj(array, 6, 1);
    }
    delete ia;

    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/**
 * 任2，全包
 */
Handle<Value> Check::Count0609(const Arguments& args)
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

    NumType *pNumType = new NumType(pChar, length);
    int count = 0;
    char firstChar = pNumType->getCharAt(0);
    int firstHitCount = self->pDrawNumType->getCharCount(firstChar);
    if(pNumType->getCharLen() == 1) //说明用户选了两个相同的号码
    {
        count = MathUtil::GetC(firstHitCount, 2);
    }
    else
    {
        char secondChar = pNumType->getCharAt(1);
        int secondHitCount = self->pDrawNumType->getCharCount(secondChar);
        count = firstHitCount*secondHitCount;
    }
    if(count > 0)
    {
        self->gl->appendBonusObj(array, 6, count);
    }

    delete pNumType;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/**
 * 任3，单式算奖
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

            int hitCount = 0;
            ReNumType *pReNumType = new ReNumType(tmp, jCount);
            for(int i = 0; i < 4; i++)
            {
                if(pReNumType->hasChar(i, self->pDrawNum->getCharAt(i)))
                {
                    hitCount++;
                }
            }
            if(hitCount >= 3)
            {
                self->gl->appendBonusObj(array, 7, 1);
            }

            jCount = 0; //号码长度重新计算
            delete pReNumType;
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
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/**
 * 任3，复式算奖
 */
Handle<Value> Check::Count0701(const Arguments& args)
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

    int hitCount = 0;
    ReNumType *pReNumType = new ReNumType(pChar, length);
    for(int i = 0; i < 4; i++)
    {
        if(pReNumType->hasChar(i, self->pDrawNum->getCharAt(i)))
        {
            hitCount++;
        }
    }
    if(hitCount > 0)
    {
        int count = MathUtil::GetC(hitCount, 3);
        self->gl->appendBonusObj(array, 7, count);
    }
    delete pReNumType;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/**
 * 任3，全包
 */
Handle<Value> Check::Count0709(const Arguments& args)
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

    NumType *pNumType = new NumType(pChar, length);
    int count = 0;
    char firstChar = pNumType->getCharAt(0);
    int firstCharCount = pNumType->getCharCountAt(0);
    int firstHitCount = self->pDrawNumType->getCharCount(firstChar);
    int firstCount = MathUtil::GetC(firstHitCount, firstCharCount);
    if(pNumType->getCharLen() == 1) //说明用户选了3个相同的号码
    {
        count = firstCount;
    }
    else
    {
        char secondChar = pNumType->getCharAt(1);
        int secondCharCount = pNumType->getCharCountAt(1);
        int secondHitCount = self->pDrawNumType->getCharCount(secondChar);
        int secondCount = MathUtil::GetC(secondHitCount, secondCharCount);
        if(pNumType->getCharLen() == 2) //说明用户选了2个相同的号码
        {
            count = firstCount*secondCount;
        }
        else    //说明没有相同的号码
        {
            char thChar = pNumType->getCharAt(2);
            int thCharCount = pNumType->getCharCountAt(2);
            int thHitCount = self->pDrawNumType->getCharCount(thChar);
            int thCount = MathUtil::GetC(thHitCount, thCharCount);

            count = firstHitCount*secondHitCount*thCount;
        }
    }
    if(count > 0)
    {
        self->gl->appendBonusObj(array, 7, count);
    }
    delete pNumType;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/**
 * 任4，单式算奖
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

            int hitCount = 0;
            ReNumType *pReNumType = new ReNumType(tmp, jCount);
            for(int i = 0; i < 4; i++)
            {
                if(pReNumType->hasChar(i, self->pDrawNum->getCharAt(i)))
                {
                    hitCount++;
                }
            }
            if(hitCount >= 4)
            {
                self->gl->appendBonusObj(array, 8, 1);
            }

            jCount = 0; //号码长度重新计算
            delete pReNumType;
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
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/**
 * 任4，复式算奖
 */
Handle<Value> Check::Count0801(const Arguments& args)
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

    int hitCount = 0;
    ReNumType *pReNumType = new ReNumType(pChar, length);
    for(int i = 0; i < 4; i++)
    {
        if(pReNumType->hasChar(i, self->pDrawNum->getCharAt(i)))
        {
            hitCount++;
        }
    }
    if(hitCount > 0)
    {
        int count = MathUtil::GetC(hitCount, 4);
        self->gl->appendBonusObj(array, 8, count);
    }
    delete pReNumType;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/**
 * 任选，单式算奖
 */
Handle<Value> Check::Count0900(const Arguments& args)
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

            int hitCount = 0;
            ReNumType *pReNumType = new ReNumType(tmp, jCount);
            for(int i = 0; i < 4; i++)
            {
                if(pReNumType->hasChar(i, self->pDrawNum->getCharAt(i)))
                {
                    hitCount++;
                }
            }
            int notEmptyCount = pReNumType->getNotEmptyCount();
            if(hitCount == notEmptyCount)
            {
                int level = self->getGlByReCount(notEmptyCount);
                self->gl->appendBonusObj(array, level, 1);
            }

            jCount = 0; //号码长度重新计算
            delete pReNumType;
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
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/**
 * 任选，复式算奖
 */
Handle<Value> Check::Count0901(const Arguments& args)
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

    int hitCount = 0;
    ReNumType *pReNumType = new ReNumType(pChar, length);
    for(int i = 0; i < 4; i++)
    {
        if(pReNumType->hasChar(i, self->pDrawNum->getCharAt(i)))
        {
            hitCount++;
        }
    }
    int notEmptyCount = pReNumType->getNotEmptyCount();
    if(hitCount == notEmptyCount)
    {
        int level = self->getGlByReCount(notEmptyCount);
        self->gl->appendBonusObj(array, level, 1);
    }

    delete pReNumType;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/**
 * 任选，组合算奖
 */
Handle<Value> Check::Count0902(const Arguments& args)
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

    int hitCount = 0;
    ReNumType *pReNumType = new ReNumType(pChar, length);
    for(int i = 0; i < 4; i++)
    {
        if(pReNumType->hasChar(i, self->pDrawNum->getCharAt(i)))
        {
            hitCount++;
        }
    }

    for(int i = 1; i < hitCount + 1; i++)
    {
        int level = self->getGlByReCount(i);
        int count = MathUtil::GetC(hitCount, i);
        self->gl->appendBonusObj(array, level, count);
    }

    delete pReNumType;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}