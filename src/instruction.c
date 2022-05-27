#include "instruction.h"
#include "operator.h"

extern int PC, HI, LO;


void goProgram()
{
  if (PC == 0 || PC == breakPC)
    step();
  while (PC != 0 && PC != breakPC)
  {
    step();
  }
}

void step()
{
  Instruction IR = {
      0,
  };                        //union variable for instruction decoding
  char *instruction = NULL; //mips instruction
  char printType = 0;       //instruction type
  // instruction fetch
  if (PC == 0)
    setPC(0x400000);
  printf("PC = 0x%08x : ", PC);
  IR.I = MEM(PC, 0, 0, 2);
  PC += 4;
  // instruction decode
  //R-Type Instruction
  if (IR.RF.opcode == 0)
  {
    switch (IR.RF.funct)
    {
      //shift print type(s)
    case 0:
      instruction = "sll";
      REG(IR.RF.rd, ALU(sll, REG(IR.RF.rt, 0, 0), IR.RF.shamt), 1);
      break;
    case 2:
      instruction = "srl";
      REG(IR.RF.rd, ALU(srl, REG(IR.RF.rt, 0, 0), IR.RF.shamt), 1);
      break;
    case 3:
      instruction = "sra";
      REG(IR.RF.rd, ALU(sra, REG(IR.RF.rt, 0, 0), IR.RF.shamt), 1);
      break;
      //jr print type(r)
    case 8:
      instruction = "jr";
      setPC(REG(IR.RF.rs, 0, 0));
      break;
      //move from HI,LO prit type(f)
    case 16:
      instruction = "mfhi";
      REG(IR.RF.rd, HI, 1);
      break;
    case 18:
      instruction = "mflo";
      REG(IR.RF.rd, LO, 1);
      break;
      //mul print type(m)
    case 24:
      instruction = "mult";
      unsigned int mul = REG(IR.RF.rs, 0, 0) * REG(IR.RF.rt, 0, 0);
      HI = mul;
      LO = mul;
      //arith print type(a)
    case 32:
      instruction = "add";
      REG(IR.RF.rd, ALU(add, REG(IR.RF.rs, 0, 0), REG(IR.RF.rt, 0, 0)), 1);
      break;
    case 34:
      instruction = "sub";
      REG(IR.RF.rd, ALU(sub, REG(IR.RF.rs, 0, 0), REG(IR.RF.rt, 0, 0)), 1);
      break;
    case 36:
      instruction = "and";
      REG(IR.RF.rd, ALU(and, REG(IR.RF.rs, 0, 0), REG(IR.RF.rt, 0, 0)), 1);
      break;
    case 37:
      instruction = "or";
      REG(IR.RF.rd, ALU(or, REG(IR.RF.rs, 0, 0), REG(IR.RF.rt, 0, 0)), 1);
      break;
    case 38:
      instruction = "xor";
      REG(IR.RF.rd, ALU(xor, REG(IR.RF.rs, 0, 0), REG(IR.RF.rt, 0, 0)), 1);
      break;
    case 39:
      instruction = "nor";
      REG(IR.RF.rd, ALU(nor, REG(IR.RF.rs, 0, 0), REG(IR.RF.rt, 0, 0)), 1);
      break;
    case 42:
      instruction = "slt";
      if (ALU(slt, REG(IR.RF.rs, 0, 0), REG(IR.RF.rt, 0, 0)))
        REG(IR.RF.rd, 1, 1);
      else
        REG(IR.RF.rd, 0, 1);
      //syscall print type(c)
    default:
      instruction = "syscall";
      if (REG(2, 0, 0) == 10)
        setPC(0); //if syscall 10 -> end program
    }
    //assign print type
    if (IR.RF.funct <= 3)
      printType = 's';
    else if (IR.RF.funct == 8)
      printType = 'r';
    else if (IR.RF.funct == 12)
      printType = 'c';
    else if (IR.RF.funct == 16 || IR.RF.funct == 18)
      printType = 'f';
    else if (IR.RF.funct == 24)
      printType = 'm';
    else
      printType = 'a';
  }
  //J-Type Instruction
  else if (IR.JF.opcode == 2 || IR.JF.opcode == 3)
  {
    if (IR.JF.opcode == 2)
    {
      instruction = "j";
      setPC(IR.JF.address << 2);
    }
    else if (IR.JF.opcode == 3)
    {
      instruction = "jal";
      REG(31, PC, 1); //store current PC in R31($ra)
      setPC(IR.JF.address << 2);
    }
    printType = 'j';
  }
  //I-Type Instruction
  else
  {
    unsigned int base = REG(IR.IF.rs, 0, 0); //base register
    switch (IR.IF.opcode)
    {
    //branch less than zero print type(z)
    case 1:
      instruction = "bltz";
      if (ALU(slt, REG(IR.IF.rs, 0, 0), 0)) //rs < 0
        setPC(PC + (IR.IF.immediate << 2));
    //branch print type(b)
    case 4:
      instruction = "beq";
      if (ALU(sub, REG(IR.IF.rs, 0, 0), REG(IR.IF.rt, 0, 0)) == 0) //rs == rt
        setPC(PC + (IR.IF.immediate << 2));
      break;
    case 5:
      instruction = "bne";
      if (ALU(sub, REG(IR.IF.rs, 0, 0), REG(IR.IF.rt, 0, 0)) != 0) //rs != rt
        setPC(PC + (IR.IF.immediate << 2));
      break;
    //immediate print type(i)
    case 8:
      instruction = "addi";
      REG(IR.IF.rt, ALU(add, REG(IR.IF.rs, 0, 0), (short)IR.IF.immediate), 1);
      break;
    case 10:
      instruction = "slti";
      if (ALU(slt, REG(IR.IF.rs, 0, 0), (short)IR.IF.immediate))
        REG(IR.IF.rt, 1, 1);
      else
        REG(IR.IF.rt, 0, 1);
      break;
    case 12:
      instruction = "andi";
      REG(IR.IF.rt, ALU(and, REG(IR.IF.rs, 0, 0), (unsigned short)IR.IF.immediate), 1);
      break;
    case 13:
      instruction = "ori";
      REG(IR.IF.rt, ALU(or, REG(IR.IF.rs, 0, 0), (unsigned short)IR.IF.immediate), 1);
      break;
    case 14:
      instruction = "xori";
      REG(IR.IF.rt, ALU(xor, REG(IR.IF.rs, 0, 0), (unsigned short)IR.IF.immediate), 1);
      break;
    //data transfer print type(d)
    case 32:
      instruction = "lb";
      REG(IR.IF.rt, (char)(MEM(ALU(add, base, IR.IF.immediate), 0, 0, 0)), 1);
      break;
    case 35:
      instruction = "lw";
      REG(IR.IF.rt, MEM(base + IR.IF.immediate, 0, 0, 2), 1);
      break;
    case 36:
      instruction = "lbu";
      REG(IR.IF.rt, (unsigned char)(MEM(ALU(add, base, IR.IF.immediate), 0, 0, 0)), 1);
      break;
    case 40:
      instruction = "sb";
      (char)(MEM(ALU(add, base, IR.IF.immediate), REG(IR.IF.rt, 0, 0), 1, 0));
      break;
    case 43:
      instruction = "sw";
      MEM(ALU(add, base, IR.IF.immediate), REG(IR.IF.rt, 0, 0), 1, 2);
      break;
    //lui print type(l)
    default:
      instruction = "lui";
      REG(IR.IF.rt, ((short)IR.IF.immediate) << 16, 1);
    }
    //assign print type
    if (IR.IF.opcode == 1)
      printType = 'z';
    else if (IR.IF.opcode == 4 || IR.IF.opcode == 5)
      printType = 'b';
    else if (IR.IF.opcode >= 8 && IR.IF.opcode <= 14)
      printType = 'i';
    else if (IR.IF.opcode == 15)
      printType = 'l';
    else
      printType = 'd';
  }

  //print type에 따라 형식을 달리하여 명령어 출력
  if (printType == 's')
  { //shift
    printf("%3s $%d, $%d, %d\t|\t", instruction, IR.RF.rd, IR.RF.rt, IR.RF.shamt);
    printf("After instruction: R%-2d = %x\n", IR.RF.rd, REG(IR.RF.rd, 0, 0));
  }
  else if (printType == 'r') //jr
    printf("%3s $%d\n", instruction, IR.RF.rs);
  else if (printType == 'c') //syscall
    printf("%3s %d\n", instruction, REG(2, 0, 0));
  else if (printType == 'f')
  { //move from HI,LO
    printf("%3s $%d\t|\t", instruction, IR.RF.rd);
    printf("After instruction: R%-2d = %x", IR.RF.rd, REG(IR.RF.rd, 0, 0));
  }
  else if (printType == 'm')
  { //mul
    printf("%3s $%d $%d\t|\t", instruction, IR.RF.rs, IR.RF.rt);
    printf("After instruction: HI=%x, LO=%x\n", HI, LO);
  }
  else if (printType == 'a')
  { //arith
    printf("%3s $%d, $%d, $%d\t|\t", instruction, IR.RF.rd, IR.RF.rs, IR.RF.rt);
    printf("After instruction: R%-2d = %x\n", IR.RF.rd, REG(IR.RF.rd, 0, 0));
  }
  else if (printType == 'j')
  { //jump
    if (IR.JF.opcode == 3)
    {
      printf("%3s 0x%08x\t|\t", instruction, IR.JF.address << 2);
      printf("After instruction: R31 = %x\n", REG(31, 0, 0));
    }
    else
      printf("%3s 0x%08x\n", instruction, IR.JF.address << 2);
  }
  else if (printType == 'z') //branch less than zero
    printf("%3s $%d %d\t|\t", instruction, IR.IF.rs, IR.IF.immediate << 2);
  else if (printType == 'b') //branch
    printf("%3s $%d, $%d, %d\n", instruction, IR.IF.rs, IR.IF.rt, IR.IF.immediate << 2);
  else if (printType == 'i')
  { //immediate
    printf("%3s $%d, $%d, %-6d\t|\t", instruction, IR.IF.rt, IR.IF.rs, IR.IF.immediate);
    printf("After instruction: R%-2d = %x\n", IR.IF.rt, REG(IR.IF.rt, 0, 0));
  }
  else if (printType == 'l')
  { //lui
    printf("%3s $%d, %-6d\t|\t", instruction, IR.IF.rt, IR.IF.immediate);
    printf("After instruction: R%-2d = %x\n", IR.IF.rt, REG(IR.IF.rt, 0, 0));
  }
  else if (printType == 'd')
  { //data transfer instruction
    printf("%3s $%d, %d($%d)\t|\t", instruction, IR.IF.rt, IR.IF.immediate, IR.IF.rs);
    unsigned int base = REG(IR.IF.rs, 0, 0);
    if (IR.IF.opcode == 43)
      printf("After instruction: MEM[0x%0x] = %08x\n", ALU(add, base, IR.IF.immediate), MEM(ALU(add, base, IR.IF.immediate), 0, 0, 2));
    else if (IR.IF.opcode == 40)
      printf("After instruction: MEM[0x%0x] = %c\n", ALU(add, base, IR.IF.immediate), (char)(MEM(ALU(add, base, IR.IF.immediate), 0, 0, 0)));
    else
      printf("After instruction: R%-2d = %x\n", IR.IF.rt, REG(IR.IF.rt, 0, 0));
  }
  IR.I = 0;
  printf("\n");
}