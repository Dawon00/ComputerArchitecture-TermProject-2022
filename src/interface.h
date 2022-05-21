#include <stdio.h>

// 입력받은 명령어 포인터에 저장 (0: 성공, 1: 실패)
int readCommand(char **command);

// 프로그램 불러오기. l 명령어 입력 시 실행됨
// 하는 일: 1. 파일을 읽기, 2. PC, 레지스터, 메모리 초기화 3. 파일 내용을 메모리에 적재
void loadProgram(const char *filename);

// 명령어 한 단계 씩 실행. s 명령어 입력 시 실행됨
int stepProgram();

// 프로그램 전체 실행. g 명령어 입력 시 실행됨
void goProgram();

//breakpoint 설정
void setbreak();