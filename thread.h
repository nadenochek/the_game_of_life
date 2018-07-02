#ifndef __THREAD_H__
#define __THREAD_H__

#include "args.h"		/*Arg**/

/** 
 *  @file thread.h
 *  @brief Threads module
 *	
 *  @details This module creates, joines and destroys threads for the game of life 
 *  @author Nadya Gneduke  (nadenok01@gmail.com)
 * 
 *  @bug No known bugs.
 */

typedef struct Pthread Pthread;

typedef void*(*func)(void*);


/** 
 * @brief Creates all the threads and activates them
 * @param _pArg  - pointer to Arg (arguments module)
 * @param _workFunc  - pointer to workers' function
 * @param _printFunc  - pointer to printer's function
 * @param _nWorkers  - number of working threads
 * 
 * @returns a pointer to the new Pthread or NULL if creation failed
 */
Pthread * createPthread (Arg * _pArg, func _workFunc, func _printFunc, unsigned int _nWorkers);		


/** 
 * @brief Joines all threads
 * @param _pPthread  - pointer to pthread
 * 
 * @returns void
 */
void joinPthread (Pthread * _pPthread);


/** 
 * @brief Destroys pthread
 * @param _ppPthread  - pointer to pointer to pthread
 * 
 * @returns void 
 */
void destroyPthread (Pthread ** _ppPthread);

#endif /*__THREAD_H__*/
