/*====================================================================*
 *
 *   size_t strfhex (char buffer [], size_t length, const byte memory [], size_t extent, unsigned c);
 *
 *   strlib.h
 *
 *   decode a memory block if given length in extent as a string of
 *   seperated hexadecimal octets; terminate when the string fills
 *   or the memory ends; terminate the string and return the actual
 *   string length;
 *
 *   allow three string characters for each memory byte; this means
 *   that the buffer must have at least three characters or nothing
 *   will be decoded; the maximum number of octets is the lesser of
 *   length/3 and extent;; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef STRFHEX_SOURCE
#define STRFHEX_SOURCE

#include <stddef.h>
#include <stdint.h>

#include "../strlib/strlib.h"
#include "../tools/number.h"

size_t strfhex (char buffer [], size_t length, const byte memory [], size_t extent, unsigned c) 

{
	char *string = buffer;

#ifdef CMASSOC_SAFEMODE

	if (buffer == (char) (0)) 
	{
		return (0);
	}
	if (memory == (char) (0)) 
	{
		return (0);
	}

#endif

	if (length) 
	{
		length /= 3;
		while ((length--) && (extent--)) 
		{
			if (string > buffer) 
			{
				*string++ = (c & 0x7F);
			}
			*string++ = DIGITS_HEX [(*memory >> 4) & 0x0F];
			*string++ = DIGITS_HEX [(*memory >> 0) & 0x0F];
			memory++;
		}
		*string = (char) (0);
	}
	return (string - buffer);
}


#endif

