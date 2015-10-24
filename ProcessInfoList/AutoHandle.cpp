#include "AutoHandle.h"

AutoHandle::AutoHandle(HANDLE& handle) : m_handle(handle)
{
	if (handle ==0) {
		throw WinApiException("Null Handle");
	}
}

AutoHandle::AutoHandle(AutoHandle& other) : m_handle(other.m_handle)
{
	if (other.m_handle == 0) {
		throw WinApiException("Null Handle");
	}
}

AutoHandle& AutoHandle::operator=(const AutoHandle& other)
{
	if (this == &other) {
		return *this;
	}

	m_handle = other.m_handle;

	return *this;
}

AutoHandle::~AutoHandle()
{
	try {
		if (m_handle != NULL) {
			CloseHandle(m_handle);
		}
	}
	catch (...)
	{

	}
}

HANDLE& AutoHandle::getHandle()
{
	return m_handle;
}