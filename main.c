#include "main.h"

BOOL CALLBACK TimerDlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	TimerHwnd = hwndDlg; 
	HFONT hFont = CreateFont(-11, 0, 0, 0, 0, FALSE, FALSE, FALSE, 1, 0, 0, 0, 0, ("Ms Shell Dlg"));
	HWND hStatic;
	char szExplainBuff[160] = { 0 };
	LoadString(hInst,IDS_RUNING, szExplainBuff, sizeof(szExplainBuff)/sizeof(char));

	switch(uMsg) {
		case WM_INITDIALOG:
			hStatic = CreateWindow(TEXT("Static"),szExplainBuff,WS_CHILDWINDOW  |WS_VISIBLE | SS_LEFT,
				11, 34, 269, 15,
				hwndDlg,NULL,hInst,NULL);
			SendMessage(hStatic,WM_SETFONT,(WPARAM)hFont,FALSE);
			SetTimer(hwndDlg, 1, 3000, NULL);
			return TRUE;

		case WM_TIMER:
			DeleteObject(hFont);//delete font handle
			EndDialog(hwndDlg, 0);
			return TRUE;

		case WM_CLOSE:
			DeleteObject(hFont);//delete font handle
			EndDialog(hwndDlg, 0);
			return TRUE;
	}
    return FALSE;
}

