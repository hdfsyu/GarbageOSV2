#pragma once
#include "efiMemory.h"
#include <stdint.h>
#include "bitmap.h"
#include "mem.h"
class PageFrameAllocator{
    public:
    void ReadEFIMemMap(EFI_MEMORY_DESCRIPTOR* memMap, size_t memMapSize, size_t memMapDescSize);
    bitmap PageBitmap;
    void FreePage(void* address);
    void LockPage(void* address);
    void FreePages(void* address, uint64_t pcount);
    void LockPages(void* address, uint64_t pcount);
    uint64_t getFreeRAM();
    uint64_t getUsedRAM();
    uint64_t getReservedRAM();
    void* RequestPage();
    private:
    void initBitmap(size_t bitmapSize, void* bufferAddr);
    void ReservePage(void* address);
    void UnreservePage(void* address);
    void ReservePages(void* address, uint64_t pcount);
    void UnreservePages(void* address, uint64_t pcount);
};