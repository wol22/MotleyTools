/*====================================================================*
 *
 *   size_t _fread(void *buffer, size_t itemsize, size_t count, FILE *fp);
 *
 *   _stdio.h
 *
 *   copy the specified number of items, each of the specified size, from
 *   the buffer assigned to a file pointer; return the number of items
 *   actually copied or 0 on end-of-file or i/o error;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#include "_stdio.h"

size_t _fread (void *buffer, size_t itemsize, size_t count, FILE * fp) 

{
	register char *buf = (char *)(buffer);
	register size_t index;
	if ((fp != NULL) && ((fp->_flag & (_IOREAD | _IOERR | _IOEOF)) == _IOREAD)) 
	{
		count *= itemsize;
		for (index = 0; index < count; index++) 
		{
			if ((fp->_cnt <= 0) && (ffill (fp) == EOF)) 
			{
				break;
			}
			buf [index] = *fp->_ptr++;
			fp->_cnt--;
		}
		return (((fp->_flag & (_IOERR)) != 0)? 0: index / itemsize);
	}
	else 
	{
		return (0);
	}
}

