#pragma once

#include "ProcessInfoFinder.h"
#include <iostream>

#define MAX_NAME 256

using namespace std;

/*
*	@brief		Gets the CPU usage info for processes.
*/
class ProcessCpuFinder : public ProcessInfoFinder
{
public:
	/*
	*	@brief		Initializes the ProcessInfoFinder - saves the input handle.
	*
	*	@param		handle - Process handle to use.
	*/
	ProcessCpuFinder(HANDLE processHandle);
	/*
	*	@brief		Gets CPU info for the instance's process.
	*
	*	@return		wstring representation of the info.
	*/
	wstring getInfo();
private:
	/*
	*	@brief		Computes the time difference in ms between 2 FILETIME objects
	*
	*	@param		ftA - Time to substract from.
	*	@param		ftB - Time to substract.
	*/
	ULONGLONG subtractTimes(const FILETIME& ftA, const FILETIME& ftB);
	DWORD m_numProcessors;
};