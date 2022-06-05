#include <stdio.h>
#include <stdlib.h>
#include "register.h"
#include "instruction.h"


int HI; //HI,LO register
int LO;
int PC; //PC register

// Memory Register
unsigned int REGS[REG_SIZE];

// Register interface -> access register interface(read & write)
unsigned int REG(unsigned int A, unsigned int V, unsigned int nRW)
{
	if (A > REG_SIZE - 1)
	{
		printf("Wrong access to register\n");
		exit(1);
	}
	if (nRW == 0) //read
		return REGS[A];
	else if (nRW == 1) //write
		REGS[A] = V;
	return 0;
}

// 'r' instruction -> show current register values
void showRegister()
{
	printf("==========[REGISTER]==========\n");
	for (int i = 0; i < REG_SIZE; i++)
	{
		char *name = REGISTER[i];
		printf("%s   %x\n", name, REGS[i]);
	}
	printf("PC    %x\n", PC);
	printf("HI    %x\n", HI);
	printf("LO    %x\n", LO);
	printf("==============================\n");
}

// 'j' instruction -> jump
void jumpRegister(unsigned int address)
{
	PC = address;
}

//setPC
void setPC(unsigned int pc)
{
	PC = pc;
}