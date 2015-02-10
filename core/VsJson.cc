#include <stdio.h>
#include <stdlib.h>

#include "VsUtil.h"
#include "VsJson.h"
#include "VsString.h"

#include "VsCharStack.h"

/**
 * 初始化一个json对象
 * @param str VsString* 要转成json对象的字符串
 * @return VsJsonObject 目标json对象
 */
struct VsJsonObject* vs_json_object_init(const char* str)
{
	struct VsString* objectStr = vs_string_init(str);
	struct VsJsonObject* object = vs_json_object_init(objectStr);
	vs_string_destroy(objectStr);
	return object;
}

/**
 * 根据字符串, 初始化一个json对象
 */
struct VsJsonObject* vs_json_object_init(struct VsString* str) {
	struct VsJsonObject* object = (struct VsJsonObject*) malloc(
			sizeof(VsJsonObject));
	object->length = 0;
	object->volume = VS_JSON_OBJECT_INIT_VOLUME;

	object->list = (struct VsJsonKv**) malloc(
	sizeof(struct VsJsonKv *) * object->volume);

	//初始化一个栈
	VsCharStack* stack = vs_char_stack_init();

	VsString* key = vs_string_init(NULL);   //存储临时的key
	VsString* value = vs_string_init(NULL); //存储临时的value

	int flag = 1; //标志,1:解析key，无内容，2:解析key，内容中,3:解析value，无内容，4:解析value，内容中，5:解析value，Object or Array
	char* tmp = str->pt;
	char last = '\0';
	char c = *tmp;
	while (c != '\0') {
		char top = vs_char_stack_get_top(stack);
		if (top == '"' && (c != '"' || (c == '"' && last == '\\')))  //字符串内部
		{
			//printf("content:%c\n", c);
			if (flag == 2) {
				vs_string_append(key, c);
			}
			else if(flag == 4 || flag == 5)
			{
				vs_string_append(value, c);
			}
		}
		else if (flag == 5)  //value为object或者array
		{
			vs_string_append(value, c);
			if (c == '{' || c == '[') {
				vs_char_stack_push(stack, c);
			} else if (c == '}' || c == ']') {
				vs_char_stack_pop(stack);
				if (stack->length == 1)  //值结束
						{
					flag = 3;
				}
			} else if (c == '"') {
				if (top == '"') {
					vs_char_stack_pop(stack);
				} else {
					vs_char_stack_push(stack, c);
				}
			}
		}
		else    //字符串外部的字符，有特殊含义
		{
			switch (c) {
			case '{': {
				if (stack->length > 0)   //第二层
						{
					flag = 5;
					vs_string_append(value, c);
				}
				vs_char_stack_push(stack, c);
				break;
			}
			case '[': {
				if (stack->length > 0)   //第二层
						{
					flag = 5;
					vs_string_append(value, c);
				}
				vs_char_stack_push(stack, c);
				break;
			}
			case '}':
			{

				vs_json_object_append(object, key, value);
				vs_string_clear(key);
				vs_string_clear(value);

				vs_char_stack_pop(stack);
				break;
			}
			case '"':
			{
				char top = vs_char_stack_get_top(stack);
				if (top == '"')  //说明字符串结束
						{
					vs_char_stack_pop(stack);

					if (flag == 2)   //key结束
							{
						flag = 1;
					} else if (flag == 4)   //value结束
							{
						flag = 3;
						vs_string_append(value, c);
					}
				} else    //字符串开始
				{
					if (flag == 1)   //key开始
							{
						flag = 2;
					} else if (flag == 3)   //value开始
							{
						vs_string_append(value, c);
						flag = 4;
					}
					vs_char_stack_push(stack, c);
				}
				break;
			}
			case ':': {
				flag = 3;
				break;
			}
			case ',':   //值的结束
			{
				flag = 1;

				vs_json_object_append(object, key, value);
				vs_string_clear(key);
				vs_string_clear(value);
				break;
			}
			default: {
				if (flag == 3 && c != ' ')   //值的开始
						{
					flag = 4;
					vs_string_append(value, c);
				} else if (flag == 4)   //值
						{
					if (c == ' ')    //值中如果遇到空格，则忽略，这儿肯定在字符串的外部
							{
						flag = 3;
					} else {
						vs_string_append(value, c);
					}
				}
			}
			}
		}
		//printf("char:%c, flag:%d\n", c, flag);
		tmp++;
		last = c;   //设置上一个字符
		c = *tmp;   //更新当前字符
	}
	//销毁栈
	vs_char_stack_destroy(stack);

