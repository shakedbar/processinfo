#pragma once

#include "ProcessInfoFinder.h"
#include "AutoPtu.h"
#include <iostream>

#define MAX_NAME 256

using namespace std;

/*
*	@brief		Gets the running user info for processes.
*/
class ProcessRunningUserFinder : public ProcessInfoFinder
{
public:
	/*
	*	@brief		Initializes the ProcessInfoFinder - saves the input handle.
	*
	*	@param		handle - Process handle to use.
	*/
	ProcessRunningUserFinder(HANDLE processHandle) : ProcessInfoFinder(processHandle) {}
	/*
	*	@brief		Gets running user info for the instance's process.
	*
	*	@return		wstring representation of the info.
	*/
	wstring getInfo();
private:
	/*
	*	@brief		Gets the running user and domain for the instance's process.
	*
	*	@param		strUser - output running user.
	*	@param		strUser - output domain.
	*/
	void GetUserFromProcess(wchar_t* strUser, wchar_t* strdomain);
	/*
	*	@brief		Extracts the running user and domain from the token.
	*
	*	@param		hToken - handle to the instance's token.
	*	@param		strUser - output running user.
	*	@param		strUser - output domain.
	*/
	void GetLogonFromToken(HANDLE hToken, wchar_t* strUser, wchar_t* strDomain);
};