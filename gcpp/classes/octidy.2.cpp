/*====================================================================*
 *
 *   octidy.cpp - definition of octidy class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oCTIDY_SOURCE
#define oCTIDY_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdio>
#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/oascii.hpp"
#include "../classes/octidy.hpp"

/*====================================================================*
 *   class variables;        
 *--------------------------------------------------------------------*/

ocgotowords octidy::gotowords;
ocexitwords octidy::exitwords;

/*====================================================================*
 *
 *   signed octidy::atheros (signed c, signed e);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed octidy::atheros (signed c, signed e) 

{
	signed level = 0;
	signed space = 0;
	while ((c != e) && (c != EOF)) 
	{
		if (oascii::isspace (c)) 
		{
			c = std::cin.get ();
			continue;
		}
		if (c == '#') 
		{
			octidy::space (space);
			do 
			{
				c = octidy::command (c, '\n');
			}
			while (c == '#');
			space = 1;
			continue;
		}
		if (c == '/') 
		{
			octidy::space (space);
			do 
			{
				c = octidy::comment (c);
			}
			while (c == '/');
			space = 1;
			continue;
		}
		if (c == '{') 
		{
			if (!level) 
			{
				octidy::space (2);
				c = octidy::feed (c);
				c = octidy::find (c);
				octidy::level (level++);
			}
			else 
			{
				c = octidy::feed (c);
				c = octidy::find (c);
				octidy::level (level++);
			}
			space = 2;
			continue;
		}
		if (c == '}') 
		{
			octidy::space (1);
			octidy::level (--level);
			do 
			{
				c = octidy::feed (c);
				c = octidy::find (c);
			}
			while (c == ';');
			if (!level) 
			{
				octidy::space (1);
				space = 1;
			}
			else 
			{
				space = 2;
			}
			continue;
		}
		if ((c == ',') || (c == ';') || (c == ':')) 
		{
			c = octidy::feed (c);
			c = octidy::find (c);
			space = 2;
			continue;
		}
		octidy::space (1);
		c = octidy::statement (c, level, space);
		space = 2;
		continue;
	}
	octidy::space (space);
	return (c);
}

/*====================================================================*
 *
 *   signed octidy::charlie (signed c);
 *
 *   this method is similar method program() but annotates comments 
 *   and inserts include guards; essentially, this is charlie's own
 *   private formatter;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed octidy::charlie (signed c, signed e) 

{
	signed level = 0;
	signed space = 0;
	c = ocomment::preamble (c);
	while ((c != e) && (c != EOF)) 
	{
		if (oascii::isspace (c)) 
		{
			c = std::cin.get ();
			continue;
		}
		if (c == '#') 
		{
			octidy::space (space);
			oinclude::header ();
			do 
			{
				c = octidy::command (c);
			}
			while (c == '#');
			space = 1;
			continue;
		}
		if (c == '/') 
		{
			octidy::space (space);
			do 
			{
				c = ocomment::comment (c);
			}
			while (c == '/');
			space = 1;
			continue;
		}
		if (c == '{') 
		{
			if (!level) 
			{
				octidy::space (1);
			}
			octidy::space (1);
			octidy::level (level++);
			c = octidy::feed (c);
			c = octidy::find (c);
			space = 2;
			continue;
		}
		if (c == '}') 
		{
			octidy::space (1);
			octidy::level (--level);
			do 
			{
				c = octidy::feed (c);
				c = octidy::find (c);
			}
			while (c == ';');
			if (!level) 
			{
				octidy::space (1);
				c = ocomment::preamble (c);
				space = 1;
			}
			else 
			{
				space = 2;
			}
			continue;
		}
		if ((c == ',') || (c == ';') || (c == ':')) 
		{
			c = octidy::feed (c);
			c = octidy::find (c);
			space = 2;
			continue;
		}
		octidy::space (1);
		c = octidy::statement (c, level, space);
		space = 2;
	}
	octidy::space (1);
	oinclude::footer ();
	return (c);
}

/*====================================================================*
 *
 *   signed octidy::program (signed c, signed e);
 *
 *   format a source code file; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed octidy::program (signed c, signed e) 

{
	signed level = 0;
	signed space = 0;
	while ((c != e) && (c != EOF)) 
	{
		if (oascii::isspace (c)) 
		{
			c = std::cin.get ();
			continue;
		}
		if (c == '#') 
		{
			octidy::space (space);
			do 
			{
				c = octidy::command (c, '\n');
			}
			while (c == '#');
			space = 1;
			continue;
		}
		if (c == '/') 
		{
			octidy::space (space);
			do 
			{
				c = octidy::comment (c);
			}
			while (c == '/');
			space = 1;
			continue;
		}
		if (c == '{') 
		{
			if (!level) 
			{
				octidy::space (1);
			}
			octidy::space (1);
			octidy::level (level++);
			c = octidy::feed (c);
			c = octidy::find (c);
			space = 2;
			continue;
		}
		if (c == '}') 
		{
			octidy::space (1);
			octidy::level (--level);
			do 
			{
				c = octidy::feed (c);
				c = octidy::find (c);
			}
			while (c == ';');
			if (!level) 
			{
				octidy::space (1);
				space = 1;
			}
			else 
			{
				space = 2;
			}
			continue;
		}
		if ((c == ',') || (c == ';') || (c == ':')) 
		{
			c = octidy::feed (c);
			c = octidy::find (c);
			space = 2;
			continue;
		}
		octidy::space (1);
		c = octidy::statement (c, level, space);
		space = 2;
	}
	octidy::space (space);
	return (c);
}

/*====================================================================*
 *
 *   signed statement (signed c, signed level, signed space); 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed octidy::statement (signed c, signed level, signed space) 

{
	char string [512];
	char * sp = string;
	while (oascii::isalnum (c) || (c == '_') || (c == '.')) 
	{
		* sp++ = c;
		c = std::cin.get ();
	}
	* sp = (char) (0);
	while (oascii::isspace (c)) 
	{
		c = std::cin.get ();
	}
	if (sp == string) 
	{
		octidy::print (level, 0, string);
		c = octidy::context (c, ",;{}#");
	}
	else if (!std::strcmp (string, "class")) 
	{
		octidy::print (level, 0, string);
		std::cout.put (' ');
		c = octidy::context (c, "{");
	}
	else if (octidy::exitwords.defined (string)) 
	{
		octidy::print (level, 0, string);
		if (c == ';') 
		{
		}
		else if (c == '(') 
		{
			std::cout.put (' ');
			c = octidy::context (c, ",;{}#");
		}
		else 
		{
			std::cout.put (' ');
			std::cout.put ('(');
			c = octidy::context (c, ";");
			std::cout.put (')');
		}
	}
#if 0
/*
 *	this may be obsolete and assumes that a colon sollows the keyword;
 *	the check vof colon has been moved;
 */
	else if (octidy::gotowords.defined (string)) 
	{
		octidy::print (level-1, 0, string);
		std::cout.put (':');
		octidy::space (1).level (level);
		c = octidy::context (c, ",;{}#");
	}
