#include "parser.h"

void registerNumberCallback(tokenCallback callback) {
    callbackFunctions.numberCallback = callback;
}

void registerStringCallback(tokenCallback callback) {
    callbackFunctions.stringCallback = callback;
}

void registerStartCallback(startStopCallback callback) {
    callbackFunctions.startCallback = callback;
}

void registerStopCallback(startStopCallback callback) {
    callbackFunctions.stopCallback = callback;
}

bool isSpace(char c) {
    return (c == ' ' || c == '\t' || c == '\n');
}

void parse(char *text) {
    callbackFunctions.startCallback();

    while (*text) {

        if (isSpace(*text)) {
            text++;
            continue;
        }
        
        int i = 0;
        for(; !isSpace(text[i]) && text[i]; ++i);

        char prev = text[i];

        text[i] = 0;
        if (*text >= '0' && *text <= '9')
            callbackFunctions.numberCallback(text);
        else
            callbackFunctions.stringCallback(text);
        text[i] = prev;

        text += i;
    }

    callbackFunctions.stopCallback();
}