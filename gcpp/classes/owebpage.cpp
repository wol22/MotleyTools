/*====================================================================*
 *
 *   owebpage.cpp - definition of the owebpage class.
 *
 *.  Motley Tools by Charles Maier
 *:  Published 1982-2005 by Charles Maier for personal use
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

#ifndef oWEBPAGE_SOURCE
#define oWEBPAGE_SOURCE

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/owebpage.hpp"

/*====================================================================*
 *   data initialization; 
 *--------------------------------------------------------------------*/

oenviron session;

/*====================================================================*
 * 
 *   char const * title (void) const;
 *
 *   return the page title as a constant string;
 *
 *--------------------------------------------------------------------*/

char const * owebpage::title (void) const 

{
	return (this->mtitle);
}

/*====================================================================*
 * 
 *   owebpage & title (char const * string) 
 *
 *   replace current title with the constant string argument only
 *   if they differ;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::title (char const * string) 

{
	this->mtitle = otext::replace (this->mtitle, string);
	return (* this);
}

/*====================================================================*
 * 
 *   char const * PageStyle (void) const;
 *
 *   return the stylesheet as a constant character string;
 *
 *--------------------------------------------------------------------*/

char const * owebpage::stylesheet (void) const 

{
	return (this->mstylesheet);
}

/*====================================================================*
 * 
 *   owebpage & PageStyle (char const * stylesheet);
 *
 *   replace the current stylesheet with the constant string argument 
 *   only if they differ;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::stylesheet (char const * stylesheet) 

{
	this->mstylesheet = otext::replace (this->mstylesheet, stylesheet);
	return (* this);
}

/*====================================================================*
 * 
 *   owebpage & PageHeader (void);
 *
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::PageHeader (void) 

{
	owebpage::print (this->mlevel, this->mspace, "<?xml version='1.0' encoding='iso-8859-1'?>");
	owebpage::print (this->mlevel, this->mspace, "<!DOCTYPE HTML PUBLIC '//W3C//DTD XHTML 1.0 Transitional//EN'>");
	owebpage::print (this->mlevel++, this->mspace, "<html xmlns='http://www.w3.org/1999/xhtml'>");
	owebpage::print (this->mlevel++, this->mspace, "<head>");
	owebpage::print (this->mlevel++, this->mspace, "<title>");
	owebpage::print (this->mlevel, this->mspace, this->mtitle);
	owebpage::print (this->mlevel--, this->mspace, "</title>");
	owebpage::MetaElement.Contents ("robots", "noindex,nofollow").EmptyTag (this->mlevel, this->mspace);
	owebpage::MetaElement.Contents ("author", "charles maier").EmptyTag (this->mlevel, this->mspace);
	owebpage::MetaElement.Contents ("generator", "Motley Tools").EmptyTag (this->mlevel, this->mspace);
	owebpage::MetaElement.Contents ("keywords", "peace, love, beauty, truth").EmptyTag (this->mlevel, this->mspace);
	owebpage::print (this->mlevel, 0, "<link href='");
	owebpage::print (0, 0, this->mstylesheet);
	owebpage::print (0, this->mspace, "' rel='stylesheet' type='text/css'/>");
	owebpage::print (this->mlevel--, this->mspace, "</head>");
	owebpage::print (this->mlevel++, this->mspace, "<body>");
	return (* this);
}

/*====================================================================*
 *   
 *   owebpage & BodyHeader (void);
 *
 *   print the page header;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::BodyHeader (void) 

{
	owebpage::print (this->mlevel++, this->mspace, "<div class='" oWEBPAGE_BODY_HEADER_CLASS "'>");
	owebpage::print (this->mlevel--, this->mspace, "</div>");
	return (* this);
}

/*====================================================================*
 *   
 *   owebpage & LinkHeader (void);
 *
 *   print the upper link division containing PREV, HOME and NEXT links;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::LinkHeader (void) 

{
	owebpage::print (this->mlevel++, this->mspace, "<div class='" oWEBPAGE_LINK_HEADER_CLASS "'>");

#if 0

	owebpage::print (this->mlevel, this->mspace, owebpage::PrevPageLink.string ());
	owebpage::print (this->mlevel, this->mspace, owebpage::HomePageLink.string ());
	owebpage::print (this->mlevel, this->mspace, owebpage::NextPageLink.string ());

#else

	owebpage::PrevPageLink.write ();
	owebpage::HomePageLink.write ();
	owebpage::NextPageLink.write ();

#endif

	owebpage::print (this->mlevel--, this->mspace, "</div>");
	return (* this);
}

/*====================================================================*
 *   
 *   owebpage & MarkStart (void);
 *
 *   print a content prefix tag;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::MarkStart (void) 

{
	owebpage::print (0, this->mspace, "<!-- BEGIN CONTENT -->");
	return (* this);
}

/*====================================================================*
 *   
 *   owebpage & MarkEnd (void);
 *
 *   print a content suffix tag;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::MarkEnd (void) 

{
	owebpage::print (0, this->mspace, "<!-- END CONTENT -->");
	return (* this);
}

/*====================================================================*
 *   
 *   owebpage & LinkFooter (void);
 *
 *   print the lower link division containing PREV, HOME and NEXT links;
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::LinkFooter (void) 

{
	owebpage::print (this->mlevel++, this->mspace, "<div class='" oWEBPAGE_LINK_FOOTER_CLASS "'>");

#if 0

	owebpage::print (this->mlevel, this->mspace, owebpage::PrevPageLink.string ());
	owebpage::print (this->mlevel, this->mspace, owebpage::HomePageLink.string ());
	owebpage::print (this->mlevel, this->mspace, owebpage::NextPageLink.string ());

#else

	owebpage::PrevPageLink.write ();
	owebpage::HomePageLink.write ();
	owebpage::NextPageLink.write ();

#endif

	owebpage::print (this->mlevel--, this->mspace, "</div>");
	return (* this);
}

/*====================================================================*
 *   
 *   owebpage & BodyFooter (void);
 *
 *   print the page footer; the footer identifies the source and data of
 *   publication plus other information; 
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::BodyFooter (void) 

{
	char buffer [512];
	owebpage::session.strfwhat (buffer, sizeof (buffer), "Published");
	owebpage::print (this->mlevel++, this->mspace, "<div class='" oWEBPAGE_BODY_FOOTER_CLASS "'>");
	owebpage::print (this->mlevel, this->mspace, this->mowner);
	owebpage::print (this->mlevel, this->mspace, "<br/>");
	owebpage::print (this->mlevel, this->mspace, buffer);
	owebpage::print (this->mlevel--, this->mspace, "</div>");
	return (* this);
}

/*====================================================================*
 *
 *   owebpage & PageFooter (void);
 *
 *
 *--------------------------------------------------------------------*/

