#ifndef _GENERAL_H_
#define _GENERAL_H_

#include <windows.h>
#include <stdio.h>

#define FILE_DIR(x,y) _T(x)_T(\\)_T(y)
#define _T(x) T(x)
#define T(x) #x

//*************************************************************
//
//  DebugPrivilege()
//
//  Purpose:    Upgrade the current process management permission.
//
//*************************************************************

void DebugPrivilege();


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

int WINAPI FormatMessageBox(LPCTSTR lpCaption, UINT uType, char *lpFormat, ...);



//*************************************************************
//
//  strrep()
//
//  Purpose:    Replace the first occurrence of ostr string in dest string with nstr string.
//
//  Parameters: dest   -   Destination string.
//              ostr   -   Old string.
//              nstr   -   New string.
//
//  Return:     Successful return new destination string address, no successful return ostr string address.
//
//*************************************************************

char *strrep(char *dest, char *ostr, const char *nstr);


//*************************************************************
//
//  strnrep()
//
//  Purpose:    Replace the all occurrence of ostr string in dest string with nstr string.
//
//  Parameters: dest   -   Destination string.
//              ostr   -   Old string.
//              nstr   -   New string.
//
//  Return:     Successful return new destination string address, no successful return ostr string address.
//
//*************************************************************

char *strnrep(char *dest, char *ostr, const char *nstr);


//*************************************************************
//
//  GetFileDirectory()
//
//  Purpose:    Find whether the folder or file under the current directory exists.
//
//  Parameters: szDirFileName   -   Directory and file name buffer, on NULL return value.
//              szFileName      -   File name or directory name.If the file in the subdirectory
//                                  needs to be \\ separated from the file name.
//
//  Return:     TRUE if successful find.
//              FALSE if no find.
//
//*************************************************************

BOOL GetFileDirectory(char *szDirFileName, char *szFileName);


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

int ReadTextFile(char *szFileName, char **szReadBuffer);


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

int WriteTextFile(char *szFileName, char *szWriteBuffer, DWORD dwMoveMethod);


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

void DoRunProc(char *szFileName, char *szLineCommand);

#endif // _GENERAL_H_



