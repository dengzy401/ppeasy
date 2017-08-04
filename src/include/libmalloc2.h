


#ifndef _LIBMALLOC_H_
#define _LIBMALLOC_H_


typedef void ( *_Destory )(void *p);

#ifdef __cplusplus
extern "C"
{
#endif
	void    malloc2_setmaxfreesize(INT64 maxSize);
	void    malloc2_getstate(INT64 *pnMemFree, INT64 *pnMemUsed, INT64 *pnMemMax);

	void *  malloc2_align( size_t cb ,int grow_count, int align);
	void *  malloc2( size_t cb );
	void *  realloc2( void *p,size_t cb );
	void	free2(void *p);
	size_t   msize2(void *p);
	int     malloc2_counter();



	void *   SharedMemCreate2( size_t cb,_Destory destroy, int bCached );
	void *   SharedMemCreate( size_t cb );
	size_t   SharedMemSize( void *p );
	INT32     SharedMemAddRef(void *p);
	INT32     SharedMemRelease(void *p);
	INT32    SharedMemCounter();
#ifdef __cplusplus
}
#endif

#endif

