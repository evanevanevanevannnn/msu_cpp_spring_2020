#include <bits/stdc++.h>

using namespace std;

using tokenCallback = void (*)(char *);
using startStopCallback = void (*)();

struct CallbackFunctions {
    tokenCallback numberCallback,
                  stringCallback;

    startStopCallback startCallback,
                      stopCallback;
};

static CallbackFunctions callbackFunctions;

void registerNumberCallback(tokenCallback callback);

void registerStringCallback(tokenCallback callback);

void registerStartCallback(startStopCallback callback);

void registerStopCallback(startStopCallback callback);

bool isSpace(char c);

void parse(char *text);