#pragma once

#include <memory>
#include "ProcessInfoFinder.h"

using namespace std;

/*
*	@brief		Abstract process finder factory - interface for the different generators.
*/
class ProcessFinderFactory 
{
public:
	ProcessFinderFactory() {}
	/*
	*	@brief		Creates a ProcessInfoFinder for the input process handle.
	*
	*	@param		handle - Process handle to use.
	*
	*	@return		Shared pointer to the ProcessInfoFinder object.
	*/
	virtual shared_ptr<ProcessInfoFinder> create(HANDLE processHandle) = 0;
};