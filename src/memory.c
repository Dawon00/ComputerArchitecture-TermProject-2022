// access memory(read & write)
unsigned int MEM(unsigned int A, int V, int nRW, int S){
  unsigned int sel, offset;
  unsigned char* pM;// pM : memory access pointer
  sel = A >> 20; // sel : 메모리에 접근하기 위해 입력받은 주소 값 A의 상위 12bit 저장
  offset = A >> 20;

  // sel 에 따라 program memory/data memory/stack memory 구분
	if (sel == 0x004) pM = progMEM;	//program memory
	else if (sel == 0x100) pM = dataMEM;	//data memory
	else if (sel == 0x7FF) pM = stackMEM;	//stack memory
	else {
		printf("[ERROR] No memory\n");
		exit(1);
	}
	pM += offset;	//해당 메모리에서 offset 만큼 포인터 이동

  // word size 별로 선택
  // nRW 에 따라 read memory / write memory
	if (S == 0) {	//byte
		if (nRW == 0) 	//read
			return *pM;
		else if (nRW == 1) 	//write
			*pM = V;
	}

	else if (S == 1) {	//half word
		if (offset % 2 != 0) {	//잘못된 변위로 접근 시 에러문 출력
			printf("[ERROR] wrong access in half word");
			exit(1);
		}
		if (nRW == 0) 	//read
			return ((short)(*pM << 8) + *(pM + 1));	//Big-endian 방식 read
		else if (nRW == 1) 	//write
			*pM = V >> 8;	*(pM + 1) = V;	//Big-endian 방식 write
	}

	else if (S == 2) {	//word
		if (offset % 4 != 0) {	//잘못된 변위로 접근 시 에러문 출력
			printf("[ERROR] wrong access in word");
			exit(1);
		}
		if (nRW == 0) 	//read
			return ((int)(*pM << 24) + (*(pM + 1) << 16) + (*(pM + 2) << 8) + *(pM + 3));
		else if (nRW == 1) 	//write
			*pM = V >> 24; *(pM + 1) = V >> 16; *(pM + 2) = V >> 8; *(pM + 3) = V;
	}


	else {	//error
		printf("[ERROR] Size error\n");
		exit(1);
	}
	return 0;

}

// 'sm' instruction -> memory address를 value 값으로
void setMemory(unsigned int address, int value){
  	printf("Enter memory address and value(address value): ");
		scanf_s("%x %x", &where, &value);
		while (getchar() != '\n')
			;
		MEM(where, value, 1, 2);
}

// program memory, data memory, stack memory 값 모두 0으로 reset
void resetMemory();


// 'm <start> <end>' -> print memory
// start address ~ end address print memory
void showMemory(){
  unsigned int start = 0;
	unsigned int end = 0;
	printf("Enter centain range of memory to show(start end): ");
	scanf_s("%x %x", &start, &end);
	while (getchar() != '\n')
		; //flush input buffer
	printf("==========[MEMORY]==========\n");
	//show memory value from start to end(1 byte at a time)
	for (unsigned int i = start; i <= end; i += 4)
	{
		printf("MEM[0x%0x] -> %x\n", i, MEM(i, 0, 0, 2));
	}
	printf("============================\n");
}
