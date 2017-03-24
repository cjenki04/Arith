#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

const int DIFF = 50;

/*int main(int argc, char *argv[])
{
    assert(argc == 3);
    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "r");

    unsigned width, height;
    unsigned a1, a2, Pb_i1, Pb_i2, Pr_i1, Pr_i2;
    signed b1, b2, c1, c2, d1, d2;
    fscanf(input, "header: %u, %u \n", &width, &height);
    for (unsigned i=0; i < width*height; i++) {
        fscanf(input, "a: %u, b: %i, c: %i, d: %i, Pb: %u, Pr: %u \n",
                                  &a1, &b1, &c1, &d1, &Pb_i1, &Pr_i1);
        fscanf(output, "a: %u, b: %i, c: %i, d: %i, Pb: %u, Pr: %u \n",
                                  &a2, &b2, &c2, &d2, &Pb_i2, &Pr_i2);
        if (a1 != a2 || b1 != b2 || c1 != c2 || d1 != d2 
                     || Pb_i1 != Pb_i2 || Pr_i1 != Pr_i2) {
                printf("not same\n");
        }
    }
}*/

int main(int argc, char *argv[])
{
    assert(argc == 3);
    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "r");

    unsigned width, height;
    int read = fscanf(input, "COMP40 Compressed image format 2\n%u %u", 
                                 &width, &height);
    assert(read == 2);
    int c = getc(input);
    assert(c == '\n');

    int ir, ig, ib, or, og, ob, r, g, b;
    int dr = 0;
    int dg = 0; 
    int db = 0;
    int off = 0;
    unsigned pixels = width * height;
    for (unsigned i=0; i < pixels; i++) {
        fscanf(input, "R: %i G: %i B: %i \n", &ir, &ig, &ib);
        fscanf(output, "R: %i G: %i B: %i \n", &or, &og, &ob);
        assert(ir != 0 && or != 0 && ig != 0 && og != 0 && ib != 0 && ob != 0);
        if (ir > or) {
            r = ir - or;
            dr += r;
        } else {
            r = or - ir;
            dr += r;
        }
        if (ig > og) {
            g = ig - og;
            dg += g;
        } else {
            g = og - ig;
            dg += g;
        }
        if (ib > ob) {
            b = ib - ob;
            db += b;
        } else {
            b = ob - ib;
            db += b;
        }
        if (r >= DIFF || g >= DIFF || b >= DIFF) {
                printf("Input  R: %i G: %i B: %i \n", ir, ig, ib);
                printf("Output R: %i G: %i B: %i \n", or, og, ob);
                off++;
        }
    }
    printf("Total Diffrence - R: %i G: %i B: %i \n", dr, dg, db);

    float avgR = (float) dr / (width * height);
    float avgG = (float) dg / (width * height);
    float avgB = (float) db / (width * height);
    printf("Average Diffrence - R: %f G: %f B: %f \n", avgR, avgG, avgB);
    printf("off / total: %i / %i\n", off, width*height);
    return 0;
 }