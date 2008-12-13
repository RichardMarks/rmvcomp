
// CODESTYLE: v2.0

// DiskFile.cpp
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: A class to simulate a virtual disk file
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include "DiskFile.h"

#include "MemoryChunk.h"

namespace VCOMP
{
	DiskFile::DiskFile() :
		readOnly_(false),
		openFlag_(false),
		data_(0),
		fileName_(0)
	{
	
	}

	DiskFile::DiskFile(const char* fileName) :
		readOnly_(false),
		openFlag_(false),
		data_(0)
	{
		fileName_ = strdup(fileName);
	}

	DiskFile::~DiskFile()
	{
		if (0 != data_)
		{
			delete data_; 
			data_ = 0;
		}
	}

	void DiskFile::Open(DISKFILE::DISKFILEMODE diskFileMode)
	{
		if (DISKFILE::Read == diskFileMode)
		{
			readOnly_ = true;
		}
		else
		{
			readOnly_ = false;
		}
	
		if (!openFlag_)
		{
			openFlag_ = true; 
			fprintf(stderr, "DiskFile::Open(%s)\n%s is now open.\n", 
			(DISKFILE::Read == diskFileMode) ? "Read" : "Write", fileName_);
			return;
		}
		fprintf(stderr, "DiskFile::Open(%s)\n%s is already open!\n", 
			(DISKFILE::Read == diskFileMode) ? "Read" : "Write", fileName_);
	}

	void DiskFile::Close()
	{
		if (openFlag_)
		{
			openFlag_ = false; 
			if (!readOnly_)
			{
				Flush(); // make sure the data gets written
			}
			fprintf(stderr, "DiskFile::Close()\n%s closed.\n", fileName_);
			return;
		}
		fprintf(stderr, "DiskFile::Close()\n%s is not open!\n", fileName_);
	}

	void DiskFile::Write(const char* data)
	{
		if (openFlag_)
		{
			if (readOnly_)
			{
				fprintf(stderr, "%s is read only!\n", fileName_);
				return;
			}
		
			unsigned long dataLength = strlen(data);
			
			fprintf(stderr, "DiskFile::Write(%s)\n\tdataLength = %d\n", data, dataLength);
			
			for (unsigned long b = 0; b < dataLength; b++)
			{
				dataCache_.push_back(static_cast<unsigned char>(data[b]));
				
				fprintf(stderr, "%02X ", static_cast<unsigned char>(data[b]));
			}
			
			fprintf(stderr, "\n");
			
			return;
		}
		fprintf(stderr, "DiskFile::Write(%s)\n%s is not open!\n", fileName_);
	}

	MemoryChunk* DiskFile::Read()
	{
		if (openFlag_)
		{
			if (readOnly_)
			{
				return data_;
			}
			else
			{
				fprintf(stderr, "%s is not open for reading!\n", fileName_);
				return 0;
			}
		}
		fprintf(stderr, "%s is not open!\n", fileName_);
		return 0;
	}

	const char* DiskFile::GetFileName()
	{
		return fileName_;
	}

	unsigned long DiskFile::GetSize()
	{
		if (0 != data_)
		{
			return data_->GetSize();
		}
		return 0;
	}

	void DiskFile::Flush()
	{
		unsigned long dataLength = dataCache_.size();
		if (0 != data_)
		{
			delete data_;
			data_ = 0;
		}
		data_ = new MemoryChunk(dataLength);
		fprintf(stderr, "Flushing %d bytes of data\n", dataLength);
		for (unsigned long b = 0; b < dataLength; b++)
		{
			data_->Write(dataCache_[b]);
		}
		dataCache_.clear();
	}
} // end namespace


