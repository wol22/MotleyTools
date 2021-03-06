/*====================================================================*
 *
 *   code_t namecode (struct _code_ const list[], size_t count, char const * name, code_t code);
 *
 *   symbol.h  
 *
 *   return the code associated with a given name by searching a list
 *   of list arranged in ascending order by name; typedef code_t and
 *   struct _code_ are defined in types.h; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef NAMECODE_SOURCE
#define NAMECODE_SOURCE

#include <string.h>

#include "../tools/symbol.h"

code_t namecode (struct _code_ const list [], size_t size, char const * name, code_t code) 

{
	size_t lower = 0;
	size_t upper = size;
	while (lower < upper) 
	{
		size_t index = (lower + upper) >> 1;
		signed order = strcmp (name, list [index].name);
		if (order < 0) 
		{
			upper = index - 0;
			continue;
		}
		if (order > 0) 
		{
			lower = index + 1;
			continue;
		}
		return (list [index].code);
	}
	return (code);
}


#endif

