
// CODESTYLE: v2.0

// Computer.h
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: A class to simulate a virtual computer

#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include "ForwardDeclares.h"
#include "ComponentList.h"

namespace VCOMP
{	

	class Computer 
	{
	public:
		Computer(const char* name);
	
		~Computer();
	
		void Boot();
	
		void Idle(unsigned long idleTime);
	
		void PowerOff();
	
		void LoadSoftware(const char* fileName, Drive* disk);
	
		void AddCPU();
	
		void AddRAMBank(unsigned long bytes);
	
		void AddDrive(unsigned long bytes);
	
		Processor* GetCPU(unsigned char cpu);
	
		Memory* GetRAMBank(unsigned char bank);
	
		Drive* GetDrive(unsigned char drive);
	
	private:
		
		typedef class ComponentList<Processor*> ProcessorList;
		typedef class ComponentList<Memory*> MemoryList;
		typedef class ComponentList<Drive*> DriveList;
		
	
		ProcessorList* cpus_;
		MemoryList* banks_;
		DriveList* drives_;
		bool booted_;
	}; // end class

} // end namespace
#endif


