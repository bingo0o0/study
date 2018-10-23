#ifndef __MEM_CHECK_DEF_H__
#define __MEM_CHECK_DEF_H__

#include <stdio.h>

/*
	重新定义基础数据类型
*/

typedef char int8;
typedef unsigned char uint8;

typedef short int16;
typedef unsigned short uint16;

typedef int int32;
typedef unsigned int uint32;

#define TRUE 1
#define FALSE 0


#ifdef __cplusplus
typedef bool BOOL;
#else
typedef uint32 BOOL;
#endif


#define ORIGINAL "\e[m\n"
#define BLACK "\e[30m"
#define REG "\e[31m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define BLUE "\e[34m"
#define PURPLE "\e[35m"
#define LIGHTBLUE "\e[36m"


#define mmc_info(fmt,...) \
	printf("[%s:%d]"fmt""ORIGINAL, \
		__FILE__, __LINE__, ##__VA_ARGS__)

#define mmc_warn(fmt,...) \
	printf(YELLOW"[%s:%d]"fmt""ORIGINAL, \
		__FILE__, __LINE__, ##__VA_ARGS__)


#define mmc_error(fmt, ...) \
	fprintf(stderr, REG"[%s:%d]"fmt""ORIGINAL, \
		__FILE__, __LINE__, ##__VA_ARGS__)


#endif //\ __MEM_CHECK_DEF_H__

