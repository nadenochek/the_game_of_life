#define _BSD_SOURCE

#include <stdlib.h>
#include <pthread.h>
#include "my_barr.h"

struct MyBarrier
{
	pthread_barrier_t m_barrier;
	unsigned int m_numThreads;	
};


MyBarrier* myBarrierCreate(unsigned int _numThreads)
{
	MyBarrier* pBarrier = NULL;
	
	if (0 == _numThreads)
	{
		return NULL;
	}
	
	pBarrier = (MyBarrier*)malloc(sizeof(MyBarrier));
	if (!pBarrier)
	{
		return NULL;
	}

	pBarrier->m_numThreads = _numThreads;

	pthread_barrier_init(&pBarrier->m_barrier, NULL, _numThreads);
	
	return pBarrier;
}


int myBarrierWait(MyBarrier* _pBarr)
{
	if (!_pBarr)
	{
		return -1;
	}
	
	pthread_barrier_wait(&_pBarr->m_barrier);
	
	return 0;
}


void myBarrierDestroy(MyBarrier** _ppBarr)
{
	if (!_ppBarr || !*_ppBarr) 
	{
		return;
	}
	
	pthread_barrier_destroy(&(*_ppBarr)->m_barrier);
	free(*_ppBarr);
	*_ppBarr = NULL;	
}



