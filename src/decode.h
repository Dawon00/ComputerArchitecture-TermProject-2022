#include <stdio.h>

// 명령어 저장 union
union IR
{
  // 명령어 전체 비트 변수
  unsigned int I;

  struct RFormat
  {
    unsigned int funct : 6;
    unsigned int sh : 5;
    unsigned int rd : 5;
    unsigned int rt : 5;
    unsigned int rs : 5;
    unsigned int op : 6;
  } RF;

  struct IFormat
  {
    int operand : 16;
    unsigned int rt : 5;
    unsigned int rs : 5;
    unsigned int op : 6;
  } IF;

  struct JFormat
  {
    unsigned int address : 26;
    unsigned int op : 6;
  } JF;
};

// str -> unsigned int 변환
unsigned int parseInt(char *str);

// Endian 변환 (big -> little, little -> big)
unsigned int convertEndian(unsigned int endian);
