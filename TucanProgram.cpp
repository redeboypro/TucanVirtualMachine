#include <iostream>
#include "TucanProgram.h"

void TucanProgram::Execute() {
    for (; mByteCode[mByteCodePtr] != Exit; ++mByteCodePtr) {
        switch (mByteCode[mByteCodePtr]) {
            case PushCStr: {
                mPushCStr();
                break;
            }
            case PushRCStr: {
                mPushCStr(true);
                break;
            }
            case ConcatCStr: {
                auto bStrLength = mStackBuffer.PopInt16();
                auto bStrPtr = mStackBuffer.PopCStr(bStrLength);

                auto aStrLength = mStackBuffer.PopInt16();
                auto aStrPtr = mStackBuffer.PopCStr(aStrLength);

                auto destStrLength = static_cast<Int16>(aStrLength + bStrLength);
                Byte* destStrPtr = new Byte[destStrLength];

                memcpy(destStrPtr, aStrPtr, aStrLength);
                memcpy(destStrPtr + aStrLength, bStrPtr, bStrLength);

                mStackBuffer.PutCStr(bStrPtr, bStrLength);

                delete[] aStrPtr;
                delete[] bStrPtr;
                delete[] destStrPtr;
                break;
            }
            case PrintCStr: {
                auto strLength = mStackBuffer.PopInt16();

                auto strPtr = mStackBuffer.PopCStr(strLength);

                for (Int16 ci = 0; ci < strLength; ++ci) {
                    std::cout << strPtr[ci];
                }

                delete[] strPtr;
                break;
            }
        }
    }
}

void TucanProgram::mPushCStr(bool reversed) {
    auto strLength = ReadInt16();
    auto strPtr = ReadCStr(strLength);

    mStackBuffer.PutCStr(strPtr, strLength, reversed);
    delete[] strPtr;
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
        strBuffer[i] = ReadByte();
    }

    return strBuffer;
}

Byte TucanBuffer::PopByte() {
    Byte value = mStack[mStackPtr];
    mStackPtr--;
    return value;
}

Int16 TucanBuffer::PopInt16() {
    Int16 value = *(Int16*)&mStack[mStackPtr];
    mStackPtr -= I16Mem;
    return value;
}

Int32 TucanBuffer::PopInt32() {
    Int32 value = *(Int32*)&mStack[mStackPtr];
    mStackPtr -= I32Mem;
    return value;
}

Float32 TucanBuffer::PopFloat32() {
    Float32 value = *(Float32*)&mStack[mStackPtr];
    mStackPtr -= F32Mem;
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
    mStack[++mStackPtr] = value;
}

void TucanBuffer::PutInt16(Int16 value) {
    mStackPtr += I16Mem;
    *(Int16*)&mStack[mStackPtr] = value;
}

void TucanBuffer::PutInt32(Int32 value) {
    mStackPtr += I32Mem;
    *(Int32*)&mStack[mStackPtr] = value;
}

void TucanBuffer::PutFloat32(Float32 value) {
    mStackPtr += F32Mem;
    *(Float32*)&mStack[mStackPtr] = value;
}

void TucanBuffer::PutCStr(const Byte* value, Int16 length, bool reversed) {
    if (value == nullptr || length == 0)
        return;

    Int16 ci = 0;
    if (reversed) {
        ci = static_cast<Int16>(length - 1);
        for (; ci >= 0; --ci) {
            PutByte(value[ci]);
        }
    }
    else {
        for (; ci < length; ++ci) {
            PutByte(value[ci]);
        }
    }

    PutInt16(length);
}

TucanBuffer::TucanBuffer(Byte* stack) : mStack(stack) {}

TucanBuffer::TucanBuffer(Int32 size) : mStack(new Byte[size]) {}

TucanBuffer::~TucanBuffer() {
    delete[] mStack;
}

Byte TucanBuffer::ReadByte() {
    return mStack[mStackPtr];
}

Int16 TucanBuffer::ReadInt16() {
    return *(Int16*)&mStack[mStackPtr];
}

Int32 TucanBuffer::ReadInt32() {
    return *(Int32*)&mStack[mStackPtr];
}

Float32 TucanBuffer::ReadFloat32() {
    return *(Float32*)&mStack[mStackPtr];
}

Byte* TucanBuffer::ReadCStr(Int16 length) {
    Byte* strBuffer = new Byte[length];

    for (Int32 i = 0; i < length; ++i) {
        strBuffer[i] = mStack[mStackPtr + i];
    }

    return strBuffer;
}
