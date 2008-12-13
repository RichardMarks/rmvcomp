
// CODESTYLE: v2.0

// Processor.h
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: A class to simulate our virtual processor

#ifndef __PROCESSOR_H__
#define __PROCESSOR_H__

#include "ForwardDeclares.h"

namespace VCOMP
{
	
	class Processor
	{
	public:

		Processor();
		~Processor();
		void SetRegisterValue(CPU::Register r, CPU::RegValue value);
		CPU::RegValue GetRegisterValue(CPU::Register r);
		
		void OpCode_Mov(CPU::RegValue value, CPU::Register r) ;
		void OpCode_Mov(CPU::Register a, CPU::Register b);
		void OpCode_Add(CPU::Register a, CPU::Register b);
		void OpCode_Sub(CPU::Register a, CPU::Register b);
		void OpCode_Mul(CPU::Register a, CPU::Register b);
		void OpCode_Div(CPU::Register a, CPU::Register b);
		
	private:

		CPU::RegValue* registers_;
	}; // end class

} // end namespace
#endif


