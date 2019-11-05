#include "service.h"

//*************************************************************
//
//  SearchSvc()
//
//  Purpose:    Retrieve whether the service is installed.
//
//  Parameters: szSvcName    -   Service name.
//
//  Return:     TRUE if installed.
//              FALSE if no installed.
//
//*************************************************************

BOOL SearchSvc(char *szSvcName)
{
	BOOL bRet = FALSE;

	SC_HANDLE schSCManager;
	char szDisplayName[256] = { 0 };
	char szKeyName[256] = { 0 };
	DWORD dwDisplayNameLength = 256;
	DWORD dwKeyNameLength = 256;

	// Get a handle to the SCM database.
	schSCManager = OpenSCManager(
		NULL,			// local computer
		NULL,			// servicesActive database 
		SC_MANAGER_ALL_ACCESS);	// full access rights

	if(schSCManager == NULL) {
		FormatMessageBox("Error Messages", MB_OK | MB_ICONERROR, "OpenSCManager failed ( %d )\n", GetLastError());
		return -1;
	}

	// Get a display name to service.
	if(!GetServiceDisplayName(
		schSCManager, 			// SCM database 
		szSvcName, 			// name of service 
		szDisplayName, 			// display name of service
		&dwDisplayNameLength)) {	// address of display name

      	 	FormatMessageBox("Error Messages", MB_OK | MB_ICONERROR, "GetServiceDisplayName failed ( %d )\n", GetLastError()); 
       		goto cleanup;
	} else bRet = TRUE;

	// Get a key name to service.
	if(!GetServiceKeyName(
		schSCManager, 			// SCM database 
		szSvcName, 			// name of service 
		szKeyName, 			// key name of service
		&dwKeyNameLength)) {		// address of key name

      	 	 FormatMessageBox("Error Messages", MB_OK | MB_ICONERROR, "GetServiceKeyName failed ( %d )\n", GetLastError()); 
       		 goto cleanup;
	}else bRet = TRUE;
		
cleanup:
	CloseServiceHandle(schSCManager);

	return bRet;
}


//*************************************************************
//
//  GetStatusSvc()
//
//  Purpose:    Get service running status.
//
//  Parameters: szSvcName    -   Service name.
//
//  Return:     1 if service running.
//              0 if service stop.
//              -1 if service error.
//
//*************************************************************

int GetStatusSvc(char *szSvcName)
{
	int iRet = 0;

	SC_HANDLE schSCManager;
	SC_HANDLE schService;
	SERVICE_STATUS ssStatus;

	// Get a handle to the SCM database.
	schSCManager = OpenSCManager(
		NULL,			// local computer
		NULL,			// servicesActive database 
		SC_MANAGER_ALL_ACCESS);	// full access rights

	if(schSCManager == NULL) {
		FormatMessageBox("Error Messages", MB_OK | MB_ICONERROR, "OpenSCManager failed ( %d )\n", GetLastError());
		return -1;
	}

	// Get a handle to the service.
	schService = OpenService(
		schSCManager,		// SCM database 
		szSvcName,		// name of service 
		SERVICE_ALL_ACCESS);	// full access 

	if (schService == NULL) { 
 		FormatMessageBox("Error Messages", MB_OK | MB_ICONERROR, "OpenService failed ( %d )\n", GetLastError());
		CloseServiceHandle(schSCManager);
		return -1;
	}

	if(!QueryServiceStatus(
		schService, 		// handle to service 
		&ssStatus)) {		// address of structure
		
		FormatMessageBox("Error Messages", MB_OK | MB_ICONERROR, "QueryServiceStatus failed ( %d )\n", GetLastError());
		goto cleanup;
	}

	if (ssStatus.dwCurrentState == SERVICE_RUNNING) {
		iRet = 1;
		goto cleanup;
	}

cleanup:	
	CloseServiceHandle(schService); 
	CloseServiceHandle(schSCManager);	
	
	return iRet;
}

//*************************************************************
//
//  DoStarSvc()
//
//  Purpose:    Start service.
//
//  Parameters: szSvcName    -   Service name.
//
//  Return:     TRUE if successful startup.
//              FALSE if no startup.
//
//*************************************************************

