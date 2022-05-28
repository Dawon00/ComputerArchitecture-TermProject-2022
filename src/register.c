#include "register.h"
#include "instruction.h"

// access register interface(read & write)
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

// 'r' instruction -> print register
void showRegister()
{
	printf("==========[REGISTER]==========\n");
	for (int i = 0; i < REG_SIZE; i++)
	{
		printf("R%-2d = %x\n", i, REGS[i]);
	}
	printf("PC = 0x%08x\n", PC);
	printf("HI = %x	 LO = %x\n", HI, LO);
	printf("==============================\n");
}

// register 값 모두 0으로 reset
void resetRegister(); //필요 없으면 빼겠음.

// 'sr' instruction -> register 값 설정
void setRegister()
{
	unsigned int where;
	unsigned int value;
	printf("Enter register number and value(number value): ");
	scanf_s("%d %x", &where, &value);
	while (getchar() != '\n')
		;
	REG(where, value, 1);
}

void jumpRegister(unsigned int address)
{
	PC = address;
}