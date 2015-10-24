#pragma once

#include "ProcessFinderFactory.h"
#include "ProcessRamFinder.h"

/*
*	@brief		Factory to generate ProcessRamFinder objects for different processes
*/
class ProcessRamFinderFactory : public ProcessFinderFactory
{
public:
	ProcessRamFinderFactory() {}
	/*
	*	@brief		Creates a ProcessRamFinder for the input process handle.
	*
	*	@param		handle - Process handle to use.
	*
	*	@return		Shared pointer to the ProcessRamFinder object.
	*/
	shared_ptr<ProcessInfoFinder> create(HANDLE processHandle) { return make_shared<ProcessRamFinder>(processHandle); }
};