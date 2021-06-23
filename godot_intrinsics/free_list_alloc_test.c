/*#include "free_list_alloc.h"
#include "godot_intrinsic_types.h"

#include <stdio.h>


static FreeListAllocator vector2_allocator = {
    .data_size = sizeof(JSVector2),
    .next_free = NULL,
    .mut = PTHREAD_MUTEX_INITIALIZER,
    .allocations_total = 0,
    .allocations_used = 0,
    };

static FreeListAllocator rect2_allocator = {
    .data_size = sizeof(JSRect2),
    .next_free = NULL,
    .mut = PTHREAD_MUTEX_INITIALIZER,
    .allocations_total = 0,
    .allocations_used = 0,
    };

#define PRINT_ALLOC(allocator) printf("total = %lu, used = %lu\n", allocator.allocations_total, allocator.allocations_used);

int main(){
    PRINT_ALLOC(rect2_allocator)
    
    JSRect2* vec0 = alloc(&rect2_allocator);
    vec0->data.position.x = 2.0;
    vec0->data.position.y = 3.0;

    PRINT_ALLOC(rect2_allocator)

    JSRect2* vec1 = alloc(&rect2_allocator);
    vec1->data.position.x = 5.0;
    vec1->data.position.y = 5.0;

    PRINT_ALLOC(rect2_allocator)
    
    JSRect2* vec2 = alloc(&rect2_allocator);
    vec2->data.position.x = 5.0;
    vec2->data.position.y = 5.0;
    
    PRINT_ALLOC(rect2_allocator)
    
    dealloc(&rect2_allocator, vec1);
    
    PRINT_ALLOC(rect2_allocator)
    
    JSRect2* vec3 = alloc(&rect2_allocator);
    vec3->data.position.x = 7.0;
    vec3->data.position.y = 7.0;
    
    PRINT_ALLOC(rect2_allocator)
    
    return 0;

}

*/