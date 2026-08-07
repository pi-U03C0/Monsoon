#ifndef MONSOON_STRUCTURE_QUEUES_H
#define MONSOON_STRUCTURE_QUEUES_H

#include <Monsoon/MONS_Types.h>

//Initializ The Queue
MONS_Queue* MONS_InitQueue(uint16_t Capacity);

//Terminate the Queue
MSBool MONS_TerminateQueue(MONS_Queue* Queue);

//Pop/Read the Current PopPos and Move it than return it
uint64_t MONS_PopQueue(MONS_Queue* Queue);

//Push/Write the Item to the Queue and Move the PushPos
MSBool MONS_PushQueue(MONS_Queue* Queue,uint64_t Item);

//Read from the Queue and return it without moveing the PopPos
uint64_t MONS_PeekQueue(MONS_Queue* Queue);

//Check if a Queue is Empty
MSBool MONS_IsQueueEmpty(MONS_Queue* Queue);

//Check if a Queue is Full True if Full else False
MSBool MONS_IsQueueFull(MONS_Queue* Queue);

//Return the Next Pop/Read Index
uint16_t MONS_NextQueuePopIndex(MONS_Queue* Queue);

//Return the Next Push/Write Index
uint16_t MONS_NextQueuePushIndex(MONS_Queue* Queue);

//check if a value can pop off the Queue
MSBool MONS_CanPopQueue(MONS_Queue* Queue);

//check if a value can push on the Queue
MSBool MONS_CanPushQueue(MONS_Queue* Queue);

//print the Queue and items
void MONS_PrintQueue(MONS_Queue* Queue);

#endif

