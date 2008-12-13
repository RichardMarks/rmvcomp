
// CODESTYLE: v2.0

// Drive.h
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: A class to simulate a virtual hard disk drive

#ifndef __DRIVE_H__
#define __DRIVE_H__

#include <string>
#include <map>

#include "Device.h"
#include "ComponentList.h"
#include "ForwardDeclares.h"
namespace VCOMP
{
	class DiskFile;
	
	class Drive : public Device 
	{
	public:
		Drive(unsigned long bytes);
	
		~Drive();
	
		void ExecuteFile(const char* fileName);
	
		void DeleteFile(const char* fileName);
	
		bool FindFile(const char* fileName);
	
		void SaveFile(DiskFile* file, const char* path);
	
		void CloseFile(DiskFile* file);
	
		unsigned long GetDiskUsage();
	
		unsigned long GetDiskCapacity();
	
		unsigned int GetFileCount();
	
		DiskFile* OpenFile(DISKFILE::DISKFILEMODE diskFileMode, const char* fileName);
	
	private:
		typedef std::map<std::string, unsigned int> NameTable;
		typedef std::map<std::string, unsigned int>::iterator NameTableIterator;
		typedef class ComponentList<DiskFile*> DiskFileList; 
		
		NameTable directory_;
		DiskFileList* files_;
		unsigned long capacity_;
		unsigned long used_;
	};
// end class

} // end namespace
#endif


