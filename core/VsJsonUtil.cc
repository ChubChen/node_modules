/*
 * VsJsonUtil.cc
 *
 *  Created on: 2015年1月28日
 *      Author: liming
 */

#include <stdlib.h>
#include <stdio.h>
#include "VsJson.h"
#include "VsJsonUtil.h"

#include "VsUtil.h"

struct VsJsonArray* vs_json_util_get_detail_mn(long m, long n)
{
	struct VsJsonArray* array = vs_json_array_init("[]");
	long tmpArray[n];
	vs_json_util_get_detail_mn(array, tmpArray, n, m, n, 0);
	return array;
}

void vs_json_util_get_detail_mn(struct VsJsonArray* array, long* tmpArray,
		long arrayLength, long m, long n, long level)
{
	if(n == 0)
	{
		struct VsJsonArray* set = vs_json_array_init(tmpArray, arrayLength);
		struct VsJsonValue* value = vs_json_value_init(set);
		vs_json_array_append(array, value);
		return;
	}
	long startIndex = 0;
	if(level > 0)
	{
		startIndex = *(tmpArray + level - 1) + 1;	//非第一层，则要从上一层的下一个记录开始
	}
	for(long i = startIndex; i < m; i++)
	{
		*(tmpArray + level) = i;	//记录当层的序号
		vs_json_util_get_detail_mn(array, tmpArray, arrayLength, m, n - 1, level + 1);
	}
}



