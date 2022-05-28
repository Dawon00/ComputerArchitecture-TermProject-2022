#include "operator.h"
// sll/srl/sra -> shiftOperation
// add/sub -> addSubtract
// and/or/xor/nor -> logicOperation
// slt -> checkSetLess
unsigned int ALU(int fct, int v1, int v2) {
	unsigned int ret = 0;
	switch (fct) {
	case sll: case srl: case sra:
		ret = shiftOperation(v2, v1, fct);	break;
	case add: case sub:
		ret = addSubtract(v1, v2, fct);	break;
	case and: case or: case xor: case nor:
		ret = logicOperation(v1, v2, fct);	break;
	case slt:
		ret = checkSetLess(v1,v2);	break;
	}
	return ret;
}


int addSubtract(int X, int Y, int C){
	int ret = 0;
	if (C == add)	//add
		ret = X + Y;
	else if (C == sub)	//subtract
		ret = X - Y;
	else
		printf("error in addSubtract operation\n");
	return ret;
}

int logicOperation(int X, int Y, int C){
	int ret = 0;
	if (C == and)
		ret = X & Y;
	else if (C == or)
		ret = X | Y;
	else if (C == xor)
		ret = X ^ Y;
	else if (C == nor)
		ret = ~(X | Y);
	else
		printf("error in logic operation\n");
	return ret;
}


//V is 5bit shift amount
int shiftOperation(int V, int Y, int C){
  	int ret = 0;
	if (C == sll)	//shift left logical
		ret = (unsigned int)Y << V;
	else if (C == srl)	//shift right logical
		ret = (unsigned int)Y >> V;
	else if (C == sra)	//shift right arithmetic
		ret = Y >> V;
	else
		printf("error in shift operation\n");
	return ret;
}

// X < Y ?
int checkSetLess(int X, int Y){
	return (X < Y);
}

// if S is 0, Z = 1
int isZero(int S, int *Z); //필요없으면 빼겠음.