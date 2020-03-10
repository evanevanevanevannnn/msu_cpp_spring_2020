#include <cstdlib>

#include "allocator.h"

void MakeAllocator(size_t maxSize) {
    allocator.data = (char *)malloc(maxSize);

    if (allocator.data == nullptr)
        allocator.size = 0;
    else
        allocator.size = maxSize;
    
    allocator.offset = 0;
}

char* alloc(size_t size) {
    if (!isAllocated() || allocator.offset + size > allocator.size)
        return nullptr;

    char *new_prt = allocator.data + allocator.offset;
    allocator.offset += size;
    return new_prt;
}

void reset() {
    allocator.offset = 0;
}

void freeAllocator() {
    free(allocator.data);
}

bool isAllocated() {
    return allocator.size != 0;
}