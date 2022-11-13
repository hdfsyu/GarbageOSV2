#pragma once
#include <stddef.h>
#include <stdint.h>
class bitmap{
    public:
    size_t size;
    uint8_t* buf;
    bool operator[](uint64_t index);
    void set(uint64_t index, bool value);
};