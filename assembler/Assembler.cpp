
// CODESTYLE: v2.0

// Assembler.cpp
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: A class that implements an assembler for the VCOMP

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "Assembler.h"

#include "LinkedList.h"

namespace VCOMP
{
	
	
	Assembler::Assembler()
	{
		stringTable_ = new LL::List;
		functionTable_ = new LL::List;
	}
	
	Assembler::~Assembler()
	{
		delete stringTable_;
		delete functionTable_;
	}
	
	int Assembler::AddString(LL::List* list, char* str)
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
	
	int Assembler::AddFunction(char* name, int entryPoint)
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
	
	void Assembler::SetFunctionInformation(char* name, int parameterCount, int localDataSize)
	{
		ASSEMBLER::FunctionTableEntry* node = GetFunction(name);
		node->parameterCount_ = parameterCount;
		node->localDataSize_ = localDataSize;
	}
	
	ASSEMBLER::FunctionTableEntry* Assembler::GetFunction(char* name)
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
	
	int Assembler::AddSymbol(char* name, int size, int stackIndex, int functionIndex)
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
	
	ASSEMBLER::SymbolTableEntry* Assembler::GetSymbol(char* name, int functionIndex)
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
	
	int Assembler::GetIdentifierStackIndex(char* identifier, int functionIndex)
	{
		ASSEMBLER::SymbolTableEntry* node = GetSymbol(identifier, functionIndex);
		return node->stackIndex_;
	}
	
	int Assembler::GetIdentifierSize(char* identifier, int functionIndex)
	{
		ASSEMBLER::SymbolTableEntry* node = GetSymbol(identifier, functionIndex);
		return node->size_;
	}
	
	int Assembler::AddLabel(char* name, int targetIndex, int functionIndex)
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
	
	ASSEMBLER::LabelTableEntry* Assembler::GetLabel(char* name, int functionIndex)
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
	
} // end namespace


