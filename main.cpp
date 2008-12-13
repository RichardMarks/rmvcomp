
// CODESTYLE: v2.0

// main.cpp
// Project: Virtual Machine (VM)
// Author: Richard Marks

#include "Computer.h"
#include "Memory.h"
#include "Drive.h"
#include "MemoryChunk.h"
#include "DiskFile.h"
#include "Software.h"

using namespace VCOMP;

class AssemblerSoftware : public Software
{
public:
	AssemblerSoftware(MemoryChunk* source) : Software("Virtual Assembler 1.0")
	{
	};
	
	void LoadData(MemoryChunk* source){};
	DiskFile* Assemble(const char* outputName)
	{
		DiskFile* file = new DiskFile(outputName);
		return file;
	}
private:
};

/******************************************************************************/

int main(int argc, char* argv[])
{
	// create a virtual computer
	Computer* pc = new Computer("RM4-RK5");
	
	pc->AddCPU(); // add a CPU
	pc->AddRAMBank(0x4000000); // add 1 GB of RAM
	pc->AddDrive(0x2000000); // add a 512MB drive for the system
	pc->AddDrive(0x4000000); // add a 1GB drive for user data
	
	// get pointers to the drives
	Drive* sysDisk = pc->GetDrive(0x0);
	Drive* usrDisk = pc->GetDrive(0x1);
	
	// load some software into the virtual machine from the real computer 
	// into the virtual drive
	pc->LoadSoftware("microOS.bin", sysDisk);
	
	// boot the virtual computer, which in turn fires up the VBIOS 
	// which searches the system disk for an operating system
	// this will in turn boot the micro OS that we loaded
	pc->Boot();

	// write a simple assembly program
	// that adds 5 and 5 and stores the result in the es register
	// the micro OS displays the values in all the registers on the screen
	// so we don't have to do anything funky to see what the program does
	const char* program1 =
		"mov 5, ax\n"
		"mov 5, bx\n"
		"add ax, bx\n"
		"ret\n";
	
	// open a disk-file on the user's virtual drive called pgm1.asm
	DiskFile* file = usrDisk->OpenFile(DISKFILE::Write, "pgm1.asm");
	
	// write the string for our program to the disk-file 
	file->Write(program1);
	
	// close the disk-file
	usrDisk->CloseFile(file);
	
	// open the disk-file that we saved to the user's virtual drive
	file = usrDisk->OpenFile(DISKFILE::Read, "pgm1.asm");
	
	// get the number of bytes that the file takes up
	unsigned long fileSize = file->GetSize();
	
	// get a pointer to the virtual RAM data bank
	Memory* userData = pc->GetRAMBank(0x0);
	
	// write the contents of the disk-file to the memory bank
	userData->Write(0x0, file->Read());
	
	// close the disk file
	usrDisk->CloseFile(file);
	
	// get a pointer to the chunk of memory that we just loaded
	MemoryChunk* memFile = userData->Read(0x0, fileSize);
	
	// assemble the program in memory and save it to the system virtual drive
	
	// open the disk-file on the system virtual drive called /bin/assembler
	file = sysDisk->OpenFile(DISKFILE::Read, "/bin/assembler");
	
	// create a new software from the disk-file
	AssemblerSoftware* assembler = new AssemblerSoftware(file->Read());
	
	// load the memory chunk file that we read earlier into our assembler
	assembler->LoadData(memFile);
	
	// assemble the program that we created, and store the result in the
	// new disk-file called program1
	DiskFile* executable = assembler->Assemble("program1");
	
	// delete the assembler software that we created, since we no longer need it
	delete assembler;
	
	// save the new disk-file that contains our assembled executable program
	// to the system virtual drive in the /user/ virtual folder
	sysDisk->SaveFile(executable, "/user/");
	
	// execute the assembled program
	sysDisk->ExecuteFile("/user/program1");
	
	// delete the program from the system virtual drive
	sysDisk->DeleteFile("/user/program1");
	
	// idle for 5 seconds and then 
	pc->Idle(5);
	
	// power off the virtual computer
	pc->PowerOff();
	
	// delete the virtual computer (handles releasing all allocated resources for drives & ram)
	delete pc;
	
	// return us to the real computer operating system
	return 0;
}

