#include "parser.h"

static CallbackFunctions callbackFunctions;

void registerNumberCallback(NumberCallback callback) {
    callbackFunctions.numberCallback = callback;
}

void registerStringCallback(StringCallback callback) {
    callbackFunctions.stringCallback = callback;
}

void registerStartCallback(parseCallback callback) {
    callbackFunctions.startCallback = callback;
}

void registerStopCallback(parseCallback callback) {
    callbackFunctions.stopCallback = callback;
}

bool allRegistered() {
    return (callbackFunctions.startCallback != nullptr &&
            callbackFunctions.numberCallback != nullptr && 
            callbackFunctions.stringCallback != nullptr &&
            callbackFunctions.stopCallback != nullptr);
}

std::string whichRegistered() { //returns registered and not registered functions
    std::string registered, notRegistered;
    std::string res;

    (callbackFunctions.startCallback == nullptr ? notRegistered : registered) += "startCallback, ";
    (callbackFunctions.numberCallback == nullptr ? notRegistered : registered) += "numberCallback, ";
    (callbackFunctions.stringCallback == nullptr ? notRegistered : registered) += "stringCallback, ";
    (callbackFunctions.stopCallback == nullptr ? notRegistered : registered) += "stopCallback, ";

    if (notRegistered.size()) {

        res += notRegistered.substr(0, notRegistered.size() - 2);
        if (notRegistered.size() > 16)
            res += " are";
        else
            res += " is";
        res += " not registered\n";

        if (registered.size())
            res += "Only using " + registered.substr(0, registered.size() - 2) + "\n";
        else
            res += "Not using anything\n";
    }

    return res;
}

void parse(const std::string& text) {
    if (callbackFunctions.startCallback != nullptr)
        callbackFunctions.startCallback();

    for (int i = 0; i < text.size(); ++i) {

        if (std::isspace(text[i]))
            continue;

        int j = i;
        while (j < text.size() && !std::isspace(text[j]))
            ++j;

        std::string token = text.substr(i, j - i);
        if (text[i] >= '0' && text[i] <= '9' && callbackFunctions.numberCallback != nullptr)
            callbackFunctions.numberCallback(std::stoi(token));
        else if (callbackFunctions.stringCallback != nullptr)
            callbackFunctions.stringCallback(token);

        i = j;
    }

    if (callbackFunctions.stopCallback != nullptr)
        callbackFunctions.stopCallback();
}