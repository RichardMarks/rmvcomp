
// CODESTYLE: v2.0

// Software.cpp
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: A base class for virtual software 
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include "Software.h"


namespace VCOMP
{
	Software::Software(const char* name)
	{
		SetName(name);
	}
	
	Software::~Software()
	{
	}
	
	void Software::SetName(const char* name)
	{
		name_ = strdup(name);
	}
	
	const char* Software::GetName()
	{
		return name_;
	}

} // end namespace