BOOL CALLBACK HelpDlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hStatic[4];
	static HFONT hFont;//define font handle
	HFONT hFontDlg = CreateFont(-11, 0, 0, 0, 0, FALSE, FALSE, FALSE, 1, 0, 0, 0, 0, ("Ms Shell Dlg"));

	char szExplainBuff[4][512] = { 0 };

	for(int i = 0; i < 4; i++) 
		LoadString(hInst,IDS_HELP_1 + i, szExplainBuff[i], sizeof(szExplainBuff)/sizeof(char));

	switch(uMsg) {
		case WM_INITDIALOG:
			hFont = CreateFont(
					27,			//height
					0,			//average width or zero
					0,			//angle the escapement vector and the x-axis of the device
					0,			//angle character's base line and the x-axis of the device.
					900,			//weight of the font in the range 0 through 1000.
					FALSE,			//Specifies an italic font if set to TRUE.
					FALSE,			//Specifies an underlined font if set to TRUE.
					0,			//A strikeout font if set to TRUE.
					DEFAULT_CHARSET,	//character set
					OUT_DEFAULT_PRECIS,	//output precision
					CLIP_DEFAULT_PRECIS,	//clipping precision
					ANTIALIASED_QUALITY,	//output quality
					DEFAULT_PITCH|FF_SCRIPT,//pitch and family of the font
					"微软雅黑");		//typeface name of the font
			SendMessage(GetDlgItem(hwndDlg,IDT_WEB),WM_SETFONT,(WPARAM)hFont,TRUE);//Send set font message
			SendMessage(GetDlgItem(hwndDlg,IDT_STUDY),WM_SETFONT,(WPARAM)hFont,TRUE);
			SendMessage(GetDlgItem(hwndDlg,IDP_HEAD), STM_SETICON, (WPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDI_HEAD)), 0);

			for(int i = 0; i < 4; i++) {
				hStatic[i] = CreateWindow(TEXT("Static"),szExplainBuff[i],WS_CHILDWINDOW  |WS_VISIBLE | SS_LEFT,
					25, 65 + i * 60, 325, 55,hwndDlg,NULL,hInst,NULL);
				SendMessage(hStatic[i],WM_SETFONT,(WPARAM)hFontDlg,FALSE);
			}

			CreateHyperLink("Apache24",DS_CENTER, 120, 312, 60, 20, hwndDlg, IDL_APACHE24);
			CreateHyperLink("PHP",DS_CENTER, 215, 312, 60, 20, hwndDlg, IDL_PHP);
			CreateHyperLink("MySQL",DS_CENTER, 280, 312, 60, 20, hwndDlg, IDL_MYSQL);
			return TRUE;

		case WM_CTLCOLORSTATIC:
			if((HWND)lParam == GetDlgItem(hwndDlg,IDT_WEB)) {
				SetTextColor((HDC)wParam, RGB(0,0,255));
			}
			SetBkMode((HDC)wParam,TRANSPARENT);
			return (INT_PTR)GetSysColorBrush(COLOR_BTNFACE);
		case WM_CLOSE:
			DeleteObject(hFont);//delete font handle
			DeleteObject(hFontDlg);//delete font handle
			EndDialog(hwndDlg, 0);
			return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam)){
				case ID_OK:
					EndDialog(hwndDlg, 0);
				return TRUE;
				case IDL_APACHE24:
					ShellExecute(NULL, "OPEN", "https://www.apachelounge.com/download/", NULL, NULL, SW_SHOW);
				return TRUE;
				case IDL_PHP:
					ShellExecute(NULL, "OPEN", "https://www.php.net/downloads.php", NULL, NULL, SW_SHOW);
				return TRUE;
				case IDL_MYSQL:
					ShellExecute(NULL, "OPEN", "https://dev.mysql.com/downloads/mysql/", NULL, NULL, SW_SHOW);
				return TRUE;
			}
			return TRUE;
	}
    return FALSE;
}

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HFONT hFont;//define font handle
	switch(uMsg) {
		case WM_INITDIALOG:
			SetClassLong(hwndDlg, GCL_HICON, (LONG)LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON)));
			
			hFont = CreateFont(
					27,			//height
					0,			//average width or zero
					0,			//angle the escapement vector and the x-axis of the device
					0,			//angle character's base line and the x-axis of the device.
					900,			//weight of the font in the range 0 through 1000.
					FALSE,			//Specifies an italic font if set to TRUE.
					FALSE,			//Specifies an underlined font if set to TRUE.
					0,			//A strikeout font if set to TRUE.
					DEFAULT_CHARSET,	//character set
					OUT_DEFAULT_PRECIS,	//output precision
					CLIP_DEFAULT_PRECIS,	//clipping precision
					ANTIALIASED_QUALITY,	//output quality
					DEFAULT_PITCH|FF_SCRIPT,//pitch and family of the font
					"微软雅黑");		//typeface name of the font
			SendMessage(GetDlgItem(hwndDlg,IDT_WEB),WM_SETFONT,(WPARAM)hFont,TRUE);//Send set font message
			SendMessage(GetDlgItem(hwndDlg,IDT_STUDY),WM_SETFONT,(WPARAM)hFont,TRUE);
			SendMessage(GetDlgItem(hwndDlg,IDP_HEAD), STM_SETICON, (WPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDI_HEAD)), 0);

			DebugPrivilege();
			InitService(hwndDlg);

			return TRUE;

		case WM_CTLCOLORSTATIC:
			if((HWND)lParam == GetDlgItem(hwndDlg,IDT_WEB)) {
				SetTextColor((HDC)wParam, RGB(0,0,255));
			}
			SetBkMode((HDC)wParam,TRANSPARENT);
			return (INT_PTR)GetSysColorBrush(COLOR_BTNFACE);
    
		case WM_CLOSE:
			DeleteObject(hFont);//delete font handle
			EndDialog(hwndDlg, 0);
			return TRUE;

		case WM_COMMAND:
			switch(LOWORD(wParam)){
				case IDB_APACHE_RUN:
					OnStarSvc(hwndDlg, IDP_APACHE, IDB_APACHE_RUN, _T(APACHE_SVC));
				return TRUE;
				case IDB_APACHE_STOP:
					OnStopSvc(hwndDlg, IDP_APACHE, IDB_APACHE_STOP, _T(APACHE_SVC));
				return TRUE;
				case IDB_APACHE_RESTART:
					if(GetStatusSvc(_T(APACHE_SVC)) == 1) {
						OnStopSvc(hwndDlg,IDP_APACHE, IDB_APACHE_STOP, _T(APACHE_SVC));
						OnStarSvc(hwndDlg,IDP_APACHE, IDB_APACHE_RUN, _T(APACHE_SVC));
					} else {
						OnStarSvc(hwndDlg,IDP_APACHE, IDB_APACHE_RUN, _T(APACHE_SVC));
					}
				return TRUE;

				case IDB_MYSQL_RUN:
					OnStarSvc(hwndDlg, IDP_MYSQL, IDB_MYSQL_RUN, _T(MYSQL_SVC));
				return TRUE;
				case IDB_MYSQL_STOP:
					OnStopSvc(hwndDlg, IDP_MYSQL, IDB_MYSQL_STOP, _T(MYSQL_SVC));
				return TRUE;
				case IDB_MYSQL_RESTART:
					if(GetStatusSvc(_T(MYSQL_SVC)) == 1) {
						OnStopSvc(hwndDlg, IDP_MYSQL, IDB_MYSQL_STOP, _T(MYSQL_SVC));
						OnStarSvc(hwndDlg, IDP_MYSQL, IDB_MYSQL_RUN, _T(MYSQL_SVC));
					} else {
						OnStarSvc(hwndDlg, IDP_MYSQL, IDB_MYSQL_RUN, _T(MYSQL_SVC));
					}
				return TRUE;

				return TRUE;
				case IDB_RESET:
					OnResetSvc(hwndDlg);
				return TRUE;
				case IDB_HELP:
					CreateDialog(NULL, MAKEINTRESOURCE(IDD_DIALOGHELP), NULL, (DLGPROC)HelpDlgMain);
				return TRUE;
			}
			return TRUE;
	}
    return FALSE;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;

    //prevent repeat runing
    HANDLE hMutex = CreateMutex(NULL, FALSE, "MyMutex");
    DWORD error = GetLastError();
    if(error == ERROR_ALREADY_EXISTS) {
	MessageBox(NULL, "程序已在运行!", "Warning Messages", MB_OK | MB_ICONWARNING);
	CloseHandle(hMutex);
	return 1;
    }
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG), NULL, (DLGPROC)DlgMain);
}

