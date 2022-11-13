#include "bitmap.h"
bool bitmap::operator[](uint64_t index){
    uint64_t byteIndex = index / 8;
    uint8_t bitIndex = index % 8;
    uint8_t bitIndexer = 0b10000000 >> bitIndex;
    if((buf[byteIndex] & bitIndexer) > 0){
        return true;
    }
    return false;
}
void bitmap::set(uint64_t index, bool value){
    uint64_t byteIndex = index / 8;
    uint8_t bitIndex = index % 8;
    uint8_t bitIndexer = 0b10000000 >> bitIndex;
    buf[byteIndex] &= ~bitIndexer;
    if(value){
        buf[byteIndex] |= bitIndexer;
    }
}