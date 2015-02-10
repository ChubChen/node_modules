#ifndef VS_UTIL
#define VS_UTIL

#include "VsString.h"

/**
 * str 转换成long型数据
 */
long vs_util_str_to_long(struct VsString* str);

/**
 * 字符串转换成double
 */
double vs_util_str_to_double(struct VsString* str);

#endif