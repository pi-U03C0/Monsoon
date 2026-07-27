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
      Queue->Items[i] = 0;
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
  if (!Queue)
  {
    LOG("Queue was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }

  if (MONS_IsQueueEmpty(Queue))
    LOG("Queue was Empty",MONSOON_LOG_WARNING,MONSOON_LOG_EMPTY);

  //read the PopPos
  uint64_t Item = (Queue -> Items[Queue -> PopPos]);
  //move the PopPos to the next pos
  Queue -> PopPos = MONS_NextQueuePopIndex(Queue);
  return Item;
}

MSBool MONS_PushQueue(MONS_Queue* Queue,uint64_t Item)
{
  if (!Queue)
  {
    LOG("Queue was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }

  if (MONS_IsQueueFull(Queue))
  {
    LOG("Queues was Full",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_FULL);
    return False;
  }

  //Write to the Write Pos
  Queue -> Items[Queue -> PushPos] = Item;
  //Meve to the next pos
  Queue -> PushPos = MONS_NextQueuePushIndex(Queue);

  return True;
}

MSBool MONS_IsQueueEmpty(MONS_Queue* Queue)
{
  if (!Queue)
  {
    LOG("Queue was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }

  if ((MONS_NextQueuePopIndex(Queue)) == (Queue -> PushPos)) return True;
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

  if (MONS_NextQueuePushIndex(Queue) == Queue -> PopPos) return False;
  return False;
}

MSBool MONS_CanPopQueue(MONS_Queue* Queue)
{
  if (!Queue)
  {
    LOG("Queue was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }
  //if the next index is not PushPos
  return !(MONS_NextQueuePopIndex(Queue) == Queue -> PushPos);
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
  if (Queue -> PopPos == Next) return Queue -> PopPos;

  return Next;
}
