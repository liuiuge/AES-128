#pragma once
#ifndef __ENCRYPT_H__
#define __ENCRYPT_H__

#include "KeyExpasion.h"
#include "Encode.h"
namespace AES
{
void encrypt(byte in[4*4], word w[4*(Nr+1)])
{
    word key[4];
    for(int i = 0; i < 4; ++i)
        key[i] = w[i];
    AddRoundKey(in,key);
    for(int round = 1; round<Nr; ++round)
    {
        SubBytes(in);
        ShiftRow(in);
        MixColumns(in);
        for(int i=0; i<4; ++i)
            key[i] = w[4*round+i];
        AddRoundKey(in,key);
    }
    SubBytes(in);
    ShiftRow(in);
    for(int i=0; i<4; ++i)
        key[i] = w[4*Nr+i];
    AddRoundKey(in,key);
}
};//namespace AES

#endif