	//销毁临时的key和value
	vs_string_destroy(key);
	vs_string_destroy(value);

	return object;
}

/**
 * 对象转换成字符串
 */
struct VsString* vs_json_object_to_string(struct VsJsonObject* object) {
	VsString* str = vs_string_init("{");
	if (object != NULL) {
		int i = 0;
		while (i < object->length) {
			if (i > 0) {
				vs_string_append(str, ',');
			}
			struct VsString* kvStr = vs_json_kv_to_string(*(object->list + i));
			vs_string_append(str, kvStr);
			vs_string_destroy(kvStr);
			i++;
		}
	}
	vs_string_append(str, '}');
	return str;
}

void vs_json_object_destroy(struct VsJsonObject* object) {
	if (object != NULL) {
		if (object->length > 0)  //如果有键值对，则销毁键值对
				{
			int i = 0;
			while (i < object->length) {
				vs_json_kv_destroy(*(object->list + i));
				i++;
			}
		}
		free(object->list);
	}
	free(object);
}

/**
 * 在json对象后面添加键值对
 */
void vs_json_object_append(struct VsJsonObject* object, struct VsJsonKv* kv) {
	if (object->length == object->volume)    //容量已满，扩充容量
	{
		int appendVolume = (int) (VS_JSON_OBJECT_INC_PER * object->volume);
		int newVolume = object->volume + appendVolume;
		object->list = (struct VsJsonKv**) realloc(object->list,
				sizeof(struct VsJsonKv *) * newVolume);
		object->volume = newVolume;
	}
	//追加在末尾
	*(object->list + object->length) = kv;
	object->length++;
}

/**
 * 在json对象后面添加键值对,if key is null, nothing will happen.
 * @param object
 * @param key
 * @param value
 */
void vs_json_object_append(struct VsJsonObject* object, struct VsString* key,
		struct VsString* value) {
	if(key != NULL && key->length > 0)
	{
		struct VsJsonKv* kv = vs_json_kv_init(key, value);
		vs_json_object_append(object, kv);
	}
}

/**
 * 初始化一个json的值
 */
struct VsJsonValue* vs_json_value_init(VsString* str) {
	struct VsJsonValue* jsonValue = (struct VsJsonValue*) malloc(
			sizeof(VsJsonValue));
	jsonValue->type = -1;
	if (str == NULL) {
		jsonValue->type = VS_JSON_VALUE_TYPE_NULL;
	} else {
		char start = *(str->pt);
		if (start == '"')    //字符串类型
				{
			struct VsString* value = vs_string_sub(str, 1, str->length - 2);
			jsonValue->type = VS_JSON_VALUE_TYPE_STRING;
			jsonValue->strValue = value;
		} else if (start == '{')   //对象
				{
			jsonValue->type = VS_JSON_VALUE_TYPE_OBJECT;
			struct VsJsonObject* object = vs_json_object_init(str);
			jsonValue->objectValue = object;
		} else if (start == '[')   //数组
				{
			jsonValue->type = VS_JSON_VALUE_TYPE_ARRAY;
			struct VsJsonArray* array = vs_json_array_init(str);
			jsonValue->arrayValue = array;
		} else if (start == 'n' || start == 'N') //null
				{
			jsonValue->type = VS_JSON_VALUE_TYPE_NULL;
		} else    //整数或者浮点数
		{
			if (vs_string_index_of(str, '.') > -1)    //浮点
					{
				jsonValue->type = VS_JSON_VALUE_TYPE_DOUBLE;
				jsonValue->doubleValue = vs_util_str_to_double(str);
			} else    //long
			{
				jsonValue->type = VS_JSON_VALUE_TYPE_LONG;
				jsonValue->longValue = vs_util_str_to_long(str);
			}
		}
	}
	return jsonValue;
}

/**
 * json的值转换成string
 */
