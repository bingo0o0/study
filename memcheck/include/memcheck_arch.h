#ifndef __MEM_CHECK_ARCH_H__
#define __MEM_CHECK_ARCH_H__

#include "memcheck_def.h"

#if defined(__arm__)

#define GET_RETURN_ADDR() \
	size_t ret_addr=0; \
	__asm__( \
	"mov %0, lr" \
	:"=r"(ret_addr) \
	: \
	)

#elif defined(__x86__)

#define GET_RETURN_ADDR() \
	size_t ret_addr=0; \
	mmc_error("do not support")

#elif defined(__x86_64__)

#define GET_RETURN_ADDR() \
	size_t ret_addr=0; \
	mmc_error("do not support")
	
#endif

#endif
