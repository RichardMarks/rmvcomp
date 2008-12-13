
// CODESTYLE: v2.0

// LinkedList.cpp
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: generic linked list class

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "LinkedList.h"

namespace VCOMP
{
	namespace LL
	{
		void List::Initialize()
		{
			head_ = 0;
			tail_ = 0;
			nodeCount_ = 0;
		}
		
		int List::Add(void* data)
		{
			// create a new node
			Node* node = (Node*)malloc(sizeof(Node));
			node->data_ = data;
			node->next_ = 0;
			
			// if the list is empty, set the head and tail to the new node
			if (!nodeCount_)
			{
				head_ = node;
				tail_ = node;
			}
			else
			{
				// append node and update tail
				tail_->next_ = node;
				tail_ = node;
			}
			++nodeCount_;
			return nodeCount_ - 1;
		}
		
		void List::Destroy()
		{
			if (nodeCount_)
			{
				Node* currentNode;
				Node* nextNode;
				
				currentNode = head_;
				
				while(1)
				{
					nextNode = currentNode->next_;
					
					if (currentNode->data_)
					{
						free(currentNode->data_);
					}
					
					if (currentNode)
					{
						free(currentNode);
					}
					
					if (nextNode)
					{
						currentNode = nextNode;
					}
					else
					{
						break;
					}
				}
			}
		}
		
	} // end namespace
} // end namespace