struct VsString* vs_json_value_to_string(struct VsJsonValue* value) {
	struct VsString* str = vs_string_init(NULL);
	if (value != NULL) {
		if (value->type == VS_JSON_VALUE_TYPE_STRING) {
			vs_string_append(str, '"');
			vs_string_append(str, value->strValue);
			vs_string_append(str, '"');
		} else if (value->type == VS_JSON_VALUE_TYPE_LONG) {
			vs_string_append(str, value->longValue);
		} else if (value->type == VS_JSON_VALUE_TYPE_DOUBLE) {
			vs_string_append(str, value->doubleValue);
		} else if (value->type == VS_JSON_VALUE_TYPE_NULL) {
			vs_string_append(str, "null");
		} else if (value->type == VS_JSON_VALUE_TYPE_OBJECT) {
			struct VsString* objectStr = vs_json_object_to_string(
					value->objectValue);
			vs_string_append(str, objectStr);
			vs_string_destroy(objectStr);
		} else if (value->type == VS_JSON_VALUE_TYPE_ARRAY) {
			struct VsString* arrayStr = vs_json_array_to_string(
					value->arrayValue);
			vs_string_append(str, arrayStr);
			vs_string_destroy(arrayStr);
		}
	}
	return str;
}

/**
 * 销毁一个json的值
 */
void vs_json_value_destroy(struct VsJsonValue* value) {
	if (value != NULL) {
		if (value->type == VS_JSON_VALUE_TYPE_STRING) {
			vs_string_destroy(value->strValue);
		} else if (value->type == VS_JSON_VALUE_TYPE_OBJECT) {
			vs_json_object_destroy(value->objectValue);
		} else if (value->type == VS_JSON_VALUE_TYPE_ARRAY) {
			vs_json_array_destroy(value->arrayValue);
		}
	}
	free(value);
}

/**
 * 打印json的值类型
 */
void vs_json_value_print(struct VsJsonValue* value) {
	if (value != NULL) {
		printf("value type:%d----------\n", value->type);
		if (value->type == VS_JSON_VALUE_TYPE_STRING) {
			vs_string_print(value->strValue);
		} else if (value->type == VS_JSON_VALUE_TYPE_LONG) {
			printf("%ld\n", value->longValue);
		} else if (value->type == VS_JSON_VALUE_TYPE_DOUBLE) {
			printf("%lf\n", value->doubleValue);
		} else if (value->type == VS_JSON_VALUE_TYPE_NULL) {
			printf("null\n");
		}
	}
}

/**
 * 初始化一个键值对
 */
struct VsJsonKv* vs_json_kv_init(struct VsString* key, struct VsString* value) {
	struct VsJsonKv* kv = (struct VsJsonKv*) malloc(sizeof(struct VsJsonKv));
	kv->key = vs_string_init(key->pt);
	kv->value = vs_json_value_init(value);
	return kv;
}

/**
 * 初始化一个键值对
 */
struct VsJsonKv* vs_json_kv_init(struct VsString* key, const char* value)
{
	struct VsJsonKv* kv = (struct VsJsonKv*) malloc(sizeof(struct VsJsonKv));
	kv->key = vs_string_init(key->pt);
	kv->value = vs_json_value_init(value);
	return kv;
}

/**
 * 键值对转换成字符串
 */
struct VsString* vs_json_kv_to_string(struct VsJsonKv* kv) {
	struct VsString* str = vs_string_init("\"");
	vs_string_append(str, kv->key);
	vs_string_append(str, "\":");

	struct VsString* valueStr = vs_json_value_to_string(kv->value);
	vs_string_append(str, valueStr);
	vs_string_destroy(valueStr);

	return str;
}

/**
 * 销毁一个键值对
 */
void vs_json_kv_destroy(struct VsJsonKv* kv) {
	if (kv != NULL) {
		vs_string_destroy(kv->key);
		vs_json_value_destroy(kv->value);
	}
	free(kv);
}

/**
 * 初始化json数组
 */
