/*====================================================================*
 *
 *   void debug (signed status, errno_t number, char const * format, ...);
 *
 *   error.h
 *
 *   custom implementation of GNU error() function for systems
 *   that do not have it;
 *
 *   Motley Tools by Charles Maier <cmaier@cmassoc.net>;
 *   Copyright (c) 2001-2006 by Charles Maier Associates;
 *   Licensed under the Internet Software Consortium License;
 *
 *--------------------------------------------------------------------*/

#ifndef DEBUG_SOURCE
#define DEBUG_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "../tools/types.h"
#include "../tools/error.h"

#ifdef __GNUC__

__attribute__ ((format (printf, 3, 4))) 

#endif

void debug (signed status, char const * string, char const * format, ...) 

{
	extern char const * program_name;
	if ((program_name) && (* program_name)) 
	{
		fprintf (stderr, "%s: ", program_name);
	}
	if ((string) && (* string)) 
	{
		fprintf (stderr, "%s: ", string);
	}
	if ((format) && (*format)) 
	{
		va_list arglist;
		va_start (arglist, format);
		vfprintf (stderr, format, arglist);
		va_end (arglist);
	}
	fprintf (stderr, "\n");
	fflush (stderr);
	if (status) 
	{
		exit (status);
	}
	return;
}


#endif

