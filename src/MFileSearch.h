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

//v1.4 copyright Comine.com 20170327M1019
#ifndef MFileSearch_h
#define MFileSearch_h

///////////////////////////////////////////
#include "MStringList.h"
#include "MString.h"

//******************************************************
//**  MFileSearch class
//******************************************************
class MFileSearch
	{
	////////////////////////////////////////////////
	MStringList mDirList;
	
	////////////////////////////////////////////////
	void ClearObject(void);
	
	////////////////////////////////////////////////
	public:
	MFileSearch(bool create=false);
	~MFileSearch(void);
	bool Create(void);
	bool Destroy(void);
	bool AddSearchDir(const char *directory);				// Add Search directory
	bool AddSearchEnvVar(const char *directory="PATH");		// Search Environment table
	bool Search(const char *file,MString &fullpath);
	bool Search(const char *file,MStringList &pathlist);
	};

#endif // MFileSearch_h

