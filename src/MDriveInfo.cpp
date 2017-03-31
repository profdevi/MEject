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

//v1.5 copyright Comine.com 20170330R0709
#include "MStdLib.h"
#include "MBuffer.h"
#include "MString.h"
#include "MDriveInfo.h"


//******************************************************
//**  MDriveInfo class
//******************************************************
MDriveInfo::MDriveInfo(bool create)
	{
	if(create==true && Create()==false)
		{
		return;
		}
	}

////////////////////////////////////////////////
MDriveInfo::~MDriveInfo(void)
	{  Destroy();  }


////////////////////////////////////////////////
bool MDriveInfo::Create(void)
	{
	Destroy();
	return true;
	}


////////////////////////////////////////////////
bool MDriveInfo::Destroy(void)
	{
	return true;
	}


////////////////////////////////////////////////
bool MDriveInfo::GetDriveLetters(MString &driveletters)
	{
	if(driveletters.Create("")==false)
		{
		return false;
		}

	DWORD drives=GetLogicalDrives();
	if(drives==0)
		{
		return false;
		}

	for(char ch='A';ch<='Z';++ch)
		{
		if(drives & 1) { driveletters.Append(ch);  }
		drives=(drives>>1);
		}

	return true;
	}


////////////////////////////////////////////////
bool MDriveInfo::IsDriveLetter(char ch)
	{
	DWORD drives=GetLogicalDrives();
	if(drives==0)
		{
		return false;
		}
	
	int driveindex;  // Get Index into drive list
	if(ch>='A' && ch<='Z')
		{ driveindex=ch-'A'; }
	else if(ch>='a' && ch<='z')
		{ driveindex=ch-'a';  }
	else
		{
		return false;
		}

	if((drives & (1<<driveindex) ) > 0 ) { return true; }

	return false;
	}


////////////////////////////////////////////////
int MDriveInfo::GetDriveType(char ch)
	{
	MBuffer buffer(100);
	MStdSPrintf(buffer.GetBuffer(),buffer.GetSize()-1,"%c:\\",ch);
	UINT type=::GetDriveTypeA(buffer.GetBuffer() );
	return static_cast<int>(type);
	}


////////////////////////////////////////////////
const char *MDriveInfo::GetDriveTypeStr(char ch)
	{
	int drivetype=GetDriveType(ch);
	if(drivetype==DRIVE_UNKNOWN)
		{  return "Unknown";  }
	else if(drivetype==DRIVE_NO_ROOT_DIR)
		{  return "No Root Dir";  }
	else if(drivetype==DRIVE_REMOVABLE)
		{  return "Removable";  }
	else if(drivetype==DRIVE_FIXED)
		{  return "Fixed";  }
	else if(drivetype==DRIVE_REMOTE)
		{  return "Remote";  }
	else if(drivetype==DRIVE_CDROM)
		{  return "CDROM";  }
	else if(drivetype==DRIVE_RAMDISK)
		{  return "Ram Disk";  }

	return NULL;	
	}



