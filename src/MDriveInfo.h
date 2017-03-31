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
#ifndef MDriveInfo_h
#define MDriveInfo_h

#include <windows.h>
#include "MString.h"

//******************************************************
//**  MDriveInfo class
//******************************************************
class MDriveInfo
	{
	////////////////////////////////////////////////
	public:
	MDriveInfo(bool create=false);
	~MDriveInfo(void);
	bool Create(void);
	bool Destroy(void);
	bool IsInitialized(void);
	bool IsValid(void);
	bool GetDriveLetters(MString &driveletters);
	bool IsDriveLetter(char ch);
	int GetDriveType(char ch);	//=DRIVE_UNKNOWN,DRIVE_NO_ROOT_DIR
								//=DRIVE_REMOVABLE,DRIVE_FIXED
								//=DRIVE_REMOTE,DRIVE_CDROM,DRIVE_RAMDISK
	const char *GetDriveTypeStr(char ch);	// Display string of drive
	};

#endif // MDriveInfo_h

