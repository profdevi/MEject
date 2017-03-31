/*    
    MEject.exe : Ejects and closes the first CD Tray
    Copyright (C) 2017  Comine.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

//v2.3 copyright Comine.com 20170328T1307
#include "MStdLib.h"
#include "MCommandArg.h"
#include "MString.h"
#include "MStringList.h"
#include "MFileSearch.h"
#include "MLicenseGPL.h"


//******************************************************
//* Module Elements
//******************************************************
static const char *GApplicationName="MWhich";	// Used in Help
static const char *GApplicationVersion="2.3";	// Used in Help

////////////////////////////////////////////////////
static void GDisplayHelp(void);
static bool GSearchFileInEnvVar(const char *filename,const char *envar);

////////////////////////////////////////////////////
int main(int argn,const char *argv[])
	{
	MCommandArg args(argn,argv);

	///////////////////////////////////////////////
	if(args.GetArgCount()<2)
		{
		GDisplayHelp();
		return 0;
		}

	/////////////////////////////////////////////
	if(args.CheckRemoveArg("-gpl")==true)
		{
		MLicenseGPL license(true);
		license.Print();
		return 0;
		}

	MString envvar;
	if(envvar.Create("PATH")==false)
		{
		MStdPrintf("**String allocation error\n");
		return 1;
		}

	const char *tmpvar;
	int index;
	if(args.GetNameValue("-var=",tmpvar,index)==true)
		{
		if(envvar.Create(tmpvar)==false)
			{
			MStdPrintf("**String allocation error\n");
			return 1;
			}

		args.RemoveArg(index);
		}

	// If path do search current
	int i;
	for(i=1;i<args.GetArgCount();++i)
		{
		GSearchFileInEnvVar(args.GetArg(i),envvar.Get() );
		}

	return 0;
	}


//////////////////////////////////////////////////////////////////
static void GDisplayHelp(void)
	{
	MStdPrintf(	"\n"
				"  usage:  %s [-var=<ENV VARIABLE>] <FILENAME>+ [-?|-gpl]\n"
				"              v%s copyright Comine.com\n"
				"              use -gpl to display GPL license\n"
				"\n"
				"  Program will search for a filename in the environment var search path\n"
				"\n"
				"     Arguments:\n"
				"        -var : Select another environment variable for search \n"
				"\n",GApplicationName,GApplicationVersion);
	}


//////////////////////////////////////////////////////////////////
static bool GSearchFileInEnvVar(const char *filename,const char *envar)
	{
	MFileSearch filesearch;
	if(filesearch.Create()==false)
		{
		return false;
		}

	if(filesearch.AddSearchEnvVar(envar)==false )
		{
		return false;
		}

	if(MStdStrCmp(envar,"PATH")==0)
		{
		filesearch.AddSearchDir(".");
		}

	MStringList strlist;
	if(filesearch.Search(filename,strlist)==false)
		{
		return false;
		}

	strlist.ReadReset();
	const char *str;
	while((str=strlist.ReadString())!=NULL)
		{
		MStdPrintf("%s\n",str);
		}

	filesearch.Destroy();

	return true;
	}


