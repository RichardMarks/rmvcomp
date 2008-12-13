
// CODESTYLE: v2.0

// Computer.cpp
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: A class to simulate a virtual computer
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include "Computer.h"

#include "Processor.h"
#include "Memory.h"
#include "Drive.h"

namespace VCOMP
{		
	
	

	Computer::Computer(const char* name)
	{
		booted_ = false;
		printf(
			"\nVirtual Computer v2.1\n"
			"Designed and Implemented by Richard Marks <ccpsceo@gmail.com>\n"
			"(C) Copyright 2008, CCPS Solutions All rights reserved.\n"
			"Virtual Hardware Architecture: %s\n", name);
		cpus_ = new ProcessorList();
		banks_ = new MemoryList();
		drives_ = new DriveList();
	}

	Computer::~Computer()
	{
		delete cpus_; cpus_ = 0;
		delete banks_; banks_ = 0;
		delete drives_; drives_ = 0;
	}

	void Computer::Boot()
	{
		static unsigned long nextMem = 0x2400;
	
		fprintf(stderr,
			"System Startup Sequence...\n"
			"> Enumerating CPUs...\n");
		unsigned int totalCpus = cpus_->GetCount();
		for (unsigned int cpuCount = 0; cpuCount < totalCpus; cpuCount++)
		{
			nextMem += (1 + cpuCount) * sizeof(Processor);
			fprintf(stderr, " > Found CPU at 0x%X\n", nextMem);
		}
		fprintf(stderr, (1 == totalCpus) ? "%d Processor OK.\n" : "%d Processors OK.\n", totalCpus);
	
		fprintf(stderr,
			"> RAM Check... %u bytes OK.\n", banks_->GetCount() * 0x800000);
	
		fprintf(stderr,
			"> Enumerating Storage Devices...\n");
		unsigned int totalDrives = drives_->GetCount();
		for (unsigned int driveCount = 0; driveCount < totalDrives; driveCount++)
		{
			Drive* drive = drives_->Get(driveCount);
			unsigned long diskUsed = drive->GetDiskUsage();
			unsigned long diskCapacity = drive->GetDiskCapacity();
			unsigned int fileCount = drive->GetFileCount();
		
			nextMem += (1 + driveCount) * sizeof(Drive);
		
			fprintf(stderr,
				" > Found Drive at 0x%X -> TOTAL: %8d USED: %8d FREE: %8d FILES: %d\n", 
				nextMem,
				diskCapacity,
				diskUsed, 
				diskCapacity - diskUsed, 
				fileCount);
		}
	
		fprintf(stderr,
			"\nNO BOOT CODE FOUND.\nHALTED.\n");
		booted_ = true;
	}

	void Computer::Idle(unsigned long idleTime)
	{
	
	}

	void Computer::PowerOff()
	{
		fprintf(stderr,
			"System Shutdown Sequence...\n"
			"> 3\n"
			"> 2\n"
			"> 1\n"
			"> POWER OFF\n");
		booted_ = false;
	}

	void Computer::LoadSoftware(const char* fileName, Drive* disk)
	{
	
	}

	void Computer::AddCPU()
	{
		cpus_->Add(new Processor());
	}

	void Computer::AddRAMBank(unsigned long bytes)
	{
		// get the number of 8MB memory banks we need
		// for 1GB we need 128 of them
		unsigned int banksNeeded = bytes / 0x800000;
		for (unsigned int bank = 0; bank < banksNeeded; bank++)
		{
			banks_->Add(new Memory());
		}
	}

	void Computer::AddDrive(unsigned long bytes)
	{
		drives_->Add(new Drive(bytes));
	}

	Processor* Computer::GetCPU(unsigned char cpu)
	{
		return cpus_->Get(cpu);
	}

	Memory* Computer::GetRAMBank(unsigned char bank)
	{
		return banks_->Get(bank);
	}

	Drive* Computer::GetDrive(unsigned char drive)
	{
		return drives_->Get(drive);
	}

} // end namespace


