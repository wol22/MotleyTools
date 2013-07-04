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
 *   signed program (signed c);
 *
 *   format a source code file; 
 *
 *--------------------------------------------------------------------*/

signed octidy::program (signed c) 

{
	oindent::level (0);
	oindent::space (0);
	while (c != EOF) 
	{
		if (oascii::isspace (c)) 
		{
			do
			{
				c = std::cin.get ();
			}
			while (oascii::isspace (c));
			continue;
		}
		if (c == '#') 
		{
			oindent::endline ();
			do
			{
				c = osource::command (c, '\n');
			}
			while (c == '#');
			oindent::space (1);
			continue;
		}
		if (c == '/') 
		{
			oindent::endline ();
			do
			{
				c = osource::comment (c);
			}
			while (c == '/');
			oindent::endline (1);
			oindent::space (1);
			continue;
		}
		if (c == '{') 
		{
			if (!this->mlevel) 
			{
				oindent::endline (1);
			}
			oindent::endline (1);
			oindent::newline ();
			c = osource::feed (c);
			oindent::increment ();
			oindent::space (2);
			continue;
		}
		if (c == '}') 
		{
			oindent::decrement ();
			oindent::endline (1);
			oindent::newline ();
			do
			{
				c = osource::feed (c);
				c = osource::find (c);
			}
			while (c == ';');
			if (!this->mlevel) 
			{
				oindent::endline (1);
				oindent::space (1);
			}
			else
			{
				oindent::space (2);
			}
			continue;
		}
		if ((c == ',') || (c == ';') || (c == ':')) 
		{
			c = osource::feed (c);
			c = osource::find (c);
			oindent::space (2);
			continue;
		}
		oindent::endline (1);
		c = octidy::statement (c);
		oindent::space (2);
	}
	oindent::endline (1);
	return (c);
}

/*====================================================================*
 *
 *   signed atheros (signed c);
 *
 *--------------------------------------------------------------------*/

signed octidy::atheros (signed c) 

{
	oindent::level (0);
	oindent::space (0);
	while (c != EOF) 
	{
		if (oascii::isspace (c)) 
		{
			do
			{
				c = std::cin.get ();
			}
			while (oascii::isspace (c));
			continue;
		}
		if (c == '#') 
		{
			oindent::endline ();
			oinclude::header ();
			do
			{
				c = osource::command (c);
			}
			while (c == '#');
			oindent::space (1);
			continue;
		}
		if (c == '/') 
		{
			oindent::endline ();
			do
			{
				c = osource::comment (c);
			}
			while (c == '/');
			oindent::endline (1);
			oindent::space (1);
			continue;
		}
		if (c == '{') 
		{
			oindent::endline (1);
			if (!this->mlevel) 
			{
				oindent::endline (1);
				oindent::newline ();
				c = osource::feed (c);
			}
			else
			{
				c = osource::feed (c);
				oindent::endline (1);
				oindent::newline ();
			}
			oindent::increment ();
			oindent::space (1);
			continue;
		}
		if (c == '}') 
		{
			oindent::decrement ();
			oindent::endline (1);
			oindent::newline ();
			do
			{
				c = osource::feed (c);
				c = osource::find (c);
			}
			while (c == ';');
			if (!this->mlevel) 
			{
				oindent::endline (1);
				oindent::space (1);
			}
			else
			{
				oindent::space (2);
			}
			continue;
		}
		if ((c == ',') || (c == ';') || (c == ':')) 
		{
			c = osource::feed (c);
			c = osource::find (c);
			oindent::space (2);
			continue;
		}
		oindent::endline (1);
		c = octidy::statement (c);
		oindent::space (2);
		continue;
	}
	oindent::endline (1);
	return (c);
}

/*====================================================================*
 *
 *   signed charlie (signed c);
 *
 *   this method is similar method program() but annotates comments 
 *   and inserts include guards; essentially, this is charlie's own
 *   private formatter;
 *
 *--------------------------------------------------------------------*/

