#ifndef MONSOON_FILESYSTEM_H
#define MONSOON_FILESYSTEM_H

#include <Monsoon/MONS_Types.h>

#define MONSOON_FILE_READ 0
#define MONSOON_FILE_WRITE 1
#define MONSOON_FILE_READ_WRITE 2

MSBool MONS_FileExists(char* FilePath);

MONS_File* MONS_OpenFile(char* FilePath,char Mode);

/*Get The Full path to a file
*`NOTE: dealloc with RemoveMemory Or there will a memory leak */
char* MONS_FullFilePath(char* FilePath);

#endif
