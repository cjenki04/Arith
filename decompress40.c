/*----------------------------------------------------------------*
*        Title: decompress40.c
*        by Eli Lagorga and Conor Jenkison
*        Date: October 23, 2016
*        Assignment: HW3: Arith a lossy image compression
*        Summary: 
*        This file is designed to handle the decompression of 
*        of text files containing codewords passed from cammand 
*                line with argument -d. It reads compressed image header, 
*                decompresses image and prints the image using pnm_ppm interface
*------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <pnm.h>
#include <a2methods.h>
#include <a2plain.h>
#include <assert.h>
#include "blocked_pixels.h"
#include "rgb_cvideo.h"
#include "chroma_quantization.h"
#include "blocked_word.h"
#include "read_write_words.h"

#define A2 A2Methods_UArray2

/* reads compressed image, writes PPM */
extern void decompress40(FILE *input)
{
        unsigned width, height;
        int read = fscanf(input, "COMP40 Compressed image format 2\n%u %u", 
                                                                                        &width, &height);
        assert(read == 2);
        int c = getc(input);
        assert(c == '\n');

        A2 words = read_compressed(input, width, height);
        A2 blocks = unmake_words(words);
        A2 cvideo = unblock_pixels(blocks);
        A2 pixels = cvideo_to_rgb(cvideo);

        A2Methods_T methods = uarray2_methods_plain;

                struct Pnm_ppm image = {.width = width, .height = height, 
            .denominator = 255, .pixels = pixels, .methods = methods};
    
        Pnm_ppmwrite(stdout, &image);
}