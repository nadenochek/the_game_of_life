#define _BSD_SOURCE
#include <stdlib.h>		/*system clear*/
#include <unistd.h>		/*sleep*/
#include <stdio.h>		/*printf*/

#include "game.h"
#include "field.h"
#include "args.h"
#include "my_barr.h"
#include "thread.h"


typedef enum
{
	SLOW = 1000000,
    MEDIUM = 500000,
    QUICK = 100000

}SPEED;


/**
 * @brief Function for the worker thread:
  *  @details calculate and change states of the grids of the specific chunk,
 * which is given to the specific thread
 *
 * @param _ptr : pointer to the arguments
  * @return void *
 */
void* playFunc(void * _ptr);


/**
 * @brief Function for the printer thread
 *  @details Prints the field each level, after all working threads have changed it 
 *
 * @param _ptr : pointer to the arguments
  * @return void*
 */
void* printFunc(void * _ptr);


/**
 * @brief Simulates one level 
 *  @details Checks which of arrays turn is it. 
 * For each grid checks sum of its neighbors
 * Calculates and saves it's new state.
 * If there is no live cells - update isFinished 
 * After all - change arrays turn, so arrays always changes.
 *
 * @param _field : pointer to the field to play at
  * @return void
 */
static void level(Field * _pField, unsigned int _begin, unsigned int _end, unsigned int _nThreads);

/**
 * @brief Cleans up the system
 *  @details Joines and destroys threads, args, field
 *
 * @param _ppField : pointer to pointer to the Field
 * @param _ppArg : pointer to pointer to the Arg
 * @param _ppPthread : pointer to pointer to Pthread
 *
 * @return void
 */
static void cleanUp(Field ** _ppField, Arg ** _ppArg, Pthread ** _ppPthread);

/*********************************************************************/
					/*API Functions*/
/*********************************************************************/

void game(unsigned int _side, unsigned int _levels, unsigned int _threads)
{
	Field* field =  NULL;
	Pthread * pthread = NULL;
	Arg * args = NULL;
	
	field = createField(_side);	
	
	args = createArg(field, _levels, _threads, "./files");
	
	pthread = createPthread(args, playFunc, printFunc, _threads);
	
	cleanUp(&field, &args, &pthread);
}


/*********************************************************************/
					/*Help Functions*/
/*********************************************************************/

static void cleanUp(Field ** _ppField, Arg ** _ppArg, Pthread ** _ppPthread)
{
	joinPthread(*_ppPthread);
	
	destroyPthread(_ppPthread);	
	
	destroyArg(_ppArg);    
	
	destroyField(_ppField);
}

static void level(Field * _pField, unsigned int _begin, unsigned int _end, unsigned int _nThreads)

{
		unsigned int i, count = 0;
		static int order = 0;
		
		if(!_pField)
		{
			return;
		}

		for (i = _begin; i <= _end; ++i)
		{	
			count += changeGridState(_pField, i);				
		}

		order++;

		if(order % _nThreads == 0)
		{
			checkAndChangeTurn(_pField, count);
		}
}

void* playFunc(void * _ptr)
{
	int i;
	
	for(i = 0; i < getNumLevels(_ptr); ++i)
	{	
		level(getField(_ptr), getBegin(_ptr), getEnd(_ptr), getNumWorkers(_ptr));	
		
		myBarrierWait(getBarrier(_ptr));
		
		myBarrierWait(getBarrier(_ptr));
	}
	
	return NULL;
}

void* printFunc(void * _ptr)
{
	int i;
	
	for(i = 0; i < getNumLevels(_ptr); ++i)
	{
		myBarrierWait(getBarrier(_ptr));
		
		system("clear");
		
		printField(getField(_ptr));
		
		printFieldToFile(getField(_ptr), i, getFileModule(_ptr));
		
		usleep(QUICK);
		
		if(isFinished(getField(_ptr)))
		{
			exit(0);
		}
		
		myBarrierWait(getBarrier(_ptr));
	}
	return NULL;
}

