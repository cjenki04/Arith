/*----------------------------------------------------------------*
*        Title: compress40.c
*        by Eli Lagorga and Conor Jenkison
*        Date: October 23, 2016
*        Assignment: HW3: Arith a lossy image compression
*        Summary: 
*        This file is designed to handle the compression of 
*        of images passed from cammand line with argument -c.
*        It prints the compressed file header and trims images
*        with odd width or height. It also handles the decompression
*         of text files containing codewords passed from cammand 
*        line with argument -d. It reads compressed image header, 
*        decompresses image and prints the image using pnm_ppm interface
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

int check_dimensions(int dimension);

/* reads PPM, writes compressed image */
extern void compress40(FILE *input)
{
        A2Methods_T methods = uarray2_methods_plain;
        assert(methods);

        Pnm_ppm image = Pnm_ppmread(input, methods);

        /* trim odd width and height */
        int width = check_dimensions(image->width);
        int height = check_dimensions(image->height);
        
        /* prints header for compressed image */
        printf("COMP40 Compressed image format 2\n%u %u", width, height);
        printf("\n");

        A2 cvideo = rgb_to_cvideo(image->pixels);
        A2 blocks = block_pixels(cvideo);
        A2 words = make_words(blocks);
        write_compressed(words);

        Pnm_ppmfree(&image);
} 

/* corrects odd dimentions */
int check_dimensions(int dimension)
{
        if (dimension % 2 != 0) {
                return (dimension - 1);
        } else {
                return dimension;
        }
}

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

#undef A2