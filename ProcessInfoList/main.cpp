#include "ProcessCpuFinderFactory.h"
#include "ProcessRamFinderFactory.h"
#include "ProcessRunningUserFinderFactory.h"
#include "ProcessFinderFactory.h"
#include "ProcessPrinter.h"
#include <list>
#include <memory>

using namespace std;

int wmain(int argc, wchar_t** argv)
{
	// Init a list of factories, with all the info getters (cpu, ram and user)
	list<shared_ptr<ProcessFinderFactory>> finderFactories;
	finderFactories.push_back(make_shared<ProcessCpuFinderFactory>());
	finderFactories.push_back(make_shared<ProcessRamFinderFactory>());
	finderFactories.push_back(make_shared<ProcessRunningUserFinderFactory>());

	// Print all the processes info using the ProcessPrinter
	ProcessPrinter printer(finderFactories);

	try 
	{
		printer.printProcessesInfo();
	}
	catch (WinApiException ex)
	{
		wcout << L"Unable to get info for processes. Error: " << ex.what() << endl;
	}
	
}