#endif
	else if (!std::strcmp (string, "case")) 
	{
		octidy::print (level-1, 0, string);
		std::cout.put (' ');
		c = octidy::context (c, ":");
	}
	else if (c == ':')
	{
		if (c == std::cin.peek ()) 
		{
			octidy::print (level, 0, string);
			c = octidy::feed (c);
			c = octidy::feed (c);
			c = octidy::context (c, ",;{}#");
		}
		else
		{
			octidy::print (level-1, 0, string);
			c = octidy::feed (c);
			c = octidy::find (c);
			octidy::space (1).level (level);
			c = octidy::context (c, ",;{}#");
		}	
	}
	else 
	{
		octidy::print (level, 0, string);
		if (oascii::isalnum (c) || (c == '_')) 
		{
			std::cout.put (' ');
		}
		else if ((c == '(') || (c == '[') || (c == '{')) 
		{
			std::cout.put (' ');
		}
		else if ((c == '=') || (c == '<') || (c == '>')) 
		{
			std::cout.put (' ');
		}
		else if ((c == '!') || (c == '&') || (c == '|') || (c == '~')) 
		{
			std::cout.put (' ');
		}
		else if ((c == '*') || (c == '/') || (c == '%')) 
		{
			std::cout.put (' ');
		}
		else if ((c == '+') || (c == '-'))
		{
			if (std::cin.peek () == '=')
			{
				std::cout.put (' ');
			}
		}
		c = octidy::context (c, ",;{}#");
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed c, char const * charset) const; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed octidy::context (signed c, char const * charset) const 

