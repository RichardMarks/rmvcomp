
// CODESTYLE: v2.0

// Device.h
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: A base class for virtual hardware device 

#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "Hardware.h"

namespace VCOMP
{
	class Device : public Hardware 
	{
	public:
		Device(const char* name);
		
		~Device();
		
	}; // end class
} // end namespace
#endif


