#ifndef FREE_LIST_ALLOC_H
#define FREE_LIST_ALLOC_H

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct ListItem {
    struct ListItem* next; 
} ListItem;

#define HEADER_SIZE  sizeof(ListItem)

typedef struct FreeListAllocator {
    size_t data_size;
    ListItem* next_free;
    pthread_mutex_t mut;
    size_t allocations_total;
    size_t allocations_used;
} FreeListAllocator;

void* alloc(FreeListAllocator* allocator);
void dealloc(FreeListAllocator* allocator, void* data);

#endif //FREE_LIST_ALLOC_H