{
	while ((c) && (c != EOF) && !std::strchr (charset, c)) 
	{
		c = octidy::context (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed c, signed o, signed e) const;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed octidy::context (signed c, signed o, signed e) const 

{
	c = octidy::feed (c);
	c = octidy::_context (c, o, e);
	c = octidy::feed (c);
	return (c);
}

signed octidy::_context (signed c, signed o, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = octidy::_context (c, o);
		c = octidy::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed c, signed e) const; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed octidy::context (signed c, signed e) const 

{
	c = octidy::feed (c);
	c = octidy::find (c);
	c = octidy::_context (c, e);
	c = octidy::feed (c);
	return (c);
}

signed octidy::_context (signed c, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = octidy::context (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed  c) const; 
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed octidy::context (signed c) const 

{
	if (oascii::isalpha (c) || (c == '_')) 
	{
		while (oascii::isalnum (c) || (c == '_')) 
		{
			c = octidy::feed (c);
		}
		if ((c == '(') || (c == '[') || (c == '{')) 
		{
			std::cout.put (' ');
		}
		else if ((c == '=') || (c == '<') || (c == '>')) 
		{
			std::cout.put (' ');
		}
		else if ((c == '*') || (c == '/') || (c == '%')) 
		{
			std::cout.put (' ');
		}
		else if ((c == '!') || (c == '&') || (c == '|') || (c == '~')) 
		{
			std::cout.put (' ');
		}
		else if ((c == '+') || (c == '-'))
		{
			if (std::cin.peek () == '=')
			{
				std::cout.put (' ');
			}
		}
	}
	else if (oascii::isspace (c)) 
	{
		c = octidy::find (c);
		if ((c == ')') || (c == ']') || (c == '}')) 
		{
			return (c);
		}
		if ((c == ',') || (c == ';')) 
		{
			return (c);
		}
		if ((c == '?') || (c == ':')) 
		{
			return (c);
		}
		if ((c == '.')) 
		{
			return (c);
		}
		std::cout.put (' ');
	}
	else if (oascii::isquote (c)) 
	{
		c = octidy::literal (c);
	}
	else if (c == '\\') 
	{
		c = octidy::feed (c);
		c = octidy::feed (c);
	}
	else if ((c == '.')) 
	{
		c = octidy::feed (c);
		c = octidy::find (c);
	}
	else if ((c == ',') || (c == ';')) 
	{
		c = octidy::feed (c);
		c = octidy::find (c);
		std::cout.put (' ');
	}
	else if ((c == '~') || (c == '^') || (c == '%')) 
	{
		c = octidy::feed (c);
		if (c == '=') 
		{
			c = octidy::feed (c);
		}
	}
	else if ((c == '=') || (c == '!')) 
	{
		c = octidy::feed (c);
		if (c == '=') 
		{
			c = octidy::feed (c);
		}
	}
	else if (c == '&') 
	{
		c = octidy::feed (c);
		if (c == '&') 
		{
			c = octidy::feed (c);
		}
		else if (c == '=') 
		{
			c = octidy::feed (c);
		}
		else if (oascii::isalpha (c)) 
		{
			std::cout.put (' ');
		}
	}
	else if (c == '|') 
	{
		c = octidy::feed (c);
		if (c == '|') 
		{
			c = octidy::feed (c);
		}
		else if (c == '=') 
		{
			c = octidy::feed (c);
		}
	}
	else if ((c == '<') || (c == '>')) 
	{
		char o = c;
		c = octidy::feed (c);
		if (c == o) 
		{
			c = octidy::feed (c);
		}
		if (c == '=') 
		{
			c = octidy::feed (c);
		}
	}
	else if ((c == '?') || (c == ':')) 
	{
		char o = c;
		c = octidy::feed (c);
		if (c == o) 
		{
			c = octidy::feed (c);
		}
		if (c == '=') 
		{
			c = octidy::feed (c);
		}
	}
	else if (c == '+') 
	{
		c = octidy::feed (c);
		if (c =='+') 
		{
			c = octidy::feed (c);
		}
		else if (c == '=') 
		{
			c = octidy::feed (c);
		}
	}
	else if (c == '-') 
	{
		c = octidy::feed (c);
		if (c == '-') 
		{
			c = octidy::feed (c);
		}
		else if (c == '=') 
		{
			c = octidy::feed (c);
		}
		else if (c == '>') 
		{
			c = octidy::feed (c);
		}
	}
	else if (c == '*') 
	{
		c = octidy::feed (c);
		if (c == '*') 
		{
			do 
			{
				c = octidy::feed (c);
			}
			while (c == '*');
			if (oascii::isalpha (c)) 
			{
				std::cout.put (' ');
			}
		}
		else if (c == '=') 
		{
			c = octidy::feed (c);
		}
		else if (oascii::isalpha (c)) 
		{
			std::cout.put (' ');
		}
	}
	else if (c == '/') 
	{
		c = octidy::feed (c);
		if (c == '/') 
		{
			c = octidy::content (c, '\n');
		}
		else if (c == '*') 
		{
			c = octidy::content (c, '*', '/');
		}
		else if (c == '=') 
		{
			c = octidy::feed (c);
		}
	}
	else if (c == '#') 
	{
		c = octidy::command (c, '\n');
	}
	else if (c == '(') 
	{
		c = octidy::context (c, ')');
	}
	else if (c == '[') 
	{
		c = octidy::context (c, ']');
	}
	else if (c == '{') 
	{
		c = octidy::context (c, '}');
	}
	else 
	{
		c = octidy::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed comment (signed c) const;
 *
 *   read and write C and C++ comments;
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed octidy::comment (signed c) const 

{
	c = octidy::feed (c);
	if (c == '/') 
	{
		c = octidy::content (c, '\n');
		return (c);
	}
	if (c == '*') 
	{
		c = octidy::content (c, '*', '/');
		return (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed find (signed c) const;
 *
 *   read and discard whitespace; start with current character (c);
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

signed octidy::find (signed c) const 

{
	while (oascii::isspace (c)) 
	{
		c = std::cin.get ();
	}
	return (c);
}

/*====================================================================*
 *
 *   octidy()
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

octidy::octidy () 

{
	return;
}

/*====================================================================*
 *
 *   ~octidy()
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

octidy::~octidy () 

{
	return;
}

/*====================================================================*
 *   end definition
 *--------------------------------------------------------------------*/

#endif
