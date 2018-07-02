#ifndef __ARGS_H__
#define __ARGS_H__
#include "my_barr.h"
#include "field.h"

/** 
 *  @file args.h
 *  @brief Creates arguments for threads 
 *	
 *  @details This module creates arguments for threads, it knows how to pack and unpack needed arguments
 *  @author Nadya Gneduke  (nadenok01@gmail.com)
 * 
 *  @bug No known bugs.
 */

typedef struct Printer_Arg Printer_Arg;
typedef struct Workers_Arg Workers_Arg;
typedef struct Arg Arg;

/** 
 * @brief Creates arguments
 * @param _pField  - pointer to Field
 * @param _levels  - number of levels
 * @param _nWorkers  - number of working threads
 * @param _dirName  - name of the directory, where to put files
 * 
 * @returns a pointer to the new Arg or NULL if creation failed
 */
Arg * createArg (Field * _pField, unsigned int _levels, unsigned int _nWorkers, char * _dirName); 


/** 
 * @brief Returns number of levels
 * @param _pArg  - pointer to Arg (arguments module)
 * 
 * @returns number of levels
 */
unsigned int getNumLevels(void * _pArg);


/** 
 * @brief Returns the number of workers
 * @param _pArg  - pointer to Arg (arguments module)
 * 
 * @returns the number of workers
 */
unsigned int getNumWorkers(void * _pArg);


/** 
 * @brief Returns the begin of the chunk
 * @param _pArg  - pointer to Arg (arguments module)
 * 
 * @returns the begin of the chunk
 */
unsigned int getBegin(void * _pArg);


/** 
 * @brief Returns the end of the chunk
 * @param _pArg  - pointer to Arg (arguments module)
 * 
 * @returns the end of the chunk
 */
unsigned int getEnd(void * _pArg);


/** 
 * @brief returns barrier
 * @param _pArg  - pointer to Arg (arguments module)
 * 
 * @returns returns pointer to  MyBarrier
 */
MyBarrier * getBarrier(void * _pArg);


/** 
 * @brief Returns Field
 * @param _pArg  - pointer to Arg (arguments module)
 * 
 * @returns Returns pointer to Field
 */
Field * getField(void * _pArg);


/** 
 * @brief Returns pointer to Printer_Arg
 * @param _pArg  - pointer to Arg (arguments module)
 * 
 * @returns a pointer to Printer_Arg 
 */
Printer_Arg * getPrinterArg(Arg * _pArg);


/** 
 * @brief Returns pointer to Workers_Arg
 * @param _pArg  - pointer to Arg (arguments module)
 * @param _index  - index of Workers_Arg
 * 
 * @returns a pointer to Workers_Arg
 */
Workers_Arg*  getWorkersArgByIndex(Arg * _pArg, unsigned int _index);


/** 
 * @brief Returns pointer to FilesModule
 * @param _pArg  - pointer to Arg (arguments module)
 * 
 * @returns a pointer to FilesModule
 */
FilesModule * getFileModule(void * _pArg);


/** 
 * @brief Destroys Arg
 * @param _ppArg  - pointer to pointer to Arg (arguments module)
 * 
 * @returns void
 */
void destroyArg (Arg ** _ppArg);

#endif /*__ARGS_H__*/
