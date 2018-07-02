#ifndef __FILES_H__
#define __FILES_H__
#include <stdio.h>	/*FILE**/

typedef struct Files FilesModule;

/** 
 * @brief Creates new FilesModule
 * @param _name  - name of the directory
 * 
 * @returns a pointer to the new FilesModule or NULL if creation failed
 */
FilesModule * createFilesModule(char * _name);


/** 
 * @brief Creates folder with the given name
 * @param _files  - pointer to FilesModule
 * 
 * @returns void
 */
void makeDir(FilesModule * _pFilesModule);


/** 
 * @brief opens file in given directory with number of frame
 * @param _pFilesModule  - pointer to FilesModule
 * @param _frame  - number of frame
 * 
 * @returns pointer to file descriptor or  NULL if failed
 */
FILE * openFile(FilesModule * _pFilesModule, unsigned int _frame);


/** 
 * @brief Closes file
 * @param _files  - pointer to FILE
 * 
 * @returns void
 */
void closeFile(FILE * _pFile);


/** 
 * @brief Destroys FileModule
 * @param _filesModule  - pointer to pointer to FilesModule
 * 
 * @returns void
 */
void destroyFilesModule(FilesModule ** _ppFilesModule);

#endif /*__FILES_H__*/
