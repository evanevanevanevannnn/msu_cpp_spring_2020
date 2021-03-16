#include <bits/stdc++.h>

#include "serializer.h"

using namespace std;

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer) {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer) {
        return deserializer(c, b, a);
    }
};

int main() {
	Data x { 1, true, 2 };

    stringstream ss;

	Serializer serializer(ss);
	serializer.save(x);

    Data y { 0, false, 0 };

    Deserializer deserializer(ss);
    const Error err = deserializer.load(y);

	return 0;
}