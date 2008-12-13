
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

#include "Tokenizer.h"

using namespace VCOMP;

class AssemblerSoftware : public Software
{
public:
	AssemblerSoftware();
	~AssemblerSoftware();
	void LoadData(MemoryChunk* source);
	DiskFile* Assemble(const char* outputName);
	
private:
	void Destroy();
	
	void Parse();
	void ParseLine();
	
	std::string source_;
};

AssemblerSoftware::AssemblerSoftware() : 
	Software("Virtual Assembler 1.0")
{
}

AssemblerSoftware::~AssemblerSoftware()
{
	Destroy();
}

void AssemblerSoftware::Destroy()
{
	source_ = "";
}

void AssemblerSoftware::LoadData(MemoryChunk* source)
{
	Destroy();
	
	unsigned long dataLength = source->GetSize();

	for (unsigned long b = 0; b < dataLength; b++)
	{
		source_ += source->Read();
	}
}

void AssemblerSoftware::Parse()
{
}

void AssemblerSoftware::ParseLine(unsigned int lineIndex, const std::vector<std::string>& lineTokens)
{
	// if the first token of the line is not a string
	// then we bail with an error
	if (!RMUL::Tokenizer::IsString(lineTokens.at(0)))
	{
		fprintf(stderr, "Invalid Token at line #%d token#0 (%s)\n", lineIndex + 1, lineTokens.at(0).c_str());
		return;
	}
	
	unsigned int numLineTokens = lineTokens.size();

	// what mnemonic
	std::string mnemonic = lineTokens.at(0);
	if (mnemonic == "ret")
	{
		fprintf(stderr, "RETURN mnemonic: %s\n", mnemonic.c_str());
		std::string d = "";
		d += static_cast<unsigned char>(1);
		file->Write(d.c_str());
	} else if (mnemonic == "mov")
	{
		fprintf(stderr, "MOVE mnemonic: %s\n", mnemonic.c_str());
		
		// get operands
		if (numLineTokens == 3)
		{
			std::string operandA = lineTokens.at(1);
			std::string operandB = lineTokens.at(2);
			
			if (RMUL::Tokenizer::IsNumber(operandA))
			{
				CPU::RegValue source = static_cast<CPU::RegValue>(atoi(operandA.c_str()));
			}
			else
			{
				CPU::Register source = CPU::INVALID_REGISTER;
				if (operandA == "ax") { source = CPU::AX; }
				if (operandA == "bx") { source = CPU::BX; }
				if (operandA == "cx") { source = CPU::CX; }
				if (operandA == "dx") { source = CPU::DX; }
				if (operandA == "ds") { source = CPU::DS; }
				if (operandA == "es") { source = CPU::ES; }
				if (CPU::INVALID_REGISTER == source)
				{
					fprintf(stderr, "Invalid Operand. Expected: Register\n");
				}
			}
		}
		else
		{
			fprintf(stderr, "Missing Operands. Expected: mnemonic operand, operand\n");
		}
		
	} else if (mnemonic == "add")
	{
		fprintf(stderr, "ADD mnemonic: %s\n", mnemonic.c_str());
	} else if (mnemonic == "sub")
	{
		fprintf(stderr, "SUBTRACT mnemonic: %s\n", mnemonic.c_str());
	} else if (mnemonic == "mul")
	{
		fprintf(stderr, "MULTIPLY mnemonic: %s\n", mnemonic.c_str());
	} else if (mnemonic == "div")
	{
		fprintf(stderr, "DIVIDE mnemonic: %s\n", mnemonic.c_str());
	}
	else
	{
		fprintf(stderr, "Unknown mnemonic: %s\n", mnemonic.c_str());
	}
}

