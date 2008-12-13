
// CODESTYLE: v2.0

// MemoryChunk.h
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: A class to simulate an arbitrary amount of data

#ifndef __MEMORYCHUNK_H__
#define __MEMORYCHUNK_H__

namespace VCOMP
{
	class MemoryChunk
	{
	public:
	
		MemoryChunk(unsigned long bytes);
	
		~MemoryChunk();
	
		unsigned char Read();
	
		void Zero();
	
		void Write(unsigned char value);
	
		unsigned long GetSize();
	
		void Seek(unsigned long address);
	
	private:
	
		void Reset();
	
		unsigned long size_;
		unsigned long ptr_;
		unsigned char* data_;
	};// end class

} // end namespace
#endif


