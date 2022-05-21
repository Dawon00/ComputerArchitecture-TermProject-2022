unsigned int ALU(int X, int Y, int S, int *Z);
// sll/srl/sra -> shiftOperation
// add/sub -> addSubtract
// and/or/xor/nor -> logicOperation
// slt -> checkSetLess

int addSubtract(int X, int Y, int C);

int logicOperation(int X, int Y, int C);

//V is 5bit shift amount
int shiftOperation(int V, int Y, int C);

int checkSetLess(int X, int Y);
// X < Y ?

int isZero(int S, int *Z);
// if S is 0, Z = 1