struct VsJsonArray* vs_json_array_init(struct VsString* str) {
	struct VsJsonArray* jsonArray = (struct VsJsonArray*) malloc(
			sizeof(struct VsJsonArray));
	jsonArray->length = 0;
	jsonArray->volume = VS_JSON_OBJECT_INIT_VOLUME;
	jsonArray->list = (struct VsJsonValue**) malloc(
			sizeof(struct VsJsonValue *) * jsonArray->volume);
	if(str->length == 2)	//only two char, init an empty array
	{
		return jsonArray;
	}
	//初始化一个栈
	VsCharStack* stack = vs_char_stack_init();
	VsString* valueStr = vs_string_init(NULL);   //存储临时的value
	char* tmp = str->pt;
	char last = '\0';
	char c = *tmp;
	while (c != '\0') {
		char top = vs_char_stack_get_top(stack);
		if (top == '"' && (c != '"' || (c == '"' && last == '\\')))  //字符串内部
				{
			vs_string_append(valueStr, c);
		} else    //字符串外部的字符，有特殊含义
		{
			switch (c) {
			case ' ': {
				break;
			}
			case '{': {
				vs_string_append(valueStr, c);
				vs_char_stack_push(stack, c);
				break;
			}
			case '[': {
				if (stack->length > 0)   //第二层
						{
					vs_string_append(valueStr, c);
				}
				vs_char_stack_push(stack, c);
				break;
			}
			case '}': {
				vs_char_stack_pop(stack);
				vs_string_append(valueStr, c);
				break;
			}
			case ']': {
				vs_char_stack_pop(stack);
				if (stack->length == 0)  //当栈的长度为0时，值的结束
						{
					struct VsJsonValue* value = vs_json_value_init(valueStr);
					vs_json_array_append(jsonArray, value);
					vs_string_clear(valueStr);
				} else {
					vs_string_append(valueStr, c);
				}
				break;
			}
			case '"': {
				char top = vs_char_stack_get_top(stack);
				if (top == '"')  //说明字符串结束
						{
					vs_char_stack_pop(stack);
				} else    //字符串开始
				{
					vs_char_stack_push(stack, c);
				}
				vs_string_append(valueStr, c);
				break;
			}
			case ',':   //值的结束
			{
				if (stack->length == 1)  //当栈的长度为1时，值的结束
						{
					struct VsJsonValue* value = vs_json_value_init(valueStr);
					vs_json_array_append(jsonArray, value);
					vs_string_clear(valueStr);
				} else    //值进行中，追加到值
				{
					vs_string_append(valueStr, c);
				}
				break;
			}
			default: {
				vs_string_append(valueStr, c);
			}
			}
		}
		//printf("char:%c\n", c);
		tmp++;
		last = c;   //设置上一个字符
		c = *tmp;   //更新当前字符
	}
	//销毁栈
	vs_char_stack_destroy(stack);
	//销毁临时的key和value
	vs_string_destroy(valueStr);
	return jsonArray;
}

/**
 * 初始化json数组
 */
struct VsJsonArray* vs_json_array_init(const char* str)
{
	struct VsString* arrayStr = vs_string_init(str);
	struct VsJsonArray* array = vs_json_array_init(arrayStr);
	vs_string_destroy(arrayStr);
	return array;
}

/**
 * 初始化json数组
 */
struct VsJsonArray* vs_json_array_init(long* array, long length)
{
	struct VsJsonArray* jsonArray = vs_json_array_init("[]");
	for(long i = 0; i < length; i++)
	{
		struct VsJsonValue* value = vs_json_value_init(*(array + i));
		vs_json_array_append(jsonArray, value);
	}
	return jsonArray;
}

/**
 * 在json数组后面添加value
 */
void vs_json_array_append(struct VsJsonArray* array,
		struct VsJsonValue* value) {
	if (array->length == array->volume)    //容量已满，扩充容量
	{
		int appendVolume = (int) (VS_JSON_OBJECT_INC_PER * array->volume);
		int newVolume = array->volume + appendVolume;
		array->list = (struct VsJsonValue**) realloc(array->list,
				sizeof(struct VsJsonValue *) * newVolume);
		array->volume = newVolume;
	}
	//追加在末尾
	*(array->list + array->length) = value;
	array->length++;
}

/**
 * 销毁一个数组
 */
void vs_json_array_destroy(struct VsJsonArray* array) {
	if (array != NULL) {
		int i = 0;
		while (i < array->length) {
			vs_json_value_destroy(*(array->list + i));
			i++;
		}
		free(array->list);
	}
	free(array);
}

/**
 * 在json数组转换乘字符串
 */
