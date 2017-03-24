#ifndef CHROMA_QUANTIZATION_INCLUDED
#define CHROMA_QUANTIZATION_INCLUDED

extern unsigned Pb_index(float Pr1, float Pr2, float Pr3, float Pr4);
extern unsigned Pr_index(float Pb1, float Pb2, float Pb3, float Pb4);
extern float Pb_value(unsigned index);
extern float Pr_value(unsigned index);

#endif