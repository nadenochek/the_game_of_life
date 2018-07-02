#ifndef __GAME_H__
#define __GAME_H__



/** 
 *  @file game.h
 *  @brief The Game of Life
 *	
 *  @details Simulates the game of life devised by John Horton Conway 
 * Creates random field of given size and activates the game of life for given number of levels.
 * Each grid is represented by bit
 *  result of each level is printed on the screen  - so we have some sort of animation
 *  in this version - the field has borders equals one grid on each side - it is a "dead zone"
 *
 *  @author Nadya Gneduke  (nadenok01@gmail.com)
 * 
 *  @bug No known bugs.
 */
 
 

/**
 * @brief Creates random field of given size and activates the game for given number of levels
 *
 * @param _side : side of the field in bits
 * @param _levels : number of levels to play
 * @return void
 */
void game(unsigned int _side, unsigned int _levels, unsigned int _threads);

#endif /*__GAME_H__*/
