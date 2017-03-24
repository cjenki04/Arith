#ifndef BLOCKED_WORD_INCLUDED
#define BLOCKED_WORD_INCLUDED

typedef struct Word_Values *Word_Values;
/* integer representation of blocked pixel          *   
 * following quantization and cosine transformation */
struct Word_Values { 
        unsigned a;
        signed b;
        signed c;
        signed d;
        unsigned Pb;
        unsigned Pr;
};

/* 
 * converts blocked floating point pixel representaion
 * to struct containting compressed word parts
 */
extern A2Methods_UArray2 make_words(A2Methods_UArray2 blocks);

/* 
 * decompresses word values into 2x2 blocked floating 
 * point pixels
 */
extern A2Methods_UArray2 unmake_words(A2Methods_UArray2 words);

#endif

