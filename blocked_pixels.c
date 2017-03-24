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

#include <stdlib.h>
#include <stdio.h>
#include <pnm.h>
#include <a2methods.h>
#include <a2blocked.h>
#include <a2plain.h>
#include "blocked_pixels.h"
#include "rgb_cvideo.h"

#define methods uarray2_methods_plain
#define A2 A2Methods_UArray2

const int BLOCK_SIZE = 2;

void block_transformation(int i, int j, A2 array2, A2Methods_Object *ptr, void *cl);
void unblock_transformation(int i , int j, A2 pixels, A2Methods_Object *ptr, void *cl);
int dimensions(int dimension);

extern A2 block_pixels(A2 cvideo)
{
        /* trim odd width and height */
        int width = methods->width(cvideo)/BLOCK_SIZE;
        int height = methods->height(cvideo)/BLOCK_SIZE;

        /* 2d array of 2x2 blocks of integer represented pixels */
        A2 blocks = methods->new(width, height, sizeof(struct Blocked_Pixel));

        methods->map_row_major(blocks, &block_transformation, cvideo);

        methods->free(&cvideo);

        return blocks;
}

int dimensions(int dimension)
{
        if (dimension % 2 != 0) {
            return (dimension - 1);
        } else {
            return dimension;
        }
}

void block_transformation(int i, int j, A2 pixels, A2Methods_Object *ptr, void *cl)
{
        (void)pixels;

        /* get image from closure */
        A2 image = (struct A2*)cl;
        Blocked_Pixel bp = (struct Blocked_Pixel*)ptr;

        CVideo p = methods->at(image, i*BLOCK_SIZE, j*BLOCK_SIZE);
        bp->Y1 = p->Y;
        bp->Pb1 = p->Pb;
        bp->Pr1 = p->Pr;
        
        p = methods->at(image, i*BLOCK_SIZE + 1,  j*BLOCK_SIZE);
        bp->Y2 = p->Y;
        bp->Pb2 = p->Pb;
        bp->Pr2 = p->Pr;
        
        p = methods->at(image, i*BLOCK_SIZE, j*BLOCK_SIZE + 1);
        bp->Y3 = p->Y;
        bp->Pb3 = p->Pb;
        bp->Pr3 = p->Pr;
        
        p = methods->at(image, i*BLOCK_SIZE + 1, j*BLOCK_SIZE + 1);
        bp->Y4 = p->Y;
        bp->Pb4 = p->Pb;
        bp->Pr4 = p->Pr;
}

extern A2Methods_UArray2 unblock_pixels(A2 blocked)
{
        int width = methods->width(blocked);
        int height = methods->height(blocked);
        
        A2 unblocked = methods->new(width*BLOCK_SIZE, height*BLOCK_SIZE, sizeof(struct CVideo));
        methods->map_row_major(blocked, &unblock_transformation, unblocked);

        return unblocked;

}

void unblock_transformation(int i , int j, A2Methods_UArray2 pixels, A2Methods_Object *ptr, void *cl)
{
        A2Methods_UArray2 unblocked = (struct A2Methods_UArray2*)cl;
        Blocked_Pixel bp = (struct Blocked_Pixel*)ptr;
        (void) pixels;

        CVideo p = methods->at(unblocked, i*BLOCK_SIZE, j*BLOCK_SIZE);
        p->Y = bp->Y1;
        p->Pb = bp->Pb1;
        p->Pr = bp->Pr1;
        
        p = methods->at(unblocked, i*BLOCK_SIZE + 1,  j*BLOCK_SIZE);
        p->Y = bp->Y2;
        p->Pb = bp->Pb2;
        p->Pr = bp->Pr2;
        
        p = methods->at(unblocked, i*BLOCK_SIZE, j*BLOCK_SIZE + 1);
        p->Y = bp->Y3;
        p->Pb = bp->Pb3;
        p->Pr = bp->Pr3;
        
        p = methods->at(unblocked, i*BLOCK_SIZE + 1, j*BLOCK_SIZE + 1);
        p->Y = bp->Y4;
        p->Pb = bp->Pb4;
        p->Pr = bp->Pr4;

}


