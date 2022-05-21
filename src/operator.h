enum ALU_OPS
{
  ALU_NO_SHIFT,
  ALU_SLL,
  ALU_SRL,
  ALU_SRA,
  ALU_SET_LESS,
  ALU_ADD = 8,
  ALU_SUBTRACT,
  ALU_AND = 12,
  ALU_OR,
  ALU_XOR,
  ALU_NOR
};

int ALU(int X, int Y, int S, int *Z);
