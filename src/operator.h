#ifndef OPERATOR_H
#define OPERATOR_H

#define sll 0
#define srl 2
#define sra 3
#define add 32
#define sub 34
#define and 36
#define or 37
#define xor 38
#define nor 39
#define slt 42

unsigned int ALU(int fct, int v1, int v2); //ALU

int addSubtract(int X, int Y, int C);

int logicOperation(int X, int Y, int C);

//V is 5bit shift amount
int shiftOperation(int V, int Y, int C);

// X < Y ?
int checkSetLess(int X, int Y);

#endif