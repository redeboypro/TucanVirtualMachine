#include <iostream>
#include "TucanProgram.h"

int main() {
    Byte byteCode[] = {
            PushCStr, 0x5, 0x0, 'H', 'e', 'l', 'l', 'o',
            PushCStr, 0x7, 0x0, ' ', 'W', 'o', 'r', 'l', 'd', '!',
            ConcatCStr,
            PrintCStr,
            Exit
    };

    auto program = new TucanProgram(byteCode, 256);

    program->Execute();

    delete program;

    return 0;
}
