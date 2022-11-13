#include "BasicRenderer.h"
#include "cstr.h"
#include "efiMemory.h"
#include "mem.h"
#include "bitmap.h"
#include "PageFrameAllocator.h"
#include <stdint.h>
struct BootInfo{
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_Font;
	EFI_MEMORY_DESCRIPTOR* mMap;
	uint64_t mMapSize;
    uint64_t mMapDescSize;
};
extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;
uint8_t testbuffer[20];
extern "C" void _start(BootInfo* bootInfo){
    unsigned int xNum = 1400; //i would remove this, but its fine and im lazy so whatever, also its good for debugging the X position of the text
    BasicRenderer newRenderer = BasicRenderer(bootInfo->framebuffer, bootInfo->psf1_Font);
    // newRenderer.CursorPosition = {xNum,newRenderer.CursorPosition.Y + 16};
    // newRenderer.Print(to_string((uint64_t)4385948));
    // newRenderer.CursorPosition = {xNum,newRenderer.CursorPosition.Y + 16};
    // newRenderer.Print(to_string((int64_t)-4385948));
    // newRenderer.CursorPosition = {xNum,newRenderer.CursorPosition.Y + 16};
    // newRenderer.Print(to_string((double)-516.82));
    // newRenderer.CursorPosition = {xNum,newRenderer.CursorPosition.Y + 16};
    // newRenderer.Print(to_hstring((uint64_t)0xF0));
    // newRenderer.CursorPosition = {xNum,newRenderer.CursorPosition.Y + 16};
    // newRenderer.Print(to_hstring((uint32_t)0xF0));
    // newRenderer.CursorPosition = {xNum,newRenderer.CursorPosition.Y + 16};
    // newRenderer.Print(to_hstring((uint16_t)0xF0));
    // newRenderer.CursorPosition = {xNum,newRenderer.CursorPosition.Y + 16};
    // newRenderer.Print(to_hstring((uint8_t)0xF0));
    // newRenderer.CursorPosition = {xNum,newRenderer.CursorPosition.Y + 16};
    newRenderer.CursorPosition = {xNum,newRenderer.CursorPosition.Y + 16};
    newRenderer.Print("the most garbage os ever. (version 2!!!!)");
    PageFrameAllocator newAlloc;
    newAlloc.ReadEFIMemMap(bootInfo->mMap, bootInfo->mMapSize,bootInfo->mMapDescSize);
    newRenderer.CursorPosition = {xNum,newRenderer.CursorPosition.Y + 16};
    newRenderer.Print("Free Memory: ");
    newRenderer.Print(to_string(newAlloc.getFreeRAM() / 1024));
    newRenderer.Print(" KB ");
    newRenderer.CursorPosition = {xNum,newRenderer.CursorPosition.Y + 16};
    newRenderer.Print("Used Memory: ");
    newRenderer.Print(to_string(newAlloc.getUsedRAM() / 1024));
    newRenderer.Print(" KB ");
    newRenderer.CursorPosition = {xNum,newRenderer.CursorPosition.Y + 16};
    newRenderer.Print("Reserved Memory: ");
    newRenderer.Print(to_string(newAlloc.getReservedRAM() / 1024));
    newRenderer.Print(" KB ");
    // for(int t = 0;t<20;t++){
    //     void* address = newAlloc.RequestPage();
    //     newRenderer.CursorPosition = {xNum,newRenderer.CursorPosition.Y + 16};
    //     newRenderer.Print(to_hstring((uint64_t)address));
    // }
    // example of requesting pages
    uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages = (uint64_t)kernelSize /4096 + 1;
    newAlloc.LockPages(&_KernelStart, kernelPages);
    //newRenderer.Print(to_string(GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescSize)));
    // for(int i =0; i < mMapEntries; i++){
    //     EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)bootInfo->mMap + (i*bootInfo->mMapDescSize));
    //     newRenderer.CursorPosition = {xNum, newRenderer.CursorPosition.Y + 16};
    //     newRenderer.Print(EFI_MEMORY_TYPE_STRINGS[desc->type]);
    //     newRenderer.Colour = 0x00ff00;
    //     newRenderer.Print(" ");
    //     newRenderer.Print(to_string(desc->numPages * 4096 / 1024));
    //     newRenderer.Print(" KB");
    //     newRenderer.Colour = 0xffffffff;
    // }
    return;
}