#ifndef VS_STRING
#define VS_STRING

/**
 * 字符串的初始化长度
 */
#define VS_STRING_INIT_VOLUME 80L

/**
 * 当字符串长度不够时，字符串增长的百分比
 */
#define VS_STRING_INC_PER 0.3

/**
 * 字符串最小扩充长度
 */
#define VS_STRING_MIN_INC_VOLUME 10L

/**
 * 字符串数组的初始化长度
 */
#define VS_STRING_LIST_INIT_VOLUME 10L

/**
 * 当字符串数组长度不够时，字符串增长的百分比
 */
#define VS_STRING_LIST_INC_PER 0.3

/**
 * 字符串数组最小扩充长度
 */
#define VS_STRING_LIST_MIN_INC_VOLUME 6L

/**
 * 字符串
 */
struct VsString
{
    char *pt;
    long volume;
    long length;
};

/**
 * 字符串数组
 */
struct VsStringList {
    struct VsString** pt;
    long length;
    long volume;
};

/**
 * 初始化一个字符串
 * @param src 源字符串
 * @return VsString * 结构体指针
 */
VsString* vs_string_init(const char *src);

/**
 * 初始化一个字符串，容量为volume
 * @param long 容量
 * @return VsString * 结构体指针
 */
VsString* vs_string_init(const char *src, long length, long volume);

/**
 * 初始化一个空字符串
 * @return VsString * 结构体指针
 */
VsString* vs_string_init();

/**
 * 销毁一个字符串
 * @param str VsString * 结构体指针
 * @return void
 */
void vs_string_destroy(VsString* str);

/**
 * 清空一个字符串
 * @param str VsString * 结构体指针
 * @return void
 */
void vs_string_clear(VsString* str);

/**
 * 判断两个字符串是否相等
 * @param str VsString * 结构体指针
 * @param dest VsString * 结构体指针
 * @return void
 */
bool vs_string_equal(VsString* src, VsString* dest);

/**
 * 判断字符串是否以start开始
 * @param str VsString * 结构体指针
 * @param start char *
 * @return void
 */
bool vs_string_start_with(VsString* src, const char* start);

/**
 * 在字符串末尾追加内容
 * @param str
 * @param src
 */
void vs_string_append(VsString* str, const char *src);

/**
 * 在字符串末尾追加long型数据
 * @param str
 * @param value
 */
void vs_string_append(VsString* str, long value);

/**
 * 在字符串末尾追加double型数据
 * @param str
 * @param value
 */
void vs_string_append(VsString* str, double value);

/**
 * 在字符串末尾追加char型数据
 * @param str
 * @param value
 */
void vs_string_append(VsString* str, char value);

/**
 * 在字符串末尾追加内容
 * @param str
 * @param src
 * @param length
 */
void vs_string_append(VsString* str, const char *src, int length);

/**
 * 把src字符串的内容追加到dest的末尾
 * @param dest
 * @param src
 */
void vs_string_append(VsString* dest, VsString* src);

/**
 * 获得指定索引的字符，
 * 如果索引不存在，则返回'\0'
 */
char vs_string_char_at(struct VsString* src, long index);

/**
 * 打印目标字符串
 * @param str
 */
void vs_string_print(VsString* str);

/**
 * 获得目标字符串的子串
 */
struct VsString* vs_string_sub(VsString* str, int start, int end);

/**
 * 获得char c在字符串中的位置，如果没有则返回-1
 */
int vs_string_index_of(VsString* str, char c);

/**
 * 分隔字符串
 */
struct VsStringList* vs_string_split(struct VsString* str, char c);

/**
 * 字符串复制
 */
void string_copy(const char *src, char *dest);

/**
 * 字符串复制
 * @param src
 * @param srcLength
 * @param dest
 * @param start 目标串的起始地址
 */
void string_copy(const char *src, int srcLength, char *dest, int start);

/**
 * 获得char *代表的字符串长度
 * @param src
 */
long string_length(const char *src);

/**
 * 初始化一个字符串列表
 */
struct VsStringList* vs_string_list_init();

/**
 * 销毁一个字符串数组
 */
void vs_string_list_destroy(struct VsStringList* list);

/**
 * 在字符串列表末尾追加元素
 */
void vs_string_list_append(struct VsStringList* list, struct VsString* str);

/**
 * 获取目标索引的字符串
 */
struct VsString* vs_string_list_get(struct VsStringList* list, int index);

#endif


