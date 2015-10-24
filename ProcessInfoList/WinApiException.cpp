#include "WinApiException.h"

const char* WinApiException::formatError(DWORD error)
{
	char* buffer = new char[256];
	if (!FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, 0, buffer, 255, NULL))
	{
		return "Error formatting error message";
	}

	return buffer;
}

const char* WinApiException::what()
{
	return formatError(m_error);
}