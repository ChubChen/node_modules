#ifndef GRADELEVEL_H
#define GRADELEVEL_H

#include <node.h>

class GradeLevel:public node::ObjectWrap {
    public:
        explicit GradeLevel(int levelCount = 0);
        ~GradeLevel();
        static void Init();
        static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);
        long getBonus(int level);
        void setBonus(int level, long bonus);
        int getLevelCount();
        void setBonusObj(v8::Handle<v8::Object> obj, int level, int count);
        void appendBonusObj(v8::Handle<v8::Array> array, int level, int count);
        v8::Handle<v8::Object> getRst(v8::Handle<v8::Array> array);

    private:
        static v8::Handle<v8::Value> New(const v8::Arguments& args);
        static v8::Handle<v8::Value> SetBonus(const v8::Arguments& args);
        static v8::Handle<v8::Value> GetBonus(const v8::Arguments& args);
        static v8::Persistent<v8::Function> constructor;
        long *bonusArray;
        int levelCount;
};

#endif