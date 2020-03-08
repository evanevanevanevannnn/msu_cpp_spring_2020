#include <iostream>
#include <string>

#include "second.h"

using namespace std;

static LinearAllocator linearAllocator;

void MakeAllocator(size_t maxSize) {
    linearAllocator.size = maxSize;
    linearAllocator.offset = 0;
    linearAllocator.data = (char *)malloc(maxSize);
}

char* alloc(size_t size) {
    if (linearAllocator.offset + size > linearAllocator.size)
        return nullptr;

    char *new_prt = linearAllocator.data + linearAllocator.offset;
    linearAllocator.offset += size;
    return new_prt;
}

void reset() {
    linearAllocator.offset = 0;
}

int main() {
    string command, arg;

    while (command != "EXIT") {
        cin >> command;

        if (command == "MAKE_ALLOCATOR") {
            cin >> arg;
            MakeAllocator(stoi(arg));
        }
        else if (command == "ALLOCATE") {
            cin >> arg;
            cout << (size_t)alloc(stoi(arg)) << '\n';
        }
        else if (command == "RESET")
            reset();
    }

    free(linearAllocator.data);
    return 0;
}