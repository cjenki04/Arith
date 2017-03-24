/*----------------------------------------------------------------*
*        Title: blocked_pixels.c
*        by Eli Lagorga and Conor Jenkison
*        Date: October 23, 2016
*        Assignment: HW3: Arith a lossy image compression
*        Summary: 
*        Module that converts from single floating point component
*        video pixel to 2x2 block of floating point pixel components
*        and back from block of pixels to 4 unblocked, single pixels
*------------------------------------------------------------------*/

#include <a2methods.h>
#include <a2blocked.h>
#include <a2plain.h>
#include <assert.h>
#include "blocked_pixels.h"
#include "rgb_cvideo.h"
#include "chroma_quantization.h"
#include <stdlib.h>
#include <stdio.h>
#include "discrete_cosine_transform.h"
#include "blocked_word.h"

#define methods uarray2_methods_plain
#define A2 A2Methods_UArray2

void block_to_word(int i, int j, A2 pixels, A2Methods_Object *ptr, void *cl);
void word_to_block(int i, int j, A2 pixels, A2Methods_Object *ptr, void *cl);

extern A2 make_words(A2 blocks)
{
        A2 words = methods->new(methods->width(blocks), 
                                methods->height(blocks), 
                                sizeof(struct Word_Values));

        methods->map_row_major(words, &block_to_word, blocks);

        methods->free(&blocks);

        return words;
}


void block_to_word(int i, int j, A2 pixels, A2Methods_Object *ptr, void *cl)
{
        (void)pixels;
    
        A2 blocked_pixels = (struct A2*)cl;

        Blocked_Pixel bp = (struct Blocked_Pixel*)methods->at(blocked_pixels,
                                                                         i, j);

        Word_Values wv = (struct Word_Values*)ptr;

        wv->a = calc_a(bp->Y1, bp->Y2, bp->Y3, bp->Y4);
        wv->b = calc_b(bp->Y1, bp->Y2, bp->Y3, bp->Y4);
        wv->c = calc_c(bp->Y1, bp->Y2, bp->Y3, bp->Y4);
        wv->d = calc_d(bp->Y1, bp->Y2, bp->Y3, bp->Y4);

        wv->Pb = Pb_index(bp->Pb1, bp->Pb2, bp->Pb3, bp->Pb4);
        wv->Pr = Pr_index(bp->Pr1, bp->Pr2, bp->Pr3, bp->Pr4);
    
}

extern A2 unmake_words(A2 words)
{
        A2 blocks = methods->new(methods->width(words), 
                                 methods->height(words), 
                                 sizeof(struct Blocked_Pixel));

        methods->map_row_major(blocks, &word_to_block, words);

        methods->free(&words);

        return blocks;
}

void word_to_block(int i, int j, A2 pixels, A2Methods_Object *ptr, void *cl)
{
        (void)pixels;
    
        A2 word_vals = (struct A2*)cl;

        Word_Values wv = (struct Word_Values*)methods->at(word_vals, i, j);

        Blocked_Pixel bp = (struct Blocked_Pixel*)ptr;

        bp->Y1 = calc_Y1(wv->a, wv->b, wv->c, wv->d);
        bp->Y2 = calc_Y2(wv->a, wv->b, wv->c, wv->d);
        bp->Y3 = calc_Y3(wv->a, wv->b, wv->c, wv->d);
        bp->Y4 = calc_Y4(wv->a, wv->b, wv->c, wv->d);

        bp->Pb1 = Pb_value(wv->Pb);
        bp->Pb2 = Pb_value(wv->Pb);
        bp->Pb3 = Pb_value(wv->Pb);
        bp->Pb4 = Pb_value(wv->Pb);

        bp->Pr1 = Pr_value(wv->Pr);
        bp->Pr2 = Pr_value(wv->Pr);
        bp->Pr3 = Pr_value(wv->Pr);
        bp->Pr4 = Pr_value(wv->Pr);
}