DiskFile* AssemblerSoftware::Assemble(const char* outputName)
{
	DiskFile* file = new DiskFile(outputName);
	file->Open(DISKFILE::Write);
	
	fprintf(stderr, "Assembling %s...\n", outputName);
	
	std::vector<std::string> codeLines = RMUL::Tokenizer::Tokenize(source_, "\n");
	
	unsigned int numLines = codeLines.size();
	
	fprintf(stderr, "> assembly source code to be assembled contains %d lines.\n", numLines);
	
	for (unsigned int lineIndex = 0; lineIndex < numLines; lineIndex++)
	{
		std::vector<std::string> lineTokens = RMUL::Tokenizer::Tokenize(codeLines.at(lineIndex), " ,");
		
		
		fprintf(stderr, "> parsing line %d: %s\n", lineIndex + 1, codeLines.at(lineIndex).c_str());
		
		ParseLine(lineIndex, lineTokens);
	}
	
#if 0
		for (unsigned int tokenIndex = 0; tokenIndex < numLineTokens; tokenIndex++)
		{
			std::string token = lineTokens.at(tokenIndex);
			fprintf(stderr, "> Token # %d: %s (length = %d)\n", tokenIndex + 1, token.c_str(), token.size());

			if (token == "ret")
			{
				fprintf(stderr, "RETURN Token: %s\n", token.c_str());
				std::string d = "";
				d += static_cast<unsigned char>(1);
				file->Write(d.c_str());
			} else if (token == "mov")
			{
				fprintf(stderr, "MOVE Token: %s\n", token.c_str());
			} else if (token == "add")
			{
				fprintf(stderr, "ADD Token: %s\n", token.c_str());
			} else if (token == "sub")
			{
				fprintf(stderr, "SUBTRACT Token: %s\n", token.c_str());
			} else if (token == "mul")
			{
				fprintf(stderr, "MULTIPLY Token: %s\n", token.c_str());
			} else if (token == "div")
			{
				fprintf(stderr, "DIVIDE Token: %s\n", token.c_str());
			}
			else
			{
				fprintf(stderr, "Unknown Token: %s\n", token.c_str());
			}			
		}
#endif

	
	fprintf(stderr, "Finished. %d bytes assembled.\n", file->GetSize());
	file->Close();
	return file;
}

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
		"\nmov 5, ax\n"
		"mov 5, bx\n"
		"add ax, bx\n"
		"ret";
	
	// open a disk-file on the user's virtual drive called pgm1.asm
	// fprintf(stderr, "open a disk-file on the user's virtual drive called pgm1.asm\n");
	DiskFile* file = usrDisk->OpenFile(DISKFILE::Write, "pgm1.asm");
	
	// write the string for our program to the disk-file 
	file->Write(program1);
	
	// close the disk-file
	usrDisk->CloseFile(file);
	
	// save the disk-file to the user's drive
	usrDisk->SaveFile(file, "/");
	
	//+DEBUG
#if 0
	{
		unsigned long diskUsed = usrDisk->GetDiskUsage();
		unsigned long diskCapacity = usrDisk->GetDiskCapacity();
		unsigned int fileCount = usrDisk->GetFileCount();

		fprintf(stderr,
			"Drive: USER\tTOTAL: %8d\tUSED: %8d\tFREE: %8d\tFILES: %d\n", 
			diskCapacity,
			diskUsed, 
			diskCapacity - diskUsed, 
			fileCount);
	}
#endif
	//-DEBUG
	
	
	// open the disk-file that we saved to the user's virtual drive
	//fprintf(stderr, "open the disk-file that we saved to the user's virtual drive\n");
	file = usrDisk->OpenFile(DISKFILE::Read, "/pgm1.asm");
	
	// get the number of bytes that the file takes up
	unsigned long fileSize = file->GetSize();
	
	// get a pointer to the virtual RAM data bank
	Memory* userData = pc->GetRAMBank(0x0);
	
	MemoryChunk* fileContents = file->Read();
	
	// write the contents of the disk-file to the memory bank
	//fprintf(stderr, "write the contents of the disk-file to the memory bank\n");
	
	//fprintf(stderr, "\nfileSize = %d\nuserData = 0x%X08\nfileContents = 0x%X08\n\n", fileSize, &userData, &fileContents);
	
	userData->Write(0x0, fileContents);
	
	// close the disk file
	usrDisk->CloseFile(file);
	
	// get a pointer to the chunk of memory that we just loaded
	MemoryChunk* memFile = userData->Read(0x0, fileSize);
	
	// create a new assembler software
	AssemblerSoftware* assembler = new AssemblerSoftware();
	
	// load the memory chunk file that we read earlier into our assembler
	//fprintf(stderr, "load the memory chunk file that we read earlier into our assembler\n");
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

