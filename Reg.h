#ifndef _REG_H_
#define _REG_H_

#include <windows.h>
#include "general.h"

//*************************************************************
//
//  RegDelnode()
//
//  Purpose:    Deletes a registry key and all its subkeys / values.
//
//  Parameters: hKeyRoot    -   Root key
//              lpSubKey    -   SubKey to delete
//
//  Return:     TRUE if successful.
//              FALSE if an error occurs.
//
//*************************************************************

BOOL RegDelnode (HKEY hKeyRoot, LPCTSTR lpSubKey);

#endif // _REG_H_
