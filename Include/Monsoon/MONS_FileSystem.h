#ifndef MONSOON_FILESYSTEM_H
#define MONSOON_FILESYSTEM_H

#include <Monsoon/MONS_Types.h>

#define MONSOON_FILE_READ 0
#define MONSOON_FILE_WRITE 1
#define MONSOON_FILE_READ_WRITE 2

//check if a file exists
//----------------------------------------
//`FilePath`:The Path to the file
MSBool MONS_FileExists(char* FilePath);

//Open a file Handle for action define by Mode
//----------------------------------------
//`FilePath`:The Path to the File
//`Mode`:how to open it Read/Write
MONS_File* MONS_OpenFile(char* FilePath,char Mode);

//Close a file and Frees the MONS_File Object
//----------------------------------------
//`FileHandle`:The Monsoon Handle to the File
MSBool MONS_CloseFile(MONS_File* FileHandle);

//Read from a file
//----------------------------------------
//`FileHandle`:The Monsoon Handle to the File
//`Buffer`:The Buffer to Read the Byte from
//`Length`:The Number of byte to read
uint64_t MONS_ReadFile(MONS_File* FileHandle,char* Buffer,uint64_t Length);

//Write to a File
//----------------------------------------
//`FileHandle`:The Monsoon File Handle to the file
//`Buffer`:The Buffer of byte to write to
//`Length`:The Number of byte to read from the file and write to the buffer
int MONS_WriteFile(MONS_File* FileHandle,char* Buffer,uint64_t Length);

/*Get The Full path to a file
**NOTE: dealloc with RemoveMemory Or there will a memory leak
------
*`FilePath`: The Path to the file */
char* MONS_FullFilePath(char* FilePath);

//Get the Size of a File in bytes
//----------------------------------------
//`hFile`:The Monsoon File Handle
uint64_t MONS_GetFileSize(MONS_File* hFile);

//Convert a Mode to String
//----------------------------------------
//`Mode`:The File Mode
char* MONS_OpenModeToString(char Mode);

//Finds the first File with that name
//----------------------------------------
//`FileName`:The Name of the file to search for
//`FileSearchPath`:The Path To Search
//`SearchSystemPath`:Should function check the SystemPath for that File
//----------------------------------------
//`The` SearchPath Paths are Split by byte 0x01 which is define as MONSOON_SPLIT_PATH 1 for example:
//`"c:\somethings{0x1}c:\somethingelse"`
//`　　　　　　　　^`
//`This` is what it will split in to {"c:\somethings","c:\somethingelse"},
char* MONS_FindFile(char* FileName,char* FileSearchPath,MSBool SearchSystemPath);

#endif
