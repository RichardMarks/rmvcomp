
// CODESTYLE: v2.0

// Assembler.cpp
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: A class that implements an assembler for the VCOMP

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "Assembler.h"
#include "Tokenizer.h"

#include "LinkedList.h"

namespace VCOMP
{
	
	
	Assembler::Assembler()
	{
		stringTable_ = new LL::List;
		functionTable_ = new LL::List;
		instructionTable_ = new ASSEMBLER::InstructionTable [ASSEMBLER_MAX_INSTRUCTIONS];
		
		
		
		// define instruction set
		int index = 0;
		int opcode = 0;

		// memory
		index = AddInstruction("mov", opcode++, 2);
		SetOperandType(index, 0, ASSEMBLER::OpFlag_Register | ASSEMBLER::OpFlag_Memory | ASSEMBLER::OpFlag_String | ASSEMBLER::OpFlag_Float | ASSEMBLER::OpFlag_Integer);
		SetOperandType(index, 1, ASSEMBLER::OpFlag_Register | ASSEMBLER::OpFlag_Memory);
		
		// math
		index = AddInstruction("add", opcode++, 2);
		index = AddInstruction("sub", opcode++, 2);
		index = AddInstruction("mul", opcode++, 2);
		index = AddInstruction("div", opcode++, 2);
		index = AddInstruction("mod", opcode++, 2);
		index = AddInstruction("exp", opcode++, 2);
		index = AddInstruction("neg", opcode++, 1);
		index = AddInstruction("inc", opcode++, 1);
		index = AddInstruction("dec", opcode++, 1);
		
		// bit operations
		index = AddInstruction("and", opcode++, 2);
		index = AddInstruction("or", opcode++, 2);
		index = AddInstruction("xor", opcode++, 2);
		index = AddInstruction("not", opcode++, 1);
		index = AddInstruction("shl", opcode++, 2);
		index = AddInstruction("shr", opcode++, 2);
		
		// string processing
		index = AddInstruction("cat", opcode++, 2);
		index = AddInstruction("gch", opcode++, 3);
		index = AddInstruction("sch", opcode++, 3);
		
		// logic
		index = AddInstruction("jmp", opcode++, 1);
		index = AddInstruction("je", opcode++, 3);
		index = AddInstruction("jne", opcode++, 3);
		index = AddInstruction("jg", opcode++, 3);
		index = AddInstruction("jl", opcode++, 3);
		index = AddInstruction("jge", opcode++, 3);
		index = AddInstruction("jle", opcode++, 3);
		
		// stack manipulation
		index = AddInstruction("push", opcode++, 1);
		index = AddInstruction("pop", opcode++, 1);
		
		// function calls
		index = AddInstruction("call", opcode++, 1);
		index = AddInstruction("ret", opcode++, 0);
		
		// misc
		index = AddInstruction("pause", opcode++, 1);
		index = AddInstruction("exit", opcode++, 1);
	}
	
	Assembler::~Assembler()
	{
		delete stringTable_;
		delete functionTable_;
		delete [] instructionTable_;
	}
	
	int Assembler::AddString(LL::List* list, const char* str)
	{
		LL::Node* node = list->head_;
		
		for (int index = 0; index < list->nodeCount_; index++)
		{
			if (0 == strcmp((char*)node->data_, str))
			{
				return index;
			}
			node = node->next_;
		}
		
		char* strNode = (char*)malloc(strlen(str)+1);
		strcpy(strNode, str);
		return list->Add(strNode);
	}
	
	int Assembler::AddFunction(const char* name, int entryPoint)
	{
		if (GetFunction(name))
		{
			// cannot add if it already exists
			// return invalid index value
			return -1;
		}
		
		ASSEMBLER::FunctionTableEntry* node = (ASSEMBLER::FunctionTableEntry*)malloc(sizeof(ASSEMBLER::FunctionTableEntry));
		strcpy(node->name_, name);
		node->entryPoint_ = entryPoint;
		int index = functionTable_->Add(node);
		node->index_ = index;
		return index;
	}
	
	void Assembler::SetFunctionInformation(const char* name, int parameterCount, int localDataSize)
	{
		ASSEMBLER::FunctionTableEntry* node = GetFunction(name);
		node->parameterCount_ = parameterCount;
		node->localDataSize_ = localDataSize;
	}
	
	ASSEMBLER::FunctionTableEntry* Assembler::GetFunction(const char* name)
	{
		// if the function table is empty, return 0
		if (!functionTable_->nodeCount_)
		{
			return 0;
		}
		
		LL::Node* currentNode = functionTable_->head_;
		
		for (int index = 0; index < functionTable_->nodeCount_; index++)
		{
			ASSEMBLER::FunctionTableEntry* node = (ASSEMBLER::FunctionTableEntry*)currentNode->data_;
			
			if (0 == strcmp(node->name_, name))
			{
				return node;
			}
			currentNode = currentNode->next_;
		}
		
		return 0;
	}
	
