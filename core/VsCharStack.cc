#include <stdio.h>
#include <stdlib.h>

#include "VsCharStack.h"

/**
 * 初始化一个字符栈
 */
VsCharStack* vs_char_stack_init() {
	VsCharStack* stack = (VsCharStack *) malloc(sizeof(VsCharStack));
	stack->pt = (char *) malloc(sizeof(char) * VS_STACK_INIT_VOLUME);
	stack->length = 0;
	stack->volume = VS_STACK_INIT_VOLUME;

	*(stack->pt + stack->length) = '\0';
	return stack;
}

/**
 * 销毁一个字符栈
 */
void vs_char_stack_destroy(VsCharStack* stack) {
	if (stack != NULL) {
		free(stack->pt);
	}
	free(stack);
}

/**
 * 入栈
 */
void vs_char_stack_push(VsCharStack* stack, char c) {
	int newLength = stack->length + 2;  //最后一位留做结束符
	if (newLength > stack->volume) {
		int appendVolume = (int) (VS_STACK_INC_PER * stack->volume);
		if (appendVolume < VS_STACK_MIN_INC_VOLUME) {
			appendVolume = VS_STACK_MIN_INC_VOLUME;
		}
		int newVolume = stack->volume + appendVolume;
		stack->pt = (char *) realloc(stack->pt, sizeof(char) * newVolume);
		stack->volume = newVolume;
	}
	*(stack->pt + stack->length) = c;   //添加到末尾
	*(stack->pt + stack->length + 1) = '\0';
	stack->length++;    //栈的长度+1
}

/**
 * 出栈
 */
char vs_char_stack_pop(VsCharStack* stack) {
	if (stack->length > 0) {
		char c = *(stack->pt + stack->length - 1);
		stack->length--;
		*(stack->pt + stack->length) = '\0';
		return c;
	} else {
		printf("error:no element in stack!\n");
		return '\0';
	}
}

/**
 * 遍历整个栈
 */
void vs_char_stack_traverse(VsCharStack* stack) {
	printf("%s\n", stack->pt);
}

/**
 * 获得栈顶元素
 */
char vs_char_stack_get_top(VsCharStack* stack) {
	if (stack->length == 0) {
		return '\0';
	} else {
		return *(stack->pt + stack->length - 1);
	}
}
