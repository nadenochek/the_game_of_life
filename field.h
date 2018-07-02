#ifndef __FIELD_H__
#define __FIELD_H__
#include "files.h"
/** 
 *  @file field.h
 *  @brief Functions for the field of the game of life
 *	
 *  @author Nadya Gneduke  (nadenok01@gmail.com)
 * 
 *  @bug No known bugs.
 */

typedef struct Field Field;

/**
 * @brief Creates random field of given size (side*side)
 *
 * @param _side : side of the field in bits
 * @return pointer to new Field or NULL if something gone wrong
 */
Field* createField(unsigned int _side);

/**
 * @brief Creates random field of given size (side*side)
 *
 * @param _side : side of the field in bits
 * @return pointer to new Field or NULL if something gone wrong
 */
unsigned int getSide(Field * _field);


/**
 * @brief Checks if isFinished is turned on
 *
 * @param _pField : pointer to the field
 * @return 1 if True, 0 if False 
 */
int isFinished(Field * _pField);


/**
 * @brief Changes Turn of arrays and checks if is finished
 *
 * @param _pField : pointer to the field
 * @param _numLiveGrids : number of live grids
 * @return void
 */
void checkAndChangeTurn(Field * _pField, unsigned int _numLiveGrids);


/**
 * @brief Changes the state of specifig grid
 *
 * @param _pField : pointer to the field
 * @param _numOfBit : number of grid to change
 * @return 1 if become live, 0 - if become dead
 */
int changeGridState(Field * _pField, unsigned int _numOfBit);


/**
 * @brief Prints field
 *
 * @param _field : pointer to the field to print
  * @return void
 */
void printField(Field* _pField);


/**
 * @brief Prints field to file
 *
 * @param _field : pointer to the field to print
 * @param _frame : the number of the frame
 * @param _pFilesModule : pointer to the FilesModule

  * @return void
 */
void printFieldToFile(Field* _pField, unsigned int _frame, FilesModule * _pFilesModule);


/**
 * @brief Destroys field
 *
 * @param _field : pointer to pointer to the field to destroy
 * @return void
 */
void destroyField(Field** ppField);


#endif /*__FIELD_H__*/
