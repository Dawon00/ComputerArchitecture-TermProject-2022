// 메모리에서 PC가 가리키는 명령어 가져오기
union IR instructionFetch();

// R 포맷 명령어
int sll(int rd, int rt, int sh);
int srl(int rd, int rt, int sh);
int sra(int rd, int rt, int sh);
int jr(int rs);
int syscall();
int mfhi(int rd);
int mflo(int rd);
int mul(int rs, int rt);
int add(int rd, int rs, int rt);
int sub(int rd, int rs, int rt);
int and (int rd, int rs, int rt);
int or (int rd, int rs, int rt);
int xor (int rd, int rs, int rt);
int nor(int rd, int rs, int rt);
int slt(int rd, int rs, int rt);

// I 포맷 명령어
int bltz(int rs, int rt, int offset);
int beq(int rs, int rt, int offset);
int bne(int rs, int rt, int offset);
int addi(int rt, int rs, int offset);
int slti(int rt, int rs, int offset);
int andi(int rt, int rs, int offset);
int ori(int rt, int rs, int offset);
int xori(int rt, int rs, int offset);
int lui(int rt, int offset);
int lb(int rt, int offset, int rs);
int lw(int rt, int offset, int rs);
int lbu(int rt, int offset, int rs);
int sb(int rt, int offset, int rs);
int sw(int rt, int offset, int rs);

// J 포맷 명령어
int j(int address);
int jal(int address);