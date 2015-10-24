#include "AutoPtu.h"

AutoPtu::AutoPtu(PTOKEN_USER& ptu) : m_ptu(ptu)
{
	if (ptu ==0) {
		throw WinApiException("Null PTU");
	}
}

AutoPtu::AutoPtu(AutoPtu& other) : m_ptu(other.m_ptu)
{
	if (other.m_ptu == 0) {
		throw WinApiException("Null PTU");
	}
}

AutoPtu& AutoPtu::operator=(const AutoPtu& other)
{
	if (this == &other) {
		return *this;
	}

	m_ptu = other.m_ptu;

	return *this;
}

AutoPtu::~AutoPtu()
{
	try {
		if (m_ptu != NULL) {
			HeapFree(GetProcessHeap(), 0, (LPVOID)m_ptu);
		}
	}
	catch (...)
	{

	}
}
