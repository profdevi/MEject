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

//v1.4 copyright Comine.com 20170327M1009
#include <windows.h>
#include "MStdLib.h"
#include "MBuffer.h"
#include "MString.h"
#include "MProcEnvironTable.h"


//******************************************************
//**  MProcEnvironTable class
//******************************************************
void MProcEnvironTable::ClearObject(void)
	{
	}


////////////////////////////////////////////////
MProcEnvironTable::MProcEnvironTable(void)
	{  ClearObject();  }


////////////////////////////////////////////////
MProcEnvironTable::~MProcEnvironTable(void)
	{  Destroy();  }


////////////////////////////////////////////////
bool MProcEnvironTable::Create(void)
	{
	Destroy();
	return true;
	}


////////////////////////////////////////////////
bool MProcEnvironTable::Destroy(void)
	{
	ClearObject();
	return true;
	}


/////////////////////////////////////////////////
bool MProcEnvironTable::Delete(const char *variable)
	{
	if(SetEnvironmentVariableA(variable,NULL)==FALSE)
		{	
		return false;
		}

	return true;
	}


/////////////////////////////////////////////////
bool MProcEnvironTable::Set(const char *variable,const char *value)
	{
	if(SetEnvironmentVariableA(variable,value)==FALSE)
		{	
		return false;
		}
	
	return true;
	}


/////////////////////////////////////////////////
bool MProcEnvironTable::Get(const char *variable,MString &value)
	{
	MBuffer buffer;
	if(buffer.Create(1024*8)==false)
		{
		return false;
		}

	const int envlength=GetEnvironmentVariableA(variable,buffer.GetBuffer(),buffer.GetSize() );
	if(envlength==0 || envlength>=buffer.GetSize() )
		{	
		return false;
		}

	if(value.Create(buffer.GetBuffer())==false)
		{
		return false;
		}
	
	return true;
	}


/////////////////////////////////////////////////
bool MProcEnvironTable::Exists(const char *variable)
	{
	MBuffer buffer;
	if(buffer.Create(2000)==false)
		{
		return false;
		}

	if(GetEnvironmentVariableA(variable,buffer.GetBuffer(),buffer.GetSize() )==0)
		{  return false;  }

	return true;
	}


///////////////////////////////////////////////////////
bool MProcEnvironTable::Expand(const char *input,MString &output)
	{
	MBuffer tmpbuffer;
	if(tmpbuffer.Create(1024*4)==false)
		{
		return false;
		}

	DWORD ret;
	ret=ExpandEnvironmentStringsA(input,tmpbuffer.GetBuffer()
			,tmpbuffer.GetSize()-1);
	if(ret==0)
		{
		return false;
		}
	
	if(output.Create(tmpbuffer.GetBuffer() )==false)
		{
		return false;
		}

	return true;
	}


