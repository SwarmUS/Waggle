#ifndef BBZ_UTILS_H
#define BBZ_UTILS_H

#include <stdint.h>

#define BBZFLOAT_SIGNMASK 0x8000
#define BBZFLOAT_EXPMASK  0x7E00
#define BBZFLOAT_FRACMASK 0x01FF

#define BBZFLOAT_SIGNSHIFT 15
#define BBZFLOAT_EXPSHIFT  9

typedef uint16_t bbzfloat;

bbzfloat bbzfloat_fromfloat(float f);

#endif
