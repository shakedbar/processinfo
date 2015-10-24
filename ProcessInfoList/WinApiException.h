#pragma once

#include <stdexcept>
#include <string.h>
#include <sstream>
#include "Windows.h"

using namespace std;

/*
*	@brief		WinAPI exception object, generating error from the GetLastError call and message.
*/
class WinApiException : public exception {
public:
	WinApiException(string errorMessage) : m_error(GetLastError()), m_errorMessage(errorMessage) {}
	const char* what();
private:
	const char* formatError(DWORD error);
	DWORD m_error;
	string m_errorMessage;
};