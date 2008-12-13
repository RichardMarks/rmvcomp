
// CODESTYLE: v2.0

// Tokenizer.h
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: generic linked list class

#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

namespace VCOMP
{
	// linked list
	namespace LL
	{
		class Node
		{
		public:
			void* data_;
			Node* next_;
		};
		
		class List
		{
		public:
			Node* head_;
			Node* tail_;
			int nodeCount_;
			
			void Initialize();
			void Destroy();
			int Add(void* data);
		};
		
	} // end namespace
	
} // end namespace

#endif