BOOL DoStarSvc(char *szSvcName)
{
	BOOL bRet = FALSE;

	SC_HANDLE schSCManager;
	SC_HANDLE schService;
	SERVICE_STATUS ssStatus;
	DWORD dwWaitTime;

	// Get a handle to the SCM database.
	schSCManager = OpenSCManager(
		NULL,			// local computer
		NULL,			// servicesActive database 
		SC_MANAGER_ALL_ACCESS);	// full access rights

	if(schSCManager == NULL) {
		FormatMessageBox("Error Messages", MB_OK | MB_ICONERROR, "OpenSCManager failed ( %d )\n", GetLastError());
		return FALSE;
	}

	// Get a handle to the service.
	schService = OpenService(
		schSCManager,		// SCM database 
		szSvcName,		// name of service 
		SERVICE_ALL_ACCESS);	// full access 

	if (schService == NULL) { 
 		FormatMessageBox("Error Messages", MB_OK | MB_ICONERROR, "OpenService failed ( %d )\n", GetLastError());
		CloseServiceHandle(schSCManager);
		return FALSE;
	}

	// Check the status until the service is no longer start pending. 
	if(!QueryServiceStatus(
		schService, 		// handle to service 
		&ssStatus)) {		// address of structure
		
		FormatMessageBox("Error Messages", MB_OK | MB_ICONERROR, "QueryServiceStatus failed ( %d )\n", GetLastError());
		goto cleanup;
	}

	// Check if the service is already running. It would be possible 
	// to stop the service here, but for simplicity this example just returns. 
	if (ssStatus.dwCurrentState != SERVICE_STOPPED && ssStatus.dwCurrentState != SERVICE_STOP_PENDING) {
		goto cleanup;
	}

	// Wait for the service to stop before attempting to start it.
	if (ssStatus.dwCurrentState == SERVICE_STOP_PENDING) {
		dwWaitTime = ssStatus.dwWaitHint / 10;

		if( dwWaitTime < 1000 )
			dwWaitTime = 1000;
		else if ( dwWaitTime > 10000 )
			dwWaitTime = 10000;

		Sleep( dwWaitTime );
	}

	// Attempt to start the service.
	if(!StartService(
		schService,		// handle to service 
		0, 			// number of arguments 
		NULL)) {		// no arguments 
		FormatMessageBox("Error Messages", MB_OK | MB_ICONERROR, "StartService failed ( %d )\n", GetLastError());
            	goto cleanup;
	} else	bRet = TRUE;	//Service start pending...

cleanup:	
	CloseServiceHandle(schService); 
	CloseServiceHandle(schSCManager);

	return bRet;
	
}


//*************************************************************
//
//  DoStopSvc()
//
//  Purpose:    Stop service.
//
//  Parameters: szSvcName    -   Service name.
//
//  Return:     TRUE if successful closed.
//              FALSE if no closed.
//
//*************************************************************

BOOL DoStopSvc(char *szSvcName)
{
	BOOL bRet = FALSE;

	SC_HANDLE schSCManager;
	SC_HANDLE schService;
	SERVICE_STATUS ssStatus;
	DWORD dwWaitTime;

	// Get a handle to the SCM database.
	schSCManager = OpenSCManager(
		NULL,			// local computer
		NULL,			// servicesActive database 
		SC_MANAGER_ALL_ACCESS);	// full access rights

	if(schSCManager == NULL) {
		FormatMessageBox("Error Messages", MB_OK | MB_ICONERROR, "OpenSCManager failed ( %d )\n", GetLastError());
		return FALSE;
	}

	// Get a handle to the service.
	schService = OpenService(
		schSCManager,		// SCM database 
		szSvcName,		// name of service 
		SERVICE_ALL_ACCESS);	// full access 

	if (schService == NULL) { 
 		FormatMessageBox("Error Messages", MB_OK | MB_ICONERROR, "OpenService failed ( %d )\n", GetLastError());
		CloseServiceHandle(schSCManager);
		return FALSE;
	}

	// Check the status until the service is no longer start pending. 
	if(!QueryServiceStatus(
		schService, 		// handle to service 
		&ssStatus)) {		// address of structure
		
		FormatMessageBox("Error Messages", MB_OK | MB_ICONERROR, "QueryServiceStatus failed ( %d )\n", GetLastError());
		goto cleanup;
	}

	if (ssStatus.dwCurrentState == SERVICE_STOPPED && ssStatus.dwCurrentState == SERVICE_STOP_PENDING) {
		goto cleanup;
	}

	if (ssStatus.dwCurrentState == SERVICE_START_PENDING) {
		dwWaitTime = ssStatus.dwWaitHint / 10;

		if( dwWaitTime < 1000 )
			dwWaitTime = 1000;
		else if ( dwWaitTime > 10000 )
			dwWaitTime = 10000;

		Sleep( dwWaitTime );
	}

	// Send a stop code to the service.
	if(!ControlService(
		schService, 		// handle to service 
		SERVICE_CONTROL_STOP, 	// send stop control
		&ssStatus)) {		// address of structure

		FormatMessageBox("Error Messages", MB_OK | MB_ICONERROR, "ControlService failed ( %d )\n", GetLastError() );
		goto cleanup;
	} else bRet = TRUE;

cleanup:
	CloseServiceHandle(schService); 
	CloseServiceHandle(schSCManager);

	return bRet;	
}