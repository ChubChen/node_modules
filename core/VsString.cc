#include <stdio.h>
#include <stdlib.h>

#include "VsString.h"

/**
 * 初始化一个空字符串
 * @return VsString * 结构体指针
 */
VsString* vs_string_init()
{
    return vs_string_init(NULL, 0L, VS_STRING_INIT_VOLUME);
}

VsString* vs_string_init(const char *src)
{
    return vs_string_init(src, -1L, VS_STRING_INIT_VOLUME);
}

/**
 * 初始化一个字符串，容量为volume
 * @param long 容量
 * @return VsString * 结构体指针
 */
VsString* vs_string_init(const char *src, long length, long volume)
{
    VsString* str = (VsString *)malloc(sizeof(VsString));
    str->pt = (char *)malloc(sizeof(char)*volume);
    str->volume = volume;
    str->length = 0;
    *(str->pt + str->length) = '\0';
    if(length >= 0)
    {
        vs_string_append(str, src, length);
    }
    else
    {
        vs_string_append(str, src);
    }
    return str;
}

void vs_string_destroy(VsString* str)
{
    if(str != NULL) //如果str不为空，则释放str存储内容的指针
    {
        //printf("销毁字符串:%s\n", str->pt);
        free(str->pt);
        free(str);
    }
}

void vs_string_print(VsString* str)
{
    printf("%s\n", str->pt);
}

void vs_string_append(VsString* str, const char *src)
{
    if(src == NULL) //如果源为空，不做任何操作
    {
        return;
    }
    int srcLength = string_length(src);
    vs_string_append(str, src, srcLength);
}

/**
 * 在字符串末尾追加long型数据
 * @param str
 * @param value
 */
void vs_string_append(VsString* str, long value)
{
    char src[24];
    sprintf(src, "%ld", value);
    vs_string_append(str, src);
}

/**
 * 在字符串末尾追加double型数据
 * @param str
 * @param value
 */
void vs_string_append(VsString* str, double value)
{
    char src[48];
    sprintf(src, "%lf", value);
    vs_string_append(str, src);
}

/**
 * 在字符串末尾追加char型数据
 * @param str
 * @param value
 */
void vs_string_append(VsString* str, char value)
{
    int newLength = str->length + 2;
    if(newLength > str->volume)
    {
        int appendVolume = (int)(VS_STRING_INC_PER*str->volume);
        if(appendVolume < VS_STRING_MIN_INC_VOLUME)
        {
            appendVolume = VS_STRING_MIN_INC_VOLUME;
        }
        int newVolume = str->volume + appendVolume;
        str->pt = (char *)realloc(str->pt, sizeof(char)*newVolume);
        str->volume = newVolume;
    }
    *(str->pt + str->length) = value;
    str->length++;
    *(str->pt + str->length) = '\0';
}

void vs_string_append(VsString* str, const char *src, int length)
{
    if(src == NULL) //如果源为空，不做任何操作
    {
        return;
    }
    int newLength = str->length + length + 1;
    if(newLength > str->volume)
    {
        int appendVolume = (int)(VS_STRING_INC_PER*str->volume);
        if(appendVolume < VS_STRING_MIN_INC_VOLUME)
        {
            appendVolume = VS_STRING_MIN_INC_VOLUME;
        }
        int newVolume = str->volume + appendVolume;
        if(newVolume < newLength)
        {
            newVolume = str->volume + appendVolume + length;
        }
        str->pt = (char *)realloc(str->pt, sizeof(char)*newVolume);
        str->volume = newVolume;
    }
    string_copy(src, length, str->pt, str->length);
    str->length = str->length + length;
    *(str->pt + str->length) = '\0';
}

void vs_string_append(VsString* dest, VsString* src)
{
    if(src == NULL) //如果源为空，不做任何操作
    {
        return;
    }
    vs_string_append(dest, src->pt, src->length);
}

/**
 * 获得指定索引的字符，
 * 如果索引不存在，则返回'\0'
 */
char vs_string_char_at(struct VsString* src, long index)
{
	if(index >= 0 && index < src->length)
	{
		return *(src->pt + index);
	}
	else
	{
		return '\0';
	}
}

void string_copy(const char *src, char *dest)
{
    int i = 0;
    char c = *src;
    while(c != '\0')
    {
        *dest = c;
        dest++;
        i++;
        c = *(src + i);
    }
    *dest = '\0';
}

void string_copy(const char *src, int srcLength, char *dest, int start)
{
    int i = 0;
    dest = dest + start;
    char c = *src;
    while(i < srcLength)
    {
        *dest = c;
        dest++;
        i++;
        c = *(src + i);
    }
    *dest = '\0';
}

long string_length(const char *src)
{
    long i = 0;
    char c = *src;
    while(c != '\0')
    {
        i++;
        c = *(src + i);
    }
    return i;
}

