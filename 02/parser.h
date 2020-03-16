#include <string>

using tokenCallback = void (*)(std::string);
using parseCallback = void (*)();

struct CallbackFunctions {
    tokenCallback numberCallback,
                  stringCallback;

    parseCallback startCallback,
                      stopCallback;
};

static CallbackFunctions callbackFunctions;

void registerNumberCallback(tokenCallback callback);

void registerStringCallback(tokenCallback callback);

void registerStartCallback(parseCallback callback);

void registerStopCallback(parseCallback callback);

bool isSpace(char c);

void parse(std::string text);