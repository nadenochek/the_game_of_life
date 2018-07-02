#include <stdlib.h>		/*rand*/

#include "bit_manipulate.h"


typedef struct Offset
{
	unsigned int m_index;
	char m_pos;
}Offset;


/**
 * @brief Calculates the offset of array of chars from the number of bit
 *
 * @param _num : the number of bit from the beginning of the array
  * @return Offset of the bit
 */
static Offset calcOffset(unsigned int _num);


/*********************************************************************/
					/*API Functions*/
/*********************************************************************/

void setBit(char * _matrix, unsigned int _num)
{
	Offset offset = calcOffset(_num);
	char mask = 1<<offset.m_pos;
	_matrix[offset.m_index] |= mask;
}


void clearBit(char * _pMatrix, unsigned int _num)
{
	Offset offset = calcOffset(_num);
	char mask = ~(1<<offset.m_pos);
	_pMatrix[offset.m_index] &= mask;
}


char ifSet (char *  _pMatrix, unsigned int _num)
{
	Offset offset = calcOffset(_num);
	char res = (_pMatrix[offset.m_index]>>offset.m_pos) & 1;
	return res;
}


void randomSetBit(char * _pMatrix, unsigned int _num)
{	
	int fortune = rand() % 2;
	
	if (fortune)
	{
		setBit(_pMatrix, _num);
	}
}

/*********************************************************************/
					/*Help Functions*/
/*********************************************************************/
static Offset calcOffset(unsigned int _num)
{
	Offset newOffset;
	
	newOffset.m_index = (_num) / NUM_OF_BITS;
	
	newOffset.m_pos = (_num) % NUM_OF_BITS;
	
	return newOffset;
}
