﻿#include "general.h"

//*************************************************************
//
//  FormatMessageBox()
//
//  Purpose:    Format parameters message box.
//
//  Parameters: lpCaption    -   Dialog box title.
//              uType        -   Contents and behavior.
//              lpCaption    -   The message to be displayed.
//              ...          -   The parameters return value.
//
//  Return:     Message box select button value.
//
//*************************************************************

int WINAPI FormatMessageBox(LPCTSTR lpCaption, UINT uType, char *lpFormat, ...)
{
	char szBuffer[1024] = { 0 };

	va_list pArgList;

	va_start(pArgList, lpFormat);

	wvsprintf(szBuffer, lpFormat, pArgList);

	va_end(pArgList);

#ifdef DEBUG
	return MessageBox(NULL,szBuffer,lpCaption,uType);
#else
	return printf("%s\n",szBuffer);
#endif
	
}


//*************************************************************
//
//  DebugPrivilege()
//
//  Purpose:    Upgrade the current process management permission.
//
//*************************************************************

void DebugPrivilege()
{
	HANDLE hToken = NULL;
	BOOL bRet = OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken);
	if(bRet == TRUE) {
		TOKEN_PRIVILEGES tp;
		tp.PrivilegeCount = 1;
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);

		CloseHandle(hToken);
	} else
		MessageBox(NULL, "OpenProcessToken Error！", "Warning Messages", MB_OK | MB_ICONWARNING);
}


//*************************************************************
//
//  GetFileDirectory()
//
//  Purpose:    Find whether the folder or file under the current directory exists.
//
//  Parameters: szGetFileFullPathBuffer   	-   Directory and file name buffer, on NULL return value.
//              szFileName      			-   File name or directory name, Wildcards can be used.
//
//  Return:     TRUE if successful find.
//              FALSE if no find.
//
//*************************************************************

BOOL GetFileFullDirectory(char *szFileFullPathBuffer, const char *szFileName)
{
	BOOL bRet = FALSE;
	char szCurrentDirectory[MAX_PATH] = { 0 };
	WIN32_FIND_DATA wfdFindData;

	// Get current directory and append file name
	GetCurrentDirectory(MAX_PATH, szCurrentDirectory);
	strcat(szCurrentDirectory, "\\");
	strcat(szCurrentDirectory, szFileName);    //after adding the file name to the current directory

	// Find file 
	if(INVALID_HANDLE_VALUE != FindFirstFile(szCurrentDirectory, &wfdFindData)) { //find file in the current directory, successful return true
		bRet = TRUE;
		if(szFileFullPathBuffer != NULL) {
			strncpy(szFileFullPathBuffer, szCurrentDirectory,strlen(szCurrentDirectory) - strlen(strrchr(szCurrentDirectory,'\\')));
			strcat(szFileFullPathBuffer, "\\");
			strcat(szFileFullPathBuffer, wfdFindData.cFileName);
		}
	} 
    return bRet;
}
//*************************************************************
//
//  ReadTextFile()
//
//  Purpose:    Read text files into memory.
//
//  Parameters: szFileName   -   File name.
//              szReadBuffer -   Memory address.
//
//  Return:     Number of characters read in. 0 for error.
//
//*************************************************************

int ReadTextFile(char *szFileName, char **szReadBuffer)
{
	HANDLE hFile = NULL;
	DWORD dwFileSize = 0;
	DWORD dwRead = 0;
	hFile = CreateFile(szFileName, 		// file name
			GENERIC_READ, 		// read modle
			FILE_SHARE_READ, 	// read modle
			NULL,
			OPEN_EXISTING, 		// open 
			FILE_ATTRIBUTE_NORMAL, 0);
	if(INVALID_HANDLE_VALUE == hFile) {
		FormatMessageBox("Error Messages", MB_OK | MB_ICONERROR, "CreateFile error: ( %d )\n", GetLastError());
		return 0;
	}

	// get file size
	dwFileSize = GetFileSize(hFile, 0);
	if(INVALID_FILE_SIZE == dwFileSize) {
		FormatMessageBox("Error Messages", MB_OK | MB_ICONERROR, "GetFileSize error: (%d )\n", GetLastError());
		return 0;
	}

	// create memory address
	*szReadBuffer = (void *)malloc(dwFileSize);
	memset(*szReadBuffer, 0, sizeof(*szReadBuffer));

	if(!ReadFile(hFile, (LPVOID)*szReadBuffer, dwFileSize, &dwRead, NULL)) {
		FormatMessageBox("Error Messages", MB_OK | MB_ICONERROR, "ReadFile error: ( %d )\n",GetLastError());
		return 0;
	}
	
	CloseHandle(hFile);
	
	return dwRead;
}



//*************************************************************
//
//  WriteTextFile()
//
//  Purpose:    Write text files.
//
//  Parameters: szFileName    -   File name.
//              szWriteBuffer -   Memory address.
//              dwMoveMethod  -   File pointer address and file open method.
//
//  Return:     Number of characters write in file. 0 for error.
//
//*************************************************************

int WriteTextFile(char *szFileName, char *szWriteBuffer, DWORD dwMoveMethod)
{
	HANDLE hFile = NULL;
	DWORD dwWrite = 0;
	DWORD dwCreationDisposition = OPEN_ALWAYS;	

	// if open or create
	if(dwMoveMethod == FILE_BEGIN)
		dwCreationDisposition = CREATE_ALWAYS;
	
	hFile = CreateFile(szFileName, 
			GENERIC_READ | GENERIC_WRITE, 
			FILE_SHARE_READ | FILE_SHARE_WRITE, 	// read and write modle
			NULL,
			dwCreationDisposition, 			// open file or create new file
			FILE_ATTRIBUTE_NORMAL, 0);
	if(INVALID_HANDLE_VALUE == hFile) {
		FormatMessageBox("Error Messages", MB_OK | MB_ICONERROR, "CreateFile error: ( %d )\n", GetLastError());
		return 0;
	}

	// move file pointer
	SetFilePointer(hFile, 0, 0, dwMoveMethod);

	if(!WriteFile(hFile, (LPVOID)szWriteBuffer, strlen(szWriteBuffer), &dwWrite, NULL)) {
		FormatMessageBox("Error Messages", MB_OK | MB_ICONERROR, "WriteFile error: ( %d )\n",GetLastError());
		return 0;
	}

	CloseHandle(hFile);
	
	return dwWrite;
}


//*************************************************************
//
//  DoRunProc()
//
//  Purpose:    Runing process.
//
//  Parameters: szFileName    -   Process name.
//              szLineCommand -   Command line parameters.
//
//*************************************************************

void DoRunProc(char *szFileName, char *szLineCommand)
{
	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFO si = { 0 };

	si.cb = sizeof(STARTUPINFO);

	if(!CreateProcess(
		szFileName, 		// file name or null
		szLineCommand, 		// line command or file name and lien command
		NULL, NULL, FALSE, 
		CREATE_NO_WINDOW, 	// on show window
		NULL,
		NULL,
		&si, &pi)) {
		FormatMessageBox("Error Messages", MB_OK | MB_ICONERROR, "CreateProess Error %d\n", GetLastError());
		return ;
	}

	WaitForSingleObject( pi.hThread, INFINITE );	
	WaitForSingleObject( pi.hProcess, INFINITE );	

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}