struct VsString* vs_json_array_to_string(struct VsJsonArray* array) {
	struct VsString* str = vs_string_init("[");
	if (array != NULL) {
		int i = 0;
		while (i < array->length) {
			if (i > 0) {
				vs_string_append(str, ',');
			}
			struct VsString* valueStr = vs_json_value_to_string(
					*(array->list + i));
			vs_string_append(str, valueStr);
			vs_string_destroy(valueStr);
			i++;
		}
	}
	vs_string_append(str, ']');
	return str;
}

/**
 * 设置json的值
 */
void vs_json_object_set_by_path(struct VsJsonObject* object,
		struct VsString* path, struct VsJsonValue* value) {
	struct VsStringList* keyList = vs_string_split(path, '.');
	struct VsJsonKv* kv = vs_json_object_get_kv_upsert(object, keyList);
	struct VsString* lastKey = vs_string_list_get(keyList,
			keyList->length - 1);
	if (kv->value->type == VS_JSON_VALUE_TYPE_ARRAY
			&& vs_string_start_with(lastKey, "["))
	{
		struct VsString* trueKey = vs_string_sub(lastKey, 1,
				lastKey->length - 2);
		long index = vs_util_str_to_long(trueKey);
		//设置对应的索引值为目标value
		vs_json_array_set(kv->value->arrayValue, index, value);
		vs_string_destroy(trueKey);
	}
	else
	{
		struct VsJsonValue* oldValue = kv->value;
		kv->value = value;
		vs_json_value_destroy(oldValue);
	}
	vs_string_list_destroy(keyList);
}

/**
 * 设置json的值
 */
void vs_json_object_set_by_path(struct VsJsonObject* object, const char* path, struct VsJsonValue* value)
{
	struct VsString* strPath = vs_string_init(path);
	vs_json_object_set_by_path(object, strPath, value);
	vs_string_destroy(strPath);
}

/**
 * 设置json的值
 */
void vs_json_object_set_by_path(struct VsJsonObject* object, const char* path, const char* value)
{
	struct VsString* strPath = vs_string_init(path);
	struct VsJsonValue* jsonValue = vs_json_value_init(value);
	vs_json_object_set_by_path(object, strPath, jsonValue);
	vs_string_destroy(strPath);
}

/**
 * 设置json的值
 */
void vs_json_object_set_string_by_path(struct VsJsonObject* object, const char* path, const char* value)
{
	struct VsString* strPath = vs_string_init(path);
	struct VsJsonValue* jsonValue = vs_json_value_init_string(value);
	vs_json_object_set_by_path(object, strPath, jsonValue);
	vs_string_destroy(strPath);
}

/**
 * 设置json的值
 */
void vs_json_object_set_by_path(struct VsJsonObject* object, const char* path, long value)
{
	struct VsString* strPath = vs_string_init(path);
	struct VsJsonValue* jsonValue = vs_json_value_init(value);
	vs_json_object_set_by_path(object, strPath, jsonValue);
	vs_string_destroy(strPath);
}

/**
 * 设置json的值
 */
void vs_json_object_set_by_path(struct VsJsonObject* object, const char* path, double value)
{
	struct VsString* strPath = vs_string_init(path);
	struct VsJsonValue* jsonValue = vs_json_value_init(value);
	vs_json_object_set_by_path(object, strPath, jsonValue);
	vs_string_destroy(strPath);
}

/**
 * 获得json的值
 */
struct VsJsonValue* vs_json_object_get_by_path(struct VsJsonObject* object,
		struct VsString* path) {
	struct VsJsonValue* value = NULL;
	struct VsStringList* keyList = vs_string_split(path, '.');
	struct VsJsonKv* kv = vs_json_object_get_kv(object, keyList);
	if (kv != NULL) {
		struct VsString* lastKey = vs_string_list_get(keyList,
				keyList->length - 1);
		if (vs_string_start_with(lastKey, "[")) {
			value = vs_json_value_get(kv->value, lastKey);
		} else {
			value = kv->value;
		}
	}
	vs_string_list_destroy(keyList);    //销毁字符串
	return value;
}

/**
 * 获得json的值
 */
struct VsJsonValue* vs_json_object_get_by_path(struct VsJsonObject* object, const char* path)
{
	struct VsString* str = vs_string_init(path);
	struct VsJsonValue* value = vs_json_object_get_by_path(object, str);
	vs_string_destroy(str);
	return value;
}

