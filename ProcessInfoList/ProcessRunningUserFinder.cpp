#include "ProcessRunningUserFinder.h"

wstring ProcessRunningUserFinder::getInfo() 
{
	wchar_t strUser[MAX_NAME];
    wchar_t strDomain[MAX_NAME];
	
	GetUserFromProcess(strUser, strDomain);

	wstringstream stringStream;
	stringStream << L"Running User: " << strDomain << "\\" << strUser;
	return stringStream.str();
	

}

void ProcessRunningUserFinder::GetLogonFromToken(HANDLE hToken, wchar_t* strUser, wchar_t* strDomain) 
{
	DWORD dwSize = MAX_NAME;
	BOOL bSuccess = FALSE;
	DWORD dwLength = 0;
	PTOKEN_USER ptu = NULL;
   
	// Call GetTokenInformation with 0 size to get the actual PTU user token size
	if (!GetTokenInformation(hToken, TokenUser,	(LPVOID) ptu, 0, &dwLength)) 
	{
		if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) 
			throw WinApiException("Error getting token information");

		ptu = (PTOKEN_USER)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwLength);

		if (ptu == NULL) {
			throw WinApiException("Error allocating memory for the user's token");
		}
	}

	AutoPtu autoPtu(ptu);

	// Call GetTokenInformation again to get the token info
	if (!GetTokenInformation(hToken, TokenUser,	(LPVOID) ptu, dwLength, &dwLength)) 
	{
		throw WinApiException("Error getting token information");
	}

	SID_NAME_USE SidType;

	// Get the user name and domain name from the account token
	if(!LookupAccountSid(NULL , ptu->User.Sid, strUser, &dwSize, strDomain, &dwSize, &SidType))                                    
	{
		throw WinApiException("Error getting account SID details");
	}
}

void ProcessRunningUserFinder::GetUserFromProcess(wchar_t* strUser, wchar_t* strDomain)
{
	// Get the process' token. From the token extract the user info
    HANDLE hToken = NULL;

	if(!OpenProcessToken(m_processHandle, TOKEN_QUERY, &hToken ) )
    {
        throw WinApiException("Unable to open process token");
    }

	AutoHandle tokenHandle(hToken);
    GetLogonFromToken(hToken, strUser,  strDomain);
}