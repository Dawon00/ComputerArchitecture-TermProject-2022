#define REGISTER_SIZE 32
int PC = 0x400000;
int HI = 0;
int LO = 0;

static char REGISTER[REGISTER_SIZE][6] = {
    "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$g7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};

// access register interface(read & write)
unsigned int REG(unsigned int A, unsigned int V, unsigned int nRW){
  if (A > REGISTER_SIZE - 1) {
		printf("Wrong access to register\n");
		exit(1);
	}
	if (nRW == 0)	//read
		return REGISTER[A];
	else if(nRW == 1)	//write
		REGISTER[A] = V;
	return 0;
}


// 'r' instruction -> print register
void showRegister(){
  	printf("==========[REGISTER]==========\n");
	for (int i = 0; i < REGISTER_SIZE; i++)
	{
		printf("R%-2d = %x\n", i, REGISTER[i]);
	}
	printf("PC = 0x%08x\n", PC);
	printf("HI = %x	 LO = %x\n", HI, LO);
	printf("==============================\n");
}

// register 값 모두 0으로 reset
void resetRegister();

// 'sr' instruction -> register 값 설정
void setRegister(unsigned int number, int value){
		REG(number, value, 1);
}

