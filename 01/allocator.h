#include <cstddef>

struct LinearAllocator {
	size_t offset;
	size_t size;
	char *data;
};

static LinearAllocator allocator;

void MakeAllocator(size_t maxSize);

char* alloc(size_t size);

void reset();

void freeAllocator();

bool isAllocated();