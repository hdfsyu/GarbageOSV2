#pragma once
#include "paging.h"
class PageTableManager{
public:
    PageTableManager(PageTable* PML4Addr);
    PageTable* PML4Addr;
    void MapMemory(void* vmem, void* pmem);
};