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
#include "MStdLib.h"
#include "MString.h"
#include "MStringList.h"
#include "MFileOps.h"
#include "MPathParser.h"
#include "MDynamicString.h"
#include "MProcEnvironTable.h"
#include "MFileSearch.h"



//******************************************************
//**  MFileSearch class
//******************************************************
void MFileSearch::ClearObject(void)
	{
	}


////////////////////////////////////////////////
MFileSearch::MFileSearch(bool create)
	{
	ClearObject();
	if(create==true && Create()==false)
		{
		return;
		}
	}


////////////////////////////////////////////////
MFileSearch::~MFileSearch(void)
	{  Destroy();  }


////////////////////////////////////////////////
bool MFileSearch::Create(void)
	{
	Destroy();

	if(mDirList.Create()==false)
		{
		return false;
		}

	return true;
	}


////////////////////////////////////////////////
bool MFileSearch::Destroy(void)
	{
	mDirList.Destroy();
	ClearObject();
	return true;
	}


////////////////////////////////////////////////
bool MFileSearch::AddSearchDir(const char *directory)
	{
	if(mDirList.AddString(directory)==false)
		{
		return false;
		}

	return true;
	}


////////////////////////////////////////////////
bool MFileSearch::AddSearchEnvVar(const char *envvariable)	// Search Environment table
	{
	// Set Default to PATH envariable if NULL
	if(envvariable==NULL)
		{
		return false;
		}

	MProcEnvironTable envtable;
	if(envtable.Create()==false)
		{
		return false;
		}

	// Search for path variable
	MString pathinfo;
	if(envtable.Get(envvariable,pathinfo)==false)
		{
		return false;
		}

	// Unable to get path info
	const char *path=pathinfo.Get();
	MDynamicString string;
	if(string.Create(1024)==false)
		{
		return false;
		}

	for(int i=0; ;++i)
		{
		if(path[i]==0)
			{
			if(string.GetLength()!=0)
				{  return mDirList.AddString(string.Get());  }

			return true;
			}

		if(path[i]==';')
			{
			if(string.GetLength()!=0)
				{
				if(mDirList.AddString(string.Get())==false) { return false; }
				}
			string.Clear(); continue;
			}

		string.Insert(path[i]);
		}
	}


/////////////////////////////////////////////////
bool MFileSearch::Search(const char *file,MString &fullpath)
	{
	mDirList.ReadReset();

	const char *seachdir;  MFileOps fileops(true);
	while((seachdir=mDirList.ReadString())!=NULL)
		{
		MPathParser testpath(true);
		if(testpath.SetDir(seachdir)==false)
			{
			return false;
			}

		if(testpath.SetFullFileName(file)==false)
			{
			return false;
			}

		if(fileops.Exists(testpath.GetPath())==false) { continue; }

		//=We have found the file
		if(fullpath.Create(testpath.GetPath())==false)
			{
			return false;
			}
		
		return true;
		}

	return false;	
	}


/////////////////////////////////////////////////////
bool MFileSearch::Search(const char *file,MStringList &pathlist)
	{
	mDirList.ReadReset();

	// init path list
	if(pathlist.Create()==false)
		{
		return false;
		}

	const char *seachdir;  MFileOps fileops(true);
	bool retvalue=false;
	while((seachdir=mDirList.ReadString())!=NULL)
		{
		MPathParser testpath(true);
		if(testpath.SetDir(seachdir)==false)
			{
			return false;
			}

		if(testpath.SetFullFileName(file)==false)
			{
			return false;
			}

		if(fileops.Exists(testpath.GetPath())==false) { continue; }

		//=We have found the file

		if(pathlist.AddString(testpath.GetPath())==false)
			{
			return false;
			}

		retvalue=true;
		}

	return retvalue;
	}