signed octidy::charlie (signed c) 

{
	oindent::level (0);
	oindent::space (0);
	c = ocomment::preamble (c);
	while (c != EOF) 
	{
		if (oascii::isspace (c)) 
		{
			do
			{
				c = std::cin.get ();
			}
			while (oascii::isspace (c));
			continue;
		}
		if (c == '#') 
		{
			oindent::endline ();
			oinclude::header ();
			do
			{
				c = osource::command (c);
			}
			while (c == '#');
			oindent::space (1);
			continue;
		}
		if (c == '/') 
		{
			oindent::endline ();
			do
			{
				c = ocomment::comment (c);
			}
			while (c == '/');
			oindent::space (1);
			continue;
		}
		if (c == '{') 
		{
			if (!this->mlevel) 
			{
				oindent::endline (1);
			}
			oindent::endline (1);
			oindent::newline ();
			c = osource::feed (c);
			oindent::increment ();
			oindent::space (2);
			continue;
		}
		if (c == '}') 
		{
			oindent::decrement ();
			oindent::endline (1);
			oindent::newline ();
			do
			{
				c = osource::feed (c);
				c = osource::find (c);
			}
			while (c == ';');
			if (!this->mlevel) 
			{
				oindent::endline (1);
				c = ocomment::preamble (c);
				oindent::space (1);
			}
			else
			{
				oindent::space (2);
			}
			continue;
		}
		if ((c == ',') || (c == ';') || (c == ':')) 
		{
			c = osource::feed (c);
			c = osource::find (c);
			oindent::space (2);
			continue;
		}
		oindent::endline (1);
		c = octidy::statement (c);
		oindent::space (2);
	}
	oindent::endline (1);
	oinclude::footer ();
	return (c);
}

/*====================================================================*
 *
 *   signed statement (signed c); 
 *
 *--------------------------------------------------------------------*/

signed octidy::statement (signed c) 

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
		oindent::print (this->mlevel, 0, string);
		c = octidy::context (c, ",;{}#");
	}
	else if (!std::strcmp (string, "class")) 
	{
		oindent::print (this->mlevel, 0, string);
		std::cout.put (' ');
		c = octidy::context (c, "{");
	}
	else if (octidy::exitwords.defined (string)) 
	{
		oindent::print (this->mlevel, 0, string);
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
		oindent::print (this->mlevel-1, 0, string);
		std::cout.put (':');
		oindent::endline (1);
		oindent::newline ();
		c = octidy::context (c, ",;{}#");
	}

