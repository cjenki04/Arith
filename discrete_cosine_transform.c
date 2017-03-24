/*----------------------------------------------------------------*
*        Title: chroma_quantization.c
*        by Eli Lagorga and Conor Jenkison
*        Date: October 23, 2016
*        Assignment: HW3: Arith a lossy image compression
*        Summary: 
*        Module that contains chroma quantization conversions ensures
*        luminance coefficient are between -0.3 and 0.3 after compression 
*------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include "discrete_cosine_transform.h"

static float check_bounds(float avg);

extern unsigned calc_a(float Y1, float Y2, float Y3, float Y4)
{
    float avg = (Y1 + Y2 + Y3 + Y4) / 4;
    return (float) (avg * 63);
}

extern signed calc_b(float Y1, float Y2, float Y3, float Y4)
{
    float avg = (Y4 + Y3 - Y2 - Y1) / 4;
    return (float) check_bounds(avg) * 103.3;
}

extern signed calc_c(float Y1, float Y2, float Y3, float Y4)
{
    float avg = (Y4 - Y3 + Y2 - Y1) / 4;
    return (float) check_bounds(avg) * 103.3;
}

extern signed calc_d(float Y1, float Y2, float Y3, float Y4)
{
    float avg = (Y4 - Y3 - Y2 + Y1) / 4;
        return (float) check_bounds(avg) * 103.3;
}

static float check_bounds(float avg)
{
    if (avg < -0.3) {
        return -0.3;
    } 
    else if (avg > 0.3) {
        return 0.3;
    } 
    else {
        return avg;
    }
}

extern float calc_Y1(unsigned a, signed b, signed c, signed d)
{
    float Y1 = (float) (a - b - c + d)/63;
    return Y1;
}

extern float calc_Y2(unsigned a, signed b, signed c, signed d)
{
    float Y2 = (float)( a - b + c - d)/63;
    return Y2;

}

extern float calc_Y3(unsigned a, signed b, signed c, signed d)
{
    float Y3 = (float) (a + b - c - d)/63;
    return Y3;

}

extern float calc_Y4(unsigned a, signed b, signed c, signed d)
{
    float Y4 = (float) (a + b + c + d)/63;
    return Y4;
}