	int Assembler::AddSymbol(const char* name, int size, int stackIndex, int functionIndex)
	{
		if (GetSymbol(name, functionIndex))
		{
			// already exists
			return -1;
		}
		
		ASSEMBLER::SymbolTableEntry* node = (ASSEMBLER::SymbolTableEntry*)malloc(sizeof(ASSEMBLER::SymbolTableEntry));
		strcpy(node->name_, name);
		node->size_ = size;
		node->stackIndex_ = stackIndex;
		node->functionIndex_ = functionIndex;
		int index = symbolTable_->Add(node);
		node->index_ = index;
		return index;
	}
	
	ASSEMBLER::SymbolTableEntry* Assembler::GetSymbol(const char* name, int functionIndex)
	{
		if (!symbolTable_->nodeCount_)
		{
			// no entries
			return 0;
		}
		
		LL::Node* currentNode = symbolTable_->head_;
		
		for (int index = 0; index < symbolTable_->nodeCount_; index++)
		{
			ASSEMBLER::SymbolTableEntry* node = (ASSEMBLER::SymbolTableEntry*)currentNode->data_;
			
			if (0 == strcmp(node->name_, name))
			{
				if (node->functionIndex_ == functionIndex || node->stackIndex_ >= 0)
				{
					return node;
				}
			}
			currentNode = currentNode->next_;
		}
		
		return 0;
	}
	
	int Assembler::GetIdentifierStackIndex(const char* identifier, int functionIndex)
	{
		ASSEMBLER::SymbolTableEntry* node = GetSymbol(identifier, functionIndex);
		return node->stackIndex_;
	}
	
	int Assembler::GetIdentifierSize(const char* identifier, int functionIndex)
	{
		ASSEMBLER::SymbolTableEntry* node = GetSymbol(identifier, functionIndex);
		return node->size_;
	}
	
	int Assembler::AddLabel(const char* name, int targetIndex, int functionIndex)
	{
		if (GetLabel(name, functionIndex))
		{
			// already exists
			return -1;
		}
		
		ASSEMBLER::LabelTableEntry* node = (ASSEMBLER::LabelTableEntry*)malloc(sizeof(ASSEMBLER::LabelTableEntry));
		strcpy(node->name_, name);
		node->targetIndex_ = targetIndex;
		node->functionIndex_ = functionIndex;
		int index = labelTable_->Add(node);
		node->index_ = index;
		return index;
	}
	
	ASSEMBLER::LabelTableEntry* Assembler::GetLabel(const char* name, int functionIndex)
	{
		if (!labelTable_->nodeCount_)
		{
			// no entries
			return 0;
		}
		
		LL::Node* currentNode = labelTable_->head_;
		
		for (int index = 0; index < labelTable_->nodeCount_; index++)
		{
			ASSEMBLER::LabelTableEntry* node = (ASSEMBLER::LabelTableEntry*)currentNode->data_;
			
			if (0 == strcmp(node->name_, name))
			{
				if (node->functionIndex_ == functionIndex)
				{
					return node;
				}
			}
			currentNode = currentNode->next_;
		}
		
		return 0;
	}
	
	int Assembler::AddInstruction(const char* mnemonic, int opcode, int operandCount)
	{
		static unsigned int nextInstructionIndex = 0;
		if (nextInstructionIndex >= ASSEMBLER_MAX_INSTRUCTIONS)
		{
			// cannot add anymore!
			return -1;
		}
		
		strcpy(instructionTable_[nextInstructionIndex].mnemonic_, mnemonic);
		
		PARSING::StringProcessor::UCase(instructionTable_[nextInstructionIndex].mnemonic_);
		
		//strupr(instructionTable_[nextInstructionIndex].mnemonic_);
		
		instructionTable_[nextInstructionIndex].opcode_ = opcode;
		instructionTable_[nextInstructionIndex].operandCount_ = operandCount;
		instructionTable_[nextInstructionIndex].operandList_ = (ASSEMBLER::ByteX4*)malloc(operandCount * sizeof(ASSEMBLER::ByteX4));
		nextInstructionIndex++;
		return nextInstructionIndex - 1;
	}
	
	void Assembler::SetOperandType(int instructionIndex, int operandIndex, ASSEMBLER::ByteX4 operandType)
	{
		instructionTable_[instructionIndex].operandList_[operandIndex] = operandType;
	}
	
} // end namespace