/**
 * 获得json对应键的键值对，如果以数组结束，则返回上一级的kv，
 * 比如如果key为obj.[0]，则实际返回key:obj,value:[]
 */
struct VsJsonKv* vs_json_object_get_kv_by_path(struct VsJsonObject* object,
		struct VsString* path) {
	struct VsStringList* keyList = vs_string_split(path, '.');
	struct VsJsonKv* kv = vs_json_object_get_kv(object, keyList);
	vs_string_list_destroy(keyList);    //销毁字符串
	return kv;
}

/**
 * 获得json对应键的键值对
 */
struct VsJsonKv* vs_json_object_get_kv(struct VsJsonObject* object,
		struct VsStringList* keyList) {
	if (keyList->length == 0)    //空字符串
			{
		return NULL;
	}
	struct VsString* key = vs_string_list_get(keyList, 0);
	struct VsJsonKv* kv = vs_json_object_get_kv(object, key);
	if (kv == NULL)   //没有对应的键值
	{
		return NULL;
	}
	struct VsJsonValue* value = kv->value;
	//一值遍历，直到没找到匹配值，或者到最后一个key
	for (int i = 1; i < keyList->length; i++) {
		key = vs_string_list_get(keyList, i);
		if (value->type == VS_JSON_VALUE_TYPE_ARRAY)     //数组的话，直接到下一个键
		{
			value = vs_json_value_get(value, key);
			if (value == NULL && i != keyList->length - 1) //如果是最后一个的话，继续返回上一级的kv值
					{
				kv = NULL;
				break;
			}
		}
		else if (value->type == VS_JSON_VALUE_TYPE_OBJECT)   //对象，记录当前键值
		{
			kv = vs_json_object_get_kv(value->objectValue, key);
			if (kv == NULL) {
				break;
			} else {
				value = kv->value;
			}
		}
		else    //不合法的键值路径
		{
			kv = NULL;
			break;
		}
	}
	return kv;
}

/**
 * 获得json对应键的键值对
 */
struct VsJsonKv* vs_json_object_get_kv_upsert(struct VsJsonObject* object,
		struct VsStringList* keyList) {
	if (keyList->length == 0)    //空字符串
	{
		return NULL;
	}
	struct VsString* key = vs_string_list_get(keyList, 0);
	struct VsString* nextKey = vs_string_list_get(keyList, 1);    //下一个键值对
	struct VsJsonKv* kv = vs_json_object_get_kv(object, key);
	if (kv == NULL)   //没有对应的键值
	{
		struct VsJsonKv* newKv = NULL;
		if (nextKey != NULL && vs_string_start_with(nextKey, "["))  //说明下一个是数组访问
		{
			newKv = vs_json_kv_init(key, "[]");
		}
		else
		{
			if(nextKey == NULL)
			{
				newKv = vs_json_kv_init(key, "null");
			}
			else
			{
				newKv = vs_json_kv_init(key, "{}");
			}
		}
		vs_json_object_append(object, newKv);
		kv = newKv;
	}
	struct VsJsonValue* value = kv->value;
	for(int i = 1; i < keyList->length; i++)
	{
		key = vs_string_list_get(keyList, i);
		nextKey = vs_string_list_get(keyList, i + 1);

		struct VsJsonValue* nextValue = vs_json_value_get(value, key);
		if(nextValue == NULL)	//键值对不存在
		{
			if(vs_string_start_with(key, "["))	//current key is array index
			{
				struct VsString* trueKey = vs_string_sub(key, 1, key->length - 2);
				long index;
				if (trueKey->length == 0)
				{
					index = 0L;
				}
				else
				{
					index = vs_util_str_to_long(trueKey);
				}
				vs_string_destroy(trueKey);
				struct VsJsonValue* newValue;
				if(nextKey == NULL)
				{
					newValue = vs_json_value_init_null();
				}
				else
				{
					newValue = vs_json_value_init("{}");
				}
				vs_json_array_set(value->arrayValue, index, newValue);

				value = newValue;	//set the value to remember the current value
			}
			else	//current key is object key
			{
				struct VsJsonKv* newKv = NULL;
				if (nextKey != NULL && vs_string_start_with(nextKey, "["))  //说明下一个是数组访问
				{
					newKv = vs_json_kv_init(key, "[]");
				}
				else
				{
					if(nextKey == NULL)
					{
						newKv = vs_json_kv_init(key, "null");
					}
					else
					{
						newKv = vs_json_kv_init(key, "{}");
					}
				}
				vs_json_object_append(value->objectValue, newKv);
				kv = newKv;

				value = kv->value;	//set the value to remember the current value
			}
		}
		else
		{
			if(value->type == VS_JSON_VALUE_TYPE_OBJECT)	//object, change the kv
			{
				kv = vs_json_object_get_kv(value->objectValue, key);
			}
			value = nextValue;
		}
	}
	return kv;
}

