#include "bbz_utils.h"

bbzfloat bbzfloat_fromfloat(float f) {
    /* We assume float respect the IEEE754 format */
    /* Buffer for the bbzfloat */
    bbzfloat x;
    /* Copy the sign */
    x = ((*(uint32_t*)(&f)) & 0x80000000) >> 16;
    /* Check exponent */
    int16_t e = ((*(uint32_t*)(&f)) & 0x7F800000) >> 23;
    if(e > 96 && e < 158) {
        /* Float value is within the range of bbzfloat */
        /* Set exponent */
        x |= (e - 96) << BBZFLOAT_EXPSHIFT;
        /* Set fraction */
        x |= ((*(uint32_t*)(&f)) & 0x7FFFFF) >> 14;
    }
    else if(e > 0 && e < 0xFF) {
        /* Normalized value, but too big to fit -> Inf */
        /* Set exponent */
        x |= BBZFLOAT_EXPMASK;
    }
    else if(e == 0xFF) {
        /* Inf or NaN */
        /* Set exponent */
        x |= BBZFLOAT_EXPMASK;
        /* Set fraction, actual value doesn't matter, only 0 or <>0 */
        x |= (*(uint32_t*)(&f)) & BBZFLOAT_FRACMASK;
    }
    /* Nothing to do for the case e <= 96, as the values are already all zeroes */
    return x;
}