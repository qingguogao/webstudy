#include "initfile.h"

// modify php.ini
BOOL SetPHPIni(char *szCurrentDirectory, char *szFileName)
{
	BOOL bRet = TRUE;

	char szOpenFileName[MAX_PATH] = { 0 };
	char szWriteFileName[MAX_PATH] = { 0 };

	if(!GetFileFullDirectory(szOpenFileName, szFileName))
		return FALSE;		

	char *szWirteFileDirectory = strnrep(szCurrentDirectory, "\\", "/");

	strcpy(szWriteFileName,szCurrentDirectory);
	strcat(szWriteFileName,"php\\php.ini");

	char *szFileBuffer = NULL;
	char *szTempFileBuffer = NULL;
	DWORD dsize = ReadTextFile(szOpenFileName, &szFileBuffer);
		
	char szBuffer[MAX_PATH] = { 0 };
	sprintf(szBuffer, "extension_dir = \"%sphp/ext\"", szWirteFileDirectory); 
	
	szTempFileBuffer = strrep(szFileBuffer, ";extension_dir = \"ext\"", szBuffer);
	if(strcmp(szTempFileBuffer, ";extension_dir = \"ext\""))
		szFileBuffer = szTempFileBuffer;
	else {
		szFileBuffer = strrep(szFileBuffer, "; extension_dir = \"ext\"", szBuffer);
		if(0 == strcmp(szFileBuffer, "; extension_dir = \"ext\"")) {
			bRet = FALSE;
			goto freememory;
		}
	}

	szTempFileBuffer = strrep(szFileBuffer, ";extension=mysqli", "extension=mysqli");
	if(strcmp(szTempFileBuffer, ";extension=mysqli"))
		szFileBuffer = szTempFileBuffer;
	else {
		szFileBuffer = strrep(szFileBuffer, ";extension=php_mysqli.dll", "extension=php_mysqli.dll");

		if(0 == strcmp(szFileBuffer, ";extension=php_mysqli.dll")){
			bRet = FALSE;
			goto freememory;
		}
	}

	szTempFileBuffer = strrep(szFileBuffer, ";extension=pdo_mysql", "extension=pdo_mysql");
	if(strcmp(szTempFileBuffer, ";extension=pdo_mysql"))
		szFileBuffer = szTempFileBuffer;
	else {
		szFileBuffer = strrep(szFileBuffer, ";extension=php_pdo_mysql.dll", "extension=php_pdo_mysql.dll");
		if(0 == strcmp(szFileBuffer, ";extension=php_pdo_mysql.dll")){
			bRet = FALSE;
			goto freememory;
		}
	}

	WriteTextFile(szWriteFileName, szFileBuffer, FILE_BEGIN);

freememory:

	free(szWirteFileDirectory);
	free(szTempFileBuffer);
	free(szFileBuffer);

	return bRet;
}


//httpd.conf needs to be modified due to PHP
BOOL SetApache24ConfFromPHP(char *szCurrentDirectory, char *szFileName, char *szPHPDirectory)
{
	char szWriteFileName[MAX_PATH] = { 0 };
	char szPHPDLL8[MAX_PATH] = { 0 };
	char szPHPDLL7[MAX_PATH] = { 0 };
	char szPHPDLL5[MAX_PATH] = { 0 };

	if(!GetFileFullDirectory(szWriteFileName, szFileName))
		return FALSE;	

	char *szWirteFileDirectory = strnrep(szCurrentDirectory, "\\", "/");

	strcpy(szPHPDLL8,"\\");
	strcpy(szPHPDLL8,szPHPDirectory);
	strcat(szPHPDLL8,"\\php8apache2_4.dll");

	strcpy(szPHPDLL7,"\\");
	strcpy(szPHPDLL7,szPHPDirectory);
	strcat(szPHPDLL7,"\\php7apache2_4.dll");

	strcpy(szPHPDLL5,"\\");
	strcpy(szPHPDLL5,szPHPDirectory);
	strcat(szPHPDLL5,"\\php5apache2_4.dll");

	char *szFileBufferToPhp = malloc(MAX_PATH * 5);
	memset(szFileBufferToPhp, 0, sizeof(szFileBufferToPhp));

	if(GetFileFullDirectory(NULL, szPHPDLL8)) {
		sprintf(szFileBufferToPhp, "# php support\r\n"
			"LoadFile \"%sphp/php8ts.dll\"\r\n"
			"LoadModule php_module \"%sphp/php8apache2_4.dll\"\r\n"
			"AddType application/x-httpd-php .php\r\n"
			"PHPIniDir \"%sphp\"\r\n", 
			szWirteFileDirectory,szWirteFileDirectory,szWirteFileDirectory); 
	}else if(GetFileFullDirectory(NULL, szPHPDLL7)) {
		sprintf(szFileBufferToPhp, "# php support\r\n"
			"LoadFile \"%sphp/php7ts.dll\"\r\n"
			"LoadModule php7_module \"%sphp/php7apache2_4.dll\"\r\n"
			"AddType application/x-httpd-php .php\r\n"
			"PHPIniDir \"%sphp\"\r\n", 
			szWirteFileDirectory,szWirteFileDirectory,szWirteFileDirectory); 
	} else if(GetFileFullDirectory(NULL, szPHPDLL5)) {
		sprintf(szFileBufferToPhp, "# php support\r\n"
			"LoadFile \"%sphp/php5ts.dll\"\r\n"
			"LoadModule php5_module \"%sphp/php5apache2_4.dll\"\r\n"
			"AddType application/x-httpd-php .php\r\n"
			"PHPIniDir \"%sphp\"\r\n", 
			szWirteFileDirectory,szWirteFileDirectory,szWirteFileDirectory); 
	}
	
	WriteTextFile(szWriteFileName, szFileBufferToPhp, FILE_END);

	free(szWirteFileDirectory);
	free(szFileBufferToPhp);

	return TRUE;
}

