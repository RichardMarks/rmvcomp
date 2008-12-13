
// CODESTYLE: v2.0

// Memory.h
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: A class to simulate a virtual chip of 8MB of virtual memory

#ifndef __MEMORY_H__
#define __MEMORY_H__

namespace VCOMP
{
	class MemoryChunk;
	
	class Memory
	{
	public:
	
		Memory();
	
		~Memory();
	
		void Write(unsigned long address, MemoryChunk* data);
	
		MemoryChunk* Read(unsigned long address, unsigned long bytes);

	private:
	
		unsigned char* data_;
	}; // end class

} // end namespace
#endif


