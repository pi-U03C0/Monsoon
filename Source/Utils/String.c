#include <Monsoon/Monsoon.h>

uint64_t MONS_StringLength(char* String)
{
  if (!String)return 0;

  uint64_t i = 0;
  while (String[i])
    i++;

  return i;
}

uint64_t MONS_StringCopy(char* CopyTo,char* From)
{
  if ((!CopyTo) || (!From))
  {
    LOG("CopyTo and or From was NULL",MONSOON_LOG_ERROR,MONSOON_LOG_WAS_NULL);
    return False;
  }

  //get the Length and copy it to "CopyTo" from "From"
  uint64_t From_Length = MONS_StringLength(From);
  uint64_t i = 0;
  for ( ; i <= From_Length ; i++)
  {
     CopyTo[i] = From[i];
  }
  return From_Length;
}

char** MONS_SplitString(char* text,char on)
{
  if (!text)return NULL;

  //count how many times to split
  int Split_Count = 1;
  for (int i = 0 ; text[i] ; i++)
    if (text[i] == on) Split_Count++;

  //alloc buffer
  char** Return_Split = (char**)GetMemory(sizeof(char**)*(Split_Count+2));
  if (!Return_Split)return NULL;

  //add the array count
  Return_Split[0] =  ((char*)(long long)Split_Count);
  Return_Split++;

  char* text_buffer = GetMemory(MONS_StringLength(text)+1);
  if (!text_buffer)
  {
    RemoveMemory(Return_Split-1);
    return NULL;
  }
  int String_Count = 0;
  int c_char = 0;

  for (int i = 0 ; text[i] ; i++)
  {
     if (text[i] == on)
     {
        text_buffer[c_char] = 0;
        Return_Split[String_Count] = MONS_DupeString(text_buffer);
        String_Count++;
        c_char = 0;
        continue;
     }
     text_buffer[c_char] = text[i];
     c_char++;
  }

  if (c_char)
  {
    text_buffer[c_char] = 0;
    Return_Split[String_Count] = MONS_DupeString(text_buffer);
  }
  Return_Split[Split_Count] = NULL;

  RemoveMemory(text_buffer);

  return Return_Split;
}

char* MONS_FindAndReplaceString(char* Original,char* Find,char* Replace)
{
  //check NULL
  if (!Original || !Find || !Replace) return NULL;

  //cache Length
  uint64_t Original_Length = MONS_StringLength(Original);
  uint64_t Replace_Length = MONS_StringLength(Replace);;
  uint64_t Find_Length = MONS_StringLength(Find);


  //check if any Length is 0
  if (!(Original_Length) || !(Find_Length) || !(Replace_Length))return NULL;

  //get the split Length
  uint64_t Replace_Count = 1;
  for (uint64_t i = 0 ; i < Original_Length ; i++)
  {
    if (MONS_CheckIfEqualStringFromPos(&Original[i],Find))
    {
      Replace_Count += 2;
    }
  }

  //alloc split and temp string
  char** ReturnS = GetMemory(sizeof(char*)*Replace_Count);
  if (!ReturnS)return NULL;

  char* Temp_String = GetMemory(Original_Length+1);
  if (!Temp_String)return NULL;

  uint64_t ReturnS_Index = 0;
  uint64_t Temp_Index = 0;
  for (uint64_t i = 0 ; i < Original_Length ; i++)
  {
    if (MONS_CheckIfEqualStringFromPos(&Original[i], Find))
    {
      Temp_String[Temp_Index] = 0;

      ReturnS[ReturnS_Index] = MONS_DupeString(Temp_String);

      if (!ReturnS[ReturnS_Index])
      {
        RemoveMemory(Temp_String);
        RemoveMemory(ReturnS);
        return NULL;
      }

      Temp_Index = 0;
      ReturnS_Index++;
      ReturnS[ReturnS_Index] = MONS_DupeString(Replace);

      if (!ReturnS[ReturnS_Index])
      {
        RemoveMemory(Temp_String);
        RemoveMemory(ReturnS);
        return NULL;
      }

      ReturnS_Index++;
      i += Find_Length - 1;
    }
    else
    {
      Temp_String[Temp_Index] = Original[i];
      Temp_Index++;
    }
  }

  //check if there is any left and add append it
  if (Temp_Index)
  {
    Temp_String[Temp_Index] = 0;
    ReturnS[ReturnS_Index++] = MONS_DupeString(Temp_String);
  }

  //merge string and if failed ReturnString is allredey NULL
  char* ReturnString = MONS_MergeString(ReturnS, ReturnS_Index);

  //dealloc
  for (uint64_t i = 0 ; i < ReturnS_Index ; i++)
  {
    RemoveMemory(ReturnS[i]);
  }
  RemoveMemory(Temp_String);
  RemoveMemory(ReturnS);

  return ReturnString;
}

