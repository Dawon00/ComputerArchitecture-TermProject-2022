unsigned int DM;

unsigned int MEM(unsigned int A, int V, int nRW, int S);
// access memory(read & write)
// pM : memory access pointer
// sel : 메모리에 접근하기 위해 입력받은 주소 값 A의 상위 12bit 저장
// sel 에 따라 program memory/data memory/stack memory 구분
// word size 별로 선택
// nRW 에 따라 read memory / write memory


void showMemory();
// 'm <start> <end>' -> print memory
// start address ~ end address print memory

void setMemory();
// setmemory instruction -> memory address를 value 값으로

void resetMemory();
// program memory, data memory, stack memory 값 모두 0으로 reset
