#include "ProcessCpuFinder.h"


ProcessCpuFinder::ProcessCpuFinder(HANDLE processHandle) : ProcessInfoFinder(processHandle)
{
	SYSTEM_INFO sysInfo;

    GetSystemInfo(&sysInfo);
    m_numProcessors = sysInfo.dwNumberOfProcessors;
}

ULONGLONG ProcessCpuFinder::subtractTimes(const FILETIME& ftA, const FILETIME& ftB)
{
	LARGE_INTEGER a, b;
    a.LowPart = ftA.dwLowDateTime;
    a.HighPart = ftA.dwHighDateTime;
	b.LowPart = ftB.dwLowDateTime;
	b.HighPart = ftB.dwHighDateTime;
	
	return a.QuadPart - b.QuadPart;
}


wstring ProcessCpuFinder::getInfo()
{
	FILETIME sysIdleTime1, sysKernelTime1, sysUserTime1;
	FILETIME sysIdleTime2, sysKernelTime2, sysUserTime2;
	FILETIME processCreationTime1, processExitTime1, processKernelTime1, processUserTime1;
	FILETIME processCreationTime2, processExitTime2, processKernelTime2, processUserTime2;

	// Get system and process times for the first time
	if (!GetSystemTimes(&sysIdleTime1, &sysKernelTime1, &sysUserTime1) ||
		!GetProcessTimes(m_processHandle, &processCreationTime1,
		 &processExitTime1, &processKernelTime1, &processUserTime1))
	{
		throw WinApiException("Unable to get times");
	}

	Sleep(50);

	// Get system and process times for the second time after waiting a bit
	if (!GetSystemTimes(&sysIdleTime2, &sysKernelTime2, &sysUserTime2) ||
		!GetProcessTimes(m_processHandle, &processCreationTime2,
		 &processExitTime2, &processKernelTime2, &processUserTime2))
	{
		throw WinApiException("Unable to get times");
	}

	/*	Calculate the CPU usage:
		Calculate the total time the process ran (user+kernal) in the sample period.
		Calculate the total time the system ran (user+kernal) in the sample period.
		Divide the 2 values.
	*/
	
	ULONGLONG sysKernelTimeDiff = subtractTimes(sysKernelTime2, sysKernelTime1);
	ULONGLONG sysUserTimeDiff = subtractTimes(sysUserTime2, sysUserTime1);

	ULONGLONG processKernelTimeDiff = subtractTimes(processKernelTime2, processKernelTime1);
	ULONGLONG processUserTimeDiff = subtractTimes(processUserTime2, processUserTime1);

	ULONGLONG nTotalSys =  sysKernelTimeDiff + sysUserTimeDiff;
	ULONGLONG nTotalProc = processKernelTimeDiff + processUserTimeDiff;
	short cpu = 0;
	if (nTotalSys > 0)
	{
		cpu = (short)(nTotalProc*100.0/nTotalSys);
	}

	wstringstream stringstream;
	stringstream << L"CPU Usage: " << cpu;

	return stringstream.str();
}
