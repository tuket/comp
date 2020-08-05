#pragma once

/* IR = Intermediate representation */

namespace tkc
{

namespace ir
{

enum class OperandType { // operarand type
    I8, U8, I16, U16, I32, U32, I64, U64,
};

union OperandValue {
    int32_t I32;
    uint32_t U32;
    int64_t I64;
    uint64_t U64;
};

struct Instruction
{
    enum Type {
        ADD,
        MOVE,
    };
    Type type;
    OperandType opTypes[2];

}

}

}