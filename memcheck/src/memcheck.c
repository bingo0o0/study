
#include "memcheck_arch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct memcheck_node
{
	struct memcheck_node *next;
	struct memcheck_node *prev;
	
	size_t caller;
	size_t size;
	
}memcheck_node;


static memcheck_node s_listHead;
static memcheck_node *s_pListHead = NULL;
static memcheck_node *s_pCurNode = NULL;

#ifdef __cplusplus
extern "C" {
#endif


extern void *__real_malloc(size_t size);
extern void __real_free(void *ptr);
extern void *__real_calloc(size_t nmemb, size_t size);
extern void *__real_realloc(void *ptr, size_t size);



static memcheck_node *initListHead()
{
	if (!s_pListHead)
	{
		s_pListHead = &s_listHead;
		memset((void *)s_pListHead, 0, sizeof(memcheck_node));
		
		s_pListHead->next = NULL;
		s_pListHead->prev = s_pListHead;
		
		s_pCurNode = s_pListHead;
	}
	
	return s_pListHead;
}



static BOOL addAllocNode(memcheck_node *pNode)
{
	if (!s_pCurNode)
	{
		initListHead();
	}
	
	pNode->prev = s_pCurNode;
	s_pCurNode->next = pNode;
	s_pCurNode = pNode;
	
	return TRUE;
}


static void delAllocNode(memcheck_node *pNode)
{
	if (pNode == s_pCurNode)
	{
		s_pCurNode = pNode->prev;
	}
	
	if (NULL == pNode->next)
	{
		pNode->prev->next = NULL;
	}
	else{
		pNode->prev->next =  pNode->next;
		pNode->next->prev = pNode->prev;
	}
	
	return;
}


void dumpList()
{
	if (!s_pListHead)
	{
		return;
	}
	
	memcheck_node *pNode = s_pListHead->next;
	int i = 0;
	while(pNode)
	{
		printf("i:%d 	lr:[%p]	size:%Zd\n", i++,(void *)pNode->caller, pNode->size);
		pNode = pNode->next;
	}
	
	printf("\n");
}


void *__wrap_malloc(size_t size)
{
	GET_RETURN_ADDR();
	
	memcheck_node *pNode = NULL;
	if (0 == size)
	{
		mmc_error("param invalid");
		return NULL;
	}
	
	size += sizeof(memcheck_node);
	void *pAddr = __real_malloc(size);
	
	mmc_info("__wrap_malloc : %p \n", pAddr);
	if (pAddr)
	{
		pNode = (memcheck_node *)pAddr;
		pNode->next = NULL;
		pNode->prev = NULL;
		
		pNode->caller = ret_addr;
		pNode->size = size-sizeof(memcheck_node);
		addAllocNode(pNode);
	}
	
	return (void *)(((int8 *)pAddr)+sizeof(memcheck_node));
}




void *__wrap_calloc(size_t nmemb, size_t size)
{
	GET_RETURN_ADDR();
	
	memcheck_node *pNode = NULL;
	if (0==size || 0==nmemb)
	{
		mmc_error("param invalid");
		return NULL;
	}
	
	size = sizeof(memcheck_node) + (size*nmemb);
	void *pAddr = __real_malloc(size);
	if (pAddr)
	{
		pNode = (memcheck_node *)pAddr;
		pNode->next = NULL;
		pNode->prev = NULL;
		
		pNode->caller = ret_addr;
		pNode->size = size-sizeof(memcheck_node);
		addAllocNode(pNode);
	}
	
	pAddr = ((int8 *)pAddr)+sizeof(memcheck_node);
	memset(pAddr, 0, size-sizeof(memcheck_node));
	return (void *)pAddr;
}



void *__wrap_realloc(void *ptr, size_t size)
{
	GET_RETURN_ADDR();
	memcheck_node *pNode = NULL;
	if (!ptr || 0==size)
	{
		mmc_error("param invalid");
		return NULL;
	}
	
	size = sizeof(memcheck_node) + size;
	void *pAddr = (void *)((int8 *)ptr-sizeof(memcheck_node));
	pAddr = __real_realloc(pAddr, size);
	if (pAddr)
	{
		pNode = (memcheck_node *)pAddr;
		pNode->next = NULL;
		pNode->prev = NULL;
		
		pNode->caller = ret_addr;
		pNode->size = size-sizeof(memcheck_node);
		addAllocNode(pNode);
	}
	
	return (void *)(((int8 *)pAddr)+sizeof(memcheck_node)); 
}



void __wrap_free(void *ptr)
{
	printf("__wrap_free entry\n");
	if (ptr)
	{
		memcheck_node *pNode = (memcheck_node *)((int8 *)ptr -sizeof(memcheck_node));
		
		mmc_info("__wrap_free pNode:%p\n", pNode);
		
		delAllocNode(pNode);
		
		__real_free((void *)pNode);
	}
	else{
		printf("__wrap_free \n");
		dumpList();
	}
	
	return;
}




#ifdef __cplusplus
}
#endif











