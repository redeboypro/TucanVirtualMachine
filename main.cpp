#include <iostream>
#include "TucanProgram.h"

int main() {
    Byte byteCode[] = {
            VmPushInt16, 0x2, 0x0,
            VmPushInt16, 0x3, 0x0,
            VmAddInt16,

            VmPushInt16, 0x5, 0x0,
            VmAddInt16,

            VmPrtInt16,
            VmExit
    };

    auto program = new TucanProgram(byteCode, 256);

    program->Execute();

    delete program;

    return 0;
}
