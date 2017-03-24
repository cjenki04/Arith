#include "rgb_cvideo.h"

#ifndef BLOCK_PIXELS_INCLUDED
#define BLOCK_PIXELS_INCLUDED

typedef struct Blocked_Pixel *Blocked_Pixel;
/* 4 colored pixel floating points */
struct Blocked_Pixel {
        float Y1, Pb1, Pr1,
              Y2, Pb2, Pr2,
              Y3, Pb3, Pr3,
              Y4, Pb4, Pr4;
};

/* 
 * performs non-linear transformation on uarray2b of pixels
 * maps 2x2 block of pixels to single blocked pixel representation
 * trims images if height or width are odd
 */
extern A2Methods_UArray2 block_pixels(A2Methods_UArray2 image);

/* 
 * performs transformation on uarray2b of blocked pixels
 * maps block pixel representation to 2x2 single pixel representation
 */
extern A2Methods_UArray2 unblock_pixels(A2Methods_UArray2 image);

#undef T
#endif


