#include <cstddef>

struct LinearAllocator {
	size_t offset;
	size_t size;
	char *data;
};

void MakeAllocator(size_t maxSize);

char* alloc(size_t size);

void reset();