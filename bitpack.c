/*----------------------------------------------------------------*
*        Title: bitpack.c
*        by Eli Lagorga and Conor Jenkison
*        Date: October 23, 2016
*        Assignment: HW3: Arith a lossy image compression
*        Summary: 
*        Packs signed and unsigned integer values into 32 bit word,
*        raises Bitpack_Overflow if value cannot be represented in
*        specified number of bits.
*------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <assert.h>
#include "except.h"
#include "bitpack.h"

Except_T Bitpack_Overflow = { "Overflow packing bits" };

bool Bitpack_fitsu(uint64_t n, unsigned width)
{
    assert(width!=0);
    unsigned max = (2 << (width-1)) -1;
    unsigned min = 0;

    if (n <= max && n >= min){
        return true;
    } else {
        return false;
    }
}

bool Bitpack_fitss(int64_t n, unsigned width)
{
    assert(width != 0);    
    int max, min;

    if (width == 1){
        min = -1;
        max = 0;
    }
    else {
    min = ~(2 << (width-2)) + 1;
    max = (2 << (width-2)) - 1;
    }

    if ((n >= min) && (n <= max)){
        return true;
    } else {
        return false;
    }
}

uint64_t Bitpack_getu( uint64_t word, unsigned width, unsigned lsb)
{
    assert(width > 0 && width < 64);

    uint64_t mask = ~0;
    mask = mask >> (64 - width) << lsb;
    return (mask & word) >> lsb;

}

int64_t Bitpack_gets( uint64_t word, unsigned width, unsigned lsb)
{
    assert(width > 0 && (width + lsb) < 64);
    
    uint64_t mask = ~0;
    mask = mask >> (64 - width) << (64 - width);
    word = word << (64 - (width + lsb));
    int64_t new = (mask & word);
    return new >> (64 - width);

}
uint64_t Bitpack_newu( uint64_t word, unsigned width, unsigned lsb,
                                                      uint64_t value)
{
    assert(width > 0 && width < 64);
    if (!Bitpack_fitsu(value, width)) {
        RAISE(Bitpack_Overflow);
    }

    uint64_t mask = ~0;
    mask = mask >> (64 - width) << lsb;
    word = (~mask & word);
    return (word | (value << lsb));
}


uint64_t Bitpack_news( uint64_t word, unsigned width, unsigned lsb, 
                                                      int64_t value)
{
    assert(width > 0 && (width + lsb) < 64);
    if (!Bitpack_fitss(value, width)) {
        RAISE(Bitpack_Overflow);
    }
    
    uint64_t mask;
    if (value < 0){
        mask = ~0;
        mask = mask >> (64 - width) << lsb;
        mask = (mask | word);
        return (mask & (value << lsb));
    } else{
        mask = ~0;
        mask = mask >> (64 - width) << lsb;
        mask = (~mask & word);
        return (mask | (value << lsb));
    }
}




