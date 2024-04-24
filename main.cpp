#include <iostream>
#include "TucanProgram.h"

int main() {
    Byte byteCode[] = {
            PushRCStr, 0x5, 0x0, 'H', 'e', 'l', 'l', 'o',
            PushRCStr, 0x6, 0x0, ' ', 'w', 'o', 'r', 'l', 'd',
            PrintCStr,
            PrintCStr,
            Exit
    };

    auto program = new TucanProgram(byteCode, 256);

    program->Execute();

    delete program;

    return 0;
}
