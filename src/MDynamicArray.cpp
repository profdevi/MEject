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
#include "MStdLib.h"
#include "MDynamicArray.h"


/////////////////////////////////////////////
void MDynamicArray::ClearObject(void)
	{
	mItemSize=0;
	mItemArray=NULL;
	mItemCount=0;
	mDataBlockSize=0;
	mMaxItemCount=0;
	}


////////////////////////////////////////////
int MDynamicArray::GetBlockCountToHoldItems(int items)
	{
	return (items*mItemSize+mDataBlockSize-1)/mDataBlockSize;
	}


////////////////////////////////////////////////////////////////
int MDynamicArray::GetItemCountInBlocks(int blockcount) //=max # of items in blocks
	{
	return (blockcount*mDataBlockSize)/mItemSize;
	}


/////////////////////////////////////////////////////////////////
MDynamicArray::MDynamicArray(void)
	{	ClearObject();  }


/////////////////////////////////////////////////////////////////
MDynamicArray::MDynamicArray(int itemsize,int initialcapacity,int datablocksize)
	{
	ClearObject();
	if(Create(itemsize,initialcapacity,datablocksize)==false)
		{
		return;
		}
	}


/////////////////////////////////////////////////////////////////
MDynamicArray::~MDynamicArray(void)
	{  Destroy();  }


/////////////////////////////////////////////////////////////////
bool MDynamicArray::Create(int itemsize,int initialcapacity,int datablocksize)
	{
	Destroy();
	if((mItemSize=itemsize)<=0 || itemsize>datablocksize 
			|| datablocksize<=0 || initialcapacity<0 )
		{
		return false;
		}
	
	mItemArray=NULL; mItemCount=0; mItemSize=itemsize;
	mDataBlockSize=datablocksize;  mMaxItemCount=0;

	if(Resize(initialcapacity)==false)
		{
		return false;
		}

	return true;
	}


//////////////////////////////////////////////////////////////////
bool MDynamicArray::Destroy(void)
	{
	if(Resize(0)==false)
		{
		}

	ClearObject();  return true;
	}


/////////////////////////////////////////////////////////////////
bool MDynamicArray::Insert(void *item) // Insert at End of list
	{
	if(mItemCount>=mMaxItemCount)
		{
		if(Resize(mMaxItemCount+1)==false)
			{
			return false;
			}
		}

	MStdMemCpy(mItemArray+mItemCount*mItemSize,item,mItemSize);
	mItemCount += 1;
	return true;
	}


/////////////////////////////////////////////////////////////////
bool MDynamicArray::Insert(int index,void *item)
	{

	if(index<0 || index>mItemCount)
		{
		return false;
		}

	if(mItemCount>=mMaxItemCount)
		{
		if(Resize(mMaxItemCount+1)==false)
			{
			return false;
			}
		}

	MStdMemMove(mItemArray+(index+1)*mItemSize
			,mItemArray+index*mItemSize,(mItemCount-index)*mItemSize);

	MStdMemCpy(mItemArray+index*mItemSize,item,mItemSize);
	mItemCount += 1;
	return true;
	}


/////////////////////////////////////////////////////////////////
bool MDynamicArray::Remove(int index)
	{
	if(index<0 || index>=mItemCount)
		{
		return false;
		}

	MStdMemMove(mItemArray+index*mItemSize
		,mItemArray+(index+1)*mItemSize,(mItemCount-index)*mItemSize);

	mItemCount -=1;
	return true;
	}


/////////////////////////////////////////////////////////////////
void *MDynamicArray::Get(int index) // Return memory address of object
	{
	if(index<0 || index>=mItemCount)
		{
		return NULL;
		}

	return mItemArray+index*mItemSize;
	}


/////////////////////////////////////////////////////////////////
bool MDynamicArray::Set(int index,void *item)
	{

	if(index<0 || index>=mItemCount)
		{
		return false;
		}

	MStdMemCpy(mItemArray+index*mItemSize,item,mItemSize);
	return true;
	}


//////////////////////////////////////////////////////////////////
int MDynamicArray::GetCount(void)
	{  return mItemCount;  }


/////////////////////////////////////////////////////////////////
int MDynamicArray::GetMaxCapacity(void)
	{
	return mMaxItemCount;
	}


/////////////////////////////////////////////////////////////////
bool MDynamicArray::Clear(void) // reset set the total count of items
	{
	if(mItemArray!=NULL)
		{
		MStdMemSet(mItemArray,0,mItemSize*mMaxItemCount);
		}
	
	mItemCount=0;
	return true;
	}


/////////////////////////////////////////////////////////////////
bool MDynamicArray::Resize(int maxitems)	// Reset to maxitems. If Smaller, memory is released
	{
	if(maxitems<0)
		{
		return false;
		}

	if(maxitems==0)  // Resize to zero blocks
		{
		if(mItemArray!=NULL)
			{
			delete[] mItemArray;
			mItemArray=NULL;
			}

		mItemCount=0;
		mMaxItemCount=0;
		return true;
		}

	// Get a new block of data
	int newblockcount=GetBlockCountToHoldItems(maxitems);
	char *newblock=new char[newblockcount*mDataBlockSize];
	if(newblock==NULL)
		{
		return false;
		}

	//zeros out the memory block
	MStdMemSet(newblock,0,newblockcount*mDataBlockSize);

	if(mItemArray==NULL) // No Data Yet
		{
		mItemArray=newblock;  mItemCount=0;
		mMaxItemCount=(newblockcount*mDataBlockSize)/mItemSize;
		return true;
		}

	int newitems=maxitems;
	if(mItemCount<maxitems) { newitems=mItemCount; }
	MStdMemCpy(newblock,mItemArray,newitems*mItemSize);

	delete[] mItemArray;

	mItemArray=newblock;
	mItemCount=newitems;
	mMaxItemCount=(newblockcount*mDataBlockSize)/mItemSize;

	return true;
	}


//////////////////////////////////////////////////////////////////
int MDynamicArray::GetItemSize(void)
	{
	return mItemSize;
	}



