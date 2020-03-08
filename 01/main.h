#include <cstddef>

struct LinearAllocator {
	size_t size;
	size_t offset;
	char *data;
};

void MakeAllocator(size_t maxSize);

char* alloc(size_t size);

void reset();