#ifndef DISCRETE_COSINE_TRANSFORM_INCLUDED
#define DISCRETE_COSINE_TRANSFORM_INCLUDED

extern unsigned calc_a(float Y1, float Y2, float Y3, float Y4);
extern signed   calc_b(float Y1, float Y2, float Y3, float Y4);
extern signed   calc_c(float Y1, float Y2, float Y3, float Y4);
extern signed   calc_d(float Y1, float Y2, float Y3, float Y4);
extern float    calc_Y1(unsigned a, signed b, signed c, signed d);
extern float    calc_Y2(unsigned a, signed b, signed c, signed d);
extern float    calc_Y3(unsigned a, signed b, signed c, signed d);
extern float    calc_Y4(unsigned a, signed b, signed c, signed d);

#endif

