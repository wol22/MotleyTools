/*====================================================================*
 *
 *   ophptidy.cpp - definition of ophptidy class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oPHPTIDY_SOURCE
#define oPHPTIDY_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cerrno>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ophptidy.hpp"
#include "../classes/oascii.hpp"

/*====================================================================*
 *
 *   signed ophptidy::page (signed c);
 *
 *   search for PHP source; ignore asp source; 
 *
 *--------------------------------------------------------------------*/

signed ophptidy::page (signed c) 

{ 
	while (c != EOF) 
	{ 
		if (c == '<') 
		{ 
			c = osource::feed (c); 
			c = osource::find (c); 
			if (c == '!') 
			{ 
				c = ophptidy::context (c, '>'); 
				continue; 
			} 
			if (c == '%') 
			{ 
				c = ophptidy::context (c, '%', '>'); 
				continue; 
			} 
			if (c == '?') 
			{ 
				char string [256]; 
				char * cp = string; 
				do
				{ 
					* cp++ = c; 
					c = std::cin.get (); 
				} 
				while (oascii::isalpha (c)); 
				* cp = (char) (0); 
				std::cout << string; 
				if (!strcmp (string, "?php")) 
				{ 
					c = ophptidy::program (c); 
					continue; 
				} 
				if (!strcmp (string, "?xml")) 
				{ 
					c = ophptidy::context (c, '?', '>'); 
					continue; 
				} 
				continue; 
			} 
			while (oascii::isalpha (c)) 
			{ 
				c = osource::feed (c); 
			} 
			c = ophptidy::context (c, '>'); 
			continue; 
		} 
		c = osource::feed (c); 
	} 
	return (c); 
} 

/*====================================================================*
 *
 *   signed ophptidy::program (signed c);
 *
 *   format php markup using class ophptidy for support;
 *
 *--------------------------------------------------------------------*/

signed ophptidy::program (signed c) 

{ 
	ophptidy::space (1); 
	ophptidy::level (0); 
	while (c != EOF) 
	{ 
		if (oascii::isspace (c)) 
		{ 
			do
			{ 
				c = std::cin.get (); 
			} 
			while (oascii::isspace (c)); 
			std::cout.put (' '); 
			continue; 
		} 
		if (oascii::isquote (c)) 
		{ 
			c = osource::literal (c); 
			continue; 
		} 
		if (c == '?') 
		{ 
			c = std::cin.get (); 
			if (c == '>') 
			{ 
				ophptidy::newline (); 
				std::cout.put (' '); 
				std::cout.put ('?'); 
				break; 
			} 
			std::cout.put ('?'); 
			continue; 
		} 
		if (c == '#') 
		{ 
			ophptidy::endline (); 
			do
			{ 
				c = osource::command ('#', '\n'); 
			} 
			while (c == '#'); 
			ophptidy::space (1); 
			continue; 
		} 
		if (c == '/') 
		{ 
			ophptidy::endline (); 
			c = osource::comment (c); 
			ophptidy::space (1); 
			continue; 
		} 
		if (c == '{') 
		{ 

#if 0

			c = osource::feed (c); 
			c = osource::find (c); 
			ophptidy::increment (); 

#else

			if (!this->mlevel) 
			{ 
				ophptidy::endline (1); 
			} 
			ophptidy::endline (1); 
			ophptidy::newline (); 
			ophptidy::increment (); 
			c = osource::feed (c); 
			c = osource::find (c); 

#endif

			ophptidy::space (1); 
			continue; 
		} 
		if (c == '}') 
		{ 
			ophptidy::decrement (); 
			ophptidy::endline (1); 
			ophptidy::newline (); 
			c = osource::feed (c); 
			c = osource::find (c); 
			if (!this->mlevel) 
			{ 
				ophptidy::endline (1); 
			} 
			ophptidy::space (2); 
			continue; 
		} 
		if ((c == ',') || (c == ';') || (c == ':')) 
		{ 
			c = osource::feed (c); 
			c = osource::find (c); 
			ophptidy::space (2); 
			continue; 
		} 
		ophptidy::endline (1); 
		c = ophptidy::statement (c); 
		ophptidy::space (2); 
	} 
	c = osource::feed (c); 
	return (c); 
} 

/*====================================================================*
 *
 *   signed ophptidy::statement (signed c);
 *   
 *--------------------------------------------------------------------*/

signed ophptidy::statement (signed c) 

