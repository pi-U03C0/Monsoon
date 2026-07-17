#ifndef MONSOON_FILESYSTEM_H
#define MONSOON_FILESYSTEM_H

#include <Monsoon/MONS_Types.h>
#include <stdint.h>

#define MONSOON_FILE_READ 0
#define MONSOON_FILE_WRITE 1
#define MONSOON_FILE_READ_WRITE 2

MSBool MONS_FileExists(char* FilePath);

MONS_File* MONS_OpenFile(char* FilePath,char Mode);

MSBool MONS_CloseFile(MONS_File* FileHandle);

uint64_t MONS_ReadFile(MONS_File* FileHandle,char* Buffer,uint64_t Length);

int MONS_WriteFile(MONS_File* FileHandle,char* Buffer,uint64_t Length);

/*Get The Full path to a file
*`NOTE: dealloc with RemoveMemory Or there will a memory leak */
char* MONS_FullFilePath(char* FilePath);

uint64_t MONS_GetFileSize(MONS_File* hFile);

char* MONS_OpenModeToString(char Mode);

#endif
