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
#ifndef MDynamicString_h
#define MDynamicString_h

////////////////////////////////////////////////
#include "MDynamicArray.h"

///////////////////////////////////////////////
class MDynamicString
	{
	MDynamicArray mString;
	
	///////////////////////////////////////////////
	void ClearObject(void);

	///////////////////////////////////////////////
	public:
	MDynamicString(void);
	MDynamicString(const char *string,int blocksize=32);
	~MDynamicString(void);
	bool Create(int blocksize=32);
	bool Create(const char *string,int blocksize=32);
	bool Destroy(void);
	const char *Get(void);
	char Get(int index);
	bool Set(int index,char ch);
	bool Set(const char *string);
	bool Remove(int index);
	bool Insert(int index,char ch);
	bool Insert(char ch);
	bool Clear(void);
	int GetLength(void);
	bool Append(const char *str);
	bool TrimLeft(void);
	bool TrimRight(void);
	bool Trim(void);
	bool IsBlank(void);
	};

#endif // MDynamicString_h