/**
 * 清空一个字符串
 * @param str VsString * 结构体指针
 * @return void
 */
void vs_string_clear(VsString* str)
{
    str->length = 0;
    *(str->pt) = '\0';
}

/**
*截取一个字符串
* @param str VsString * 结构体指针
*从多少长开始截取
*/

void vs_string_truncate(VsString* str, long srcLength){
    if(str->length > srcLength){
        str->length = srcLength;
        *(str->pt +srcLength) = '\0';
    }
}


/**
 * 判断两个字符串是否相等
 * @param str VsString * 结构体指针
 * @param dest VsString * 结构体指针
 * @return void
 */
bool vs_string_equal(VsString* src, VsString* dest)
{
    bool equal = false;
    if(src->length == dest->length)
    {
        char* srcPt = src->pt;
        char* destPt = dest->pt;
        int i = 0;
        while(i < src->length)
        {
            if(*srcPt != *destPt)
            {
                break;
            }
            srcPt++;
            destPt++;
            i++;
        }
        if(i == src->length)
        {
            equal = true;
        }
    }
    return equal;
}

/**
 * 获得目标字符串的子串
 */
struct VsString* vs_string_sub(VsString* str, int start, int end)
{
    struct VsString* newStr = vs_string_init(NULL);
    while(start <= end)
    {
        vs_string_append(newStr, *(str->pt + start));
        start++;
    }
    return newStr;
}

/**
 * 获得char c在字符串中的位置，如果没有则返回-1
 */
int vs_string_index_of(VsString* str, char c)
{
    int index = -1;
    if(str != NULL && str->pt != NULL)
    {
        int i = 0;
        while(i < str->length)
        {
            char tmp = *(str->pt + i);
            if(c == tmp)
            {
                index = i;
                break;
            }
            i++;
        }
    }
    return index;
}

/**
 * 分隔字符串
 */
struct VsStringList* vs_string_split(struct VsString* str, char c)
{
    struct VsStringList* list = vs_string_list_init();
    char* tmp = str->pt;
    int i = 0;
    int last = 0;
    int length = 0;
    while(i <= str->length)
    {
        char cur = *tmp;
        if(cur == c || cur == '\0') //如果是目标字符，或者字符串结束
        {
            struct VsString* tmpStr = vs_string_init("");
            vs_string_append(tmpStr, str->pt + last, length);
            vs_string_list_append(list, tmpStr);

            last = i + 1;
            length = 0;
        }
        else
        {
            length++;
        }
        tmp++;
        i++;
    }
    return list;
}

/**
 * 初始化一个字符串列表
 */
struct VsStringList* vs_string_list_init()
{
    struct VsStringList* list = (struct VsStringList*)malloc(sizeof(struct VsStringList));
    list->length = 0;
    list->volume = VS_STRING_LIST_INIT_VOLUME;
    list->pt = (struct VsString**)malloc(sizeof(struct VsString *)*list->volume);
    return list;
}


/**
 * 销毁一个字符串数组
 */
void vs_string_list_destroy(struct VsStringList* list)
{
    if(list != NULL)
    {
        for(int i = 0; i < list->length; i++)
        {
            struct VsString* str = *(list->pt + i);
            vs_string_destroy(str);
        }
        free(list->pt);
        free(list);
    }
}

/**
 * 在字符串列表末尾追加元素
 */
void vs_string_list_append(struct VsStringList* list, struct VsString* str)
{
    int newLength = list->length + 1;
    if(newLength > list->volume)
    {
        int appendVolume = (int)(VS_STRING_LIST_INC_PER*list->volume);
        if(appendVolume < VS_STRING_LIST_MIN_INC_VOLUME)
        {
            appendVolume = VS_STRING_LIST_MIN_INC_VOLUME;
        }
        long newVolume = list->volume + appendVolume;
        list->pt = (struct VsString **)realloc(list->pt, sizeof(struct VsString*)*newVolume);
        list->volume = newVolume;
    }
    *(list->pt + list->length) = str;   //添加到末尾
    list->length++;    //栈的长度+1
}

/**
 * 获取目标索引的字符串
 */
struct VsString* vs_string_list_get(struct VsStringList* list, int index)
{
    if(index < list->length)
    {
        return *(list->pt + index);
    }
    else
    {
        return NULL;
    }
}

/**
 * 判断字符串是否以start开始
 * @param str VsString * 结构体指针
 * @param start char *
 * @return void
 */
bool vs_string_start_with(VsString* src, const char* start)
{
    bool equal = false;
    int length = string_length(start);

    char* srcPt = src->pt;
    int i = 0;
    while(i < length)
    {
        if(*srcPt != *start)
        {
            break;
        }
        srcPt++;
        start++;
        i++;
    }
    if(i == length)
    {
        equal = true;
    }
    return equal;
}
