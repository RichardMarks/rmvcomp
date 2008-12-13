
// CODESTYLE: v2.0

// DiskFile.h
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: A class to simulate a virtual disk file

#ifndef __DISKFILE_H__
#define __DISKFILE_H__

#include <vector>
#include "ForwardDeclares.h"
namespace VCOMP
{
	

	class DiskFile 
	{
	public:
	
		DiskFile();
	
		DiskFile(const char* fileName);
	
		~DiskFile();
	
		void Open(DISKFILE::DISKFILEMODE diskFileMode);
	
		void Close();
	
		void Write(const char* data);
	
		MemoryChunk* Read();
	
		const char* GetFileName();
	
		unsigned long GetSize();
	
	private:
		typedef std::vector<unsigned char> ByteVector;
		
		void Flush();

		ByteVector dataCache_;
		MemoryChunk* data_;	
		const char* fileName_;
		bool openFlag_;
		bool readOnly_;
	}; // end class

} // end namespace
#endif


