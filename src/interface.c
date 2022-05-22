#include <stdio.h>
#include <string.h>
#include "interface.h"

#define COMMAND_LIMIT 100
#define ARGV_SIZE 2

int main(void)
{
  char command[COMMAND_LIMIT];
  char *argv[ARGV_SIZE];
  int command_len, argc;

  while (1)
  {
    command_len = readCommand(command);
    argc = parseCommand(command, argv);
  }
}

int readCommand(char *command)
{
  printf("명령어 입력: ");
  fgets(command, COMMAND_LIMIT, stdin);
  return strlen(command);
}

int parseCommand(char *command, char **argv)
{
  char *ptr = strtok(command, " \n");
  int argc;
  for (argc = 0; ptr != NULL; argc++)
  {
    argv[argc] = ptr;
    ptr = strtok(NULL, " \n");
  }
  return argc;
}