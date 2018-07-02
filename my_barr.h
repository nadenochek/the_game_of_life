#ifndef __MY_BARR_H__
#define __MY_BARR_H__

/** 
 * @brief API for my_barr.h
 * The calling thread will be blocked until the required number of threads will get to the barrier
 * 
 * This API includes functions:
 * 
 * Treads* myBarrierCreate(unsigned int _numThreads);
 * int MyBarrierrWait(MyBarrier* _pData);
 * int MyBarrierrDestroy(MyBarrier* _pData);
 * 
 * @author Nadya Gneduke (nadenok01@gmail.com)
 */


typedef struct MyBarrier MyBarrier;

/** 
 * @brief Creates new barrier
 * @param _numThreads  - number of threads waiting on barrier
 * 
 * @returns a pointer to the new barrier or NULL if creation failed
 */
MyBarrier* myBarrierCreate(unsigned int _numThreads);


/** 
 * @brief Waits on the barrier until all the threads are got to barrier
 * 
 * @param _pData: pointer to barrier
 * 
 * @returns if success: 0.
 * 			on fail: -1.
 */
int myBarrierWait(MyBarrier* _pBarr);


 /** 
 * @brief Destroys the barrier
 * @param _pData : pointer to barrier
 * 
 * @returns void.
 */
void myBarrierDestroy(MyBarrier** _ppBarr);


#endif /*__MY_BARR_H*/
