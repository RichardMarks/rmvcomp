
// CODESTYLE: v2.0

// Memory.cpp
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: A class to simulate a virtual chip of 8MB of virtual memory
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include "Memory.h"
#include "MemoryChunk.h"

namespace VCOMP
{
	Memory::Memory()
	{
		data_ = new unsigned char [0x800000];
	}

	Memory::~Memory()
	{
		delete [] data_;
	}

	void Memory::Write(unsigned long address, MemoryChunk* data)
	{
		if (0 == data)
		{
			fprintf(stderr,
				"Error. Attempted to write invalid data to a Memory Block!\n");
			return;
		}
	
		unsigned long dataLength = data->GetSize();
		if ((address + dataLength) > 0x800000)
		{
			fprintf(stderr, "Out of Memory writing %u bytes to address 0x%08X\n", dataLength, address);
			return;
		}
		data->Seek(0);
		for (unsigned long b = 0; b < dataLength; b++)
		{
			data_[address + b] = data->Read();
		}
	} 

	MemoryChunk* Memory::Read(unsigned long address, unsigned long bytes)
	{
		if ((address + bytes) > 0x800000)
		{
			fprintf(stderr, "Out of Memory reading %u bytes from address: 0x%08X\n", bytes, address);
			return 0;
		}
	
		MemoryChunk* chunk = new MemoryChunk(bytes);
		for (unsigned long b = 0; b < bytes; b++)
		{
			chunk->Write(data_[address + b]);
		}
		return chunk;
	}
} // end namespace


