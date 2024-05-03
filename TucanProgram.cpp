#include <iostream>
#include "TucanProgram.h"

void TucanProgram::Execute() {
    for (; mByteCode[mByteCodePtr] != VmExit; ++mByteCodePtr) {
        switch (mByteCode[mByteCodePtr]) {
            case VmPushByte: {
                mStackBuffer.PutByte(ReadByte());
                break;
            }
            case VmPushInt16: {
                mStackBuffer.PutInt16(ReadInt16());
                break;
            }
            case VmPushInt32: {
                mStackBuffer.PutInt32(ReadInt32());
                break;
            }
            case VmPushFloat32: {
                mStackBuffer.PutFloat32(ReadFloat32());
                break;
            }
            case VmPushCStr: {
                auto strLength = ReadInt16();
                auto strPtr = ReadCStr(strLength);

                mStackBuffer.PutCStr(strPtr, strLength);
                delete[] strPtr;
                break;
            }
            case VmAddInt16: {
                mStackBuffer.PutInt16(static_cast<Int16>(mStackBuffer.PopInt16() + mStackBuffer.PopInt16()));
                break;
            }
            case VmSubInt16: {
                mStackBuffer.PutInt16(static_cast<Int16>(mStackBuffer.PopInt16() - mStackBuffer.PopInt16()));
                break;
            }
            case VmMulInt16: {
                mStackBuffer.PutInt16(static_cast<Int16>(mStackBuffer.PopInt16() * mStackBuffer.PopInt16()));
                break;
            }
            case VmDivInt16: {
                mStackBuffer.PutInt16(static_cast<Int16>(mStackBuffer.PopInt16() / mStackBuffer.PopInt16()));
                break;
            }
            case VmRemInt16: {
                mStackBuffer.PutInt16(static_cast<Int16>(mStackBuffer.PopInt16() % mStackBuffer.PopInt16()));
                break;
            }
            case VmCatCStr: {
                auto aStrLength = mStackBuffer.PopInt16();
                auto* aStrPtr = mStackBuffer.PopCStr(aStrLength);

                auto bStrLength = mStackBuffer.PopInt16();
                auto* bStrPtr = mStackBuffer.PopCStr(bStrLength);

                auto destStrLength = static_cast<Int16>(aStrLength + bStrLength);
                auto* destStrPtr = new Byte[destStrLength];

                for (int i = 0; i < aStrLength; i++) {
                    destStrPtr[i] = aStrPtr[aStrLength - i - 1];
                }

                for (int i = 0; i < bStrLength; i++) {
                    destStrPtr[aStrLength + i] = bStrPtr[bStrLength - i - 1];
                }

                mStackBuffer.PutCStr(destStrPtr, destStrLength);

                delete[] aStrPtr;
                delete[] bStrPtr;
                delete[] destStrPtr;
                break;
            }
            case VmPrtInt16: {
                std::cout << mStackBuffer.PopInt16();
                break;
            }
            case VmPrtCStr: {
                auto strLength = mStackBuffer.PopInt16();
                auto strPtr = mStackBuffer.PopCStr(strLength);

                for (Int16 ci = 0; ci < strLength; ++ci) {
                    std::cout << strPtr[ci];
                }

                delete[] strPtr;
                break;
            }
            case VmSwapInt16Int16: {
                auto rValue = mStackBuffer.PopInt16();
                auto lValue = mStackBuffer.PopInt16();
                mStackBuffer.PutInt16(rValue);
                mStackBuffer.PutInt16(lValue);
                break;
            }
            case VmSwapInt16Int32: {
                auto rValue = mStackBuffer.PopInt32();
                auto lValue = mStackBuffer.PopInt16();
                mStackBuffer.PutInt32(rValue);
                mStackBuffer.PutInt16(lValue);
                break;
            }
            case VmSwapInt16Float32: {
                auto rValue = mStackBuffer.PopFloat32();
                auto lValue = mStackBuffer.PopInt16();
                mStackBuffer.PutFloat32(rValue);
                mStackBuffer.PutInt16(lValue);
                break;
            }
            case VmSwapInt32Int16: {
                auto rValue = mStackBuffer.PopInt16();
                auto lValue = mStackBuffer.PopInt32();
                mStackBuffer.PutInt16(rValue);
                mStackBuffer.PutInt32(lValue);
                break;
            }
            case VmSwapInt32Int32: {
                auto rValue = mStackBuffer.PopInt32();
                auto lValue = mStackBuffer.PopInt32();
                mStackBuffer.PutInt32(rValue);
                mStackBuffer.PutInt32(lValue);
                break;
            }
            case VmSwapInt32Float32: {
                auto rValue = mStackBuffer.PopFloat32();
                auto lValue = mStackBuffer.PopInt32();
                mStackBuffer.PutFloat32(rValue);
                mStackBuffer.PutInt32(lValue);
                break;
            }
            case VmSwapFloat32Int16: {
                auto rValue = mStackBuffer.PopInt16();
                auto lValue = mStackBuffer.PopFloat32();
                mStackBuffer.PutInt16(rValue);
                mStackBuffer.PutFloat32(lValue);
                break;
            }
            case VmSwapFloat32Int32: {
                auto rValue = mStackBuffer.PopInt32();
                auto lValue = mStackBuffer.PopFloat32();
                mStackBuffer.PutInt32(rValue);
                mStackBuffer.PutFloat32(lValue);
                break;
            }
            case VmSwapFloat32Float32: {
                auto rValue = mStackBuffer.PopFloat32();
                auto lValue = mStackBuffer.PopFloat32();
                mStackBuffer.PutFloat32(rValue);
                mStackBuffer.PutFloat32(lValue);
                break;
            }
            case VmJmp: {
                mByteCodePtr = ReadInt16() - 1;
                break;
            }
        }
    }
}

