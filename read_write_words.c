/*----------------------------------------------------------------*
*        Title: read_write_words.c
*        by Eli Lagorga and Conor Jenkison
*        Date: October 23, 2016
*        Assignment: HW3: Arith a lossy image compression
*        Summary: 
*        Writes and reads uint32_t code word using bitpack.h interface
*        given specific packing instructions for feilds width and lsb
*------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <pnm.h>
#include <a2methods.h>
#include <a2blocked.h>
#include <a2plain.h>
#include <assert.h>
#include "blocked_word.h"
#include "bitpack.h"

#define methods uarray2_methods_plain
#define A2 A2Methods_UArray2

void write_codewords(int i, int j, A2 pixels, A2Methods_Object *ptr, void *cl);
void read_codewords(int i, int j, A2 pixels, A2Methods_Object *ptr, void *cl);

extern void write_compressed(A2 words)
{
        methods->map_row_major(words, &write_codewords, NULL);

        methods->free(&words);    
}

void write_codewords(int i, int j, A2 pixels, A2Methods_Object *ptr, void *cl) 
{
        (void)pixels;
        (void)i;
        (void)j;
        (void)cl;
    
        Word_Values wv = (struct Word_Values*)ptr;

        uint32_t word = 0;
        word = Bitpack_newu(word, 6, 26, wv->a);
        word = Bitpack_news(word, 6, 20, wv->b);
        word = Bitpack_news(word, 6, 14, wv->c);
        word = Bitpack_news(word, 6, 8, wv->d);
        word = Bitpack_newu(word, 4, 4, wv->Pb);
        word = Bitpack_newu(word, 4, 0, wv->Pr);

        printf("%" PRIu32 "\n", word);
}

extern A2 read_compressed(FILE *input, int width, int height)
{
        A2 words = methods->new(width/2, height/2, sizeof(struct Word_Values));
    
        methods->map_row_major(words, &read_codewords, input);

        return words;
}

void read_codewords(int i, int j, A2 pixels, A2Methods_Object *ptr, void *cl) 
{ 
        (void)pixels;
        (void)i;
        (void)j;

        FILE *input = (FILE*)cl;

        uint32_t word;
        fscanf(input, "%" PRIu32 "\n", &word);

        Word_Values wv = (struct Word_Values*)ptr;

        wv->a = Bitpack_getu(word, 6, 26);
        wv->b = Bitpack_gets(word, 6, 20);
        wv->c = Bitpack_gets(word, 6, 14);
        wv->d = Bitpack_gets(word, 6, 8);
        wv->Pb = Bitpack_getu(word, 4, 4);
        wv->Pr = Bitpack_getu(word, 4, 0);
}







