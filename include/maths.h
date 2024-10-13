#ifndef MATHS_H
#define MATHS_H

typedef unsigned char Byte;

Byte xtime(Byte byte);
Byte multByte(Byte byte1,Byte byte2);
void multPolynomials(Byte* A,Byte* B,Byte* res);
void xor128(Byte *p1,Byte *p2,Byte *res);
void xtime_GF128(Byte *p,Byte *res);

#endif