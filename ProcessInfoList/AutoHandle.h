#pragma once

#include "Windows.h"
#include "WinApiException.h"
#include <iostream>

using namespace std;

/*
*	@brief		RAII wrapper for Handle
*/
class AutoHandle {
public:
	AutoHandle();
	/*
	*	@brief		Initializes the AutoHandle - saves the input handle.
	*
	*	@param		handle - Handle to use.
	*
	*	@note		handle will be closed by the d'tor.
	*/
	AutoHandle(HANDLE& handle);
	/*
	*	@brief		Copy c'tor - copies the handle.
	*
	*	@param		handle - Handle to use.
	*
	*	@note		handle will be closed by the d'tor.
	*/
	AutoHandle(AutoHandle& other);
	/*
	*	@brief		Operator= - copies the handle
	*
	*	@param		handle - Handle to use.
	*
	*	@note		handle will be closed by the d'tor.
	*/
	AutoHandle& operator=(const AutoHandle& other);
	/*
	*	@brief		Closes the handle.
	*/
	~AutoHandle();
	/*
	*	@brief		Getter for the Handle
	*
	*	@return		Handle.
	*/
	HANDLE& getHandle();
private:
	HANDLE& m_handle;
};