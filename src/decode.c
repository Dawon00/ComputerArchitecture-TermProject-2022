#include "decode.h"

unsigned int parseInt(char *str)
{
  return strtoul(str, NULL, 10);
}

unsigned int convertEndian(unsigned int endian)
{
  return ((n >> 24) & 0xff) | ((n << 8) & 0xff0000) | ((n >> 8) & 0xff00) | ((n << 24) & 0xff000000);
}
