#include <iostream>
#include <string>

using StringCallback = void (*)(const std::string&);
using NumberCallback = void (*)(int);
using parseCallback = void (*)();

struct CallbackFunctions {
    NumberCallback numberCallback;
    StringCallback stringCallback;

    parseCallback startCallback,
                      stopCallback;
};

void registerNumberCallback(NumberCallback callback);

void registerStringCallback(StringCallback callback);

void registerStartCallback(parseCallback callback);

void registerStopCallback(parseCallback callback);

bool allRegistered();

std::string whichRegistered();

void parse(const std::string& text);