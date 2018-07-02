#ifndef __CHUNKS_H__
#define __CHUNKS_H__


/** 
 *  @file chunks.h
 *  @brief The Chunks Module
 *	
 *  @details This module is needed to divide an array to chunks for giving to each thread it's own chunk for work
 *  @author Nadya Gneduke  (nadenok01@gmail.com)
 * 
 *  @bug No known bugs.
 */

typedef struct Chunk Chunk;
typedef struct Chunks Chunks;


/** 
 * @brief Creates Chunks
 * @param _initial  - pointer to pthread
 * @param _noe  - pointer to pthread
 * 
 * @returns pointer to Chunks
 */
Chunks * createChunks(unsigned int _initial, unsigned int _noe);


/** 
 * @brief Returns begin of the Chunk
 * @param _pChunk  - pointer to Chunk
 * 
 * @returns begin of the Chunk
 */
unsigned int getChunkBegin(Chunk * _pChunk);


/** 
 * @brief end of the Chunk
 * @param _pChunk  - pointer to Chunk
 * 
 * @returns end of the Chunk
 */
unsigned int getChunkEnd(Chunk * _pChunk);


/** 
 * @brief pointer to Chunk at the  specific index 
 * @param _pChunks  - pointer to Chunks
 * @param _index  - index at the array of chunks
 * 
 * @returns pointer to specific Chunk
 */
Chunk * getChunkByIndex(Chunks * _pChunks, unsigned int _index);


/** 
 * @brief Prints chunks
 * @param _pChunks  - pointer to chunks to print
 * 
 * @returns void
 */
void printChunks(Chunks * _pChunks);


/** 
 * @brief Destroys chunks
 * @param _ppChunks  - pointer to pointer to chunks
 * 
 * @returns void
 */
void destroyChunks(Chunks ** _ppChunks);

#endif /*__CHUNKS_H__*/
