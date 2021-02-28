/*
 * Tools.c
 *
 *  Created on: 26 févr. 2021
 *      Author: Utilisateur
 */


#include "Tools.h"

char *strsep(char **stringp, const char *delim) {
    char *rv = *stringp;
    if (rv) {
        *stringp += strcspn(*stringp, delim);
        if (**stringp)
            *(*stringp)++ = '\0';
        else
            *stringp = 0; }
    return rv;
}

char * __strsep (char **stringp, const char *delim)
{
  char *begin, *end;
  begin = *stringp;
  if (begin == NULL)
    return NULL;
  // Find the end of the token.
  end = begin + strcspn (begin, delim);
  if (*end)
    {
//       Terminate the token and set *STRINGP past NUL character.
      *end++ = '\0';
      *stringp = end;
    }
  else
    // No more delimiters; this is the last token.
    *stringp = NULL;
  return begin;
}

UINT8 ToolsPutArrayToBuffer(OUT UINT8* pu8BuffOut,
                              IN const UINT8* pu8Data,
                              IN UINT8 u8Length)
{
   UINT8 i = 0;

   for(i = 0; i < u8Length; i++)
   {
      pu8BuffOut[i] = pu8Data[i];
   }

   return i;
}