// modify httpd.conf
BOOL SetApache24Conf(char *szCurrentDirectory, char *szFileName)
{
	BOOL bRet = TRUE;

	char szOpenFileName[MAX_PATH] = { 0 };
	char szWriteFileName[MAX_PATH] = { 0 };
	char szTempFileName[MAX_PATH] = { 0 };
	strcpy(szTempFileName,szFileName);
	strcat(szTempFileName,"_bak");

	if(!GetFileFullDirectory(szOpenFileName, szTempFileName)) {
		if(!GetFileFullDirectory(szWriteFileName, szFileName))
			return FALSE;
		strcpy(szOpenFileName,szWriteFileName);
		strcat(szOpenFileName,"_bak");
		CopyFile(szWriteFileName, szOpenFileName,TRUE);	

	} else GetFileFullDirectory(szWriteFileName, szFileName);

	char *szWirteFileDirectory = strnrep(szCurrentDirectory, "\\", "/");

	//Apache24 .conf
	char *szFileBuffer = NULL;

	ReadTextFile(szOpenFileName, &szFileBuffer);

	char szBuffer[MAX_PATH] = { 0 };
	sprintf(szBuffer, "Define SRVROOT \"%sApache24\"", szWirteFileDirectory); 
	szFileBuffer = strrepex(szFileBuffer, "Define SRVROOT", "\n", szBuffer);
	if(!strcmp(szFileBuffer,"Define SRVROOT")) {
		bRet = FALSE;
		goto freememory;
	}

	memset(szBuffer, 0, sizeof(szBuffer));
	sprintf(szBuffer, "\"%shtdocs\"", szWirteFileDirectory); 
	szFileBuffer = strnrep(szFileBuffer, "\"${SRVROOT}/htdocs\"", szBuffer);
	if(!strcmp(szFileBuffer,"\"${SRVROOT}/htdocs\"")) {
		bRet = FALSE;
		goto freememory;
	}

	szFileBuffer = strrep(szFileBuffer, "DirectoryIndex index.html", "DirectoryIndex index.html index.php");
	if(!strcmp(szFileBuffer,"DirectoryIndex index.html")) {
		bRet = FALSE;
		goto freememory;
	}

	WriteTextFile(szWriteFileName, szFileBuffer, FILE_BEGIN);

freememory:
	free(szWirteFileDirectory);
	free(szFileBuffer);

	return bRet;
}

// create my.ini
DWORD CreateMYSQLIni(char *szCurrentDirectory, char *szFileName)
{
	DWORD dRet = 0;

	char szNewFileName[MAX_PATH] = { 0 };

	char *szWirteFileDirectory = strnrep(szCurrentDirectory, "\\", "/");
	
	strcpy(szNewFileName, szCurrentDirectory);
	strcat(szNewFileName, szFileName);

	char *szFileBufferToPhp = malloc(MAX_PATH * 5);
	memset(szFileBufferToPhp, 0, sizeof(szFileBufferToPhp));
	sprintf(szFileBufferToPhp, 
			"[mysqld]\r\n\r\n"
			"port = 3306\r\n"
			"basedir = %smysql\r\n"
			"datadir = %sdata\r\n"
			"max_connections = 200\r\n"
			"max_connect_errors = 10\r\n"
			"character-set-server = utf8\r\n"
			"default-storage-engine = INNODB\r\n"
			"default_authentication_plugin = mysql_native_password\r\n\r\n"
			"[mysql]\r\n\r\n"
			"default-character-set = utf8\r\n\r\n"
			"[client]\r\n\r\n"
			"port = 3306\r\n"
			"default-character-set = utf8\r\n", 
			szWirteFileDirectory,szWirteFileDirectory); 
	
	dRet = WriteTextFile(szNewFileName, szFileBufferToPhp, FILE_BEGIN);

	free(szWirteFileDirectory);
	free(szFileBufferToPhp);
	
	return dRet;
}
