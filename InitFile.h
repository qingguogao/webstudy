#ifndef _INITFILE_H_
#define _INITFILE_H_

#include <windows.h>
#include "general.h"
#include "stringx.h"

//*************************************************************
//
//  SetPHPIni()
//
//  Purpose:    Modify php.ini.
//
//  Parameters: szCurrentDirectory   -   Current directory, Note must include"\".
//              szFileName           -   File name, Can include subdirectories.
//
//  Return:     TRUN if successful.
//              FALSE if on successful.
//
//*************************************************************

BOOL SetPHPIni(char *szCurrentDirectory, char *szFileName);


//*************************************************************
//
//  SetApache24ConfFromPHP()
//
//  Purpose:    Httpd.conf needs to be modified due to PHP.
//
//  Parameters: szCurrentDirectory   -   Current directory, Note must include"\".
//              szFileName           -   File name, Can include subdirectories.
//              szPHPDirectory       -   PHP File directory.
//
//  Return:     TRUN if successful.
//              FALSE if on successful.
//
//*************************************************************

BOOL SetApache24ConfFromPHP(char *szCurrentDirectory, char *szFileName, char *szPHPDirectory);


//*************************************************************
//
//  SetApache24Conf()
//
//  Purpose:    Modify httpd.conf.
//
//  Parameters: szCurrentDirectory   -   Current directory, Note must include"\".
//              szFileName           -   File name, Can include subdirectories.
//
//  Return:     TRUN if successful.
//              FALSE if on successful.
//
//*************************************************************

BOOL SetApache24Conf(char *szCurrentDirectory, char *szFileName);


//*************************************************************
//
//  CreateMYSQLIni()
//
//  Purpose:    Create my.ini.
//
//  Parameters: szCurrentDirectory   -   Current directory, Note must include"\".
//              szFileName           -   File name, Can include subdirectories.
//
//  Return:     Successful return file size, no successful return 0.
//
//*************************************************************

DWORD CreateMYSQLIni(char *szCurrentDirectory, char *szFileName);

#endif // _INITFILE_H_



