#include <stdio.h>		/*printf*/
#include <stdlib.h>		/*malloc*/

#include "chunks.h"

struct Chunk
{
	unsigned int m_begin;
	unsigned int m_end;
};


struct Chunks
{
	unsigned int m_initialSize;
	unsigned int m_noe;
	Chunk * m_arr;
};


/** 
 * @brief Creates an array of chunks
 * @param _initial  - the number to divide
 * @param _noe  - number of chunks
 * 
 * @returns an array of chunks or NULL if failed
 */
static Chunk * createChunkArr(unsigned int _initial, unsigned int _noe);

/*********************************************************************/
					/*API Functions*/
/*********************************************************************/

Chunks * createChunks(unsigned int _initial, unsigned int _noe)
{
	Chunks * newChunks = NULL;

	if (_noe > _initial)
	{
		return NULL;
	}
	
	newChunks = malloc(sizeof(Chunks));
	if(!newChunks)
	{
		return NULL;
	}
	
	newChunks->m_initialSize = _initial;
	
	newChunks->m_noe = _noe;
	
	newChunks->m_arr = createChunkArr(_initial, _noe);
	if(!newChunks->m_arr)
	{
		free(newChunks);
		return NULL;
	}
	
	return newChunks;
}

unsigned int getChunkBegin(Chunk * _pChunk)
{
	return _pChunk->m_begin;
}


unsigned int getChunkEnd(Chunk * _pChunk)
{
	return _pChunk->m_end;
}


Chunk * getChunkByIndex(Chunks * _pChunks, unsigned int _index)
{
	if(!_pChunks)
	{
		return NULL;
	}
	
	return &_pChunks->m_arr[_index];
}


void printChunks(Chunks * _pChunks)
{
	int i;
	
	if(!_pChunks)
	{
		return;
	}
	
	for (i = 0; i < _pChunks->m_noe; ++i)
	{
		printf ("[%d - %d] ", _pChunks->m_arr[i].m_begin, _pChunks->m_arr[i].m_end);
	}
	
	printf("\n");
}


void destroyChunks(Chunks ** _ppChunks)
{
	if(!_ppChunks || !*_ppChunks)
	{
		return;
	}
	
	if((*_ppChunks)->m_arr)
		{
			free((*_ppChunks)->m_arr);
			(*_ppChunks)->m_arr = NULL;
		}
		
		free(*_ppChunks);
		*_ppChunks = NULL;
} 

/*********************************************************************/
					/*Help Functions*/
/*********************************************************************/


static Chunk * createChunkArr(unsigned int _initial, unsigned int _noe)
{
	Chunk * newArr = NULL;
	unsigned int i = 0, delta, begin = 0;
	
	newArr = malloc(sizeof(Chunk) * _noe);
	if (!newArr)
	{
		return NULL;
	}
	
	delta = _initial / _noe;
	
	for (; i < _noe - 1; ++i)
	{
		newArr[i].m_begin = begin;
		newArr[i].m_end = begin + delta - 1;
		begin += delta;
	}
	
	newArr[i].m_begin = begin;
	newArr[i].m_end = _initial - 1;
	
	return newArr;	
}



