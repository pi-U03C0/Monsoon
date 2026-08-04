#include <Monsoon/Monsoon.h>

char** MONS_SplitString(char* text,char on)
{
  //get the split count
  int sp_count = 1;
  for (int i = 0 ; text[i] ; i++)
    if (text[i] == on) sp_count++;

  char** ret_s = (char**)malloc(sizeof(char**)*(sp_count+1));
  if (!ret_s)return NULL;

  ret_s[0] =  ((char*)(long long)sp_count);
  ret_s++;

  char* text_buffer = malloc(strlen(text)+1);
  if (!text_buffer)return NULL;
  int s_count = 0;
  int c_char = 0;

  for (int i = 0 ; text[i] ; i++)
  {
     if (text[i] == on)
     {
        text_buffer[c_char+1] = 0;
        ret_s[s_count] = strdup(text_buffer);
        s_count++;
        c_char = 0;
        continue;
     }
     text_buffer[c_char] = text[i];
     c_char++;
  }

  if (c_char)
  {
    text_buffer[c_char+1] = 0;
    ret_s[s_count] = strdup(text_buffer);
  }
  ret_s[sp_count+1] = NULL;

  free(text_buffer);

  return ret_s;
}

char* MONS_AddString(char* fires,char* toadd)
{
  size_t fires_len = strlen(fires);
  size_t toadd_len = strlen(toadd);

  char* return_string = malloc(fires_len+toadd_len+1);

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
  if (!strlen(text)) return 0;

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
  char* r_buffer = malloc(strlen(string));
  int string_len = strlen(string);
  for (int i = 1 ; i <= string_len ; i++)
  {
    r_buffer[i-1] = string[string_len-i];
  }

  r_buffer[string_len] = 0;
  return r_buffer;
}

char* MONS_IntToString(int num)
{
  char* d = malloc(10);
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
  free(e);
  return d;
}
