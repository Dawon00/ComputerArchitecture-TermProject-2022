#include <stdio.h>
#include "decode.h"

unsigned int parseInt(char *str)
{
  return strtoul(str, NULL, 10);
}

unsigned int convertEndian(unsigned int endian)
{
  return ((endian >> 24) & 0xff) | ((endian << 8) & 0xff0000) | ((endian >> 8) & 0xff00) | ((endian << 24) & 0xff000000);
}
