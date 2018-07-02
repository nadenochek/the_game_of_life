#include <stdlib.h>		/*malloc*/

#include "args.h"
#include "files.h"
#include "chunks.h"

struct Printer_Arg
{
		Field * m_field;
		unsigned int m_levels;
		MyBarrier * m_barr;
		FilesModule * m_filesModule;
};


struct Workers_Arg
{
		Field * m_field;
		unsigned int m_levels;
		MyBarrier * m_barr;
		unsigned int m_nWorkers;
		unsigned int m_begin;
		unsigned int m_end;			
};


struct Arg
{
		Workers_Arg * m_workArgs;
		Printer_Arg * m_printArg;
};



/** 
 * @brief Creates an array of Workers arguments
 * @param _pField  - pointer to Field
 * @param _pBarr  - pointer to MyBarrier
 * @param _levels  - number of levels
 * @param _nWorkers  - number of working threads
 * 
 * @returns an array of Workers arguments or NULL if failed
 */
static Workers_Arg * createWorkersArg (Field * _pField, MyBarrier * _pBarr, unsigned int _levels, unsigned int _nWorkers);


/** 
 * @brief Creates a Printer_Arg
 * @param _pField  - pointer to Field
 * @param _pBarr  - pointer to MyBarrier
 * @param _levels  - number of levels
 * @param _dirName - the name of the directory
 * 
 * @returns a pointer to Printer_Arg or NULL if failed
 */
static Printer_Arg * createPrinterArg (Field * _pField, MyBarrier * _pBarr, unsigned int _levels, char * _dirName);

/*********************************************************************/
					/*API Functions*/
/*********************************************************************/

Arg * createArg (Field * _pField, unsigned int _levels, unsigned int _nWorkers, char * _name)
{
	Arg * pArg = NULL;
	MyBarrier *  pBarr;
	
	if(!_pField || !_name)
	{
		return NULL;
	}
	
	pBarr = myBarrierCreate (_nWorkers + 1);
	if (!pBarr)
	{
		return NULL;
	}

	pArg = malloc (sizeof (Arg));
	if (!pArg)
	{
		return NULL;
	}
	
	pArg->m_workArgs = createWorkersArg (_pField, pBarr, _levels, _nWorkers);	
	pArg->m_printArg = createPrinterArg (_pField, pBarr, _levels, _name);	
	return pArg;
}


unsigned int getNumLevels(void * _pArg)
{
	Printer_Arg * pack = (Printer_Arg*)_pArg;
	return pack->m_levels;
}


unsigned int getNumWorkers(void * _pArg)
{
	Workers_Arg * pack = (Workers_Arg*)_pArg;
	return pack->m_nWorkers;
}


unsigned int getBegin(void * _pArg)
{
	Workers_Arg * pack = (Workers_Arg*)_pArg;
	return pack->m_begin;

}

unsigned int getEnd(void * _pArg)
{
	Workers_Arg * pack = (Workers_Arg*)_pArg;
	return pack->m_end;

}


MyBarrier * getBarrier(void * _pArg)
{
	Printer_Arg * pack = (Printer_Arg*)_pArg;
	return pack->m_barr;
}


Field * getField(void * _pArg)
{
	Printer_Arg * pack = (Printer_Arg*)_pArg;
	return pack->m_field;
}


Printer_Arg * getPrinterArg(Arg * _pArg)
{
	return _pArg->m_printArg;
}


Workers_Arg *  getWorkersArgByIndex(Arg * _pArg, unsigned int _index)
{
	return &_pArg->m_workArgs[_index];
}


FilesModule * getFileModule(void * _pArg)
{
	Printer_Arg * pack = (Printer_Arg*)_pArg;
	return pack->m_filesModule;
}


void destroyArg (Arg ** _ppArg)
{
	if (!_ppArg || !*_ppArg)
	{
		return;
	}
		
	if((*_ppArg)->m_printArg->m_barr)
	{
		myBarrierDestroy(&(*_ppArg)->m_printArg->m_barr);
	}
		
	if((*_ppArg)->m_printArg->m_filesModule)
	{
		destroyFilesModule(&(*_ppArg)->m_printArg->m_filesModule);
	}
		
	free ((*_ppArg)->m_printArg);
	
	free ((*_ppArg)->m_workArgs);
	
	free (*_ppArg);	
}

/*********************************************************************/
					/*Help Functions*/
/*********************************************************************/

static Workers_Arg * createWorkersArg (Field * _pField, MyBarrier * _pBarr, unsigned int _levels, unsigned int _nWorkers)
{
	Workers_Arg * pWorkers;
	int i;
	Chunks * pChunks;
	
	pChunks = createChunks(getSide(_pField) * getSide(_pField), _nWorkers);
	if (!pChunks)
	{
		return NULL;
	}

	
	if (!_pField)
	{
		return NULL;
	}
	
	pWorkers = malloc (_nWorkers * sizeof (Workers_Arg));
	if (!pWorkers)
	{
		return NULL;
	}
	for (i = 0; i < _nWorkers; ++i)
	{	
		pWorkers[i].m_field = _pField;
		pWorkers[i].m_levels = _levels;
		pWorkers[i].m_barr = _pBarr;
		pWorkers[i].m_nWorkers = _nWorkers;
		pWorkers[i].m_begin = getChunkBegin(getChunkByIndex(pChunks, i));
		pWorkers[i].m_end = getChunkEnd(getChunkByIndex(pChunks, i));
	}
	
	destroyChunks(&pChunks);	

	return pWorkers;		
}


static Printer_Arg * createPrinterArg (Field * _pField, MyBarrier * _pBarr, unsigned int _levels, char * _name)
{
	Printer_Arg * pPrinter_arg;
	FilesModule * pFilesModule = NULL;
	
	if (!_pField || !_name)
	{
		return NULL;
	}	
	
	pFilesModule = createFilesModule(_name);
	if(!pFilesModule)
	{
		return NULL;
	}

	pPrinter_arg = malloc (sizeof (Printer_Arg));
	if (!pPrinter_arg)
	{
		destroyFilesModule(&pFilesModule);
		return NULL;
	}
		
	makeDir(pFilesModule);
	
	pPrinter_arg->m_field = _pField;
	pPrinter_arg->m_levels = _levels;
	pPrinter_arg->m_barr = _pBarr;
	pPrinter_arg->m_filesModule = pFilesModule;
	
	return pPrinter_arg; 
}

