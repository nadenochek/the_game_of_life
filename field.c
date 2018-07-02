#include <stdio.h>		/*printf*/
#include <stdlib.h>		/*malloc, rand*/
#include <time.h>		/*time*/

#include "field.h"
#include "bit_manipulate.h"

#define NAME_SIZE 30


/*main and help arrays switch each level*/
struct Field		
{
	char * m_main;		/*main array of chars (each char has 8 bits - grids)*/
	char * m_help;		/*help array of chars (each char has 8 bits - grids)*/
	unsigned int m_side;	/*side of the field in bytes*/
	int m_turn;		/*0 - main, 1 - help*/
	int m_isFinished;	/*0 if not finished*/
	unsigned int m_size;	/*size of field in chars*/
};


/**
 * @brief Creates array of chars
 *
 * @param _size : size of array in chars
 * @return char * or NULL if allocated failed
 */
static char* createMatrix(int _size);


/**
 * @brief Randomly sets bits on a new matrix
 *
 * @param _matrix : matrix to change
 * @param _side : side of the field in bits
 * @return void
 */
static void randomMatrix(char * _matrix, unsigned int _side);


/**
 * @brief checks the new state of cell by the rules of the game of life
 *  @details If live cell has less than two neighbores - it dies due to under population
 * If live cell has more than three neighbores - it dies due to over population
 * If live cell has two or three neighbors - it lives to next generation
 * If dead cell has three neighbors - it became live
 *
 * @param _state : the current state of cell
  * @param _sum : the sum of neighbors
  * @return void
 */
static char checkState(char _state, char _sum);


/**
 * @brief Check is grid is on the edge
 *
 * @param _side : side of the field in bits
 * @param _num : the number of the grid
 * @return 1 if yes, 0 if  no
 */
static char isOnEdge(unsigned int _side, unsigned int _num);


/**
 * @brief Returns the sum of the neighbors grids
 *
 * @param _matrix : matrix to change
 * @param _side : side of the field in bits
 * @param _num : the number of the grid
 * @return the sum of the neighbors grids
 */
static char sumOfNeighborsByNumOfBits(char * _matrix, unsigned int _side, unsigned int _num);


/*********************************************************************/
					/*API Functions*/
/*********************************************************************/

Field* createField(unsigned int _side)
{
	Field * newField = NULL;
	
	srand(time(NULL));	/*random seed - happens only once, when field is created*/
	
	if(!_side)
	{
		return NULL;
	}
	newField = malloc(sizeof(Field));
	
	if (!newField)
	{
		return NULL;
	}
	
	newField->m_side = _side;
	
	newField->m_turn = 0;	/*main*/
	
	newField->m_isFinished = 0;	/*false*/
	
	newField->m_size = (_side * _side) % NUM_OF_BITS == 0 ? (_side * _side) / NUM_OF_BITS : (_side * _side) / NUM_OF_BITS + 1;
	
	newField->m_help = createMatrix(newField->m_size);
	if(!newField->m_help)
	{
		free(newField);
		
		return NULL;
	}
	
	newField->m_main = createMatrix(newField->m_size);
	if (!newField->m_main)
	{
		free(newField->m_help);	
		
		free(newField);
		
		return NULL;
	}	
	
	randomMatrix(newField->m_main, _side);
	
	return newField;
}


unsigned int getSide(Field * _pField)
{
	return _pField->m_side;
}


int isFinished(Field * _pField)
{
	return _pField->m_isFinished;
}


void checkAndChangeTurn(Field * _pField, unsigned int _numLiveGrids)
{
			if(!_numLiveGrids)						
			{
				_pField->m_isFinished = 1;
			}
		
			_pField->m_turn ^= 1;
}


