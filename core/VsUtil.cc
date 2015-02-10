#include <stdio.h>
#include <stdlib.h>

#include "VsUtil.h"

/**
 * str 转换成long型数据
 */
long vs_util_str_to_long(struct VsString* str)
{
    return atol(str->pt);
}

double vs_util_str_to_double(struct VsString* str)
{
    return strtod(str->pt, NULL);
}