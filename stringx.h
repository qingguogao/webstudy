#ifndef _stringx_h_
#define _stringx_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
  strrep()
  Purpose:    Replace the first occurrence of ostr string in dest string with nstr string.
  Parameters: dest   -   Destination string.
              ostr   -   Old string.
              nstr   -   New string.
  Return:     Successful return new destination string address, no successful return ostr string address.
*/
char *strrep(char *dest, char *ostr, const char *nstr);

/*
  strnrep()
  Purpose:    Replace the all occurrence of ostr string in dest string with nstr string.
  Parameters: dest   -   Destination string.
              ostr   -   Old string.
              nstr   -   New string.
  Return:     Successful return new destination string address, no successful return ostr string address.
*/
char *strnrep(char *dest, char *ostr, const char *nstr);

/*
   strrepex()
   Purpose:    Replace the first occurrence of string between ostrs and ostre in dest string with nstr string.
   Parameters: dest   -   Destination string.
               ostrs  -   Old string start position.
               ostre  -   Old string end position.
               nstr   -   New string.
   Return:     Successful return new destination string address, no successful return ostrs string address.
*/
char *strrepex(char *dest, char *ostrs, const char *ostre, const char *nstr);

/*
  strnrepex()
  Purpose:    Replace the all occurrence of string between ostrs and ostre in dest string with nstr string.
  Parameters: dest   -   Destination string.
              ostrs  -   Old string start position.
              ostre  -   Old string end position.
              nstr   -   New string.
  Return:     Successful return new destination string address, no successful return ostrs string address.
*/
char *strnrepex(char *dest, char *ostrs, char *ostre, const char *nstr);

#endif //end _stringx_h_