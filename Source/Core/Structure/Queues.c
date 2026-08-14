#include "Monsoon/Structure/Queues.h"
#include "Monsoon/MONS_Log.h"
#include <Monsoon/Monsoon.h>
#include <stdio.h>

MONS_Queue* MONS_InitQueue(uint16_t Capacity)
{
  MONS_Queue* Queue = GetMemory(sizeof(MONS_Queue));
  if (!Queue)
  {
    Error_Memory();
    return NULL;
  }

  Queue -> Items = GetMemory(sizeof(uint64_t)*Capacity);
  if (!Queue -> Items)
  {
    Error_Memory();
    RemoveMemory(Queue);
    return NULL;
  }

  Queue -> Capacity = Capacity;
  Queue -> PopPos = 0;
  Queue -> PushPos = 0;

  for (uint16_t i = 0; i < Capacity; i++)
  {
    Queue -> Items[i] = 0;
  }

  return Queue;
}

MSBool MONS_TerminateQueue(MONS_Queue* Queue)
{
  if (!Queue)
  {
    LOG("Queue was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }

  if (!Queue -> Items)
  {
    LOG("Queues -> Item was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }

  RemoveMemory(Queue -> Items);
  Queue -> Capacity = 0;
  Queue -> PopPos = 0;
  Queue -> PushPos = 0;

  return True;
}

uint64_t MONS_PopQueue(MONS_Queue* Queue)
{
  LOG("Poping Value %020llu from %d",MONSOON_LOG_DEBUG,255,Queue -> Items[Queue -> PopPos],Queue -> PopPos);
  if (!Queue)
  {
    LOG("Queue was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }

  //read the PopPos
  uint64_t Item = (Queue -> Items[Queue -> PopPos]);
  Queue -> Items[Queue -> PopPos] = 0;
  //move the PopPos to the next pos

  //if can pop than pop
  if (MONS_CanPopQueue(Queue))
  {
    Queue -> PopPos = MONS_NextQueuePopIndex(Queue);
  }

  return Item;
}

MSBool MONS_PushQueue(MONS_Queue* Queue,uint64_t Item)
{
  LOG("Pushing %020llu To Queue at pos %d",MONSOON_LOG_DEBUG,255,Item,Queue -> PushPos);
  if (!Queue)
  {
    LOG("Queue was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }

  if (MONS_IsQueueFull(Queue))
  {
    LOG("Queues was Full",MONSOON_LOG_WARNING,MONSOON_LOG_WAS_FULL);
    Queue -> Items[Queue -> PushPos] = Item;
    return True;
  }

  //Write to the Write Pos
  Queue -> Items[Queue -> PushPos] = Item;
  //Meve to the next pos
  Queue -> PushPos = MONS_NextQueuePushIndex(Queue);

  return True;
}

uint64_t MONS_PeekQueue(MONS_Queue* Queue)
{
  if (!Queue)
  {
    LOG("Queue was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }

  uint64_t Item = Queue -> Items[Queue -> PopPos];
  return Item;
}

MSBool MONS_IsQueueEmpty(MONS_Queue* Queue)
{
  if (!Queue)
  {
    LOG("Queue was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }

  //if the Next Queues Pop index equeal PushPos than return true
  if ((MONS_NextQueuePopIndex(Queue)) == (Queue -> PushPos)) return True;
  //if both are 0 than return true
  if ((Queue -> PopPos == 0) == (Queue -> PushPos == 0)) return True;

  return False;
}

MSBool MONS_IsQueueFull(MONS_Queue* Queue)
{
  if (!Queue)
  {
    LOG("Queue was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }

  //if the next PushPos index is equeal to PopPos then return true
  if (((Queue -> PushPos+1) % Queue -> Capacity) == Queue -> PopPos) return True;
  return False;
}

MSBool MONS_CanPopQueue(MONS_Queue* Queue)
{
  if (!Queue)
  {
    LOG("Queue was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }

  //get the next PopPos
  uint16_t Next = ((Queue -> PopPos+1) % Queue -> Capacity);

  //if the next index is not PushPos and not at the same index e.g at 0
  if (Next == Queue -> PushPos)
  {
    return False;
  }
  if (Queue -> PopPos == Queue -> PushPos)
  {
    return False;
  }
  return True;
}

MSBool MONS_CanPushQueue(MONS_Queue* Queue)
{
  if (!Queue)
  {
    LOG("Queue was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }
  return (Queue -> PushPos == (Queue -> PopPos-1));
}

uint16_t MONS_NextQueuePopIndex(MONS_Queue* Queue)
{
  if (!Queue)
  {
    LOG("Queue was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }

  uint16_t Next = ((Queue -> PopPos+1) % Queue -> Capacity);
  if (Queue -> PushPos == Next) return Queue -> PopPos;

  return Next;
}

uint16_t MONS_NextQueuePushIndex(MONS_Queue* Queue)
{
  if (!Queue)
  {
    LOG("Queue was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }

  uint16_t Next = ((Queue -> PushPos+1) % Queue -> Capacity);
  if (Queue -> PushPos == Next) return Queue -> PushPos;

  return Next;
}

void MONS_PrintQueue(MONS_Queue* Queue)
{
   printf("Queue -> Capacity = %d\n",Queue -> Capacity);
   printf("Queue -> PopPos = %d\n",Queue -> PopPos);
   printf("Queue -> PushPos = %d\n",Queue -> PushPos);

   for (uint16_t i = 0 ; i < Queue -> Capacity ; i++)
   {
      printf("Queue index at %d is %020llu\n",i,Queue -> Items[i]);
   }
}
