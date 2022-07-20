#include "stringx.h"
/*
  strrep()
  Purpose:    Replace the first occurrence of ostr string in dest string with nstr string.
  Parameters: dest   -   Destination string.
              ostr   -   Old string.
              nstr   -   New string.
  Return:     Successful return new destination string address, no successful return ostr string address.
*/
char *strrep(char *dest, char *ostr, const char *nstr)
{
	if(!strstr(dest, ostr))
		return ostr;

	int lenght = strlen(dest) + strlen(nstr) - strlen(ostr);
	char *retstr = (char*)malloc((lenght + 1)*sizeof(char));

	int beflen = strstr(dest, ostr) - dest;
	char *midstr = strstr(dest, ostr);

	int aftlen = strlen(midstr) - strlen(ostr);

	memmove(retstr, dest, beflen);
	memmove(retstr + beflen, nstr, strlen(nstr));
	memmove(retstr + beflen + strlen(nstr), midstr + strlen(ostr), aftlen + 1);

	free(dest);
	return retstr;
}

/*
  strnrep()
  Purpose:    Replace the all occurrence of ostr string in dest string with nstr string.
  Parameters: dest   -   Destination string.
              ostr   -   Old string.
              nstr   -   New string.
  Return:     Successful return new destination string address, no successful return ostr string address.
*/
char *strnrep(char *dest, char *ostr, const char *nstr)
{
	if(!strstr(dest, ostr))
		return ostr;
	do{
		dest = strrep(dest, ostr, nstr);
	}while(strstr(dest, ostr));

	return dest;
}

/*
   strrepex()
   Purpose:    Replace the first occurrence of string between ostrs and ostre in dest string with nstr string.
   Parameters: dest   -   Destination string.
               ostrs  -   Old string start position.
               ostre  -   Old string end position.
               nstr   -   New string.
   Return:     Successful return new destination string address, no successful return ostrs string address.
*/
char *strrepex(char *dest, char *ostrs, const char *ostre, const char *nstr)
{
	if(!strstr(dest, ostrs)) return ostrs;

	int ostrlen = strlen(strstr(dest, ostrs)) - strlen(strstr(strstr(dest, ostrs), ostre));
	char *ostr = (char *)malloc((ostrlen + 1)*sizeof(char));
	strncpy(ostr, strstr(dest, ostrs), ostrlen); 

	int retlen = strlen(dest) + strlen(nstr) - ostrlen;
	char *retstr = (char *)malloc((retlen + 1)*sizeof(char));

	char *midstr = strstr(dest, ostrs);
	int beflen = strlen(dest) - strlen(midstr);
	int aftlen = strlen(midstr) - ostrlen;

	memmove(retstr, dest, beflen);
	memmove(retstr + beflen, nstr, strlen(nstr));
	memmove(retstr + beflen + strlen(nstr), midstr + ostrlen, aftlen + 1);

	free((void *)ostr);
	free((void *)dest);
	return retstr;
}

/*
  strnrepex()
  Purpose:    Replace the all occurrence of string between ostrs and ostre in dest string with nstr string.
  Parameters: dest   -   Destination string.
              ostrs  -   Old string start position.
              ostre  -   Old string end position.
              nstr   -   New string.
  Return:     Successful return new destination string address, no successful return ostrs string address.
*/
char *strnrepex(char *dest, char *ostrs, char *ostre, const char *nstr)
{
	if(!strstr(dest, ostrs)) return ostrs;

	do{ 
		dest = strrepex(dest, ostrs, ostre, nstr); 
	}while (strstr(dest, ostrs));
	
	return dest;	
}