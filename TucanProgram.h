#ifndef TUCANVIRTUALMACHINE_TUCANPROGRAM_H
#define TUCANVIRTUALMACHINE_TUCANPROGRAM_H

#include <cstdio>
#include <cstring>

using Int32         =        int;
using Int16         =      short;
using Float32       =      float;
using Byte          =       char;

typedef enum : Byte {
    VmPushByte,
    VmPushFloat32,
    VmPushInt32,
    VmPushInt16,
    VmPushCStr,

    VmSwapInt16Int16,
    VmSwapInt16Int32,
    VmSwapInt16Float32,

    VmSwapInt32Int16,
    VmSwapInt32Int32,
    VmSwapInt32Float32,

    VmSwapFloat32Int16,
    VmSwapFloat32Int32,
    VmSwapFloat32Float32,

    VmCastInt16Int32,
    VmCastInt32Int16,

    VmCastInt16Float32,
    VmCastFloat32Int16,

    VmCastInt32Float32,
    VmCastFloat32Int32,

    VmBoolean,

    VmAndInt16,
    VmOrInt16,

    VmAndInt32,
    VmOrInt32,

    VmGInt16,
    VmLInt16,
    VmEInt16,

    VmGInt32,
    VmLInt32,
    VmEInt32,

    VmGFloat32,
    VmLFloat32,
    VmEFloat32,

    VmAddInt16,
    VmSubInt16,
    VmMulInt16,
    VmDivInt16,
    VmRemInt16,

    VmAddInt32,
    VmSubInt32,
    VmMulInt32,
    VmDivInt32,
    VmRemInt32,

    VmAddFloat32,
    VmSubFloat32,
    VmMulFloat32,
    VmDivFloat32,
    VmRemFloat32,

    VmStoreInt16,
    VmLoadInt16,

    VmStoreInt32,
    VmLoadInt32,

    VmStoreFloat32,
    VmLoadFloat32,

    VmStoreCStr,
    VmLoadCStr,

    VmEqualCStr,
    VmCatCStr,

    VmPrtInt16,
    VmPrtInt32,
    VmPrtCStr,

    VmJmp,
    VmExit
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

    Byte PopByte();
    Int16 PopInt16();
    Int32 PopInt32();
    Float32 PopFloat32();
    Byte* PopCStr(Int16 length);

    void PutByte(Byte value);
    void PutInt16(Int16 value);
    void PutInt32(Int32 value);
    void PutFloat32(Float32 value);
    void PutCStr(const Byte* value, Int16 length);
};

class TucanProgram {
private:
    Int32 mByteCodePtr = 0;
    Byte* mByteCode;
    TucanBuffer mStackBuffer;
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