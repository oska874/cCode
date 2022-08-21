#include <stdio.h>
#include <stdlib.h>
#include "NE10.h"
int main(void)
{
    ne10_int32_t i;
    ne10_float32_t thesrc[5];
    ne10_float32_t thecst;
    ne10_float32_t thedst1[5];
    ne10_float32_t thedst2[5];
    for (i=0; i<5; i++) {
        thesrc[i] = (ne10_float32_t) rand()/RAND_MAX*5.0f;
    }
    thecst = (ne10_float32_t) rand()/RAND_MAX*5.0f;
    ne10_addc_float_c( thedst1, thesrc, thecst, 5 );
    ne10_addc_float_neon( thedst2, thesrc, thecst, 5 );
    printf("==========end=========\n");
    return 0;
}
