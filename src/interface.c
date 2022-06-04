#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "decode.h"
#include "instruction.h"
#include "memory.h"
#include "operator.h"
#include "register.h"

#define COMMAND_LIMIT 100
#define ARGV_SIZE 3

extern int PC;

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
      loadProgram(argv[1]);
      break;
    case 'j':
      jumpProgram(parseInt(argv[1]));
      break;
    case 'g':
      goProgram();
      break;
    case 's':
      stepProgram();
      break;
    case 'm':
      // 입력 주소의 메모리값 출력
      showMemory(parseInt(argv[1]), parseInt(argv[2]));
      break;
    case 'r':
      // 전체 레지스터값 출력
      showRegister();
      break;
    case 'h':
      helpCommand();
      break;
    case 'b':
      setBreak(parseInt(argv[1]));
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

void loadProgram(char *fileName)
{
  int num_inst = 0; //명령어 개수
  int num_data = 0; //데이터 개수
  FILE *pFile = NULL;
  unsigned char M[100];
  unsigned int DM = 0x10000000;
  PC = 0x400000;
  //파일 오픈
  pFile = fopen(fileName, "rb");
  if (pFile == NULL)
  {
    printf("Cannot open file\n");
    return;
  }
  fread(&num_inst, sizeof(int), 1, pFile);
  fread(&num_data, sizeof(int), 1, pFile);
  num_inst = num_inst >> 24;
  num_data = num_data >> 24;
  printf("Number of Instructions: %d, Number of Data: %d\n", num_inst, num_data);

  // 메모리 로드 (한 번에 1바이트씩)
  for (int i = 0; i < (num_inst * 4); i++)
  {
    unsigned int access_prog = PC + i;
    fread(&M[i], sizeof(M[0]), 1, pFile);
    MEM(access_prog, M[i], 1, 0);
  }
  for (int i = 0; i < (num_data * 4); i++)
  {
    unsigned int access_data = DM + i;
    fread(&M[i], sizeof(M[0]), 1, pFile);
    MEM(access_data, M[i], 1, 0);
  }
  PC = 0x400000;
  REG(29, 0x80000000, 1);
  fclose(pFile);
}

void jumpProgram(unsigned int address)
{
  // PC를 address로 설정
  jumpRegister(address);
}

int stepProgram()
{
  step();
  return 1; // 프로그램 끝났으면 1 반환, 아니면 0 반환
}

void goProgram()
{
  if (PC == 0 || PC == breakPC)
    end = stepProgram();
  while (PC != 0 && PC != breakPC)
  {
    end = stepProgram();
  }
  if (end)
    return;
}

void setBreak(unsigned int addressPC)
{
  breakPC = addressPC;
}

void helpCommand()
{
  printf("usage: <command> <option>\n");
  printf("=====Command List=====\n");
  printf("l <path>\t 해당 경로의 프로그램 로드\n");
  printf("j <address>\t 해당 주소로 PC 점프\n");
  printf("g\t\t 프로그램의 모든 명령어 실행\n");
  printf("s\t\t 프로그램의 명령어 한 줄 실행\n");
  printf("m <start> <end>\t 입력받은 주소의 메모리 값 출력\n");
  printf("r\t\t 레지스터 값 출력\n");
  printf("h\t\t 명령어 help 리스트 출력\n");
  printf("b <PC>\t\t PC값을 break point로 설정\n");
  printf("x\t\t 프로그램 종료\n");
}