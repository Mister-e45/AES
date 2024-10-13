#include "maths.h"
#include <stdio.h>

//P=x^8+x^4+x^3+x+1

static Byte BitMasks[9]={0x0,0x1, 0x2 , 0x4 ,0x8 ,0x10 , 0x20, 0x40, 0x80}; //first element is equal to 0 to have a more natural indexation
static unsigned int x8=0x1b; // representation of x^8 mod P
static Byte polynomial[4]={0x0,0x0,0x0,0x0}; //used in multPolynomials to temporarily store the result 
// multiplication by x mod P=x^8+x^4+x^3+x+1 with elements unsigned char (Byte) representing the polynomials (the left-most bits a the highest degree terms)
Byte xtime(Byte byte){
    return ( (byte & BitMasks[8]) == 0)? (Byte)( byte<<1) :(Byte)( ((byte<<1)^x8) );
}

// multiplication of two Bytes(unsigned char) as defined in AES 
Byte multByte(Byte byte1,Byte byte2){
    
    Byte res=0;
    Byte p=byte2;
    for(int i=1; i<=8 ;++i){
        if( BitMasks[i] & byte1){
            res=res ^ p;
        }
        
        p=xtime(p);
    }
    return res;
}

/*multiplicaction of two polynomials mod x^4+1 with coeficients being in F2[X]/P (represented by Byte type)
params are two pointers to 4 elements arrays of Bytes result is stored in res
*/
void multPolynomials(Byte* A,Byte* B,Byte* res){  
    //polynomial will have values as defined in FIPS-197 page 13
    //it contains coefficients of the multiplication mod x^4+1
    res[0]=multByte(A[0],B[0]) ^ multByte(A[3],B[1]) ^ multByte(A[2],B[2]) ^ multByte(A[1],B[3]);
    res[1]=multByte(A[1],B[0]) ^ multByte(A[0],B[1]) ^ multByte(A[3],B[2]) ^ multByte(A[2],B[3]);
    res[2]=multByte(A[2],B[0]) ^ multByte(A[1],B[1]) ^ multByte(A[0],B[2]) ^ multByte(A[3],B[3]);
    res[3]=multByte(A[3],B[0]) ^ multByte(A[2],B[1]) ^ multByte(A[1],B[2]) ^ multByte(A[0],B[3]);
} 

// for gcm the field is GF(2^128) by quotient of f=1+x+x^2+x^7+x^128

static Byte xmodf =0x87; // represents the polynomial f




void xor128(Byte* p1,Byte* p2,Byte* *res){
    for(int i=0;i<16;++i){
        res[i] = p1[i] ^ p2[i];
    }
}

void xtime_GF128(Byte* p,Byte *res){ 
    int carry=0;
    for(int i=15;i>-1;--i){
        if(carry){
            carry= p[i] & 0x80;
            res[i]=p[i]<<1;
            ++res[i];
        }
        else{
            carry= p[i] & 0x80;
            res[i]=p[i]<<=1;
        }
    }
    if(carry){
        res[15] ^= xmodf;
    }

}