owebpage & owebpage::PageFooter (void) 

{
	owebpage::print (this->mlevel--, this->mspace, "</body>");
	owebpage::print (this->mlevel--, this->mspace, "</html>");
	return (* this);
}

/*====================================================================*
 *
 *   owebpage ();
 *   
 *   
 *--------------------------------------------------------------------*/

owebpage::owebpage (void) 

{
	this->mtitle = otext::save (oWEBPAGE_PAGE_TITLE);
	this->mstylesheet = otext::save (oWEBPAGE_PAGE_STYLE);
	this->mowner = otext::save ("Courtesy of <a href='mailto:cmaier@cmassoc.net'>Charles Maier Associates Limited</a>, The Motley Tools Folks, Nashua NH, USA");
	owebpage::PrevPageLink.name ("PREV").link (oWEBPAGE_LINK_PREV_NAME, oWEBPAGE_LINK_PREV_PAGE);
	owebpage::HomePageLink.name ("HOME").link (oWEBPAGE_LINK_HOME_NAME, oWEBPAGE_LINK_HOME_PAGE);
	owebpage::NextPageLink.name ("NEXT").link (oWEBPAGE_LINK_NEXT_NAME, oWEBPAGE_LINK_NEXT_PAGE);
	return;
}

/*====================================================================*
 *
 *   ~owebpage (void);
 *   
 *   
 *--------------------------------------------------------------------*/

owebpage::~owebpage (void) 

{
	delete [] this->mtitle;
	delete [] this->mstylesheet;
	delete [] this->mowner;
	return;
}

/*====================================================================*
 *   end definition;
 *--------------------------------------------------------------------*/

#endif

