#include <bits/stdc++.h>

#include "format.h"

int main() {
	auto res = format("{1} + {1} = {0}", 2, 1);
	std::cout << res << '\n';
	return 0;
}