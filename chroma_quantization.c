/*----------------------------------------------------------------*
*        Title: chroma_quantization.c
*        by Eli Lagorga and Conor Jenkison
*        Date: October 23, 2016
*        Assignment: HW3: Arith a lossy image compression
*        Summary: 
*        Module that contains chroma quantization conversions ensures
*        chroma values are between -0.5 and 0.5 after compression 
*------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include "arith40.h"
#include "chroma_quantization.h"

static float check_bounds(float index);

extern unsigned Pb_index(float Pb1, float Pb2, float Pb3, float Pb4)
{
    float avg = (Pb1 + Pb2 + Pb3 + Pb4) / 4;
    return Arith40_index_of_chroma(avg);
}

extern unsigned Pr_index(float Pr1, float Pr2, float Pr3, float Pr4)
{
    float avg = (Pr1 + Pr2 + Pr3 + Pr4) / 4;
    return Arith40_index_of_chroma(avg);
}

extern float Pb_value(unsigned index)
{
    float Pb = Arith40_chroma_of_index(index);
    return check_bounds(Pb);
}

extern float Pr_value(unsigned index)
{
    float Pr = Arith40_chroma_of_index(index);
    return check_bounds(Pr);
}

static float check_bounds(float index)
{
    if (index < -0.5) {
        return -0.5;
    } 
    else if (index > 0.5) {
        return 0.5;
    } 
    else {
        return index;
    }
}
