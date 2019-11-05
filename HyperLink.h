#ifndef _HYPERLINK_H_
#define _HYPERLINK_H_

#include <Windows.h>
#include <stdio.h>

//register hyperlink class
ATOM WINAPI RegisterHyperLink(HWND hWnd);

// Create the typerlink button
HWND WINAPI CreateHyperLink(
	LPCSTR    lpWindowName,
	DWORD     dwStyle,
	int       X,
	int       Y,
	int       nWidth,
	int       nHeight,
	HWND      hWndParent,
	UINT      uID);

// Set hyperlink style for button 
LONG WINAPI SetHyperLinkStyle(HWND hwnd);

#endif // _HYPERLINK_H_