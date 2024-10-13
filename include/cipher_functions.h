#ifndef CIPHER_FUNCTIONS_H
#define CIPHER_FUNCTIONS_H

#include "maths.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



void setState(Byte* s);
void outState(Byte* s);
void SubBytes();
void ShiftRows();
void MixColumns();
void AddRoundKey(Byte* rKey);
void SubWord(Byte* word);
void RotWord(Byte* word);
void takeKey(Byte* K,int size);
int throwKeys();
void Cipher(Byte* block);
int readKey(char* k);
void AES(Byte* block,char* k);

void invMixColumns();
void invShiftRows();
void invSubBytes();

void deCipher(Byte* block);
void invAES(Byte* block,char* k);


#endif