char* MONS_MergeString(char** Strings,uint64_t Length)
{
  uint64_t TotalLength = 0 ;
  for (uint64_t i = 0 ; i < Length ; i++)
  {
     TotalLength += MONS_StringLength(Strings[i]);
  }

  char* ReturnString = malloc(TotalLength+1);
  if (!ReturnString) return NULL;

  uint64_t StringIndex = 0;
  for (uint64_t i = 0 ; i < Length ; i++)
  {
    for (uint64_t j = 0 ; j < MONS_StringLength(Strings[i]) ; j++)
    {
      ReturnString[StringIndex] = Strings[i][j];
      StringIndex++;
    }
  }

  ReturnString[TotalLength] = 0;
  return ReturnString;
}

MSBool MONS_CheckIfEqualStringFromPos(char* Original,char* Find)
{
   uint64_t Find_Length = MONS_StringLength(Find);

   for (uint64_t i = 0 ; i < Find_Length ; i++)
   {
     if (!(Original[i] == Find[i]))return False;
   }
   return True;
}

char* MONS_DupeString(char* String)
{
  uint64_t String_Length = MONS_StringLength(String);
  char* ReturnString = GetMemory(String_Length+1);
  if (!ReturnString)return NULL;

  for (uint64_t i = 0 ; i <= String_Length ; i++)
  {
    ReturnString[i] = String[i];
  }

  return ReturnString;
}

char* MONS_AddString(char* fires,char* toadd)
{
  size_t fires_len = MONS_StringLength(fires);
  size_t toadd_len = MONS_StringLength(toadd);

  char* return_string = GetMemory(fires_len+toadd_len+1);

  for (size_t i = 0 ; i < fires_len ; i++)
  {
    return_string[i] = fires[i];
  }

  for (size_t i = fires_len ; i < toadd_len+fires_len ; i++)
  {
    return_string[i] = toadd[i-fires_len];
  }

  return_string[fires_len+toadd_len] = 0;
  return return_string;
}

MSBool MONS_FindInString(char* text,char on)
{
  for (int i = 0 ;text[i] ; i++)
  {
    if (text[i] == on) return True;
  }
  return False;
}

int MONS_StringToInt(char* text)
{
  if (!MONS_StringLength(text)) return 0;

  size_t r = 0;
  for (int i = 0 ; text[i] ; i++)
  {
    if (!((text[i] >= 48) || (text[i] <= 57))) return -1;

    r *= 10;
    r += text[i] - 48;
  }

  return r;
}

char* strevs(char* string)
{
  char* r_buffer = GetMemory(MONS_StringLength(string));
  int string_len = MONS_StringLength(string);
  for (int i = 1 ; i <= string_len ; i++)
  {
    r_buffer[i-1] = string[string_len-i];
  }

  r_buffer[string_len] = 0;
  return r_buffer;
}

char* MONS_IntToString(int num)
{
  char* d = GetMemory(10);
  int c = 0;

  for (int i = 0 ; num ; i++ ) 
  {
    d[i] = (num % 10) + 48;          // (num % 10) to get the number in the one place than add 48 to get the ascii value
    num = ((num-(num % 10))/10);     // (num-(num % 10)) to set the one place to 0 then div by 10 to set the one the value of the 10th place
    c = i;                           // i index
  }

  d[c+1] = 0;
  char* e = d;
  d = strevs(d);
  RemoveMemory(e);
  return d;
}