#endif

	else if (!std::strcmp (string, "case")) 
	{
		oindent::print (this->mlevel-1, 0, string);
		std::cout.put (' ');
		c = octidy::context (c, ":");
	}
	else if (c == ':') 
	{
		if (c == std::cin.peek ()) 
		{
			oindent::print (this->mlevel, 0, string);
			c = osource::feed (c);
			c = osource::feed (c);
			c = octidy::context (c, ",;{}#");
		}
		else
		{
			oindent::print (this->mlevel-1, 0, string);
			c = osource::feed (c);
			c = osource::find (c);
			oindent::endline (1);
			oindent::newline ();
			c = octidy::context (c, ",;{}#");
		}
	}
	else
	{
		oindent::print (this->mlevel, 0, string);
		if (oascii::isalnum (c) || (c == '_')) 
		{
			std::cout.put (' ');
		}
		else if ((c == '(') || (c == '[')) 
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
 *--------------------------------------------------------------------*/

signed octidy::context (signed c, signed o, signed e) const 

{
	c = osource::feed (c);
	c = osource::find (c);
	c = octidy::_context (c, o, e);
	c = osource::feed (c);
	return (c);
}

signed octidy::_context (signed c, signed o, signed e) const 

{
	while ((c != e) && (c != EOF)) 
	{
		c = octidy::_context (c, o);
		c = osource::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   signed context (signed c, signed e) const; 
 *
 *--------------------------------------------------------------------*/

signed octidy::context (signed c, signed e) const 

{
	c = osource::feed (c);
	c = osource::find (c);
	c = octidy::_context (c, e);
	c = osource::feed (c);
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
 *--------------------------------------------------------------------*/

signed octidy::context (signed c) const 

{
	if (oascii::isalpha (c) || (c == '_')) 
	{
		c = octidy::moniker (c);
		if ((c == '(') || (c == '[')) 
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
		c = osource::find (c);
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
		c = osource::literal (c);
	}
	else if (c == '\\') 
	{
		signed o;
		o = osource::feed (c);
		c = osource::feed (o);
		if (o == '\n') 
		{
			oindent::print (oindent::margin (), oindent::offset (), oindent::level ());
		}
	}
	else if ((c == '.')) 
	{
		c = osource::feed (c);
		c = osource::find (c);
	}
	else if ((c == ',') || (c == ';')) 
	{
		c = osource::feed (c);
		c = osource::find (c);
		std::cout.put (' ');
	}
	else if ((c == '~') || (c == '^') || (c == '%')) 
	{
		c = osource::feed (c);
		if (c == '=') 
		{
			c = osource::feed (c);
		}
	}
	else if ((c == '=') || (c == '!')) 
	{
		c = osource::feed (c);
		if (c == '=') 
		{
			c = osource::feed (c);
		}
	}
	else if (c == '&') 
	{
		c = osource::feed (c);
		if (c == '&') 
		{
			c = osource::feed (c);
		}
		else if (c == '=') 
		{
			c = osource::feed (c);
		}
		else if (oascii::isalpha (c)) 
		{
			std::cout.put (' ');
		}
	}
	else if (c == '|') 
	{
		c = osource::feed (c);
		if (c == '|') 
		{
			c = osource::feed (c);
		}
		else if (c == '=') 
		{
			c = osource::feed (c);
		}
	}
	else if ((c == '<') || (c == '>')) 
	{
		char o = c;
		c = osource::feed (c);
		if (c == o) 
		{
			c = osource::feed (c);
		}
		if (c == '=') 
		{
			c = osource::feed (c);
		}
	}
	else if ((c == '?') || (c == ':')) 
	{
		char o = c;
		c = osource::feed (c);
		if (c == o) 
		{
			c = osource::feed (c);
		}
		if (c == '=') 
		{
			c = osource::feed (c);
		}
	}
	else if (c == '+') 
	{
		c = osource::feed (c);
		if (c =='+') 
		{
			c = osource::feed (c);
		}
		else if (c == '=') 
		{
			c = osource::feed (c);
		}
	}
	else if (c == '-') 
	{
		c = osource::feed (c);
		if (c == '-') 
		{
			c = osource::feed (c);
		}
		else if (c == '=') 
		{
			c = osource::feed (c);
		}
		else if (c == '>') 
		{
			c = osource::feed (c);
		}
	}
	else if (c == '*') 
	{
		c = osource::feed (c);
		if (c == '*') 
		{
			do
			{
				c = osource::feed (c);
			}
			while (c == '*');
			if (oascii::isalpha (c)) 
			{
				std::cout.put (' ');
			}
		}
		else if (c == '=') 
		{
			c = osource::feed (c);
		}
		else if (oascii::isalpha (c)) 
		{
			std::cout.put (' ');
		}
	}
	else if (c == '/') 
	{
		c = osource::feed (c);
		if (c == '/') 
		{
			c = osource::content (c, '\n');
		}
		else if (c == '*') 
		{
			c = osource::content (c, '*', '/');
		}
		else if (c == '=') 
		{
			c = osource::feed (c);
		}
	}
	else if (c == '#') 
	{
		c = osource::command (c, '\n');
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
		c = osource::feed (c);
	}
	return (c);
}

/*====================================================================*
 *
 *   octidy()
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
 *--------------------------------------------------------------------*/

octidy::~octidy () 

{
	return;
}

/*====================================================================*
 *   end definition
 *--------------------------------------------------------------------*/

#endif

