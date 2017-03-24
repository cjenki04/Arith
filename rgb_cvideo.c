/*----------------------------------------------------------------*
*        Title: rgb_cvideo.c
*        by Eli Lagorga and Conor Jenkison
*        Date: October 23, 2016
*        Assignment: HW3: Arith a lossy image compression
*        Summary: 
*        Module that converts rgb integer representation of pixel to 
*        floating point component video representation and back from
*        component video to rgb, ensures rgb values between 0 and 255
*        ofter decompression
*------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <pnm.h>
#include <a2methods.h>
#include <a2plain.h>
#include "rgb_cvideo.h"

#define methods uarray2_methods_plain
#define A2 A2Methods_UArray2

void to_cvideo(int i, int j, A2 pixels, A2Methods_Object *ptr, void *cl);
float calc_brightness(int red, int green, int blue);
float calc_color_diff_blue(int red, int green, int blue);
float calc_color_diff_red(int red, int green, int blue);

void to_rgb(int i, int j, A2 pixels, A2Methods_Object *ptr, void *cl);
int calc_red(float Y, float Pb, float Pr);
int calc_green(float Y, float Pb, float Pr);
int calc_blue(float Y, float Pb, float Pr);
static float check_bounds(int value);

extern A2 rgb_to_cvideo(A2 rgb)
{
        A2 cvideo = methods->new(methods->width(rgb), 
                                 methods->height(rgb), 
                                 sizeof(struct CVideo));

        methods->map_row_major(rgb, &to_cvideo, cvideo);

        return cvideo;
}

void to_cvideo(int i, int j, A2 pixels, A2Methods_Object *ptr, void *cl)
{
        (void) pixels;

        Pnm_rgb rgb = (struct Pnm_rgb*)ptr;
        
        A2 cvideo_pixels = (A2*)cl;
        CVideo ypp = (CVideo)methods->at(cvideo_pixels, i, j);

        ypp->Y = calc_brightness(rgb->red, rgb->green, rgb->blue);
        ypp->Pb = calc_color_diff_blue(rgb->red, rgb->green, rgb->blue);
        ypp->Pr = calc_color_diff_red(rgb->red, rgb->green, rgb->blue);
}

float calc_brightness(int red, int green, int blue)
{
        return (float) ((0.299 * red + 0.587 * green + 0.114 * blue)/255);
}

float calc_color_diff_blue(int red, int green, int blue)
{
        return (float) ((-0.168736 * red - 0.331264 * green + 0.5 * blue)/255);
}

float calc_color_diff_red(int red, int green, int blue)
{
        return (float) ((0.5 * red - 0.418688 * green - 0.081312 * blue)/255);
}


extern A2 cvideo_to_rgb(A2 cvideo)
{
        int width = methods->width(cvideo);
        int height = methods->height(cvideo);

        A2 rgb = methods->new(width, height, sizeof(struct Pnm_rgb));

        methods->map_row_major(cvideo, &to_rgb, rgb);

        methods->free(&cvideo);

        return rgb;
}

void to_rgb(int i, int j, A2 pixels, A2Methods_Object *ptr, void *cl)
{
        (void) pixels;

        CVideo ypp = (struct CVideo*)ptr;

        A2 rgb_pixels = (A2*)cl;
        Pnm_rgb rgb = (Pnm_rgb)methods->at(rgb_pixels, i, j);

        rgb->red = calc_red(ypp->Y, ypp->Pb, ypp->Pr);
        rgb->green = calc_green(ypp->Y, ypp->Pb, ypp->Pr);
        rgb->blue = calc_blue(ypp->Y, ypp->Pb, ypp->Pr);
}

int calc_red(float Y, float Pb, float Pr)
{
        (void)Pb;
        int R = (float) ((Y + 1.402 * Pr)*255);
        return check_bounds(R);
}

int calc_green(float Y, float Pb, float Pr)
{
        int G = (float) ((Y - 0.344136 * Pb - 0.714136 * Pr)*255);
        return check_bounds(G);
}
int calc_blue(float Y, float Pb, float Pr)
{
        (void)Pr;
        int B = (float) ((Y + 1.772 * Pb)*255);
        return check_bounds(B);
}

static float check_bounds(int value)
{
    if (value < 0) {
        return 0;
    } 
    else if (value > 255) {
        return 255;
    } 
    else {
        return value;
    }
}


#undef methods
#undef A2

