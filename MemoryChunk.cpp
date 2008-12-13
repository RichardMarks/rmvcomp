
// CODESTYLE: v2.0

// MemoryChunk.cpp
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: A class to simulate an arbitrary amount of data
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include "MemoryChunk.h"

namespace VCOMP
{
	MemoryChunk::MemoryChunk(unsigned long bytes)
	{
		data_ = new unsigned char [bytes];
		size_ = bytes;
		Reset();
		Zero();
	}

	MemoryChunk::~MemoryChunk()
	{
		delete [] data_;
	}

	unsigned char MemoryChunk::Read()
	{
		ptr_++;
		if (ptr_ > size_)
		{
			// wrap around reading
			Reset();
		}
		return data_[ptr_];
	}

	void MemoryChunk::Zero()
	{
		memset(data_, 0, size_);
	}

	void MemoryChunk::Write(unsigned char value)
	{
		data_[ptr_] = value;
		ptr_++;
		if (ptr_ > size_)
		{
			// wrap around writing
			Reset();
		}
	}

	unsigned long MemoryChunk::GetSize()
	{
		return size_;
	}

	void MemoryChunk::Seek(unsigned long address)
	{
		ptr_ = (address < size_) ? address : ptr_;
	}
	
	void MemoryChunk::Reset()
	{
		ptr_ = 0;
	}
	
} // end namespace


