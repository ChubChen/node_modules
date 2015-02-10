#include <node.h>
#include "Check.h"
#include "MathUtil.h"

using namespace v8;

Persistent<Function> Check::constructor;

Check::Check()
{
    this->gl = NULL;
    //一维索引是红球猜中数目，二维是篮球猜中数目
    this->hitAndLevel[6][1] = 1;
    this->hitAndLevel[6][0] = 2;
    this->hitAndLevel[5][1] = 3;
    this->hitAndLevel[5][0] = 4;
    this->hitAndLevel[4][1] = 4;
    this->hitAndLevel[4][0] = 5;
    this->hitAndLevel[3][1] = 5;
    this->hitAndLevel[3][0] = -1;
    this->hitAndLevel[2][1] = 6;
    this->hitAndLevel[2][0] = -1;
    this->hitAndLevel[1][1] = 6;
    this->hitAndLevel[1][0] = -1;
    this->hitAndLevel[0][1] = 6;
    this->hitAndLevel[0][0] = -1;
}

Check::~Check()
{
    delete this->gl;
    delete this->redIntArray;
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
    constructor = Persistent<Function>::New(tpl->GetFunction());
}

/**
 * 真正初始化的方法
 */
Handle<Value> Check::New(const Arguments& args)
{
    HandleScope scope;
    if(args.IsConstructCall()) //from new Check()
    {
        Check * obj = new Check();
        obj->Wrap(args.This());
        return args.This();
    }
    else //from Check()
    {
        const int argc = 0;
        Local<Value> argv[argc] = {};
        return scope.Close(constructor->NewInstance(argc, argv));
    }
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

    int sepIndex = -1;      //红球和蓝球的分隔符位置
    for(int i = 0; i < length; i++)
    {
        char tmpChar = pChar[i];
        if(tmpChar == '|')
        {
            sepIndex = i;
        }
    }
    if(sepIndex >= 0)
    {
        obj->redIntArray = new IntArray(6, pChar, sepIndex, ',');
    }
    obj->blue = MathUtil::StrToInt(pChar + sepIndex + 1, 2);
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
 * 单式
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

            IntArray* numRedIntArray;   //要算奖的红球号码数组
            int blue = -1;
            //拆分号码串
            int sepIndex = -1;      //红球和蓝球的分隔符位置
            for(int i = 0; i < jCount; i++)
            {
                char tmpChar = tmp[i];
                if(tmpChar == '|')
                {
                    sepIndex = i;
                }
            }
            numRedIntArray = new IntArray(6, tmp, sepIndex, ',');
            blue = MathUtil::StrToInt(tmp + sepIndex + 1, 2);

            //红球选中数目
            int redHitCount = MathUtil::getHitCount(numRedIntArray, self->redIntArray);
            //蓝球选中数目
            int blueHitCount = 0;
            if(blue == self->blue)
            {
                blueHitCount = 1;
            }
            int level = self->hitAndLevel[redHitCount][blueHitCount];
            self->gl->appendBonusObj(array, level, 1);

            jCount = 0; //号码长度重新计算
            delete numRedIntArray;
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
 * 复式，遍历每一个奖级的中奖注数
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

    IntArray* numRedIntArray;   //要算奖的红球号码数组
    IntArray* numBlueIntArray;   //要算奖的蓝球号码数组
    //拆分号码串
    int sepIndex = -1;      //红球和蓝球的分隔符位置
    for(int i = 0; i < length; i++)
    {
        char tmpChar = pChar[i];
        if(tmpChar == '|')
        {
            sepIndex = i;
        }
    }
    numRedIntArray = new IntArray(33, pChar, sepIndex, ',');
    numBlueIntArray = new IntArray(16, pChar + sepIndex + 1, length - sepIndex - 1, ',');

    //红球选中数目
    int redHitCount = MathUtil::getHitCount(numRedIntArray, self->redIntArray);
    //蓝球选中数目
    int blueHitCount = 0;
    if(numBlueIntArray->hasValue(self->blue))
    {
        blueHitCount = 1;
    }
    int redNotHitCount = numRedIntArray->length() - redHitCount;
    int blueNotHitCount = numBlueIntArray->length() - blueHitCount;

    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            int level = self->hitAndLevel[i][j];
            if(level > 0)
            {
                int redCount = MathUtil::GetC(redHitCount, i)*MathUtil::GetC(redNotHitCount, 6 - i);
                int blueCount = MathUtil::GetC(blueHitCount, j)*MathUtil::GetC(blueNotHitCount, 1 - j);
                self->gl->appendBonusObj(array, level, redCount*blueCount);
            }
        }
    }

    delete numRedIntArray;
    delete numBlueIntArray;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}

/**
 * 胆拖算奖
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

    IntArray* numDanRedIntArray;   //要算奖的红球号码(胆)数组
    IntArray* numTuoRedIntArray;   //要算奖的红球号码(拖)数组
    IntArray* numBlueIntArray;   //要算奖的蓝球号码数组
    //拆分号码串
    int sepIndex = -1;      //红球和蓝球的分隔符位置
    int dtIndex = -1;
    for(int i = 0; i < length; i++)
    {
        char tmpChar = pChar[i];
        if(tmpChar == '$')
        {
            dtIndex = i;
        }
        if(tmpChar == '|')
        {
            sepIndex = i;
        }
    }
    numDanRedIntArray = new IntArray(33, pChar, dtIndex, ',');
    numTuoRedIntArray = new IntArray(33, pChar + dtIndex + 1, sepIndex - dtIndex - 1, ',');
    numBlueIntArray = new IntArray(16, pChar + sepIndex + 1, length - sepIndex - 1, ',');

    int danRedHitCount = MathUtil::getHitCount(numDanRedIntArray, self->redIntArray);
    int danRedNotHicCount = numDanRedIntArray->length() - danRedHitCount;

    int tuoRedHitCount = MathUtil::getHitCount(numTuoRedIntArray, self->redIntArray);
    int tuoRedNotHitCount = numTuoRedIntArray->length() - tuoRedHitCount;

    /*numTuoRedIntArray->traverse();
    self->redIntArray->traverse();
    printf("tuoRedHitCount:%d, tuoRedNotHitCount:%d\n", tuoRedHitCount, tuoRedNotHitCount);*/

    //蓝球选中数目
    int blueHitCount = 0;
    if(numBlueIntArray->hasValue(self->blue))
    {
        blueHitCount = 1;
    }
    int blueNotHitCount = numBlueIntArray->length() - blueHitCount;

    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            int level = self->hitAndLevel[i][j];
            if(level > 0)
            {
                int redCount = MathUtil::GetC(tuoRedHitCount, i - danRedHitCount)*MathUtil::GetC(tuoRedNotHitCount, 6 - danRedNotHicCount - i);
                int blueCount = MathUtil::GetC(blueHitCount, j)*MathUtil::GetC(blueNotHitCount, 1 - j);
                //printf("redHit:%d, blueHit:%d, redCount:%d, blueCount:%d\n", i, j, redCount, blueCount);
                self->gl->appendBonusObj(array, level, redCount*blueCount);
            }
        }
    }

    delete numDanRedIntArray;
    delete numTuoRedIntArray;
    delete numBlueIntArray;
    delete[] pChar;
    return scope.Close(self->gl->getRst(array));
}


