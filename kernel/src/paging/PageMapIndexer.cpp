#include "PageMapIndexer.h"
PageMapIndexer::PageMapIndexer(uint64_t vaddr){
    vaddr >>= 12;
    P_i = vaddr & 0x1ff;
    vaddr >>= 9;
    PT_i = vaddr & 0x1ff;
    vaddr >>= 9;
    PD_i = vaddr & 0x1ff;
    vaddr >>= 9;
    PDP_i = vaddr & 0x1ff;
}