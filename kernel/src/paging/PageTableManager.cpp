#include "PageTableManager.h"
#include "PageMapIndexer.h"
#include <stdint.h>
#include "PageFrameAllocator.h"
#include "../mem.h"
PageTableManager::PageTableManager(PageTable *PML4Addr) {
    this->PML4Addr = PML4Addr;
}
void PageTableManager::MapMemory(void *vmem, void *pmem) {
    PageMapIndexer indexer = PageMapIndexer((uint64_t)vmem);
    PageDirectoryEntry PDE;
    PDE = PML4Addr->entries[indexer.PDP_i];
    PageTable* PDP;
    if(!PDE.Present){
        PDP = (PageTable*)globalAlloc.RequestPage();
        memoryset(PDP, 0, 0x1000);
        PDE.Address = (uint64_t)PDP >> 12;
        PDE.Present = true;
        PDE.ReadWrite = true;
        PML4Addr->entries[indexer.PDP_i] = PDE;
    }else{
        PDP = (PageTable*)((uint64_t)PDE.Address << 12);
    }
    PDE = PDP->entries[indexer.PD_i];
    PageTable* PD;
    if(!PDE.Present){
        PD = (PageTable*)globalAlloc.RequestPage();
        memoryset(PD, 0, 0x1000);
        PDE.Address = (uint64_t)PD >> 12;
        PDE.Present = true;
        PDE.ReadWrite = true;
        PML4Addr->entries[indexer.PD_i] = PDE;
    }else{
        PD = (PageTable*)((uint64_t)PDE.Address << 12);
    }
    PDE = PD->entries[indexer.PT_i];
    PageTable* PT;
    if(!PDE.Present){
        PT = (PageTable*)globalAlloc.RequestPage();
        memoryset(PT, 0, 0x1000);
        PDE.Address = (uint64_t)PT >> 12;
        PDE.Present = true;
        PDE.ReadWrite = true;
        PML4Addr->entries[indexer.PT_i] = PDE;
    }else{
        PT = (PageTable*)((uint64_t)PDE.Address << 12);
    }
    PDE = PT->entries[indexer.P_i];
    PDE.Address = (uint64_t)pmem >> 12;
    PDE.Present = true;
    PDE.ReadWrite = true;
    PT->entries[indexer.P_i] = PDE;
}