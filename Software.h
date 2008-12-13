
// CODESTYLE: v2.0

// Software.h
// Project: The Virtual Computer Project (VCOMP)
// Author: Richard Marks
// Purpose: A base class for virtual software 

#ifndef __SOFTWARE_H__
#define __SOFTWARE_H__

namespace VCOMP
{
	class Software 
	{
	public:
		
		Software(const char* name);
		
		virtual ~Software();
		
		void SetName(const char* name);
		
		const char* GetName();
		
	protected:
		
		const char* name_;
	}; // end class
} // end namespace
#endif


