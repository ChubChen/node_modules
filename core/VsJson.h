#ifndef VS_JSON
#define VS_JSON

#include "VsString.h"

/**
 * 长整数类型
 */
#define VS_JSON_VALUE_TYPE_LONG 1

/**
 * 浮点数类型
 */
#define VS_JSON_VALUE_TYPE_DOUBLE 2

/**
 * 字符串类型
 */
#define VS_JSON_VALUE_TYPE_STRING 3

/**
 * 对象
 */
#define VS_JSON_VALUE_TYPE_OBJECT 4

/**
 * 数组
 */
#define VS_JSON_VALUE_TYPE_ARRAY 5

/**
 * null or NULL
 */
#define VS_JSON_VALUE_TYPE_NULL 6

/**
 * json对象key-value对的初始容量
 */
#define VS_JSON_OBJECT_INIT_VOLUME 20

/**
 * json对象key-value对的扩充比率
 */
#define VS_JSON_OBJECT_INC_PER 0.3


/**
 * 代表一个json对象
 */
struct VsJsonObject {
    struct VsJsonKv** list; //这儿是一个指向指针的指针
    int length;
    int volume;
};

/**
 * 代表一个json的对象数组
 */
struct VsJsonArray {
    struct VsJsonValue** list;
    int length;
    int volume;
};

/**
 * 代表一个键值对
 */
struct VsJsonKv {
    struct VsString* key;
    struct VsJsonValue* value;
};

/**
 * 代表一个值
 */
struct VsJsonValue {
    int type;   //类型
    long longValue; //整数及长整数类型时的值
    struct VsString* strValue; //当值是字符串时
    double doubleValue; //当值是浮点数时
    struct VsJsonArray* arrayValue;    //数组
    struct VsJsonObject* objectValue;  //对象
};


/**
 * 初始化一个json对象
 * @param str VsString* 要转成json对象的字符串
 * @return VsJsonObject 目标json对象
 */
struct VsJsonObject* vs_json_object_init(struct VsString* str);

/**
 * 初始化一个json对象
 * @param str VsString* 要转成json对象的字符串
 * @return VsJsonObject 目标json对象
 */
struct VsJsonObject* vs_json_object_init(const char* str);

/**
 * 对象转换成字符串
 */
struct VsString* vs_json_object_to_string(struct VsJsonObject* object);


/**
 * 获得json的值
 */
struct VsJsonValue* vs_json_object_get_by_path(struct VsJsonObject* object, struct VsString* path);

/**
 * 获得json的值
 */
struct VsJsonValue* vs_json_object_get_by_path(struct VsJsonObject* object, const char* path);

/**
 * 获得json的值
 */
struct VsJsonValue* vs_json_object_get(struct VsJsonObject* object, struct VsString* key);

/**
 * 获得json的值
 */
struct VsJsonValue* vs_json_object_get(struct VsJsonObject* object, const char* key);

/**
 * 设置json的值
 */
void vs_json_object_set(struct VsJsonObject* object, struct VsString* key, struct VsJsonValue* value);

/**
 * 设置json的值
 */
void vs_json_object_set(struct VsJsonObject* object, const char* key, struct VsJsonValue* value);

/**
 * 设置json的值
 */
void vs_json_object_set(struct VsJsonObject* object, const char* key, const char* value);

/**
 * 设置json的值
 */
void vs_json_object_set_string(struct VsJsonObject* object, const char* key, const char* value);

/**
 * 设置json的值
 */
void vs_json_object_set(struct VsJsonObject* object, const char* key, long value);

/**
 * 设置json的值
 */
void vs_json_object_set(struct VsJsonObject* object, const char* key, double value);

/**
 * 设置json的值
 */
void vs_json_object_set_by_path(struct VsJsonObject* object, struct VsString* path, struct VsJsonValue* value);

/**
 * 设置json的值
 */
void vs_json_object_set_by_path(struct VsJsonObject* object, const char* path, struct VsJsonValue* value);

/**
 * 设置json的值
 */
void vs_json_object_set_by_path(struct VsJsonObject* object, const char* path, const char* value);

/**
 * 设置json的值
 */
void vs_json_object_set_string_by_path(struct VsJsonObject* object, const char* path, const char* value);

/**
 * 设置json的值
 */
void vs_json_object_set_by_path(struct VsJsonObject* object, const char* path, long value);

