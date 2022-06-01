#include <stdio.h>
#include <stdlib.h>
#include "decode.h"

unsigned int parseInt(char *str)
{
  return (unsigned int) strtoul(str, NULL, 0);
}

unsigned int convertEndian(unsigned int endian)
{
  return ((endian >> 24) & 0xff) | ((endian << 8) & 0xff0000) | ((endian >> 8) & 0xff00) | ((endian << 24) & 0xff000000);
}
