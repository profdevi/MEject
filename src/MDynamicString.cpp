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

//v1.9 copyright Comine.com 20150813R1125
#include "MStdLib.h"
#include "MDynamicArray.h"
#include "MDynamicString.h"


//******************************************************
//** MDynamicString Code
//******************************************************
///////////////////////////////////////////////////////
void MDynamicString::ClearObject(void)
	{
	}


///////////////////////////////////////////////////////
MDynamicString::MDynamicString(void)
	{  ClearObject();  }


//////////////////////////////////////////////////////
MDynamicString::MDynamicString(const char *string,int blocksize)
	{
	ClearObject();
	if(Create(string,blocksize)==false)
		{
		return;
		}
	}

///////////////////////////////////////////////////////
MDynamicString::~MDynamicString(void)
	{  Destroy();  }


///////////////////////////////////////////////////////
bool MDynamicString::Create(int blocksize)
	{
	Destroy();
	if(mString.Create(1,1,blocksize)==false)
		{
		return false;
		}

	char ch=0;
	if(mString.Insert(&ch)==false)
		{
		mString.Destroy(); return false;
		}

	return true;
	}


////////////////////////////////////////////////////////
bool MDynamicString::Create(const char *string,int blocksize)
	{
	Destroy();

	if(blocksize<=0)
		{
		Destroy(); return false;
		}
	
	int len=MStdStrLen(string);
	if(mString.Create(1,len+1,blocksize)==false)
		{
		Destroy();  return false;
		}

	for(const char *p=string;*p!=0;++p)
		{  mString.Insert((void *)p);  }

	char endchar=0;
	if(mString.Insert(&endchar)==false)
		{
		Destroy();  return false;
		}

	return true;
	}

///////////////////////////////////////////////////////
bool MDynamicString::Destroy(void)
	{
	mString.Destroy();
	ClearObject();
	return true;
	}


///////////////////////////////////////////////////////
const char *MDynamicString::Get(void)
	{
	return (const char *)mString.Get(0);
	}


///////////////////////////////////////////////////////
char MDynamicString::Get(int index)
	{
	int count=mString.GetCount();
	if(index<0 || index>=count)
		{
		return 0;
		}

	return *(char *)mString.Get(index);
	}


///////////////////////////////////////////////////////
bool MDynamicString::Set(int index,char ch)
	{
	int count=mString.GetCount();
	if(count==0)
		{
		return false;
		}
	
	if(index<0 || index>=count)
		{
		return 0;
		}

	if(index==count-1)
		{
		if(mString.Insert(index,&ch)==false)
			{
			return false;
			}
		return true;
		}

	*(char *)mString.Get(index) = ch;
	return false;
	}


///////////////////////////////////////////////////////
bool MDynamicString::Set(const char *string)
	{
	mString.Clear();

	bool bflag=true;
	for(const char *p=string;*p!=0;++p)
		{
		if(mString.Insert((void*)p)==false) { bflag=false; }
		}
	char endchar=0;
	if(mString.Insert(&endchar)==false) { bflag=false; }

	if(bflag==false)
		{
		return false;
		}

	return true;
	}


///////////////////////////////////////////////////////
bool MDynamicString::Remove(int index)
	{
	int count=mString.GetCount();
	if(index<0 || index>=count-1)
		{
		return false;
		}
	
	if(mString.Remove(index)==false)
		{
		return false;
		}

	return true;
	}


///////////////////////////////////////////////////////
bool MDynamicString::Insert(int index,char ch)
	{

	int count=mString.GetCount();
	if(index<0 || index>=count)
		{
		return false;
		}

	if(mString.Insert(index,&ch)==false)
		{
		return false;  
		}

	return true;
	}


///////////////////////////////////////////////////////
bool MDynamicString::Insert(char ch)
	{
	int count=mString.GetCount();
	if(mString.Insert(count-1,&ch)==false)
		{
		return false;
		}

	return true;
	}


///////////////////////////////////////////////////////
bool MDynamicString::Clear(void)
	{
	mString.Clear();
	char endchar=0;
	if(mString.Insert(&endchar)==false)
		{
		return false;
		}

	return true;
	}


///////////////////////////////////////////////////////
int MDynamicString::GetLength(void)
	{
	return mString.GetCount()-1;
	}


///////////////////////////////////////////////////////
bool MDynamicString::Append(const char *str)
	{
	for(int i=0;str[i]!=0;++i)
		{
		if(Insert(str[i])==false)
			{
			return false;
			}
		}
	return true;
	}


////////////////////////////////////////////////////
bool MDynamicString::TrimRight(void)
	{
	for(int i=GetLength()-1;i>=0;--i)
		{
		char ch=Get(i);
		if(ch==' ' || ch=='\t' || ch=='\r' || ch=='\n')
			{  Remove(i);  continue; }
		break;
		}

	return true;
	}


////////////////////////////////////////////////////
bool MDynamicString::TrimLeft(void)
	{
	for(;;)
		{	char ch=Get(0);
		if(ch==' ' || ch=='\t' || ch=='\r' || ch=='\n')
			{  Remove(0);  continue; }

		break;
		}
	return true;
	}


//////////////////////////////////////////////////////
bool MDynamicString::Trim(void)
	{
	for(int i=GetLength()-1;i>=0;--i)
		{
		char ch=Get(i);
		if(ch==' ' || ch=='\t' || ch=='\r' || ch=='\n')
			{  Remove(i);  continue; }
		}

	return true;
	}


//////////////////////////////////////////////////////////////
bool MDynamicString::IsBlank(void)
	{
	for(int i=0;i<GetLength();++i)
		{
		char ch=Get(i);
		if(ch==' ' || ch=='\t' || ch=='\r' || ch=='\n') { continue; }
		return false;
		}
	return true;
	}



