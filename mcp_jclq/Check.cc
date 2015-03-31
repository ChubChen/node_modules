#include <stdio.h>
#include <stdlib.h>
#include <node.h>
#include <math.h>
#include <iostream>
using namespace std;

#include "Check.h"
#include "VsString.h"
#include "VsJson.h"
#include "VsUtil.h"
#include "VsJsonUtil.h"

using namespace v8;

Persistent<Function> Check::constructor;

Check::Check()
{
    this->initBunchMap();

    /*struct VsString* jsonStr = vs_json_object_to_string(this->bunchMap);
    vs_string_print(jsonStr);
    vs_string_destroy(jsonStr);*/

    this->drawMap = vs_json_object_init("{}");

    this->cancelFlag = vs_string_init("*");
}

Check::~Check()
{
    vs_json_object_destroy(this->bunchMap);
    vs_json_object_destroy(this->drawMap);
    vs_string_destroy(this->cancelFlag);
}

void Check::initBunchMap()
{
    struct VsJsonObject* obj = vs_json_object_init("{}");
    vs_json_object_set_string(obj, "11", "10000000");
    vs_json_object_set_string(obj, "21", "01000000");
    vs_json_object_set_string(obj, "31", "00100000");
    vs_json_object_set_string(obj, "41", "00010000");
    vs_json_object_set_string(obj, "51", "00001000");
    vs_json_object_set_string(obj, "61", "00000100");
    vs_json_object_set_string(obj, "71", "00000010");
    vs_json_object_set_string(obj, "81", "00000001");
    vs_json_object_set_string(obj, "23", "11000000");
    vs_json_object_set_string(obj, "36", "11000000");
    vs_json_object_set_string(obj, "37", "11100000");
    vs_json_object_set_string(obj, "410", "11000000");
    vs_json_object_set_string(obj, "414", "11100000");
    vs_json_object_set_string(obj, "415", "11110000");
    vs_json_object_set_string(obj, "515", "11000000");
    vs_json_object_set_string(obj, "525", "11100000");
    vs_json_object_set_string(obj, "530", "11110000");
    vs_json_object_set_string(obj, "531", "11111000");
    vs_json_object_set_string(obj, "621", "11000000");
    vs_json_object_set_string(obj, "641", "11100000");
    vs_json_object_set_string(obj, "656", "11110000");
    vs_json_object_set_string(obj, "662", "11111000");
    vs_json_object_set_string(obj, "663", "11111100");
    vs_json_object_set_string(obj, "7127", "11111110");
    vs_json_object_set_string(obj, "8255", "11111111");
    vs_json_object_set_string(obj, "33", "01000000");
    vs_json_object_set_string(obj, "34", "01100000");
    vs_json_object_set_string(obj, "46", "01000000");
    vs_json_object_set_string(obj, "411", "01110000");
    vs_json_object_set_string(obj, "510", "01000000");
    vs_json_object_set_string(obj, "520", "01100000");
    vs_json_object_set_string(obj, "526", "01111000");
    vs_json_object_set_string(obj, "615", "01000000");
    vs_json_object_set_string(obj, "635", "01100000");
    vs_json_object_set_string(obj, "650", "01110000");
    vs_json_object_set_string(obj, "657", "01111100");
    vs_json_object_set_string(obj, "7120", "01111110");
    vs_json_object_set_string(obj, "8247", "01111111");
    vs_json_object_set_string(obj, "44", "00100000");
    vs_json_object_set_string(obj, "45", "00110000");
    vs_json_object_set_string(obj, "516", "00111000");
    vs_json_object_set_string(obj, "620", "00100000");
    vs_json_object_set_string(obj, "642", "00111100");
    vs_json_object_set_string(obj, "55", "00010000");
    vs_json_object_set_string(obj, "56", "00011000");
    vs_json_object_set_string(obj, "622", "00011100");
    vs_json_object_set_string(obj, "735", "00010000");
    vs_json_object_set_string(obj, "870", "00010000");
    vs_json_object_set_string(obj, "66", "00001000");
    vs_json_object_set_string(obj, "67", "00001100");
    vs_json_object_set_string(obj, "721", "00001000");
    vs_json_object_set_string(obj, "856", "00001000");
    vs_json_object_set_string(obj, "77", "00000100");
    vs_json_object_set_string(obj, "78", "00000110");
    vs_json_object_set_string(obj, "828", "00000100");
    vs_json_object_set_string(obj, "88", "00000010");
    vs_json_object_set_string(obj, "89", "00000011");
    this->bunchMap = obj;
}