int changeGridState(Field * _pField, unsigned int _numOfBit)
{
	char state, sum;
	int count = 0;
	char * first, *second;
	
	first =  _pField->m_turn ? _pField->m_help : _pField->m_main;
	
	second =  _pField->m_turn ? _pField->m_main : _pField->m_help;	
	
	if (isOnEdge(_pField->m_side, _numOfBit))
	{
		return count;
	}
	
	state = ifSet(first, _numOfBit);				
	
	sum = sumOfNeighborsByNumOfBits(first, _pField->m_side, _numOfBit);
	
	if (checkState(state, sum))
	{
		count++;
		
		setBit(second, _numOfBit);
	}
				
	else
	{
		clearBit(second, _numOfBit);
	}

	return count;
}


void printField(Field* _pField)		
{
	int i, j;
	char * matrix;
		
	if(!_pField)
	{
		return;
	}
	matrix = _pField->m_turn ? _pField->m_help : _pField->m_main;
	
	for(i = 0; i < _pField->m_side; ++i)
	{
		for(j = 0; j < _pField->m_side; ++j)
		{
			if (ifSet(matrix, (i * _pField->m_side + j)))
			{
				printf("0");
			}
				
			else
			{
				printf(" ");
			}		
		}	
		printf("\n");
	}		
}


void printFieldToFile(Field* _pField, unsigned int _frame, FilesModule * _pFilesModule)	
{
	int i, j;
	char * matrix;
	FILE *fptr;
	
	if(!_pField || !_pFilesModule)
	{
		return;
	}
	
	fptr = openFile(_pFilesModule, _frame);
		if(!_pField)
		{
			return;
		}
		
		matrix = _pField->m_turn ? _pField->m_help : _pField->m_main;
		
		for(i = 0; i < _pField->m_side; ++i)
		{
			for(j = 0; j < _pField->m_side; ++j)
			{
				if (ifSet(matrix, (i*_pField->m_side + j)))
				{
				
					fprintf(fptr, "0");
				}				
				else
				{
				
					fprintf(fptr, " ");
				}				
			}
			
			fprintf(fptr, "\n");
		}	
		
		closeFile(fptr);		    	
}


void destroyField(Field** _ppField)
{
	if(!_ppField || !*_ppField)
	{
		return;
	}
	if((*_ppField)->m_main)
	{
		free((*_ppField)->m_main);
		
		(*_ppField)->m_main = NULL;
	}
	
	if((*_ppField)->m_help)
	{
		free((*_ppField)->m_help);
		
		(*_ppField)->m_help = NULL;
	}
	free(*_ppField);
	
	*_ppField = NULL;
}


/*********************************************************************/
					/*Help Functions*/
/*********************************************************************/

static char isOnEdge(unsigned int _side, unsigned int _num)
{
	if (0 == _num / _side || _side - 1 == _num / _side 
	|| 0 == _num % _side || _side - 1 == _num % _side)
	{
		return 1;
	}
	
	return 0;
}


static char sumOfNeighborsByNumOfBits(char * _matrix, unsigned int _side, unsigned int _num)
{
	char sum = 0;
	
	unsigned int col = _num/_side;
	
	unsigned int row = _num % _side;
	
	sum = ifSet(_matrix, ((col - 1) * _side + row - 1)) + ifSet(_matrix, ((col - 1) *_side + row)) + ifSet(_matrix, ((col - 1) * _side + row + 1)) 
							  + ifSet(_matrix, (col * _side + row - 1)) + ifSet(_matrix, (col * _side + row + 1)) 
							  + ifSet(_matrix, ((col + 1) * _side + row - 1)) + ifSet(_matrix, ((col + 1) * _side + row)) 
							  + ifSet(_matrix, ((col + 1) * _side + row + 1));
	return sum;
}


static char checkState(char _state, char _sum)
{
	if (3 == _sum || (2 == _sum && _state))
	{
		return 1;
	}
	
	return 0;
}


static char* createMatrix(int _size)
{
	if (_size)
	{
		char * matrix = (char*)malloc(_size);
		if(matrix)
		{
			return matrix;
		}
	}
	
	return NULL;
}
 

static void randomMatrix(char * _matrix, unsigned int _side)
{
	int i, j;

	for (i = 1; i < _side - 1; ++i)
	{
		for (j = 1; j < _side - 1; ++j)
		{
			randomSetBit(_matrix, (i*_side + j));
		}
	}		
}
