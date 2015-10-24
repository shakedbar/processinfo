#pragma once

#include "ProcessFinderFactory.h"
#include "ProcessCpuFinder.h"

/*
*	@brief		Factory to generate ProcessCpuFinder objects for different processes
*/
class ProcessCpuFinderFactory : public ProcessFinderFactory
{
public:
	ProcessCpuFinderFactory() {}
	/*
	*	@brief		Creates a ProcessCpuFinder for the input process handle.
	*
	*	@param		handle - Process handle to use.
	*
	*	@return		Shared pointer to the ProcessCpuFinder object.
	*/
	shared_ptr<ProcessInfoFinder> create(HANDLE processHandle) { return make_shared<ProcessCpuFinder>(processHandle); }
};