TucanProgram::TucanProgram(Byte *byteCode, Int32 stackSize) :
        mByteCode(byteCode),
        mStackBuffer(stackSize) {}

Byte TucanProgram::ReadByte() {
    return mByteCode[++mByteCodePtr];
}

Int16 TucanProgram::ReadInt16() {
    auto i16 = *(Int16*)&mByteCode[++mByteCodePtr];
    mByteCodePtr += I16BO;
    return i16;
}

Int32 TucanProgram::ReadInt32() {
    auto i32 = *(Int32*)&mByteCode[++mByteCodePtr];
    mByteCodePtr += I32BO;
    return i32;
}

Float32 TucanProgram::ReadFloat32() {
    auto f32 = *(Float32*)&mByteCode[++mByteCodePtr];
    mByteCodePtr += F32BO;
    return f32;
}

Byte* TucanProgram::ReadCStr(Int16 length) {
    Byte* strBuffer = new Byte[length];

    for (Int32 i = 0; i < length; ++i) {
        strBuffer[length - i - 1] = ReadByte();
    }

    return strBuffer;
}

Byte TucanBuffer::PopByte() {
    Byte value = mStack[--mStackPtr];
    return value;
}

Int16 TucanBuffer::PopInt16() {
    mStackPtr -= I16Mem;
    Int16 value = *(Int16*)&mStack[mStackPtr];
    return value;
}

Int32 TucanBuffer::PopInt32() {
    mStackPtr -= I32Mem;
    Int32 value = *(Int32*)&mStack[mStackPtr];
    return value;
}

Float32 TucanBuffer::PopFloat32() {
    mStackPtr -= F32Mem;
    Float32 value = *(Float32*)&mStack[mStackPtr];
    return value;
}

Byte* TucanBuffer::PopCStr(Int16 length) {
    Byte* strBuffer = new Byte[length];

    for (Int32 i = 0; i < length; ++i) {
        strBuffer[i] = PopByte();
    }

    return strBuffer;
}

void TucanBuffer::PutByte(Byte value) {
    mStack[mStackPtr] = value;
    mStackPtr++;
}

void TucanBuffer::PutInt16(Int16 value) {
    *(Int16*)&mStack[mStackPtr] = value;
    mStackPtr += I16Mem;
}

void TucanBuffer::PutInt32(Int32 value) {
    *(Int32*)&mStack[mStackPtr] = value;
    mStackPtr += I32Mem;
}

void TucanBuffer::PutFloat32(Float32 value) {
    *(Float32*)&mStack[mStackPtr] = value;
    mStackPtr += F32Mem;
}

void TucanBuffer::PutCStr(const Byte* value, Int16 length) {
    if (value == nullptr || length == 0)
        return;

    for (Int16 ci = 0; ci < length; ++ci) {
        PutByte(value[ci]);
    }

    PutInt16(length);
}

TucanBuffer::TucanBuffer(Byte* stack) : mStack(stack) {}

TucanBuffer::TucanBuffer(Int32 size) : mStack(new Byte[size]) {}

TucanBuffer::~TucanBuffer() {
    delete[] mStack;
}