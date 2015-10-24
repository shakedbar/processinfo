#include "ProcessPrinter.h"

void ProcessPrinter::printProcessesInfo()
{
	PROCESSENTRY32W processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processSnapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processSnapshotHandle == INVALID_HANDLE_VALUE)
	{
		throw WinApiException("Unable to get processes");
	}

	if (Process32FirstW(processSnapshotHandle, &processInfo))
	{
		safePrintProcess(processInfo);
	}
	
	while (Process32NextW(processSnapshotHandle, &processInfo))
	{
		safePrintProcess(processInfo);
	}
}

void ProcessPrinter::safePrintProcess(PROCESSENTRY32W processInfo)
{
	try 
	{
		printProcess(processInfo);
	}
	catch (WinApiException ex)
	{
		wcout << L"Unable to get info for process " << processInfo.szExeFile << " - Error: " << ex.what() << endl;
	}
}

void ProcessPrinter::printProcess(PROCESSENTRY32W processInfo)
{
	// Get the process handle
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, 0, processInfo.th32ProcessID);
	if (!hProcess) {
		ostringstream stringstream;
		stringstream << "Unable to open process: " << processInfo.szExeFile; 
		throw WinApiException(stringstream.str());
	}

	wstringstream stringStream;
	stringStream << "Process name: " << processInfo.szExeFile << endl;
	
	// Run all the info finders to get the data of the process as a string
	for (list<shared_ptr<ProcessFinderFactory>>::const_iterator iterator = m_infoFactories.begin(), end = m_infoFactories.end();
		iterator != end;
		++iterator) {
            shared_ptr<ProcessInfoFinder> infoFinder = iterator->get()->create(hProcess);
			stringStream << infoFinder.get()->getInfo() << endl;
	}

	stringStream << endl;

	// Print the info
	wcout << stringStream.str();
}