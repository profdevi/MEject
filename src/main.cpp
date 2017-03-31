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

//v1.1 copyright Comine.com 20170331F1106
#include "MStdLib.h"
#include "MCommandArg.h"
#include "MCDControl.h"
#include "MLicenseGPL.h"


//******************************************************
//* Module Elements
//******************************************************
static const char *GApplicationName="MEject";	// Used in Help
static const char *GApplicationVersion="1.1";	// Used in Help

////////////////////////////////////////////////////
static void GDisplayHelp(void);

////////////////////////////////////////////////////
int main(int argn,const char *argv[])
	{
	MCommandArg args(argn,argv);

	if(args.CheckRemoveArg("-gpl")==true)
		{
		MLicenseGPL lic(true);
		lic.Print();
		return 0;
		}

	if(args.CheckRemoveHelp()==true)
		{
		GDisplayHelp();
		return 0;
		}

	// Check for open or close
	bool flagopendrive=true;
	if(args.CheckRemoveArg("-c")==true || args.CheckRemoveArg("-t")==true)
		{
		flagopendrive=false;
		}

	// Check for all drives
	bool flagalldrives=false;
	if(args.CheckRemoveArg("-a")==true)
		{
		flagalldrives=true;
		}

	MCDControl cdcontrol(true);
	// Open All the drives
	if(flagalldrives==true && flagopendrive==true)
		{
		MStdPrintf("Ejecting All Drives...");
		cdcontrol.DriveEjectAll();
		MStdPrintf("Done\n");
		return 0;
		}

	// close all the drives
	if(flagalldrives==true && flagopendrive==false)
		{
		MStdPrintf("Closing All Drives...");
		cdcontrol.DriveCloseAll();
		MStdPrintf("Done\n");
		return 0;		
		}

	// Open the first drive
	if(flagopendrive==true && args.GetArgCount()==1)
		{
		MStdPrintf("Opening First Drive...");
		if(cdcontrol.DriveEject()==false)
			{
			MStdPrintf("FAILED\n");
			return 1;
			}

		MStdPrintf("Done\n");
		return 0;				
		}

	// Close the first drive
	if(flagopendrive==false && args.GetArgCount()==1)
		{
		MStdPrintf("Closing First Drive...");
		if(cdcontrol.DriveClose()==false)
			{
			MStdPrintf("FAILED\n");
			return 1;
			}

		MStdPrintf("Done\n");
		return 0;				
		}

	// Process passed drive letters
	if(flagopendrive==true)
		{
		int i;
		for(i=1;i<args.GetArgCount();++i)
			{
			char driveletter=MStdToUpper(args.GetArg(i)[0]);
			MStdPrintf("Opening Drive %c: ... ",driveletter );
			if(cdcontrol.DriveEject(driveletter)==false)
				{
				MStdPrintf("FAILED\n");
				continue;
				}

			MStdPrintf("Done\n");
			}

		return 0;
		}

	// Close passed drive list
	if(flagopendrive==true)
		{
		int i;
		for(i=1;i<args.GetArgCount();++i)
			{
			char driveletter=MStdToUpper(args.GetArg(i)[0]);
			MStdPrintf("Closing Drive %c: ... ",driveletter );
			if(cdcontrol.DriveEject(driveletter)==false)
				{
				MStdPrintf("FAILED\n");
				continue;
				}

			MStdPrintf("Done\n");
			}

		return 0;
		}
	
	return 0;
	}


////////////////////////////////////////////////////
static void GDisplayHelp(void)
	{
	MStdPrintf(	"\n"
				"   usage:  %s [-c] [-a] [<driveletter>+] [-?|-gpl]\n"
				"           v%s copyright Comine.com\n"
				"           use -gpl to display GPL license\n"
				"\n"
				"   Program ejects or closes the CD/DVD drive tray\n"
				"\n"
				"        -a      : All CD/DVD Drives \n"
				"        -c,-t   : Close the drive tray\n"
				"\n"
				,GApplicationName,GApplicationVersion);
	}


