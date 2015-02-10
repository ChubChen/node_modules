#include <node.h>
#include <stdlib.h>
#include "EasyString.h"

EasyString::EasyString()
{
}

EasyString::EasyString(v8::Handle<v8::String> pStr)
{
    int length = pStr->Utf8Length();
    this->content = (char *)malloc(sizeof(char)*length);
    pStr->WriteUtf8(this->content);
    this->len = length;
}

char * EasyString::pointer()
{
    return this->content;
}

int EasyString::length()
{
    return this->len;
}

EasyString::~EasyString()
{
    free(this->content);
}