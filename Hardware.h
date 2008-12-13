
// CODESTYLE: v2.0

// Hardware.h
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: A base class for virtual hardware 

#ifndef __HARDWARE_H__
#define __HARDWARE_H__

namespace VCOMP
{
	class Hardware 
	{
	public:
		
		Hardware(const char* name);
		
		virtual ~Hardware();
		
		void SetName(const char* name);
		
		const char* GetName();
		
	protected:
		
		const char* name_;
	}; // end class

} // end namespace
#endif