{ 
	char string [512]; 
	char * sp = string; 
	while (oascii::isalnum (c) || (c == '_')) 
	{ 
		* sp++ = c; 
		c = std::cin.get (); 
	} 
#if 0
	while (oascii::isspace (c)) 
	{ 
		c = std::cin.get (); 
	} 
#endif
	* sp = (char) (0); 
	if (sp == string) 
	{ 
		ophptidy::newline (this->mlevel); 
		c = ophptidy::context (c, ",;{}?#"); 
	} 
	else if (!std::strcmp (string, "case")) 
	{ 
		ophptidy::newline (this->mlevel-1); 
		std::cout << string; 
		c = ophptidy::context (c, ':'); 
	} 
	else if (!std::strcmp (string, "default")) 
	{ 
		ophptidy::newline (this->mlevel-1); 
		std::cout << string; 
		c = ophptidy::context (c, ':'); 
	} 
	else
	{ 
		ophptidy::newline (this->mlevel); 
		std::cout << string; 
		if ((c == '(') || (c == '[') || (c == '{')) 
		{ 
			std::cout.put (' '); 
		} 
		c = ophptidy::context (c, ",;{}?#"); 
	} 
	return (c); 
} 

/*====================================================================*
 *
 *   signed context (signed o, char const *charset); 
 *
 *   read stdin and buffer characters until one of the chracters in
 *   charset is read; return that character as the function value;
 *
 *   this function essentially collects an entire statement in the
 *   buffer; it is similar to other context methods but checks for 
 *   multiple terminators instead of one and returns the terminator
 *   instead of the following character;
 *
 *--------------------------------------------------------------------*/

signed ophptidy::context (signed c, char const * charset) 

{ 
	while ((c) && (c != EOF) && !std::strchr (charset, c)) 
	{ 
		c = ophptidy::context (c); 
	} 
	return (c); 
} 

/*====================================================================*
 *
 *   signed context (signed c, signed o, signed e);
 *
 *--------------------------------------------------------------------*/

signed ophptidy::context (signed c, signed o, signed e) 

{ 
	c = osource::feed (c); 
	c = ophptidy::_context (c, o, e); 
	c = osource::feed (c); 
	return (c); 
} 

signed ophptidy::_context (signed c, signed o, signed e) 

{ 
	while ((c != e) && (c != EOF)) 
	{ 
		c = ophptidy::_context (c, o); 
		c = osource::feed (c); 
	} 
	return (c); 
} 

/*====================================================================*
 *
 *   signed context (signed c, signed e); 
 *
 *   read and buffer nested expressions and literals until character
 *   (e) is encountered; buffer (e) and return the next character; 
 *
 *--------------------------------------------------------------------*/

signed ophptidy::context (signed c, signed e) 

{ 
	c = osource::feed (c); 
	c = osource::find (c); 
	c = ophptidy::_context (c, e); 
	c = osource::feed (c); 
	return (c); 
} 

signed ophptidy::_context (signed c, signed e) 

{ 
	while ((c != e) && (c != EOF)) 
	{ 
		c = ophptidy::context (c); 
	} 
	return (c); 
} 

/*====================================================================*
 *
 *   signed context (signed  c); 
 *
 *--------------------------------------------------------------------*/

signed ophptidy::context (signed c) 

{ 
	if (oascii::isspace (c)) 
	{ 
		c = osource::find (c); 
		if ((c == ',') || (c == ';')) 
		{ 
			return (c); 
		} 
		if ((c == ':') || (c == '?')) 
		{ 
			return (c); 
		} 
		if ((c == ')') || (c == ']') || (c == '}')) 
		{ 
			return (c); 
		} 
		std::cout.put (' '); 
	} 
	else if ((c == ',') || (c == ';') || (c == '?')) 
	{ 
		c = osource::feed (c); 
		c = osource::find (c); 
		std::cout.put (' '); 
	} 
	else if (oascii::isdigit (c)) 
	{ 
		do
		{ 
			c = osource::feed (c); 
		} 
		while (oascii::isdigit (c) || (c == '.')); 
	} 
	else if (oascii::isalpha (c)) 
	{ 
		do
		{ 
			c = osource::feed (c); 
		} 
		while (oascii::isalnum (c) || (c == '_')); 
		if ((c == '(') || (c == '[') || (c == '{')) 
		{ 
			std::cout.put (' '); 
		} 
	} 
	else if (oascii::isquote (c)) 
	{ 
		c = osource::literal (c); 
	} 
	else if (c == '/') 
	{ 
		c = osource::comment (c); 
	} 
	else if (c == '{') 
	{ 
		c = ophptidy::context ('{', '}'); 
	} 
	else if (c == '[') 
	{ 
		c = ophptidy::context ('[', ']'); 
	} 
	else if (c == '(') 
	{ 
		c = ophptidy::context ('(', ')'); 
	} 
	else
	{ 
		c = osource::feed (c); 
	} 
	return (c); 
} 

/*====================================================================*
 *
 *   ophptidy ()
 *
 *--------------------------------------------------------------------*/

ophptidy::ophptidy () 

{ 
	return; 
} 

/*====================================================================*
 *
 *   ~ ophptidy ()
 *
 *--------------------------------------------------------------------*/

ophptidy::~ophptidy () 

{ 
	return; 
} 

/*====================================================================*
 *   end definition
 *--------------------------------------------------------------------*/

#endif


