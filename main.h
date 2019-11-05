#include <windows.h>
#include <commctrl.h>
#include "resource.h"
#include "service.h"
#include "initfile.h"
#include "reg.h"
#include "HyperLink.h"
#define DEBUG TRUE
#include "general.h"

#define APACHE_SVC 	apache24
#define MYSQL_SVC 	mysql

#define APACHE24_DIR		apache24
#define APACHE24_HTDOCS_DIR 	htdocs
#define PHP_DIR 		php
#define MYSQL_DIR 		mysql
#define MYSQL_DATA_DIR 		data

#define APACHE24_CONF	conf\\httpd.conf
#define APACHE24_EXE 	bin\\httpd.exe
#define PHP_INI 	php.ini-development
#define PHP_EXE 	php.exe
#define PHP_DLL7 	php7apache2_4.dll
#define PHP_DLL5 	php5apache2_4.dll
#define MYSQL_EXE 	bin\\mysqld.exe
#define MYSQL_INI	my.ini

#define REG_MYSQL_SET1 "SYSTEM\\ControlSet001\\services\\eventlog\\Application\\mysql"
#define REG_MYSQL_SET2 "SYSTEM\\ControlSet002\\services\\eventlog\\Application\\mysql"
#define REG_MYSQL_SET0 "SYSTEM\\CurrentControlSet\\services\\eventlog\\Application\\mysql"

HINSTANCE hInst;
HWND TimerHwnd = NULL; 

void InitService(HWND hwnd);
void OnStarSvc(HWND hwnd, int IDP_NAME, int IDB_NAME, char *szSvcName);
void OnStopSvc(HWND hwnd, int IDP_NAME, int IDB_NAME, char *szSvcName);
void OnResetSvc(HWND hwnd);