
// CODESTYLE: v2.0

// ForwardDeclares.h
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: forward declarations

#ifndef __FORWARDDECLARES_H__
#define __FORWARDDECLARES_H__

namespace VCOMP
{
	class Software;
	class Hardware;
	class Device;

	class Processor;

	class MemoryChunk;
	class DiskFile;

	class Memory;
	class Drive;
	
	namespace DISKFILE 
	{ 
		enum DISKFILEMODE 
		{ 
			Write, 
			Read 
		}; 
	} // end namespace
	
	namespace CPU 
	{ 
		enum Register 
		{ 
			AX, BX, CX, DX, DS, ES, INVALID_REGISTER
		}; 
		
		typedef unsigned long RegValue; 
	} // end namespace
	
} // end namespace

#endif