/**
 * 设置json的值
 */
void vs_json_object_set_by_path(struct VsJsonObject* object, const char* path, double value);

/**
 * 获得json对应键的键值对
 */
struct VsJsonKv* vs_json_object_get_kv(struct VsJsonObject* object, struct VsString* key);

/**
 * 获得json对应键的键值对
 */
struct VsJsonKv* vs_json_object_get_kv(struct VsJsonObject* object, struct VsStringList* keyList);


/**
 * 获得json对应键的键值对,如果不存在对应的键值对,则会新建
 */
struct VsJsonKv* vs_json_object_get_kv_upsert(struct VsJsonObject* object, struct VsStringList* keyList);

/**
 * 获得json对应键的键值对,如果不存在对应的键值对,则会新建
 */
struct VsJsonKv* vs_json_object_get_kv_upsert(struct VsJsonObject* object, const char* path);

/**
 * 获得json对应键的键值对
 */
struct VsJsonKv* vs_json_object_get_kv_by_path(struct VsJsonObject* object, struct VsString* path);

/**
 * 获得json array的值
 */
struct VsJsonValue* vs_json_array_get(struct VsJsonArray* array, int index);

/**
 * 设置json array的值
 */
void vs_json_array_set(struct VsJsonArray* array, int index, struct VsJsonValue* value);


/**
 * 获得json value的值
 */
struct VsJsonValue* vs_json_value_get(struct VsJsonValue* value, struct VsString* key);


/**
 * 销毁一个json对象
 * @param object 要销毁的对象
 */
void vs_json_object_destroy(struct VsJsonObject* object);


/**
 * 在json对象后面添加键值对
 */
void vs_json_object_append(struct VsJsonObject* object, struct VsJsonKv* kv);

/**
 * 在json对象后面添加键值对
 */
void vs_json_object_append(struct VsJsonObject* object, struct VsString* key, struct VsString* value);


/**
 * 初始化一个json的值
 */
struct VsJsonValue* vs_json_value_init(VsString* str);

/**
 * 初始化一个json的值
 */
struct VsJsonValue* vs_json_value_init(const char* str);

/**
 * 初始化一个json的值
 */
struct VsJsonValue* vs_json_value_init(long value);

/**
 * 初始化一个json的值
 */
struct VsJsonValue* vs_json_value_init(double value);

/**
 * 初始化一个json的值
 */
struct VsJsonValue* vs_json_value_init_null();

/**
 * 初始化一个json的值
 */
struct VsJsonValue* vs_json_value_init_string(const char* str);

/**
 * 初始化一个json的值
 */
struct VsJsonValue* vs_json_value_init(struct VsJsonArray* array);

/**
 * json的值转换成string
 */
struct VsString* vs_json_value_to_string(struct VsJsonValue* value);

/**
 * 销毁一个json的值
 */
void vs_json_value_destroy(struct VsJsonValue* value);

/**
 * 打印json的值类型
 */
void vs_json_value_print(struct VsJsonValue* value);

/**
 * 初始化一个键值对
 */
struct VsJsonKv* vs_json_kv_init(struct VsString* key, struct VsString* value);

/**
 * 初始化一个键值对
 */
struct VsJsonKv* vs_json_kv_init(struct VsString* key, const char* value);

/**
 * 初始化一个键值对,值为空
 */
struct VsJsonKv* vs_json_kv_init(struct VsString* key);


/**
 * 键值对转换成字符串
 */
struct VsString* vs_json_kv_to_string(struct VsJsonKv* kv);


/**
 * 销毁一个键值对
 */
void vs_json_kv_destroy(struct VsJsonKv* kv);


/**
 * 初始化json数组
 */
struct VsJsonArray* vs_json_array_init(struct VsString* str);

/**
 * 初始化json数组
 */
struct VsJsonArray* vs_json_array_init(const char* str);

/**
 * 初始化json数组
 */
struct VsJsonArray* vs_json_array_init(long* array, long length);

/**
 * 在json数组后面添加value
 */
void vs_json_array_append(struct VsJsonArray* array, struct VsJsonValue* value);

/**
 * 在json数组转换乘字符串
 */
struct VsString* vs_json_array_to_string(struct VsJsonArray* array);

/**
 * 销毁一个数组
 */
void vs_json_array_destroy(struct VsJsonArray* array);

#endif