//set icon
//parameters：hwnd - window handle; state - 0 red picture means stop, >0 green picture means runing, 0< gray picture means not available
void SetStateImage(HWND hwnd, int state)
{
	if(state == 0)
		SendMessage(hwnd, STM_SETICON, (WPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_STOP)), 0);
	else if(state > 0)
		SendMessage(hwnd, STM_SETICON, (WPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_RUN)), 0);
	else if(state < 0)
		SendMessage(hwnd, STM_SETICON, (WPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_NA)), 0);
}

//modify httpd.conf and php.ini
//return: TRUE if successful, FALSE if not successful
BOOL Apache24Init(HWND hwnd)
{
	char szExplainBuff[5][512] = { 0 };

	for(int i = 0; i < 5; i++) 
		LoadString(hInst,IDS_A24INIT_1 + i, szExplainBuff[i], sizeof(szExplainBuff)/sizeof(char));

	char szCurrentDirectory[MAX_PATH] = { 0 };

	GetCurrentDirectory(MAX_PATH, szCurrentDirectory);//Get current directory 
	strcat(szCurrentDirectory,"\\");

	//find httpd.exe file
	if(!GetFileFullDirectory(NULL, FILE_DIR(APACHE24_DIR,APACHE24_EXE))) {
		MessageBox(NULL, szExplainBuff[0], "Warning Messages", MB_OK | MB_ICONWARNING);
		return FALSE;
	}

	if(!SetApache24Conf(szCurrentDirectory, FILE_DIR(APACHE24_DIR,APACHE24_CONF))) {
		MessageBox(NULL, szExplainBuff[1],"Warning Messages", MB_OK | MB_ICONERROR);
		return FALSE;	
	}

	//find php.exe and phpXapache2_4.dll
	if(!(GetFileFullDirectory(NULL, FILE_DIR(PHP_DIR,PHP_EXE)) && GetFileFullDirectory(NULL, FILE_DIR(PHP_DIR,PHP_DLL)))) {
		MessageBox(NULL, szExplainBuff[2],"Warning Messages", MB_OK | MB_ICONWARNING);
		goto ret;
	} 

	if(!SetApache24ConfFromPHP(szCurrentDirectory, FILE_DIR(APACHE24_DIR,APACHE24_CONF), _T(PHP_DIR))){
		MessageBox(NULL, szExplainBuff[3],"Error Messages", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	if(!SetPHPIni(szCurrentDirectory, FILE_DIR(PHP_DIR,PHP_INI))){
		MessageBox(NULL, szExplainBuff[4],"Error Messages", MB_OK | MB_ICONERROR);
		return FALSE;
	}

ret:
	CreateDirectory(strcat(szCurrentDirectory, _T(APACHE24_HTDOCS_DIR)), NULL);	//create web file directory
	
	return TRUE;
	
}

//modify my.ini file
//return: TRUE if successful, FALSE if not successful
BOOL MySQLInit(HWND hwnd)
{
	char szExplainBuff[512] = { 0 };
	LoadString(hInst,IDS_MYSQLINIT, szExplainBuff, sizeof(szExplainBuff)/sizeof(char));

	char szCurrentDirectory[MAX_PATH] = { 0 };

	//find mysqld.exe file
	if(!GetFileFullDirectory(NULL, FILE_DIR(MYSQL_DIR,MYSQL_EXE))) {
		MessageBox(NULL, szExplainBuff, "Warning Messages", MB_OK | MB_ICONWARNING);
		return FALSE;
	}

	GetCurrentDirectory(MAX_PATH, szCurrentDirectory);
	strcat(szCurrentDirectory,"\\");

	CreateMYSQLIni(szCurrentDirectory, FILE_DIR(MYSQL_DIR,MYSQL_INI));
	
	return TRUE;
}

//Initialization service
//parameters：hwnd - window handle
void InitService(HWND hwnd)
{
	char szRunName[MAX_PATH] = { 0 };

	//find Apache24 server
	if(!SearchSvc(_T(APACHE_SVC))) {
		
		if(!Apache24Init(hwnd)) {
			SetStateImage(GetDlgItem(hwnd,IDP_APACHE), -1);		//set run state icoe is gray
			for(int i = 0; i < 3; i++)	
			EnableWindow(GetDlgItem(hwnd,IDB_APACHE_RUN + i),FALSE);	//set button not available
		} else {
			CreateDialog(NULL, MAKEINTRESOURCE(IDD_TIMEDIALOG), NULL, (DLGPROC)TimerDlgMain);
			memset(szRunName, 0, sizeof(szRunName));
			GetFileFullDirectory(szRunName, FILE_DIR(APACHE24_DIR,APACHE24_EXE));
			DoRunProc(szRunName, " -k install -n \"apache24\"");

			if(SearchSvc(_T(APACHE_SVC))) {
				OnStarSvc(hwnd, IDP_APACHE, IDB_APACHE_RUN, _T(APACHE_SVC));
				EnableWindow(GetDlgItem(hwnd, IDB_APACHE_RESTART),TRUE);
			} else {
				SetStateImage(GetDlgItem(hwnd,IDP_APACHE), -1);		//set run state icoe is gray
				for(int i = 0; i < 3; i++)	
					EnableWindow(GetDlgItem(hwnd,IDB_APACHE_RUN + i),FALSE);	//set button not available
			}
			EndDialog(TimerHwnd, 0);
		}
	} else {
		if(GetStatusSvc(_T(APACHE_SVC)) == 1) {
			SetStateImage(GetDlgItem(hwnd,IDP_APACHE), 1);
			EnableWindow(GetDlgItem(hwnd,IDB_APACHE_RUN),FALSE);
			EnableWindow(GetDlgItem(hwnd,IDB_APACHE_RUN+1),TRUE);
		} else {
			SetStateImage(GetDlgItem(hwnd,IDP_APACHE), 0);
			EnableWindow(GetDlgItem(hwnd,IDB_APACHE_STOP),FALSE);
			EnableWindow(GetDlgItem(hwnd,IDB_APACHE_STOP-1),TRUE);		
		}
	} 

	//find MySql server
	if(!SearchSvc(_T(MYSQL_SVC))) {
		
		if(!MySQLInit(hwnd)) {
			SetStateImage(GetDlgItem(hwnd,IDP_MYSQL), -1);	//set run state icoe is gray
			for(int i = 0; i < 3; i++)	
			EnableWindow(GetDlgItem(hwnd,IDB_MYSQL_RUN + i),FALSE);	//set button not available
		} else {
			CreateDialog(NULL, MAKEINTRESOURCE(IDD_TIMEDIALOG), NULL, (DLGPROC)TimerDlgMain);
			memset(szRunName, 0, sizeof(szRunName));
			GetFileFullDirectory(szRunName, FILE_DIR(MYSQL_DIR,MYSQL_EXE));
			DoRunProc(szRunName, " --initialize-insecure --user=mysql");
			Sleep(1000);
			strcat(szRunName, " --install");
			DoRunProc(NULL, szRunName);	//MySQL service must be installed from the command line
			if(SearchSvc(_T(MYSQL_SVC))) {
				OnStarSvc(hwnd, IDP_MYSQL, IDB_MYSQL_RUN, _T(MYSQL_SVC));
				EnableWindow(GetDlgItem(hwnd, IDB_MYSQL_RESTART),TRUE);
			} else {
				SetStateImage(GetDlgItem(hwnd,IDP_MYSQL), -1);	//set run state icoe is gray
				for(int i = 0; i < 3; i++)	
				EnableWindow(GetDlgItem(hwnd,IDB_MYSQL_RUN + i),FALSE);	//set button not available
			}
			EndDialog(TimerHwnd, 0);
		}
	} else {
		if(GetStatusSvc(_T(MYSQL_SVC)) == 1) {
			SetStateImage(GetDlgItem(hwnd,IDP_MYSQL), 1);
			EnableWindow(GetDlgItem(hwnd,IDB_MYSQL_RUN),FALSE);
			EnableWindow(GetDlgItem(hwnd,IDB_MYSQL_RUN+1),TRUE);
		} else {
			SetStateImage(GetDlgItem(hwnd,IDP_MYSQL), 0);
			EnableWindow(GetDlgItem(hwnd,IDB_MYSQL_STOP),FALSE);
			EnableWindow(GetDlgItem(hwnd,IDB_MYSQL_STOP-1),TRUE);	
		}	
	}
}


//start service
//parameters：hwnd - window handle；IDP_NAME - picture or icoe ID；IDB_NAME - button ID；szSvcName - server name
void OnStarSvc(HWND hwnd, int IDP_NAME, int IDB_NAME, char *szSvcName)
{
	char szExplainBuff[512] = { 0 };
	LoadString(hInst,IDS_STARSVC, szExplainBuff, sizeof(szExplainBuff)/sizeof(char));

	if(DoStarSvc(szSvcName)) {
		SetStateImage(GetDlgItem(hwnd,IDP_NAME), 1);
		EnableWindow(GetDlgItem(hwnd,IDB_NAME),FALSE);	//设置服务按钮不可用
		EnableWindow(GetDlgItem(hwnd,IDB_NAME+1),TRUE);
	} else
		MessageBox(NULL, szExplainBuff,"Warning Messages", MB_OK | MB_ICONWARNING);	
}

//stop service
//parameters：hwnd - window handle；IDP_NAME - picture or icoe ID；IDB_NAME - button ID；szSvcName - server name
void OnStopSvc(HWND hwnd, int IDP_NAME, int IDB_NAME, char *szSvcName)
{
	char szExplainBuff[512] = { 0 };
	LoadString(hInst,IDS_STOPSVC, szExplainBuff, sizeof(szExplainBuff)/sizeof(char));

	if(DoStopSvc(szSvcName)) {
		SetStateImage(GetDlgItem(hwnd,IDP_NAME), 0);
		EnableWindow(GetDlgItem(hwnd,IDB_NAME),FALSE);	//设置服务按钮不可用
		EnableWindow(GetDlgItem(hwnd,IDB_NAME-1),TRUE);
	} else
		MessageBox(NULL, szExplainBuff,"Warning Messages", MB_OK | MB_ICONWARNING);	
}

//stop service and deltree data
void OnResetSvc(HWND hwnd)
{
	char szExplainBuff[2][512] = { 0 };

	for(int i = 0; i < 2; i++) 
		LoadString(hInst,IDS_RESETSVC_1 + i, szExplainBuff[i], sizeof(szExplainBuff)/sizeof(char));

	char szApache24Name[MAX_PATH] = { 0 };
	char szMySQLName[MAX_PATH] = { 0 };
	char szMySQLData[MAX_PATH] = { 0 };
	char szMySQLDataBak[MAX_PATH] = { 0 };

	//backup mysql data
	GetCurrentDirectory(MAX_PATH, szMySQLData);
	strcat(szMySQLData, "\\");
	strcat(szMySQLData, _T(MYSQL_DATA_DIR));
	strcpy(szMySQLDataBak,szMySQLData);
	strcat(szMySQLDataBak, "_bak");

	if(!(GetFileFullDirectory(szApache24Name, FILE_DIR(APACHE24_DIR,APACHE24_EXE)) && GetFileFullDirectory(szMySQLName, FILE_DIR(MYSQL_DIR,MYSQL_EXE)))) {
		MessageBox(hwnd, szExplainBuff[0], "Warning Messages", MB_OK | MB_ICONWARNING);
		return ;
	}

	if( IDNO == MessageBox(hwnd, szExplainBuff[1],"Warning Messages", MB_YESNO | MB_ICONWARNING))
		return ;

	if(SearchSvc(_T(APACHE_SVC)) ) {
		if(GetStatusSvc(_T(APACHE_SVC)))
			DoStopSvc(_T(APACHE_SVC));
		DoRunProc(szApache24Name, " -k uninstall -n \"apache24\"");
	}

	if(SearchSvc(_T(MYSQL_SVC))) {
		if(GetStatusSvc(_T(MYSQL_SVC))){
			DoStopSvc(_T(MYSQL_SVC));
			Sleep(3000);
		}
		DoRunProc(szMySQLName, " --remove mysql");
		RegDelnode(HKEY_LOCAL_MACHINE, REG_MYSQL_SET0);
		RegDelnode(HKEY_LOCAL_MACHINE, REG_MYSQL_SET1);
		RegDelnode(HKEY_LOCAL_MACHINE, REG_MYSQL_SET2);
		MoveFileEx(szMySQLData, szMySQLDataBak, MOVEFILE_WRITE_THROUGH);
	}
	
	EndDialog(hwnd, 0);
}


