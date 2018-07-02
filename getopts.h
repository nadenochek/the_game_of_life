#ifndef __GETOPTS_H__
#define __GETOPTS_H__

/** 
 *  @file getopts.h
 *  @brief Gets arguments from command line
 *	
 *  @details This module gets from command line arguments needed for the game of life
 *  @author Nadya Gneduke  (nadenok01@gmail.com)
 * 
 *  @bug No known bugs.
 */

typedef struct Getopt Getopt;

/** 
 * @brief Joines all threads
 * @param _argc  - number of the arguments from command line
 * @param _argv  - an array of arguments from command line
 * 
 * @returns void
 */
Getopt * createGetopt(int _argc, char * _argv[]);


/** 
 * @brief Returns the side of the field
 * @param _pGetopt  - pointer to getopt
 * 
 * @returns the side of the field
 */
unsigned int getFieldSide(Getopt * _pGetopt);


/** 
 * @brief Returns the number of levels for the game of life
 * @param _pGetopt  - pointer to getopt
 * 
 * @returns number of levels for the game
 */
unsigned int getNumberLevels(Getopt * _pGetopt);


/** 
 * @brief Returns the number of threads for the game of life
 * @param _pGetopt  - pointer to getopt
 * 
 * @returns number of threads for the game
 */
unsigned int getNumThreads(Getopt * _pGetopt);


/** 
 * @brief Destroys Getopt
 * @param _ppGetopt  - pointer to pointer to Getopt
 * 
 * @returns void
 */
void destroyGetopt(Getopt ** _ppGetopt);
#endif /*__GETOPTS_H__*/
