#include <stdio.h>
#include <stdlib.h>
#include "decode.h"

// str -> unsigned int 변환
unsigned int parseInt(char *str)
{
  return (unsigned int) strtoul(str, NULL, 0);
}

// Endian 변환 (big -> little, little -> big)
unsigned int convertEndian(unsigned int endian)
{
  return ((endian >> 24) & 0xff) | ((endian << 8) & 0xff0000) | ((endian >> 8) & 0xff00) | ((endian << 24) & 0xff000000);
}
