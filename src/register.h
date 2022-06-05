#ifndef REGISTER_H
#define REGISTER_H

#define REG_SIZE 32


static char REGISTER[REG_SIZE][6] = {
    "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$g7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};

// Register interface -> access register interface(read & write)
unsigned int REG(unsigned int A, unsigned int V, unsigned int nRW);

// 'r' instruction -> show current register values
void showRegister();

// 'j' instruction -> jump
void jumpRegister(unsigned int address);

//setPC
void setPC(unsigned int pc);

#endif