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

//v1.11 copyright Comine.com 20130813R1128
#ifndef MDynamicArray_h
#define MDynamicArray_h

/////////////////////////////////////////////////////////
class MDynamicArray
	{
	int mItemSize;	char *mItemArray;  int mItemCount; 
	int mDataBlockSize; int mMaxItemCount;

	/////////////////////////////////////////////////////
	void ClearObject(void);
	int GetBlockCountToHoldItems(int itemcount);	//=total blocks to hold itemcount
	int GetItemCountInBlocks(int blockcount);		//=max # of items in blocks

	/////////////////////////////////////////////////////
	public:
	MDynamicArray(void);
	MDynamicArray(int itemsize,int initialcapacity=1,int datablocksize=512);
	~MDynamicArray(void);
	bool Create(int itemsize,int initialcapacity=1,int datablocksize=512);
	bool Destroy(void);
	bool Insert(void *item);					// Insert at End of list
	bool Insert(int index,void *item);			// Insert at position
	bool Remove(int index);						// Remove at index
	void *Get(int index);						// Return memory address of object
	bool Set(int index,void *item);				// Set an item
	int GetCount(void);
	int GetMaxCapacity(void);
	bool Clear(void);							// reset set the total count of items
	bool Resize(int maxitems);					// Reset to maxitems. If Smaller, memory is released
	int GetItemSize(void);						// Return Item Count
	};


#endif // MDynamicArray_h

