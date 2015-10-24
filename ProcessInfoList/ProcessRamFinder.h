#pragma once

#include "ProcessInfoFinder.h"
#include <iostream>
#include "psapi.h"

#define MAX_NAME 256

/*
*	@brief		Gets the RAM usage info for processes.
*/
class ProcessRamFinder : public ProcessInfoFinder
{
public:
	/*
	*	@brief		Initializes the ProcessInfoFinder - saves the input handle.
	*
	*	@param		handle - Process handle to use.
	*/
	ProcessRamFinder(HANDLE processHandle) : ProcessInfoFinder(processHandle) {}
	/*
	*	@brief		Gets RAM info for the instance's process.
	*
	*	@return		wstring representation of the info.
	*/
	wstring getInfo();
};