/**
 *  获得键值对，如果不存在则会创建
 * @param object
 * @param path
 */
struct VsJsonKv* vs_json_object_get_kv_upsert(struct VsJsonObject* object, const char* path)
{
	struct VsString* str = vs_string_init(path);
	struct VsStringList* keyList = vs_string_split(str, '.');
	struct VsJsonKv* kv = vs_json_object_get_kv_upsert(object, keyList);
	vs_string_destroy(str);
	vs_string_list_destroy(keyList);
	return kv;
}

/**
 * 获得json的值
 */
struct VsJsonValue* vs_json_object_get(struct VsJsonObject* object,
		struct VsString* key) {
	struct VsJsonKv* kv = vs_json_object_get_kv(object, key);
	if (kv != NULL) {
		return kv->value;
	} else {
		return NULL;
	}
}

/**
 * 获得json的值
 */
struct VsJsonValue* vs_json_object_get(struct VsJsonObject* object, const char* key)
{
	struct VsString* strKey = vs_string_init(key);
	struct VsJsonValue* value = vs_json_object_get(object, strKey);
	vs_string_destroy(strKey);
	return value;
}

/**
 * 设置json的值
 */
void vs_json_object_set(struct VsJsonObject* object, struct VsString* key,
		struct VsJsonValue* value) {
	struct VsJsonKv* kv = vs_json_object_get_kv(object, key);
	if (kv == NULL)  //如果没有这个键，那么，新增这个键值对
	{
		kv = vs_json_kv_init(key);
		kv->value = value;

		vs_json_object_append(object, kv);
	} else {
		struct VsJsonValue* oldValue = kv->value;
		kv->value = value;
		vs_json_value_destroy(oldValue);
	}
}

/**
 * 设置json的值
 */
void vs_json_object_set(struct VsJsonObject* object, const char* key, struct VsJsonValue* value)
{
	struct VsString* keyStr = vs_string_init(key);
	vs_json_object_set(object, keyStr, value);
	vs_string_destroy(keyStr);
}

/**
 * 获得json对应键的键值对
 */
struct VsJsonKv* vs_json_object_get_kv(struct VsJsonObject* object,
		struct VsString* key) {
	struct VsJsonKv** kvList = object->list;
	for (int i = 0; i < object->length; i++) {
		struct VsJsonKv* kv = *(kvList + i);
		if (vs_string_equal(kv->key, key)) {
			return kv;
		}
	}
	return NULL;
}

/**
 * 获得json array的值
 */
struct VsJsonValue* vs_json_array_get(struct VsJsonArray* array, int index) {
	if (index < array->length) {
		return *(array->list + index);
	} else {
		return NULL;
	}
}

/**
 * 获得json value的值
 */
struct VsJsonValue* vs_json_value_get(struct VsJsonValue* value,
		struct VsString* key) {
	if (value->type == VS_JSON_VALUE_TYPE_OBJECT)
	{
		return vs_json_object_get(value->objectValue, key);
	}
	else if (value->type == VS_JSON_VALUE_TYPE_ARRAY)
	{
		struct VsString* trueKey = vs_string_sub(key, 1, key->length - 2);
		if (trueKey->length == 0)
		{
			vs_string_destroy(trueKey);
			return NULL;
		}
		else
		{
			long index = vs_util_str_to_long(trueKey);
			vs_string_destroy(trueKey);
			return vs_json_array_get(value->arrayValue, index);
		}
	}
	else
	{
		return NULL;
	}
}

/**
 * 初始化一个键值对,值为空
 */
struct VsJsonKv* vs_json_kv_init(struct VsString* key) {
	struct VsJsonKv* kv = (struct VsJsonKv*) malloc(sizeof(struct VsJsonKv));
	kv->key = vs_string_init(key->pt);
	kv->value = NULL;
	return kv;
}