void Check::Init()
{
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("Check"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    tpl->PrototypeTemplate()->Set(String::NewSymbol("count"), FunctionTemplate::New(Count)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("setDrawNumber"), FunctionTemplate::New(SetDrawNumber)->GetFunction());
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
    else{   //from Check()
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
 * 获得号码串
 */
struct VsString* Check::getNumber(Local<Object> pObj)
{
    //获得号码的字符串
    Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
    int length = pNum->Utf8Length();
    struct VsString* str = vs_string_init(NULL, -1L, length + 1);
    pNum->WriteUtf8(str->pt);
    str->length = length;
    *(str->pt + str->length) = '\0';
    return str;
}

/**
 * 获得号码串
 */
struct VsString* Check::getBetType(Local<Object> pObj)
{
    //获得号码的字符串
    Local<String> pNum = pObj->Get(String::NewSymbol("bType"))->ToString();
    int length = pNum->Utf8Length();
    struct VsString* str = vs_string_init(NULL, -1L, length + 1);
    pNum->WriteUtf8(str->pt);
    str->length = length;
    *(str->pt + str->length) = '\0';
    return str;
}

//获得场次及号码串、选项、赔率等信息
struct VsJsonObject* Check::getNumberObj(struct VsString* number, struct VsString* betType)
{
    struct VsJsonObject* numberObj = vs_json_object_init("{}");
    struct VsJsonValue* dataArray = vs_json_value_init("[]");
    vs_json_object_set(numberObj, "data", dataArray);
    vs_json_object_set_string(numberObj, "betType", betType->pt);

    //vs_string_print(number);
    struct VsStringList* list = vs_string_split(number, ';');
    for(int i = 0; i < list->length; i++)
    {
        struct VsString* match = vs_string_list_get(list, i);
        struct VsStringList* matchList = vs_string_split(match, '|');
        struct VsString* playType = vs_string_list_get(matchList, 0);
        struct VsString* matchCode = vs_string_list_get(matchList, 1);
        struct VsString* choice = vs_string_list_get(matchList, 2);

        struct VsJsonValue* obj = vs_json_value_init("{}");
        vs_json_object_set_string(obj->objectValue, "playType", playType->pt);
        vs_json_object_set_string(obj->objectValue, "matchCode", matchCode->pt);
        vs_json_object_set_string(obj->objectValue, "choiceResult", choice->pt);

        struct VsStringList* choiceList = vs_string_split(choice, ',');
        struct VsJsonValue* choiceObject = vs_json_value_init("{}");
        for(int j = 0; j < choiceList->length; j++)
        {
            struct VsString* str = vs_string_list_get(choiceList, j);
            struct VsStringList* choiceOptionList = vs_string_split(str, '@');
            struct VsString* option = vs_string_list_get(choiceOptionList, 0);
            struct VsString* odds = vs_string_list_get(choiceOptionList, 1);

            vs_json_object_set(choiceObject->objectValue, option->pt, odds->pt);
            vs_string_list_destroy(choiceOptionList);
        }
        vs_json_object_set(obj->objectValue, "choice", choiceObject);
        vs_string_list_destroy(choiceList);

        vs_json_array_set(dataArray->arrayValue, i, obj);
        vs_string_list_destroy(matchList);
    }
    vs_string_list_destroy(list);
    return numberObj;
}

/**
 * 设置开奖号码，当nodejs层发现场次还未设置开奖号码，则会调用此方法进行设置
 */
Handle<Value> Check::SetDrawNumber(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Local<Object> pObj = Local<Object>::Cast(args[0]);

    //获得场次
    Local<String> code = pObj->Get(String::NewSymbol("code"))->ToString();
    int length = code->Utf8Length();
    struct VsString* codeStr = vs_string_init(NULL, -1L, length + 1);
    code->WriteUtf8(codeStr->pt);
    codeStr->length = length;
    *(codeStr->pt + codeStr->length) = '\0';

    //获得开奖号码
    Local<String> pNum = pObj->Get(String::NewSymbol("number"))->ToString();
    length = pNum->Utf8Length();
    struct VsString* str = vs_string_init(NULL, -1L, length + 1);
    pNum->WriteUtf8(str->pt);
    str->length = length;
    *(str->pt + str->length) = '\0';

    struct VsJsonValue* matchValue = vs_json_value_init("{}");
    if(vs_string_equal(str, self->cancelFlag))
    {
        vs_json_object_set_string(matchValue->objectValue, "02", "*");
        vs_json_object_set_string(matchValue->objectValue, "01", "*");
        vs_json_object_set_string(matchValue->objectValue, "03", "*");
        vs_json_object_set_string(matchValue->objectValue, "04", "*");
        vs_json_object_set_string(matchValue->objectValue, "06", "*");
    }
    else
    {
        //105:99  主队得分
        struct VsStringList* endStrList = vs_string_split(str, ':');


        //long rang = vs_util_str_to_long(rangStr);   //让球数

        long hostEnd = vs_util_str_to_long(vs_string_list_get(endStrList, 0));   //全场主队分数
        long guestEnd = vs_util_str_to_long(vs_string_list_get(endStrList, 1));   //客场分数

        long bifenCha = hostEnd - guestEnd;//比分差

        //统计胜平负
        if(hostEnd > guestEnd)
        {
            vs_json_object_set_string(matchValue->objectValue, "02", "1");
        }
        else
        {
            vs_json_object_set_string(matchValue->objectValue, "02", "2");
        }
        //统计让球胜平负
         vs_json_object_set_string(matchValue->objectValue, "01", str->pt);

         vs_json_object_set_string(matchValue->objectValue, "04", str->pt);

        if(bifenCha > 0){
            if(bifenCha >= 1 && bifenCha <= 5){
                vs_json_object_set_string(matchValue->objectValue, "03", "01");
            }
            else if(bifenCha >= 6 && bifenCha <= 10){
                vs_json_object_set_string(matchValue->objectValue, "03", "02");
            }
            else if(bifenCha >= 11 && bifenCha <= 15){
                vs_json_object_set_string(matchValue->objectValue, "03", "03");
            }
            else if(bifenCha >= 16 && bifenCha <= 20){
                vs_json_object_set_string(matchValue->objectValue, "03", "04");
            }
            else if(bifenCha >= 21 && bifenCha <= 25){
                vs_json_object_set_string(matchValue->objectValue, "03", "05");
            }
            else{
                vs_json_object_set_string(matchValue->objectValue, "03", "06");
            }
        }else{
            bifenCha = 0 - bifenCha;
            if(bifenCha >= 1 && bifenCha <= 5){
                vs_json_object_set_string(matchValue->objectValue, "03", "11");
            }
            else if(bifenCha >= 6 && bifenCha <= 10){
                vs_json_object_set_string(matchValue->objectValue, "03", "12");
            }
            else if(bifenCha >= 11 && bifenCha <= 15){
                vs_json_object_set_string(matchValue->objectValue, "03", "13");
            }
            else if(bifenCha >= 16 && bifenCha <= 20){
                vs_json_object_set_string(matchValue->objectValue, "03", "14");
            }
            else if(bifenCha >= 21 && bifenCha <= 25){
                vs_json_object_set_string(matchValue->objectValue, "03", "15");
            }
            else{
                vs_json_object_set_string(matchValue->objectValue, "03", "16");
            }
        }
        vs_string_list_destroy(endStrList);
    }
    vs_json_object_set(self->drawMap, codeStr, matchValue);

    vs_string_destroy(codeStr);
    vs_string_destroy(str);
    return scope.Close(Undefined());
}

/**
 * 让球胜平负
 */
Handle<Value> Check::Count(const Arguments& args)
{
    HandleScope scope;
    Check *self = ObjectWrap::Unwrap<Check>(args.This());
    Local<Object> pObj = Local<Object>::Cast(args[0]);
    Handle<Array> array = Array::New();
    Handle<Array> detailArray = Array::New();

    double totalBonus = 0;    //ticket all bonus
    struct VsString* number = self->getNumber(pObj);
    struct VsString* betType = self->getBetType(pObj);
    struct VsJsonObject* numberObj = self->getNumberObj(number, betType);

    struct VsString* bunchFlag = vs_json_object_get(self->bunchMap, betType)->strValue;
    struct VsJsonArray* matchArray = vs_json_object_get(numberObj, "data")->arrayValue;
    long m = matchArray->length;
    for(int i = 0; i < bunchFlag->length; i++)
    {
        char c = vs_string_char_at(bunchFlag, i);
        if(c == '1')
        {
            long n = i + 1;
            long level = n*10 + 1;  //奖级,21,31,41...
            long count = 0; //注数
            double bonus = 0; //这一级别的中奖金额
            struct VsJsonArray* detail = vs_json_util_get_detail_mn(m, n);
            //traverse the detail
            for(int j = 0; j < detail->length; j++)
            {
                double totalMultiplier = 200.00;    //一注2元
                long curCount = 1;
                struct VsJsonArray* set = vs_json_array_get(detail, j)->arrayValue;
                for(int l = 0; l < set->length; l++)
                {
                    long matchIndex = vs_json_array_get(set, l)->longValue;

                    struct VsJsonObject* curMatch = vs_json_array_get(matchArray, matchIndex)->objectValue;
                    struct VsString* matchCode = vs_json_object_get(curMatch, "matchCode")->strValue;
                    struct VsString* playType = vs_json_object_get(curMatch, "playType")->strValue;
                    struct VsString* choiceResult = vs_json_object_get(curMatch, "choiceResult")->strValue;

                    struct VsJsonObject* choiceObject = vs_json_object_get(curMatch, "choice")->objectValue;

                    struct VsJsonObject* drawOptions = vs_json_object_get(self->drawMap, matchCode)->objectValue;
                    struct VsString* drawOption = vs_json_object_get(drawOptions, playType)->strValue;

                    if(vs_string_equal(drawOption, self->cancelFlag))   //场次取消，有多少个选项，则为多少倍
                    {
                        totalMultiplier *= choiceObject->length;
                        curCount *= choiceObject->length;
                    }
                    else
                    {
                        struct VsString*  playRang = vs_string_init("01");
                        struct VsString*  playDaXiao = vs_string_init("04");
                        if(vs_string_equal(playRang, playType)){
                            struct VsStringList* choiceList = vs_string_split(choiceResult, ',');
                            struct VsStringList* endStrList = vs_string_split(drawOption, ':');

                            long hostEnd = vs_util_str_to_long(vs_string_list_get(endStrList, 0));   //全场主队分数
                            long guestEnd = vs_util_str_to_long(vs_string_list_get(endStrList, 1));   //客场分数
                            bool prizeFlag = false;
                            for(int j = 0; j < choiceList->length; j++)
                            {
                               struct VsString* str = vs_string_list_get(choiceList, j);
                               struct VsStringList* choiceOptionList = vs_string_split(str, '@');
                               struct VsString* option = vs_string_list_get(choiceOptionList, 0);
                               double rangqiu = 0 ;
                               if(vs_string_index_of(option, '(') > 0){
                                   struct VsStringList* realChoiceOptionList = vs_string_split(option, '(');
                                   option = vs_string_list_get(realChoiceOptionList, 0);
                                   struct VsString* otherInfo = vs_string_list_get(realChoiceOptionList, 1); //让球值 或者预示总分
                                   vs_string_truncate(otherInfo, otherInfo->length - 1);
                                   rangqiu = vs_util_str_to_double(otherInfo);
                               }

                                struct VsString* odds = vs_string_list_get(choiceOptionList, 1);
                               //判断让球胜平负
                               if(hostEnd + rangqiu > guestEnd ){//主胜
                                    if(vs_util_str_to_long(option) == 1){
                                        totalMultiplier *= vs_util_str_to_double(odds);
                                        prizeFlag = true;
                                        break;
                                    }
                               }else{
                                    if(vs_util_str_to_long(option) == 2 ){
                                        totalMultiplier *= vs_util_str_to_double(odds);
                                         prizeFlag = true;
                                         break;
                                    }
                               }
                               vs_string_list_destroy(choiceOptionList);
                            }
                            if(!prizeFlag){
                                 totalMultiplier = 0;
                                 curCount = 0;
                                 break;
                            }
                           vs_string_list_destroy(choiceList);
                           vs_string_list_destroy(endStrList);
                        }else if (vs_string_equal(playDaXiao, playType)){

                            struct VsStringList* choiceList = vs_string_split(choiceResult, ',');
                            struct VsStringList* endStrList = vs_string_split(drawOption, ':');

                            long hostEnd = vs_util_str_to_long(vs_string_list_get(endStrList, 0));   //全场主队分数
                            long guestEnd = vs_util_str_to_long(vs_string_list_get(endStrList, 1));   //客场分数
                            bool prizeFlag = false;

                            for(int j = 0; j < choiceList->length; j++)
                            {
                               struct VsString* str = vs_string_list_get(choiceList, j);
                               struct VsStringList* choiceOptionList = vs_string_split(str, '@');
                               struct VsString* option = vs_string_list_get(choiceOptionList, 0);
                               double totalFen = 0;
                               if(vs_string_index_of(option, '(') > 0){
                                   struct VsStringList* realChoiceOptionList = vs_string_split(option, '(');
                                   option = vs_string_list_get(realChoiceOptionList, 0);
                                   struct VsString* otherInfo = vs_string_list_get(realChoiceOptionList, 1); //让球值 或者预示总分
                                   vs_string_truncate(otherInfo, otherInfo->length - 1);
                                   totalFen = vs_util_str_to_double(otherInfo);

                               }

                               struct VsString* odds = vs_string_list_get(choiceOptionList, 1);
                               //判断让球胜平负
                               if(hostEnd + guestEnd > totalFen ){//大
                                    if(vs_util_str_to_long(option) == 1 ){
                                        totalMultiplier *=vs_util_str_to_double(odds);
                                        prizeFlag = true;
                                        break;
                                    }
                               }else{
                                    if(vs_util_str_to_long(option) == 2 ){
                                        totalMultiplier *=vs_util_str_to_double(odds);
                                        prizeFlag = true;
                                        break;
                                    }
                               }
                               vs_string_list_destroy(choiceOptionList);
                            }
                            if(!prizeFlag){
                                totalMultiplier = 0;
                                curCount = 0;
                                break;
                            }
                           vs_string_list_destroy(choiceList);
                           vs_string_list_destroy(endStrList);
                        }else{
                            struct VsJsonValue* select = vs_json_object_get(choiceObject, drawOption);
                            if(select == NULL)  //用户选择错误
                            {
                                totalMultiplier = 0;
                                curCount = 0;
                                break;
                            }
                            else    //选择正确
                            {
                                totalMultiplier *= select->doubleValue;
                            }
                        }
                        vs_string_destroy(playRang);
                        vs_string_destroy(playDaXiao);
                    }
                }
                count += curCount;
                bonus += totalMultiplier;
                //printf("the multiple is:%lf.\n", totalMultiplier);
            }
            if(bonus > 0)   //中奖，生成奖级信息
            {
                totalBonus += bonus;

                Handle<Object> obj = Object::New();
                Local<String> bonusKey = String::NewSymbol("bonus");
                Local<String> bonusBeforeTaxKey = String::NewSymbol("bonusBeforeTax");
                Local<String> levelKey = String::NewSymbol("level");
                Local<String> countKey = String::NewSymbol("count");
                obj->Set(bonusKey, Number::New(bonus));
                obj->Set(bonusBeforeTaxKey, Number::New(bonus));
                obj->Set(levelKey, Number::New(level));
                obj->Set(countKey, Number::New(count));

                int len = detailArray->Length();
                detailArray->Set(len, obj);
            }
            vs_json_array_destroy(detail);
        }
    }
    vs_string_destroy(betType);
    vs_string_destroy(number);
    vs_json_object_destroy(numberObj);

    long totalBonusLong = floor(totalBonus);
    if(totalBonusLong > 1000000){
        totalBonusLong = totalBonusLong * 4 / 5;
    }
    //生成总计信息
    array->Set(String::NewSymbol("bonus"), Number::New(totalBonusLong));
    array->Set(String::NewSymbol("bonusBeforeTax"), Number::New(totalBonusLong));
    array->Set(String::NewSymbol("bonusDetail"), detailArray);

    return scope.Close(array);
}

