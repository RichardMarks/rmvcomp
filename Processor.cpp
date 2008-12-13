
// CODESTYLE: v2.0

// Processor.cpp
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: A class to simulate our virtual processor
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include "Processor.h"

namespace VCOMP
{
	Processor::Processor()
	{
		registers_ = new CPU::RegValue [6];
		registers_[0] = 0;
		registers_[1] = 0;
		registers_[2] = 0;
		registers_[3] = 0;
		registers_[4] = 0;
		registers_[5] = 0;
	}

	/**************************************************************************/
	
	Processor::~Processor()
	{
		delete [] registers_;
	}

	/**************************************************************************/
	
	void Processor::SetRegisterValue(CPU::Register r, CPU::RegValue value)
	{
		registers_[static_cast<unsigned int>(r)] = value;
	}

	/**************************************************************************/
	
	CPU::RegValue Processor::GetRegisterValue(CPU::Register r)
	{
		return registers_[static_cast<unsigned int>(r)];
	}

	/**************************************************************************/
	
	void Processor::OpCode_Mov(CPU::RegValue value, CPU::Register r) 
	{ 
		SetRegisterValue(r, value); 
	}

	/**************************************************************************/
	
	void Processor::OpCode_Mov(CPU::Register a, CPU::Register b)
	{
		SetRegisterValue(b, GetRegisterValue(a));
	}

	/**************************************************************************/
	
	void Processor::OpCode_Add(CPU::Register a, CPU::Register b) 
	{
		CPU::RegValue valueA = GetRegisterValue(a);
		CPU::RegValue valueB = GetRegisterValue(b);
		SetRegisterValue(CPU::ES, valueA + valueB);
	}

	/**************************************************************************/
	
	void Processor::OpCode_Sub(CPU::Register a, CPU::Register b)
	{
		CPU::RegValue valueA = GetRegisterValue(a);
		CPU::RegValue valueB = GetRegisterValue(b);
		SetRegisterValue(CPU::ES, valueA - valueB);
	}

	/**************************************************************************/
	
	void Processor::OpCode_Mul(CPU::Register a, CPU::Register b)
	{
		CPU::RegValue valueA = GetRegisterValue(a);
		CPU::RegValue valueB = GetRegisterValue(b);
		SetRegisterValue(CPU::ES, valueA * valueB);
	}
	
	/**************************************************************************/
	
	void Processor::OpCode_Div(CPU::Register a, CPU::Register b)
	{
		CPU::RegValue valueA = GetRegisterValue(a);
		CPU::RegValue valueB = GetRegisterValue(b);
		SetRegisterValue(CPU::ES, valueA / valueB);
	}
	
} // end namespace


