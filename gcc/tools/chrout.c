/*====================================================================*
 *
 *   void chrout (void const * memory, size_t extent, char c, char e, FILE * fp) 
 *
 *   memory.h
 *
 *   print memory as an ASCII character string; replace non-printable 
 *   characters with (c) on output; terminate output with (e); 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef CHROUT_SOURCE
#define CHROUT_SOURCE

#include <stdio.h>
#include <ctype.h>

#include "../tools/memory.h"

void chrout (void const * memory, size_t extent, char c, char e, FILE * fp) 

{
	byte * offset = (byte *)(memory);
	while (extent--) 
	{
		putc (isprint (* offset)? * offset: c, fp);
		offset++;
	}
	if (e) 
	{
		putc (e, fp);
	}
	return;
}


#endif

