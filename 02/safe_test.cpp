#include "parser.h"

using namespace std;

void parseStart() {
	cout << "\tparsing started\n";
}

void parseFinish() {
	cout << "\tparsing finished\n";
}

void numberTokenHandler(int token) {
	cout << "\tnumber token -> " << token << '\n';
}

void anotherNumberTokenHandler(int token) {
	cout << "\tsame number token -> " << token << '\n';
}

void stringTokenHandler(const string& token) {
	cout << "\tstring token -> " << token << '\n';
}

void anotherStringTokenHandler(const string& token) {
	cout << "\tsame string token -> " << token << '\n';
}

void test(string testString) {
	static int testCounter = 1;

	cout << "TEST " << testCounter << "\n\n";

	if (!allRegistered()) {
		cout << "warnings:\n\t";

		string registered = whichRegistered();
		for (auto c: registered) {
			cout << c;

			if (c == '\n')
				cout << '\t';
		}

		cout << '\n';
	}

	cout << "test output:\n";

	parse(testString);
	cout << '\n';

	testCounter++;
}

int main() {

	registerNumberCallback(numberTokenHandler);
	registerStringCallback(stringTokenHandler);

	test("this 123 is 45 fine"); //not registered functions

	registerStartCallback(parseStart);
	registerStopCallback(parseFinish);

	test("this 123 is 45 fine"); //basic functionality 

	test("  this \n\t  123\t\t\nis  45 \t \n fine   \n"); //space symbols handeling

	registerNumberCallback(anotherNumberTokenHandler);
	registerStringCallback(anotherStringTokenHandler);

	test("this 123 is 45 fine"); //changing callback functions

	return 0;
}