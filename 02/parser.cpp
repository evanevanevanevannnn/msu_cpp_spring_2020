#include "parser.h"

void registerNumberCallback(tokenCallback callback) {
    callbackFunctions.numberCallback = callback;
}

void registerStringCallback(tokenCallback callback) {
    callbackFunctions.stringCallback = callback;
}

void registerStartCallback(parseCallback callback) {
    callbackFunctions.startCallback = callback;
}

void registerStopCallback(parseCallback callback) {
    callbackFunctions.stopCallback = callback;
}

bool isSpace(char c) {
    return (c == ' ' || c == '\t' || c == '\n');
}

void parse(std::string text) {
    callbackFunctions.startCallback();

    for (int i = 0; i < text.size(); ++i) {

        if (isSpace(text[i]))
            continue;

        int j = i;
        while (j < text.size() && !isSpace(text[j]))
            ++j;

        std::string token = text.substr(i, j - i);
        if (text[i] >= '0' && text[i] <= '9')
            callbackFunctions.numberCallback(token);
        else
            callbackFunctions.stringCallback(token);

        i = j;
    }

    callbackFunctions.stopCallback();
}