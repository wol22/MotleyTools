/*====================================================================*
 *
 *   void version();
 *
 *   version.h
 *
 *   print program and package version information on stdout; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef PUTOPT_SOURCE
#define PUTOPT_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include "../tools/version.h"

void version () 

{
	extern char const *program_name;
	printf ("%s ", program_name);
	printf (PACKAGE "-");
	printf (VERSION " ");
	printf ("ISO C ");
	printf (COMPANY " ");
	printf (RELEASE " ");
	printf (LICENSE "\n");
	return;
}


#endif

