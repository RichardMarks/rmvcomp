
// CODESTYLE: v2.0

// ComponentList.h
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: A template class for simple lists of pointers to a class

#ifndef __COMPONENTLIST_H__
#define __COMPONENTLIST_H__

#include <vector>

namespace VCOMP
{
	template <typename ComponentType>
	class ComponentList
	{
	public:
		ComponentList() {};
	
		~ComponentList()
		{
			unsigned int count = GetCount();
			for (unsigned int index = 0; index < count; index++)
			{
				if (0 != components_[index])
				{
					delete components_[index];
					components_[index] = 0;
				}
			}
			components_.clear();
		};
	
		unsigned int Add(ComponentType component)
		{
			components_.push_back(component);
			return static_cast<unsigned int>(components_.size() - 1);
		};
	
		ComponentType Get(unsigned int index)
		{
			return components_.at(index);
		};
	
		unsigned int GetCount()
		{
			return static_cast<unsigned int>(components_.size());
		};
	
	private:

		std::vector<ComponentType> components_;
	};

} // end namespace
#endif