/**
 * 初始化一个json的值
 */
struct VsJsonValue* vs_json_value_init(const char* str) {
	struct VsString* newStr = vs_string_init(str);
	struct VsJsonValue* value = vs_json_value_init(newStr);
	vs_string_destroy(newStr);
	return value;
}

/**
 * 设置json的值
 */
void vs_json_object_set(struct VsJsonObject* object, const char* key,
		const char* value) {
	struct VsString* strKey = vs_string_init(key);
	struct VsJsonValue* jsonValue = vs_json_value_init(value);
	vs_json_object_set(object, strKey, jsonValue);
	vs_string_destroy(strKey);
}

/**
 * 设置json的值
 */
void vs_json_object_set_string(struct VsJsonObject* object, const char* key, const char* value)
{
	struct VsString* strKey = vs_string_init(key);
	struct VsJsonValue* jsonValue = vs_json_value_init_string(value);
	vs_json_object_set(object, strKey, jsonValue);
	vs_string_destroy(strKey);
}

/**
 * 设置json的值
 */
void vs_json_object_set(struct VsJsonObject* object, const char* key, long value)
{
	struct VsString* strKey = vs_string_init(key);
	struct VsJsonValue* jsonValue = vs_json_value_init(value);
	vs_json_object_set(object, strKey, jsonValue);
	vs_string_destroy(strKey);
}

/**
 * 设置json的值
 */
void vs_json_object_set(struct VsJsonObject* object, const char* key, double value)
{
	struct VsString* strKey = vs_string_init(key);
	struct VsJsonValue* jsonValue = vs_json_value_init(value);
	vs_json_object_set(object, strKey, jsonValue);
	vs_string_destroy(strKey);
}

/**
 * 设置json array的值
 */
void vs_json_array_set(struct VsJsonArray* array, int index,
		struct VsJsonValue* value) {
	if (array != NULL) {
		struct VsJsonValue* oldValue = vs_json_array_get(array, index);
		if (oldValue == NULL) {
			for (int i = array->length; i < index; i++) {
				vs_json_array_append(array, vs_json_value_init_null());
			}
			vs_json_array_append(array, value);
		} else {
			*(array->list + index) = value;
			vs_json_value_destroy(oldValue);
		}
	}
}

/**
 * 初始化一个json的值
 */
struct VsJsonValue* vs_json_value_init_null() {
	struct VsJsonValue* jsonValue = (struct VsJsonValue*) malloc(
			sizeof(VsJsonValue));
	jsonValue->type = VS_JSON_VALUE_TYPE_NULL;
	return jsonValue;
}

/**
 * 初始化一个json的值
 */
struct VsJsonValue* vs_json_value_init(struct VsJsonArray* array)
{
	struct VsJsonValue* jsonValue = (struct VsJsonValue*) malloc(
			sizeof(VsJsonValue));
	jsonValue->type = VS_JSON_VALUE_TYPE_ARRAY;
	jsonValue->arrayValue = array;
	return jsonValue;
}

/**
 * 初始化一个json的值
 */
struct VsJsonValue* vs_json_value_init_string(const char* str)
{
	struct VsJsonValue* jsonValue = (struct VsJsonValue*) malloc(
				sizeof(VsJsonValue));
	jsonValue->type = VS_JSON_VALUE_TYPE_STRING;
	struct VsString* value = vs_string_init(str);
	jsonValue->strValue = value;
	return jsonValue;
}

/**
 * 初始化一个json的值
 */
struct VsJsonValue* vs_json_value_init(long value)
{
	struct VsJsonValue* jsonValue = (struct VsJsonValue*) malloc(
					sizeof(VsJsonValue));
	jsonValue->type = VS_JSON_VALUE_TYPE_LONG;
	jsonValue->longValue = value;
	return jsonValue;
}

/**
 * 初始化一个json的值
 */
struct VsJsonValue* vs_json_value_init(double value)
{
	struct VsJsonValue* jsonValue = (struct VsJsonValue*) malloc(
						sizeof(VsJsonValue));
	jsonValue->type = VS_JSON_VALUE_TYPE_DOUBLE;
	jsonValue->doubleValue = value;
	return jsonValue;
}
