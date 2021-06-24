#include "godot_intrinsic_types.h"
#include <math.h>

#include "free_list_alloc.h"


FreeListAllocator vector2_allocator = {
    .data_size = sizeof(JSVector2),
    .next_free = NULL,
    .mut = PTHREAD_MUTEX_INITIALIZER,
    .allocations_total = 0,
    .allocations_used = 0,
    };

FreeListAllocator rect2_allocator = {
    .data_size = sizeof(JSRect2),
    .next_free = NULL,
    .mut = PTHREAD_MUTEX_INITIALIZER,
    .allocations_total = 0,
    .allocations_used = 0,
    };
