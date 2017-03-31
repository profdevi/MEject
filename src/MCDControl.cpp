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
#include <windows.h>
#include <Mmsystem.h>
#include "MStdLib.h"
#include "MString.h"
#include "MDriveInfo.h"
#include "MCDControl.h"


////////////////////////////////////////////////
// Reference http://www.codeproject.com/KB/system/eject_cdrom.aspx


////////////////////////////////////////////////
#pragma comment(lib,"Winmm.lib")

//******************************************************
//**  MCDControl class
//******************************************************
void MCDControl::ClearObject(void)
	{
	}


////////////////////////////////////////////////
MCDControl::MCDControl(bool create)
	{
	ClearObject();
	if(create==true && Create()==false )
		{
		return;
		}
	}


////////////////////////////////////////////////
MCDControl::~MCDControl(void)
	{  Destroy();  }


////////////////////////////////////////////////
bool MCDControl::Create(void)
	{
	Destroy();
	return true;
	}


////////////////////////////////////////////////
bool MCDControl::Destroy(void)
	{
	ClearObject();
	return true;
	}


///////////////////////////////////////////////
bool MCDControl::DriveEject(char deviceletter)
	{
	MCI_OPEN_PARMSA openparams;
	MStdMemZero(&openparams,sizeof(openparams) );

	// Build up drive path
	char elementname[100];
	MStdSPrintf(elementname,sizeof(elementname)-1,"%c",deviceletter);

	
	openparams.lpstrDeviceType = (LPCSTR)MCI_DEVTYPE_CD_AUDIO;
	openparams.lpstrElementName=elementname;
	
	// Open Handle to device
	MCIERROR error;
	error=mciSendCommandA(0,MCI_OPEN
			,MCI_OPEN_TYPE|MCI_OPEN_TYPE_ID|MCI_OPEN_ELEMENT|MCI_OPEN_SHAREABLE
			,(DWORD)&openparams);
	if(error!=0)
		{
		return false;
		}

	// Send Eject Command
	error=mciSendCommandA(openparams.wDeviceID,MCI_SET,MCI_SET_DOOR_OPEN,0);
	if(error!=0)
		{
		// Close Device Handle
		mciSendCommandA(openparams.wDeviceID, MCI_CLOSE, MCI_WAIT, 0);
		return false;
		}

	// Close Device Handle
	error=mciSendCommand(openparams.wDeviceID, MCI_CLOSE, MCI_WAIT, 0);
	return true;
	}


///////////////////////////////////////////////
bool MCDControl::DriveClose(char deviceletter)
	{
	MCI_OPEN_PARMSA openparams;
	MStdMemZero(&openparams,sizeof(openparams) );

	// Build up drive path
	char elementname[100];
	MStdSPrintf(elementname,sizeof(elementname)-1,"%c",deviceletter);

	
	openparams.lpstrDeviceType = (LPCSTR)MCI_DEVTYPE_CD_AUDIO;
	openparams.lpstrElementName=elementname;
	
	// Open Handle to device
	MCIERROR error;
	error=mciSendCommandA(0,MCI_OPEN
			,MCI_OPEN_TYPE|MCI_OPEN_TYPE_ID|MCI_OPEN_ELEMENT|MCI_OPEN_SHAREABLE
			,(DWORD)&openparams);
	if(error!=0)
		{
		return false;
		}

	// Send CLOSE Command
	error=mciSendCommandA(openparams.wDeviceID,MCI_SET,MCI_SET_DOOR_CLOSED,0);
	if(error!=0)
		{
		// Close Device Handle
		mciSendCommandA(openparams.wDeviceID, MCI_CLOSE, MCI_WAIT, 0);
		return false;
		}

	// Close Device Handle
	error=mciSendCommand(openparams.wDeviceID, MCI_CLOSE, MCI_WAIT, 0);
	return true;
	}


/////////////////////////////////////////////////////////
bool MCDControl::DriveEject(void)
	{
	MDriveInfo driveinfo(true);
	
	MString driveletters;
	if(driveinfo.GetDriveLetters(driveletters)==false)
		{
		return false;
		}

	int i;
	for(i=0;driveletters[i]!=0;++i)
		{
		int drivetype=driveinfo.GetDriveType(driveletters[i]);
		if(drivetype!=DRIVE_CDROM)
			{
			continue;
			}

		if(DriveEject(driveletters[i])==false)
			{
			return false;
			}

		return true;
		}
	
	return true;
	}


/////////////////////////////////////////////////////////
bool MCDControl::DriveClose(void)
	{
	MDriveInfo driveinfo(true);
	
	MString driveletters;
	if(driveinfo.GetDriveLetters(driveletters)==false)
		{
		return false;
		}

	int i;
	for(i=0;driveletters[i]!=0;++i)
		{
		int drivetype=driveinfo.GetDriveType(driveletters[i]);
		if(drivetype!=DRIVE_CDROM)
			{
			continue;
			}

		if(DriveClose(driveletters[i])==false)
			{
			return false;
			}

		return true;
		}
	
	return true;
	}


/////////////////////////////////////////////////////////
bool MCDControl::DriveEjectAll(void)
	{
	MDriveInfo driveinfo(true);
	
	MString driveletters;
	if(driveinfo.GetDriveLetters(driveletters)==false)
		{
		return false;
		}

	int i;
	for(i=0;driveletters[i]!=0;++i)
		{
		int drivetype=driveinfo.GetDriveType(driveletters[i]);
		if(drivetype!=DRIVE_CDROM)
			{
			continue;
			}

		if(DriveEject(driveletters[i])==false)
			{
			// Continue anyway
			continue;
			}
		}
	
	return true;
	}


/////////////////////////////////////////////////////////
bool MCDControl::DriveCloseAll(void)
	{
	MDriveInfo driveinfo(true);
	
	MString driveletters;
	if(driveinfo.GetDriveLetters(driveletters)==false)
		{
		return false;
		}

	int i;
	for(i=0;driveletters[i]!=0;++i)
		{
		int drivetype=driveinfo.GetDriveType(driveletters[i]);
		if(drivetype!=DRIVE_CDROM)
			{
			continue;
			}

		if(DriveClose(driveletters[i])==false)
			{
			// Continue anyway
			continue;
			}
		}
	
	return true;
	}


