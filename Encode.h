#pragma once
#ifndef __ENCODE_H__
#define __ENCODE_H__

#include "KeyExpasion.h"
namespace AES
{
// S box变换
void SubBytes(byte mtx[4*4])
{
    for(int i = 0; i < 16; ++ i)
    {
        int row = mtx[i][7] * 8+ mtx[i][6] * 4 + mtx[i][5] * 2 + mtx[i][4];
        int col = mtx[i][3] * 8+ mtx[i][2] * 4 + mtx[i][1] * 2 + mtx[i][0];
        mtx[i] = S_box[row][col];
    }
}
//行变换，第2行移动一次，第3行移动2次，第4行移动3次
void ShiftRow(byte mtx[4*4])
{
#ifdef HELLO
    byte temp[3] = { 0 };
    for(int i = 1; i < 4; ++ i){
        int j = 0,k = 0;
        for(j = 0;j < i; ++j)
        {
            temp[j] = mtx[4*i + j];
        }
        for(k=0;j<4;++j,++k){
            mtx[4*i+k] = mtx[4*i+j];
        }
        for(j=0;k<4;++k,++j)
        {
            mtx[4*i+k] = temp[j];
        }
    }
#endif
    byte temp = mtx[4];
    for(int i = 0; i<3; ++i)
        mtx[4+i] = mtx[5+i];
    mtx[7] = temp;
    for(int i = 0; i<3; ++i){
        temp = mtx[8 + i];
        mtx[8+i] = mtx[10+i];
        mtx[10+i] = temp;
    }
    temp = mtx[15];
    for(int i = 14; i > 1; --i)
    {
        mtx[i+1] = mtx[i];
    }
    mtx[12] = temp;
}
//GF有限域域乘法
//It employs the following reducing polynomial for multiplication:x^8 + x^4 + x^3 + x + 1.
//example:
//x^13 + x^12 + x^11 + x^10 + x^9 + x^8 + x^6 + x^5 + x^4 + x^3 + x^2 + x modulo x^8 + x^4 + x^3 + x^1 + 1
//= (11111101111110 mod 100011011) = {3F7E mod 11B} = {01} = 1 
byte GFMulti(byte a, byte b)
{
    byte p = 0;  
    byte hi_bit_set;  
    for (int counter = 0; counter < 8; counter++) {  
        if ((b & byte(1)) != 0) {  
            p ^= a;  
        }  
        hi_bit_set = (byte) (a & byte(0x80));  
        a <<= 1;  
        if (hi_bit_set != 0) {  
            a ^= 0x1b; /* x^8 + x^4 + x^3 + x + 1 */  
        }  
        b >>= 1;  
    }  
    return p;
}
//列变换
void MixColumns(byte mtx[4*4])  
{  
    byte arr[4];  
    for(int i=0; i<4; ++i)  
    {  
        for(int j=0; j<4; ++j)  
            arr[j] = mtx[i+j*4];  
  
        mtx[i] = GFMulti(0x02, arr[0]) ^ GFMulti(0x03, arr[1]) ^ arr[2] ^ arr[3];  
        mtx[i+4] = arr[0] ^ GFMulti(0x02, arr[1]) ^ GFMulti(0x03, arr[2]) ^ arr[3];  
        mtx[i+8] = arr[0] ^ arr[1] ^ GFMulti(0x02, arr[2]) ^ GFMulti(0x03, arr[3]);  
        mtx[i+12] = GFMulti(0x03, arr[0]) ^ arr[1] ^ arr[2] ^ GFMulti(0x02, arr[3]);  
    }  
} 
//轮秘钥转换，每一列与扩展秘钥进行转换
void AddRoundKey(byte mtx[4*4], word k[4])  
{  
    for(int i=0; i<4; ++i)  
    {  
        word k1 = k[i] >> 24;  
        word k2 = (k[i] << 8) >> 24;  
        word k3 = (k[i] << 16) >> 24;  
        word k4 = (k[i] << 24) >> 24;  
          
        mtx[i] = mtx[i] ^ byte(k1.to_ulong());  
        mtx[i+4] = mtx[i+4] ^ byte(k2.to_ulong());  
        mtx[i+8] = mtx[i+8] ^ byte(k3.to_ulong());  
        mtx[i+12] = mtx[i+12] ^ byte(k4.to_ulong());  
    }  
} 
}//end of AES

#endif
