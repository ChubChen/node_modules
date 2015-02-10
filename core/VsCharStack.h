#ifndef VS_CHAR_STACK
#define VS_CHAR_STACK

/**
 * VsCharStack主要实现char类型的栈
 */


/**
 * 初始化长度
 */
#define VS_STACK_INIT_VOLUME 80

/**
 * 长度不够时，增长的百分比
 */
#define VS_STACK_INC_PER 0.3

/**
 * 最小扩充长度
 */
#define VS_STACK_MIN_INC_VOLUME 10


struct VsCharStack {
    char *pt;
    int volume;
    int length;
};

/**
 * 初始化一个字符栈
 */
VsCharStack* vs_char_stack_init();

/**
 * 销毁一个字符栈
 */
void vs_char_stack_destroy(VsCharStack* stack);

/**
 * 入栈
 */
void vs_char_stack_push(VsCharStack* stack, char c);

/**
 * 出栈
 */
char vs_char_stack_pop(VsCharStack* stack);


/**
 * 遍历整个栈
 */
void vs_char_stack_traverse(VsCharStack* stack);

/**
 * 获得栈顶元素
 */
char vs_char_stack_get_top(VsCharStack* stack);


#endif