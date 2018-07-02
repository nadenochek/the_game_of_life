#include <pthread.h>		/*pthread*/
#include <stdlib.h>		/*malloc*/

#include "thread.h"

struct Pthread
{
	pthread_t  * m_workers;	
	pthread_t  * m_printer;
	unsigned int m_nWorkers;	
};



static pthread_t * printerAllocation ();

static pthread_t * workersAllocation (int _nWorkers);

static pthread_t * createWorkers(Arg * _pArg, func _workFunc, int _nWorkers);

static pthread_t * createPrinter(Arg * _pArg, func _sum);

static void joinWorkers (pthread_t * _pWorkers, unsigned int _nWorkers);


static void joinPrinter (pthread_t * _pPrinter);


/*********************************************************************/
					/*API Functions*/
/*********************************************************************/

Pthread * createPthread (Arg * _pArg, func _workFunc, func _printFunc, unsigned int _nWorkers)
{
	Pthread * pPthread;
	
	if (!_pArg || !_workFunc || !_printFunc)
	{
		return NULL;
	}
	
	pPthread = malloc(sizeof (Pthread));
	if (!pPthread)
	{
		return NULL;
	}
	
	pPthread->m_workers = createWorkers(_pArg, _workFunc, _nWorkers);
	if (!pPthread->m_workers)
	{
		free(pPthread);
		return NULL;
	}
	
	pPthread->m_printer = createPrinter(_pArg, _printFunc);
	if (!pPthread->m_printer)
	{
		free(pPthread->m_workers);
		free(pPthread);
		return NULL;
	}
	
	pPthread->m_nWorkers = _nWorkers;
	return pPthread; 
}



void joinPthread (Pthread * _pPthread)
{
	if (!_pPthread)
	{
		return;
	}
	
	if (_pPthread->m_workers)
	{
		joinWorkers (_pPthread->m_workers, _pPthread->m_nWorkers);
	}
	
	if (_pPthread->m_printer)
	{
		joinPrinter (_pPthread->m_printer);
	}		
}


void destroyPthread (Pthread ** _ppPthread)
{
	if (!_ppPthread || !*_ppPthread)
	{
		return;
	}
	
	if ((*_ppPthread)->m_workers)
	{
		free ((*_ppPthread)->m_workers);
	}
	
	if ((*_ppPthread)->m_printer)
	{
		free ((*_ppPthread)->m_printer);
	}
	
	free (*_ppPthread);
	
	*_ppPthread = NULL;
}

/*********************************************************************/
					/*Help Functions*/
/*********************************************************************/

static void joinPrinter (pthread_t * _pPrinter)
{
	if (_pPrinter)
	{
		pthread_join(*_pPrinter, NULL);	

	}	
}


static void joinWorkers (pthread_t * _pWorkers, unsigned int _nWorkers)
{
	int i;
	
	for (i = 0; i < _nWorkers; ++i)
	{
		pthread_join(_pWorkers[i], NULL);
	}
}


static pthread_t * createPrinter(Arg * _arg, func _print)
{
	int status;
	pthread_t * pPrinter;
	
	if (!_arg || !_print)
	{
		return NULL;
	}
	
	pPrinter = printerAllocation();
	if(!pPrinter)
	{
		return NULL;
	}
	
	status = pthread_create(pPrinter, NULL, _print, getPrinterArg(_arg));
	if (status)
	{
		return NULL;
	}
		
	return pPrinter;		
}


static pthread_t * createWorkers(Arg * _pArg, func _workFunc, int _nWorkers)

{
	int i, status;
	pthread_t * pWorkers;
	
	if (!_pArg || !_workFunc)
	{
		return NULL;
	}
	
	pWorkers = workersAllocation (_nWorkers);

	for (i = 0; i < _nWorkers; ++i)
	{
		status = pthread_create(&pWorkers[i], NULL, _workFunc, getWorkersArgByIndex(_pArg, i));
		if (status != 0)
		{
			return NULL;
		}		
	}
	
	return pWorkers;
}


static pthread_t * workersAllocation (int _nWorkers)

{
	pthread_t * pWorkers;
	
	if (_nWorkers < 1)
	{
		return NULL;
	}
	
	pWorkers = malloc (_nWorkers * sizeof (pthread_t));
	if (!pWorkers)
	{
		return NULL;
	}
	
	return pWorkers;
}


static pthread_t * printerAllocation ()
{
	pthread_t * pPrinter;
	
	pPrinter = malloc (sizeof (pthread_t));
	if (!pPrinter)
	{
		return NULL;
	}
	
	return pPrinter;
}

