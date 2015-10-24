#include "ProcessRamFinder.h"

wstring ProcessRamFinder::getInfo()
{
	PROCESS_MEMORY_COUNTERS pmc;
    if (!GetProcessMemoryInfo(m_processHandle, &pmc, sizeof(pmc)))
	{
		throw WinApiException("Unable to get process memory");
	}

	wstringstream stringstream;

	// Get the physical RAM usage of the process by getting the WorkingSetSize from the PROCESS_MEMORY_COUNTERS.
	stringstream << L"Ram Usage: " << pmc.WorkingSetSize / 1024 << " KBs";
	return stringstream.str();
}