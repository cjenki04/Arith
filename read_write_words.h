#ifndef READ_WRITE_WORD_INCLUDED
#define READ_WRITE_WORD_INCLUDED

#define A2 A2Methods_UArray2

/* 
 * uses bitpack to make uint32_t codeword out of struct containing
 * luminance and color diffrences for a 2x2 block of pixels,
 * prints codewords to stdout
 */
extern void write_compressed(A2 words);

/* 
 * reads uint32_t code words from stdin, uses bitpack to build 
 * struct containing luminance and color diffrence for 2x2 block
 * of pixels
 */
extern A2 read_compressed(FILE *input, int width, int height);

#endif