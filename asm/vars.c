//
// Created by ash on 28.04.24.
//


struct var{
    long long __flags;
    void* __data;
};

#pragma region FLAGS DEFINITION

#define TYPE 0xffffffff

#define RO_PTR 0x8000000000000000
#define LR_VALUE 0x4000000000000000

#pragma endregion



