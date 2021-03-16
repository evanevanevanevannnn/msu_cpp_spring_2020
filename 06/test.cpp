#include <bits/stdc++.h>

#include "format.h"

int main() {
	auto res = format("{10} + {1} = {0}", 2, "1", 1, 1, 1, 1, 1, 1, 1, 1, 10, 1);
	std::cout << res << '\n';
	return 0;
}