#ifndef     __SLAB_H__
#define     __SLAB_H__

#include "page.h"

#define KMEM_CACHE_DEFAULT_ORDER    (0)
#define KMEM_CACHE_MAX_ORDER        (5)
#define KMEM_CACHE_SAVE_RATE        (90)
#define KMEM_CACHE_PERCENT          (100)
#define KMEM_CACHE_MAX_WAST         (0x1000 - KMEM_CACHE_SAVE_RATE * 0x1000/KMEM_CACHE_PERCENT)

#define MIN_OBJECT 8
#define MAX_ORDER 13
#define MAX_OBJS_PER_PAGE 65535


#define KMALLOC_MIN                 (8)
#define KMALLOC_MAX_SIZE            (2 * 1024 * 1024)
/* 8 16 32 64 128 256 512 1024 2048 4096 */
/* 8*1024 16*1024 32*1024 64*1024 128*1024 256*1024 512*1024 1024*1024 2*1024*1024 */
#define KMALLOC_INDEX_MAX           (19)


struct kmem_cache {
    unsigned int obj_size;
    unsigned int obj_num;
    unsigned int page_order;
    struct page *head_page;
    void *obj_block;
};

/* 只要让浪费率小于90%就可以满足要求了 */
/*
static inline int find_order(unsigned int size)
{
    int order;
    for (order = 0; order <= KMEM_CACHE_MAX_ORDER; order++) {
        if (size <= (KMEM_CACHE_MAX_WAST) * (1 << order)) {
            return order;
        }
    }
    if (size > (1 << order) * 0x1000)
        return -1;
    return order;
}
*/


struct kmem_cache *kmem_cache_create(struct kmem_cache *cache, unsigned int size);
void *kmem_cache_alloc(struct kmem_cache *cache);
void kmem_cache_free(struct kmem_cache *cache, void *objp);
void kmem_cache_destroy(struct kmem_cache *cache);
void init_kmem_cache(void);

void *kmalloc(unsigned int size);
void kfree(void *addr);

#endif
