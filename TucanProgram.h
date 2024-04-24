#ifndef TUCANVIRTUALMACHINE_TUCANPROGRAM_H
#define TUCANVIRTUALMACHINE_TUCANPROGRAM_H

#include <cstdio>
#include <cstring>

using Int32         =        int;
using Int16         =      short;
using Float32       =      float;
using Byte          =       char;

typedef enum : Byte {
    Push16,
    Push32,

    AndInt16,
    OrInt16,

    AndInt32,
    OrInt32,

    GInt16,
    LInt16,
    EInt16,

    GInt32,
    LInt32,
    EInt32,

    AddInt16,
    SubInt16,
    MulInt16,
    DivInt16,

    AddInt32,
    SubInt32,
    MulInt32,
    DivInt32,

    Store16,
    Load16,

    Store32,
    Load32,

    PrintInt32,

    PushCStr,
    PushRCStr,

    EqualCStr,
    ConcatCStr,

    StoreCStr,
    LoadCStr,

    PrintCStr,

    Jmp,
    Exit
} InstructionSet;

const Int32 I16Mem  =   sizeof(Int16);
const Int32 I16BO   =      I16Mem - 1;

const Int32 I32Mem  =   sizeof(Int32);
const Int32 I32BO   =      I32Mem - 1;

const Int32 F32Mem  = sizeof(Float32);
const Int32 F32BO   =      F32Mem - 1;

class TucanBuffer
{
private:
    Byte* mStack;
    Int32 mStackPtr = 0;

public:
    explicit TucanBuffer(Byte* data);
    explicit TucanBuffer(Int32 size);
    ~TucanBuffer();

    Byte ReadByte();
    Int16 ReadInt16();
    Int32 ReadInt32();
    Float32 ReadFloat32();
    Byte* ReadCStr(Int16 length);

    Byte PopByte();
    Int16 PopInt16();
    Int32 PopInt32();
    Float32 PopFloat32();
    Byte* PopCStr(Int16 length);

    void PutByte(Byte value);
    void PutInt16(Int16 value);
    void PutInt32(Int32 value);
    void PutFloat32(Float32 value);
    void PutCStr(const Byte* value, Int16 length, bool reversed = false);
};

class TucanProgram {
private:
    Int32 mByteCodePtr = 0;
    Byte* mByteCode;
    TucanBuffer mStackBuffer;
    void mPushCStr(bool reversed = false);
public:
    explicit TucanProgram(Byte* byteCode, Int32 stackSize);
    ~TucanProgram() = default;

    Byte ReadByte();
    Int16 ReadInt16();
    Int32 ReadInt32();
    Float32 ReadFloat32();
    Byte* ReadCStr(Int16 length);

    void Execute();
};

#endif