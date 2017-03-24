#ifndef RGB_CVIDEO_INCLUDED
#define RGB_CVIDEO_INCLUDED

#define A2 A2Methods_UArray2

typedef struct CVideo *CVideo;
/* colored pixel (floating point) */
struct CVideo {
        float Y, Pb, Pr;
};

/* 
 * converts rgb integer representation of pixel to CVideo
 * floating-point representation of pixel
 */
extern A2 rgb_to_cvideo(A2 rgb);

/* 
 * converts CVideo floating-point representation of pixel
 * to rgb integer representation of pixel
 */
extern A2 cvideo_to_rgb(A2 cvideo);

#undef A2
#endif




