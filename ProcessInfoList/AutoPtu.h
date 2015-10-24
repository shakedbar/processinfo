#pragma once

#include "Windows.h"
#include "WinApiException.h"
#include <iostream>

using namespace std;

/*
*	@brief		RAII wrapper for PTOKEN_USER
*/
class AutoPtu {
public:
	AutoPtu();
	/*
	*	@brief		Initializes the AutoPtu - saves the PTOKEN_USER.
	*
	*	@param		ptu - PTU to use.
	*
	*	@note		Heap memory for the PTU will be released by the d'tor.
	*/
	AutoPtu(PTOKEN_USER& ptu);
	/*
	*	@brief		Copy c'tor - copies the PTU.
	*
	*	@param		other - PTU to copy.
	*
	*	@note		Heap memory for the PTU will be released by the d'tor.
	*/
	AutoPtu(AutoPtu& other);
	/*
	*	@brief		Operator= - copies the PTU.
	*
	*	@param		other - PTU to copy.
	*
	*	@note		Heap memory for the PTU will be released by the d'tor.
	*/
	AutoPtu& operator=(const AutoPtu& other);
	/*
	*	@brief		Releases PTU memory from the heap.
	*/
	~AutoPtu();
private:
	PTOKEN_USER& m_ptu;
};