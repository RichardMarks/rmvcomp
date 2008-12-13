
// CODESTYLE: v2.0

// Drive.cpp
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: A class to simulate a virtual hard disk drive
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include "Drive.h"
#include "DiskFile.h"

namespace VCOMP
{
	
	Drive::Drive(unsigned long bytes) : Device("Disk Drive Device")
	{
		files_ = new DiskFileList();
		capacity_ = bytes;
	}

	Drive::~Drive()
	{
		delete files_; files_ = 0;
	}

	void Drive::ExecuteFile(const char* fileName)
	{
		if(FindFile(fileName))
		{
			fprintf(stderr,
				"Cannot execute %s!\n\n"
				"FILE PARSER UNAVAILABLE AT THIS TIME.\n", fileName);
		}
		else
		{
			fprintf(stderr,
				"%s not found!", fileName);
		}
	}

	void Drive::DeleteFile(const char* fileName)
	{
		NameTableIterator iter;
		if ((iter = directory_.find(fileName)) != directory_.end())
		{
			unsigned int fileID = iter->second;
			DiskFile* file = files_->Get(fileID);
			unsigned long fileSize = file->GetSize();
			directory_.erase(fileName);
			used_ -= fileSize;
		}
		else
		{
			fprintf(stderr,
				"%s not found!", fileName);
		}
	}

	bool Drive::FindFile(const char* fileName)
	{
		NameTableIterator iter;
		if ((iter = directory_.find(fileName)) != directory_.end())
		{
			return true;
		}
		return false;
	}

	void Drive::SaveFile(DiskFile* file, const char* path)
	{
		unsigned long fileSize = file->GetSize();

		if (used_ + fileSize > capacity_)
		{
			fprintf(stderr, "Out of Disk Space while Saving %s%s\n", file->GetFileName(), path);
			return;
		}
	
		if (!FindFile(file->GetFileName()))
		{
			unsigned int fileID = files_->Add(file);
			std::string fullPath;
			fullPath += path;
			fullPath += file->GetFileName();
			directory_[fullPath] = fileID;
			used_ += fileSize;
			
			fprintf(stderr, "Saving file #%d to %s\n", fileID, fullPath.c_str());
		}
		else
		{
			fprintf(stderr,
				"%s exists already!\n"
				"Cannot overwrite files!\n", file->GetFileName());
		}
	}

	DiskFile* Drive::OpenFile(DISKFILE::DISKFILEMODE diskFileMode, const char* fileName)
	{
		if (DISKFILE::Write == diskFileMode)
		{
			DiskFile* file = new DiskFile(fileName);
			file->Open(DISKFILE::Write);
			return file;
		}
		
		// read
		NameTableIterator iter;
		if ((iter = directory_.find(fileName)) != directory_.end())
		{
			unsigned int fileID = iter->second;
			DiskFile* file = files_->Get(fileID);
			file->Open(DISKFILE::Read);
			return file;
		}
		
		return 0;
	}

	void Drive::CloseFile(DiskFile* file)
	{
		file->Close();
	}

	unsigned long Drive::GetDiskUsage()
	{
		return used_;
	}

	unsigned long Drive::GetDiskCapacity()
	{
		return capacity_;
	}

	unsigned int Drive::GetFileCount()
	{
		return files_->GetCount();
	}

} // end namespace


