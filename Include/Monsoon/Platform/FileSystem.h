#ifndef MONSOON_FILESYSTEM_H
#define MONSOON_FILESYSTEM_H

#include <Monsoon/Monsoon.h>

#define MONSOON_FILE_READ 0
#define MONSOON_FILE_WRITE 1
#define MONSOON_FILE_READ_WRITE 2

#define MONSOON_SPLIT_PATH 0x1

#define MONSOON_FILE_UNUSED (void*)1

//check if a file exists
//----------------------------------------
//`FilePath`:The Path to the file
MONS_API MSBool MONS_FileExists(char* FilePath);

//Open a file Handle for action define by Mode
//----------------------------------------
//`FilePath`:The Path to the File
//`Mode`:how to open it Read/Write
MONS_API MONS_File* MONS_OpenFile(char* FilePath,char Mode);

//Close a file and Frees the MONS_File Object
//----------------------------------------
//`FileHandle`:The Monsoon Handle to the File
MONS_API MSBool MONS_CloseFile(MONS_File* FileHandle);

//Read from a file
//----------------------------------------
//`FileHandle`:The Monsoon Handle to the File
//`Buffer`:The Buffer to Read the Byte from
//`Length`:The Number of byte to read
MONS_API uint64_t MONS_ReadFile(MONS_File* FileHandle,char* Buffer,uint64_t Length);

//Write to a File
//----------------------------------------
//`FileHandle`:The Monsoon File Handle to the file
//`Buffer`:The Buffer of byte to write to
//`Length`:The Number of byte to read from the file and write to the buffer
MONS_API int MONS_WriteFile(MONS_File* FileHandle,char* Buffer,uint64_t Length);

/*Get The Full path to a file
**NOTE: dealloc with RemoveMemory Or there will a memory leak
------
*`FilePath`: The Path to the file */
MONS_API char* MONS_FullFilePath(char* FilePath);

//Get the Size of a File in bytes
//----------------------------------------
//`hFile`:The Monsoon File Handle
MONS_API uint64_t MONS_GetFileSize(MONS_File* hFile);

//Convert a Mode to String
//----------------------------------------
//`Mode`:The File Mode
MONS_API char* MONS_OpenModeToString(char Mode);

//Finds the first File with that name
//----------------------------------------
//`FileName`:The Name of the file to search for
//`FileSearchPath`:The Path To Search
//`SearchSystemPath`:Should function check the SystemPath for that File
//----------------------------------------
//`The` SearchPath Paths are Split by byte 0x01 which is define as MONSOON_SPLIT_PATH for example:
//`"c:\somethings{0x1}c:\somethingelse"`
//`　　　　　　　　^`
//`This` is what it will split in to {"c:\somethings","c:\somethingelse"},
MONS_API char* MONS_FindFile(char* FileName,char* FileSearchPath,MSBool SearchSystemPath);

//Close all File that are current Open
//----------------------------------------
//`This` Function runs on Monsoon Exit
MONS_API void MONS_CloseAllFile();


//Add a Path to GLoable File SearchPath
//----------------------------------------
//`Path`:The Path to add
//----------------------------------------
MONS_API MSBool MONS_AddSearchPath(char* Path);

MONS_API MSBool MONS_IsAtLimitFile();

MONS_API MSBool MONS_AddOpenFile(MONS_File* File);

MONS_API MSBool MONS_RemoveOpenFile(MONS_File* File);



#endif
