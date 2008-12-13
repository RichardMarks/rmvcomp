
// CODESTYLE: v2.0

// Assembler.h
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: A class that implements an assembler for the VCOMP

#ifndef __ASSEMBLER_H__
#define __ASSEMBLER_H__

namespace VCOMP
{
	class Assembler
	{
	public:
		Assembler();
		~Assembler();
	}; // end class

} // end namespace

#if 1
/*
	THE VCOMP INSTRUCTION SET


	Memory:
	
		mov source, destination
	
	Math:
	
		add source, destination
		sub source, destination
		mul source, destination
		div source, destination
		mod source, destination
		exp power, destination
		neg destination
		inc destination
		dec destination
		
	Bit Operations:
	
		and source, destination
		or source, destination
		xor source, destination
		not destination
		shl count, destination
		shr count, destination
		
	String Processing:
	
		cat source, destination
		gch source, index, destination
		sch source, index, destination
		
	Conditional Logic:
	
		jmp label
		je operand1, operand2, label
		jne operand1, operand2, label
		jg operand1, operand2, label
		jl operand1, operand2, label
		jge operand1, operand2, label
		jle operand1, operand2, label
		
	Stack Manipulation:
	
		push source
		pop destination
		
	Function Calls:
	
		call functionName
		ret
		
	Misc:
	
		pause duration
		exit exit_code
		
	
	
	Defining a function:
	
		function functionName { ...code... }
		
	Declaring the parameters of a function:
	
		param paramName
		
		
	Defining a variable:
	
		var variableName
		var variableName[elementCount]
		
	
	EXECUTABLE FORMAT:
	
		Header:
			4 bytes ID "VCEF" (Virtual Computer Executable File)
			1 byte MAJOR VERSION #
			1 byte MINOR VERSION #
			4 bytes OPTIONAL_STACK_SIZE (0 uses default stack size)
			4 bytes GLOBAL_DATA_SIZE
			1 byte AUTORUN (set to 0 or 1)
			4 bytes AUTORUN FUNCTION INDEX #
			
		Code Segment:
			4 bytes INSTRUCTION_COUNT
			Instruction Stream:
				1 byte opcode
				Operand Stream:
					1 byte OPERAND_COUNT
					Operand:
						1 byte OPERAND_TYPE
							Operand Types:
								0 literal integer value
								1 literal floating point value
								2 literal string index
								3 absolute stack index
								4 relative stack index
								5 jump target
								6 function table index
								7 special register
						N bytes OPERAND_DATA
						
		Data Segment:
			4 bytes STRING_COUNT
			String Entry:
				4 bytes STRING_LENGTH
				N bytes STRING_CONTENTS
				
		Function Table:
			4 bytes FUNCTION_COUNT
			Functions:
				4 bytes index of the first instruction for the function
				1 byte PARAMETER_COUNT
				4 bytes LOCAL_DATA_SIZE
		
	

 */
#endif

#endif


