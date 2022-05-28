unsigned int DM;

// access memory(read & write)
unsigned int MEM(unsigned int A, int V, int nRW, int S);
// pM : memory access pointer
// sel : 메모리에 접근하기 위해 입력받은 주소 값 A의 상위 12bit 저장
// sel 에 따라 program memory/data memory/stack memory 구분
// word size 별로 선택
// nRW 에 따라 read memory / write memory

// 'm' instruction 입력하면 실행
// '<start> <end>' 입력하면 print memory
// start address ~ end address print memory
void showMemory();

// memory address를 value 값으로
void setMemory();


// program memory, data memory, stack memory 값 모두 0으로 reset
void resetMemory();

