/*
 * VsJsonUtil.h
 *
 *  Created on: 2015年1月28日
 *      Author: liming
 */

#ifndef VSJSONUTIL_H_
#define VSJSONUTIL_H_

#include "VsJson.h"

struct VsJsonArray* vs_json_util_get_detail_mn(long m, long n);

void vs_json_util_get_detail_mn(struct VsJsonArray* array, long* tmpArray, long arrayLength, long m, long n, long level);

#endif /* VSJSONUTIL_H_ */
