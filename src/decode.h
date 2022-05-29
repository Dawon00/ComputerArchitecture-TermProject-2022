#ifndef DECODE_H
#define DECODE_H

// str -> unsigned int 변환
unsigned int parseInt(char *str);

// Endian 변환 (big -> little, little -> big)
unsigned int convertEndian(unsigned int endian);

#endif