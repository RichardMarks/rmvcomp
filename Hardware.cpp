
// CODESTYLE: v2.0

// Hardware.cpp
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: A base class for virtual hardware 
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include "Hardware.h"


namespace VCOMP
{
	Hardware::Hardware(const char* name)
	{
		SetName(name);
	}
	
	Hardware::~Hardware()
	{
	}
	
	void Hardware::SetName(const char* name)
	{
		name_ = strdup(name);
	}
	
	const char* Hardware::GetName()
	{
		return name_;
	}

} // end namespace


