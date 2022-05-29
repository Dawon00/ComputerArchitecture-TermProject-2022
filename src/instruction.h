unsigned int HI; //HI,LO register
unsigned int LO;
unsigned int PC;      //PC register
unsigned int breakPC; //break point
unsigned int DM;      //Entry of data memory
int end;              //goProgram

typedef union IR
{ //union for instruction decoding
    struct RFormat
    {
        unsigned int funct : 6;
        unsigned int shamt : 5;
        unsigned int rd : 5;
        unsigned int rt : 5;
        unsigned int rs : 5;
        unsigned int opcode : 6;
    } RF; //R-Type Instruction
    struct IFormat
    {
        int immediate : 16;
        unsigned int rt : 5;
        unsigned int rs : 5;
        unsigned int opcode : 6;
    } IF; //I-Type Instruction
    struct JFormat
    {
        unsigned int address : 26;
        unsigned int opcode : 6;
    } JF; //J-Type Instruction
    unsigned int I;
} Instruction; //Instruction Register

// 메모리에서 PC가 가리키는 명령어 가져오기
union IR instructionFetch(); //필요없으면 빼겠음.

void step();