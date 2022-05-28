#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "decode.h"
#include "instruction.h"
#include "memory.h"
#include "operator.h"
#include "register.h"

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
      // instruction.c 에 있는 goProgram() 사용해주세요.
      break;
    case 's':
      // instruction.c 에 있는 step() 사용해주세요.
      break;
    case 'm':
      // 입력 주소의 메모리값 출력
      // showMemory(unsigned char address);
      break;
    case 'r':
      // 전체 레지스터값 출력
      // showRegister()
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

void loadProgram(char *fileName)
{
  int num_inst = 0; //number of instructions
  int num_data = 0; //number of data
  FILE *pFile = NULL;
  unsigned char M[100]; // for store instruction
  DM = 0x10000000;      // Entry of data memory
  PC = 0x400000;
  //open file
  pFile = fopen(fileName, "rb");
  if (pFile == NULL)
  {
    printf("Cannot open file\n");
    return;
  }
  // get number of instruction & data
  fread(&num_inst, sizeof(int), 1, pFile);
  fread(&num_data, sizeof(int), 1, pFile);
  num_inst = num_inst >> 24; //because of Big-endian
  num_data = num_data >> 24;
  printf("Number of Instructions: %d, Number of Data: %d\n", num_inst, num_data);

  // load on memory(1 byte at a time)
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
  // initialize PC, StackPointer
  setPC(0x400000);
  REG(29, 0x80000000, 1);
  fclose(pFile);
}

// 프로그램 점프하기. j 명령어 입력 시 실행됨
void jumpProgram(unsigned int address)
{
  // PC를 address로 설정
  jumpRegister(address);
}

  // instruction에 구현되어 있는 step 함수를 사용하였음
int stepProgram()
{
  step();
  return 1; // 프로그램 끝났으면 1 반환, 아니면 0 반환
}

  // 프로그램 전체 실행. g 명령어 입력 시 실행됨
void goProgram() {
  if (PC == 0 || PC == breakPC)
	  end = stepProgram();
	while (PC != 0 && PC != breakPC)
	{
	  end = stepProgram();
	}
  if (end) return;
}

  // breakpoint 설정. b 명령어 입력 시 실행됨
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
  printf("m <address>\t 입력받은 주소의 메모리 값 출력\n");
  printf("r\t\t 레지스터 값 출력\n");
  printf("h\t\t 명령어 help 리스트 출력\n");
  printf("b <PC>\t\t PC값을 break point로 설정\n");
  printf("x\t\t 프로그램 종료\n");
}