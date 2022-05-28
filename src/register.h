#define REG_SIZE 32

static char REGISTER[REG_SIZE][6] = {
    "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$g7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};

// Memory Register
unsigned int REGS[REG_SIZE];

unsigned int REG(unsigned int A, unsigned int V, unsigned int nRW);
// access register interface(read & write)

void showRegister();
// 'r' instruction -> print register

void resetRegister();
// register 값 모두 0으로 reset

void setRegister();
// 'sr' instruction -> register 값 설정

void jumpRegister(unsigned int address);
// 'j' instruction -> jump
