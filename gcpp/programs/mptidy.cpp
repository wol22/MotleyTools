/*====================================================================*
 *
 *   mptidy.cpp - tidy man page files;
 *
 *.  Motley Tools by Charles Maier <cmaier@cmassoc.net>;
 *:  Copyright 2001-2006 by Charles Maier Associates;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/

#include <cstdlib>
#include <cstring>
#include <iostream>            

/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/

#include "../classes/ogetoptv.hpp"
#include "../classes/oerror.hpp"
#include "../classes/oescape.hpp"
#include "../classes/ofileopen.hpp"
#include "../classes/opathspec.hpp"
#include "../classes/oprofile.hpp"
#include "../classes/omptidy.hpp"

/*====================================================================*
 *   custom source files;
 *--------------------------------------------------------------------*/

#ifndef MAKEFILE
#include "../classes/ogetoptv.cpp"
#include "../classes/oputoptv.cpp"
#include "../classes/oversion.cpp"
#include "../classes/oerror.cpp"
#include "../classes/oflagword.cpp"
#include "../classes/ofileopen.cpp"
#include "../classes/ofilespec.cpp"
#include "../classes/opathspec.cpp"
#include "../classes/oprofile.cpp"
#include "../classes/ocontext.cpp"
#include "../classes/ocollect.cpp"
#include "../classes/owildcard.cpp"
#include "../classes/oescape.cpp"
#include "../classes/oascii.cpp"
#include "../classes/oindent.cpp"
#include "../classes/oswitch.cpp"
#include "../classes/otext.cpp"
#include "../classes/omptidy.cpp"
#endif

#define MPTIDY_S_PROFILE "/etc/mp.ini"     
#define MPTIDY_S_SECTION "default"     
#define MPTIDY_S_PROJECT "Motley Tools"     
#define MPTIDY_S_PACKAGE "mtools-1.8.1"     
#define MPTIDY_S_PROGRAM "program"     
#define MPTIDY_S_RELEASE "data/time"     

/*====================================================================*
 *   
 *   int main (int argc, char const * argv []);
 *   
 *   
 *.  Motley Tools by Charles Maier <cmaier@cmassoc.net>;
 *:  Copyright 2001-2006 by Charles Maier Associates;
 *;  Licensed under the Internet Software Consortium License
 *
 *--------------------------------------------------------------------*/

int main (int argc, char const * argv []) 

{
	static char const * optv [] = 
	{
		"op:s:",
		oPUTOPTV_S_FILTER,
		"format C/C++ source code with preamble annotations",
		"o\toutput configuration profile on stdout",
		"p s\tprofile is (s) [" LITERAL (MPTIDY_S_PROFILE) "]",
		"s s\tsection is (s) [" LITERAL (MPTIDY_S_SECTION) "]",
		(char const *) (0)
	};
	ogetoptv getopt;
	ofileopen fileopen;
	opathspec pathspec;
	oprofile config;
	omptidy object;
	omptidy & (omptidy::* method) () = &omptidy::page;
	char const * profile = MPTIDY_S_PROFILE;
	char const * section = MPTIDY_S_SECTION;
	char const * project = MPTIDY_S_PROJECT;
	char const * package = MPTIDY_S_PACKAGE;
	char const * program = MPTIDY_S_PROGRAM;
	char const * release = MPTIDY_S_RELEASE;
	signed c;
	while ((c = getopt.getoptv (argc, argv, optv)) != -1) 
	{
		switch (c) 
		{
		case 'o':
			config.write (MPTIDY_S_SECTION);
			config.write (oMPTIDY_S_PROJECT, MPTIDY_S_PROJECT);
			config.write (oMPTIDY_S_PACKAGE, MPTIDY_S_PACKAGE);
			config.write (oMPTIDY_S_PROGRAM, MPTIDY_S_PROGRAM);
			config.write (oMPTIDY_S_RELEASE, MPTIDY_S_RELEASE);
			std::cout << std::endl;
			std::exit (0);
		default:
			break;
		}
	}
	project = config.string (profile, section, oMPTIDY_S_PROJECT, project);
	package = config.string (profile, section, oMPTIDY_S_PACKAGE, package);
	program = config.string (profile, section, oMPTIDY_S_PROGRAM, program);
	release = config.string (profile, section, oMPTIDY_S_RELEASE, release);
	object.project (project);
	object.package (package);
	object.program (program);
	object.release (release);
	if (!getopt.argc ()) 
	{
		(object.*method) ();
	}
	while (getopt.argc () && * getopt.argv ()) 
	{
		char filename [FILENAME_MAX];
		pathspec.fullpath (filename, * getopt.argv ());
		if (fileopen.openedit (filename)) 
		{
//			object.filename (filename);
			(object.*method) ();
			fileopen.close ();
		}
		getopt++;
	}
	std::exit (0);
}

