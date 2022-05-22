// 입력받은 문자열(명령어) 저장 후 문자열 길이 반환
int readCommand(char *command);

// 명령어 문자열 파싱 (argc 반환)
int parseCommand(char *command, char **argv);

// 프로그램 불러오기. l 명령어 입력 시 실행됨
// 하는 일: 1. 파일을 읽기, 2. PC, 레지스터, 메모리 초기화 3. 파일 내용을 메모리에 적재
void loadProgram(const char *filename);

// 명령어 한 단계 씩 실행. s 명령어 입력 시 실행됨
int stepProgram();

// 프로그램 전체 실행. g 명령어 입력 시 실행됨
void goProgram();

//breakpoint 설정
void setBreak();

// 명령어 help 리스트 출력
void helpCommand();
