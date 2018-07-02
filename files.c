#include <sys/stat.h> 	/*mkdir*/
#include <string.h>		/*strcpy*/
#include <stdlib.h>		/*malloc*/

#include "files.h"

#define DIR_SIZE 20
#define FILE_NAME_SIZE 50

struct Files
{
	char m_dirName[DIR_SIZE];
};



FilesModule * createFilesModule(char * _name)
{
	FilesModule * newFilesMod = NULL;
	
	newFilesMod = (FilesModule*)malloc(sizeof(FilesModule));
	if (!newFilesMod)
	{
		return NULL;
	}
	
	strncpy(newFilesMod->m_dirName, _name, DIR_SIZE);
	
	return newFilesMod;
}


void makeDir(FilesModule * _pFilesModule)
{
	if(!_pFilesModule)
	{
		return;
	}
	
	mkdir(_pFilesModule->m_dirName, 0700);	
}


FILE * openFile(FilesModule * _pFilesModule, unsigned int _frame)
{
	char file_name[FILE_NAME_SIZE];
	FILE *fptr;
	
	if(!_pFilesModule)
	{
		return NULL;
	}
	
	sprintf(file_name, "%s/frame_%d.txt",_pFilesModule->m_dirName, _frame + 1); 
	
	fptr = fopen(file_name, "w");
    if (NULL == fptr)
    {
        printf("File does not exists \n");
        return NULL;
    } 
    
    return fptr;
}


void closeFile(FILE * _pFile)
{
	if(!_pFile)
	{
		return;
	}
	
	fclose(_pFile);
}


void destroyFilesModule(FilesModule ** _ppFilesModule)
{
	if(!_ppFilesModule || !*_ppFilesModule)
	{
		return;
	}
	
	free(*_ppFilesModule);
	*
	_ppFilesModule = NULL;
}

