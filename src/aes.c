#include <stdio.h>
#include <string.h>
#include "AES_parser.h"
#include "maths.h"
#include "cipher_modes.h"

char defaultKey[67]="0x000102030405060708090a0b0c0d0e0f";
int keysize=128;


int main(int argc,char* argv[]){

  parser(argc,argv);
  char* Key=defaultKey;
  defaultKey[35]='\0';

  if(cipher==1){
    if(blockCiphering==1){ //ecb mode
      if(gotKey==0){
        FILE* keyFile=fopen(argv[keyFileNameIndex],"r");
        if(keyFile==NULL){
          printf("trouble opening file containing key\n");
          exit(0);
        }
        int count=0;
        while(!feof(keyFile)){
          char c=fgetc(keyFile);
          if(!feof(keyFile)){
            Key[count]=c;
            ++count;
          }
          
        }
        Key[count]='\0';
        keysize=(count-1)*4;
        fclose(keyFile);
      }
      if(gotKey==1)
      {
        Key=argv[keyIndex];
      }
      printf("input : %s \n",argv[inputFileNameIndex]);
      printf("output : %s \n",argv[outputFileNameIndex]);
      if(hexMode)
        ECB_Mode_Cipher_hex(Key,argv[inputFileNameIndex],argv[outputFileNameIndex]);
      else
        ECB_Mode_Cipher(Key,argv[inputFileNameIndex],argv[outputFileNameIndex]);
    }

    if(blockCiphering==2){ //GCM mode
      /*projet à continuer*/
    }
  }

  if(cipher==2){
    if(blockCiphering==1){ //ecb mode
      if(gotKey==0){
        FILE* keyFile=fopen(argv[keyFileNameIndex],"r");
        if(keyFile==NULL){
          printf("trouble opening file containing key\n");
          exit(0);
        }
        int count=0;
        while(!feof(keyFile)){
          char c=fgetc(keyFile);
          if(!feof(keyFile)){
            Key[count]=c;
            ++count;
          }
        }
        Key[count]='\0';
        keysize=(count-1)*4;
        fclose(keyFile);
      }
      if(gotKey==1)
      {
        Key=argv[keyIndex];
      }
      printf("input : %s \n",argv[inputFileNameIndex]);
      printf("output : %s \n",argv[outputFileNameIndex]);
      if(hexMode)
        ECB_Mode_Decipher_fromhex(Key,argv[inputFileNameIndex],argv[outputFileNameIndex]);
      else
        ECB_Mode_Decipher(Key,argv[inputFileNameIndex],argv[outputFileNameIndex]);
    
    }
    if(blockCiphering==2){ //GCM mode
      /*projet à continuer */
    }

  }

  return 0;
}
