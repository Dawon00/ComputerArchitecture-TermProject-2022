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

    switch (argv[0][0])
    {
    case 'l':
      // loadProgram(argv[1]);
      break;
    case 'j':
      // 입력 주소로 프로그램 PC 점프
      break;
    case 'g':
      // goProgram();
      break;
    case 's':
      // stepProgram();
      break;
    case 'm':
      // 입력 주소의 메모리값 출력
      break;
    case 'h':
      helpCommand();
      break;
    case 'b':
      // setBreak();
      break;
    case 'x': // 프로그램 종료
      return 0;
    default:
      break;
    }
  }
  return 0;
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

void helpCommand()
{
  printf("usage: <command> <option>\n");
  printf("=====Command List=====\n");
  printf("l <path>\t 해당 경로의 프로그램 로드\n");
  printf("j <address>\t 해당 주소로 PC 점프\n");
  printf("g\t\t 프로그램의 모든 명령어 실행\n");
  printf("s\t\t 프로그램의 명령어 한 줄 실행\n");
  printf("m <address>\t 입력받은 주소의 메모리 값 출력\n");
  printf("r\t\t 레지스터 값 출력\n");
  printf("h\t\t 명령어 help 리스트 출력\n");
  printf("b <PC>\t\t PC값을 break point로 설정\n");
  printf("x\t\t 프로그램 종료\n");
}