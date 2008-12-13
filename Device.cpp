
// CODESTYLE: v2.0

// Device.cpp
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: A base class for virtual hardware device 
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include "Device.h"


namespace VCOMP
{
	Device::Device(const char* name) : 
		Hardware(name) 
	{
	}
	
	Device::~Device()
	{
	}

} // end namespace


