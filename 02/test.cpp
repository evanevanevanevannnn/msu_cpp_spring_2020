#include <iostream>
#include <string>

#include "parser.h"

using namespace std;

void parseStart() {
	cout << "parsing started\n";
}

void parseFinish() {
	cout << "parsing finished\n";
}

void numberTokenHandler(string token) {
	cout << "number token -> " << token << '\n';
}

void anotherNumberTokenHandler(string token) {
	cout << "same number token -> " << token << '\n';
}

void stringTokenHandler(string token) {
	cout << "string token -> " << token << '\n';
}

void anotherStringTokenHandler(string token) {
	cout << "same string token -> " << token << '\n';
}

void test(string testString) {
	static int counter = 1;

	cout << "test " << counter << ":\n";
	parse(testString);
	cout << '\n';

	counter++;
}

int main() {

	cout << "\n___________testing___________\n\n";

	registerStartCallback(parseStart);
	registerStopCallback(parseFinish);

	registerNumberCallback(numberTokenHandler);
	registerStringCallback(stringTokenHandler);

	test("this 123 is 45 fine"); //basic functionality 

	test("  this \n\t  123\t\t\nis  45 \t \n fine   \n"); //space symbols handeling

	registerNumberCallback(anotherNumberTokenHandler);
	registerStringCallback(anotherStringTokenHandler);

	test("this 123 is 45 fine"); //changing callback functions



	return 0;
}