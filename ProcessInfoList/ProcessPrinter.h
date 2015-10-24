#pragma once

#include <memory>
#include <list>
#include "Windows.h"
#include "TlHelp32.h"
#include "ProcessFinderFactory.h"

using namespace std;

/*
*	@brief		Prints information for all the running processes.
*/
class ProcessPrinter
{
public:
	/*
	*	@brief		Initializes the ProcessPrinter - saves the list of ProcessFinderFactory.
	*
	*	@param		infoFactories - list of ProcessFinderFactory to generate ProcessInfoFinder objects to get data.
	*/
	ProcessPrinter(list<shared_ptr<ProcessFinderFactory>> infoFactories) : m_infoFactories(infoFactories) {}
	/*
	*	@brief		Prints information for all the running processes.
	*/
	void printProcessesInfo();
private:
	list<shared_ptr<ProcessFinderFactory>> m_infoFactories;
	/*
	*	@brief		Prints a single process' information safely.
	*				In case of error, prints the error message.
	*	@param		processInfo - PROCESSENTRY32W object with the process info.
	*/
	void safePrintProcess(PROCESSENTRY32W processInfo);
	/*
	*	@brief		Prints a single process' information, by calling all the ProcessInfoFinders
	*	@param		processInfo - PROCESSENTRY32W object with the process info.
	*/
	void printProcess(PROCESSENTRY32W processInfo);
};