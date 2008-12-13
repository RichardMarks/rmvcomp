
// CODESTYLE: v2.0

// Assembler.h
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: A class that implements an assembler for the VCOMP

#ifndef __ASSEMBLER_H__
#define __ASSEMBLER_H__

namespace VCOMP
{
	const int ASSEMBLER_MAX_SOURCE_LINE_LENGTH = 0x1000; // 4096 max characters
	const int ASSEMBLER_MAX_IDENTIFIER_LENGTH = 0x80; // 128 max characters
	
	namespace LL { class Node; class List; }
	
	namespace ASSEMBLER
	{
		typedef struct Operand_Type
		{
			int operandType_;
			union
			{
				int valueAsInteger_;
				float valueAsFloat_;
				int valueAsStringIndex_;
				int valueAsStackIndex_;
				int valueAsInstructionIndex_;
				int valueAsFunctionIndex_;
				int valueAsRegister_;
			};
			int offset_;
			
		} Operand;
		
		typedef struct Instruction_Type
		{
			int opcode_;
			int operandCount_;
			Operand* operands_;
		} Instruction;
		
		typedef struct ExecutableHeader_Type
		{
			int stackSize_;
			int globalDataSize_;
			int autoRunFunctionIndex_;
			int autoRunFunctionExists_;
		} ExecutableHeader;
		
		typedef struct FunctionTableEntry_Type
		{
			int index_;
			char name_[ASSEMBLER_MAX_IDENTIFIER_LENGTH];
			int entryPoint_;
			int parameterCount_;
			int localDataSize_;
		} FunctionTableEntry;
		
		typedef struct SymbolTableEntry_Type
		{
			int index_;
			char name_[ASSEMBLER_MAX_IDENTIFIER_LENGTH];
			int size_; // size of the entry is 1 for variables and > 1 for arrays
			int stackIndex_; // stack index that the symbol points to
			int functionIndex_; // the function that this symbol lives in
		} SymbolTableEntry;
		
		typedef struct LabelTableEntry_Type
		{
			int index_;
			char name_[ASSEMBLER_MAX_IDENTIFIER_LENGTH];
			int targetIndex_; // index of target instruction
			int functionIndex_; // the function that this label lives in
		} LabelTableEntry;
		
	} // end namespace

	class Assembler
	{
	public:
		Assembler();
		~Assembler();
		
	private:
	
		// string table
		int AddString(LL::List* list, char* str);
		
		// function table
		int AddFunction(char* name, int entryPoint);
		void SetFunctionInformation(char* name, int parameterCount, int localDataSize);
		ASSEMBLER::FunctionTableEntry* GetFunction(char* name);
		
		// symbol table
		int AddSymbol(char* name, int size, int stackIndex, int functionIndex);
		ASSEMBLER::SymbolTableEntry* GetSymbol(char* name, int functionIndex);
		int GetIdentifierStackIndex(char* identifier, int functionIndex);
		int GetIdentifierSize(char* identifier, int functionIndex);
		
		// label table
		int AddLabel(char* name, int targetIndex, int functionIndex);
		ASSEMBLER::LabelTableEntry* GetLabel(char* name, int functionIndex);
	
		unsigned int sourceSize_;
		char** sourceCode_;
		LL::List* stringTable_;
		LL::List* functionTable_;
		LL::List* symbolTable_;
		LL::List* labelTable_;
		
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


