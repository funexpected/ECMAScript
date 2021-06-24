#include "free_list_alloc.h"

#include <assert.h>
#include <stddef.h>

void* alloc(FreeListAllocator* allocator) {
    assert(allocator != NULL);
    char * p;

    pthread_mutex_lock(&allocator->mut);
    if (allocator->next_free != NULL) {
        // there is a free block, let's use it
        p = (char*)allocator->next_free;
        allocator->next_free = allocator->next_free->next;
    } else {
        // no free blocks, need to allocate
        p = (char *)malloc(HEADER_SIZE + allocator->data_size);
        ((ListItem*)p)->next = NULL;
        allocator->allocations_total++;
    }
    allocator->allocations_used++;

    pthread_mutex_unlock(&allocator->mut);

    return (void*) (p + HEADER_SIZE);
}

void dealloc(FreeListAllocator* allocator, void* data) {
    char *p = (char*)data - HEADER_SIZE;

    pthread_mutex_lock(&allocator->mut);
    ListItem* t = allocator->next_free;
    allocator->next_free = (ListItem*)p;
    ((ListItem*)p)->next = t;
    allocator->allocations_used--;
    pthread_mutex_unlock(&allocator->mut);
}
