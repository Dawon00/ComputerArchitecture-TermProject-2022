#define REG_SIZE 32

static char REGISTER[REG_SIZE][6] = {
    "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$g7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};

// Memory Register
unsigned int REGS[REG_SIZE];
// PC, HI, LO
unsigned int PC, HI, LO;
// Instruction Register
union IR
{
    // 명령어 전체 비트 변수
    unsigned int I;

    struct RFormat
    {
        unsigned int funct : 6;
        unsigned int sh : 5;
        unsigned int rd : 5;
        unsigned int rt : 5;
        unsigned int rs : 5;
        unsigned int op : 6;
    } RF;

    struct IFormat
    {
        int operand : 16;
        unsigned int rt : 5;
        unsigned int rs : 5;
        unsigned int op : 6;
    } IF;

    struct JFormat
    {
        unsigned int address : 26;
        unsigned int op : 6;
    } JF;
};

unsigned int REG(unsigned int A, unsigned int V, unsigned int nRW);
// access register interface(read & write)

void showRegister();
// 'r' instruction -> print register

void resetRegister();
// register 값 모두 0으로 reset

void setRegister(unsigned int number, int value);
// 'sr' instruction -> register 값 설정

void jumpRegister(unsigned int address);
// 'j' instruction -> jump
