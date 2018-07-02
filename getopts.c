#include <stdio.h>		/*printf*/
#include <stdlib.h>		/*malloc, rand*/
#include <getopt.h>		/*getopt*/

#include "getopts.h"

static void print_usage();

static void print_usage() 
{
    printf("Usage: [-s] side of field [-l] number of levels [-t] number of threads\n");
}

struct Getopt
{
	unsigned int m_side;
	unsigned int m_nLevels;
	unsigned int m_nThreads;
};

Getopt * createGetopt(int _argc, char * _argv[])
{
	int option = 0;
    unsigned int side = 0, levels = 0, threads = 0;
    Getopt * pGetopt = NULL;
    	
	while ((option = getopt(_argc, _argv, "s:l:t:")) != -1) 
           {
               switch (option) 
               {
               case 's':
                   side = atoi(optarg);
                   break;
               
               case 'l':
                   levels = atoi(optarg);
                   break;
               
               case 't':
                   threads = atoi(optarg);
                   break;
               
               default: /* '?' */
					print_usage();
                    
                    exit(EXIT_FAILURE);
               }
           }

     if (!side || !levels) 
     {
		print_usage();
		
		exit(EXIT_FAILURE);
     }
		
	pGetopt = malloc(sizeof(Getopt));
    if (!pGetopt)
    {
		return NULL;
	}

		
	pGetopt->m_side = side;

	pGetopt->m_nLevels = levels;
		
	pGetopt->m_nThreads = threads;
	
	return pGetopt;
}


unsigned int getFieldSide(Getopt * _pGetopt)
{
	return _pGetopt->m_side;
}


unsigned int getNumberLevels(Getopt * _pGetopt)
{
	return _pGetopt->m_nLevels;
}


unsigned int getNumThreads(Getopt * _pGetopt)
{
	return _pGetopt->m_nThreads;
}


void destroyGetopt(Getopt ** _ppGetopt)
{
	if (!_ppGetopt || !*_ppGetopt)
	{
		return;
	}
	
	free(*_ppGetopt);
	*_ppGetopt = NULL;
}
