#include "mem.h"
uint64_t GetMemorySize(EFI_MEMORY_DESCRIPTOR* memMap, uint64_t memMapEnt, uint64_t memMapDescSize){
    static uint64_t memSizeBytes = 0;
    if(memSizeBytes > 0) return memSizeBytes;
    for(int i = 0; i < memMapEnt; i++){
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)memMap + (i*memMapDescSize));
        memSizeBytes += desc->numPages * 4096;
    }
    return memSizeBytes;
}