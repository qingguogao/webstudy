#include "HyperLink.h"

LRESULT CALLBACK HyperLinkProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//register hyperlink class
ATOM WINAPI RegisterHyperLink(HWND hWnd) 
{ 
    WNDCLASSEX wcx; 

    wcx.cbSize = sizeof(wcx);          		// *size of structure 
    wcx.style = CS_PARENTDC|CS_GLOBALCLASS;	// *redraw if size changes 
    wcx.lpfnWndProc = HyperLinkProc;   		// *points to window procedure 
    wcx.cbClsExtra = 0;                		// no extra class memory 
    wcx.cbWndExtra = sizeof(INT*);      	// *extra window memory, to save the pointer 
    wcx.hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);  // *handle to instance 
    wcx.hIcon = NULL;           		// default predefined app. icon 
    wcx.hCursor = LoadCursor(NULL,IDC_HAND);  	// *predefined arrow (IDC_HAND)
    wcx.hbrBackground = NULL;           	// default background brush 
    wcx.lpszMenuName =  NULL;			// no menu resource 
    wcx.lpszClassName = "HyperLink";		// *name of window class 
    wcx.hIconSm = NULL; 			// no small class icon 
         
    // Register the window class. 
 
    return RegisterClassEx(&wcx); 
}

// Create the main window
HWND WINAPI CreateHyperLink(
	LPCSTR    lpWindowName,	// title-bar string 
	DWORD     dwStyle,	// top-level window 
	int       X,		// horizontal position 
	int       Y,		// vertical position 
	int       nWidth,	// width 
	int       nHeight,	// height 
	HWND      hWndParent,	// parent handle
	UINT      uID)		// id
{
	RegisterHyperLink(hWndParent);

	HWND hwnd = CreateWindowEx( 
		0,			//default extended window style
		"HyperLink",		// name of window class 
		lpWindowName,		// title-bar string 
		WS_CHILD | dwStyle,	// top-level window 
		X,			// horizontal position 
		Y,			// vertical position 
		nWidth,  		// width 
		nHeight,       		// height 
		hWndParent,		// no owner window 
		(HMENU) uID,		// use class menu 
		NULL,			// no handle to application instance 
		0);			// no window-creation data 

	ShowWindow(hwnd, SW_SHOW);
	return hwnd;
}

//Set hyperlink style for child ctrl
LONG WINAPI SetHyperLinkStyle(HWND hwnd)
{
	if (!SetWindowLongPtr(hwnd, 0, 0))
		SetClassLongPtr(hwnd, GCL_CBWNDEXTRA, sizeof(INT*));

	SetWindowLongPtr(hwnd, 0, 0);

	return SetWindowLongPtr(hwnd, GWL_WNDPROC, (LONG)HyperLinkProc);
}

//Set text color for ctrl
void WINAPI SetCtrlTextColor(HWND hWnd, HDC hDC, COLORREF cf, BOOL lfUnderline)
{
	HFONT hFont;
	LOGFONT lFont;
	int nLength;
	char *szTitle;
	RECT rc;
	if (hDC == NULL)
		hDC = GetDC(hWnd);
  
	hFont = (HFONT)SendMessage(GetParent(hWnd), WM_GETFONT, 0, 0);

	memset(&lFont, 0, sizeof(lFont));
	GetObject(hFont, sizeof(lFont), &lFont);
	lFont.lfUnderline = lfUnderline;
	hFont = CreateFontIndirect(&lFont);
	SelectObject(hDC, hFont);
  
	nLength = GetWindowTextLength(hWnd);
	szTitle = malloc(nLength + 1);
	memset(szTitle, 0, sizeof(char)*(nLength + 1));
	GetWindowText(hWnd, szTitle, nLength + 1);

	//set color for back and text
	SetTextColor(hDC, cf);
	SetBkMode(hDC, TRANSPARENT);

	GetClientRect(hWnd, &rc);
	DWORD dwStyle = GetWindowLongPtr(hWnd, GWL_STYLE);

	//set text style
	if (dwStyle & DT_CENTER)
		DrawText(hDC, szTitle, nLength, &rc, DT_CENTER);
	else if (dwStyle & DT_RIGHT)
		DrawText(hDC, szTitle, nLength, &rc, DT_RIGHT);
	else
		DrawText(hDC, szTitle, nLength, &rc, DT_LEFT);
	
	free(szTitle);
	ReleaseDC(hWnd, hDC);
}

//hyperlink proc
LRESULT CALLBACK HyperLinkProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	TRACKMOUSEEVENT tms;	//track mouse event
	PAINTSTRUCT ps;
	HDC hDC;
	int nLength = 0;
	char *szMSGResul = NULL;
	BOOL bUnderline = TRUE;

	switch (uMsg) {
		case WM_PAINT:
			hDC = BeginPaint(hWnd, &ps);
			SetCtrlTextColor(hWnd, hDC, RGB(0,0,255), bUnderline);
			EndPaint(hWnd, &ps);
		break;

		case WM_ERASEBKGND: // 画背景
			hDC = (HDC)wParam;
		break;

		case WM_MOUSEMOVE:
			tms.cbSize = sizeof(tms);
			tms.hwndTrack = hWnd;
			tms.dwFlags = TME_HOVER|TME_LEAVE;
			tms.dwHoverTime = 10;
			TrackMouseEvent(&tms);
      
			if (GetCapture() != hWnd) // 是否捕获过鼠标
				break;

			RECT rc;
			POINT pt;
			GetCursorPos(&pt);  // 获取当前鼠标位置
			GetWindowRect(hWnd, &rc); // 获取控件区域

			if (!PtInRect(&rc, pt)) // 如果鼠标离开控件则释放鼠标
				ReleaseCapture();
		break;

		case WM_MOUSEHOVER:	//mouse hover
			SetCtrlTextColor(hWnd, NULL, RGB(255,0,0), bUnderline);
		break;

		case WM_MOUSELEAVE:	//mouse leave
			SetCtrlTextColor(hWnd, NULL, RGB(0,0,255), bUnderline);
		break;

		case WM_LBUTTONDOWN:
			SetCapture(hWnd); // 捕获鼠标
		break;

		case WM_LBUTTONUP:	//send message command to parent window
			if (GetCapture() != hWnd) // 如果没有捕获过鼠标说明没有在控件上进行单击
				break;
			SendMessage(GetParent(hWnd), WM_COMMAND, GetDlgCtrlID(hWnd), (LPARAM)hWnd);
		break;

		case WM_SETCURSOR:
			SetCursor(LoadCursor(NULL, IDC_HAND));
		break;

		case WM_COMMAND:
			SendMessage(GetParent(hWnd), WM_COMMAND, wParam, lParam);
		break;

		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}