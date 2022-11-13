#pragma once
#include <stdint.h>
#include "efiMemory.h"
uint64_t GetMemorySize(EFI_MEMORY_DESCRIPTOR* memMap, uint64_t memMapEnt, uint64_t memMapDescSize);