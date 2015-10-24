#pragma once

#include "Windows.h"
#include "AutoHandle.h"

/*
*	@brief		Abstract process info factory - interface for the different info finders for processes.
*/
class ProcessInfoFinder
{
   public:
	/*
	*	@brief		Initializes the ProcessInfoFinder - saves the input handle.
	*
	*	@param		handle - Process handle to use.
	*/
	   ProcessInfoFinder(HANDLE processHandle) : m_processHandle(processHandle) {}
	/*
	*	@brief		Gets info for the instance's process.
	*
	*	@return		wstring representation of the info.
	*/
      virtual wstring getInfo() = 0;
   protected:
      HANDLE m_processHandle;
};