
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
		data_(0),
		fileName_(fileName)
	{
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
			return;
		}
		fprintf(stderr, "%s is already open!\n", fileName_);
	}

	void DiskFile::Close()
	{
		if (openFlag_)
		{
			openFlag_ = false; 
			Flush(); // make sure the data gets written
			return;
		}
		fprintf(stderr, "%s is not open!\n", fileName_);
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
			for (unsigned long b = 0; b < dataLength; b++)
			{
				dataCache_.push_back(static_cast<unsigned char>(data[b]));
			}
			return;
		}
		fprintf(stderr, "%s is not open!\n", fileName_);
	}

	MemoryChunk* DiskFile::Read()
	{
		if (openFlag_)
		{
			if (readOnly_)
			{
				return data_;
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
		if (openFlag_ && readOnly_)
		{
			if (0 != data_)
			{
				return data_->GetSize();
			}
			return 0;
		}
		fprintf(stderr, "%s is not open!\n", fileName_);
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
		for (unsigned long b = 0; b < dataLength; b++)
		{
			data_->Write(dataCache_[b]);
		}
		dataCache_.clear();
	}
} // end namespace


