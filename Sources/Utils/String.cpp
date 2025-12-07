#include "Utils/String.hpp"

#include "CallFuncWrapper.hpp"
#include "Function.hpp"

int String::countTextLen(char* text) {
    return Function<int>(0x003038A0)(text);
}