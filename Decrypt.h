#pragma once
#ifndef __DECRYPT_H__
#define __DECRYPT_H__

#include "Decode.h"
namespace AES
{
void decrypt(byte in[4*4], word w[4*(Nr+1)])
{
    word key[4];
    for(int i=0; i<4; ++i)
        key[i] = w[4*Nr+i];
    AddRoundKey(in,key);
    for(int round= Nr-1; round>0; --round)
    {
        InvShiftRows(in);
        InvSubBytes(in);
        for(int i=0; i<4; ++i)
            key[i] = w[4*round+i];
        AddRoundKey(in,key);
        InvMixColumns(in);
    }
    InvShiftRows(in);
    InvSubBytes(in);
    for(int i =0; i<4; ++i)
        key[i] = w[i];
    AddRoundKey(in,key);
}
}//namespace AES
#endif
