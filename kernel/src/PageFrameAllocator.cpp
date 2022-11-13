#include "PageFrameAllocator.h"
uint64_t freemem;
uint64_t reservedmem;
uint64_t usedmem;
bool initd = false; //is initialized?
void PageFrameAllocator::ReadEFIMemMap(EFI_MEMORY_DESCRIPTOR* memMap, size_t memMapSize, size_t memMapDescSize){
    if(initd) return;
    initd = true;
    uint64_t memMapEnt = memMapSize / memMapDescSize;
    void* largestFreeMemSeg = NULL;
    size_t lfmsSize = 0;
    for(int i = 0; i < memMapEnt; i++){
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)memMap+(i*memMapDescSize));
        if(desc->type == 7){//is memory type 7?
            if(desc->numPages * 4096 > lfmsSize){
                largestFreeMemSeg = desc->physAddr;
                lfmsSize = desc->numPages * 4096;
            }
        }
    }
    uint64_t memSize = GetMemorySize(memMap, memMapEnt, memMapDescSize);
    freemem = memSize;
    uint64_t bitmapSize = memSize / 4096 / 8 + 1;
    initBitmap(bitmapSize, largestFreeMemSeg);
    LockPages(&PageBitmap, PageBitmap.size / 4096 + 1);
    for(int i = 0; i < memMapEnt; i++){
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)memMap+(i*memMapDescSize));
        if(desc->type != 7){
            ReservePages(desc->physAddr, desc->numPages);
        }
    }
}
void PageFrameAllocator::initBitmap(size_t bitmapSize, void* bufferAddr){
    PageBitmap.size = bitmapSize;
    PageBitmap.buf = (uint8_t*)bufferAddr;
    for(int i = 0; i < bitmapSize; i++){
        *(uint8_t*)(PageBitmap.buf + i) = 0;
    }
}
void PageFrameAllocator::FreePage(void* address){
    uint64_t index = (uint64_t)address / 4096;
    if(PageBitmap[index] == false) return;
    PageBitmap.set(index, false);
    freemem += 4096;
    usedmem -= 4096;
}
void PageFrameAllocator::LockPage(void* address){
    uint64_t index = (uint64_t)address / 4096;
    if(PageBitmap[index] == true) return;
    PageBitmap.set(index, true);
    freemem -= 4096;
    usedmem += 4096;
}
void PageFrameAllocator::ReservePage(void* address){
    uint64_t index = (uint64_t)address / 4096;
    if(PageBitmap[index] == false) return;
    PageBitmap.set(index, false);
    freemem -= 4096;
    reservedmem += 4096;
}
void PageFrameAllocator::UnreservePage(void* address){
    uint64_t index = (uint64_t)address / 4096;
    if(PageBitmap[index] == true) return;
    PageBitmap.set(index, true);
    freemem += 4096;
    reservedmem -= 4096;
}
void PageFrameAllocator::FreePages(void* address, uint64_t pcount){
    for(int t = 0; t < pcount; t++){
        FreePage((void*)((uint64_t)address + (t * 4096)));
    }
}
void PageFrameAllocator::LockPages(void* address, uint64_t pcount){
    for(int t = 0; t < pcount; t++){
        LockPage((void*)((uint64_t)address + (t * 4096)));
    }
}
void PageFrameAllocator::ReservePages(void* address, uint64_t pcount){
    for(int t = 0; t < pcount; t++){
        ReservePage((void*)((uint64_t)address + (t * 4096)));
    }
}
void PageFrameAllocator::UnreservePages(void* address, uint64_t pcount){
    for(int t = 0; t < pcount; t++){
        UnreservePage((void*)((uint64_t)address + (t * 4096)));
    }
}
uint64_t PageFrameAllocator::getFreeRAM(){
    return freemem;
}
uint64_t PageFrameAllocator::getUsedRAM(){
    return usedmem;
}
uint64_t PageFrameAllocator::getReservedRAM(){
    return reservedmem;
}
void* PageFrameAllocator::RequestPage(){
    for(uint64_t index = 0; index < PageBitmap.size * 8; index++){
        if(PageBitmap[index] == true){
            continue;
        }
        LockPage((void*)(index*4096));
        return (void*)(index*4096);
    }
    return NULL;// TODO: make hdd drivers and make swap file on hdd
}