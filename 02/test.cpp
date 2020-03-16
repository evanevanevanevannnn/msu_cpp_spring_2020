#include <iostream>
#include <string>

#include "parser.h"

using namespace std;

void func1() {
	cout << "testing testing 1\n";
}

void func2(char *text) {
	cout << string(text) << " testing2\n";
}

int main() {

	char text[] = "this is 123 text 45 number 67 string";
	char *text2 = text;
	
	registerStartCallback(func1);
	registerStopCallback(func1);

	registerNumberCallback(func2);
	registerStringCallback(func2);

	parse(text2);

	return 0;
}