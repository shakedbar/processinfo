#pragma once

#include "ProcessFinderFactory.h"
#include "ProcessRunningUserFinder.h"

/*
*	@brief		Factory to generate ProcessRunningUserFinder objects for different processes
*/
class ProcessRunningUserFinderFactory : public ProcessFinderFactory
{
public:
	ProcessRunningUserFinderFactory() {}
	/*
	*	@brief		Creates a ProcessRunningUserFinder for the input process handle.
	*
	*	@param		handle - Process handle to use.
	*
	*	@return		Shared pointer to the ProcessRunningUserFinder object.
	*/
	shared_ptr<ProcessInfoFinder> create(HANDLE processHandle) { return make_shared<ProcessRunningUserFinder>(processHandle); }
};