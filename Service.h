#ifndef _SERVICE_H_
#define _SERVICE_H_

#include <windows.h>
#include "general.h"

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

BOOL SearchSvc(char *szSvcName);


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

int GetStatusSvc(char *szSvcName);



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

BOOL DoStarSvc(char *szSvcName);



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

BOOL DoStopSvc(char *szSvcName);

#endif // _SERVICE_H_
