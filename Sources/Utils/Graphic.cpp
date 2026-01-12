#include "Utils/Graphic.hpp"
#include "Function.hpp"

void Graphic::GSP_Init() {
    Function<void>(0x00559184)();
}

void Graphic::GSP_shutdown() {
    Function<void>(0x005597b0)();
}