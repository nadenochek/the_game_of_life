#include <stdio.h>		/*NULL*/

#include "getopts.h"
#include "game.h"

int main(int argc, char *argv[])		
{
	Getopt * pGetopt = NULL;
	
	pGetopt = createGetopt(argc, argv);
	
	game(getFieldSide(pGetopt), getNumberLevels(pGetopt), getNumThreads(pGetopt));
	
	destroyGetopt(&pGetopt);
	return 0;
}
