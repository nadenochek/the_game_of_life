#ifndef __BIT_MANIPULATE_H__
#define __BIT_MANIPULATE_H__
#define NUM_OF_BITS 8


/** 
 *  @file bit_manipulate.h
 *  @brief Manipulations with bits in matrix of chars
 *	
 *  @author Nadya Gneduke  (nadenok01@gmail.com)
 * 
 *  @bug No known bugs.
 */

/**
 * @brief Sets bit on
 *
 * @param _matrix : matrix of chars
 * @param _num : number of bit to change from the beginning of the matrix
 * @return void
 */
void setBit(char * _pMatrix, unsigned int _num);


/**
 * @brief Clears bit 
 *
 * @param _matrix : matrix of chars
 * @param _num : number of bit to change from the beginning of the matrix
 * @return void
 */
void clearBit(char * _pMatrix, unsigned int _num);


/**
 * @brief Checks if bit is on
 *
 * @param _matrix : matrix of chars
 * @param _num : number of bit to change from the beginning of the matrix
 * @return 1 - set, 0 - not set
 */
char ifSet (char *  _pMatrix, unsigned int _num);


/**
 * @brief Randomly sets bit or not (used for create random matrix)
 *
 * @param _matrix : matrix of chars
 * @param _num : number of bit to change from the beginning of the matrix
 * @return void
 */
void randomSetBit(char * _pMatrix, unsigned int _num);

#endif /*__BIT_BIT_MANIPULATE_H__*/
